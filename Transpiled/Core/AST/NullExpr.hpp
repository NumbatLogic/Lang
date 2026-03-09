#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class NullExpr;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class OutputBuilder;
}
#line 1 "../../../Source/Core/AST/NullExpr.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/NullExpr.nll"
	class NullExpr : public AST
	{
#line 6 "../../../Source/Core/AST/NullExpr.nll"
		public: NullExpr();
#line 11 "../../../Source/Core/AST/NullExpr.nll"
		public: static NullExpr* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 27 "../../../Source/Core/AST/NullExpr.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 32 "../../../Source/Core/AST/NullExpr.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

