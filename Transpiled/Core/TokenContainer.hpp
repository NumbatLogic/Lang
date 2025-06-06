#pragma once

#include "../../../LangTranspiled/Shared/Vector/OwnedVector.hpp"
#include "Token.hpp"

namespace NumberDuck
{
	namespace Secret
	{
		class Token;
		class InternalString;
		class ParseDatum;
		class OffsetDatum;
	}
}
namespace NumberDuck
{
	namespace Secret
	{
		class TokenContainer
		{
			public: OwnedVector<Token*>* m_pTokenVector;
			protected: InternalString* m_sTemp;
			public: TokenContainer();
			public: unsigned short ReadChar(ParseDatum* pParseDatum, bool bPeak);
			public: bool Tokenize(const char* sInput, InternalString* sFileName, OwnedVector<InternalString*>* sDefineVector);
			protected: void ProcessCurrentRead(ParseDatum* pParseDatum);
			protected: void PushToken(Token::Type eType, int nLine, int nColumn, ParseDatum* pParseDatum, bool bCopyString);
			protected: void ParseQuoted(ParseDatum* pParseDatum, unsigned short nQuoteChar);
			public: void Stringify(InternalString* sOut);
			public: void StripWhitespace();
			public: Token* Peek(OffsetDatum* pOffsetDatum);
			public: Token* PeekExpect(OffsetDatum* pOffsetDatum, Token::Type eType);
			public: const char* StringifyOffset(OffsetDatum* pOffsetDatum);
			public: virtual ~TokenContainer();
		};
	}
}

