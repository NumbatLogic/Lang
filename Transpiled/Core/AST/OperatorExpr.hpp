#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class Token;
	class AST;
	class OperatorExpr;
	class Validator;
	class InternalString;
}
namespace NumbatLogic
{
	class OperatorExpr : public AST
	{
		public: Token* m_pOperatorToken;
		public: AST* m_pLeft;
		public: AST* m_pRight;
		public: Token* m_pOwnedOperatorToken;
		public: OperatorExpr();
		public: static OperatorExpr* Create(Token* pOperatorToken, AST* pLeft, AST* pRight);
		public: virtual AST* BaseClone();
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
		public: virtual ~OperatorExpr();
	};
}

