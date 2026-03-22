#pragma once

#include "../../../../LangShared/Transpiled/Vector/OwnedVector.hpp"
#include "SymbolScope.hpp"
#include "../../../../LangShared/Source/Vector/CPP/Vector.hpp"
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
#line 0 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
namespace NumbatLogic
{
#line 4 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
	class Resolver
	{
#line 7 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
		public: SymbolScope* m_pGlobalScope;
#line 11 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
		public: OwnedVector<SymbolScope*>* m_pScopeVector;
#line 14 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
		protected: Vector<Symbol*>* m_pBuildTempSymbolVector;
#line 16 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
		public: Resolver();
#line 27 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
		protected: ClassDecl* GetClassDeclFromOwnerAST(AST* pOwner);
#line 41 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
		protected: SymbolScope* CreateChildScope(AST* pNode, SymbolScope* pParent, SymbolScope::Kind eKind);
#line 52 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
		protected: void AddSymbolToScope(SymbolScope* pScope, const char* sShortName, Symbol::Kind eKind, AST* pDeclAST, const char* sQualifiedName);
#line 69 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
		public: SymbolScope* GetEnclosingScope(AST* pNode);
#line 92 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
		protected: void EnsureClassScope(AST* pOwnerNode);
#line 130 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
		protected: void AddGenericParamsToScope(ClassDecl* pClassDecl, SymbolScope* pScope);
#line 142 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
		protected: void AddMemberSymbolToScope(AST* pMemberNode, SymbolScope* pScope);
#line 184 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
		public: void BuildForRoot(AST* pRoot);
#line 194 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
		protected: void BuildForNode(AST* pNode, SymbolScope* pScope);
#line 396 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
		public: void ResolveInScopeChainNoBaseClasses(const char* sName, SymbolScope* pStartScope, Vector<Symbol*>* pOut);
#line 413 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
		public: void ResolveInScopeChain(const char* sName, SymbolScope* pStartScope, Vector<Symbol*>* pOut);
#line 453 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
		public: void ResolveFromNode(AST* pNode, const char* sName, Vector<Symbol*>* pOut);
#line 4 "/home/cliffya/git/Lang/Source/Core/Semantic/Resolver.nll"
		public: virtual ~Resolver();
	};
}

