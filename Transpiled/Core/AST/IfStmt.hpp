#pragma once

#include "AST.hpp"

namespace NumberDuck
{
	namespace Secret
	{
		class IfStmt;
		class TokenContainer;
		class OffsetDatum;
		class InternalString;
	}
}
namespace NumberDuck
{
	namespace Secret
	{
		class IfStmt : public AST
		{
			public: IfStmt();
			public: static IfStmt* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
			public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
		};
	}
}

