#line 1 "../../../Source/Core/AST/AccessLevel.nll"
namespace NumbatLogic
{
	class AccessLevel : AST
	{
		public static AccessLevel TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 9 "../../../Source/Core/AST/AccessLevel.nll"
			Token pAccessLevelToken = pTokenContainer.Peek(pTempOffset);
			if (pAccessLevelToken == null || pAccessLevelToken.m_eType != Token.Type.TOKEN_KEYWORD_PRIVATE && pAccessLevelToken.m_eType != Token.Type.TOKEN_KEYWORD_PUBLIC)
			{
#line 11 "../../../Source/Core/AST/AccessLevel.nll"
				return null;
			}
#line 12 "../../../Source/Core/AST/AccessLevel.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 14 "../../../Source/Core/AST/AccessLevel.nll"
			AccessLevel pAccessLevel = new AccessLevel();
#line 16 "../../../Source/Core/AST/AccessLevel.nll"
			pAccessLevel.m_eType = AST.Type.AST_ACCESS_LEVEL;
			pAccessLevel.m_pFirstToken = pAccessLevelToken;
#line 19 "../../../Source/Core/AST/AccessLevel.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.AccessLevel __98812046 = pAccessLevel;
#line 20 "../../../Source/Core/AST/AccessLevel.nll"
			pAccessLevel = null;
#line 20 "../../../Source/Core/AST/AccessLevel.nll"
			return __98812046;
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			switch (m_pFirstToken.m_eType)
			{
				case Token.Type.TOKEN_KEYWORD_PRIVATE:
				{
					if (eLanguage == AST.Language.NLL_DEF)
						pOutputBuilder.m_sOut.AppendString("private");
					else
						pOutputBuilder.m_sOut.AppendString("protected");
					return;
				}

				case Token.Type.TOKEN_KEYWORD_PUBLIC:
				{
#line 37 "../../../Source/Core/AST/AccessLevel.nll"
					pOutputBuilder.m_sOut.AppendString("public");
					return;
				}

			}
#line 41 "../../../Source/Core/AST/AccessLevel.nll"
			pOutputBuilder.m_sOut.AppendString("???");
		}

	}
}

