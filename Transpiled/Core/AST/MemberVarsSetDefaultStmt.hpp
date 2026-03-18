#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class Validator;
	class OperatorExpr;
	class OutputBuilder;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarsSetDefaultStmt.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarsSetDefaultStmt.nll"
	class MemberVarsSetDefaultStmt : public AST
	{
		public: MemberVarsSetDefaultStmt();
#line 11 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarsSetDefaultStmt.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 44 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarsSetDefaultStmt.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

