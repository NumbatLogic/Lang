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
#line 1 "../../../Source/Core/Semantic/SymbolScope.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/Semantic/SymbolScope.nll"
#line 27 "../../../Source/Core/Semantic/SymbolScope.nll"
	SymbolScope::SymbolScope()
	{
		m_eKind = Kind::GLOBAL;
		m_pParent = 0;
		m_pOwnerAST = 0;
		m_pSymbolMap = 0;
#line 29 "../../../Source/Core/Semantic/SymbolScope.nll"
		m_eKind = Kind::BLOCK;
#line 30 "../../../Source/Core/Semantic/SymbolScope.nll"
		m_pParent = 0;
#line 31 "../../../Source/Core/Semantic/SymbolScope.nll"
		m_pOwnerAST = 0;
#line 32 "../../../Source/Core/Semantic/SymbolScope.nll"
		m_pSymbolMap = new OwnedStringMap<OwnedVector<Symbol*>*>();
	}

#line 36 "../../../Source/Core/Semantic/SymbolScope.nll"
	void SymbolScope::AddSymbol(const char* sName, Symbol* ppSymbol)
	{
#line 38 "../../../Source/Core/Semantic/SymbolScope.nll"
		if (ppSymbol == 0)
#line 39 "../../../Source/Core/Semantic/SymbolScope.nll"
			return;
		OwnedVector<Symbol*>* pBucket = 0;
#line 42 "../../../Source/Core/Semantic/SymbolScope.nll"
		if (m_pSymbolMap->Contains(sName))
		{
#line 44 "../../../Source/Core/Semantic/SymbolScope.nll"
			pBucket = m_pSymbolMap->Get(sName);
		}
		else
		{
			OwnedVector<Symbol*>* pOwnedBucket = new OwnedVector<Symbol*>();
#line 49 "../../../Source/Core/Semantic/SymbolScope.nll"
			pBucket = pOwnedBucket;
			NumbatLogic::OwnedVector<NumbatLogic::Symbol*>* __1215975972 = pOwnedBucket;
#line 50 "../../../Source/Core/Semantic/SymbolScope.nll"
			pOwnedBucket = 0;
#line 50 "../../../Source/Core/Semantic/SymbolScope.nll"
			m_pSymbolMap->Set(sName, __1215975972);
			if (pOwnedBucket) delete pOwnedBucket;
		}
#line 53 "../../../Source/Core/Semantic/SymbolScope.nll"
		ppSymbol->m_pScope = this;
#line 54 "../../../Source/Core/Semantic/SymbolScope.nll"
		pBucket->PushBack(ppSymbol);
	}

#line 58 "../../../Source/Core/Semantic/SymbolScope.nll"
	void SymbolScope::FindInThisScope(const char* sName, Vector<Symbol*>* pOut)
	{
#line 60 "../../../Source/Core/Semantic/SymbolScope.nll"
		Assert::Plz(pOut != 0);
#line 62 "../../../Source/Core/Semantic/SymbolScope.nll"
		pOut->Clear();
#line 64 "../../../Source/Core/Semantic/SymbolScope.nll"
		if (m_pSymbolMap->Contains(sName))
		{
			OwnedVector<Symbol*>* pBucket = m_pSymbolMap->Get(sName);
#line 67 "../../../Source/Core/Semantic/SymbolScope.nll"
			for (int i = 0; i < pBucket->GetSize(); i++)
			{
#line 69 "../../../Source/Core/Semantic/SymbolScope.nll"
				pOut->PushBack(pBucket->Get(i));
			}
		}
	}

#line 77 "../../../Source/Core/Semantic/SymbolScope.nll"
	SymbolScope* SymbolScope::FindNamespaceScope(const char* sName)
	{
#line 79 "../../../Source/Core/Semantic/SymbolScope.nll"
		if (!m_pSymbolMap->Contains(sName))
#line 80 "../../../Source/Core/Semantic/SymbolScope.nll"
			return 0;
		OwnedVector<Symbol*>* pBucket = m_pSymbolMap->Get(sName);
#line 82 "../../../Source/Core/Semantic/SymbolScope.nll"
		for (int i = 0; i < pBucket->GetSize(); i++)
		{
			Symbol* pSym = pBucket->Get(i);
#line 85 "../../../Source/Core/Semantic/SymbolScope.nll"
			if (pSym->m_eKind == Symbol::Kind::NAMESPACE && pSym->m_pScope != 0)
#line 86 "../../../Source/Core/Semantic/SymbolScope.nll"
				return pSym->m_pScope;
		}
#line 88 "../../../Source/Core/Semantic/SymbolScope.nll"
		return 0;
	}

#line 4 "../../../Source/Core/Semantic/SymbolScope.nll"
	SymbolScope::~SymbolScope()
	{
		if (m_pSymbolMap) delete m_pSymbolMap;
	}

}

