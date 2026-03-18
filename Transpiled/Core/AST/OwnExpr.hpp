#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class OwnExpr;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class OutputBuilder;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/OwnExpr.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/OwnExpr.nll"
	class OwnExpr : public AST
	{
		public: AST* m_pExpression;
#line 7 "/home/cliffya/git/Lang/Source/Core/AST/OwnExpr.nll"
		public: static OwnExpr* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 35 "/home/cliffya/git/Lang/Source/Core/AST/OwnExpr.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 63 "/home/cliffya/git/Lang/Source/Core/AST/OwnExpr.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/OwnExpr.nll"
		public: OwnExpr();
	};
}

