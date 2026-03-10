#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class ContinueStmt;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class OutputBuilder;
}
#line 0 "../../../Source/Core/AST/ContinueStmt.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/ContinueStmt.nll"
	class ContinueStmt : public AST
	{
#line 5 "../../../Source/Core/AST/ContinueStmt.nll"
		public: ContinueStmt();
#line 10 "../../../Source/Core/AST/ContinueStmt.nll"
		public: static ContinueStmt* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 36 "../../../Source/Core/AST/ContinueStmt.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 42 "../../../Source/Core/AST/ContinueStmt.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

