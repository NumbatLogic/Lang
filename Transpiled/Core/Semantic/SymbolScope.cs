#line 0 "../../../Source/Core/Semantic/SymbolScope.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/Semantic/SymbolScope.nll"
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

		public Kind m_eKind;
		public SymbolScope m_pParent;
		public AST m_pOwnerAST;
		public OwnedStringMap<OwnedVector<Symbol>> m_pSymbolMap;
		public SymbolScope()
		{
			m_eKind = Kind.BLOCK;
			m_pParent = null;
			m_pOwnerAST = null;
			m_pSymbolMap = new OwnedStringMap<OwnedVector<Symbol>>();
		}

		public void AddSymbol(string sName, Symbol ppSymbol)
		{
			if (ppSymbol == null)
				return;
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
				pOwnedBucket = null;
				m_pSymbolMap.Set(sName, __1215975972);
			}
			ppSymbol.m_pScope = this;
			pBucket.PushBack(ppSymbol);
		}

		public void FindInThisScope(string sName, Vector<Symbol> pOut)
		{
			Assert.Plz(pOut != null);
			pOut.Clear();
			if (m_pSymbolMap.Contains(sName))
			{
				OwnedVector<Symbol> pBucket = m_pSymbolMap.Get(sName);
				for (int i = 0; i < pBucket.GetSize(); i++)
				{
					pOut.PushBack(pBucket.Get(i));
				}
			}
		}

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

		~SymbolScope()
		{
		}

	}
}

