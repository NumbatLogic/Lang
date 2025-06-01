#pragma once

#include "AST.hpp"

namespace NumberDuck
{
	namespace Secret
	{
		class ContinueStmt;
		class TokenContainer;
		class OffsetDatum;
		class Validator;
		class OperatorExpr;
		class InternalString;
	}
}
namespace NumberDuck
{
	namespace Secret
	{
		class ContinueStmt : public AST
		{
			public: ContinueStmt();
			public: static ContinueStmt* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
			public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
			public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
		};
	}
}

