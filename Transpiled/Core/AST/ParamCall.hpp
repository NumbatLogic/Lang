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
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/ParamCall.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/ParamCall.nll"
	class ParamCall : public AST
	{
		public: static ParamCall* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 59 "/home/cliffya/git/Lang/Source/Core/AST/ParamCall.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

