namespace NumbatLogic
{
	class MemberEnumDecl : AST
	{
		public AccessLevel m_pAccessLevel;
		public EnumDecl m_pEnumDecl;
		public MemberEnumDecl()
		{
			m_bCanDescend = true;
		}

		public static MemberEnumDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			AccessLevel pAccessLevel = AccessLevel.TryCreate(pTokenContainer, pTempOffset);
			if (pAccessLevel == null)
			{
				return null;
			}
			EnumDecl pEnumDecl = EnumDecl.TryCreate(pTokenContainer, pTempOffset);
			if (pEnumDecl == null)
			{
				return null;
			}
			MemberEnumDecl pMemberEnumDecl = new MemberEnumDecl();
			pMemberEnumDecl.m_eType = AST.Type.AST_MEMBER_ENUM_DECL;
			pMemberEnumDecl.m_pAccessLevel = pAccessLevel;
			pMemberEnumDecl.m_pEnumDecl = pEnumDecl;
			NumbatLogic.AccessLevel __257201134 = pAccessLevel;
			pAccessLevel = null;
			pMemberEnumDecl.AddChild(__257201134);
			NumbatLogic.EnumDecl __2346898043 = pEnumDecl;
			pEnumDecl = null;
			pMemberEnumDecl.AddChild(__2346898043);
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.MemberEnumDecl __1876560565 = pMemberEnumDecl;
			pMemberEnumDecl = null;
			return __1876560565;
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			if (eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE)
				return;
			Util.Pad(nDepth, sOut);
			m_pAccessLevel.Stringify(eLanguage, eOutputFile, 0, sOut);
			if (eLanguage == AST.Language.CPP)
				sOut.AppendChar(':');
			sOut.AppendChar(' ');
			m_pEnumDecl.Stringify(eLanguage, eOutputFile, nDepth, sOut);
			sOut.AppendChar('\n');
		}

	}
}

