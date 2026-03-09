#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class Token;
	class NumberExpr;
	class TokenContainer;
	class OffsetDatum;
	class AST;
	class Validator;
	class OperatorExpr;
	class OutputBuilder;
}
#line 1 "../../../Source/Core/AST/NumberExpr.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/NumberExpr.nll"
	class NumberExpr : public AST
	{
#line 6 "../../../Source/Core/AST/NumberExpr.nll"
		public: NumberExpr(Token* pFirstToken);
#line 12 "../../../Source/Core/AST/NumberExpr.nll"
		public: static NumberExpr* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 22 "../../../Source/Core/AST/NumberExpr.nll"
		public: virtual AST* BaseClone();
#line 29 "../../../Source/Core/AST/NumberExpr.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 34 "../../../Source/Core/AST/NumberExpr.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

