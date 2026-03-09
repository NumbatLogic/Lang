#pragma once

#include "../../../../LangShared/Transpiled/Map/OwnedStringMap.hpp"
#include "../../../../LangShared/Transpiled/Vector/OwnedVector.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"

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
#line 1 "../../../Source/Core/Semantic/SymbolScope.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/Semantic/SymbolScope.nll"
	class SymbolScope
	{
#line 6 "../../../Source/Core/Semantic/SymbolScope.nll"
		public: enum Kind
		{
			GLOBAL,
			NAMESPACE,
			CLASS,
			ENUM,
			FUNCTION,
			BLOCK,
		};

#line 15 "../../../Source/Core/Semantic/SymbolScope.nll"
		public: Kind m_eKind;
#line 18 "../../../Source/Core/Semantic/SymbolScope.nll"
		public: SymbolScope* m_pParent;
#line 21 "../../../Source/Core/Semantic/SymbolScope.nll"
		public: AST* m_pOwnerAST;
#line 25 "../../../Source/Core/Semantic/SymbolScope.nll"
		public: OwnedStringMap<OwnedVector<Symbol*>*>* m_pSymbolMap;
#line 27 "../../../Source/Core/Semantic/SymbolScope.nll"
		public: SymbolScope();
#line 36 "../../../Source/Core/Semantic/SymbolScope.nll"
		public: void AddSymbol(const char* sName, Symbol* ppSymbol);
#line 58 "../../../Source/Core/Semantic/SymbolScope.nll"
		public: void FindInThisScope(const char* sName, Vector<Symbol*>* pOut);
#line 77 "../../../Source/Core/Semantic/SymbolScope.nll"
		public: SymbolScope* FindNamespaceScope(const char* sName);
#line 4 "../../../Source/Core/Semantic/SymbolScope.nll"
		public: virtual ~SymbolScope();
	};
}

