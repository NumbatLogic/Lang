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
namespace NumbatLogic
{
	SymbolScope::SymbolScope()
	{
		m_eKind = Kind::GLOBAL;
		m_pParent = 0;
		m_pOwnerAST = 0;
		m_pSymbolMap = 0;
		m_eKind = Kind::BLOCK;
		m_pParent = 0;
		m_pOwnerAST = 0;
		m_pSymbolMap = new OwnedStringMap<OwnedVector<Symbol*>*>();
	}

	void SymbolScope::AddSymbol(const char* sName, Symbol* ppSymbol)
	{
		if (ppSymbol == 0)
			return;
		OwnedVector<Symbol*>* pBucket = 0;
		if (m_pSymbolMap->Contains(sName))
		{
			pBucket = m_pSymbolMap->Get(sName);
		}
		else
		{
			OwnedVector<Symbol*>* pOwnedBucket = new OwnedVector<Symbol*>();
			pBucket = pOwnedBucket;
			NumbatLogic::OwnedVector<NumbatLogic::Symbol*>* __1215975972 = pOwnedBucket;
			pOwnedBucket = 0;
			m_pSymbolMap->Set(sName, __1215975972);
			if (pOwnedBucket) delete pOwnedBucket;
		}
		ppSymbol->m_pScope = this;
		pBucket->PushBack(ppSymbol);
	}

	void SymbolScope::FindInThisScope(const char* sName, Vector<Symbol*>* pOut)
	{
		Assert::Plz(pOut != 0);
		pOut->Clear();
		if (m_pSymbolMap->Contains(sName))
		{
			OwnedVector<Symbol*>* pBucket = m_pSymbolMap->Get(sName);
			for (int i = 0; i < pBucket->GetSize(); i++)
			{
				pOut->PushBack(pBucket->Get(i));
			}
		}
	}

	SymbolScope* SymbolScope::FindNamespaceScope(const char* sName)
	{
		if (!m_pSymbolMap->Contains(sName))
			return 0;
		OwnedVector<Symbol*>* pBucket = m_pSymbolMap->Get(sName);
		for (int i = 0; i < pBucket->GetSize(); i++)
		{
			Symbol* pSym = pBucket->Get(i);
			if (pSym->m_eKind == Symbol::Kind::NAMESPACE && pSym->m_pScope != 0)
				return pSym->m_pScope;
		}
		return 0;
	}

	SymbolScope::~SymbolScope()
	{
		if (m_pSymbolMap) delete m_pSymbolMap;
	}

}

