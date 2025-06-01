#pragma once

#include "AST.hpp"

namespace NumberDuck
{
	namespace Secret
	{
		class AST;
		class InternalString;
		class DisownExpr;
		class TokenContainer;
		class OffsetDatum;
		class Validator;
		class OperatorExpr;
	}
}
namespace NumberDuck
{
	namespace Secret
	{
		class DisownExpr : public AST
		{
			public: AST* m_pExpression;
			public: InternalString* m_sTempVarName;
			public: DisownExpr();
			public: static DisownExpr* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
			public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
			public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
			public: virtual ~DisownExpr();
		};
	}
}

