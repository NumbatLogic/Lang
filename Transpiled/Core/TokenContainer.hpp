#pragma once

#include "../../../LangShared/Transpiled/Vector/OwnedVector.hpp"
#include "Token.hpp"

namespace NumbatLogic
{
	template <class T>
	class OwnedVector;
	class Token;
	class InternalString;
	class ParseDatum;
	class OffsetDatum;
}
#line 0 "../../../Source/Core/TokenContainer.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/TokenContainer.nll"
	class TokenContainer
	{
		public: OwnedVector<Token*>* m_pTokenVector;
		protected: InternalString* m_sTemp;
#line 8 "../../../Source/Core/TokenContainer.nll"
		public: TokenContainer();
#line 14 "../../../Source/Core/TokenContainer.nll"
		public: unsigned short ReadChar(ParseDatum* pParseDatum, bool bPeak);
#line 26 "../../../Source/Core/TokenContainer.nll"
		public: bool Tokenize(const char* sInput, InternalString* sFileName, OwnedVector<InternalString*>* sDefineVector);
#line 260 "../../../Source/Core/TokenContainer.nll"
		protected: void ProcessCurrentRead(ParseDatum* pParseDatum);
#line 698 "../../../Source/Core/TokenContainer.nll"
		protected: void PushToken(Token::Type eType, int nLine, int nColumn, ParseDatum* pParseDatum, bool bCopyString);
#line 714 "../../../Source/Core/TokenContainer.nll"
		protected: void ParseQuoted(ParseDatum* pParseDatum, unsigned short nQuoteChar);
#line 762 "../../../Source/Core/TokenContainer.nll"
		public: void Stringify(InternalString* sOut);
#line 771 "../../../Source/Core/TokenContainer.nll"
		public: void StripWhitespace();
#line 790 "../../../Source/Core/TokenContainer.nll"
		public: Token* Peek(OffsetDatum* pOffsetDatum);
#line 797 "../../../Source/Core/TokenContainer.nll"
		public: Token* PeekExpect(OffsetDatum* pOffsetDatum, Token::Type eType);
#line 805 "../../../Source/Core/TokenContainer.nll"
		public: const char* StringifyOffset(OffsetDatum* pOffsetDatum);
#line 3 "../../../Source/Core/TokenContainer.nll"
		public: virtual ~TokenContainer();
	};
}

