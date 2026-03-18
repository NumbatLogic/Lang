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
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
	class ReturnStmt : public AST
	{
		public: AST* m_pExpression;
#line 7 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
		public: ReturnStmt();
#line 13 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
		public: static ReturnStmt* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 40 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 46 "/home/cliffya/git/Lang/Source/Core/AST/ReturnStmt.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

