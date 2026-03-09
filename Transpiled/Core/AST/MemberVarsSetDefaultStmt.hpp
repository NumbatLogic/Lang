#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class Validator;
	class OperatorExpr;
	class OutputBuilder;
}
#line 1 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
	class MemberVarsSetDefaultStmt : public AST
	{
#line 6 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
		public: MemberVarsSetDefaultStmt();
#line 12 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 45 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

