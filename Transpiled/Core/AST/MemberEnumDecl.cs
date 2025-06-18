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
			{
				NumbatLogic.AccessLevel __2194276919 = pAccessLevel;
				pAccessLevel = null;
				pMemberEnumDecl.AddChild(__2194276919);
			}
			{
				NumbatLogic.EnumDecl __3345757416 = pEnumDecl;
				pEnumDecl = null;
				pMemberEnumDecl.AddChild(__3345757416);
			}
			pOffsetDatum.Set(pTempOffset);
			{
				NumbatLogic.MemberEnumDecl __26865667 = pMemberEnumDecl;
				pMemberEnumDecl = null;
				{
					return __26865667;
				}
			}
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

