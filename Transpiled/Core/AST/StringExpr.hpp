#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class StringExpr;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class OutputBuilder;
}
#line 1 "../../../Source/Core/AST/StringExpr.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/StringExpr.nll"
	class StringExpr : public AST
	{
#line 6 "../../../Source/Core/AST/StringExpr.nll"
		public: static StringExpr* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 19 "../../../Source/Core/AST/StringExpr.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 24 "../../../Source/Core/AST/StringExpr.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

