#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class RefExpr;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class OutputBuilder;
}
#line 1 "../../../Source/Core/AST/RefExpr.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/RefExpr.nll"
	class RefExpr : public AST
	{
#line 6 "../../../Source/Core/AST/RefExpr.nll"
		public: AST* m_pExpression;
#line 8 "../../../Source/Core/AST/RefExpr.nll"
		public: static RefExpr* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 36 "../../../Source/Core/AST/RefExpr.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 52 "../../../Source/Core/AST/RefExpr.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 4 "../../../Source/Core/AST/RefExpr.nll"
		public: RefExpr();
	};
}

