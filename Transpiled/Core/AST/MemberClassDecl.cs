#line 1 "../../../Source/Core/AST/MemberClassDecl.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/MemberClassDecl.nll"
	class MemberClassDecl : AST
	{
#line 6 "../../../Source/Core/AST/MemberClassDecl.nll"
		public ClassDecl m_pParentClassDecl;
#line 7 "../../../Source/Core/AST/MemberClassDecl.nll"
		public AccessLevel m_pAccessLevel;
#line 8 "../../../Source/Core/AST/MemberClassDecl.nll"
		public ClassDecl m_pClassDecl;
#line 10 "../../../Source/Core/AST/MemberClassDecl.nll"
		public MemberClassDecl()
		{
#line 12 "../../../Source/Core/AST/MemberClassDecl.nll"
			m_eType = AST.Type.AST_MEMBER_CLASS_DECL;
#line 13 "../../../Source/Core/AST/MemberClassDecl.nll"
			m_bCanDescend = true;
		}

#line 16 "../../../Source/Core/AST/MemberClassDecl.nll"
		public static MemberClassDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum, ClassDecl pParentClassDecl)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			AccessLevel pAccessLevel = AccessLevel.TryCreate(pTokenContainer, pTempOffset);
#line 21 "../../../Source/Core/AST/MemberClassDecl.nll"
			if (pAccessLevel == null)
			{
#line 22 "../../../Source/Core/AST/MemberClassDecl.nll"
				return null;
			}
			MemberClassDecl pMemberClassDecl = new MemberClassDecl();
#line 26 "../../../Source/Core/AST/MemberClassDecl.nll"
			pMemberClassDecl.m_pParentClassDecl = pParentClassDecl;
#line 27 "../../../Source/Core/AST/MemberClassDecl.nll"
			pMemberClassDecl.m_pAccessLevel = pAccessLevel;
#line 28 "../../../Source/Core/AST/MemberClassDecl.nll"
			pMemberClassDecl.m_pFirstToken = pAccessLevel.m_pFirstToken;
			ClassDecl pClassDecl = ClassDecl.TryCreate(pTokenContainer, pTempOffset, pMemberClassDecl);
#line 32 "../../../Source/Core/AST/MemberClassDecl.nll"
			if (pClassDecl == null)
			{
#line 33 "../../../Source/Core/AST/MemberClassDecl.nll"
				return null;
			}
			NumbatLogic.AccessLevel __98877649 = pAccessLevel;
#line 35 "../../../Source/Core/AST/MemberClassDecl.nll"
			pAccessLevel = null;
#line 35 "../../../Source/Core/AST/MemberClassDecl.nll"
			pMemberClassDecl.AddChild(__98877649);
#line 37 "../../../Source/Core/AST/MemberClassDecl.nll"
			pMemberClassDecl.m_pClassDecl = pClassDecl;
			NumbatLogic.ClassDecl __3174337334 = pClassDecl;
#line 38 "../../../Source/Core/AST/MemberClassDecl.nll"
			pClassDecl = null;
#line 38 "../../../Source/Core/AST/MemberClassDecl.nll"
			pMemberClassDecl.AddChild(__3174337334);
#line 40 "../../../Source/Core/AST/MemberClassDecl.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.MemberClassDecl __578676116 = pMemberClassDecl;
#line 41 "../../../Source/Core/AST/MemberClassDecl.nll"
			pMemberClassDecl = null;
#line 41 "../../../Source/Core/AST/MemberClassDecl.nll"
			return __578676116;
		}

#line 44 "../../../Source/Core/AST/MemberClassDecl.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
#line 46 "../../../Source/Core/AST/MemberClassDecl.nll"
			base.Validate(pValidator, pParent);
		}

#line 49 "../../../Source/Core/AST/MemberClassDecl.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 63 "../../../Source/Core/AST/MemberClassDecl.nll"
			pOutputBuilder.UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 64 "../../../Source/Core/AST/MemberClassDecl.nll"
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 66 "../../../Source/Core/AST/MemberClassDecl.nll"
			if (!(eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE))
			{
#line 68 "../../../Source/Core/AST/MemberClassDecl.nll"
				m_pAccessLevel.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 70 "../../../Source/Core/AST/MemberClassDecl.nll"
				if (eLanguage == AST.Language.CPP)
#line 71 "../../../Source/Core/AST/MemberClassDecl.nll"
					pOutputBuilder.m_sOut.AppendChar(':');
#line 73 "../../../Source/Core/AST/MemberClassDecl.nll"
				pOutputBuilder.m_sOut.AppendChar(' ');
			}
#line 76 "../../../Source/Core/AST/MemberClassDecl.nll"
			m_pClassDecl.Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
		}

	}
}

