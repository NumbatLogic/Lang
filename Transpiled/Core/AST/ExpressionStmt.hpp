#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class ExpressionStmt;
	class TokenContainer;
	class OffsetDatum;
	class InternalString;
}
namespace NumbatLogic
{
	class ExpressionStmt : public AST
	{
		public: AST* m_pExpression;
		public: ExpressionStmt();
		public: static ExpressionStmt* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
	};
}

