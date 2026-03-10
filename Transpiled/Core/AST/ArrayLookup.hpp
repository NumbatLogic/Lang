#pragma once

#include "AST.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"

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
#line 0 "../../../Source/Core/AST/ArrayLookup.nll"
namespace NumbatLogic
{
#line 5 "../../../Source/Core/AST/ArrayLookup.nll"
	class ArrayLookup : public AST
	{
#line 7 "../../../Source/Core/AST/ArrayLookup.nll"
		public: AST* m_pExpression;
#line 8 "../../../Source/Core/AST/ArrayLookup.nll"
		public: Vector<AST*>* m_pIndexExpressionVector;
#line 10 "../../../Source/Core/AST/ArrayLookup.nll"
		public: ArrayLookup();
#line 16 "../../../Source/Core/AST/ArrayLookup.nll"
		public: static ArrayLookup* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 63 "../../../Source/Core/AST/ArrayLookup.nll"
		public: virtual AST* BaseClone();
#line 82 "../../../Source/Core/AST/ArrayLookup.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 93 "../../../Source/Core/AST/ArrayLookup.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 5 "../../../Source/Core/AST/ArrayLookup.nll"
		public: virtual ~ArrayLookup();
	};
}

