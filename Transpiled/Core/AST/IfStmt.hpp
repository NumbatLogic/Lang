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
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/IfStmt.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/IfStmt.nll"
	class IfStmt : public AST
	{
		public: IfStmt();
#line 10 "/home/cliffya/git/Lang/Source/Core/AST/IfStmt.nll"
		public: static IfStmt* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 83 "/home/cliffya/git/Lang/Source/Core/AST/IfStmt.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

