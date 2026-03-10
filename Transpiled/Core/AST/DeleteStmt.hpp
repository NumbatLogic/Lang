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
#line 0 "../../../Source/Core/AST/DeleteStmt.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/DeleteStmt.nll"
	class DeleteStmt : public AST
	{
#line 5 "../../../Source/Core/AST/DeleteStmt.nll"
		public: AST* m_pExpression;
#line 7 "../../../Source/Core/AST/DeleteStmt.nll"
		public: DeleteStmt();
#line 13 "../../../Source/Core/AST/DeleteStmt.nll"
		public: static DeleteStmt* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 41 "../../../Source/Core/AST/DeleteStmt.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 55 "../../../Source/Core/AST/DeleteStmt.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

