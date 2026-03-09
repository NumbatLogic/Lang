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
#line 1 "../../../Source/Core/AST/ExpressionStmt.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/ExpressionStmt.nll"
	class ExpressionStmt : public AST
	{
#line 6 "../../../Source/Core/AST/ExpressionStmt.nll"
		public: AST* m_pExpression;
#line 8 "../../../Source/Core/AST/ExpressionStmt.nll"
		public: ExpressionStmt();
#line 14 "../../../Source/Core/AST/ExpressionStmt.nll"
		public: static ExpressionStmt* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 36 "../../../Source/Core/AST/ExpressionStmt.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

