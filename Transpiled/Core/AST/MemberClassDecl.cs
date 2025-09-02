namespace NumbatLogic
{
	class MemberClassDecl : AST
	{
		public ClassDecl m_pParentClassDecl;
		public AccessLevel m_pAccessLevel;
		public ClassDecl m_pClassDecl;
		public MemberClassDecl()
		{
			m_eType = AST.Type.AST_MEMBER_CLASS_DECL;
			m_bCanDescend = true;
		}

		public static MemberClassDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum, ClassDecl pParentClassDecl)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			AccessLevel pAccessLevel = AccessLevel.TryCreate(pTokenContainer, pTempOffset);
			if (pAccessLevel == null)
			{
				return null;
			}
			MemberClassDecl pMemberClassDecl = new MemberClassDecl();
			pMemberClassDecl.m_pParentClassDecl = pParentClassDecl;
			pMemberClassDecl.m_pAccessLevel = pAccessLevel;
			pMemberClassDecl.m_pFirstToken = pAccessLevel.m_pFirstToken;
			ClassDecl pClassDecl = ClassDecl.TryCreate(pTokenContainer, pTempOffset, pMemberClassDecl);
			if (pClassDecl == null)
			{
				return null;
			}
			NumbatLogic.AccessLevel __475304624 = pAccessLevel;
			pAccessLevel = null;
			pMemberClassDecl.AddChild(__475304624);
			pMemberClassDecl.m_pClassDecl = pClassDecl;
			NumbatLogic.ClassDecl __2197702937 = pClassDecl;
			pClassDecl = null;
			pMemberClassDecl.AddChild(__2197702937);
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.MemberClassDecl __3387277467 = pMemberClassDecl;
			pMemberClassDecl = null;
			return __3387277467;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			base.Validate(pValidator, pParent);
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			Util.Pad(nDepth, sOut);
			if (!(eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE))
			{
				m_pAccessLevel.Stringify(eLanguage, eOutputFile, 0, sOut);
				if (eLanguage == AST.Language.CPP)
					sOut.AppendChar(':');
				sOut.AppendChar(' ');
			}
			m_pClassDecl.Stringify(eLanguage, eOutputFile, nDepth, sOut);
		}

	}
}

