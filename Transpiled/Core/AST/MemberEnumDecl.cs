#line 1 "../../../Source/Core/AST/MemberEnumDecl.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/MemberEnumDecl.nll"
	class MemberEnumDecl : AST
	{
#line 5 "../../../Source/Core/AST/MemberEnumDecl.nll"
		public AccessLevel m_pAccessLevel;
#line 6 "../../../Source/Core/AST/MemberEnumDecl.nll"
		public EnumDecl m_pEnumDecl;
#line 8 "../../../Source/Core/AST/MemberEnumDecl.nll"
		public MemberEnumDecl()
		{
#line 10 "../../../Source/Core/AST/MemberEnumDecl.nll"
			m_bCanDescend = true;
		}

#line 13 "../../../Source/Core/AST/MemberEnumDecl.nll"
		public static MemberEnumDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
#line 15 "../../../Source/Core/AST/MemberEnumDecl.nll"
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 17 "../../../Source/Core/AST/MemberEnumDecl.nll"
			AccessLevel pAccessLevel = AccessLevel.TryCreate(pTokenContainer, pTempOffset);
#line 18 "../../../Source/Core/AST/MemberEnumDecl.nll"
			if (pAccessLevel == null)
			{
#line 19 "../../../Source/Core/AST/MemberEnumDecl.nll"
				return null;
			}
#line 21 "../../../Source/Core/AST/MemberEnumDecl.nll"
			EnumDecl pEnumDecl = EnumDecl.TryCreate(pTokenContainer, pTempOffset);
#line 22 "../../../Source/Core/AST/MemberEnumDecl.nll"
			if (pEnumDecl == null)
			{
#line 23 "../../../Source/Core/AST/MemberEnumDecl.nll"
				return null;
			}
#line 25 "../../../Source/Core/AST/MemberEnumDecl.nll"
			MemberEnumDecl pMemberEnumDecl = new MemberEnumDecl();
#line 27 "../../../Source/Core/AST/MemberEnumDecl.nll"
			pMemberEnumDecl.m_eType = AST.Type.AST_MEMBER_ENUM_DECL;
#line 28 "../../../Source/Core/AST/MemberEnumDecl.nll"
			pMemberEnumDecl.m_pAccessLevel = pAccessLevel;
#line 29 "../../../Source/Core/AST/MemberEnumDecl.nll"
			pMemberEnumDecl.m_pEnumDecl = pEnumDecl;
#line 30 "../../../Source/Core/AST/MemberEnumDecl.nll"
			pMemberEnumDecl.m_pFirstToken = pMemberEnumDecl.m_pAccessLevel.m_pFirstToken;
			NumbatLogic.AccessLevel __98877647 = pAccessLevel;
#line 32 "../../../Source/Core/AST/MemberEnumDecl.nll"
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

#line 39 "../../../Source/Core/AST/MemberEnumDecl.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 41 "../../../Source/Core/AST/MemberEnumDecl.nll"
			if (eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE)
#line 42 "../../../Source/Core/AST/MemberEnumDecl.nll"
				return;
#line 44 "../../../Source/Core/AST/MemberEnumDecl.nll"
			pOutputBuilder.UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 45 "../../../Source/Core/AST/MemberEnumDecl.nll"
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 47 "../../../Source/Core/AST/MemberEnumDecl.nll"
			m_pAccessLevel.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 48 "../../../Source/Core/AST/MemberEnumDecl.nll"
			if (eLanguage == AST.Language.CPP)
#line 49 "../../../Source/Core/AST/MemberEnumDecl.nll"
				pOutputBuilder.m_sOut.AppendChar(':');
#line 50 "../../../Source/Core/AST/MemberEnumDecl.nll"
			pOutputBuilder.m_sOut.AppendChar(' ');
#line 51 "../../../Source/Core/AST/MemberEnumDecl.nll"
			m_pEnumDecl.Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
#line 52 "../../../Source/Core/AST/MemberEnumDecl.nll"
			pOutputBuilder.m_sOut.AppendChar('\n');
		}

	}
}

