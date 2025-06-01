#pragma once

#include "AST.hpp"

namespace NumberDuck
{
	namespace Secret
	{
		class AST;
		class Token;
		class EnumDeclValue;
		class TokenContainer;
		class OffsetDatum;
		class InternalString;
	}
}
namespace NumberDuck
{
	namespace Secret
	{
		class EnumDeclValue : public AST
		{
			public: AST* m_pForceValue;
			public: EnumDeclValue(Token* pFirstToken);
			public: static EnumDeclValue* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
			public: virtual AST* FindByName(const char* sxName, AST* pCallingChild);
			public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
			public: virtual ~EnumDeclValue();
		};
	}
}

