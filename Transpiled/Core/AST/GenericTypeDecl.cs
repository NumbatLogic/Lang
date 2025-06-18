namespace NumbatLogic
{
	class GenericTypeDecl : AST
	{
		public static GenericTypeDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token pTypeToken = pTokenContainer.Peek(pTempOffset);
			if (pTypeToken == null || pTypeToken.m_eType != Token.Type.TOKEN_IDENTIFIER)
			{
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			GenericTypeDecl pGenericTypeDecl = new GenericTypeDecl();
			pGenericTypeDecl.m_eType = AST.Type.AST_GENERIC_TYPE_DECL;
			pGenericTypeDecl.m_pFirstToken = pTypeToken;
			pOffsetDatum.Set(pTempOffset);
			{
				NumbatLogic.GenericTypeDecl __3828846222 = pGenericTypeDecl;
				pGenericTypeDecl = null;
				{
					return __3828846222;
				}
			}
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			m_pFirstToken.Stringify(sOut);
		}

	}
}

