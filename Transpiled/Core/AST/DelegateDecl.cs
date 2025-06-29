namespace NumbatLogic
{
	class DelegateDecl : AST
	{
		public AccessLevel m_pAccessLevel;
		public FunctionDecl m_pFunctionDecl;
		public DelegateDecl()
		{
			m_eType = AST.Type.DELEGATE_DECL;
		}

		public static DelegateDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum, ClassDecl pParentClassDecl)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			AccessLevel pAccessLevel = AccessLevel.TryCreate(pTokenContainer, pTempOffset);
			if (pAccessLevel == null)
			{
				return null;
			}
			Token pToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_DELEGATE);
			if (pToken == null)
			{
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			DelegateDecl pDelegateDecl = new DelegateDecl();
			pDelegateDecl.m_pFirstToken = pToken;
			pDelegateDecl.m_pAccessLevel = pAccessLevel;
			NumbatLogic.AccessLevel __1197960421 = pAccessLevel;
			pAccessLevel = null;
			pDelegateDecl.AddChild(__1197960421);
			FunctionDecl pFunctionDecl = FunctionDecl.TryCreate(pTokenContainer, pTempOffset, null);
			if (pFunctionDecl == null)
			{
				Console.Log("expected function decl");
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			if (pFunctionDecl.m_pScope != null)
			{
				Console.Log("function def can't have scope!");
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			pDelegateDecl.m_pFunctionDecl = pFunctionDecl;
			NumbatLogic.FunctionDecl __1338261948 = pFunctionDecl;
			pFunctionDecl = null;
			pDelegateDecl.AddChild(__1338261948);
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.DelegateDecl __2803299726 = pDelegateDecl;
			pDelegateDecl = null;
			return __2803299726;
		}

		public override AST FindByName(string sxName, AST pCallingChild)
		{
			if (ExternalString.Equal(sxName, m_pFunctionDecl.m_pNameToken.GetString()))
				return this;
			return base.FindByName(sxName, pCallingChild);
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			if (eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE)
				return;
			Util.Pad(nDepth, sOut);
			m_pAccessLevel.Stringify(eLanguage, eOutputFile, 0, sOut);
			if (eLanguage == AST.Language.CPP)
				sOut.AppendChar(':');
			sOut.AppendChar(' ');
			switch (eLanguage)
			{
				case AST.Language.CPP:
				{
					sOut.Append("typedef ");
					break;
				}

				case AST.Language.CS:
				case AST.Language.NLL:
				case AST.Language.NLL_DEF:
				{
					sOut.Append("delegate ");
					break;
				}

			}
			m_pFunctionDecl.m_pTypeRef.Stringify(eLanguage, eOutputFile, 0, sOut);
			sOut.AppendChar(' ');
			if (eLanguage == AST.Language.CPP)
				sOut.AppendChar('(');
			sOut.Append(m_pFunctionDecl.m_pNameToken.GetString());
			if (eLanguage == AST.Language.CPP)
				sOut.AppendChar(')');
			m_pFunctionDecl.m_pParamDecl.Stringify(eLanguage, eOutputFile, 0, sOut);
			sOut.Append(";\n");
		}

	}
}

