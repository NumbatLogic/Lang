#line 1 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
namespace NumbatLogic
{
	class DelegateDecl : AST
	{
		public AccessLevel m_pAccessLevel;
		public FunctionDecl m_pFunctionDecl;
#line 8 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
		public DelegateDecl()
		{
			m_eType = AST.Type.DELEGATE_DECL;
		}

		public static DelegateDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum, ClassDecl pParentClassDecl)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 17 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
			AccessLevel pAccessLevel = AccessLevel.TryCreate(pTokenContainer, pTempOffset);
			if (pAccessLevel == null)
			{
#line 19 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
				return null;
			}
			Token pToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_DELEGATE);
			if (pToken == null)
			{
#line 23 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
				return null;
			}
#line 24 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 26 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
			DelegateDecl pDelegateDecl = new DelegateDecl();
			pDelegateDecl.m_pFirstToken = pToken;
			pDelegateDecl.m_pAccessLevel = pAccessLevel;
			NumbatLogic.AccessLevel __98812055 = pAccessLevel;
#line 29 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
			pAccessLevel = null;
#line 29 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
			pDelegateDecl.AddChild(__98812055);
#line 31 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
			FunctionDecl pFunctionDecl = FunctionDecl.TryCreate(pTokenContainer, pTempOffset, null);
			if (pFunctionDecl == null)
			{
				Console.Log("expected function decl");
				Assert.Plz(false);
				return null;
			}
#line 39 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
			if (pFunctionDecl.m_pScope != null)
			{
				Console.Log("function def can't have scope!");
				Assert.Plz(false);
				return null;
			}
#line 46 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
			pDelegateDecl.m_pFunctionDecl = pFunctionDecl;
			NumbatLogic.FunctionDecl __4279829941 = pFunctionDecl;
#line 47 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
			pFunctionDecl = null;
#line 47 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
			pDelegateDecl.AddChild(__4279829941);
#line 49 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.DelegateDecl __305311194 = pDelegateDecl;
#line 50 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
			pDelegateDecl = null;
#line 50 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
			return __305311194;
		}

#line 58 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 63 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
			if (eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE)
				return;
#line 66 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
			m_pAccessLevel.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			if (eLanguage == AST.Language.CPP)
				pOutputBuilder.m_sOut.AppendChar(':');
			pOutputBuilder.m_sOut.AppendChar(' ');
#line 72 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
			switch (eLanguage)
			{
				case AST.Language.CPP:
				{
					pOutputBuilder.m_sOut.Append("typedef ");
					break;
				}

				case AST.Language.CS:
				case AST.Language.NLL:
				case AST.Language.NLL_DEF:
				{
#line 83 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
					pOutputBuilder.m_sOut.Append("delegate ");
					break;
				}

			}
			m_pFunctionDecl.m_pTypeRef.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			pOutputBuilder.m_sOut.AppendChar(' ');
#line 91 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
			if (eLanguage == AST.Language.CPP)
				pOutputBuilder.m_sOut.AppendChar('(');
			pOutputBuilder.m_sOut.Append(m_pFunctionDecl.m_pNameToken.GetString());
			if (eLanguage == AST.Language.CPP)
				pOutputBuilder.m_sOut.AppendChar(')');
#line 97 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
			m_pFunctionDecl.m_pParamDecl.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 99 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
			pOutputBuilder.m_sOut.Append(";\n");
		}

	}
}

