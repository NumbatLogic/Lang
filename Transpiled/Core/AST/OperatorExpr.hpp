#pragma once

#include "AST.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
#include "../Token.hpp"

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
		public: Vector<Token*>* m_pOperatorTokenVector;
		public: Token* m_pOwnedOperatorToken;
		public: AST* m_pLeft;
		public: AST* m_pRight;
		public: OperatorExpr();
		public: Token* GetFirstOperatorToken();
		public: static OperatorExpr* Create(Vector<Token*>* pOperatorTokenVector, AST* pLeft, AST* pRight);
		public: virtual AST* BaseClone();
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
		public: virtual ~OperatorExpr();
	};
}

