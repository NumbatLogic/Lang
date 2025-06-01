#pragma once

#include "AST.hpp"

namespace NumberDuck
{
	namespace Secret
	{
		class AST;
		class TrinaryExpr;
		class TokenContainer;
		class OffsetDatum;
		class Validator;
		class OperatorExpr;
		class InternalString;
	}
}
namespace NumberDuck
{
	namespace Secret
	{
		class TrinaryExpr : public AST
		{
			public: AST* m_pFirstExpression;
			public: AST* m_pSecondExpression;
			public: AST* m_pThirdExpression;
			public: TrinaryExpr();
			public: static TrinaryExpr* Create(AST* pFirstExpressionTransition, TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
			public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
			public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
		};
	}
}

