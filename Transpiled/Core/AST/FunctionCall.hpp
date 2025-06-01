#pragma once

#include "AST.hpp"

namespace NumberDuck
{
	namespace Secret
	{
		class ParamCall;
		class FunctionCall;
		class TokenContainer;
		class OffsetDatum;
		class Validator;
		class OperatorExpr;
		class InternalString;
	}
}
namespace NumberDuck
{
	namespace Secret
	{
		class FunctionCall : public AST
		{
			public: const char* m_sMangledName;
			public: ParamCall* m_pParamCall;
			public: static FunctionCall* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
			public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
			public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
			public: FunctionCall();
		};
	}
}

