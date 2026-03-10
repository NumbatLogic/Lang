#line 1 "../../../Source/Core/AST/MemberVarDecl.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/MemberVarDecl.nll"
	class MemberVarDecl : AST
	{
#line 5 "../../../Source/Core/AST/MemberVarDecl.nll"
		public AccessLevel m_pAccessLevel;
#line 6 "../../../Source/Core/AST/MemberVarDecl.nll"
		public bool m_bStatic;
#line 7 "../../../Source/Core/AST/MemberVarDecl.nll"
		public VarDecl m_pVarDecl;
#line 9 "../../../Source/Core/AST/MemberVarDecl.nll"
		public MemberVarDecl()
		{
#line 11 "../../../Source/Core/AST/MemberVarDecl.nll"
			m_bCanDescend = true;
		}

#line 14 "../../../Source/Core/AST/MemberVarDecl.nll"
		public static MemberVarDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
#line 16 "../../../Source/Core/AST/MemberVarDecl.nll"
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 18 "../../../Source/Core/AST/MemberVarDecl.nll"
			bool bStatic = false;
#line 20 "../../../Source/Core/AST/MemberVarDecl.nll"
			AccessLevel pAccessLevel = AccessLevel.TryCreate(pTokenContainer, pTempOffset);
#line 21 "../../../Source/Core/AST/MemberVarDecl.nll"
			if (pAccessLevel == null)
			{
#line 22 "../../../Source/Core/AST/MemberVarDecl.nll"
				return null;
			}
#line 24 "../../../Source/Core/AST/MemberVarDecl.nll"
			Token pStaticToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_STATIC);
#line 25 "../../../Source/Core/AST/MemberVarDecl.nll"
			if (pStaticToken != null)
			{
#line 27 "../../../Source/Core/AST/MemberVarDecl.nll"
				bStatic = true;
#line 28 "../../../Source/Core/AST/MemberVarDecl.nll"
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			}
#line 31 "../../../Source/Core/AST/MemberVarDecl.nll"
			VarDecl pVarDecl = VarDecl.TryCreate(pTokenContainer, pTempOffset, false);
#line 32 "../../../Source/Core/AST/MemberVarDecl.nll"
			if (pVarDecl == null)
			{
#line 33 "../../../Source/Core/AST/MemberVarDecl.nll"
				return null;
			}
#line 35 "../../../Source/Core/AST/MemberVarDecl.nll"
			MemberVarDecl pMemberVarDecl = new MemberVarDecl();
#line 37 "../../../Source/Core/AST/MemberVarDecl.nll"
			pMemberVarDecl.m_eType = AST.Type.AST_MEMBER_VAR_DECL;
#line 38 "../../../Source/Core/AST/MemberVarDecl.nll"
			pMemberVarDecl.m_pAccessLevel = pAccessLevel;
#line 39 "../../../Source/Core/AST/MemberVarDecl.nll"
			pMemberVarDecl.m_bStatic = bStatic;
#line 40 "../../../Source/Core/AST/MemberVarDecl.nll"
			pMemberVarDecl.m_pVarDecl = pVarDecl;
			NumbatLogic.AccessLevel __98943246 = pAccessLevel;
#line 42 "../../../Source/Core/AST/MemberVarDecl.nll"
			pAccessLevel = null;
#line 42 "../../../Source/Core/AST/MemberVarDecl.nll"
			pMemberVarDecl.AddChild(__98943246);
			NumbatLogic.VarDecl __2365456416 = pVarDecl;
#line 43 "../../../Source/Core/AST/MemberVarDecl.nll"
			pVarDecl = null;
#line 43 "../../../Source/Core/AST/MemberVarDecl.nll"
			pMemberVarDecl.AddChild(__2365456416);
#line 45 "../../../Source/Core/AST/MemberVarDecl.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.MemberVarDecl __4110847305 = pMemberVarDecl;
#line 46 "../../../Source/Core/AST/MemberVarDecl.nll"
			pMemberVarDecl = null;
#line 46 "../../../Source/Core/AST/MemberVarDecl.nll"
			return __4110847305;
		}

#line 49 "../../../Source/Core/AST/MemberVarDecl.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
#line 51 "../../../Source/Core/AST/MemberVarDecl.nll"
			base.Validate(pValidator, pParent);
#line 53 "../../../Source/Core/AST/MemberVarDecl.nll"
			InternalString sTemp = new InternalString(m_pVarDecl.m_pNameToken.GetString());
#line 54 "../../../Source/Core/AST/MemberVarDecl.nll"
			if (!(sTemp.StartsWith("m_") || sTemp.StartsWith("__")) && !m_pVarDecl.m_pTypeRef.m_bConst)
			{
#line 56 "../../../Source/Core/AST/MemberVarDecl.nll"
				pValidator.AddError("Member var name does not start with \"m_\"", m_pVarDecl.m_pNameToken.m_sFileName, m_pVarDecl.m_pNameToken.m_nLine, m_pVarDecl.m_pNameToken.m_nColumn);
			}
		}

#line 60 "../../../Source/Core/AST/MemberVarDecl.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 62 "../../../Source/Core/AST/MemberVarDecl.nll"
			bool bArrayAssignment = m_pVarDecl.m_pArraySizeVector != null && m_pVarDecl.m_pAssignment != null;
#line 67 "../../../Source/Core/AST/MemberVarDecl.nll"
			if (eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE)
			{
#line 69 "../../../Source/Core/AST/MemberVarDecl.nll"
				bool bDoIt = false;
#line 70 "../../../Source/Core/AST/MemberVarDecl.nll"
				if (bArrayAssignment)
#line 71 "../../../Source/Core/AST/MemberVarDecl.nll"
					bDoIt = true;
#line 74 "../../../Source/Core/AST/MemberVarDecl.nll"
				if (m_bStatic && !(m_pVarDecl.m_pTypeRef.m_bConst && m_pVarDecl.m_pTypeRef.IsIntegral()))
#line 75 "../../../Source/Core/AST/MemberVarDecl.nll"
					bDoIt = true;
#line 77 "../../../Source/Core/AST/MemberVarDecl.nll"
				if (!bDoIt)
#line 78 "../../../Source/Core/AST/MemberVarDecl.nll"
					return;
			}
#line 82 "../../../Source/Core/AST/MemberVarDecl.nll"
			pOutputBuilder.UpdateSourceLocation(eLanguage, m_pVarDecl.m_pFirstToken);
#line 83 "../../../Source/Core/AST/MemberVarDecl.nll"
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 85 "../../../Source/Core/AST/MemberVarDecl.nll"
			if (!(eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE))
			{
#line 87 "../../../Source/Core/AST/MemberVarDecl.nll"
				m_pAccessLevel.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 88 "../../../Source/Core/AST/MemberVarDecl.nll"
				if (eLanguage == AST.Language.CPP)
#line 89 "../../../Source/Core/AST/MemberVarDecl.nll"
					pOutputBuilder.m_sOut.AppendChar(':');
#line 90 "../../../Source/Core/AST/MemberVarDecl.nll"
				pOutputBuilder.m_sOut.AppendChar(' ');
#line 92 "../../../Source/Core/AST/MemberVarDecl.nll"
				if (m_bStatic)
				{
#line 94 "../../../Source/Core/AST/MemberVarDecl.nll"
					if (eLanguage == AST.Language.CS)
					{
#line 96 "../../../Source/Core/AST/MemberVarDecl.nll"
						if (m_pVarDecl.m_pTypeRef.m_bConst == false || !m_pVarDecl.m_pTypeRef.IsIntegral() || m_pVarDecl.m_pArraySizeVector != null)
#line 97 "../../../Source/Core/AST/MemberVarDecl.nll"
							pOutputBuilder.m_sOut.AppendString("static ");
					}
					else
					{
#line 101 "../../../Source/Core/AST/MemberVarDecl.nll"
						pOutputBuilder.m_sOut.AppendString("static ");
					}
				}
			}
#line 107 "../../../Source/Core/AST/MemberVarDecl.nll"
			m_pVarDecl.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		}

	}
}

