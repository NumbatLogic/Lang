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
#line 4 "../../../Source/Core/AST/ForStmt.nll"
	class ForStmt : public AST
	{
#line 6 "../../../Source/Core/AST/ForStmt.nll"
		public: ForStmt();
#line 12 "../../../Source/Core/AST/ForStmt.nll"
		public: static ForStmt* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 108 "../../../Source/Core/AST/ForStmt.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

