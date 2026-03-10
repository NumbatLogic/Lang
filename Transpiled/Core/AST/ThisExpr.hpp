#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class ThisExpr;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class OutputBuilder;
}
#line 0 "../../../Source/Core/AST/ThisExpr.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/ThisExpr.nll"
	class ThisExpr : public AST
	{
#line 5 "../../../Source/Core/AST/ThisExpr.nll"
		public: static ThisExpr* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 23 "../../../Source/Core/AST/ThisExpr.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 45 "../../../Source/Core/AST/ThisExpr.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

