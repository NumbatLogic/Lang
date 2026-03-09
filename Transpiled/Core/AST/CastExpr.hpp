#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class TypeRef;
	class ParamCall;
	class CastExpr;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class OutputBuilder;
}
#line 1 "../../../Source/Core/AST/CastExpr.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/CastExpr.nll"
	class CastExpr : public AST
	{
#line 6 "../../../Source/Core/AST/CastExpr.nll"
		public: TypeRef* m_pTypeRef;
#line 7 "../../../Source/Core/AST/CastExpr.nll"
		public: ParamCall* m_pParamCall;
#line 9 "../../../Source/Core/AST/CastExpr.nll"
		public: CastExpr();
#line 14 "../../../Source/Core/AST/CastExpr.nll"
		public: static CastExpr* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 53 "../../../Source/Core/AST/CastExpr.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 98 "../../../Source/Core/AST/CastExpr.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

