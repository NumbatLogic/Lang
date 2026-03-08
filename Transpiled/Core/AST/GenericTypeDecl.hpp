#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class GenericTypeDecl;
	class TokenContainer;
	class OffsetDatum;
	class OutputBuilder;
}
#line 0 "../../../Source/Core/AST/GenericTypeDecl.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/GenericTypeDecl.nll"
	class GenericTypeDecl : public AST
	{
		public: static GenericTypeDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* out);
	};
}

