#pragma once

#include "../../../../LangShared/Transpiled/Map/OwnedStringMap.hpp"
#include "../../../../LangShared/Transpiled/Vector/OwnedVector.hpp"
#include "../../../../LangShared/Source/Vector/CPP/Vector.hpp"

namespace NumbatLogic
{
	class SymbolScope;
	class AST;
	template <class TValue>
	class OwnedStringMap;
	template <class T>
	class OwnedVector;
	class Symbol;
	template <class T>
	class Vector;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/Semantic/SymbolScope.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/Semantic/SymbolScope.nll"
	class SymbolScope
	{
		public: enum Kind
		{
			GLOBAL,
			NAMESPACE,
			CLASS,
			ENUM,
			FUNCTION,
			BLOCK,
		};

#line 14 "/home/cliffya/git/Lang/Source/Core/Semantic/SymbolScope.nll"
		public: Kind m_eKind;
#line 17 "/home/cliffya/git/Lang/Source/Core/Semantic/SymbolScope.nll"
		public: SymbolScope* m_pParent;
#line 20 "/home/cliffya/git/Lang/Source/Core/Semantic/SymbolScope.nll"
		public: AST* m_pOwnerAST;
#line 24 "/home/cliffya/git/Lang/Source/Core/Semantic/SymbolScope.nll"
		public: OwnedStringMap<OwnedVector<Symbol*>*>* m_pSymbolMap;
#line 26 "/home/cliffya/git/Lang/Source/Core/Semantic/SymbolScope.nll"
		public: SymbolScope();
#line 35 "/home/cliffya/git/Lang/Source/Core/Semantic/SymbolScope.nll"
		public: void AddSymbol(const char* sName, Symbol* ppSymbol);
#line 57 "/home/cliffya/git/Lang/Source/Core/Semantic/SymbolScope.nll"
		public: void FindInThisScope(const char* sName, Vector<Symbol*>* pOut);
#line 76 "/home/cliffya/git/Lang/Source/Core/Semantic/SymbolScope.nll"
		public: SymbolScope* FindNamespaceScope(const char* sName);
#line 3 "/home/cliffya/git/Lang/Source/Core/Semantic/SymbolScope.nll"
		public: virtual ~SymbolScope();
	};
}

