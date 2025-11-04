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
	class InternalString;
}
namespace NumbatLogic
{
	class Identifier : public AST
	{
		public: bool m_bRef;
		public: Token* m_pNameToken;
		public: static Identifier* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
		public: virtual AST* BaseClone();
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
		public: Identifier();
	};
}

