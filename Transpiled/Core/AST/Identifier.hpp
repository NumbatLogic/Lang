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
		public: static Identifier* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
		public: virtual AST* BaseClone();
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* out);
		public: Identifier();
	};
}

