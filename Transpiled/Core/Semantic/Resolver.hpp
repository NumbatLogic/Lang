#pragma once

#include "../../../../LangShared/Transpiled/Vector/OwnedVector.hpp"
#include "SymbolScope.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
#include "Symbol.hpp"

namespace NumbatLogic
{
	class SymbolScope;
	template <class T>
	class OwnedVector;
	template <class T>
	class Vector;
	class Symbol;
	class ClassDecl;
	class AST;
}
#line 1 "../../../Source/Core/Semantic/Resolver.nll"
namespace NumbatLogic
{
#line 5 "../../../Source/Core/Semantic/Resolver.nll"
	class Resolver
	{
#line 8 "../../../Source/Core/Semantic/Resolver.nll"
		public: SymbolScope* m_pGlobalScope;
#line 12 "../../../Source/Core/Semantic/Resolver.nll"
		public: OwnedVector<SymbolScope*>* m_pScopeVector;
#line 15 "../../../Source/Core/Semantic/Resolver.nll"
		protected: Vector<Symbol*>* m_pBuildTempSymbolVector;
#line 17 "../../../Source/Core/Semantic/Resolver.nll"
		public: Resolver();
#line 28 "../../../Source/Core/Semantic/Resolver.nll"
		protected: ClassDecl* GetClassDeclFromOwnerAST(AST* pOwner);
#line 42 "../../../Source/Core/Semantic/Resolver.nll"
		protected: SymbolScope* CreateChildScope(AST* pNode, SymbolScope* pParent, SymbolScope::Kind eKind);
#line 53 "../../../Source/Core/Semantic/Resolver.nll"
		protected: void AddSymbolToScope(SymbolScope* pScope, const char* sShortName, Symbol::Kind eKind, AST* pDeclAST, const char* sQualifiedName);
#line 70 "../../../Source/Core/Semantic/Resolver.nll"
		public: SymbolScope* GetEnclosingScope(AST* pNode);
#line 93 "../../../Source/Core/Semantic/Resolver.nll"
		protected: void EnsureClassScope(AST* pOwnerNode);
#line 131 "../../../Source/Core/Semantic/Resolver.nll"
		protected: void AddGenericParamsToScope(ClassDecl* pClassDecl, SymbolScope* pScope);
#line 143 "../../../Source/Core/Semantic/Resolver.nll"
		protected: void AddMemberSymbolToScope(AST* pMemberNode, SymbolScope* pScope);
#line 185 "../../../Source/Core/Semantic/Resolver.nll"
		public: void BuildForRoot(AST* pRoot);
#line 195 "../../../Source/Core/Semantic/Resolver.nll"
		protected: void BuildForNode(AST* pNode, SymbolScope* pScope);
#line 397 "../../../Source/Core/Semantic/Resolver.nll"
		public: void ResolveInScopeChainNoBaseClasses(const char* sName, SymbolScope* pStartScope, Vector<Symbol*>* pOut);
#line 414 "../../../Source/Core/Semantic/Resolver.nll"
		public: void ResolveInScopeChain(const char* sName, SymbolScope* pStartScope, Vector<Symbol*>* pOut);
#line 454 "../../../Source/Core/Semantic/Resolver.nll"
		public: void ResolveFromNode(AST* pNode, const char* sName, Vector<Symbol*>* pOut);
#line 5 "../../../Source/Core/Semantic/Resolver.nll"
		public: virtual ~Resolver();
	};
}

