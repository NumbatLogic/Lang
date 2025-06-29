namespace NumbatLogic
{
	class MemberFunctionDecl : AST
	{
		public ClassDecl m_pParentClassDecl;
		public AccessLevel m_pAccessLevel;
		public FunctionDecl m_pFunctionDecl;
		public bool m_bStatic;
		public bool m_bVirtual;
		public bool m_bOverride;
		public MemberFunctionDecl()
		{
			m_eType = AST.Type.AST_MEMBER_FUNCTION_DECL;
			m_bCanDescend = true;
		}

		public static MemberFunctionDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum, ClassDecl pParentClassDecl)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			AccessLevel pAccessLevel = AccessLevel.TryCreate(pTokenContainer, pTempOffset);
			if (pAccessLevel == null)
			{
				return null;
			}
			bool bStatic = false;
			bool bVirtual = false;
			bool bOverride = false;
			Token pToken = pTokenContainer.Peek(pTempOffset);
			if (pToken == null)
			{
				return null;
			}
			switch (pToken.m_eType)
			{
				case Token.Type.TOKEN_KEYWORD_STATIC:
				{
					bStatic = true;
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
					break;
				}

				case Token.Type.TOKEN_KEYWORD_VIRTUAL:
				{
					bVirtual = true;
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
					break;
				}

				case Token.Type.TOKEN_KEYWORD_OVERRIDE:
				{
					bOverride = true;
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
					break;
				}

			}
			MemberFunctionDecl pMemberFunctionDecl = new MemberFunctionDecl();
			pMemberFunctionDecl.m_pParent = pParentClassDecl;
			pMemberFunctionDecl.m_pParentClassDecl = pParentClassDecl;
			pMemberFunctionDecl.m_pAccessLevel = pAccessLevel;
			pMemberFunctionDecl.m_pFirstToken = pAccessLevel.m_pFirstToken;
			pMemberFunctionDecl.m_bStatic = bStatic;
			pMemberFunctionDecl.m_bVirtual = bVirtual;
			pMemberFunctionDecl.m_bOverride = bOverride;
			FunctionDecl pFunctionDecl = FunctionDecl.TryCreate(pTokenContainer, pTempOffset, pMemberFunctionDecl);
			if (pFunctionDecl == null)
			{
				return null;
			}
			NumbatLogic.AccessLevel __3646168542 = pAccessLevel;
			pAccessLevel = null;
			pMemberFunctionDecl.AddChild(__3646168542);
			pMemberFunctionDecl.m_pFunctionDecl = pFunctionDecl;
			NumbatLogic.FunctionDecl __1624742725 = pFunctionDecl;
			pFunctionDecl = null;
			pMemberFunctionDecl.AddChild(__1624742725);
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.MemberFunctionDecl __3782689298 = pMemberFunctionDecl;
			pMemberFunctionDecl = null;
			return __3782689298;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			base.Validate(pValidator, pParent);
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			if (eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE)
			{
				if (m_pParentClassDecl.m_pGenericTypeDeclVector.GetSize() > 0)
				{
				}
			}
			Util.Pad(nDepth, sOut);
			if (!(eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE))
			{
				m_pAccessLevel.Stringify(eLanguage, eOutputFile, 0, sOut);
				if (eLanguage == AST.Language.CPP)
					sOut.AppendChar(':');
				if (m_bStatic)
					sOut.Append(" static");
				if (m_bVirtual)
					sOut.Append(" virtual");
				if (m_bOverride)
					if (eLanguage == AST.Language.CPP)
						sOut.Append(" virtual");
					else
						sOut.Append(" override");
				sOut.AppendChar(' ');
			}
			m_pFunctionDecl.Stringify(eLanguage, eOutputFile, nDepth, sOut);
		}

	}
}

