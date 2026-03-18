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
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/NullExpr.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/NullExpr.nll"
	class NullExpr : public AST
	{
		public: NullExpr();
#line 10 "/home/cliffya/git/Lang/Source/Core/AST/NullExpr.nll"
		public: static NullExpr* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 26 "/home/cliffya/git/Lang/Source/Core/AST/NullExpr.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 31 "/home/cliffya/git/Lang/Source/Core/AST/NullExpr.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

