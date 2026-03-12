#line 1 "../../../Source/Core/AST/MemberEnumDecl.nll"
namespace NumbatLogic
{
	class MemberEnumDecl : AST
	{
		public AccessLevel m_pAccessLevel;
		public EnumDecl m_pEnumDecl;
#line 8 "../../../Source/Core/AST/MemberEnumDecl.nll"
		public MemberEnumDecl()
		{
			m_bCanDescend = true;
		}

		public static MemberEnumDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 17 "../../../Source/Core/AST/MemberEnumDecl.nll"
			AccessLevel pAccessLevel = AccessLevel.TryCreate(pTokenContainer, pTempOffset);
			if (pAccessLevel == null)
			{
#line 19 "../../../Source/Core/AST/MemberEnumDecl.nll"
				return null;
			}
			EnumDecl pEnumDecl = EnumDecl.TryCreate(pTokenContainer, pTempOffset);
			if (pEnumDecl == null)
			{
#line 23 "../../../Source/Core/AST/MemberEnumDecl.nll"
				return null;
			}
			MemberEnumDecl pMemberEnumDecl = new MemberEnumDecl();
#line 27 "../../../Source/Core/AST/MemberEnumDecl.nll"
			pMemberEnumDecl.m_eType = AST.Type.AST_MEMBER_ENUM_DECL;
			pMemberEnumDecl.m_pAccessLevel = pAccessLevel;
			pMemberEnumDecl.m_pEnumDecl = pEnumDecl;
			pMemberEnumDecl.m_pFirstToken = pMemberEnumDecl.m_pAccessLevel.m_pFirstToken;
			NumbatLogic.AccessLevel __98877647 = pAccessLevel;
			pAccessLevel = null;
#line 32 "../../../Source/Core/AST/MemberEnumDecl.nll"
			pMemberEnumDecl.AddChild(__98877647);
			NumbatLogic.EnumDecl __4281946683 = pEnumDecl;
#line 33 "../../../Source/Core/AST/MemberEnumDecl.nll"
			pEnumDecl = null;
#line 33 "../../../Source/Core/AST/MemberEnumDecl.nll"
			pMemberEnumDecl.AddChild(__4281946683);
#line 35 "../../../Source/Core/AST/MemberEnumDecl.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.MemberEnumDecl __645533336 = pMemberEnumDecl;
#line 36 "../../../Source/Core/AST/MemberEnumDecl.nll"
			pMemberEnumDecl = null;
#line 36 "../../../Source/Core/AST/MemberEnumDecl.nll"
			return __645533336;
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			if (eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE)
				return;
#line 44 "../../../Source/Core/AST/MemberEnumDecl.nll"
			pOutputBuilder.UpdateSourceLocation(eLanguage, m_pFirstToken);
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 47 "../../../Source/Core/AST/MemberEnumDecl.nll"
			m_pAccessLevel.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			if (eLanguage == AST.Language.CPP)
				pOutputBuilder.m_sOut.AppendChar(':');
			pOutputBuilder.m_sOut.AppendChar(' ');
			m_pEnumDecl.Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
			pOutputBuilder.m_sOut.AppendChar('\n');
		}

	}
}

