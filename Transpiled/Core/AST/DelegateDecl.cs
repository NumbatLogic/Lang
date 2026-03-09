#line 1 "../../../Source/Core/AST/DelegateDecl.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/DelegateDecl.nll"
	class DelegateDecl : AST
	{
#line 6 "../../../Source/Core/AST/DelegateDecl.nll"
		public AccessLevel m_pAccessLevel;
#line 7 "../../../Source/Core/AST/DelegateDecl.nll"
		public FunctionDecl m_pFunctionDecl;
#line 9 "../../../Source/Core/AST/DelegateDecl.nll"
		public DelegateDecl()
		{
#line 11 "../../../Source/Core/AST/DelegateDecl.nll"
			m_eType = AST.Type.DELEGATE_DECL;
		}

#line 14 "../../../Source/Core/AST/DelegateDecl.nll"
		public static DelegateDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum, ClassDecl pParentClassDecl)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			AccessLevel pAccessLevel = AccessLevel.TryCreate(pTokenContainer, pTempOffset);
#line 19 "../../../Source/Core/AST/DelegateDecl.nll"
			if (pAccessLevel == null)
			{
#line 20 "../../../Source/Core/AST/DelegateDecl.nll"
				return null;
			}
			Token pToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_DELEGATE);
#line 23 "../../../Source/Core/AST/DelegateDecl.nll"
			if (pToken == null)
			{
#line 24 "../../../Source/Core/AST/DelegateDecl.nll"
				return null;
			}
#line 25 "../../../Source/Core/AST/DelegateDecl.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			DelegateDecl pDelegateDecl = new DelegateDecl();
#line 28 "../../../Source/Core/AST/DelegateDecl.nll"
			pDelegateDecl.m_pFirstToken = pToken;
#line 29 "../../../Source/Core/AST/DelegateDecl.nll"
			pDelegateDecl.m_pAccessLevel = pAccessLevel;
			NumbatLogic.AccessLevel __98812055 = pAccessLevel;
#line 30 "../../../Source/Core/AST/DelegateDecl.nll"
			pAccessLevel = null;
#line 30 "../../../Source/Core/AST/DelegateDecl.nll"
			pDelegateDecl.AddChild(__98812055);
			FunctionDecl pFunctionDecl = FunctionDecl.TryCreate(pTokenContainer, pTempOffset, null);
#line 33 "../../../Source/Core/AST/DelegateDecl.nll"
			if (pFunctionDecl == null)
			{
#line 35 "../../../Source/Core/AST/DelegateDecl.nll"
				Console.Log("expected function decl");
#line 36 "../../../Source/Core/AST/DelegateDecl.nll"
				Assert.Plz(false);
#line 37 "../../../Source/Core/AST/DelegateDecl.nll"
				return null;
			}
#line 40 "../../../Source/Core/AST/DelegateDecl.nll"
			if (pFunctionDecl.m_pScope != null)
			{
#line 42 "../../../Source/Core/AST/DelegateDecl.nll"
				Console.Log("function def can't have scope!");
#line 43 "../../../Source/Core/AST/DelegateDecl.nll"
				Assert.Plz(false);
#line 44 "../../../Source/Core/AST/DelegateDecl.nll"
				return null;
			}
#line 47 "../../../Source/Core/AST/DelegateDecl.nll"
			pDelegateDecl.m_pFunctionDecl = pFunctionDecl;
			NumbatLogic.FunctionDecl __4279829941 = pFunctionDecl;
#line 48 "../../../Source/Core/AST/DelegateDecl.nll"
			pFunctionDecl = null;
#line 48 "../../../Source/Core/AST/DelegateDecl.nll"
			pDelegateDecl.AddChild(__4279829941);
#line 50 "../../../Source/Core/AST/DelegateDecl.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.DelegateDecl __305311194 = pDelegateDecl;
#line 51 "../../../Source/Core/AST/DelegateDecl.nll"
			pDelegateDecl = null;
#line 51 "../../../Source/Core/AST/DelegateDecl.nll"
			return __305311194;
		}

#line 59 "../../../Source/Core/AST/DelegateDecl.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 64 "../../../Source/Core/AST/DelegateDecl.nll"
			if (eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE)
#line 65 "../../../Source/Core/AST/DelegateDecl.nll"
				return;
#line 67 "../../../Source/Core/AST/DelegateDecl.nll"
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 68 "../../../Source/Core/AST/DelegateDecl.nll"
			m_pAccessLevel.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 69 "../../../Source/Core/AST/DelegateDecl.nll"
			if (eLanguage == AST.Language.CPP)
#line 70 "../../../Source/Core/AST/DelegateDecl.nll"
				pOutputBuilder.m_sOut.AppendChar(':');
#line 71 "../../../Source/Core/AST/DelegateDecl.nll"
			pOutputBuilder.m_sOut.AppendChar(' ');
#line 73 "../../../Source/Core/AST/DelegateDecl.nll"
			switch (eLanguage)
			{
				case AST.Language.CPP:
				{
#line 77 "../../../Source/Core/AST/DelegateDecl.nll"
					pOutputBuilder.m_sOut.Append("typedef ");
#line 78 "../../../Source/Core/AST/DelegateDecl.nll"
					break;
				}

				case AST.Language.CS:
				case AST.Language.NLL:
				case AST.Language.NLL_DEF:
				{
#line 84 "../../../Source/Core/AST/DelegateDecl.nll"
					pOutputBuilder.m_sOut.Append("delegate ");
#line 85 "../../../Source/Core/AST/DelegateDecl.nll"
					break;
				}

			}
#line 89 "../../../Source/Core/AST/DelegateDecl.nll"
			m_pFunctionDecl.m_pTypeRef.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 90 "../../../Source/Core/AST/DelegateDecl.nll"
			pOutputBuilder.m_sOut.AppendChar(' ');
#line 92 "../../../Source/Core/AST/DelegateDecl.nll"
			if (eLanguage == AST.Language.CPP)
#line 93 "../../../Source/Core/AST/DelegateDecl.nll"
				pOutputBuilder.m_sOut.AppendChar('(');
#line 94 "../../../Source/Core/AST/DelegateDecl.nll"
			pOutputBuilder.m_sOut.Append(m_pFunctionDecl.m_pNameToken.GetString());
#line 95 "../../../Source/Core/AST/DelegateDecl.nll"
			if (eLanguage == AST.Language.CPP)
#line 96 "../../../Source/Core/AST/DelegateDecl.nll"
				pOutputBuilder.m_sOut.AppendChar(')');
#line 98 "../../../Source/Core/AST/DelegateDecl.nll"
			m_pFunctionDecl.m_pParamDecl.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 100 "../../../Source/Core/AST/DelegateDecl.nll"
			pOutputBuilder.m_sOut.Append(";\n");
		}

	}
}

