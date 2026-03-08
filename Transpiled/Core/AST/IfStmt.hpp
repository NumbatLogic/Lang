#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class IfStmt;
	class TokenContainer;
	class OffsetDatum;
	class AST;
	class Scope;
	class OutputBuilder;
}
#line 1 "../../../Source/Core/AST/IfStmt.nll"
namespace NumbatLogic
{
	class IfStmt : public AST
	{
		public: IfStmt();
		public: static IfStmt* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* out);
	};
}

