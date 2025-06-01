#pragma once

#include "AST.hpp"

namespace NumberDuck
{
	namespace Secret
	{
		class AccessLevel;
		class TokenContainer;
		class OffsetDatum;
		class InternalString;
	}
}
namespace NumberDuck
{
	namespace Secret
	{
		class AccessLevel : public AST
		{
			public: static AccessLevel* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
			public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
		};
	}
}

