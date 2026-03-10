#include "SymbolScope.hpp"
#include "../../../../LangShared/Transpiled/Vector/OwnedVector.hpp"
#include "../../../../LangShared/Transpiled/Map/OwnedStringMap.hpp"
#include "Symbol.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
#include "../AST/AST.hpp"

namespace NumbatLogic
{
	class SymbolScope;
	class Symbol;
	template <class T>
	class OwnedVector;
	template <class TValue>
	class OwnedStringMap;
	class Assert;
	template <class T>
	class Vector;
	class AST;
}
#line 0 "../../../Source/Core/Semantic/SymbolScope.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/Semantic/SymbolScope.nll"
#line 26 "../../../Source/Core/Semantic/SymbolScope.nll"
	SymbolScope::SymbolScope()
	{
		m_eKind = Kind::GLOBAL;
		m_pParent = 0;
		m_pOwnerAST = 0;
		m_pSymbolMap = 0;
#line 28 "../../../Source/Core/Semantic/SymbolScope.nll"
		m_eKind = Kind::BLOCK;
#line 29 "../../../Source/Core/Semantic/SymbolScope.nll"
		m_pParent = 0;
#line 30 "../../../Source/Core/Semantic/SymbolScope.nll"
		m_pOwnerAST = 0;
#line 31 "../../../Source/Core/Semantic/SymbolScope.nll"
		m_pSymbolMap = new OwnedStringMap<OwnedVector<Symbol*>*>();
	}

#line 35 "../../../Source/Core/Semantic/SymbolScope.nll"
	void SymbolScope::AddSymbol(const char* sName, Symbol* ppSymbol)
	{
#line 37 "../../../Source/Core/Semantic/SymbolScope.nll"
		if (ppSymbol == 0)
#line 38 "../../../Source/Core/Semantic/SymbolScope.nll"
			return;
#line 40 "../../../Source/Core/Semantic/SymbolScope.nll"
		OwnedVector<Symbol*>* pBucket = 0;
#line 41 "../../../Source/Core/Semantic/SymbolScope.nll"
		if (m_pSymbolMap->Contains(sName))
		{
#line 43 "../../../Source/Core/Semantic/SymbolScope.nll"
			pBucket = m_pSymbolMap->Get(sName);
		}
		else
		{
#line 47 "../../../Source/Core/Semantic/SymbolScope.nll"
			OwnedVector<Symbol*>* pOwnedBucket = new OwnedVector<Symbol*>();
#line 48 "../../../Source/Core/Semantic/SymbolScope.nll"
			pBucket = pOwnedBucket;
			NumbatLogic::OwnedVector<NumbatLogic::Symbol*>* __1215975972 = pOwnedBucket;
#line 49 "../../../Source/Core/Semantic/SymbolScope.nll"
			pOwnedBucket = 0;
#line 49 "../../../Source/Core/Semantic/SymbolScope.nll"
			m_pSymbolMap->Set(sName, __1215975972);
			if (pOwnedBucket) delete pOwnedBucket;
		}
#line 52 "../../../Source/Core/Semantic/SymbolScope.nll"
		ppSymbol->m_pScope = this;
#line 53 "../../../Source/Core/Semantic/SymbolScope.nll"
		pBucket->PushBack(ppSymbol);
	}

#line 57 "../../../Source/Core/Semantic/SymbolScope.nll"
	void SymbolScope::FindInThisScope(const char* sName, Vector<Symbol*>* pOut)
	{
#line 59 "../../../Source/Core/Semantic/SymbolScope.nll"
		Assert::Plz(pOut != 0);
#line 61 "../../../Source/Core/Semantic/SymbolScope.nll"
		pOut->Clear();
#line 63 "../../../Source/Core/Semantic/SymbolScope.nll"
		if (m_pSymbolMap->Contains(sName))
		{
#line 65 "../../../Source/Core/Semantic/SymbolScope.nll"
			OwnedVector<Symbol*>* pBucket = m_pSymbolMap->Get(sName);
#line 66 "../../../Source/Core/Semantic/SymbolScope.nll"
			for (int i = 0; i < pBucket->GetSize(); i++)
			{
#line 68 "../../../Source/Core/Semantic/SymbolScope.nll"
				pOut->PushBack(pBucket->Get(i));
			}
		}
	}

#line 76 "../../../Source/Core/Semantic/SymbolScope.nll"
	SymbolScope* SymbolScope::FindNamespaceScope(const char* sName)
	{
#line 78 "../../../Source/Core/Semantic/SymbolScope.nll"
		if (!m_pSymbolMap->Contains(sName))
#line 79 "../../../Source/Core/Semantic/SymbolScope.nll"
			return 0;
#line 80 "../../../Source/Core/Semantic/SymbolScope.nll"
		OwnedVector<Symbol*>* pBucket = m_pSymbolMap->Get(sName);
#line 81 "../../../Source/Core/Semantic/SymbolScope.nll"
		for (int i = 0; i < pBucket->GetSize(); i++)
		{
#line 83 "../../../Source/Core/Semantic/SymbolScope.nll"
			Symbol* pSym = pBucket->Get(i);
#line 84 "../../../Source/Core/Semantic/SymbolScope.nll"
			if (pSym->m_eKind == Symbol::Kind::NAMESPACE && pSym->m_pScope != 0)
#line 85 "../../../Source/Core/Semantic/SymbolScope.nll"
				return pSym->m_pScope;
		}
#line 87 "../../../Source/Core/Semantic/SymbolScope.nll"
		return 0;
	}

#line 3 "../../../Source/Core/Semantic/SymbolScope.nll"
	SymbolScope::~SymbolScope()
	{
		if (m_pSymbolMap) delete m_pSymbolMap;
	}

}

