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
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
	class TrinaryExpr : public AST
	{
		public: AST* m_pFirstExpression;
		public: AST* m_pSecondExpression;
		public: AST* m_pThirdExpression;
#line 9 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
		public: TrinaryExpr();
#line 14 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
		public: static TrinaryExpr* Create(AST* pFirstExpressionTransition, TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 57 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 76 "/home/cliffya/git/Lang/Source/Core/AST/TrinaryExpr.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

