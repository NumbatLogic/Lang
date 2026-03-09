#pragma once

#include "AST.hpp"
#include "OperatorExpr.hpp"

namespace NumbatLogic
{
	class Token;
	class AST;
	class TokenContainer;
	class OffsetDatum;
	class OperatorExpr;
	class Validator;
	class OutputBuilder;
}
#line 1 "../../../Source/Core/AST/OperatorExpr.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/OperatorExpr.nll"
	class OperatorExpr : public AST
	{
#line 6 "../../../Source/Core/AST/OperatorExpr.nll"
		public: enum OperatorType
		{
			LOGICAL_AND,
			LESS_THAN,
			LESS_THAN_OR_EQUAL,
			GREATER_THAN,
			GREATER_THAN_OR_EQUAL,
			BITWISE_AND,
			BITWISE_OR,
			BITWISE_XOR,
			DIVISION,
			MEMBER_ACCESS,
			LEFT_SHIFT,
			RIGHT_SHIFT,
			SCOPE_RESOLUTION,
			EQUALITY,
			ASSIGNMENT,
			SUBTRACTION,
			SUBTRACT_ASSIGN,
			DECREMENT,
			MODULO,
			INEQUALITY,
			LOGICAL_OR,
			ADDITION,
			ADD_ASSIGN,
			INCREMENT,
			MULTIPLICATION,
			MULTIPLY_ASSIGN,
			DIVIDE_ASSIGN,
			LEFT_SHIFT_ASSIGN,
			RIGHT_SHIFT_ASSIGN,
			UNKNOWN,
		};

#line 39 "../../../Source/Core/AST/OperatorExpr.nll"
		public: OperatorExpr::OperatorType m_eOperatorType;
#line 40 "../../../Source/Core/AST/OperatorExpr.nll"
		public: Token* m_pFirstOperatorToken;
#line 41 "../../../Source/Core/AST/OperatorExpr.nll"
		public: Token* m_pOwnedOperatorToken;
#line 42 "../../../Source/Core/AST/OperatorExpr.nll"
		public: AST* m_pLeft;
#line 43 "../../../Source/Core/AST/OperatorExpr.nll"
		public: AST* m_pRight;
#line 45 "../../../Source/Core/AST/OperatorExpr.nll"
		public: OperatorExpr();
#line 50 "../../../Source/Core/AST/OperatorExpr.nll"
		public: Token* GetFirstOperatorToken();
#line 56 "../../../Source/Core/AST/OperatorExpr.nll"
		public: OperatorExpr::OperatorType GetOperatorType();
#line 61 "../../../Source/Core/AST/OperatorExpr.nll"
		public: static bool IsPostfix(OperatorExpr::OperatorType eOperatorType);
#line 66 "../../../Source/Core/AST/OperatorExpr.nll"
		protected: static int GetOperatorTokenCount(OperatorExpr::OperatorType eOp);
#line 93 "../../../Source/Core/AST/OperatorExpr.nll"
		protected: static OperatorExpr::OperatorType GetOperatorTypeFromTokens(Token* pFirst, Token* pSecond, Token* pThird);
#line 156 "../../../Source/Core/AST/OperatorExpr.nll"
		public: static OperatorExpr::OperatorType PeekOperator(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 174 "../../../Source/Core/AST/OperatorExpr.nll"
		public: static OperatorExpr* Create(OperatorExpr::OperatorType eOperatorType, Token* pFirstOperatorToken, AST* pLeft, AST* pRight);
#line 200 "../../../Source/Core/AST/OperatorExpr.nll"
		public: virtual AST* BaseClone();
#line 217 "../../../Source/Core/AST/OperatorExpr.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 509 "../../../Source/Core/AST/OperatorExpr.nll"
		protected: static const char* GetOperatorString(OperatorExpr::OperatorType eOperatorType);
#line 546 "../../../Source/Core/AST/OperatorExpr.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 4 "../../../Source/Core/AST/OperatorExpr.nll"
		public: virtual ~OperatorExpr();
	};
}

