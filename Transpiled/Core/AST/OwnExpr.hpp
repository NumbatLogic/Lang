#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class OwnExpr;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class OutputBuilder;
}
#line 1 "../../../Source/Core/AST/OwnExpr.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/OwnExpr.nll"
	class OwnExpr : public AST
	{
#line 6 "../../../Source/Core/AST/OwnExpr.nll"
		public: AST* m_pExpression;
#line 8 "../../../Source/Core/AST/OwnExpr.nll"
		public: static OwnExpr* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 36 "../../../Source/Core/AST/OwnExpr.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 64 "../../../Source/Core/AST/OwnExpr.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 4 "../../../Source/Core/AST/OwnExpr.nll"
		public: OwnExpr();
	};
}

