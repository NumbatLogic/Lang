#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class Token;
	class Identifier;
	class TokenContainer;
	class OffsetDatum;
	class AST;
	class Validator;
	class OperatorExpr;
	class NamespaceDecl;
	class Symbol;
	class ValueType;
	class OutputBuilder;
}
#line 1 "../../../Source/Core/AST/Identifier.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/Identifier.nll"
	class Identifier : public AST
	{
#line 6 "../../../Source/Core/AST/Identifier.nll"
		public: Token* m_pNameToken;
#line 8 "../../../Source/Core/AST/Identifier.nll"
		public: static Identifier* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 27 "../../../Source/Core/AST/Identifier.nll"
		public: virtual AST* BaseClone();
#line 36 "../../../Source/Core/AST/Identifier.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 425 "../../../Source/Core/AST/Identifier.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 4 "../../../Source/Core/AST/Identifier.nll"
		public: Identifier();
	};
}

