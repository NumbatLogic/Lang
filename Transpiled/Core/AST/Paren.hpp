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
#line 1 "../../../Source/Core/AST/Paren.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/Paren.nll"
	class Paren : public AST
	{
#line 6 "../../../Source/Core/AST/Paren.nll"
		public: static Paren* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 34 "../../../Source/Core/AST/Paren.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 45 "../../../Source/Core/AST/Paren.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

