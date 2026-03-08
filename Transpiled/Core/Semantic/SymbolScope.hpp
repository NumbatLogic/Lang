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

		public: Kind m_eKind;
		public: SymbolScope* m_pParent;
		public: AST* m_pOwnerAST;
		public: OwnedStringMap<OwnedVector<Symbol*>*>* m_pSymbolMap;
		public: SymbolScope();
		public: void AddSymbol(const char* sName, Symbol* ppSymbol);
		public: void FindInThisScope(const char* sName, Vector<Symbol*>* pOut);
		public: SymbolScope* FindNamespaceScope(const char* sName);
		public: virtual ~SymbolScope();
	};
}

