#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class GenericTypeDecl;
	class TokenContainer;
	class OffsetDatum;
	class InternalString;
}
namespace NumbatLogic
{
	class GenericTypeDecl : public AST
	{
		public: static GenericTypeDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
	};
}

