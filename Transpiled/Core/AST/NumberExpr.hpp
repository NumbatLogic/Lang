#pragma once

#include "AST.hpp"

namespace NumberDuck
{
	namespace Secret
	{
		class Token;
		class NumberExpr;
		class TokenContainer;
		class OffsetDatum;
		class AST;
		class Validator;
		class OperatorExpr;
		class InternalString;
	}
}
namespace NumberDuck
{
	namespace Secret
	{
		class NumberExpr : public AST
		{
			public: NumberExpr(Token* pFirstToken);
			public: static NumberExpr* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
			public: virtual AST* BaseClone();
			public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
			public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
		};
	}
}

