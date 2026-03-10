#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class BoolExpr;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class OutputBuilder;
}
#line 0 "../../../Source/Core/AST/BoolExpr.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/BoolExpr.nll"
	class BoolExpr : public AST
	{
#line 5 "../../../Source/Core/AST/BoolExpr.nll"
		public: static BoolExpr* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 19 "../../../Source/Core/AST/BoolExpr.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 24 "../../../Source/Core/AST/BoolExpr.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

