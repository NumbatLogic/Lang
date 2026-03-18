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
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/RefExpr.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/RefExpr.nll"
	class RefExpr : public AST
	{
		public: AST* m_pExpression;
#line 7 "/home/cliffya/git/Lang/Source/Core/AST/RefExpr.nll"
		public: static RefExpr* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 35 "/home/cliffya/git/Lang/Source/Core/AST/RefExpr.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 51 "/home/cliffya/git/Lang/Source/Core/AST/RefExpr.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/RefExpr.nll"
		public: RefExpr();
	};
}

