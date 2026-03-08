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
		public: MemberVarsSetDefaultStmt();
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* out);
	};
}

