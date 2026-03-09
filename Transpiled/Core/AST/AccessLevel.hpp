#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class AccessLevel;
	class TokenContainer;
	class OffsetDatum;
	class OutputBuilder;
}
#line 1 "../../../Source/Core/AST/AccessLevel.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/AccessLevel.nll"
	class AccessLevel : public AST
	{
#line 6 "../../../Source/Core/AST/AccessLevel.nll"
		public: static AccessLevel* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 24 "../../../Source/Core/AST/AccessLevel.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

