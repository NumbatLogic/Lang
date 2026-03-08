#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class Scope;
	class TokenContainer;
	class OffsetDatum;
	class AST;
	class Validator;
	class OperatorExpr;
	class Symbol;
	class OutputBuilder;
}
#line 1 "../../../Source/Core/AST/Scope.nll"
namespace NumbatLogic
{
	class Scope : public AST
	{
		public: bool m_bPseudo;
		public: Scope();
		public: static Scope* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, bool bPseudoScope);
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* out);
	};
}

