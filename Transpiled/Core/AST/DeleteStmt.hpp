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
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/DeleteStmt.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/DeleteStmt.nll"
	class DeleteStmt : public AST
	{
		public: AST* m_pExpression;
#line 7 "/home/cliffya/git/Lang/Source/Core/AST/DeleteStmt.nll"
		public: DeleteStmt();
#line 13 "/home/cliffya/git/Lang/Source/Core/AST/DeleteStmt.nll"
		public: static DeleteStmt* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 41 "/home/cliffya/git/Lang/Source/Core/AST/DeleteStmt.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 55 "/home/cliffya/git/Lang/Source/Core/AST/DeleteStmt.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

