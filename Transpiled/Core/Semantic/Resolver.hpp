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
	class Resolver
	{
		public: SymbolScope* m_pGlobalScope;
		public: OwnedVector<SymbolScope*>* m_pScopeVector;
		protected: Vector<Symbol*>* m_pBuildTempSymbolVector;
		public: Resolver();
		protected: ClassDecl* GetClassDeclFromOwnerAST(AST* pOwner);
		protected: SymbolScope* CreateChildScope(AST* pNode, SymbolScope* pParent, SymbolScope::Kind eKind);
		protected: void AddSymbolToScope(SymbolScope* pScope, const char* sShortName, Symbol::Kind eKind, AST* pDeclAST, const char* sQualifiedName);
		public: SymbolScope* GetEnclosingScope(AST* pNode);
		protected: void EnsureClassScope(AST* pOwnerNode);
		protected: void AddGenericParamsToScope(ClassDecl* pClassDecl, SymbolScope* pScope);
		protected: void AddMemberSymbolToScope(AST* pMemberNode, SymbolScope* pScope);
		public: void BuildForRoot(AST* pRoot);
		protected: void BuildForNode(AST* pNode, SymbolScope* pScope);
		public: void ResolveInScopeChainNoBaseClasses(const char* sName, SymbolScope* pStartScope, Vector<Symbol*>* pOut);
		public: void ResolveInScopeChain(const char* sName, SymbolScope* pStartScope, Vector<Symbol*>* pOut);
		public: void ResolveFromNode(AST* pNode, const char* sName, Vector<Symbol*>* pOut);
		public: virtual ~Resolver();
	};
}

