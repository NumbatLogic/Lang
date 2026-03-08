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
#line 0 "../../../Source/Core/AST/TTHashExpr.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/TTHashExpr.nll"
	class TTHashExpr : public AST
	{
		protected: StringExpr* m_pStringExpr;
		public: TTHashExpr();
		public: static TTHashExpr* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* out);
	};
}

