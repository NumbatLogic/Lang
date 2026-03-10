#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class ExpressionStmt;
	class TokenContainer;
	class OffsetDatum;
	class OutputBuilder;
}
#line 0 "../../../Source/Core/AST/ExpressionStmt.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/ExpressionStmt.nll"
	class ExpressionStmt : public AST
	{
#line 5 "../../../Source/Core/AST/ExpressionStmt.nll"
		public: AST* m_pExpression;
#line 7 "../../../Source/Core/AST/ExpressionStmt.nll"
		public: ExpressionStmt();
#line 13 "../../../Source/Core/AST/ExpressionStmt.nll"
		public: static ExpressionStmt* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 35 "../../../Source/Core/AST/ExpressionStmt.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

