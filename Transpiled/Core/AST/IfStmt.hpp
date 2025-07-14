#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class IfStmt;
	class TokenContainer;
	class OffsetDatum;
	class InternalString;
}
namespace NumbatLogic
{
	class IfStmt : public AST
	{
		public: IfStmt();
		public: static IfStmt* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
	};
}

