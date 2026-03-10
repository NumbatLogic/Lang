#include "TokenContainer.hpp"
#include "Token.hpp"
#include "../../../LangShared/Transpiled/Vector/OwnedVector.hpp"
#include "../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "ParseDatum.hpp"
#include "../../../LangShared/Console/CPP/Console.hpp"
#include "../../../LangShared/Assert/CPP/Assert.hpp"
#include "OffsetDatum.hpp"

namespace NumbatLogic
{
	class TokenContainer;
	class Token;
	template <class T>
	class OwnedVector;
	class InternalString;
	class ParseDatum;
	class Console;
	class Assert;
	class OffsetDatum;
}
#line 0 "../../../Source/Core/TokenContainer.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/TokenContainer.nll"
#line 8 "../../../Source/Core/TokenContainer.nll"
	TokenContainer::TokenContainer()
	{
		m_pTokenVector = 0;
		m_sTemp = 0;
#line 10 "../../../Source/Core/TokenContainer.nll"
		m_pTokenVector = new OwnedVector<Token*>();
#line 11 "../../../Source/Core/TokenContainer.nll"
		m_sTemp = new InternalString("");
	}

#line 14 "../../../Source/Core/TokenContainer.nll"
	unsigned short TokenContainer::ReadChar(ParseDatum* pParseDatum, bool bPeak)
	{
#line 16 "../../../Source/Core/TokenContainer.nll"
		if (pParseDatum->m_sInput->GetLength() > 0)
		{
			unsigned short nChar = pParseDatum->m_sInput->GetChar(0);
#line 19 "../../../Source/Core/TokenContainer.nll"
			if (!bPeak)
#line 20 "../../../Source/Core/TokenContainer.nll"
				pParseDatum->m_sInput->SubStr(1, pParseDatum->m_sInput->GetLength() - 1);
#line 21 "../../../Source/Core/TokenContainer.nll"
			return nChar;
		}
#line 23 "../../../Source/Core/TokenContainer.nll"
		return '\0';
	}

#line 26 "../../../Source/Core/TokenContainer.nll"
	bool TokenContainer::Tokenize(const char* sInput, InternalString* sFileName, OwnedVector<InternalString*>* sDefineVector)
	{
		ParseDatum* pParseDatum = new ParseDatum();
#line 29 "../../../Source/Core/TokenContainer.nll"
		pParseDatum->m_sInput->Set(sInput);
#line 30 "../../../Source/Core/TokenContainer.nll"
		pParseDatum->m_sFileName = sFileName;
		int nIfdefDepth = 0;
#line 34 "../../../Source/Core/TokenContainer.nll"
		while (true)
		{
			unsigned short nChar = ReadChar(pParseDatum, false);
#line 37 "../../../Source/Core/TokenContainer.nll"
			if (nChar == 0 || nChar < 0)
			{
#line 39 "../../../Source/Core/TokenContainer.nll"
				ProcessCurrentRead(pParseDatum);
#line 40 "../../../Source/Core/TokenContainer.nll"
				break;
			}
#line 44 "../../../Source/Core/TokenContainer.nll"
			if (nChar == '#')
			{
#line 46 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sInput->StartsWith("ifdef "))
				{
#line 48 "../../../Source/Core/TokenContainer.nll"
					pParseDatum->m_sInput->SubStr(6, pParseDatum->m_sInput->GetLength() - 6);
					InternalString* sName = new InternalString("");
#line 51 "../../../Source/Core/TokenContainer.nll"
					while (true)
					{
#line 53 "../../../Source/Core/TokenContainer.nll"
						nChar = ReadChar(pParseDatum, false);
#line 54 "../../../Source/Core/TokenContainer.nll"
						if (nChar == '\0')
						{
#line 56 "../../../Source/Core/TokenContainer.nll"
							Console::Log("End of #ifdef name not found");
#line 57 "../../../Source/Core/TokenContainer.nll"
							Assert::Plz(false);
						}
#line 59 "../../../Source/Core/TokenContainer.nll"
						if (nChar == ' ' || nChar == '\t' || nChar == '\n')
#line 60 "../../../Source/Core/TokenContainer.nll"
							break;
#line 61 "../../../Source/Core/TokenContainer.nll"
						sName->AppendChar(nChar);
					}
#line 64 "../../../Source/Core/TokenContainer.nll"
					pParseDatum->m_nLine = pParseDatum->m_nLine + 1;
#line 65 "../../../Source/Core/TokenContainer.nll"
					pParseDatum->m_nColumn = 0;
					bool bFound = false;
					const char* sxName = sName->GetExternalString();
#line 69 "../../../Source/Core/TokenContainer.nll"
					for (int i = 0; i < sDefineVector->GetSize(); i++)
					{
#line 71 "../../../Source/Core/TokenContainer.nll"
						if (sDefineVector->Get(i)->IsEqual(sxName))
						{
#line 73 "../../../Source/Core/TokenContainer.nll"
							bFound = true;
#line 74 "../../../Source/Core/TokenContainer.nll"
							break;
						}
					}
#line 80 "../../../Source/Core/TokenContainer.nll"
					if (bFound)
					{
#line 82 "../../../Source/Core/TokenContainer.nll"
						nIfdefDepth++;
						if (sName) delete sName;
#line 83 "../../../Source/Core/TokenContainer.nll"
						continue;
					}
#line 87 "../../../Source/Core/TokenContainer.nll"
					while (true)
					{
#line 89 "../../../Source/Core/TokenContainer.nll"
						nChar = ReadChar(pParseDatum, false);
#line 90 "../../../Source/Core/TokenContainer.nll"
						if (nChar == '\0')
						{
#line 92 "../../../Source/Core/TokenContainer.nll"
							Console::Log("End of #ifdef not found");
#line 93 "../../../Source/Core/TokenContainer.nll"
							Assert::Plz(false);
						}
#line 96 "../../../Source/Core/TokenContainer.nll"
						if (nChar == '#')
						{
#line 98 "../../../Source/Core/TokenContainer.nll"
							if (pParseDatum->m_sInput->StartsWith("endif"))
							{
#line 100 "../../../Source/Core/TokenContainer.nll"
								pParseDatum->m_sInput->SubStr(5, pParseDatum->m_sInput->GetLength() - 5);
#line 101 "../../../Source/Core/TokenContainer.nll"
								break;
							}
						}
#line 105 "../../../Source/Core/TokenContainer.nll"
						if (nChar == '\n')
						{
#line 107 "../../../Source/Core/TokenContainer.nll"
							pParseDatum->m_nLine = pParseDatum->m_nLine + 1;
#line 108 "../../../Source/Core/TokenContainer.nll"
							pParseDatum->m_nColumn = 0;
						}
					}
					if (sName) delete sName;
#line 111 "../../../Source/Core/TokenContainer.nll"
					continue;
				}
#line 114 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sInput->StartsWith("endif"))
				{
#line 116 "../../../Source/Core/TokenContainer.nll"
					if (nIfdefDepth <= 0)
					{
#line 118 "../../../Source/Core/TokenContainer.nll"
						Console::Log("#endif with no #ifdef???");
#line 119 "../../../Source/Core/TokenContainer.nll"
						Console::Log(sFileName->GetExternalString());
#line 120 "../../../Source/Core/TokenContainer.nll"
						Assert::Plz(false);
					}
#line 123 "../../../Source/Core/TokenContainer.nll"
					nIfdefDepth--;
#line 124 "../../../Source/Core/TokenContainer.nll"
					pParseDatum->m_sInput->SubStr(5, pParseDatum->m_sInput->GetLength() - 5);
#line 125 "../../../Source/Core/TokenContainer.nll"
					continue;
				}
			}
#line 130 "../../../Source/Core/TokenContainer.nll"
			if (nChar == '/')
			{
				unsigned short nNextChar = ReadChar(pParseDatum, true);
				{
#line 135 "../../../Source/Core/TokenContainer.nll"
					if (nNextChar == '/')
					{
#line 137 "../../../Source/Core/TokenContainer.nll"
						ProcessCurrentRead(pParseDatum);
#line 139 "../../../Source/Core/TokenContainer.nll"
						while (true)
						{
							unsigned short nNextNextChar = ReadChar(pParseDatum, false);
#line 142 "../../../Source/Core/TokenContainer.nll"
							if (nNextNextChar == 0 || nNextNextChar < 0)
#line 143 "../../../Source/Core/TokenContainer.nll"
								break;
#line 145 "../../../Source/Core/TokenContainer.nll"
							if (nNextNextChar == '\n')
#line 146 "../../../Source/Core/TokenContainer.nll"
								break;
						}
#line 149 "../../../Source/Core/TokenContainer.nll"
						pParseDatum->m_nLine = pParseDatum->m_nLine + 1;
#line 152 "../../../Source/Core/TokenContainer.nll"
						continue;
					}
					else
#line 154 "../../../Source/Core/TokenContainer.nll"
						if (nNextChar == '*')
						{
#line 156 "../../../Source/Core/TokenContainer.nll"
							ProcessCurrentRead(pParseDatum);
							int nLastChar = 0;
#line 159 "../../../Source/Core/TokenContainer.nll"
							while (true)
							{
								unsigned short nNextNextChar = ReadChar(pParseDatum, false);
#line 162 "../../../Source/Core/TokenContainer.nll"
								if (nNextNextChar == 0 || nNextNextChar < 0)
#line 163 "../../../Source/Core/TokenContainer.nll"
									break;
#line 165 "../../../Source/Core/TokenContainer.nll"
								pParseDatum->m_nColumn = pParseDatum->m_nColumn + 1;
#line 166 "../../../Source/Core/TokenContainer.nll"
								if (nNextNextChar == '\n')
								{
#line 168 "../../../Source/Core/TokenContainer.nll"
									pParseDatum->m_nLine = pParseDatum->m_nLine + 1;
#line 169 "../../../Source/Core/TokenContainer.nll"
									pParseDatum->m_nColumn = 0;
								}
#line 172 "../../../Source/Core/TokenContainer.nll"
								if (nNextNextChar == '/' && nLastChar == '*')
#line 173 "../../../Source/Core/TokenContainer.nll"
									break;
#line 175 "../../../Source/Core/TokenContainer.nll"
								nLastChar = nNextNextChar;
							}
#line 177 "../../../Source/Core/TokenContainer.nll"
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
					int nLength = pParseDatum->m_sCurrentRead->GetLength();
#line 212 "../../../Source/Core/TokenContainer.nll"
					if (nChar == '.' && nLength > 0)
					{
						int i = 0;
#line 215 "../../../Source/Core/TokenContainer.nll"
						for (int hax = 0; i < nLength; i = i + 1)
						{
#line 217 "../../../Source/Core/TokenContainer.nll"
							hax++;
							int nTestChar = pParseDatum->m_sCurrentRead->GetChar(i);
#line 219 "../../../Source/Core/TokenContainer.nll"
							if (nTestChar < '0' || nTestChar > '9')
#line 220 "../../../Source/Core/TokenContainer.nll"
								break;
						}
#line 223 "../../../Source/Core/TokenContainer.nll"
						if (i == nLength)
#line 224 "../../../Source/Core/TokenContainer.nll"
							break;
					}
#line 227 "../../../Source/Core/TokenContainer.nll"
					ProcessCurrentRead(pParseDatum);
#line 228 "../../../Source/Core/TokenContainer.nll"
					pParseDatum->m_sCurrentRead->AppendChar(nChar);
#line 230 "../../../Source/Core/TokenContainer.nll"
					pParseDatum->m_nColumn = pParseDatum->m_nColumn + 1;
#line 231 "../../../Source/Core/TokenContainer.nll"
					if (nChar == '\n')
					{
#line 233 "../../../Source/Core/TokenContainer.nll"
						pParseDatum->m_nLine = pParseDatum->m_nLine + 1;
#line 234 "../../../Source/Core/TokenContainer.nll"
						pParseDatum->m_nColumn = 0;
					}
#line 237 "../../../Source/Core/TokenContainer.nll"
					ProcessCurrentRead(pParseDatum);
#line 238 "../../../Source/Core/TokenContainer.nll"
					continue;
				}

				case '"':
				case '\'':
				{
#line 243 "../../../Source/Core/TokenContainer.nll"
					ProcessCurrentRead(pParseDatum);
#line 244 "../../../Source/Core/TokenContainer.nll"
					pParseDatum->m_sCurrentRead->AppendChar(nChar);
#line 246 "../../../Source/Core/TokenContainer.nll"
					pParseDatum->m_nColumn = pParseDatum->m_nColumn + 1;
#line 247 "../../../Source/Core/TokenContainer.nll"
					ParseQuoted(pParseDatum, nChar);
#line 248 "../../../Source/Core/TokenContainer.nll"
					continue;
				}

			}
#line 252 "../../../Source/Core/TokenContainer.nll"
			pParseDatum->m_sCurrentRead->AppendChar(nChar);
#line 253 "../../../Source/Core/TokenContainer.nll"
			pParseDatum->m_nColumn = pParseDatum->m_nColumn + 1;
		}
		if (pParseDatum) delete pParseDatum;
#line 257 "../../../Source/Core/TokenContainer.nll"
		return true;
	}

#line 260 "../../../Source/Core/TokenContainer.nll"
	void TokenContainer::ProcessCurrentRead(ParseDatum* pParseDatum)
	{
#line 262 "../../../Source/Core/TokenContainer.nll"
		switch (pParseDatum->m_sCurrentRead->GetLength())
		{
			case 0:
			{
#line 266 "../../../Source/Core/TokenContainer.nll"
				return;
			}

			case 1:
			{
				Token::Type eType = Token::Type::TOKEN_IDENTIFIER;
#line 271 "../../../Source/Core/TokenContainer.nll"
				switch (pParseDatum->m_sCurrentRead->GetChar(0))
				{
					case ' ':
					{
#line 273 "../../../Source/Core/TokenContainer.nll"
						eType = Token::Type::TOKEN_SPACE;
#line 273 "../../../Source/Core/TokenContainer.nll"
						break;
					}

					case '!':
					{
#line 274 "../../../Source/Core/TokenContainer.nll"
						eType = Token::Type::TOKEN_BANG;
#line 274 "../../../Source/Core/TokenContainer.nll"
						break;
					}

					case '%':
					{
#line 275 "../../../Source/Core/TokenContainer.nll"
						eType = Token::Type::TOKEN_MODULUS;
#line 275 "../../../Source/Core/TokenContainer.nll"
						break;
					}

					case '&':
					{
#line 276 "../../../Source/Core/TokenContainer.nll"
						eType = Token::Type::TOKEN_BITWISE_AND;
#line 276 "../../../Source/Core/TokenContainer.nll"
						break;
					}

					case '(':
					{
#line 277 "../../../Source/Core/TokenContainer.nll"
						eType = Token::Type::TOKEN_PARENTHESIS_LEFT;
#line 277 "../../../Source/Core/TokenContainer.nll"
						break;
					}

					case ')':
					{
#line 278 "../../../Source/Core/TokenContainer.nll"
						eType = Token::Type::TOKEN_PARENTHESIS_RIGHT;
#line 278 "../../../Source/Core/TokenContainer.nll"
						break;
					}

					case '*':
					{
#line 279 "../../../Source/Core/TokenContainer.nll"
						eType = Token::Type::TOKEN_STAR;
#line 279 "../../../Source/Core/TokenContainer.nll"
						break;
					}

					case '+':
					{
#line 280 "../../../Source/Core/TokenContainer.nll"
						eType = Token::Type::TOKEN_PLUS;
#line 280 "../../../Source/Core/TokenContainer.nll"
						break;
					}

					case ',':
					{
#line 281 "../../../Source/Core/TokenContainer.nll"
						eType = Token::Type::TOKEN_COMMA;
#line 281 "../../../Source/Core/TokenContainer.nll"
						break;
					}

					case '-':
					{
#line 282 "../../../Source/Core/TokenContainer.nll"
						eType = Token::Type::TOKEN_MINUS;
#line 282 "../../../Source/Core/TokenContainer.nll"
						break;
					}

					case '.':
					{
#line 283 "../../../Source/Core/TokenContainer.nll"
						eType = Token::Type::TOKEN_DOT;
#line 283 "../../../Source/Core/TokenContainer.nll"
						break;
					}

					case '/':
					{
#line 284 "../../../Source/Core/TokenContainer.nll"
						eType = Token::Type::TOKEN_DIVIDE;
#line 284 "../../../Source/Core/TokenContainer.nll"
						break;
					}

					case ':':
					{
#line 285 "../../../Source/Core/TokenContainer.nll"
						eType = Token::Type::TOKEN_COLON;
#line 285 "../../../Source/Core/TokenContainer.nll"
						break;
					}

					case ';':
					{
#line 286 "../../../Source/Core/TokenContainer.nll"
						eType = Token::Type::TOKEN_SEMICOLON;
#line 286 "../../../Source/Core/TokenContainer.nll"
						break;
					}

					case '<':
					{
#line 287 "../../../Source/Core/TokenContainer.nll"
						eType = Token::Type::TOKEN_ANGLE_BRACKET_LEFT;
#line 287 "../../../Source/Core/TokenContainer.nll"
						break;
					}

					case '=':
					{
#line 288 "../../../Source/Core/TokenContainer.nll"
						eType = Token::Type::TOKEN_EQUALS;
#line 288 "../../../Source/Core/TokenContainer.nll"
						break;
					}

					case '>':
					{
#line 289 "../../../Source/Core/TokenContainer.nll"
						eType = Token::Type::TOKEN_ANGLE_BRACKET_RIGHT;
#line 289 "../../../Source/Core/TokenContainer.nll"
						break;
					}

					case '?':
					{
#line 290 "../../../Source/Core/TokenContainer.nll"
						eType = Token::Type::TOKEN_QUESTION_MARK;
#line 290 "../../../Source/Core/TokenContainer.nll"
						break;
					}

					case '[':
					{
#line 291 "../../../Source/Core/TokenContainer.nll"
						eType = Token::Type::TOKEN_SQUARE_BRACKET_LEFT;
#line 291 "../../../Source/Core/TokenContainer.nll"
						break;
					}

					case '\n':
					{
#line 292 "../../../Source/Core/TokenContainer.nll"
						eType = Token::Type::TOKEN_NEW_LINE;
#line 292 "../../../Source/Core/TokenContainer.nll"
						break;
					}

					case '\r':
					{
#line 293 "../../../Source/Core/TokenContainer.nll"
						eType = Token::Type::TOKEN_CARRIGE_RETURN;
#line 293 "../../../Source/Core/TokenContainer.nll"
						break;
					}

					case '\t':
					{
#line 294 "../../../Source/Core/TokenContainer.nll"
						eType = Token::Type::TOKEN_TAB;
#line 294 "../../../Source/Core/TokenContainer.nll"
						break;
					}

					case ']':
					{
#line 295 "../../../Source/Core/TokenContainer.nll"
						eType = Token::Type::TOKEN_SQUARE_BRACKET_RIGHT;
#line 295 "../../../Source/Core/TokenContainer.nll"
						break;
					}

					case '^':
					{
#line 296 "../../../Source/Core/TokenContainer.nll"
						eType = Token::Type::TOKEN_CARET;
#line 296 "../../../Source/Core/TokenContainer.nll"
						break;
					}

					case '{':
					{
#line 297 "../../../Source/Core/TokenContainer.nll"
						eType = Token::Type::TOKEN_CURLY_BRACE_LEFT;
#line 297 "../../../Source/Core/TokenContainer.nll"
						break;
					}

					case '|':
					{
#line 298 "../../../Source/Core/TokenContainer.nll"
						eType = Token::Type::TOKEN_BITWISE_OR;
#line 298 "../../../Source/Core/TokenContainer.nll"
						break;
					}

					case '}':
					{
#line 299 "../../../Source/Core/TokenContainer.nll"
						eType = Token::Type::TOKEN_CURLY_BRACE_RIGHT;
#line 299 "../../../Source/Core/TokenContainer.nll"
						break;
					}

					case '~':
					{
#line 300 "../../../Source/Core/TokenContainer.nll"
						eType = Token::Type::TOKEN_TILDE;
#line 300 "../../../Source/Core/TokenContainer.nll"
						break;
					}

				}
#line 302 "../../../Source/Core/TokenContainer.nll"
				if (eType != Token::Type::TOKEN_IDENTIFIER)
				{
#line 304 "../../../Source/Core/TokenContainer.nll"
					if (m_pTokenVector->GetSize() > 0)
					{
						Token* pPreviousToken = m_pTokenVector->Get(m_pTokenVector->GetSize() - 1);
#line 308 "../../../Source/Core/TokenContainer.nll"
						if (pPreviousToken->m_eType == Token::Type::TOKEN_COLON && eType == Token::Type::TOKEN_COLON)
						{
#line 310 "../../../Source/Core/TokenContainer.nll"
							pPreviousToken->m_eType = Token::Type::TOKEN_DOUBLE_COLON;
#line 311 "../../../Source/Core/TokenContainer.nll"
							pParseDatum->ClearCurrentRead();
#line 312 "../../../Source/Core/TokenContainer.nll"
							return;
						}
#line 315 "../../../Source/Core/TokenContainer.nll"
						if (pPreviousToken->m_eType == Token::Type::TOKEN_PLUS && eType == Token::Type::TOKEN_PLUS)
						{
#line 317 "../../../Source/Core/TokenContainer.nll"
							pPreviousToken->m_eType = Token::Type::TOKEN_PLUS_PLUS;
#line 318 "../../../Source/Core/TokenContainer.nll"
							pParseDatum->ClearCurrentRead();
#line 319 "../../../Source/Core/TokenContainer.nll"
							return;
						}
#line 322 "../../../Source/Core/TokenContainer.nll"
						if (pPreviousToken->m_eType == Token::Type::TOKEN_MINUS && eType == Token::Type::TOKEN_MINUS)
						{
#line 324 "../../../Source/Core/TokenContainer.nll"
							pPreviousToken->m_eType = Token::Type::TOKEN_MINUS_MINUS;
#line 325 "../../../Source/Core/TokenContainer.nll"
							pParseDatum->ClearCurrentRead();
#line 326 "../../../Source/Core/TokenContainer.nll"
							return;
						}
#line 329 "../../../Source/Core/TokenContainer.nll"
						if (pPreviousToken->m_eType == Token::Type::TOKEN_STAR && eType == Token::Type::TOKEN_STAR)
						{
#line 331 "../../../Source/Core/TokenContainer.nll"
							pPreviousToken->m_eType = Token::Type::TOKEN_STAR_DOUBLE;
#line 332 "../../../Source/Core/TokenContainer.nll"
							pParseDatum->ClearCurrentRead();
#line 333 "../../../Source/Core/TokenContainer.nll"
							return;
						}
					}
#line 337 "../../../Source/Core/TokenContainer.nll"
					PushToken(eType, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 338 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 340 "../../../Source/Core/TokenContainer.nll"
				break;
			}

			case 2:
			{
#line 344 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("if"))
				{
#line 346 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_IF, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 347 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 349 "../../../Source/Core/TokenContainer.nll"
				break;
			}

			case 3:
			{
#line 353 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("for"))
				{
#line 355 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_FOR, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 356 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 358 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("int"))
				{
#line 360 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_INT, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 361 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 363 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("new"))
				{
#line 365 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_NEW, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 366 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 368 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("own"))
				{
#line 370 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_OWN, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 371 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 373 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("ref"))
				{
#line 375 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_REF, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 376 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 378 "../../../Source/Core/TokenContainer.nll"
				break;
			}

			case 4:
			{
#line 382 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("bool"))
				{
#line 384 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_BOOL, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 385 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 387 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("base"))
				{
#line 389 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_BASE, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 390 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 392 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("case"))
				{
#line 394 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_CASE, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 395 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 397 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("cast"))
				{
#line 399 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_CAST, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 400 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 402 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("enum"))
				{
#line 404 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_ENUM, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 405 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 407 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("else"))
				{
#line 409 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_ELSE, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 410 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 412 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("Int8"))
				{
#line 414 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_INT8, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 415 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 417 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("null"))
				{
#line 419 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_NULL, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 420 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 422 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("this"))
				{
#line 424 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_THIS, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 425 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 427 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("true"))
				{
#line 429 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_TRUE, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 430 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 432 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("uint"))
				{
#line 434 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_UINT, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 435 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 437 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("void"))
				{
#line 439 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_VOID, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 440 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 442 "../../../Source/Core/TokenContainer.nll"
				break;
			}

			case 5:
			{
#line 446 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("break"))
				{
#line 448 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_BREAK, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 449 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 451 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("class"))
				{
#line 453 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_CLASS, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 454 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 456 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("const"))
				{
#line 458 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_CONST, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 459 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 461 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("false"))
				{
#line 463 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_FALSE, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 464 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 466 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("float"))
				{
#line 468 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_FLOAT, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 469 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 471 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("Int16"))
				{
#line 473 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_INT16, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 474 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 476 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("Int32"))
				{
#line 478 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_INT32, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 479 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 481 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("Uint8"))
				{
#line 483 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_UINT8, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 484 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 486 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("using"))
				{
#line 488 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_USING, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 489 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 491 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("while"))
				{
#line 493 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_WHILE, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 494 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 496 "../../../Source/Core/TokenContainer.nll"
				break;
			}

			case 6:
			{
#line 500 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("delete"))
				{
#line 502 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_DELETE, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 503 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 505 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("disown"))
				{
#line 507 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_DISOWN, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 508 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 510 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("double"))
				{
#line 512 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_DOUBLE, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 513 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 515 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("public"))
				{
#line 517 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_PUBLIC, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 518 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 520 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("return"))
				{
#line 522 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_RETURN, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 523 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 525 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("static"))
				{
#line 527 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_STATIC, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 528 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 530 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("string"))
				{
#line 532 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_STRING, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 533 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 535 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("switch"))
				{
#line 537 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_SWITCH, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 538 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 540 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("tthash"))
				{
#line 542 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_TTHASH, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 543 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 545 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("Uint16"))
				{
#line 547 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_UINT16, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 548 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 550 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("Uint32"))
				{
#line 552 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_UINT32, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 553 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 555 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("Uint64"))
				{
#line 557 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_UINT64, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 558 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 561 "../../../Source/Core/TokenContainer.nll"
				break;
			}

			case 7:
			{
#line 565 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("default"))
				{
#line 567 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_DEFAULT, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 568 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 570 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("private"))
				{
#line 572 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_PRIVATE, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 573 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 575 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("UniChar"))
				{
#line 577 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_UNICHAR, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 578 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 580 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("virtual"))
				{
#line 582 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_VIRTUAL, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 583 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 585 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("voidptr"))
				{
#line 587 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_VOIDPTR, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 588 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 590 "../../../Source/Core/TokenContainer.nll"
				break;
			}

			case 8:
			{
#line 594 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("continue"))
				{
#line 596 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_CONTINUE, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 597 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 599 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("delegate"))
				{
#line 601 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_DELEGATE, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 602 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 604 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("destruct"))
				{
#line 606 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_DESTRUCT, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 607 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 609 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("override"))
				{
#line 611 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_OVERRIDE, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 612 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 614 "../../../Source/Core/TokenContainer.nll"
				break;
			}

			case 9:
			{
#line 618 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("construct"))
				{
#line 620 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_CONSTRUCT, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 621 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 624 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("namespace"))
				{
#line 626 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_NAMESPACE, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 627 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 629 "../../../Source/Core/TokenContainer.nll"
				break;
			}

			case 10:
			{
#line 633 "../../../Source/Core/TokenContainer.nll"
				if (pParseDatum->m_sCurrentRead->IsEqual("disposable"))
				{
#line 635 "../../../Source/Core/TokenContainer.nll"
					PushToken(Token::Type::TOKEN_KEYWORD_DISPOSABLE, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, false);
#line 636 "../../../Source/Core/TokenContainer.nll"
					return;
				}
#line 638 "../../../Source/Core/TokenContainer.nll"
				break;
			}

		}
		{
			int i = 0;
			bool bFirstZero = false;
			bool bHex = false;
			int nLength = pParseDatum->m_sCurrentRead->GetLength();
#line 648 "../../../Source/Core/TokenContainer.nll"
			for (int hax = 0; i < nLength; i = i + 1)
			{
#line 650 "../../../Source/Core/TokenContainer.nll"
				hax++;
				int nChar = pParseDatum->m_sCurrentRead->GetChar(i);
#line 653 "../../../Source/Core/TokenContainer.nll"
				if (i == 0 && nChar == '0')
				{
#line 655 "../../../Source/Core/TokenContainer.nll"
					bFirstZero = true;
#line 656 "../../../Source/Core/TokenContainer.nll"
					continue;
				}
#line 659 "../../../Source/Core/TokenContainer.nll"
				if (i == 1 && bFirstZero && nChar == 'x')
				{
#line 661 "../../../Source/Core/TokenContainer.nll"
					bHex = true;
#line 662 "../../../Source/Core/TokenContainer.nll"
					continue;
				}
#line 665 "../../../Source/Core/TokenContainer.nll"
				if (bHex)
				{
#line 667 "../../../Source/Core/TokenContainer.nll"
					if (nChar >= '0' && nChar <= '9' || nChar >= 'A' && nChar <= 'F' || nChar >= 'a' && nChar <= 'f')
					{
#line 669 "../../../Source/Core/TokenContainer.nll"
						continue;
					}
				}
				else
				{
#line 674 "../../../Source/Core/TokenContainer.nll"
					if (nChar >= '0' && nChar <= '9' || nChar == '.')
					{
#line 676 "../../../Source/Core/TokenContainer.nll"
						continue;
					}
#line 679 "../../../Source/Core/TokenContainer.nll"
					if (i == nLength - 1 && nChar == 'f')
#line 680 "../../../Source/Core/TokenContainer.nll"
						continue;
				}
#line 683 "../../../Source/Core/TokenContainer.nll"
				break;
			}
#line 686 "../../../Source/Core/TokenContainer.nll"
			if (i == nLength)
			{
#line 688 "../../../Source/Core/TokenContainer.nll"
				PushToken(Token::Type::TOKEN_NUMBER, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, true);
#line 689 "../../../Source/Core/TokenContainer.nll"
				return;
			}
		}
#line 695 "../../../Source/Core/TokenContainer.nll"
		PushToken(Token::Type::TOKEN_IDENTIFIER, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, true);
	}

#line 698 "../../../Source/Core/TokenContainer.nll"
	void TokenContainer::PushToken(Token::Type eType, int nLine, int nColumn, ParseDatum* pParseDatum, bool bCopyString)
	{
		Token* pToken = new Token();
#line 701 "../../../Source/Core/TokenContainer.nll"
		pToken->m_eType = eType;
#line 702 "../../../Source/Core/TokenContainer.nll"
		pToken->m_sFileName = pParseDatum->m_sFileName;
#line 703 "../../../Source/Core/TokenContainer.nll"
		pToken->m_nLine = nLine;
#line 704 "../../../Source/Core/TokenContainer.nll"
		pToken->m_nColumn = nColumn;
#line 706 "../../../Source/Core/TokenContainer.nll"
		if (bCopyString)
#line 707 "../../../Source/Core/TokenContainer.nll"
			pToken->m_sValue = new InternalString(pParseDatum->m_sCurrentRead->GetExternalString());
#line 709 "../../../Source/Core/TokenContainer.nll"
		pParseDatum->ClearCurrentRead();
		NumbatLogic::Token* __3820032206 = pToken;
#line 711 "../../../Source/Core/TokenContainer.nll"
		pToken = 0;
#line 711 "../../../Source/Core/TokenContainer.nll"
		m_pTokenVector->PushBack(__3820032206);
		if (pToken) delete pToken;
	}

#line 714 "../../../Source/Core/TokenContainer.nll"
	void TokenContainer::ParseQuoted(ParseDatum* pParseDatum, unsigned short nQuoteChar)
	{
		bool bEscaping = false;
#line 724 "../../../Source/Core/TokenContainer.nll"
		while (true)
		{
			unsigned short nChar = ReadChar(pParseDatum, false);
#line 727 "../../../Source/Core/TokenContainer.nll"
			if (nChar == '\0')
			{
				Token::Type eType = Token::Type::TOKEN_CHAR_UNTERMINATED;
#line 731 "../../../Source/Core/TokenContainer.nll"
				if (nQuoteChar == '"')
#line 732 "../../../Source/Core/TokenContainer.nll"
					eType = Token::Type::TOKEN_STRING_UNTERMINATED;
#line 733 "../../../Source/Core/TokenContainer.nll"
				PushToken(eType, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, true);
#line 734 "../../../Source/Core/TokenContainer.nll"
				return;
			}
#line 737 "../../../Source/Core/TokenContainer.nll"
			pParseDatum->m_sCurrentRead->AppendChar(nChar);
#line 738 "../../../Source/Core/TokenContainer.nll"
			pParseDatum->m_nColumn = pParseDatum->m_nColumn + 1;
#line 740 "../../../Source/Core/TokenContainer.nll"
			if (nChar == nQuoteChar && !bEscaping)
			{
				Token::Type eType = Token::Type::TOKEN_CHAR;
#line 743 "../../../Source/Core/TokenContainer.nll"
				if (nQuoteChar == '"')
#line 744 "../../../Source/Core/TokenContainer.nll"
					eType = Token::Type::TOKEN_STRING;
#line 745 "../../../Source/Core/TokenContainer.nll"
				PushToken(eType, pParseDatum->m_nCurrentReadLine, pParseDatum->m_nCurrentReadColumn, pParseDatum, true);
#line 746 "../../../Source/Core/TokenContainer.nll"
				return;
			}
#line 749 "../../../Source/Core/TokenContainer.nll"
			if (bEscaping)
#line 750 "../../../Source/Core/TokenContainer.nll"
				bEscaping = false;
			else
#line 751 "../../../Source/Core/TokenContainer.nll"
				if (nChar == '\\')
				{
#line 753 "../../../Source/Core/TokenContainer.nll"
					bEscaping = true;
				}
		}
	}

#line 762 "../../../Source/Core/TokenContainer.nll"
	void TokenContainer::Stringify(InternalString* sOut)
	{
#line 764 "../../../Source/Core/TokenContainer.nll"
		for (int i = 0; i < m_pTokenVector->GetSize(); i++)
		{
			Token* pToken = m_pTokenVector->Get(i);
#line 767 "../../../Source/Core/TokenContainer.nll"
			sOut->Append(pToken->GetString());
		}
	}

#line 771 "../../../Source/Core/TokenContainer.nll"
	void TokenContainer::StripWhitespace()
	{
		int nIn = 0;
#line 774 "../../../Source/Core/TokenContainer.nll"
		while (nIn < m_pTokenVector->GetSize())
		{
			Token* pToken = m_pTokenVector->Get(nIn);
#line 777 "../../../Source/Core/TokenContainer.nll"
			if (pToken->m_eType == Token::Type::TOKEN_CARRIGE_RETURN || pToken->m_eType == Token::Type::TOKEN_NEW_LINE || pToken->m_eType == Token::Type::TOKEN_SPACE || pToken->m_eType == Token::Type::TOKEN_TAB)
			{
#line 782 "../../../Source/Core/TokenContainer.nll"
				m_pTokenVector->Erase(nIn);
#line 783 "../../../Source/Core/TokenContainer.nll"
				continue;
			}
#line 786 "../../../Source/Core/TokenContainer.nll"
			nIn++;
		}
	}

#line 790 "../../../Source/Core/TokenContainer.nll"
	Token* TokenContainer::Peek(OffsetDatum* pOffsetDatum)
	{
#line 792 "../../../Source/Core/TokenContainer.nll"
		if (pOffsetDatum->m_nOffset < m_pTokenVector->GetSize())
#line 793 "../../../Source/Core/TokenContainer.nll"
			return m_pTokenVector->Get(pOffsetDatum->m_nOffset);
#line 794 "../../../Source/Core/TokenContainer.nll"
		return 0;
	}

#line 797 "../../../Source/Core/TokenContainer.nll"
	Token* TokenContainer::PeekExpect(OffsetDatum* pOffsetDatum, Token::Type eType)
	{
		Token* pToken = Peek(pOffsetDatum);
#line 800 "../../../Source/Core/TokenContainer.nll"
		if (pToken == 0 || pToken->m_eType != eType)
#line 801 "../../../Source/Core/TokenContainer.nll"
			return 0;
#line 802 "../../../Source/Core/TokenContainer.nll"
		return pToken;
	}

#line 805 "../../../Source/Core/TokenContainer.nll"
	const char* TokenContainer::StringifyOffset(OffsetDatum* pOffsetDatum)
	{
		Token* pToken = 0;
#line 808 "../../../Source/Core/TokenContainer.nll"
		if (pOffsetDatum->m_nOffset < m_pTokenVector->GetSize())
#line 809 "../../../Source/Core/TokenContainer.nll"
			pToken = m_pTokenVector->Get(pOffsetDatum->m_nOffset);
#line 810 "../../../Source/Core/TokenContainer.nll"
		if (pToken == 0 && m_pTokenVector->GetSize() > 0)
#line 811 "../../../Source/Core/TokenContainer.nll"
			pToken = m_pTokenVector->Get(m_pTokenVector->GetSize() - 1);
#line 813 "../../../Source/Core/TokenContainer.nll"
		if (pToken == 0)
#line 814 "../../../Source/Core/TokenContainer.nll"
			return "unbeknownst:?:?";
#line 816 "../../../Source/Core/TokenContainer.nll"
		m_sTemp->Set(pToken->m_sFileName->GetExternalString());
#line 817 "../../../Source/Core/TokenContainer.nll"
		m_sTemp->Append(":");
#line 818 "../../../Source/Core/TokenContainer.nll"
		m_sTemp->AppendInt(pToken->m_nLine);
#line 819 "../../../Source/Core/TokenContainer.nll"
		m_sTemp->Append(":");
#line 820 "../../../Source/Core/TokenContainer.nll"
		m_sTemp->AppendInt(pToken->m_nColumn);
#line 821 "../../../Source/Core/TokenContainer.nll"
		m_sTemp->Append(" ");
#line 822 "../../../Source/Core/TokenContainer.nll"
		m_sTemp->Append(pToken->GetString());
#line 823 "../../../Source/Core/TokenContainer.nll"
		return m_sTemp->GetExternalString();
	}

#line 3 "../../../Source/Core/TokenContainer.nll"
	TokenContainer::~TokenContainer()
	{
		if (m_pTokenVector) delete m_pTokenVector;
		if (m_sTemp) delete m_sTemp;
	}

}

