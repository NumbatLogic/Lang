namespace NumberDuck
{
	namespace Secret
	{
		class EnumDecl : AST
		{
			public Token m_pNameToken;
			public Vector<EnumDeclValue> m_pEnumDeclValueVector;
			public EnumDecl()
			{
				m_bCanDescend = true;
			}

			public static EnumDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
			{
				OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
				Token pEnumToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_ENUM);
				if (pEnumToken == null)
				{
					return null;
				}
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
				EnumDecl pEnumDecl = new EnumDecl();
				pEnumDecl.m_eType = AST.Type.AST_ENUM_DECL;
				pEnumDecl.m_pFirstToken = pEnumToken;
				pEnumDecl.m_pEnumDeclValueVector = new Vector<EnumDeclValue>();
				pEnumDecl.m_pNameToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_IDENTIFIER);
				if (pEnumDecl.m_pNameToken == null)
				{
					Console.Log("expected enum name");
					NumbatLogic.Assert.Plz(false);
					{
						return null;
					}
				}
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_CURLY_BRACE_LEFT) == null)
				{
					Console.Log("expected opening curly brace");
					NumbatLogic.Assert.Plz(false);
					{
						return null;
					}
				}
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
				while (true)
				{
					if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_CURLY_BRACE_RIGHT) != null)
					{
						pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
						break;
					}
					EnumDeclValue pEnumDeclValue = EnumDeclValue.TryCreate(pTokenContainer, pTempOffset);
					if (pEnumDeclValue == null)
					{
						Console.Log("expected EnumDeclValue");
						NumbatLogic.Assert.Plz(false);
					}
					pEnumDecl.m_pEnumDeclValueVector.PushBack(pEnumDeclValue);
					{
						NumberDuck.Secret.EnumDeclValue __954462356 = pEnumDeclValue;
						pEnumDeclValue = null;
						pEnumDecl.AddChild(__954462356);
					}
					if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_CURLY_BRACE_RIGHT) != null)
					{
						continue;
					}
					if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_COMMA) == null)
					{
						Console.Log("expected comma");
						Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
						NumbatLogic.Assert.Plz(false);
					}
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
				}
				pOffsetDatum.Set(pTempOffset);
				{
					NumberDuck.Secret.EnumDecl __3345757416 = pEnumDecl;
					pEnumDecl = null;
					{
						return __3345757416;
					}
				}
			}

			public override AST FindByName(string sxName, AST pCallingChild)
			{
				if (ExternalString.Equal(sxName, m_pNameToken.GetString()))
					return this;
				return base.FindByName(sxName, pCallingChild);
			}

			public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
			{
				sOut.Append("enum ");
				m_pNameToken.Stringify(sOut);
				sOut.AppendChar('\n');
				Util.Pad(nDepth, sOut);
				sOut.Append("{\n");
				for (int i = 0; i < m_pEnumDeclValueVector.GetSize(); i++)
				{
					Util.Pad(nDepth + 1, sOut);
					EnumDeclValue pEnumDeclValue = m_pEnumDeclValueVector.Get(i);
					pEnumDeclValue.Stringify(eLanguage, eOutputFile, 0, sOut);
					sOut.Append(",\n");
				}
				Util.Pad(nDepth, sOut);
				if (eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.HEADER)
					sOut.Append("};\n");
				else
					sOut.Append("}\n");
			}

			~EnumDecl()
			{
			}

		}
	}
}

