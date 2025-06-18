#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class Validator;
	class OperatorExpr;
	class InternalString;
}
namespace NumbatLogic
{
	class MemberVarsSetDefaultStmt : public AST
	{
		public: MemberVarsSetDefaultStmt();
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
	};
}

