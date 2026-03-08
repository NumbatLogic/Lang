#pragma once

#include "AST.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
#include "../Token.hpp"
#include "OperatorExpr.hpp"

namespace NumbatLogic
{
	class Token;
	class AST;
	class OperatorExpr;
	template <class T>
	class Vector;
	class Validator;
	class InternalString;
}
namespace NumbatLogic
{
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
			UNKNOWN,
		};

		public: Vector<Token*>* m_pOperatorTokenVector;
		public: Token* m_pOwnedOperatorToken;
		public: AST* m_pLeft;
		public: AST* m_pRight;
		public: OperatorExpr();
		public: Token* GetFirstOperatorToken();
		public: OperatorExpr::OperatorType GetOperatorType();
		public: static OperatorExpr* Create(Vector<Token*>* pOperatorTokenVector, AST* pLeft, AST* pRight);
		public: virtual AST* BaseClone();
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
		public: virtual ~OperatorExpr();
	};
}

