#line 1 "../../../Source/Core/Semantic/SymbolScope.nll"
namespace NumbatLogic
{
	class SymbolScope
	{
		public enum Kind
		{
			GLOBAL,
			NAMESPACE,
			CLASS,
			ENUM,
			FUNCTION,
			BLOCK,
		}

#line 14 "../../../Source/Core/Semantic/SymbolScope.nll"
		public Kind m_eKind;
#line 17 "../../../Source/Core/Semantic/SymbolScope.nll"
		public SymbolScope m_pParent;
#line 20 "../../../Source/Core/Semantic/SymbolScope.nll"
		public AST m_pOwnerAST;
#line 24 "../../../Source/Core/Semantic/SymbolScope.nll"
		public OwnedStringMap<OwnedVector<Symbol>> m_pSymbolMap;
#line 26 "../../../Source/Core/Semantic/SymbolScope.nll"
		public SymbolScope()
		{
			m_eKind = Kind.BLOCK;
			m_pParent = null;
			m_pOwnerAST = null;
			m_pSymbolMap = new OwnedStringMap<OwnedVector<Symbol>>();
		}

#line 35 "../../../Source/Core/Semantic/SymbolScope.nll"
		public void AddSymbol(string sName, Symbol ppSymbol)
		{
			if (ppSymbol == null)
				return;
#line 40 "../../../Source/Core/Semantic/SymbolScope.nll"
			OwnedVector<Symbol> pBucket;
			if (m_pSymbolMap.Contains(sName))
			{
				pBucket = m_pSymbolMap.Get(sName);
			}
			else
			{
				OwnedVector<Symbol> pOwnedBucket = new OwnedVector<Symbol>();
				pBucket = pOwnedBucket;
				NumbatLogic.OwnedVector<NumbatLogic.Symbol> __1215975972 = pOwnedBucket;
#line 49 "../../../Source/Core/Semantic/SymbolScope.nll"
				pOwnedBucket = null;
#line 49 "../../../Source/Core/Semantic/SymbolScope.nll"
				m_pSymbolMap.Set(sName, __1215975972);
			}
#line 52 "../../../Source/Core/Semantic/SymbolScope.nll"
			ppSymbol.m_pScope = this;
			pBucket.PushBack(ppSymbol);
		}

#line 57 "../../../Source/Core/Semantic/SymbolScope.nll"
		public void FindInThisScope(string sName, Vector<Symbol> pOut)
		{
			Assert.Plz(pOut != null);
#line 61 "../../../Source/Core/Semantic/SymbolScope.nll"
			pOut.Clear();
#line 63 "../../../Source/Core/Semantic/SymbolScope.nll"
			if (m_pSymbolMap.Contains(sName))
			{
				OwnedVector<Symbol> pBucket = m_pSymbolMap.Get(sName);
				for (int i = 0; i < pBucket.GetSize(); i++)
				{
					pOut.PushBack(pBucket.Get(i));
				}
			}
		}

#line 76 "../../../Source/Core/Semantic/SymbolScope.nll"
		public SymbolScope FindNamespaceScope(string sName)
		{
			if (!m_pSymbolMap.Contains(sName))
				return null;
			OwnedVector<Symbol> pBucket = m_pSymbolMap.Get(sName);
			for (int i = 0; i < pBucket.GetSize(); i++)
			{
				Symbol pSym = pBucket.Get(i);
				if (pSym.m_eKind == Symbol.Kind.NAMESPACE && pSym.m_pScope != null)
					return pSym.m_pScope;
			}
			return null;
		}

#line 3 "../../../Source/Core/Semantic/SymbolScope.nll"
		~SymbolScope()
		{
		}

	}
}

