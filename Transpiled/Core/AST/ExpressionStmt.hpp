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
		public: AST* m_pExpression;
		public: ExpressionStmt();
		public: static ExpressionStmt* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* out);
	};
}

