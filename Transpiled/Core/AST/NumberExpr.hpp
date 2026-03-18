#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class Token;
	class NumberExpr;
	class TokenContainer;
	class OffsetDatum;
	class AST;
	class Validator;
	class OperatorExpr;
	class OutputBuilder;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/NumberExpr.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/NumberExpr.nll"
	class NumberExpr : public AST
	{
		public: NumberExpr(Token* pFirstToken);
#line 11 "/home/cliffya/git/Lang/Source/Core/AST/NumberExpr.nll"
		public: static NumberExpr* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 21 "/home/cliffya/git/Lang/Source/Core/AST/NumberExpr.nll"
		public: virtual AST* BaseClone();
#line 28 "/home/cliffya/git/Lang/Source/Core/AST/NumberExpr.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 33 "/home/cliffya/git/Lang/Source/Core/AST/NumberExpr.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

