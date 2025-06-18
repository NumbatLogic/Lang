#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class Scope;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class InternalString;
}
namespace NumbatLogic
{
	class Scope : public AST
	{
		public: Scope();
		public: static Scope* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
	};
}

