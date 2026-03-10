#line 1 "../../../Source/Core/Semantic/SymbolScope.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/Semantic/SymbolScope.nll"
	class SymbolScope
	{
#line 5 "../../../Source/Core/Semantic/SymbolScope.nll"
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
#line 28 "../../../Source/Core/Semantic/SymbolScope.nll"
			m_eKind = Kind.BLOCK;
#line 29 "../../../Source/Core/Semantic/SymbolScope.nll"
			m_pParent = null;
#line 30 "../../../Source/Core/Semantic/SymbolScope.nll"
			m_pOwnerAST = null;
#line 31 "../../../Source/Core/Semantic/SymbolScope.nll"
			m_pSymbolMap = new OwnedStringMap<OwnedVector<Symbol>>();
		}

#line 35 "../../../Source/Core/Semantic/SymbolScope.nll"
		public void AddSymbol(string sName, Symbol ppSymbol)
		{
#line 37 "../../../Source/Core/Semantic/SymbolScope.nll"
			if (ppSymbol == null)
#line 38 "../../../Source/Core/Semantic/SymbolScope.nll"
				return;
#line 40 "../../../Source/Core/Semantic/SymbolScope.nll"
			OwnedVector<Symbol> pBucket;
#line 41 "../../../Source/Core/Semantic/SymbolScope.nll"
			if (m_pSymbolMap.Contains(sName))
			{
#line 43 "../../../Source/Core/Semantic/SymbolScope.nll"
				pBucket = m_pSymbolMap.Get(sName);
			}
			else
			{
#line 47 "../../../Source/Core/Semantic/SymbolScope.nll"
				OwnedVector<Symbol> pOwnedBucket = new OwnedVector<Symbol>();
#line 48 "../../../Source/Core/Semantic/SymbolScope.nll"
				pBucket = pOwnedBucket;
				NumbatLogic.OwnedVector<NumbatLogic.Symbol> __1215975972 = pOwnedBucket;
#line 49 "../../../Source/Core/Semantic/SymbolScope.nll"
				pOwnedBucket = null;
#line 49 "../../../Source/Core/Semantic/SymbolScope.nll"
				m_pSymbolMap.Set(sName, __1215975972);
			}
#line 52 "../../../Source/Core/Semantic/SymbolScope.nll"
			ppSymbol.m_pScope = this;
#line 53 "../../../Source/Core/Semantic/SymbolScope.nll"
			pBucket.PushBack(ppSymbol);
		}

#line 57 "../../../Source/Core/Semantic/SymbolScope.nll"
		public void FindInThisScope(string sName, Vector<Symbol> pOut)
		{
#line 59 "../../../Source/Core/Semantic/SymbolScope.nll"
			Assert.Plz(pOut != null);
#line 61 "../../../Source/Core/Semantic/SymbolScope.nll"
			pOut.Clear();
#line 63 "../../../Source/Core/Semantic/SymbolScope.nll"
			if (m_pSymbolMap.Contains(sName))
			{
#line 65 "../../../Source/Core/Semantic/SymbolScope.nll"
				OwnedVector<Symbol> pBucket = m_pSymbolMap.Get(sName);
#line 66 "../../../Source/Core/Semantic/SymbolScope.nll"
				for (int i = 0; i < pBucket.GetSize(); i++)
				{
#line 68 "../../../Source/Core/Semantic/SymbolScope.nll"
					pOut.PushBack(pBucket.Get(i));
				}
			}
		}

#line 76 "../../../Source/Core/Semantic/SymbolScope.nll"
		public SymbolScope FindNamespaceScope(string sName)
		{
#line 78 "../../../Source/Core/Semantic/SymbolScope.nll"
			if (!m_pSymbolMap.Contains(sName))
#line 79 "../../../Source/Core/Semantic/SymbolScope.nll"
				return null;
#line 80 "../../../Source/Core/Semantic/SymbolScope.nll"
			OwnedVector<Symbol> pBucket = m_pSymbolMap.Get(sName);
#line 81 "../../../Source/Core/Semantic/SymbolScope.nll"
			for (int i = 0; i < pBucket.GetSize(); i++)
			{
#line 83 "../../../Source/Core/Semantic/SymbolScope.nll"
				Symbol pSym = pBucket.Get(i);
#line 84 "../../../Source/Core/Semantic/SymbolScope.nll"
				if (pSym.m_eKind == Symbol.Kind.NAMESPACE && pSym.m_pScope != null)
#line 85 "../../../Source/Core/Semantic/SymbolScope.nll"
					return pSym.m_pScope;
			}
#line 87 "../../../Source/Core/Semantic/SymbolScope.nll"
			return null;
		}

#line 3 "../../../Source/Core/Semantic/SymbolScope.nll"
		~SymbolScope()
		{
		}

	}
}

