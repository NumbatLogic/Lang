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
#line 1 "../../../Source/Core/AST/FunctionCall.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/FunctionCall.nll"
	class FunctionCall : public AST
	{
#line 6 "../../../Source/Core/AST/FunctionCall.nll"
		public: const char* m_sMangledName;
#line 7 "../../../Source/Core/AST/FunctionCall.nll"
		public: ParamCall* m_pParamCall;
#line 9 "../../../Source/Core/AST/FunctionCall.nll"
		public: static FunctionCall* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 45 "../../../Source/Core/AST/FunctionCall.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 554 "../../../Source/Core/AST/FunctionCall.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 4 "../../../Source/Core/AST/FunctionCall.nll"
		public: FunctionCall();
	};
}

