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
#line 0 "../../../Source/Core/AST/Identifier.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/Identifier.nll"
	class Identifier : public AST
	{
		public: Token* m_pNameToken;
#line 7 "../../../Source/Core/AST/Identifier.nll"
		public: static Identifier* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 26 "../../../Source/Core/AST/Identifier.nll"
		public: virtual AST* BaseClone();
#line 35 "../../../Source/Core/AST/Identifier.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 418 "../../../Source/Core/AST/Identifier.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 3 "../../../Source/Core/AST/Identifier.nll"
		public: Identifier();
	};
}

