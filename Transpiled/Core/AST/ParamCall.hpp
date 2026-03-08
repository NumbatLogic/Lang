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
#line 0 "../../../Source/Core/AST/ParamCall.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/ParamCall.nll"
	class ParamCall : public AST
	{
		public: static ParamCall* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* out);
	};
}

