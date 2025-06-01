#pragma once

#include "AST.hpp"

namespace NumberDuck
{
	namespace Secret
	{
		class Validator;
		class OperatorExpr;
		class InternalString;
	}
}
namespace NumberDuck
{
	namespace Secret
	{
		class MemberVarsSetDefaultStmt : public AST
		{
			public: MemberVarsSetDefaultStmt();
			public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
			public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
		};
	}
}

