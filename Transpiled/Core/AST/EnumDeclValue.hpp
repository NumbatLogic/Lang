#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class Token;
	class EnumDeclValue;
	class TokenContainer;
	class OffsetDatum;
	class OutputBuilder;
}
#line 0 "../../../Source/Core/AST/EnumDeclValue.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/EnumDeclValue.nll"
	class EnumDeclValue : public AST
	{
		public: AST* m_pForceValue;
		public: EnumDeclValue(Token* pFirstToken);
		public: static EnumDeclValue* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* out);
		public: virtual ~EnumDeclValue();
	};
}

