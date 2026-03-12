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
#line 0 "../../../Source/Core/AST/ForStmt.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/ForStmt.nll"
	class ForStmt : public AST
	{
		public: ForStmt();
#line 11 "../../../Source/Core/AST/ForStmt.nll"
		public: static ForStmt* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 107 "../../../Source/Core/AST/ForStmt.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

