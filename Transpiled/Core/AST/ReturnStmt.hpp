#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class ReturnStmt;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class OutputBuilder;
}
#line 1 "../../../Source/Core/AST/ReturnStmt.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/ReturnStmt.nll"
	class ReturnStmt : public AST
	{
#line 6 "../../../Source/Core/AST/ReturnStmt.nll"
		public: AST* m_pExpression;
#line 8 "../../../Source/Core/AST/ReturnStmt.nll"
		public: ReturnStmt();
#line 14 "../../../Source/Core/AST/ReturnStmt.nll"
		public: static ReturnStmt* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 41 "../../../Source/Core/AST/ReturnStmt.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 47 "../../../Source/Core/AST/ReturnStmt.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

