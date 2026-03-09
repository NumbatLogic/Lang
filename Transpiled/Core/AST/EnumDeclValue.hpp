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
#line 1 "../../../Source/Core/AST/EnumDeclValue.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/EnumDeclValue.nll"
	class EnumDeclValue : public AST
	{
#line 6 "../../../Source/Core/AST/EnumDeclValue.nll"
		public: AST* m_pForceValue;
#line 8 "../../../Source/Core/AST/EnumDeclValue.nll"
		public: EnumDeclValue(Token* pFirstToken);
#line 14 "../../../Source/Core/AST/EnumDeclValue.nll"
		public: static EnumDeclValue* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 44 "../../../Source/Core/AST/EnumDeclValue.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 4 "../../../Source/Core/AST/EnumDeclValue.nll"
		public: virtual ~EnumDeclValue();
	};
}

