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
#line 4 "../../../Source/Core/AST/IfStmt.nll"
	class IfStmt : public AST
	{
#line 6 "../../../Source/Core/AST/IfStmt.nll"
		public: IfStmt();
#line 11 "../../../Source/Core/AST/IfStmt.nll"
		public: static IfStmt* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 84 "../../../Source/Core/AST/IfStmt.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

