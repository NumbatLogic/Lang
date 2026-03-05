## Resolver Architecture Plan

### Goal

Design a clean, efficient, and predictable name-resolution system for the language, independent of the current ad‑hoc `FindByName` logic.

---

### 1. Core data structures

- **Symbol kinds**
  - **Types**: namespace, class, struct, enum, type alias, generic parameter.
  - **Values**: variable, parameter, function, method, property, enum value.
  - **Others**: label, module, etc. as needed.

- **Symbol**
  - **Fields**:
    - `kind: SymbolKind`
    - `shortName: string`
    - `qualifiedName: string` (e.g. `NumbatLogic::Net::Socket`)
    - `decl: AST*` (pointer to declaring node)
    - `scope: Scope*` (owning scope)
  - For functions/methods: overload group:
    - `SymbolFunctionGroup { vector<FunctionSymbol*> overloads; }`

- **Scope**
  - **Kinds**: Global, Namespace, Class, Function, Block.
  - **Fields**:
    - `parent: Scope*`
    - `symbols: Map<string, vector<Symbol*>>` (overloads)
    - `usingNamespaces: vector<Scope*>` (optional, for `using namespace` behavior)
    - `associatedAST: AST*` (e.g. the `NamespaceDecl` or `ClassDecl` that owns it)

---

### 2. Resolution APIs (centralized resolver)

Create a `Resolver` module with:

- **Unqualified lookup**

  ```text
  ResolveUnqualified(Scope* scope, string name, SymbolKindMask mask) -> SymbolSet
  ```

  - Check `scope->symbols[name]` filtered by `mask`.
  - If no match, recursively check `scope->parent`, until global.
  - Optionally, check `usingNamespaces` of each scope in a well-defined order.

- **Qualified lookup**

  ```text
  ResolveQualified(Scope* scope, list<string> parts, SymbolKindMask mask) -> Symbol|SymbolSet
  ```

  - For `A::B::C`:
    - Resolve `A` in global (or as unqualified from `scope` if you allow that).
    - If `A` is a namespace or type, move into its **member scope** and resolve `B`.
    - Repeat down the chain; at last part, apply `mask` and return matches.

- **Type name resolution**

  ```text
  ResolveType(Scope* scope, TypeRefAST* typeRef) -> TypeSymbol
  ```

  - Parses type qualifiers (`const`, pointers, generics) but base name resolution is via `ResolveUnqualified` / `ResolveQualified` restricted to **type symbols**.

- **Value/Member access**

  ```text
  ResolveMember(Symbol* baseTypeOrNamespace, string name, SymbolKindMask mask) -> SymbolSet
  ```

  - For `obj.Method` or `Namespace::Func`, use the **member scope** of the base symbol and apply unqualified lookup **within that member scope only** (plus base-class hierarchy for types).

All expression and type resolution code calls these APIs rather than walking AST/namespace trees directly.

---

### 3. Symbol table construction phases

- **Phase 1: Collect declarations (global + namespaces)**

  - Walk all translation units.
  - For each top-level `NamespaceDecl`:
    - Build/lookup a `NamespaceScope` under the global scope for its full name (`NumbatLogic::Net`).
    - Register the namespace symbol if not already present.
  - For each top-level type/function:
    - Determine its enclosing namespace scope.
    - Create and register a `Symbol` for it in that scope.

- **Phase 2: Build member and local scopes**

  - For each `ClassDecl`:
    - Create a `ClassScope` with parent = its enclosing namespace/class scope.
    - Register all members (methods, fields, nested types) in that `ClassScope`.
  - For each `FunctionDecl`/`TorDecl`:
    - Create a `FunctionScope` with parent = enclosing namespace/class scope.
    - Register parameters and local type aliases there.
  - For each block (`Scope` AST):
    - Optionally create nested block scopes for local variables.

- **Phase 3: Handle imports/usings**

  - Process `using`/`import` declarations after main scopes exist:
    - For `using namespace X::Y;`, lookup that namespace scope and push into `scope->usingNamespaces`.

---

### 4. Tying resolver to AST nodes

- Each AST node that needs lookup (`TypeRef`, `Identifier`, `FunctionCall`, `NewExpr`, etc.) gets:

  - `Scope* currentScope;` set during an earlier “scope binding” pass:
    - As you traverse AST with a `Scope*` stack, assign `currentScope` to each child.

- During validation:

  - `TypeRef.Validate`:
    - If unqualified: call `ResolveType(currentScope, this)`.
    - If qualified: split `A::B::C`, call `ResolveQualified` with type mask.

  - `Identifier.Validate`:
    - If part of `Namespace::Name`: resolve base via `ResolveType`/`ResolveQualified`, then call `ResolveMember` on that namespace/type.
    - If unqualified: `ResolveUnqualified(currentScope, name, value/type mask)`; then infer `m_pValueType` from the symbol kind.

  - `FunctionCall.Validate`:
    - `foo()`:
      - Get candidates via `ResolveUnqualified(currentScope, "foo", function mask)`.
    - `obj.Method()`:
      - From `obj`’s type symbol, call `ResolveMember(objTypeSymbol, "Method", function mask)` and then overload-resolve by parameters.
    - `Namespace::Func()`:
      - Base namespace from resolver, then `ResolveMember(namespaceSymbol, "Func", function mask)`.

---

### 5. Ambiguity and error reporting

- **Ambiguous unqualified name**:
  - If `ResolveUnqualified` finds multiple symbols of the same priority (e.g. two types from two `using` namespaces), report a diagnostic:
    - “`Utils` is ambiguous between `N1::Utils` and `N2::Utils` – use a qualified name.”
- **Missing symbol**:
  - If no symbol found at all, emit “Unknown type/value” with a list of candidate namespaces (`currentScope` chain and `usingNamespaces`).

---

### 6. Performance considerations

- Use **hash maps** for `Scope.symbols` for O(1) average lookup by short name.
- Cache **fully-qualified names** on symbols; compute once.
- Optional: maintain a global map from fully qualified name → symbol for tools and quick qualified lookups.
- Lazy creation of some scopes (e.g. block scopes) if you want to avoid overhead in simple cases.

---

### 7. Migration strategy (high level)

Even though this plan ignores the current ad‑hoc logic, practically:

- Introduce the new `Scope`/`Symbol`/`Resolver` alongside old logic.
- Wire `TypeRef`, `Identifier`, and `FunctionCall` to call the new resolver first, and only fall back to the old `FindByName` paths temporarily.
- Once stable, remove the old `FindByName`/`FindClassDecl`-based resolution, keeping them only for legacy transforms or not at all.

This gives a single, centralized, namespace-aware resolver with explicit scopes and clear rules, which should prevent accidental cross-namespace binding.

