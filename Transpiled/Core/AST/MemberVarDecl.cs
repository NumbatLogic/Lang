#line 1 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
namespace NumbatLogic
{
	class MemberVarDecl : AST
	{
		public AccessLevel m_pAccessLevel;
		public bool m_bStatic;
		public VarDecl m_pVarDecl;
#line 9 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
		public MemberVarDecl()
		{
			m_bCanDescend = true;
		}

		public static MemberVarDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 18 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
			bool bStatic = false;
#line 20 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
			AccessLevel pAccessLevel = AccessLevel.TryCreate(pTokenContainer, pTempOffset);
			if (pAccessLevel == null)
			{
#line 22 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
				return null;
			}
			Token pStaticToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_STATIC);
			if (pStaticToken != null)
			{
				bStatic = true;
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			}
#line 31 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
			VarDecl pVarDecl = VarDecl.TryCreate(pTokenContainer, pTempOffset, false);
			if (pVarDecl == null)
			{
#line 33 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
				return null;
			}
			MemberVarDecl pMemberVarDecl = new MemberVarDecl();
#line 37 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
			pMemberVarDecl.m_eType = AST.Type.AST_MEMBER_VAR_DECL;
			pMemberVarDecl.m_pAccessLevel = pAccessLevel;
			pMemberVarDecl.m_bStatic = bStatic;
			pMemberVarDecl.m_pVarDecl = pVarDecl;
			NumbatLogic.AccessLevel __98943246 = pAccessLevel;
			pAccessLevel = null;
#line 42 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
			pMemberVarDecl.AddChild(__98943246);
			NumbatLogic.VarDecl __2365456416 = pVarDecl;
#line 43 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
			pVarDecl = null;
#line 43 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
			pMemberVarDecl.AddChild(__2365456416);
#line 45 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.MemberVarDecl __4110847305 = pMemberVarDecl;
#line 46 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
			pMemberVarDecl = null;
#line 46 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
			return __4110847305;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			base.Validate(pValidator, pParent);
#line 53 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
			InternalString sTemp = new InternalString(m_pVarDecl.m_pNameToken.GetString());
			if (!(sTemp.StartsWith("m_") || sTemp.StartsWith("__")) && !m_pVarDecl.m_pTypeRef.m_bConst)
			{
				pValidator.AddError("Member var name does not start with \"m_\"", m_pVarDecl.m_pNameToken.m_sFileName, m_pVarDecl.m_pNameToken.m_nLine, m_pVarDecl.m_pNameToken.m_nColumn);
			}
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			bool bArrayAssignment = m_pVarDecl.m_pArraySizeVector != null && m_pVarDecl.m_pAssignment != null;
#line 67 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
			if (eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE)
			{
				bool bDoIt = false;
				if (bArrayAssignment)
					bDoIt = true;
#line 74 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
				if (m_bStatic && !(m_pVarDecl.m_pTypeRef.m_bConst && m_pVarDecl.m_pTypeRef.IsIntegral()))
					bDoIt = true;
#line 77 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
				if (!bDoIt)
					return;
			}
#line 82 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
			pOutputBuilder.UpdateSourceLocation(eLanguage, m_pVarDecl.m_pFirstToken);
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 85 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
			if (!(eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE))
			{
				m_pAccessLevel.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
				if (eLanguage == AST.Language.CPP)
					pOutputBuilder.m_sOut.AppendChar(':');
				pOutputBuilder.m_sOut.AppendChar(' ');
#line 92 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
				if (m_bStatic)
				{
					if (eLanguage == AST.Language.CS)
					{
						if (m_pVarDecl.m_pTypeRef.m_bConst == false || !m_pVarDecl.m_pTypeRef.IsIntegral() || m_pVarDecl.m_pArraySizeVector != null)
							pOutputBuilder.m_sOut.AppendString("static ");
					}
					else
					{
						pOutputBuilder.m_sOut.AppendString("static ");
					}
				}
			}
#line 107 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
			m_pVarDecl.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		}

	}
}

