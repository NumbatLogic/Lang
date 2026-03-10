#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class TrinaryExpr;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class OutputBuilder;
}
#line 0 "../../../Source/Core/AST/TrinaryExpr.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/TrinaryExpr.nll"
	class TrinaryExpr : public AST
	{
#line 5 "../../../Source/Core/AST/TrinaryExpr.nll"
		public: AST* m_pFirstExpression;
#line 6 "../../../Source/Core/AST/TrinaryExpr.nll"
		public: AST* m_pSecondExpression;
#line 7 "../../../Source/Core/AST/TrinaryExpr.nll"
		public: AST* m_pThirdExpression;
#line 9 "../../../Source/Core/AST/TrinaryExpr.nll"
		public: TrinaryExpr();
#line 14 "../../../Source/Core/AST/TrinaryExpr.nll"
		public: static TrinaryExpr* Create(AST* pFirstExpressionTransition, TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 57 "../../../Source/Core/AST/TrinaryExpr.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 76 "../../../Source/Core/AST/TrinaryExpr.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

