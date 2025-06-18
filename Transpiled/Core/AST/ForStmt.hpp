#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class ForStmt;
	class TokenContainer;
	class OffsetDatum;
	class InternalString;
}
namespace NumbatLogic
{
	class ForStmt : public AST
	{
		public: ForStmt();
		public: static ForStmt* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
	};
}

