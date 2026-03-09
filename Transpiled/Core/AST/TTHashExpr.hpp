#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class StringExpr;
	class TTHashExpr;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class OutputBuilder;
}
#line 1 "../../../Source/Core/AST/TTHashExpr.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/TTHashExpr.nll"
	class TTHashExpr : public AST
	{
#line 6 "../../../Source/Core/AST/TTHashExpr.nll"
		protected: StringExpr* m_pStringExpr;
#line 8 "../../../Source/Core/AST/TTHashExpr.nll"
		public: TTHashExpr();
#line 13 "../../../Source/Core/AST/TTHashExpr.nll"
		public: static TTHashExpr* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 61 "../../../Source/Core/AST/TTHashExpr.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 66 "../../../Source/Core/AST/TTHashExpr.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

