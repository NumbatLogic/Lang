#include "SymbolScope.hpp"
#include "../../../../LangShared/Transpiled/Vector/OwnedVector.hpp"
#include "../../../../LangShared/Transpiled/Map/OwnedStringMap.hpp"
#include "Symbol.hpp"
#include "../../../../LangShared/Source/Assert/CPP/Assert.hpp"
#include "../../../../LangShared/Source/Vector/CPP/Vector.hpp"
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
#line 0 "/home/cliffya/git/Lang/Source/Core/Semantic/SymbolScope.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/Semantic/SymbolScope.nll"
#line 26 "/home/cliffya/git/Lang/Source/Core/Semantic/SymbolScope.nll"
	SymbolScope::SymbolScope()
	{
		m_eKind = Kind::GLOBAL;
		m_pParent = 0;
		m_pOwnerAST = 0;
		m_pSymbolMap = 0;
#line 28 "/home/cliffya/git/Lang/Source/Core/Semantic/SymbolScope.nll"
		m_eKind = Kind::BLOCK;
		m_pParent = 0;
		m_pOwnerAST = 0;
		m_pSymbolMap = new OwnedStringMap<OwnedVector<Symbol*>*>();
	}

#line 35 "/home/cliffya/git/Lang/Source/Core/Semantic/SymbolScope.nll"
	void SymbolScope::AddSymbol(const char* sName, Symbol* ppSymbol)
	{
		if (ppSymbol == 0)
			return;
#line 40 "/home/cliffya/git/Lang/Source/Core/Semantic/SymbolScope.nll"
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
#line 49 "/home/cliffya/git/Lang/Source/Core/Semantic/SymbolScope.nll"
			pOwnedBucket = 0;
#line 49 "/home/cliffya/git/Lang/Source/Core/Semantic/SymbolScope.nll"
			m_pSymbolMap->Set(sName, __1215975972);
			if (pOwnedBucket) delete pOwnedBucket;
		}
		ppSymbol->m_pScope = this;
		pBucket->PushBack(ppSymbol);
	}

#line 57 "/home/cliffya/git/Lang/Source/Core/Semantic/SymbolScope.nll"
	void SymbolScope::FindInThisScope(const char* sName, Vector<Symbol*>* pOut)
	{
		Assert::Plz(pOut != 0);
#line 61 "/home/cliffya/git/Lang/Source/Core/Semantic/SymbolScope.nll"
		pOut->Clear();
#line 63 "/home/cliffya/git/Lang/Source/Core/Semantic/SymbolScope.nll"
		if (m_pSymbolMap->Contains(sName))
		{
			OwnedVector<Symbol*>* pBucket = m_pSymbolMap->Get(sName);
			for (int i = 0; i < pBucket->GetSize(); i++)
			{
				pOut->PushBack(pBucket->Get(i));
			}
		}
	}

#line 76 "/home/cliffya/git/Lang/Source/Core/Semantic/SymbolScope.nll"
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

#line 3 "/home/cliffya/git/Lang/Source/Core/Semantic/SymbolScope.nll"
	SymbolScope::~SymbolScope()
	{
		if (m_pSymbolMap) delete m_pSymbolMap;
	}

}

