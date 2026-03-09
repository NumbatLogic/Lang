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
#line 1 "../../../Source/Core/AST/GenericTypeDecl.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/GenericTypeDecl.nll"
	class GenericTypeDecl : public AST
	{
#line 6 "../../../Source/Core/AST/GenericTypeDecl.nll"
		public: static GenericTypeDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 24 "../../../Source/Core/AST/GenericTypeDecl.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

