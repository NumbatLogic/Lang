#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class OwnExpr;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class OutputBuilder;
}
#line 0 "../../../Source/Core/AST/OwnExpr.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/OwnExpr.nll"
	class OwnExpr : public AST
	{
		public: AST* m_pExpression;
		public: static OwnExpr* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* out);
		public: OwnExpr();
	};
}

