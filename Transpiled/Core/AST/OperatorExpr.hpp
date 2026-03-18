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
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/OperatorExpr.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/OperatorExpr.nll"
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

#line 38 "/home/cliffya/git/Lang/Source/Core/AST/OperatorExpr.nll"
		public: OperatorExpr::OperatorType m_eOperatorType;
		public: Token* m_pFirstOperatorToken;
		public: Token* m_pOwnedOperatorToken;
		public: AST* m_pLeft;
		public: AST* m_pRight;
#line 44 "/home/cliffya/git/Lang/Source/Core/AST/OperatorExpr.nll"
		public: OperatorExpr();
#line 49 "/home/cliffya/git/Lang/Source/Core/AST/OperatorExpr.nll"
		public: Token* GetFirstOperatorToken();
#line 55 "/home/cliffya/git/Lang/Source/Core/AST/OperatorExpr.nll"
		public: OperatorExpr::OperatorType GetOperatorType();
#line 60 "/home/cliffya/git/Lang/Source/Core/AST/OperatorExpr.nll"
		public: static bool IsPostfix(OperatorExpr::OperatorType eOperatorType);
#line 65 "/home/cliffya/git/Lang/Source/Core/AST/OperatorExpr.nll"
		protected: static int GetOperatorTokenCount(OperatorExpr::OperatorType eOp);
#line 92 "/home/cliffya/git/Lang/Source/Core/AST/OperatorExpr.nll"
		protected: static OperatorExpr::OperatorType GetOperatorTypeFromTokens(Token* pFirst, Token* pSecond, Token* pThird);
#line 155 "/home/cliffya/git/Lang/Source/Core/AST/OperatorExpr.nll"
		public: static OperatorExpr::OperatorType PeekOperator(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 173 "/home/cliffya/git/Lang/Source/Core/AST/OperatorExpr.nll"
		public: static OperatorExpr* Create(OperatorExpr::OperatorType eOperatorType, Token* pFirstOperatorToken, AST* pLeft, AST* pRight);
#line 199 "/home/cliffya/git/Lang/Source/Core/AST/OperatorExpr.nll"
		public: virtual AST* BaseClone();
#line 216 "/home/cliffya/git/Lang/Source/Core/AST/OperatorExpr.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 508 "/home/cliffya/git/Lang/Source/Core/AST/OperatorExpr.nll"
		protected: static const char* GetOperatorString(OperatorExpr::OperatorType eOperatorType);
#line 545 "/home/cliffya/git/Lang/Source/Core/AST/OperatorExpr.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/OperatorExpr.nll"
		public: virtual ~OperatorExpr();
	};
}

