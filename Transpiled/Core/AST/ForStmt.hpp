#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class ForStmt;
	class TokenContainer;
	class OffsetDatum;
	class AST;
	class OutputBuilder;
}
#line 1 "../../../Source/Core/AST/ForStmt.nll"
namespace NumbatLogic
{
	class ForStmt : public AST
	{
		public: ForStmt();
		public: static ForStmt* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* out);
	};
}

