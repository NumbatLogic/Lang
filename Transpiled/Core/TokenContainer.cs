#line 1 "../../../Source/Core/TokenContainer.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/TokenContainer.nll"
	class TokenContainer
	{
#line 6 "../../../Source/Core/TokenContainer.nll"
		public OwnedVector<Token> m_pTokenVector;
#line 7 "../../../Source/Core/TokenContainer.nll"
		protected InternalString m_sTemp;
#line 9 "../../../Source/Core/TokenContainer.nll"
		public TokenContainer()
		{
#line 11 "../../../Source/Core/TokenContainer.nll"
			m_pTokenVector = new OwnedVector<Token>();
#line 12 "../../../Source/Core/TokenContainer.nll"
			m_sTemp = new InternalString("");
		}

#line 15 "../../../Source/Core/TokenContainer.nll"
		public char ReadChar(ParseDatum pParseDatum, bool bPeak)
		{
#line 17 "../../../Source/Core/TokenContainer.nll"
			if (pParseDatum.m_sInput.GetLength() > 0)
			{
				char nChar = pParseDatum.m_sInput.GetChar(0);
#line 20 "../../../Source/Core/TokenContainer.nll"
				if (!bPeak)
#line 21 "../../../Source/Core/TokenContainer.nll"
					pParseDatum.m_sInput.SubStr(1, pParseDatum.m_sInput.GetLength() - 1);
#line 22 "../../../Source/Core/TokenContainer.nll"
				return nChar;
			}
#line 24 "../../../Source/Core/TokenContainer.nll"
			return '\0';
		}

#line 27 "../../../Source/Core/TokenContainer.nll"
		public bool Tokenize(string sInput, InternalString sFileName, OwnedVector<InternalString> sDefineVector)
		{
			ParseDatum pParseDatum = new ParseDatum();
#line 30 "../../../Source/Core/TokenContainer.nll"
			pParseDatum.m_sInput.Set(sInput);
#line 31 "../../../Source/Core/TokenContainer.nll"
			pParseDatum.m_sFileName = sFileName;
			int nIfdefDepth = 0;
#line 35 "../../../Source/Core/TokenContainer.nll"
			while (true)
			{
				char nChar = ReadChar(pParseDatum, false);
#line 38 "../../../Source/Core/TokenContainer.nll"
				if (nChar == 0 || nChar < 0)
				{
#line 40 "../../../Source/Core/TokenContainer.nll"
					ProcessCurrentRead(pParseDatum);
#line 41 "../../../Source/Core/TokenContainer.nll"
					break;
				}
#line 45 "../../../Source/Core/TokenContainer.nll"
				if (nChar == '#')
				{
#line 47 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sInput.StartsWith("ifdef "))
					{
#line 49 "../../../Source/Core/TokenContainer.nll"
						pParseDatum.m_sInput.SubStr(6, pParseDatum.m_sInput.GetLength() - 6);
						InternalString sName = new InternalString("");
#line 52 "../../../Source/Core/TokenContainer.nll"
						while (true)
						{
#line 54 "../../../Source/Core/TokenContainer.nll"
							nChar = ReadChar(pParseDatum, false);
#line 55 "../../../Source/Core/TokenContainer.nll"
							if (nChar == '\0')
							{
#line 57 "../../../Source/Core/TokenContainer.nll"
								Console.Log("End of #ifdef name not found");
#line 58 "../../../Source/Core/TokenContainer.nll"
								Assert.Plz(false);
							}
#line 60 "../../../Source/Core/TokenContainer.nll"
							if (nChar == ' ' || nChar == '\t' || nChar == '\n')
#line 61 "../../../Source/Core/TokenContainer.nll"
								break;
#line 62 "../../../Source/Core/TokenContainer.nll"
							sName.AppendChar(nChar);
						}
#line 65 "../../../Source/Core/TokenContainer.nll"
						pParseDatum.m_nLine = pParseDatum.m_nLine + 1;
#line 66 "../../../Source/Core/TokenContainer.nll"
						pParseDatum.m_nColumn = 0;
						bool bFound = false;
						string sxName = sName.GetExternalString();
#line 70 "../../../Source/Core/TokenContainer.nll"
						for (int i = 0; i < sDefineVector.GetSize(); i++)
						{
#line 72 "../../../Source/Core/TokenContainer.nll"
							if (sDefineVector.Get(i).IsEqual(sxName))
							{
#line 74 "../../../Source/Core/TokenContainer.nll"
								bFound = true;
#line 75 "../../../Source/Core/TokenContainer.nll"
								break;
							}
						}
#line 81 "../../../Source/Core/TokenContainer.nll"
						if (bFound)
						{
#line 83 "../../../Source/Core/TokenContainer.nll"
							nIfdefDepth++;
#line 84 "../../../Source/Core/TokenContainer.nll"
							continue;
						}
#line 88 "../../../Source/Core/TokenContainer.nll"
						while (true)
						{
#line 90 "../../../Source/Core/TokenContainer.nll"
							nChar = ReadChar(pParseDatum, false);
#line 91 "../../../Source/Core/TokenContainer.nll"
							if (nChar == '\0')
							{
#line 93 "../../../Source/Core/TokenContainer.nll"
								Console.Log("End of #ifdef not found");
#line 94 "../../../Source/Core/TokenContainer.nll"
								Assert.Plz(false);
							}
#line 97 "../../../Source/Core/TokenContainer.nll"
							if (nChar == '#')
							{
#line 99 "../../../Source/Core/TokenContainer.nll"
								if (pParseDatum.m_sInput.StartsWith("endif"))
								{
#line 101 "../../../Source/Core/TokenContainer.nll"
									pParseDatum.m_sInput.SubStr(5, pParseDatum.m_sInput.GetLength() - 5);
#line 102 "../../../Source/Core/TokenContainer.nll"
									break;
								}
							}
#line 106 "../../../Source/Core/TokenContainer.nll"
							if (nChar == '\n')
							{
#line 108 "../../../Source/Core/TokenContainer.nll"
								pParseDatum.m_nLine = pParseDatum.m_nLine + 1;
#line 109 "../../../Source/Core/TokenContainer.nll"
								pParseDatum.m_nColumn = 0;
							}
						}
#line 112 "../../../Source/Core/TokenContainer.nll"
						continue;
					}
#line 115 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sInput.StartsWith("endif"))
					{
#line 117 "../../../Source/Core/TokenContainer.nll"
						if (nIfdefDepth <= 0)
						{
#line 119 "../../../Source/Core/TokenContainer.nll"
							Console.Log("#endif with no #ifdef???");
#line 120 "../../../Source/Core/TokenContainer.nll"
							Console.Log(sFileName.GetExternalString());
#line 121 "../../../Source/Core/TokenContainer.nll"
							Assert.Plz(false);
						}
#line 124 "../../../Source/Core/TokenContainer.nll"
						nIfdefDepth--;
#line 125 "../../../Source/Core/TokenContainer.nll"
						pParseDatum.m_sInput.SubStr(5, pParseDatum.m_sInput.GetLength() - 5);
#line 126 "../../../Source/Core/TokenContainer.nll"
						continue;
					}
				}
#line 131 "../../../Source/Core/TokenContainer.nll"
				if (nChar == '/')
				{
					char nNextChar = ReadChar(pParseDatum, true);
					{
#line 136 "../../../Source/Core/TokenContainer.nll"
						if (nNextChar == '/')
						{
#line 138 "../../../Source/Core/TokenContainer.nll"
							ProcessCurrentRead(pParseDatum);
#line 140 "../../../Source/Core/TokenContainer.nll"
							while (true)
							{
								char nNextNextChar = ReadChar(pParseDatum, false);
#line 143 "../../../Source/Core/TokenContainer.nll"
								if (nNextNextChar == 0 || nNextNextChar < 0)
#line 144 "../../../Source/Core/TokenContainer.nll"
									break;
#line 146 "../../../Source/Core/TokenContainer.nll"
								if (nNextNextChar == '\n')
#line 147 "../../../Source/Core/TokenContainer.nll"
									break;
							}
#line 150 "../../../Source/Core/TokenContainer.nll"
							pParseDatum.m_nLine = pParseDatum.m_nLine + 1;
#line 153 "../../../Source/Core/TokenContainer.nll"
							continue;
						}
						else
#line 155 "../../../Source/Core/TokenContainer.nll"
							if (nNextChar == '*')
							{
#line 157 "../../../Source/Core/TokenContainer.nll"
								ProcessCurrentRead(pParseDatum);
								int nLastChar = 0;
#line 160 "../../../Source/Core/TokenContainer.nll"
								while (true)
								{
									char nNextNextChar = ReadChar(pParseDatum, false);
#line 163 "../../../Source/Core/TokenContainer.nll"
									if (nNextNextChar == 0 || nNextNextChar < 0)
#line 164 "../../../Source/Core/TokenContainer.nll"
										break;
#line 166 "../../../Source/Core/TokenContainer.nll"
									pParseDatum.m_nColumn = pParseDatum.m_nColumn + 1;
#line 167 "../../../Source/Core/TokenContainer.nll"
									if (nNextNextChar == '\n')
									{
#line 169 "../../../Source/Core/TokenContainer.nll"
										pParseDatum.m_nLine = pParseDatum.m_nLine + 1;
#line 170 "../../../Source/Core/TokenContainer.nll"
										pParseDatum.m_nColumn = 0;
									}
#line 173 "../../../Source/Core/TokenContainer.nll"
									if (nNextNextChar == '/' && nLastChar == '*')
#line 174 "../../../Source/Core/TokenContainer.nll"
										break;
#line 176 "../../../Source/Core/TokenContainer.nll"
									nLastChar = nNextNextChar;
								}
#line 178 "../../../Source/Core/TokenContainer.nll"
								continue;
							}
					}
				}
#line 183 "../../../Source/Core/TokenContainer.nll"
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
#line 213 "../../../Source/Core/TokenContainer.nll"
						if (nChar == '.' && nLength > 0)
						{
							int i = 0;
#line 216 "../../../Source/Core/TokenContainer.nll"
							for (int hax = 0; i < nLength; i = i + 1)
							{
#line 218 "../../../Source/Core/TokenContainer.nll"
								hax++;
								int nTestChar = pParseDatum.m_sCurrentRead.GetChar(i);
#line 220 "../../../Source/Core/TokenContainer.nll"
								if (nTestChar < '0' || nTestChar > '9')
#line 221 "../../../Source/Core/TokenContainer.nll"
									break;
							}
#line 224 "../../../Source/Core/TokenContainer.nll"
							if (i == nLength)
#line 225 "../../../Source/Core/TokenContainer.nll"
								break;
						}
#line 228 "../../../Source/Core/TokenContainer.nll"
						ProcessCurrentRead(pParseDatum);
#line 229 "../../../Source/Core/TokenContainer.nll"
						pParseDatum.m_sCurrentRead.AppendChar(nChar);
#line 231 "../../../Source/Core/TokenContainer.nll"
						pParseDatum.m_nColumn = pParseDatum.m_nColumn + 1;
#line 232 "../../../Source/Core/TokenContainer.nll"
						if (nChar == '\n')
						{
#line 234 "../../../Source/Core/TokenContainer.nll"
							pParseDatum.m_nLine = pParseDatum.m_nLine + 1;
#line 235 "../../../Source/Core/TokenContainer.nll"
							pParseDatum.m_nColumn = 0;
						}
#line 238 "../../../Source/Core/TokenContainer.nll"
						ProcessCurrentRead(pParseDatum);
#line 239 "../../../Source/Core/TokenContainer.nll"
						continue;
					}

					case '"':
					case '\'':
					{
#line 244 "../../../Source/Core/TokenContainer.nll"
						ProcessCurrentRead(pParseDatum);
#line 245 "../../../Source/Core/TokenContainer.nll"
						pParseDatum.m_sCurrentRead.AppendChar(nChar);
#line 247 "../../../Source/Core/TokenContainer.nll"
						pParseDatum.m_nColumn = pParseDatum.m_nColumn + 1;
#line 248 "../../../Source/Core/TokenContainer.nll"
						ParseQuoted(pParseDatum, nChar);
#line 249 "../../../Source/Core/TokenContainer.nll"
						continue;
					}

				}
#line 253 "../../../Source/Core/TokenContainer.nll"
				pParseDatum.m_sCurrentRead.AppendChar(nChar);
#line 254 "../../../Source/Core/TokenContainer.nll"
				pParseDatum.m_nColumn = pParseDatum.m_nColumn + 1;
			}
#line 258 "../../../Source/Core/TokenContainer.nll"
			return true;
		}

#line 261 "../../../Source/Core/TokenContainer.nll"
		protected void ProcessCurrentRead(ParseDatum pParseDatum)
		{
#line 263 "../../../Source/Core/TokenContainer.nll"
			switch (pParseDatum.m_sCurrentRead.GetLength())
			{
				case 0:
				{
#line 267 "../../../Source/Core/TokenContainer.nll"
					return;
				}

				case 1:
				{
					Token.Type eType = Token.Type.TOKEN_IDENTIFIER;
#line 272 "../../../Source/Core/TokenContainer.nll"
					switch (pParseDatum.m_sCurrentRead.GetChar(0))
					{
						case ' ':
						{
#line 274 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_SPACE;
#line 274 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '!':
						{
#line 275 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_BANG;
#line 275 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '%':
						{
#line 276 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_MODULUS;
#line 276 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '&':
						{
#line 277 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_BITWISE_AND;
#line 277 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '(':
						{
#line 278 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_PARENTHESIS_LEFT;
#line 278 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case ')':
						{
#line 279 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_PARENTHESIS_RIGHT;
#line 279 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '*':
						{
#line 280 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_STAR;
#line 280 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '+':
						{
#line 281 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_PLUS;
#line 281 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case ',':
						{
#line 282 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_COMMA;
#line 282 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '-':
						{
#line 283 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_MINUS;
#line 283 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '.':
						{
#line 284 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_DOT;
#line 284 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '/':
						{
#line 285 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_DIVIDE;
#line 285 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case ':':
						{
#line 286 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_COLON;
#line 286 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case ';':
						{
#line 287 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_SEMICOLON;
#line 287 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '<':
						{
#line 288 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_ANGLE_BRACKET_LEFT;
#line 288 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '=':
						{
#line 289 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_EQUALS;
#line 289 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '>':
						{
#line 290 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_ANGLE_BRACKET_RIGHT;
#line 290 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '?':
						{
#line 291 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_QUESTION_MARK;
#line 291 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '[':
						{
#line 292 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_SQUARE_BRACKET_LEFT;
#line 292 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '\n':
						{
#line 293 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_NEW_LINE;
#line 293 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '\r':
						{
#line 294 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_CARRIGE_RETURN;
#line 294 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '\t':
						{
#line 295 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_TAB;
#line 295 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case ']':
						{
#line 296 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_SQUARE_BRACKET_RIGHT;
#line 296 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '^':
						{
#line 297 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_CARET;
#line 297 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '{':
						{
#line 298 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_CURLY_BRACE_LEFT;
#line 298 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '|':
						{
#line 299 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_BITWISE_OR;
#line 299 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '}':
						{
#line 300 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_CURLY_BRACE_RIGHT;
#line 300 "../../../Source/Core/TokenContainer.nll"
							break;
						}

						case '~':
						{
#line 301 "../../../Source/Core/TokenContainer.nll"
							eType = Token.Type.TOKEN_TILDE;
#line 301 "../../../Source/Core/TokenContainer.nll"
							break;
						}

					}
#line 303 "../../../Source/Core/TokenContainer.nll"
					if (eType != Token.Type.TOKEN_IDENTIFIER)
					{
#line 305 "../../../Source/Core/TokenContainer.nll"
						if (m_pTokenVector.GetSize() > 0)
						{
							Token pPreviousToken = m_pTokenVector.Get(m_pTokenVector.GetSize() - 1);
#line 309 "../../../Source/Core/TokenContainer.nll"
							if (pPreviousToken.m_eType == Token.Type.TOKEN_COLON && eType == Token.Type.TOKEN_COLON)
							{
#line 311 "../../../Source/Core/TokenContainer.nll"
								pPreviousToken.m_eType = Token.Type.TOKEN_DOUBLE_COLON;
#line 312 "../../../Source/Core/TokenContainer.nll"
								pParseDatum.ClearCurrentRead();
#line 313 "../../../Source/Core/TokenContainer.nll"
								return;
							}
#line 316 "../../../Source/Core/TokenContainer.nll"
							if (pPreviousToken.m_eType == Token.Type.TOKEN_PLUS && eType == Token.Type.TOKEN_PLUS)
							{
#line 318 "../../../Source/Core/TokenContainer.nll"
								pPreviousToken.m_eType = Token.Type.TOKEN_PLUS_PLUS;
#line 319 "../../../Source/Core/TokenContainer.nll"
								pParseDatum.ClearCurrentRead();
#line 320 "../../../Source/Core/TokenContainer.nll"
								return;
							}
#line 323 "../../../Source/Core/TokenContainer.nll"
							if (pPreviousToken.m_eType == Token.Type.TOKEN_MINUS && eType == Token.Type.TOKEN_MINUS)
							{
#line 325 "../../../Source/Core/TokenContainer.nll"
								pPreviousToken.m_eType = Token.Type.TOKEN_MINUS_MINUS;
#line 326 "../../../Source/Core/TokenContainer.nll"
								pParseDatum.ClearCurrentRead();
#line 327 "../../../Source/Core/TokenContainer.nll"
								return;
							}
#line 330 "../../../Source/Core/TokenContainer.nll"
							if (pPreviousToken.m_eType == Token.Type.TOKEN_STAR && eType == Token.Type.TOKEN_STAR)
							{
#line 332 "../../../Source/Core/TokenContainer.nll"
								pPreviousToken.m_eType = Token.Type.TOKEN_STAR_DOUBLE;
#line 333 "../../../Source/Core/TokenContainer.nll"
								pParseDatum.ClearCurrentRead();
#line 334 "../../../Source/Core/TokenContainer.nll"
								return;
							}
						}
#line 338 "../../../Source/Core/TokenContainer.nll"
						PushToken(eType, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 339 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 341 "../../../Source/Core/TokenContainer.nll"
					break;
				}

				case 2:
				{
#line 345 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("if"))
					{
#line 347 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_IF, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 348 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 350 "../../../Source/Core/TokenContainer.nll"
					break;
				}

				case 3:
				{
#line 354 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("for"))
					{
#line 356 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_FOR, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 357 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 359 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("int"))
					{
#line 361 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_INT, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 362 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 364 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("new"))
					{
#line 366 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_NEW, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 367 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 369 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("own"))
					{
#line 371 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_OWN, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 372 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 374 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("ref"))
					{
#line 376 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_REF, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 377 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 379 "../../../Source/Core/TokenContainer.nll"
					break;
				}

				case 4:
				{
#line 383 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("bool"))
					{
#line 385 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_BOOL, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 386 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 388 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("base"))
					{
#line 390 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_BASE, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 391 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 393 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("case"))
					{
#line 395 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_CASE, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 396 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 398 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("cast"))
					{
#line 400 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_CAST, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 401 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 403 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("enum"))
					{
#line 405 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_ENUM, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 406 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 408 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("else"))
					{
#line 410 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_ELSE, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 411 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 413 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("Int8"))
					{
#line 415 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_INT8, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 416 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 418 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("null"))
					{
#line 420 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_NULL, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 421 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 423 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("this"))
					{
#line 425 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_THIS, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 426 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 428 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("true"))
					{
#line 430 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_TRUE, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 431 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 433 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("uint"))
					{
#line 435 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_UINT, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 436 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 438 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("void"))
					{
#line 440 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_VOID, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 441 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 443 "../../../Source/Core/TokenContainer.nll"
					break;
				}

				case 5:
				{
#line 447 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("break"))
					{
#line 449 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_BREAK, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 450 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 452 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("class"))
					{
#line 454 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_CLASS, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 455 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 457 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("const"))
					{
#line 459 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_CONST, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 460 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 462 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("false"))
					{
#line 464 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_FALSE, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 465 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 467 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("float"))
					{
#line 469 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_FLOAT, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 470 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 472 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("Int16"))
					{
#line 474 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_INT16, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 475 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 477 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("Int32"))
					{
#line 479 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_INT32, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 480 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 482 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("Uint8"))
					{
#line 484 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_UINT8, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 485 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 487 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("using"))
					{
#line 489 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_USING, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 490 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 492 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("while"))
					{
#line 494 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_WHILE, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 495 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 497 "../../../Source/Core/TokenContainer.nll"
					break;
				}

				case 6:
				{
#line 501 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("delete"))
					{
#line 503 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_DELETE, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 504 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 506 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("disown"))
					{
#line 508 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_DISOWN, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 509 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 511 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("double"))
					{
#line 513 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_DOUBLE, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 514 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 516 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("public"))
					{
#line 518 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_PUBLIC, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 519 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 521 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("return"))
					{
#line 523 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_RETURN, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 524 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 526 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("static"))
					{
#line 528 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_STATIC, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 529 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 531 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("string"))
					{
#line 533 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_STRING, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 534 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 536 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("switch"))
					{
#line 538 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_SWITCH, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 539 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 541 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("tthash"))
					{
#line 543 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_TTHASH, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 544 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 546 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("Uint16"))
					{
#line 548 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_UINT16, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 549 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 551 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("Uint32"))
					{
#line 553 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_UINT32, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 554 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 556 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("Uint64"))
					{
#line 558 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_UINT64, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 559 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 562 "../../../Source/Core/TokenContainer.nll"
					break;
				}

				case 7:
				{
#line 566 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("default"))
					{
#line 568 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_DEFAULT, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 569 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 571 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("private"))
					{
#line 573 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_PRIVATE, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 574 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 576 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("UniChar"))
					{
#line 578 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_UNICHAR, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 579 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 581 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("virtual"))
					{
#line 583 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_VIRTUAL, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 584 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 586 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("voidptr"))
					{
#line 588 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_VOIDPTR, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 589 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 591 "../../../Source/Core/TokenContainer.nll"
					break;
				}

				case 8:
				{
#line 595 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("continue"))
					{
#line 597 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_CONTINUE, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 598 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 600 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("delegate"))
					{
#line 602 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_DELEGATE, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 603 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 605 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("destruct"))
					{
#line 607 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_DESTRUCT, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 608 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 610 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("override"))
					{
#line 612 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_OVERRIDE, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 613 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 615 "../../../Source/Core/TokenContainer.nll"
					break;
				}

				case 9:
				{
#line 619 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("construct"))
					{
#line 621 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_CONSTRUCT, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 622 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 625 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("namespace"))
					{
#line 627 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_NAMESPACE, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 628 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 630 "../../../Source/Core/TokenContainer.nll"
					break;
				}

				case 10:
				{
#line 634 "../../../Source/Core/TokenContainer.nll"
					if (pParseDatum.m_sCurrentRead.IsEqual("disposable"))
					{
#line 636 "../../../Source/Core/TokenContainer.nll"
						PushToken(Token.Type.TOKEN_KEYWORD_DISPOSABLE, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
#line 637 "../../../Source/Core/TokenContainer.nll"
						return;
					}
#line 639 "../../../Source/Core/TokenContainer.nll"
					break;
				}

			}
			{
				int i = 0;
				bool bFirstZero = false;
				bool bHex = false;
				int nLength = pParseDatum.m_sCurrentRead.GetLength();
#line 649 "../../../Source/Core/TokenContainer.nll"
				for (int hax = 0; i < nLength; i = i + 1)
				{
#line 651 "../../../Source/Core/TokenContainer.nll"
					hax++;
					int nChar = pParseDatum.m_sCurrentRead.GetChar(i);
#line 654 "../../../Source/Core/TokenContainer.nll"
					if (i == 0 && nChar == '0')
					{
#line 656 "../../../Source/Core/TokenContainer.nll"
						bFirstZero = true;
#line 657 "../../../Source/Core/TokenContainer.nll"
						continue;
					}
#line 660 "../../../Source/Core/TokenContainer.nll"
					if (i == 1 && bFirstZero && nChar == 'x')
					{
#line 662 "../../../Source/Core/TokenContainer.nll"
						bHex = true;
#line 663 "../../../Source/Core/TokenContainer.nll"
						continue;
					}
#line 666 "../../../Source/Core/TokenContainer.nll"
					if (bHex)
					{
#line 668 "../../../Source/Core/TokenContainer.nll"
						if (nChar >= '0' && nChar <= '9' || nChar >= 'A' && nChar <= 'F' || nChar >= 'a' && nChar <= 'f')
						{
#line 670 "../../../Source/Core/TokenContainer.nll"
							continue;
						}
					}
					else
					{
#line 675 "../../../Source/Core/TokenContainer.nll"
						if (nChar >= '0' && nChar <= '9' || nChar == '.')
						{
#line 677 "../../../Source/Core/TokenContainer.nll"
							continue;
						}
#line 680 "../../../Source/Core/TokenContainer.nll"
						if (i == nLength - 1 && nChar == 'f')
#line 681 "../../../Source/Core/TokenContainer.nll"
							continue;
					}
#line 684 "../../../Source/Core/TokenContainer.nll"
					break;
				}
#line 687 "../../../Source/Core/TokenContainer.nll"
				if (i == nLength)
				{
#line 689 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token.Type.TOKEN_NUMBER, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, true);
#line 690 "../../../Source/Core/TokenContainer.nll"
					return;
				}
			}
#line 696 "../../../Source/Core/TokenContainer.nll"
			PushToken(Token.Type.TOKEN_IDENTIFIER, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, true);
		}

#line 699 "../../../Source/Core/TokenContainer.nll"
		protected void PushToken(Token.Type eType, int nLine, int nColumn, ParseDatum pParseDatum, bool bCopyString)
		{
			Token pToken = new Token();
#line 702 "../../../Source/Core/TokenContainer.nll"
			pToken.m_eType = eType;
#line 703 "../../../Source/Core/TokenContainer.nll"
			pToken.m_sFileName = pParseDatum.m_sFileName;
#line 704 "../../../Source/Core/TokenContainer.nll"
			pToken.m_nLine = nLine;
#line 705 "../../../Source/Core/TokenContainer.nll"
			pToken.m_nColumn = nColumn;
#line 707 "../../../Source/Core/TokenContainer.nll"
			if (bCopyString)
#line 708 "../../../Source/Core/TokenContainer.nll"
				pToken.m_sValue = new InternalString(pParseDatum.m_sCurrentRead.GetExternalString());
#line 710 "../../../Source/Core/TokenContainer.nll"
			pParseDatum.ClearCurrentRead();
			NumbatLogic.Token __3820032206 = pToken;
#line 712 "../../../Source/Core/TokenContainer.nll"
			pToken = null;
#line 712 "../../../Source/Core/TokenContainer.nll"
			m_pTokenVector.PushBack(__3820032206);
		}

#line 715 "../../../Source/Core/TokenContainer.nll"
		protected void ParseQuoted(ParseDatum pParseDatum, char nQuoteChar)
		{
			bool bEscaping = false;
#line 725 "../../../Source/Core/TokenContainer.nll"
			while (true)
			{
				char nChar = ReadChar(pParseDatum, false);
#line 728 "../../../Source/Core/TokenContainer.nll"
				if (nChar == '\0')
				{
					Token.Type eType = Token.Type.TOKEN_CHAR_UNTERMINATED;
#line 732 "../../../Source/Core/TokenContainer.nll"
					if (nQuoteChar == '"')
#line 733 "../../../Source/Core/TokenContainer.nll"
						eType = Token.Type.TOKEN_STRING_UNTERMINATED;
#line 734 "../../../Source/Core/TokenContainer.nll"
					PushToken(eType, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, true);
#line 735 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 738 "../../../Source/Core/TokenContainer.nll"
				pParseDatum.m_sCurrentRead.AppendChar(nChar);
#line 739 "../../../Source/Core/TokenContainer.nll"
				pParseDatum.m_nColumn = pParseDatum.m_nColumn + 1;
#line 741 "../../../Source/Core/TokenContainer.nll"
				if (nChar == nQuoteChar && !bEscaping)
				{
					Token.Type eType = Token.Type.TOKEN_CHAR;
#line 744 "../../../Source/Core/TokenContainer.nll"
					if (nQuoteChar == '"')
#line 745 "../../../Source/Core/TokenContainer.nll"
						eType = Token.Type.TOKEN_STRING;
#line 746 "../../../Source/Core/TokenContainer.nll"
					PushToken(eType, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, true);
#line 747 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 750 "../../../Source/Core/TokenContainer.nll"
				if (bEscaping)
#line 751 "../../../Source/Core/TokenContainer.nll"
					bEscaping = false;
				else
#line 752 "../../../Source/Core/TokenContainer.nll"
					if (nChar == '\\')
					{
#line 754 "../../../Source/Core/TokenContainer.nll"
						bEscaping = true;
					}
			}
		}

#line 763 "../../../Source/Core/TokenContainer.nll"
		public void Stringify(InternalString sOut)
		{
#line 765 "../../../Source/Core/TokenContainer.nll"
			for (int i = 0; i < m_pTokenVector.GetSize(); i++)
			{
				Token pToken = m_pTokenVector.Get(i);
#line 768 "../../../Source/Core/TokenContainer.nll"
				sOut.Append(pToken.GetString());
			}
		}

#line 772 "../../../Source/Core/TokenContainer.nll"
		public void StripWhitespace()
		{
			int nIn = 0;
#line 775 "../../../Source/Core/TokenContainer.nll"
			while (nIn < m_pTokenVector.GetSize())
			{
				Token pToken = m_pTokenVector.Get(nIn);
#line 778 "../../../Source/Core/TokenContainer.nll"
				if (pToken.m_eType == Token.Type.TOKEN_CARRIGE_RETURN || pToken.m_eType == Token.Type.TOKEN_NEW_LINE || pToken.m_eType == Token.Type.TOKEN_SPACE || pToken.m_eType == Token.Type.TOKEN_TAB)
				{
#line 783 "../../../Source/Core/TokenContainer.nll"
					m_pTokenVector.Erase(nIn);
#line 784 "../../../Source/Core/TokenContainer.nll"
					continue;
				}
#line 787 "../../../Source/Core/TokenContainer.nll"
				nIn++;
			}
		}

#line 791 "../../../Source/Core/TokenContainer.nll"
		public Token Peek(OffsetDatum pOffsetDatum)
		{
#line 793 "../../../Source/Core/TokenContainer.nll"
			if (pOffsetDatum.m_nOffset < m_pTokenVector.GetSize())
#line 794 "../../../Source/Core/TokenContainer.nll"
				return m_pTokenVector.Get(pOffsetDatum.m_nOffset);
#line 795 "../../../Source/Core/TokenContainer.nll"
			return null;
		}

#line 798 "../../../Source/Core/TokenContainer.nll"
		public Token PeekExpect(OffsetDatum pOffsetDatum, Token.Type eType)
		{
			Token pToken = Peek(pOffsetDatum);
#line 801 "../../../Source/Core/TokenContainer.nll"
			if (pToken == null || pToken.m_eType != eType)
#line 802 "../../../Source/Core/TokenContainer.nll"
				return null;
#line 803 "../../../Source/Core/TokenContainer.nll"
			return pToken;
		}

#line 806 "../../../Source/Core/TokenContainer.nll"
		public string StringifyOffset(OffsetDatum pOffsetDatum)
		{
			Token pToken = null;
#line 809 "../../../Source/Core/TokenContainer.nll"
			if (pOffsetDatum.m_nOffset < m_pTokenVector.GetSize())
#line 810 "../../../Source/Core/TokenContainer.nll"
				pToken = m_pTokenVector.Get(pOffsetDatum.m_nOffset);
#line 811 "../../../Source/Core/TokenContainer.nll"
			if (pToken == null && m_pTokenVector.GetSize() > 0)
#line 812 "../../../Source/Core/TokenContainer.nll"
				pToken = m_pTokenVector.Get(m_pTokenVector.GetSize() - 1);
#line 814 "../../../Source/Core/TokenContainer.nll"
			if (pToken == null)
#line 815 "../../../Source/Core/TokenContainer.nll"
				return "unbeknownst:?:?";
#line 817 "../../../Source/Core/TokenContainer.nll"
			m_sTemp.Set(pToken.m_sFileName.GetExternalString());
#line 818 "../../../Source/Core/TokenContainer.nll"
			m_sTemp.Append(":");
#line 819 "../../../Source/Core/TokenContainer.nll"
			m_sTemp.AppendInt(pToken.m_nLine);
#line 820 "../../../Source/Core/TokenContainer.nll"
			m_sTemp.Append(":");
#line 821 "../../../Source/Core/TokenContainer.nll"
			m_sTemp.AppendInt(pToken.m_nColumn);
#line 822 "../../../Source/Core/TokenContainer.nll"
			m_sTemp.Append(" ");
#line 823 "../../../Source/Core/TokenContainer.nll"
			m_sTemp.Append(pToken.GetString());
#line 824 "../../../Source/Core/TokenContainer.nll"
			return m_sTemp.GetExternalString();
		}

#line 4 "../../../Source/Core/TokenContainer.nll"
		~TokenContainer()
		{
		}

	}
}

