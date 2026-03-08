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
		public: ContinueStmt();
		public: static ContinueStmt* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* out);
	};
}

