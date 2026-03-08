#line 1 "../../../Source/Core/AST/DelegateDecl.nll"
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
			NumbatLogic.AccessLevel __98812055 = pAccessLevel;
			pAccessLevel = null;
			pDelegateDecl.AddChild(__98812055);
			FunctionDecl pFunctionDecl = FunctionDecl.TryCreate(pTokenContainer, pTempOffset, null);
			if (pFunctionDecl == null)
			{
				Console.Log("expected function decl");
				Assert.Plz(false);
				return null;
			}
			if (pFunctionDecl.m_pScope != null)
			{
				Console.Log("function def can't have scope!");
				Assert.Plz(false);
				return null;
			}
			pDelegateDecl.m_pFunctionDecl = pFunctionDecl;
			NumbatLogic.FunctionDecl __4279829941 = pFunctionDecl;
			pFunctionDecl = null;
			pDelegateDecl.AddChild(__4279829941);
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.DelegateDecl __305311194 = pDelegateDecl;
			pDelegateDecl = null;
			return __305311194;
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder out)
		{
			if (eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE)
				return;
			Util.Pad(nDepth, out.m_sOut);
			m_pAccessLevel.Stringify(eLanguage, eOutputFile, 0, out);
			if (eLanguage == AST.Language.CPP)
				out.m_sOut.AppendChar(':');
			out.m_sOut.AppendChar(' ');
			switch (eLanguage)
			{
				case AST.Language.CPP:
				{
					out.m_sOut.Append("typedef ");
					break;
				}

				case AST.Language.CS:
				case AST.Language.NLL:
				case AST.Language.NLL_DEF:
				{
					out.m_sOut.Append("delegate ");
					break;
				}

			}
			m_pFunctionDecl.m_pTypeRef.Stringify(eLanguage, eOutputFile, 0, out);
			out.m_sOut.AppendChar(' ');
			if (eLanguage == AST.Language.CPP)
				out.m_sOut.AppendChar('(');
			out.m_sOut.Append(m_pFunctionDecl.m_pNameToken.GetString());
			if (eLanguage == AST.Language.CPP)
				out.m_sOut.AppendChar(')');
			m_pFunctionDecl.m_pParamDecl.Stringify(eLanguage, eOutputFile, 0, out);
			out.m_sOut.Append(";\n");
		}

	}
}

