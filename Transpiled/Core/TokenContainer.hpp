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
#line 1 "../../../Source/Core/TokenContainer.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/TokenContainer.nll"
	class TokenContainer
	{
#line 6 "../../../Source/Core/TokenContainer.nll"
		public: OwnedVector<Token*>* m_pTokenVector;
#line 7 "../../../Source/Core/TokenContainer.nll"
		protected: InternalString* m_sTemp;
#line 9 "../../../Source/Core/TokenContainer.nll"
		public: TokenContainer();
#line 15 "../../../Source/Core/TokenContainer.nll"
		public: unsigned short ReadChar(ParseDatum* pParseDatum, bool bPeak);
#line 27 "../../../Source/Core/TokenContainer.nll"
		public: bool Tokenize(const char* sInput, InternalString* sFileName, OwnedVector<InternalString*>* sDefineVector);
#line 261 "../../../Source/Core/TokenContainer.nll"
		protected: void ProcessCurrentRead(ParseDatum* pParseDatum);
#line 699 "../../../Source/Core/TokenContainer.nll"
		protected: void PushToken(Token::Type eType, int nLine, int nColumn, ParseDatum* pParseDatum, bool bCopyString);
#line 715 "../../../Source/Core/TokenContainer.nll"
		protected: void ParseQuoted(ParseDatum* pParseDatum, unsigned short nQuoteChar);
#line 763 "../../../Source/Core/TokenContainer.nll"
		public: void Stringify(InternalString* sOut);
#line 772 "../../../Source/Core/TokenContainer.nll"
		public: void StripWhitespace();
#line 791 "../../../Source/Core/TokenContainer.nll"
		public: Token* Peek(OffsetDatum* pOffsetDatum);
#line 798 "../../../Source/Core/TokenContainer.nll"
		public: Token* PeekExpect(OffsetDatum* pOffsetDatum, Token::Type eType);
#line 806 "../../../Source/Core/TokenContainer.nll"
		public: const char* StringifyOffset(OffsetDatum* pOffsetDatum);
#line 4 "../../../Source/Core/TokenContainer.nll"
		public: virtual ~TokenContainer();
	};
}

