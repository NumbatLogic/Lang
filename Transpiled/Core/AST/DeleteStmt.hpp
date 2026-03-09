#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class DeleteStmt;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class OutputBuilder;
}
#line 1 "../../../Source/Core/AST/DeleteStmt.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/DeleteStmt.nll"
	class DeleteStmt : public AST
	{
#line 6 "../../../Source/Core/AST/DeleteStmt.nll"
		public: AST* m_pExpression;
#line 8 "../../../Source/Core/AST/DeleteStmt.nll"
		public: DeleteStmt();
#line 14 "../../../Source/Core/AST/DeleteStmt.nll"
		public: static DeleteStmt* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 42 "../../../Source/Core/AST/DeleteStmt.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 56 "../../../Source/Core/AST/DeleteStmt.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

