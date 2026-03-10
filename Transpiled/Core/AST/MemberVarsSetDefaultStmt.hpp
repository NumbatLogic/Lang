#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class Validator;
	class OperatorExpr;
	class OutputBuilder;
}
#line 0 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
	class MemberVarsSetDefaultStmt : public AST
	{
#line 5 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
		public: MemberVarsSetDefaultStmt();
#line 11 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 44 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

