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
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/BoolExpr.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/BoolExpr.nll"
	class BoolExpr : public AST
	{
		public: static BoolExpr* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 19 "/home/cliffya/git/Lang/Source/Core/AST/BoolExpr.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 24 "/home/cliffya/git/Lang/Source/Core/AST/BoolExpr.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

