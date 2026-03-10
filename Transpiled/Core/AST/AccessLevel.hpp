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
#line 0 "../../../Source/Core/AST/AccessLevel.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/AccessLevel.nll"
	class AccessLevel : public AST
	{
#line 5 "../../../Source/Core/AST/AccessLevel.nll"
		public: static AccessLevel* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 23 "../../../Source/Core/AST/AccessLevel.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

