#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class ParamCall;
	class TokenContainer;
	class OffsetDatum;
	class AST;
	class OutputBuilder;
}
#line 1 "../../../Source/Core/AST/ParamCall.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/ParamCall.nll"
	class ParamCall : public AST
	{
#line 6 "../../../Source/Core/AST/ParamCall.nll"
		public: static ParamCall* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 60 "../../../Source/Core/AST/ParamCall.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

