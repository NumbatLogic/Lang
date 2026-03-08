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
		public: AST* m_pExpression;
		public: DeleteStmt();
		public: static DeleteStmt* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* out);
	};
}

