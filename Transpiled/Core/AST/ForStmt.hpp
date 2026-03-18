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
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
	class ForStmt : public AST
	{
		public: ForStmt();
#line 11 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
		public: static ForStmt* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 107 "/home/cliffya/git/Lang/Source/Core/AST/ForStmt.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

