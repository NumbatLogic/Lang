#line 1 "../../../Source/Core/AST/TorDecl.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/TorDecl.nll"
	class TorDecl : AST
	{
#line 6 "../../../Source/Core/AST/TorDecl.nll"
		public ClassDecl m_pParentClassDecl;
#line 7 "../../../Source/Core/AST/TorDecl.nll"
		public AccessLevel m_pAccessLevel;
#line 8 "../../../Source/Core/AST/TorDecl.nll"
		public Token m_pTypeToken;
#line 9 "../../../Source/Core/AST/TorDecl.nll"
		public ParamDecl m_pParamDecl;
#line 10 "../../../Source/Core/AST/TorDecl.nll"
		public ParamCall m_pBaseParamCall;
#line 11 "../../../Source/Core/AST/TorDecl.nll"
		public Scope m_pScope;
#line 12 "../../../Source/Core/AST/TorDecl.nll"
		public string m_sDisambiguate;
#line 14 "../../../Source/Core/AST/TorDecl.nll"
		public static TorDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum, ClassDecl pParentClassDecl)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			AccessLevel pAccessLevel = AccessLevel.TryCreate(pTokenContainer, pTempOffset);
#line 19 "../../../Source/Core/AST/TorDecl.nll"
			if (pAccessLevel == null)
			{
#line 20 "../../../Source/Core/AST/TorDecl.nll"
				return null;
			}
			Token pTypeToken = pTokenContainer.Peek(pTempOffset);
#line 23 "../../../Source/Core/AST/TorDecl.nll"
			if (pTypeToken == null || pTypeToken.m_eType != Token.Type.TOKEN_KEYWORD_CONSTRUCT && pTypeToken.m_eType != Token.Type.TOKEN_KEYWORD_DESTRUCT)
			{
#line 24 "../../../Source/Core/AST/TorDecl.nll"
				return null;
			}
#line 25 "../../../Source/Core/AST/TorDecl.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			ParamDecl pParamDecl = ParamDecl.TryCreate(pTokenContainer, pTempOffset);
#line 28 "../../../Source/Core/AST/TorDecl.nll"
			if (pParamDecl == null)
			{
#line 30 "../../../Source/Core/AST/TorDecl.nll"
				Console.Log("expected ParamDecl");
#line 31 "../../../Source/Core/AST/TorDecl.nll"
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 32 "../../../Source/Core/AST/TorDecl.nll"
				Assert.Plz(false);
#line 33 "../../../Source/Core/AST/TorDecl.nll"
				return null;
			}
			TorDecl pTorDecl = new TorDecl();
			Scope pScope = null;
			Token pSemicolon = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SEMICOLON);
#line 40 "../../../Source/Core/AST/TorDecl.nll"
			if (pSemicolon != null)
#line 41 "../../../Source/Core/AST/TorDecl.nll"
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			else
			{
				Token pColon = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_COLON);
#line 45 "../../../Source/Core/AST/TorDecl.nll"
				if (pColon != null)
				{
#line 47 "../../../Source/Core/AST/TorDecl.nll"
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
					Token pBase = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_BASE);
#line 50 "../../../Source/Core/AST/TorDecl.nll"
					if (pBase == null)
					{
#line 52 "../../../Source/Core/AST/TorDecl.nll"
						Console.Log("expected base!");
#line 53 "../../../Source/Core/AST/TorDecl.nll"
						Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 54 "../../../Source/Core/AST/TorDecl.nll"
						Assert.Plz(false);
#line 55 "../../../Source/Core/AST/TorDecl.nll"
						return null;
					}
#line 57 "../../../Source/Core/AST/TorDecl.nll"
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
					ParamCall pParamCall = ParamCall.TryCreate(pTokenContainer, pTempOffset);
#line 60 "../../../Source/Core/AST/TorDecl.nll"
					if (pParamCall == null)
					{
						InternalString sTemp = new InternalString("expected ParamCall ");
#line 63 "../../../Source/Core/AST/TorDecl.nll"
						sTemp.Append(pTokenContainer.StringifyOffset(pTempOffset));
#line 64 "../../../Source/Core/AST/TorDecl.nll"
						Console.Log(sTemp.GetExternalString());
#line 65 "../../../Source/Core/AST/TorDecl.nll"
						Assert.Plz(false);
#line 66 "../../../Source/Core/AST/TorDecl.nll"
						return null;
					}
#line 69 "../../../Source/Core/AST/TorDecl.nll"
					pTorDecl.m_pBaseParamCall = pParamCall;
					NumbatLogic.ParamCall __1502913502 = pParamCall;
#line 70 "../../../Source/Core/AST/TorDecl.nll"
					pParamCall = null;
#line 70 "../../../Source/Core/AST/TorDecl.nll"
					pTorDecl.AddChild(__1502913502);
				}
#line 73 "../../../Source/Core/AST/TorDecl.nll"
				pScope = Scope.TryCreate(pTokenContainer, pTempOffset, false);
#line 74 "../../../Source/Core/AST/TorDecl.nll"
				if (pScope == null)
				{
#line 76 "../../../Source/Core/AST/TorDecl.nll"
					Console.Log("expected scope");
#line 77 "../../../Source/Core/AST/TorDecl.nll"
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 78 "../../../Source/Core/AST/TorDecl.nll"
					Assert.Plz(false);
				}
			}
#line 82 "../../../Source/Core/AST/TorDecl.nll"
			pTorDecl.m_eType = AST.Type.AST_TOR_DECL;
#line 83 "../../../Source/Core/AST/TorDecl.nll"
			pTorDecl.m_pParent = pParentClassDecl;
#line 84 "../../../Source/Core/AST/TorDecl.nll"
			pTorDecl.m_pParentClassDecl = pParentClassDecl;
#line 85 "../../../Source/Core/AST/TorDecl.nll"
			pTorDecl.m_pFirstToken = pTypeToken;
#line 86 "../../../Source/Core/AST/TorDecl.nll"
			pTorDecl.m_pAccessLevel = pAccessLevel;
#line 87 "../../../Source/Core/AST/TorDecl.nll"
			pTorDecl.m_pTypeToken = pTypeToken;
#line 88 "../../../Source/Core/AST/TorDecl.nll"
			pTorDecl.m_pParamDecl = pParamDecl;
#line 89 "../../../Source/Core/AST/TorDecl.nll"
			pTorDecl.m_pScope = pScope;
#line 90 "../../../Source/Core/AST/TorDecl.nll"
			pTorDecl.m_sDisambiguate = "";
			NumbatLogic.AccessLevel __99271240 = pAccessLevel;
#line 92 "../../../Source/Core/AST/TorDecl.nll"
			pAccessLevel = null;
#line 92 "../../../Source/Core/AST/TorDecl.nll"
			pTorDecl.AddChild(__99271240);
			NumbatLogic.ParamDecl __3703057184 = pParamDecl;
#line 93 "../../../Source/Core/AST/TorDecl.nll"
			pParamDecl = null;
#line 93 "../../../Source/Core/AST/TorDecl.nll"
			pTorDecl.AddChild(__3703057184);
#line 94 "../../../Source/Core/AST/TorDecl.nll"
			if (pScope != null)
			{
				NumbatLogic.Scope __1530946527 = pScope;
#line 95 "../../../Source/Core/AST/TorDecl.nll"
				pScope = null;
#line 95 "../../../Source/Core/AST/TorDecl.nll"
				pTorDecl.AddChild(__1530946527);
			}
#line 97 "../../../Source/Core/AST/TorDecl.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.TorDecl __3519495631 = pTorDecl;
#line 98 "../../../Source/Core/AST/TorDecl.nll"
			pTorDecl = null;
#line 98 "../../../Source/Core/AST/TorDecl.nll"
			return __3519495631;
		}

#line 101 "../../../Source/Core/AST/TorDecl.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
#line 103 "../../../Source/Core/AST/TorDecl.nll"
			base.Validate(pValidator, pParent);
#line 107 "../../../Source/Core/AST/TorDecl.nll"
			if (m_pParentClassDecl != null && m_pBaseParamCall != null)
			{
				ClassDecl pBaseClass = m_pParentClassDecl.GetBaseClassDecl(pValidator);
#line 112 "../../../Source/Core/AST/TorDecl.nll"
				if (pBaseClass == null)
				{
#line 114 "../../../Source/Core/AST/TorDecl.nll"
					pValidator.AddError("no base class??", m_pBaseParamCall.m_pFirstToken.m_sFileName, m_pBaseParamCall.m_pFirstToken.m_nLine, m_pBaseParamCall.m_pFirstToken.m_nColumn);
#line 115 "../../../Source/Core/AST/TorDecl.nll"
					return;
				}
				AST pMember = pBaseClass.m_pFirstChild;
#line 119 "../../../Source/Core/AST/TorDecl.nll"
				while (pMember != null)
				{
#line 121 "../../../Source/Core/AST/TorDecl.nll"
					if (pMember.m_eType == AST.Type.AST_TOR_DECL)
					{
						TorDecl pTorDecl = (TorDecl)(pMember);
#line 124 "../../../Source/Core/AST/TorDecl.nll"
						if (pTorDecl.m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_CONSTRUCT)
						{
#line 126 "../../../Source/Core/AST/TorDecl.nll"
							if (pTorDecl.m_pParamDecl.ValidateParamCall(m_pBaseParamCall, pValidator, false))
							{
#line 128 "../../../Source/Core/AST/TorDecl.nll"
								break;
							}
						}
					}
#line 132 "../../../Source/Core/AST/TorDecl.nll"
					pMember = pMember.m_pNextSibling;
				}
#line 135 "../../../Source/Core/AST/TorDecl.nll"
				if (pMember == null)
				{
					InternalString sTemp = new InternalString("could not find a matching BASE constructor in ");
#line 138 "../../../Source/Core/AST/TorDecl.nll"
					sTemp.AppendString(pBaseClass.m_pNameToken.GetString());
#line 139 "../../../Source/Core/AST/TorDecl.nll"
					pValidator.AddError(sTemp.GetExternalString(), m_pBaseParamCall.m_pFirstToken.m_sFileName, m_pBaseParamCall.m_pFirstToken.m_nLine, m_pBaseParamCall.m_pFirstToken.m_nColumn);
#line 140 "../../../Source/Core/AST/TorDecl.nll"
					return;
				}
			}
		}

#line 145 "../../../Source/Core/AST/TorDecl.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			bool bGeneric = m_pParentClassDecl != null && m_pParentClassDecl.m_pGenericTypeDeclVector.GetSize() > 0;
#line 149 "../../../Source/Core/AST/TorDecl.nll"
			if (bGeneric && eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE)
#line 150 "../../../Source/Core/AST/TorDecl.nll"
				return;
#line 153 "../../../Source/Core/AST/TorDecl.nll"
			if (eLanguage == AST.Language.CS)
			{
#line 155 "../../../Source/Core/AST/TorDecl.nll"
				if (m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_DESTRUCT)
				{
#line 157 "../../../Source/Core/AST/TorDecl.nll"
					if (m_pParentClassDecl.m_bDisposable)
					{
#line 159 "../../../Source/Core/AST/TorDecl.nll"
						Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 160 "../../../Source/Core/AST/TorDecl.nll"
						pOutputBuilder.m_sOut.AppendChar('~');
#line 161 "../../../Source/Core/AST/TorDecl.nll"
						m_pParentClassDecl.m_pNameToken.Stringify(pOutputBuilder.m_sOut);
#line 162 "../../../Source/Core/AST/TorDecl.nll"
						pOutputBuilder.m_sOut.Append(m_sDisambiguate);
#line 163 "../../../Source/Core/AST/TorDecl.nll"
						m_pParamDecl.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 164 "../../../Source/Core/AST/TorDecl.nll"
						pOutputBuilder.m_sOut.AppendChar('\n');
#line 165 "../../../Source/Core/AST/TorDecl.nll"
						Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 166 "../../../Source/Core/AST/TorDecl.nll"
						pOutputBuilder.m_sOut.Append("{\n");
#line 167 "../../../Source/Core/AST/TorDecl.nll"
						Util.Pad(nDepth + 1, pOutputBuilder.m_sOut);
#line 168 "../../../Source/Core/AST/TorDecl.nll"
						pOutputBuilder.m_sOut.Append("Dispose();\n");
#line 169 "../../../Source/Core/AST/TorDecl.nll"
						Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 170 "../../../Source/Core/AST/TorDecl.nll"
						pOutputBuilder.m_sOut.Append("}\n");
#line 171 "../../../Source/Core/AST/TorDecl.nll"
						pOutputBuilder.m_sOut.AppendChar('\n');
#line 173 "../../../Source/Core/AST/TorDecl.nll"
						Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 174 "../../../Source/Core/AST/TorDecl.nll"
						pOutputBuilder.m_sOut.Append("public void Dispose()\n");
#line 175 "../../../Source/Core/AST/TorDecl.nll"
						Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 176 "../../../Source/Core/AST/TorDecl.nll"
						pOutputBuilder.m_sOut.Append("{\n");
#line 178 "../../../Source/Core/AST/TorDecl.nll"
						nDepth++;
#line 179 "../../../Source/Core/AST/TorDecl.nll"
						m_pScope.Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
#line 180 "../../../Source/Core/AST/TorDecl.nll"
						Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 181 "../../../Source/Core/AST/TorDecl.nll"
						pOutputBuilder.m_sOut.Append("System.GC.SuppressFinalize(this);\n");
#line 183 "../../../Source/Core/AST/TorDecl.nll"
						nDepth--;
#line 185 "../../../Source/Core/AST/TorDecl.nll"
						Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 186 "../../../Source/Core/AST/TorDecl.nll"
						pOutputBuilder.m_sOut.Append("}\n");
#line 187 "../../../Source/Core/AST/TorDecl.nll"
						pOutputBuilder.m_sOut.AppendChar('\n');
#line 189 "../../../Source/Core/AST/TorDecl.nll"
						return;
					}
				}
			}
#line 194 "../../../Source/Core/AST/TorDecl.nll"
			pOutputBuilder.UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 195 "../../../Source/Core/AST/TorDecl.nll"
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 197 "../../../Source/Core/AST/TorDecl.nll"
			if (!(eLanguage == AST.Language.CS && m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_DESTRUCT))
#line 198 "../../../Source/Core/AST/TorDecl.nll"
				if (!(eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE))
				{
#line 200 "../../../Source/Core/AST/TorDecl.nll"
					m_pAccessLevel.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 201 "../../../Source/Core/AST/TorDecl.nll"
					if (eLanguage == AST.Language.CPP)
#line 202 "../../../Source/Core/AST/TorDecl.nll"
						pOutputBuilder.m_sOut.AppendChar(':');
#line 203 "../../../Source/Core/AST/TorDecl.nll"
					pOutputBuilder.m_sOut.AppendChar(' ');
				}
#line 206 "../../../Source/Core/AST/TorDecl.nll"
			if (eLanguage == AST.Language.NLL_DEF)
			{
#line 208 "../../../Source/Core/AST/TorDecl.nll"
				if (m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_DESTRUCT)
#line 209 "../../../Source/Core/AST/TorDecl.nll"
					pOutputBuilder.m_sOut.Append("destruct");
				else
#line 211 "../../../Source/Core/AST/TorDecl.nll"
					pOutputBuilder.m_sOut.Append("construct");
			}
			else
			{
#line 215 "../../../Source/Core/AST/TorDecl.nll"
				if (eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE)
				{
#line 217 "../../../Source/Core/AST/TorDecl.nll"
					m_pParentClassDecl.m_pNameToken.Stringify(pOutputBuilder.m_sOut);
#line 218 "../../../Source/Core/AST/TorDecl.nll"
					pOutputBuilder.m_sOut.Append("::");
				}
#line 221 "../../../Source/Core/AST/TorDecl.nll"
				if (m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_DESTRUCT)
				{
#line 223 "../../../Source/Core/AST/TorDecl.nll"
					if (eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.HEADER)
#line 224 "../../../Source/Core/AST/TorDecl.nll"
						pOutputBuilder.m_sOut.Append("virtual ");
#line 226 "../../../Source/Core/AST/TorDecl.nll"
					pOutputBuilder.m_sOut.Append("~");
				}
#line 229 "../../../Source/Core/AST/TorDecl.nll"
				m_pParentClassDecl.m_pNameToken.Stringify(pOutputBuilder.m_sOut);
			}
#line 231 "../../../Source/Core/AST/TorDecl.nll"
			pOutputBuilder.m_sOut.Append(m_sDisambiguate);
#line 232 "../../../Source/Core/AST/TorDecl.nll"
			m_pParamDecl.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 236 "../../../Source/Core/AST/TorDecl.nll"
			if ((!bGeneric && eOutputFile == AST.OutputFile.HEADER) || eLanguage == AST.Language.NLL_DEF)
			{
#line 238 "../../../Source/Core/AST/TorDecl.nll"
				pOutputBuilder.m_sOut.Append(";\n");
#line 239 "../../../Source/Core/AST/TorDecl.nll"
				return;
			}
#line 242 "../../../Source/Core/AST/TorDecl.nll"
			if (m_pScope == null)
			{
#line 244 "../../../Source/Core/AST/TorDecl.nll"
				pOutputBuilder.m_sOut.AppendString(";\n");
			}
			else
			{
#line 248 "../../../Source/Core/AST/TorDecl.nll"
				if (m_pBaseParamCall != null)
				{
#line 250 "../../../Source/Core/AST/TorDecl.nll"
					pOutputBuilder.m_sOut.Append(" : ");
#line 251 "../../../Source/Core/AST/TorDecl.nll"
					if (eLanguage == AST.Language.CPP)
#line 252 "../../../Source/Core/AST/TorDecl.nll"
						m_pParentClassDecl.m_pBaseTypeRef.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
					else
#line 254 "../../../Source/Core/AST/TorDecl.nll"
						pOutputBuilder.m_sOut.Append("base");
#line 255 "../../../Source/Core/AST/TorDecl.nll"
					m_pBaseParamCall.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
				}
#line 257 "../../../Source/Core/AST/TorDecl.nll"
				pOutputBuilder.m_sOut.AppendChar('\n');
#line 258 "../../../Source/Core/AST/TorDecl.nll"
				m_pScope.Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
#line 259 "../../../Source/Core/AST/TorDecl.nll"
				pOutputBuilder.m_sOut.AppendChar('\n');
			}
		}

#line 4 "../../../Source/Core/AST/TorDecl.nll"
		public TorDecl()
		{
		}

	}
}

