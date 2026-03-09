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
#line 4 "../../../Source/Core/AST/Scope.nll"
	class Scope : public AST
	{
#line 7 "../../../Source/Core/AST/Scope.nll"
		public: bool m_bPseudo;
#line 9 "../../../Source/Core/AST/Scope.nll"
		public: Scope();
#line 15 "../../../Source/Core/AST/Scope.nll"
		public: static Scope* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, bool bPseudoScope);
#line 71 "../../../Source/Core/AST/Scope.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 126 "../../../Source/Core/AST/Scope.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

