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
#line 0 "../../../Source/Core/AST/StringExpr.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/StringExpr.nll"
	class StringExpr : public AST
	{
		public: static StringExpr* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 18 "../../../Source/Core/AST/StringExpr.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 23 "../../../Source/Core/AST/StringExpr.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

