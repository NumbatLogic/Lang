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
#line 5 "../../../Source/Core/AST/EnumDeclValue.nll"
		public: AST* m_pForceValue;
#line 7 "../../../Source/Core/AST/EnumDeclValue.nll"
		public: EnumDeclValue(Token* pFirstToken);
#line 13 "../../../Source/Core/AST/EnumDeclValue.nll"
		public: static EnumDeclValue* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 43 "../../../Source/Core/AST/EnumDeclValue.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 3 "../../../Source/Core/AST/EnumDeclValue.nll"
		public: virtual ~EnumDeclValue();
	};
}

