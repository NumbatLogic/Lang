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
#line 0 "../../../Source/Core/AST/IfStmt.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/IfStmt.nll"
	class IfStmt : public AST
	{
		public: IfStmt();
#line 10 "../../../Source/Core/AST/IfStmt.nll"
		public: static IfStmt* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 83 "../../../Source/Core/AST/IfStmt.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

