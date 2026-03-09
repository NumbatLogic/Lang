#line 1 "../../../Source/Core/Semantic/SymbolScope.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/Semantic/SymbolScope.nll"
	class SymbolScope
	{
#line 6 "../../../Source/Core/Semantic/SymbolScope.nll"
		public enum Kind
		{
			GLOBAL,
			NAMESPACE,
			CLASS,
			ENUM,
			FUNCTION,
			BLOCK,
		}

#line 15 "../../../Source/Core/Semantic/SymbolScope.nll"
		public Kind m_eKind;
#line 18 "../../../Source/Core/Semantic/SymbolScope.nll"
		public SymbolScope m_pParent;
#line 21 "../../../Source/Core/Semantic/SymbolScope.nll"
		public AST m_pOwnerAST;
#line 25 "../../../Source/Core/Semantic/SymbolScope.nll"
		public OwnedStringMap<OwnedVector<Symbol>> m_pSymbolMap;
#line 27 "../../../Source/Core/Semantic/SymbolScope.nll"
		public SymbolScope()
		{
#line 29 "../../../Source/Core/Semantic/SymbolScope.nll"
			m_eKind = Kind.BLOCK;
#line 30 "../../../Source/Core/Semantic/SymbolScope.nll"
			m_pParent = null;
#line 31 "../../../Source/Core/Semantic/SymbolScope.nll"
			m_pOwnerAST = null;
#line 32 "../../../Source/Core/Semantic/SymbolScope.nll"
			m_pSymbolMap = new OwnedStringMap<OwnedVector<Symbol>>();
		}

#line 36 "../../../Source/Core/Semantic/SymbolScope.nll"
		public void AddSymbol(string sName, Symbol ppSymbol)
		{
#line 38 "../../../Source/Core/Semantic/SymbolScope.nll"
			if (ppSymbol == null)
#line 39 "../../../Source/Core/Semantic/SymbolScope.nll"
				return;
			OwnedVector<Symbol> pBucket;
#line 42 "../../../Source/Core/Semantic/SymbolScope.nll"
			if (m_pSymbolMap.Contains(sName))
			{
#line 44 "../../../Source/Core/Semantic/SymbolScope.nll"
				pBucket = m_pSymbolMap.Get(sName);
			}
			else
			{
				OwnedVector<Symbol> pOwnedBucket = new OwnedVector<Symbol>();
#line 49 "../../../Source/Core/Semantic/SymbolScope.nll"
				pBucket = pOwnedBucket;
				NumbatLogic.OwnedVector<NumbatLogic.Symbol> __1215975972 = pOwnedBucket;
#line 50 "../../../Source/Core/Semantic/SymbolScope.nll"
				pOwnedBucket = null;
#line 50 "../../../Source/Core/Semantic/SymbolScope.nll"
				m_pSymbolMap.Set(sName, __1215975972);
			}
#line 53 "../../../Source/Core/Semantic/SymbolScope.nll"
			ppSymbol.m_pScope = this;
#line 54 "../../../Source/Core/Semantic/SymbolScope.nll"
			pBucket.PushBack(ppSymbol);
		}

#line 58 "../../../Source/Core/Semantic/SymbolScope.nll"
		public void FindInThisScope(string sName, Vector<Symbol> pOut)
		{
#line 60 "../../../Source/Core/Semantic/SymbolScope.nll"
			Assert.Plz(pOut != null);
#line 62 "../../../Source/Core/Semantic/SymbolScope.nll"
			pOut.Clear();
#line 64 "../../../Source/Core/Semantic/SymbolScope.nll"
			if (m_pSymbolMap.Contains(sName))
			{
				OwnedVector<Symbol> pBucket = m_pSymbolMap.Get(sName);
#line 67 "../../../Source/Core/Semantic/SymbolScope.nll"
				for (int i = 0; i < pBucket.GetSize(); i++)
				{
#line 69 "../../../Source/Core/Semantic/SymbolScope.nll"
					pOut.PushBack(pBucket.Get(i));
				}
			}
		}

#line 77 "../../../Source/Core/Semantic/SymbolScope.nll"
		public SymbolScope FindNamespaceScope(string sName)
		{
#line 79 "../../../Source/Core/Semantic/SymbolScope.nll"
			if (!m_pSymbolMap.Contains(sName))
#line 80 "../../../Source/Core/Semantic/SymbolScope.nll"
				return null;
			OwnedVector<Symbol> pBucket = m_pSymbolMap.Get(sName);
#line 82 "../../../Source/Core/Semantic/SymbolScope.nll"
			for (int i = 0; i < pBucket.GetSize(); i++)
			{
				Symbol pSym = pBucket.Get(i);
#line 85 "../../../Source/Core/Semantic/SymbolScope.nll"
				if (pSym.m_eKind == Symbol.Kind.NAMESPACE && pSym.m_pScope != null)
#line 86 "../../../Source/Core/Semantic/SymbolScope.nll"
					return pSym.m_pScope;
			}
#line 88 "../../../Source/Core/Semantic/SymbolScope.nll"
			return null;
		}

#line 4 "../../../Source/Core/Semantic/SymbolScope.nll"
		~SymbolScope()
		{
		}

	}
}

