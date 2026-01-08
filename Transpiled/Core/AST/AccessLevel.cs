namespace NumbatLogic
{
	class AccessLevel : AST
	{
		public static AccessLevel TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token pAccessLevelToken = pTokenContainer.Peek(pTempOffset);
			if (pAccessLevelToken == null || pAccessLevelToken.m_eType != Token.Type.TOKEN_KEYWORD_PRIVATE && pAccessLevelToken.m_eType != Token.Type.TOKEN_KEYWORD_PUBLIC)
			{
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			AccessLevel pAccessLevel = new AccessLevel();
			pAccessLevel.m_eType = AST.Type.AST_ACCESS_LEVEL;
			pAccessLevel.m_pFirstToken = pAccessLevelToken;
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.AccessLevel __98812046 = pAccessLevel;
			pAccessLevel = null;
			return __98812046;
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			switch (m_pFirstToken.m_eType)
			{
				case Token.Type.TOKEN_KEYWORD_PRIVATE:
				{
					if (eLanguage == AST.Language.NLL_DEF)
						sOut.AppendString("private");
					else
						sOut.AppendString("protected");
					return;
				}

				case Token.Type.TOKEN_KEYWORD_PUBLIC:
				{
					sOut.AppendString("public");
					return;
				}

			}
			sOut.AppendString("???");
		}

	}
}

