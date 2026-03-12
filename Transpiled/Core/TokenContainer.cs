#line 1 "../../../Source/Core/TokenContainer.nll"
namespace NumbatLogic
{
	class TokenContainer
	{
		public OwnedVector<Token> m_pTokenVector;
		protected InternalString m_sTemp;
#line 8 "../../../Source/Core/TokenContainer.nll"
		public TokenContainer()
		{
			m_pTokenVector = new OwnedVector<Token>();
			m_sTemp = new InternalString("");
		}

		public char ReadChar(ParseDatum pParseDatum, bool bPeak)
		{
			if (pParseDatum.m_sInput.GetLength() > 0)
			{
				char nChar = pParseDatum.m_sInput.GetChar(0);
				if (!bPeak)
					pParseDatum.m_sInput.SubStr(1, pParseDatum.m_sInput.GetLength() - 1);
				return nChar;
			}
			return '\0';
		}

		public bool Tokenize(string sInput, InternalString sFileName, OwnedVector<InternalString> sDefineVector)
		{
			ParseDatum pParseDatum = new ParseDatum();
			pParseDatum.m_sInput.Set(sInput);
			pParseDatum.m_sFileName = sFileName;
#line 32 "../../../Source/Core/TokenContainer.nll"
			int nIfdefDepth = 0;
#line 34 "../../../Source/Core/TokenContainer.nll"
			while (true)
			{
				char nChar = ReadChar(pParseDatum, false);
				if (nChar == 0 || nChar < 0)
				{
					ProcessCurrentRead(pParseDatum);
					break;
				}
#line 44 "../../../Source/Core/TokenContainer.nll"
				if (nChar == '#')
				{
					if (pParseDatum.m_sInput.StartsWith("ifdef "))
					{
						pParseDatum.m_sInput.SubStr(6, pParseDatum.m_sInput.GetLength() - 6);
#line 50 "../../../Source/Core/TokenContainer.nll"
						InternalString sName = new InternalString("");
						while (true)
						{
							nChar = ReadChar(pParseDatum, false);
							if (nChar == '\0')
							{
								Console.Log("End of #ifdef name not found");
								Assert.Plz(false);
							}
							if (nChar == ' ' || nChar == '\t' || nChar == '\n')
								break;
							sName.AppendChar(nChar);
						}
#line 64 "../../../Source/Core/TokenContainer.nll"
						pParseDatum.m_nLine = pParseDatum.m_nLine + 1;
						pParseDatum.m_nColumn = 0;
#line 67 "../../../Source/Core/TokenContainer.nll"
						bool bFound = false;
						string sxName = sName.GetExternalString();
						for (int i = 0; i < sDefineVector.GetSize(); i++)
						{
							if (sDefineVector.Get(i).IsEqual(sxName))
							{
								bFound = true;
								break;
							}
						}
#line 80 "../../../Source/Core/TokenContainer.nll"
						if (bFound)
						{
							nIfdefDepth++;
							continue;
						}
#line 87 "../../../Source/Core/TokenContainer.nll"
						while (true)
						{
							nChar = ReadChar(pParseDatum, false);
							if (nChar == '\0')
							{
								Console.Log("End of #ifdef not found");
								Assert.Plz(false);
							}
#line 96 "../../../Source/Core/TokenContainer.nll"
							if (nChar == '#')
							{
								if (pParseDatum.m_sInput.StartsWith("endif"))
								{
									pParseDatum.m_sInput.SubStr(5, pParseDatum.m_sInput.GetLength() - 5);
									break;
								}
							}
#line 105 "../../../Source/Core/TokenContainer.nll"
							if (nChar == '\n')
							{
								pParseDatum.m_nLine = pParseDatum.m_nLine + 1;
								pParseDatum.m_nColumn = 0;
							}
						}
						continue;
					}
#line 114 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sInput.StartsWith("endif"))
					{
						if (nIfdefDepth <= 0)
						{
							Console.Log("#endif with no #ifdef???");
							Console.Log(sFileName.GetExternalString());
							Assert.Plz(false);
						}
#line 123 "../../../Source/Core/TokenContainer.nll"
						nIfdefDepth--;
						pParseDatum.m_sInput.SubStr(5, pParseDatum.m_sInput.GetLength() - 5);
						continue;
					}
				}
#line 130 "../../../Source/Core/TokenContainer.nll"
				if (nChar == '/')
				{
					char nNextChar = ReadChar(pParseDatum, true);
					{
#line 135 "../../../Source/Core/TokenContainer.nll"
						if (nNextChar == '/')
						{
							ProcessCurrentRead(pParseDatum);
#line 139 "../../../Source/Core/TokenContainer.nll"
							while (true)
							{
								char nNextNextChar = ReadChar(pParseDatum, false);
								if (nNextNextChar == 0 || nNextNextChar < 0)
									break;
#line 145 "../../../Source/Core/TokenContainer.nll"
								if (nNextNextChar == '\n')
									break;
							}
#line 149 "../../../Source/Core/TokenContainer.nll"
							pParseDatum.m_nLine = pParseDatum.m_nLine + 1;
#line 152 "../../../Source/Core/TokenContainer.nll"
							continue;
						}
						else
#line 154 "../../../Source/Core/TokenContainer.nll"
							if (nNextChar == '*')
							{
								ProcessCurrentRead(pParseDatum);
#line 158 "../../../Source/Core/TokenContainer.nll"
								int nLastChar = 0;
								while (true)
								{
									char nNextNextChar = ReadChar(pParseDatum, false);
									if (nNextNextChar == 0 || nNextNextChar < 0)
										break;
#line 165 "../../../Source/Core/TokenContainer.nll"
									pParseDatum.m_nColumn = pParseDatum.m_nColumn + 1;
									if (nNextNextChar == '\n')
									{
										pParseDatum.m_nLine = pParseDatum.m_nLine + 1;
										pParseDatum.m_nColumn = 0;
									}
#line 172 "../../../Source/Core/TokenContainer.nll"
									if (nNextNextChar == '/' && nLastChar == '*')
										break;
#line 175 "../../../Source/Core/TokenContainer.nll"
									nLastChar = nNextNextChar;
								}
								continue;
							}
					}
				}
#line 182 "../../../Source/Core/TokenContainer.nll"
				switch (nChar)
				{
					case ' ':
					case '!':
					case '&':
					case '(':
					case ')':
					case '*':
					case '+':
					case ',':
					case '-':
					case '.':
					case '/':
					case ':':
					case ';':
					case '<':
					case '=':
					case '>':
					case '[':
					case '\n':
					case '\r':
					case '\t':
					case ']':
					case '^':
					case '{':
					case '|':
					case '}':
					case '~':
					{
						int nLength = pParseDatum.m_sCurrentRead.GetLength();
						if (nChar == '.' && nLength > 0)
						{
							int i = 0;
							for (int hax = 0; i < nLength; i = i + 1)
							{
								hax++;
								int nTestChar = pParseDatum.m_sCurrentRead.GetChar(i);
								if (nTestChar < '0' || nTestChar > '9')
									break;
							}
#line 223 "../../../Source/Core/TokenContainer.nll"
							if (i == nLength)
								break;
						}
#line 227 "../../../Source/Core/TokenContainer.nll"
						ProcessCurrentRead(pParseDatum);
						pParseDatum.m_sCurrentRead.AppendChar(nChar);
#line 230 "../../../Source/Core/TokenContainer.nll"
						pParseDatum.m_nColumn = pParseDatum.m_nColumn + 1;
						if (nChar == '\n')
						{
							pParseDatum.m_nLine = pParseDatum.m_nLine + 1;
							pParseDatum.m_nColumn = 0;
						}
#line 237 "../../../Source/Core/TokenContainer.nll"
						ProcessCurrentRead(pParseDatum);
						continue;
					}

					case '"':
					case '\'':
					{
#line 243 "../../../Source/Core/TokenContainer.nll"
						ProcessCurrentRead(pParseDatum);
						pParseDatum.m_sCurrentRead.AppendChar(nChar);
#line 246 "../../../Source/Core/TokenContainer.nll"
						pParseDatum.m_nColumn = pParseDatum.m_nColumn + 1;
						ParseQuoted(pParseDatum, nChar);
						continue;
					}

				}
				pParseDatum.m_sCurrentRead.AppendChar(nChar);
				pParseDatum.m_nColumn = pParseDatum.m_nColumn + 1;
			}
#line 257 "../../../Source/Core/TokenContainer.nll"
			return true;
		}

		protected void ProcessCurrentRead(ParseDatum pParseDatum)
		{
			switch (pParseDatum.m_sCurrentRead.GetLength())
			{
				case 0:
				{
					return;
				}

				case 1:
				{
#line 270 "../../../Source/Core/TokenContainer.nll"
					Token.Type eType = Token.Type.TOKEN_IDENTIFIER;
					switch (pParseDatum.m_sCurrentRead.GetChar(0))
					{
						case ' ':
						{
#line 273 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_SPACE;
#line 273 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '!':
						{
#line 274 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_BANG;
#line 274 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '%':
						{
#line 275 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_MODULUS;
#line 275 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '&':
						{
#line 276 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_BITWISE_AND;
#line 276 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '(':
						{
#line 277 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_PARENTHESIS_LEFT;
#line 277 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case ')':
						{
#line 278 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_PARENTHESIS_RIGHT;
#line 278 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '*':
						{
#line 279 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_STAR;
#line 279 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '+':
						{
#line 280 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_PLUS;
#line 280 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case ',':
						{
#line 281 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_COMMA;
#line 281 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '-':
						{
#line 282 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_MINUS;
#line 282 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '.':
						{
#line 283 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_DOT;
#line 283 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '/':
						{
#line 284 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_DIVIDE;
#line 284 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case ':':
						{
#line 285 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_COLON;
#line 285 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case ';':
						{
#line 286 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_SEMICOLON;
#line 286 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '<':
						{
#line 287 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_ANGLE_BRACKET_LEFT;
#line 287 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '=':
						{
#line 288 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_EQUALS;
#line 288 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '>':
						{
#line 289 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_ANGLE_BRACKET_RIGHT;
#line 289 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '?':
						{
#line 290 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_QUESTION_MARK;
#line 290 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '[':
						{
#line 291 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_SQUARE_BRACKET_LEFT;
#line 291 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '\n':
						{
#line 292 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_NEW_LINE;
#line 292 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '\r':
						{
#line 293 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_CARRIGE_RETURN;
#line 293 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '\t':
						{
#line 294 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_TAB;
#line 294 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case ']':
						{
#line 295 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_SQUARE_BRACKET_RIGHT;
#line 295 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '^':
						{
#line 296 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_CARET;
#line 296 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '{':
						{
#line 297 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_CURLY_BRACE_LEFT;
#line 297 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '|':
						{
#line 298 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_BITWISE_OR;
#line 298 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '}':
						{
#line 299 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_CURLY_BRACE_RIGHT;
#line 299 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '~':
						{
#line 300 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_TILDE;
#line 300 "../../../Source/Core/TokenContainer.nll"
							break;
						}

					}
#line 302 "../../../Source/Core/TokenContainer.nll"
					if (eType != Token.Type.TOKEN_IDENTIFIER)
					{
						if (m_pTokenVector.GetSize() > 0)
						{
							Token pPreviousToken = m_pTokenVector.Get(m_pTokenVector.GetSize() - 1);
#line 308 "../../../Source/Core/TokenContainer.nll"
							if (pPreviousToken.m_eType == Token.Type.TOKEN_COLON && eType == Token.Type.TOKEN_COLON)
							{
								pPreviousToken.m_eType = Token.Type.TOKEN_DOUBLE_COLON;
								pParseDatum.ClearCurrentRead();
								return;
							}
#line 315 "../../../Source/Core/TokenContainer.nll"
							if (pPreviousToken.m_eType == Token.Type.TOKEN_PLUS && eType == Token.Type.TOKEN_PLUS)
							{
								pPreviousToken.m_eType = Token.Type.TOKEN_PLUS_PLUS;
								pParseDatum.ClearCurrentRead();
								return;
							}
#line 322 "../../../Source/Core/TokenContainer.nll"
							if (pPreviousToken.m_eType == Token.Type.TOKEN_MINUS && eType == Token.Type.TOKEN_MINUS)
							{
								pPreviousToken.m_eType = Token.Type.TOKEN_MINUS_MINUS;
								pParseDatum.ClearCurrentRead();
								return;
							}
#line 329 "../../../Source/Core/TokenContainer.nll"
							if (pPreviousToken.m_eType == Token.Type.TOKEN_STAR && eType == Token.Type.TOKEN_STAR)
							{
								pPreviousToken.m_eType = Token.Type.TOKEN_STAR_DOUBLE;
								pParseDatum.ClearCurrentRead();
								return;
							}
						}
#line 337 "../../../Source/Core/TokenContainer.nll"
						PushToken(eType, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					break;
				}

				case 2:
				{
#line 344 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("if"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_IF, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					break;
				}

				case 3:
				{
#line 353 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("for"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_FOR, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("int"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_INT, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("new"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_NEW, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("own"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_OWN, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("ref"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_REF, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					break;
				}

				case 4:
				{
#line 382 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("bool"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_BOOL, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("base"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_BASE, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("case"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_CASE, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("cast"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_CAST, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("enum"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_ENUM, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("else"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_ELSE, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("Int8"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_INT8, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("null"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_NULL, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("this"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_THIS, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("true"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_TRUE, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("uint"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_UINT, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("void"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_VOID, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					break;
				}

				case 5:
				{
#line 446 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("break"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_BREAK, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("class"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_CLASS, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("const"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_CONST, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("false"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_FALSE, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("float"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_FLOAT, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("Int16"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_INT16, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("Int32"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_INT32, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("Uint8"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_UINT8, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("using"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_USING, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("while"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_WHILE, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					break;
				}

				case 6:
				{
#line 500 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("delete"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_DELETE, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("disown"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_DISOWN, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("double"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_DOUBLE, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("public"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_PUBLIC, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("return"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_RETURN, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("static"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_STATIC, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("string"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_STRING, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("switch"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_SWITCH, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("tthash"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_TTHASH, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("Uint16"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_UINT16, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("Uint32"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_UINT32, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("Uint64"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_UINT64, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
#line 561 "../../../Source/Core/TokenContainer.nll"
					break;
				}

				case 7:
				{
#line 565 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("default"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_DEFAULT, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("private"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_PRIVATE, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("UniChar"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_UNICHAR, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("virtual"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_VIRTUAL, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("voidptr"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_VOIDPTR, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					break;
				}

				case 8:
				{
#line 594 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("continue"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_CONTINUE, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("delegate"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_DELEGATE, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("destruct"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_DESTRUCT, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("override"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_OVERRIDE, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					break;
				}

				case 9:
				{
#line 618 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("construct"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_CONSTRUCT, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
#line 624 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("namespace"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_NAMESPACE, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					break;
				}

				case 10:
				{
#line 633 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("disposable"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_DISPOSABLE, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					break;
				}

			}
			{
#line 644 "../../../Source/Core/TokenContainer.nll"
				int i = 0;
				bool bFirstZero = false;
				bool bHex = false;
				int nLength = pParseDatum.m_sCurrentRead.GetLength();
				for (int hax = 0; i < nLength; i = i + 1)
				{
					hax++;
					int nChar = pParseDatum.m_sCurrentRead.GetChar(i);
#line 653 "../../../Source/Core/TokenContainer.nll"
					if (i == 0 && nChar == '0')
					{
						bFirstZero = true;
						continue;
					}
#line 659 "../../../Source/Core/TokenContainer.nll"
					if (i == 1 && bFirstZero && nChar == 'x')
					{
						bHex = true;
						continue;
					}
#line 665 "../../../Source/Core/TokenContainer.nll"
					if (bHex)
					{
						if (nChar >= '0' && nChar <= '9' || nChar >= 'A' && nChar <= 'F' || nChar >= 'a' && nChar <= 'f')
						{
							continue;
						}
					}
					else
					{
						if (nChar >= '0' && nChar <= '9' || nChar == '.')
						{
							continue;
						}
#line 679 "../../../Source/Core/TokenContainer.nll"
						if (i == nLength - 1 && nChar == 'f')
							continue;
					}
#line 683 "../../../Source/Core/TokenContainer.nll"
					break;
				}
#line 686 "../../../Source/Core/TokenContainer.nll"
				if (i == nLength)
				{
					PushToken(Token.Type.TOKEN_NUMBER, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, true);
					return;
				}
			}
#line 695 "../../../Source/Core/TokenContainer.nll"
			PushToken(Token.Type.TOKEN_IDENTIFIER, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, true);
		}

		protected void PushToken(Token.Type eType, int nLine, int nColumn, ParseDatum pParseDatum, bool bCopyString)
		{
			Token pToken = new Token();
			pToken.m_eType = eType;
			pToken.m_sFileName = pParseDatum.m_sFileName;
			pToken.m_nLine = nLine;
			pToken.m_nColumn = nColumn;
#line 706 "../../../Source/Core/TokenContainer.nll"
			if (bCopyString)
				pToken.m_sValue = new InternalString(pParseDatum.m_sCurrentRead.GetExternalString());
#line 709 "../../../Source/Core/TokenContainer.nll"
			pParseDatum.ClearCurrentRead();
			NumbatLogic.Token __3820032206 = pToken;
			pToken = null;
#line 711 "../../../Source/Core/TokenContainer.nll"
			m_pTokenVector.PushBack(__3820032206);
		}

		protected void ParseQuoted(ParseDatum pParseDatum, char nQuoteChar)
		{
			bool bEscaping = false;
#line 724 "../../../Source/Core/TokenContainer.nll"
			while (true)
			{
				char nChar = ReadChar(pParseDatum, false);
				if (nChar == '\0')
				{
#line 730 "../../../Source/Core/TokenContainer.nll"
					Token.Type eType = Token.Type.TOKEN_CHAR_UNTERMINATED;
					if (nQuoteChar == '"')
						eType = Token.Type.TOKEN_STRING_UNTERMINATED;
					PushToken(eType, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, true);
					return;
				}
#line 737 "../../../Source/Core/TokenContainer.nll"
				pParseDatum.m_sCurrentRead.AppendChar(nChar);
				pParseDatum.m_nColumn = pParseDatum.m_nColumn + 1;
#line 740 "../../../Source/Core/TokenContainer.nll"
				if (nChar == nQuoteChar && !bEscaping)
				{
					Token.Type eType = Token.Type.TOKEN_CHAR;
					if (nQuoteChar == '"')
						eType = Token.Type.TOKEN_STRING;
					PushToken(eType, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, true);
					return;
				}
#line 749 "../../../Source/Core/TokenContainer.nll"
				if (bEscaping)
					bEscaping = false;
				else
#line 751 "../../../Source/Core/TokenContainer.nll"
					if (nChar == '\\')
					{
						bEscaping = true;
					}
			}
		}

#line 762 "../../../Source/Core/TokenContainer.nll"
		public void Stringify(InternalString sOut)
		{
			for (int i = 0; i < m_pTokenVector.GetSize(); i++)
			{
				Token pToken = m_pTokenVector.Get(i);
				sOut.Append(pToken.GetString());
			}
		}

		public void StripWhitespace()
		{
			int nIn = 0;
			while (nIn < m_pTokenVector.GetSize())
			{
				Token pToken = m_pTokenVector.Get(nIn);
				if (pToken.m_eType == Token.Type.TOKEN_CARRIGE_RETURN || pToken.m_eType == Token.Type.TOKEN_NEW_LINE || pToken.m_eType == Token.Type.TOKEN_SPACE || pToken.m_eType == Token.Type.TOKEN_TAB)
				{
#line 782 "../../../Source/Core/TokenContainer.nll"
					m_pTokenVector.Erase(nIn);
					continue;
				}
#line 786 "../../../Source/Core/TokenContainer.nll"
				nIn++;
			}
		}

		public Token Peek(OffsetDatum pOffsetDatum)
		{
			if (pOffsetDatum.m_nOffset < m_pTokenVector.GetSize())
				return m_pTokenVector.Get(pOffsetDatum.m_nOffset);
			return null;
		}

		public Token PeekExpect(OffsetDatum pOffsetDatum, Token.Type eType)
		{
			Token pToken = Peek(pOffsetDatum);
			if (pToken == null || pToken.m_eType != eType)
				return null;
			return pToken;
		}

		public string StringifyOffset(OffsetDatum pOffsetDatum)
		{
			Token pToken = null;
			if (pOffsetDatum.m_nOffset < m_pTokenVector.GetSize())
				pToken = m_pTokenVector.Get(pOffsetDatum.m_nOffset);
			if (pToken == null && m_pTokenVector.GetSize() > 0)
				pToken = m_pTokenVector.Get(m_pTokenVector.GetSize() - 1);
#line 813 "../../../Source/Core/TokenContainer.nll"
			if (pToken == null)
				return "unbeknownst:?:?";
#line 816 "../../../Source/Core/TokenContainer.nll"
			m_sTemp.Set(pToken.m_sFileName.GetExternalString());
			m_sTemp.Append(":");
			m_sTemp.AppendInt(pToken.m_nLine);
			m_sTemp.Append(":");
			m_sTemp.AppendInt(pToken.m_nColumn);
			m_sTemp.Append(" ");
			m_sTemp.Append(pToken.GetString());
			return m_sTemp.GetExternalString();
		}

#line 3 "../../../Source/Core/TokenContainer.nll"
		~TokenContainer()
		{
		}

	}
}

