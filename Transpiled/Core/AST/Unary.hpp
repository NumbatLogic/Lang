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
	class OutputBuilder;
}
#line 0 "../../../Source/Core/AST/Unary.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/Unary.nll"
	class Unary : public AST
	{
		public: AST* m_pExpression;
#line 7 "../../../Source/Core/AST/Unary.nll"
		public: static Unary* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 30 "../../../Source/Core/AST/Unary.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 47 "../../../Source/Core/AST/Unary.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 3 "../../../Source/Core/AST/Unary.nll"
		public: Unary();
	};
}

