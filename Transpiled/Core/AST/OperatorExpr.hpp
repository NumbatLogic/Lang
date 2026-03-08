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
#line 0 "../../../Source/Core/AST/OperatorExpr.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/OperatorExpr.nll"
	class OperatorExpr : public AST
	{
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

		public: OperatorExpr::OperatorType m_eOperatorType;
		public: Token* m_pFirstOperatorToken;
		public: Token* m_pOwnedOperatorToken;
		public: AST* m_pLeft;
		public: AST* m_pRight;
		public: OperatorExpr();
		public: Token* GetFirstOperatorToken();
		public: OperatorExpr::OperatorType GetOperatorType();
		public: static bool IsPostfix(OperatorExpr::OperatorType eOperatorType);
		protected: static int GetOperatorTokenCount(OperatorExpr::OperatorType eOp);
		protected: static OperatorExpr::OperatorType GetOperatorTypeFromTokens(Token* pFirst, Token* pSecond, Token* pThird);
		public: static OperatorExpr::OperatorType PeekOperator(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
		public: static OperatorExpr* Create(OperatorExpr::OperatorType eOperatorType, Token* pFirstOperatorToken, AST* pLeft, AST* pRight);
		public: virtual AST* BaseClone();
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
		protected: static const char* GetOperatorString(OperatorExpr::OperatorType eOperatorType);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* out);
		public: virtual ~OperatorExpr();
	};
}

