#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class CharExpr;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class OutputBuilder;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/CharExpr.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/CharExpr.nll"
	class CharExpr : public AST
	{
		public: static CharExpr* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 18 "/home/cliffya/git/Lang/Source/Core/AST/CharExpr.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 23 "/home/cliffya/git/Lang/Source/Core/AST/CharExpr.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

