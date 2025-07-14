#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class AST;
	class ReturnStmt;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class InternalString;
}
namespace NumbatLogic
{
	class ReturnStmt : public AST
	{
		public: AST* m_pExpression;
		public: ReturnStmt();
		public: static ReturnStmt* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
	};
}

