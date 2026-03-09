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
#line 1 "../../../Source/Core/AST/BoolExpr.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/BoolExpr.nll"
	class BoolExpr : public AST
	{
#line 6 "../../../Source/Core/AST/BoolExpr.nll"
		public: static BoolExpr* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 20 "../../../Source/Core/AST/BoolExpr.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 25 "../../../Source/Core/AST/BoolExpr.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

