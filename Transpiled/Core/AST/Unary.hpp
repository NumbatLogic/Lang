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
#line 1 "../../../Source/Core/AST/Unary.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/Unary.nll"
	class Unary : public AST
	{
#line 6 "../../../Source/Core/AST/Unary.nll"
		public: AST* m_pExpression;
#line 8 "../../../Source/Core/AST/Unary.nll"
		public: static Unary* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 31 "../../../Source/Core/AST/Unary.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 48 "../../../Source/Core/AST/Unary.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 4 "../../../Source/Core/AST/Unary.nll"
		public: Unary();
	};
}

