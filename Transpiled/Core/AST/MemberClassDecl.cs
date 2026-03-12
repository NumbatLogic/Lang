#line 1 "../../../Source/Core/AST/MemberClassDecl.nll"
namespace NumbatLogic
{
	class MemberClassDecl : AST
	{
		public ClassDecl m_pParentClassDecl;
		public AccessLevel m_pAccessLevel;
		public ClassDecl m_pClassDecl;
#line 9 "../../../Source/Core/AST/MemberClassDecl.nll"
		public MemberClassDecl()
		{
			m_eType = AST.Type.AST_MEMBER_CLASS_DECL;
			m_bCanDescend = true;
		}

		public static MemberClassDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum, ClassDecl pParentClassDecl)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 19 "../../../Source/Core/AST/MemberClassDecl.nll"
			AccessLevel pAccessLevel = AccessLevel.TryCreate(pTokenContainer, pTempOffset);
			if (pAccessLevel == null)
			{
#line 21 "../../../Source/Core/AST/MemberClassDecl.nll"
				return null;
			}
			MemberClassDecl pMemberClassDecl = new MemberClassDecl();
#line 25 "../../../Source/Core/AST/MemberClassDecl.nll"
			pMemberClassDecl.m_pParentClassDecl = pParentClassDecl;
			pMemberClassDecl.m_pAccessLevel = pAccessLevel;
			pMemberClassDecl.m_pFirstToken = pAccessLevel.m_pFirstToken;
#line 30 "../../../Source/Core/AST/MemberClassDecl.nll"
			ClassDecl pClassDecl = ClassDecl.TryCreate(pTokenContainer, pTempOffset, pMemberClassDecl);
			if (pClassDecl == null)
			{
#line 32 "../../../Source/Core/AST/MemberClassDecl.nll"
				return null;
			}
			NumbatLogic.AccessLevel __98877649 = pAccessLevel;
#line 34 "../../../Source/Core/AST/MemberClassDecl.nll"
			pAccessLevel = null;
#line 34 "../../../Source/Core/AST/MemberClassDecl.nll"
			pMemberClassDecl.AddChild(__98877649);
#line 36 "../../../Source/Core/AST/MemberClassDecl.nll"
			pMemberClassDecl.m_pClassDecl = pClassDecl;
			NumbatLogic.ClassDecl __3174337334 = pClassDecl;
#line 37 "../../../Source/Core/AST/MemberClassDecl.nll"
			pClassDecl = null;
#line 37 "../../../Source/Core/AST/MemberClassDecl.nll"
			pMemberClassDecl.AddChild(__3174337334);
#line 39 "../../../Source/Core/AST/MemberClassDecl.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.MemberClassDecl __578676116 = pMemberClassDecl;
#line 40 "../../../Source/Core/AST/MemberClassDecl.nll"
			pMemberClassDecl = null;
#line 40 "../../../Source/Core/AST/MemberClassDecl.nll"
			return __578676116;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			base.Validate(pValidator, pParent);
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 62 "../../../Source/Core/AST/MemberClassDecl.nll"
			pOutputBuilder.UpdateSourceLocation(eLanguage, m_pFirstToken);
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 65 "../../../Source/Core/AST/MemberClassDecl.nll"
			if (!(eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE))
			{
				m_pAccessLevel.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 69 "../../../Source/Core/AST/MemberClassDecl.nll"
				if (eLanguage == AST.Language.CPP)
					pOutputBuilder.m_sOut.AppendChar(':');
#line 72 "../../../Source/Core/AST/MemberClassDecl.nll"
				pOutputBuilder.m_sOut.AppendChar(' ');
			}
#line 75 "../../../Source/Core/AST/MemberClassDecl.nll"
			m_pClassDecl.Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
		}

	}
}

