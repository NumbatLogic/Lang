#pragma once

#include "AST.hpp"

namespace NumberDuck
{
	namespace Secret
	{
		class ParamCall;
		class TokenContainer;
		class OffsetDatum;
		class InternalString;
	}
}
namespace NumberDuck
{
	namespace Secret
	{
		class ParamCall : public AST
		{
			public: static ParamCall* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
			public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
		};
	}
}

