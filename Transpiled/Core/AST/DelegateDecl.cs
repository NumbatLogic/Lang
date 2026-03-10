#line 1 "../../../Source/Core/AST/DelegateDecl.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/DelegateDecl.nll"
	class DelegateDecl : AST
	{
#line 5 "../../../Source/Core/AST/DelegateDecl.nll"
		public AccessLevel m_pAccessLevel;
#line 6 "../../../Source/Core/AST/DelegateDecl.nll"
		public FunctionDecl m_pFunctionDecl;
#line 8 "../../../Source/Core/AST/DelegateDecl.nll"
		public DelegateDecl()
		{
#line 10 "../../../Source/Core/AST/DelegateDecl.nll"
			m_eType = AST.Type.DELEGATE_DECL;
		}

#line 13 "../../../Source/Core/AST/DelegateDecl.nll"
		public static DelegateDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum, ClassDecl pParentClassDecl)
		{
#line 15 "../../../Source/Core/AST/DelegateDecl.nll"
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 17 "../../../Source/Core/AST/DelegateDecl.nll"
			AccessLevel pAccessLevel = AccessLevel.TryCreate(pTokenContainer, pTempOffset);
#line 18 "../../../Source/Core/AST/DelegateDecl.nll"
			if (pAccessLevel == null)
			{
#line 19 "../../../Source/Core/AST/DelegateDecl.nll"
				return null;
			}
#line 21 "../../../Source/Core/AST/DelegateDecl.nll"
			Token pToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_DELEGATE);
#line 22 "../../../Source/Core/AST/DelegateDecl.nll"
			if (pToken == null)
			{
#line 23 "../../../Source/Core/AST/DelegateDecl.nll"
				return null;
			}
#line 24 "../../../Source/Core/AST/DelegateDecl.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 26 "../../../Source/Core/AST/DelegateDecl.nll"
			DelegateDecl pDelegateDecl = new DelegateDecl();
#line 27 "../../../Source/Core/AST/DelegateDecl.nll"
			pDelegateDecl.m_pFirstToken = pToken;
#line 28 "../../../Source/Core/AST/DelegateDecl.nll"
			pDelegateDecl.m_pAccessLevel = pAccessLevel;
			NumbatLogic.AccessLevel __98812055 = pAccessLevel;
#line 29 "../../../Source/Core/AST/DelegateDecl.nll"
			pAccessLevel = null;
#line 29 "../../../Source/Core/AST/DelegateDecl.nll"
			pDelegateDecl.AddChild(__98812055);
#line 31 "../../../Source/Core/AST/DelegateDecl.nll"
			FunctionDecl pFunctionDecl = FunctionDecl.TryCreate(pTokenContainer, pTempOffset, null);
#line 32 "../../../Source/Core/AST/DelegateDecl.nll"
			if (pFunctionDecl == null)
			{
#line 34 "../../../Source/Core/AST/DelegateDecl.nll"
				Console.Log("expected function decl");
#line 35 "../../../Source/Core/AST/DelegateDecl.nll"
				Assert.Plz(false);
#line 36 "../../../Source/Core/AST/DelegateDecl.nll"
				return null;
			}
#line 39 "../../../Source/Core/AST/DelegateDecl.nll"
			if (pFunctionDecl.m_pScope != null)
			{
#line 41 "../../../Source/Core/AST/DelegateDecl.nll"
				Console.Log("function def can't have scope!");
#line 42 "../../../Source/Core/AST/DelegateDecl.nll"
				Assert.Plz(false);
#line 43 "../../../Source/Core/AST/DelegateDecl.nll"
				return null;
			}
#line 46 "../../../Source/Core/AST/DelegateDecl.nll"
			pDelegateDecl.m_pFunctionDecl = pFunctionDecl;
			NumbatLogic.FunctionDecl __4279829941 = pFunctionDecl;
#line 47 "../../../Source/Core/AST/DelegateDecl.nll"
			pFunctionDecl = null;
#line 47 "../../../Source/Core/AST/DelegateDecl.nll"
			pDelegateDecl.AddChild(__4279829941);
#line 49 "../../../Source/Core/AST/DelegateDecl.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.DelegateDecl __305311194 = pDelegateDecl;
#line 50 "../../../Source/Core/AST/DelegateDecl.nll"
			pDelegateDecl = null;
#line 50 "../../../Source/Core/AST/DelegateDecl.nll"
			return __305311194;
		}

#line 58 "../../../Source/Core/AST/DelegateDecl.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 63 "../../../Source/Core/AST/DelegateDecl.nll"
			if (eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE)
#line 64 "../../../Source/Core/AST/DelegateDecl.nll"
				return;
#line 66 "../../../Source/Core/AST/DelegateDecl.nll"
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 67 "../../../Source/Core/AST/DelegateDecl.nll"
			m_pAccessLevel.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 68 "../../../Source/Core/AST/DelegateDecl.nll"
			if (eLanguage == AST.Language.CPP)
#line 69 "../../../Source/Core/AST/DelegateDecl.nll"
				pOutputBuilder.m_sOut.AppendChar(':');
#line 70 "../../../Source/Core/AST/DelegateDecl.nll"
			pOutputBuilder.m_sOut.AppendChar(' ');
#line 72 "../../../Source/Core/AST/DelegateDecl.nll"
			switch (eLanguage)
			{
				case AST.Language.CPP:
				{
#line 76 "../../../Source/Core/AST/DelegateDecl.nll"
					pOutputBuilder.m_sOut.Append("typedef ");
#line 77 "../../../Source/Core/AST/DelegateDecl.nll"
					break;
				}

				case AST.Language.CS:
				case AST.Language.NLL:
				case AST.Language.NLL_DEF:
				{
#line 83 "../../../Source/Core/AST/DelegateDecl.nll"
					pOutputBuilder.m_sOut.Append("delegate ");
#line 84 "../../../Source/Core/AST/DelegateDecl.nll"
					break;
				}

			}
#line 88 "../../../Source/Core/AST/DelegateDecl.nll"
			m_pFunctionDecl.m_pTypeRef.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 89 "../../../Source/Core/AST/DelegateDecl.nll"
			pOutputBuilder.m_sOut.AppendChar(' ');
#line 91 "../../../Source/Core/AST/DelegateDecl.nll"
			if (eLanguage == AST.Language.CPP)
#line 92 "../../../Source/Core/AST/DelegateDecl.nll"
				pOutputBuilder.m_sOut.AppendChar('(');
#line 93 "../../../Source/Core/AST/DelegateDecl.nll"
			pOutputBuilder.m_sOut.Append(m_pFunctionDecl.m_pNameToken.GetString());
#line 94 "../../../Source/Core/AST/DelegateDecl.nll"
			if (eLanguage == AST.Language.CPP)
#line 95 "../../../Source/Core/AST/DelegateDecl.nll"
				pOutputBuilder.m_sOut.AppendChar(')');
#line 97 "../../../Source/Core/AST/DelegateDecl.nll"
			m_pFunctionDecl.m_pParamDecl.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 99 "../../../Source/Core/AST/DelegateDecl.nll"
			pOutputBuilder.m_sOut.Append(";\n");
		}

	}
}

