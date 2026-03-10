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
#line 0 "../../../Source/Core/AST/Scope.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/Scope.nll"
	class Scope : public AST
	{
#line 6 "../../../Source/Core/AST/Scope.nll"
		public: bool m_bPseudo;
#line 8 "../../../Source/Core/AST/Scope.nll"
		public: Scope();
#line 14 "../../../Source/Core/AST/Scope.nll"
		public: static Scope* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, bool bPseudoScope);
#line 70 "../../../Source/Core/AST/Scope.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 125 "../../../Source/Core/AST/Scope.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

