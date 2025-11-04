namespace NumbatLogic
{
	class TokenContainer
	{
		public OwnedVector<Token> m_pTokenVector;
		protected InternalString m_sTemp;
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
			int nIfdefDepth = 0;
			while (true)
			{
				char nChar = ReadChar(pParseDatum, false);
				if (nChar == 0 || nChar < 0)
				{
					ProcessCurrentRead(pParseDatum);
					break;
				}
				if (nChar == '#')
				{
					if (pParseDatum.m_sInput.StartsWith("ifdef "))
					{
						pParseDatum.m_sInput.SubStr(6, pParseDatum.m_sInput.GetLength() - 6);
						InternalString sName = new InternalString("");
						while (true)
						{
							nChar = ReadChar(pParseDatum, false);
							if (nChar == '\0')
							{
								Console.Log("End of #ifdef name not found");
								NumbatLogic.Assert.Plz(false);
							}
							if (nChar == ' ' || nChar == '\t' || nChar == '\n')
								break;
							sName.AppendChar(nChar);
						}
						pParseDatum.m_nLine = pParseDatum.m_nLine + 1;
						pParseDatum.m_nColumn = 0;
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
						if (bFound)
						{
							nIfdefDepth++;
							continue;
						}
						while (true)
						{
							nChar = ReadChar(pParseDatum, false);
							if (nChar == '\0')
							{
								Console.Log("End of #ifdef not found");
								NumbatLogic.Assert.Plz(false);
							}
							if (nChar == '#')
							{
								if (pParseDatum.m_sInput.StartsWith("endif"))
								{
									pParseDatum.m_sInput.SubStr(5, pParseDatum.m_sInput.GetLength() - 5);
									break;
								}
							}
							if (nChar == '\n')
							{
								pParseDatum.m_nLine = pParseDatum.m_nLine + 1;
								pParseDatum.m_nColumn = 0;
							}
						}
						continue;
					}
					if (pParseDatum.m_sInput.StartsWith("endif"))
					{
						if (nIfdefDepth <= 0)
						{
							Console.Log("#endif with no #ifdef???");
							Console.Log(sFileName.GetExternalString());
							NumbatLogic.Assert.Plz(false);
						}
						nIfdefDepth--;
						pParseDatum.m_sInput.SubStr(5, pParseDatum.m_sInput.GetLength() - 5);
						continue;
					}
				}
				if (nChar == '/')
				{
					char nNextChar = ReadChar(pParseDatum, true);
					{
						if (nNextChar == '/')
						{
							ProcessCurrentRead(pParseDatum);
							while (true)
							{
								char nNextNextChar = ReadChar(pParseDatum, false);
								if (nNextNextChar == 0 || nNextNextChar < 0)
									break;
								if (nNextNextChar == '\n')
									break;
							}
							pParseDatum.m_nLine = pParseDatum.m_nLine + 1;
							continue;
						}
						else
							if (nNextChar == '*')
							{
								ProcessCurrentRead(pParseDatum);
								int nLastChar = 0;
								while (true)
								{
									char nNextNextChar = ReadChar(pParseDatum, false);
									if (nNextNextChar == 0 || nNextNextChar < 0)
										break;
									pParseDatum.m_nColumn = pParseDatum.m_nColumn + 1;
									if (nNextNextChar == '\n')
									{
										pParseDatum.m_nLine = pParseDatum.m_nLine + 1;
										pParseDatum.m_nColumn = 0;
									}
									if (nNextNextChar == '/' && nLastChar == '*')
										break;
									nLastChar = nNextNextChar;
								}
								continue;
							}
					}
				}
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
							if (i == nLength)
								break;
						}
						ProcessCurrentRead(pParseDatum);
						pParseDatum.m_sCurrentRead.AppendChar(nChar);
						pParseDatum.m_nColumn = pParseDatum.m_nColumn + 1;
						if (nChar == '\n')
						{
							pParseDatum.m_nLine = pParseDatum.m_nLine + 1;
							pParseDatum.m_nColumn = 0;
						}
						ProcessCurrentRead(pParseDatum);
						continue;
					}

					case '"':
					case '\'':
					{
						ProcessCurrentRead(pParseDatum);
						pParseDatum.m_sCurrentRead.AppendChar(nChar);
						pParseDatum.m_nColumn = pParseDatum.m_nColumn + 1;
						ParseQuoted(pParseDatum, nChar);
						continue;
					}

				}
				pParseDatum.m_sCurrentRead.AppendChar(nChar);
				pParseDatum.m_nColumn = pParseDatum.m_nColumn + 1;
			}
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
					Token.Type eType = Token.Type.TOKEN_IDENTIFIER;
					switch (pParseDatum.m_sCurrentRead.GetChar(0))
					{
						case ' ':
						{
							eType = Token.Type.TOKEN_SPACE;
							break;
						}

						case '!':
						{
							eType = Token.Type.TOKEN_BANG;
							break;
						}

						case '%':
						{
							eType = Token.Type.TOKEN_MODULUS;
							break;
						}

						case '&':
						{
							eType = Token.Type.TOKEN_BITWISE_AND;
							break;
						}

						case '(':
						{
							eType = Token.Type.TOKEN_PARENTHESIS_LEFT;
							break;
						}

						case ')':
						{
							eType = Token.Type.TOKEN_PARENTHESIS_RIGHT;
							break;
						}

						case '*':
						{
							eType = Token.Type.TOKEN_STAR;
							break;
						}

						case '+':
						{
							eType = Token.Type.TOKEN_PLUS;
							break;
						}

						case ',':
						{
							eType = Token.Type.TOKEN_COMMA;
							break;
						}

						case '-':
						{
							eType = Token.Type.TOKEN_MINUS;
							break;
						}

						case '.':
						{
							eType = Token.Type.TOKEN_DOT;
							break;
						}

						case '/':
						{
							eType = Token.Type.TOKEN_DIVIDE;
							break;
						}

						case ':':
						{
							eType = Token.Type.TOKEN_COLON;
							break;
						}

						case ';':
						{
							eType = Token.Type.TOKEN_SEMICOLON;
							break;
						}

						case '<':
						{
							eType = Token.Type.TOKEN_ANGLE_BRACKET_LEFT;
							break;
						}

						case '=':
						{
							eType = Token.Type.TOKEN_EQUALS;
							break;
						}

						case '>':
						{
							eType = Token.Type.TOKEN_ANGLE_BRACKET_RIGHT;
							break;
						}

						case '?':
						{
							eType = Token.Type.TOKEN_QUESTION_MARK;
							break;
						}

						case '[':
						{
							eType = Token.Type.TOKEN_SQUARE_BRACKET_LEFT;
							break;
						}

						case '\n':
						{
							eType = Token.Type.TOKEN_NEW_LINE;
							break;
						}

						case '\r':
						{
							eType = Token.Type.TOKEN_CARRIGE_RETURN;
							break;
						}

						case '\t':
						{
							eType = Token.Type.TOKEN_TAB;
							break;
						}

						case ']':
						{
							eType = Token.Type.TOKEN_SQUARE_BRACKET_RIGHT;
							break;
						}

						case '^':
						{
							eType = Token.Type.TOKEN_CARET;
							break;
						}

						case '{':
						{
							eType = Token.Type.TOKEN_CURLY_BRACE_LEFT;
							break;
						}

						case '|':
						{
							eType = Token.Type.TOKEN_BITWISE_OR;
							break;
						}

						case '}':
						{
							eType = Token.Type.TOKEN_CURLY_BRACE_RIGHT;
							break;
						}

						case '~':
						{
							eType = Token.Type.TOKEN_TILDE;
							break;
						}

					}
					if (eType != Token.Type.TOKEN_IDENTIFIER)
					{
						if (m_pTokenVector.GetSize() > 0)
						{
							Token pPreviousToken = m_pTokenVector.Get(m_pTokenVector.GetSize() - 1);
							if (pPreviousToken.m_eType == Token.Type.TOKEN_ANGLE_BRACKET_LEFT && eType == Token.Type.TOKEN_ANGLE_BRACKET_LEFT)
							{
								pPreviousToken.m_eType = Token.Type.TOKEN_DOUBLE_ANGLE_BRACKET_LEFT;
								pParseDatum.ClearCurrentRead();
								return;
							}
							if (pPreviousToken.m_eType == Token.Type.TOKEN_ANGLE_BRACKET_RIGHT && eType == Token.Type.TOKEN_ANGLE_BRACKET_RIGHT)
							{
								pPreviousToken.m_eType = Token.Type.TOKEN_DOUBLE_ANGLE_BRACKET_RIGHT;
								pParseDatum.ClearCurrentRead();
								return;
							}
							if (pPreviousToken.m_eType == Token.Type.TOKEN_BANG && eType == Token.Type.TOKEN_ANGLE_BRACKET_RIGHT)
							{
								pPreviousToken.m_eType = Token.Type.TOKEN_ANGLE_BRACKET_RIGHT;
								pParseDatum.ClearCurrentRead();
								return;
							}
							if (pPreviousToken.m_eType == Token.Type.TOKEN_COLON && eType == Token.Type.TOKEN_COLON)
							{
								pPreviousToken.m_eType = Token.Type.TOKEN_DOUBLE_COLON;
								pParseDatum.ClearCurrentRead();
								return;
							}
							if (pPreviousToken.m_eType == Token.Type.TOKEN_EQUALS && eType == Token.Type.TOKEN_EQUALS)
							{
								pPreviousToken.m_eType = Token.Type.TOKEN_DOUBLE_EQUALS;
								pParseDatum.ClearCurrentRead();
								return;
							}
							if (pPreviousToken.m_eType == Token.Type.TOKEN_PLUS && eType == Token.Type.TOKEN_EQUALS)
							{
								pPreviousToken.m_eType = Token.Type.TOKEN_PLUS_EQUALS;
								pParseDatum.ClearCurrentRead();
								return;
							}
							if (pPreviousToken.m_eType == Token.Type.TOKEN_PLUS && eType == Token.Type.TOKEN_PLUS)
							{
								pPreviousToken.m_eType = Token.Type.TOKEN_PLUS_PLUS;
								pParseDatum.ClearCurrentRead();
								return;
							}
							if (pPreviousToken.m_eType == Token.Type.TOKEN_MINUS && eType == Token.Type.TOKEN_EQUALS)
							{
								pPreviousToken.m_eType = Token.Type.TOKEN_MINUS_EQUALS;
								pParseDatum.ClearCurrentRead();
								return;
							}
							if (pPreviousToken.m_eType == Token.Type.TOKEN_MINUS && eType == Token.Type.TOKEN_MINUS)
							{
								pPreviousToken.m_eType = Token.Type.TOKEN_MINUS_MINUS;
								pParseDatum.ClearCurrentRead();
								return;
							}
							if (pPreviousToken.m_eType == Token.Type.TOKEN_BANG && eType == Token.Type.TOKEN_EQUALS)
							{
								pPreviousToken.m_eType = Token.Type.TOKEN_NOT_EQUALS;
								pParseDatum.ClearCurrentRead();
								return;
							}
							if (pPreviousToken.m_eType == Token.Type.TOKEN_BITWISE_OR && eType == Token.Type.TOKEN_BITWISE_OR)
							{
								pPreviousToken.m_eType = Token.Type.TOKEN_OR;
								pParseDatum.ClearCurrentRead();
								return;
							}
							if (pPreviousToken.m_eType == Token.Type.TOKEN_BITWISE_AND && eType == Token.Type.TOKEN_BITWISE_AND)
							{
								pPreviousToken.m_eType = Token.Type.TOKEN_AND;
								pParseDatum.ClearCurrentRead();
								return;
							}
							if (pPreviousToken.m_eType == Token.Type.TOKEN_ANGLE_BRACKET_LEFT && eType == Token.Type.TOKEN_EQUALS)
							{
								pPreviousToken.m_eType = Token.Type.TOKEN_ANGLE_BRACKET_LEFT_EQUALS;
								pParseDatum.ClearCurrentRead();
								return;
							}
							if (pPreviousToken.m_eType == Token.Type.TOKEN_ANGLE_BRACKET_RIGHT && eType == Token.Type.TOKEN_EQUALS)
							{
								pPreviousToken.m_eType = Token.Type.TOKEN_ANGLE_BRACKET_RIGHT_EQUALS;
								pParseDatum.ClearCurrentRead();
								return;
							}
							if (pPreviousToken.m_eType == Token.Type.TOKEN_STAR && eType == Token.Type.TOKEN_STAR)
							{
								pPreviousToken.m_eType = Token.Type.TOKEN_STAR_DOUBLE;
								pParseDatum.ClearCurrentRead();
								return;
							}
						}
						PushToken(eType, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					break;
				}

				case 2:
				{
					if (pParseDatum.m_sCurrentRead.IsEqual("if"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_IF, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					break;
				}

				case 3:
				{
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
					break;
				}

				case 7:
				{
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
					if (pParseDatum.m_sCurrentRead.IsEqual("construct"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_CONSTRUCT, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					if (pParseDatum.m_sCurrentRead.IsEqual("namespace"))
					{
						PushToken(Token.Type.TOKEN_KEYWORD_NAMESPACE, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, false);
						return;
					}
					break;
				}

			}
			{
				int i = 0;
				bool bFirstZero = false;
				bool bHex = false;
				int nLength = pParseDatum.m_sCurrentRead.GetLength();
				for (int hax = 0; i < nLength; i = i + 1)
				{
					hax++;
					int nChar = pParseDatum.m_sCurrentRead.GetChar(i);
					if (i == 0 && nChar == '0')
					{
						bFirstZero = true;
						continue;
					}
					if (i == 1 && bFirstZero && nChar == 'x')
					{
						bHex = true;
						continue;
					}
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
						if (i == nLength - 1 && nChar == 'f')
							continue;
					}
					break;
				}
				if (i == nLength)
				{
					PushToken(Token.Type.TOKEN_NUMBER, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, true);
					return;
				}
			}
			PushToken(Token.Type.TOKEN_IDENTIFIER, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, true);
		}

		protected void PushToken(Token.Type eType, int nLine, int nColumn, ParseDatum pParseDatum, bool bCopyString)
		{
			Token pToken = new Token();
			pToken.m_eType = eType;
			pToken.m_sFileName = pParseDatum.m_sFileName;
			pToken.m_nLine = nLine;
			pToken.m_nColumn = nColumn;
			if (bCopyString)
				pToken.m_sValue = new InternalString(pParseDatum.m_sCurrentRead.GetExternalString());
			pParseDatum.ClearCurrentRead();
			NumbatLogic.Token __3967328402 = pToken;
			pToken = null;
			m_pTokenVector.PushBack(__3967328402);
		}

		protected void ParseQuoted(ParseDatum pParseDatum, char nQuoteChar)
		{
			bool bEscaping = false;
			while (true)
			{
				char nChar = ReadChar(pParseDatum, false);
				if (nChar == '\0')
				{
					Token.Type eType = Token.Type.TOKEN_CHAR_UNTERMINATED;
					if (nQuoteChar == '"')
						eType = Token.Type.TOKEN_STRING_UNTERMINATED;
					PushToken(eType, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, true);
					return;
				}
				pParseDatum.m_sCurrentRead.AppendChar(nChar);
				pParseDatum.m_nColumn = pParseDatum.m_nColumn + 1;
				if (nChar == nQuoteChar && !bEscaping)
				{
					Token.Type eType = Token.Type.TOKEN_CHAR;
					if (nQuoteChar == '"')
						eType = Token.Type.TOKEN_STRING;
					PushToken(eType, pParseDatum.m_nCurrentReadLine, pParseDatum.m_nCurrentReadColumn, pParseDatum, true);
					return;
				}
				if (bEscaping)
					bEscaping = false;
				else
					if (nChar == '\\')
					{
						bEscaping = true;
					}
			}
		}

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
					m_pTokenVector.Erase(nIn);
					continue;
				}
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
			if (pToken == null)
				return "unbeknownst:?:?";
			m_sTemp.Set(pToken.m_sFileName.GetExternalString());
			m_sTemp.Append(":");
			m_sTemp.AppendInt(pToken.m_nLine);
			m_sTemp.Append(":");
			m_sTemp.AppendInt(pToken.m_nColumn);
			m_sTemp.Append(" ");
			m_sTemp.Append(pToken.GetString());
			return m_sTemp.GetExternalString();
		}

		~TokenContainer()
		{
		}

	}
}

