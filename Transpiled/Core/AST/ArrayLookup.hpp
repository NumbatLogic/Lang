#pragma once

#include "AST.hpp"
#include "../../../../LangShared/Source/Vector/CPP/Vector.hpp"

namespace NumbatLogic
{
	class AST;
	template <class T>
	class Vector;
	class ArrayLookup;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class OutputBuilder;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/ArrayLookup.nll"
namespace NumbatLogic
{
#line 5 "/home/cliffya/git/Lang/Source/Core/AST/ArrayLookup.nll"
	class ArrayLookup : public AST
	{
		public: AST* m_pExpression;
		public: Vector<AST*>* m_pIndexExpressionVector;
#line 10 "/home/cliffya/git/Lang/Source/Core/AST/ArrayLookup.nll"
		public: ArrayLookup();
#line 16 "/home/cliffya/git/Lang/Source/Core/AST/ArrayLookup.nll"
		public: static ArrayLookup* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 63 "/home/cliffya/git/Lang/Source/Core/AST/ArrayLookup.nll"
		public: virtual AST* BaseClone();
#line 82 "/home/cliffya/git/Lang/Source/Core/AST/ArrayLookup.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 93 "/home/cliffya/git/Lang/Source/Core/AST/ArrayLookup.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 5 "/home/cliffya/git/Lang/Source/Core/AST/ArrayLookup.nll"
		public: virtual ~ArrayLookup();
	};
}

