#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class Unary;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class InternalString;
}
namespace NumbatLogic
{
	class Unary : public AST
	{
		public: AST* m_pExpression;
		public: static Unary* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
		public: Unary();
	};
}

