#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class ParamCall;
	class FunctionCall;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class Symbol;
	class ValueType;
	class OutputBuilder;
}
#line 0 "../../../Source/Core/AST/FunctionCall.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/FunctionCall.nll"
	class FunctionCall : public AST
	{
		public: const char* m_sMangledName;
		public: ParamCall* m_pParamCall;
#line 8 "../../../Source/Core/AST/FunctionCall.nll"
		public: static FunctionCall* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 44 "../../../Source/Core/AST/FunctionCall.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 549 "../../../Source/Core/AST/FunctionCall.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 3 "../../../Source/Core/AST/FunctionCall.nll"
		public: FunctionCall();
	};
}

