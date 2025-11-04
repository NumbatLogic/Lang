#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class RefExpr;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class InternalString;
}
namespace NumbatLogic
{
	class RefExpr : public AST
	{
		public: AST* m_pExpression;
		public: static RefExpr* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
		public: RefExpr();
	};
}

