#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class Paren;
	class TokenContainer;
	class OffsetDatum;
	class AST;
	class Validator;
	class OperatorExpr;
	class OutputBuilder;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/Paren.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/Paren.nll"
	class Paren : public AST
	{
		public: static Paren* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 33 "/home/cliffya/git/Lang/Source/Core/AST/Paren.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 44 "/home/cliffya/git/Lang/Source/Core/AST/Paren.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

