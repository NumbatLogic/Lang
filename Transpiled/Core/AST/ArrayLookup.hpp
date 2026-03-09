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
#line 1 "../../../Source/Core/AST/ArrayLookup.nll"
namespace NumbatLogic
{
#line 6 "../../../Source/Core/AST/ArrayLookup.nll"
	class ArrayLookup : public AST
	{
#line 8 "../../../Source/Core/AST/ArrayLookup.nll"
		public: AST* m_pExpression;
#line 9 "../../../Source/Core/AST/ArrayLookup.nll"
		public: Vector<AST*>* m_pIndexExpressionVector;
#line 11 "../../../Source/Core/AST/ArrayLookup.nll"
		public: ArrayLookup();
#line 17 "../../../Source/Core/AST/ArrayLookup.nll"
		public: static ArrayLookup* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 64 "../../../Source/Core/AST/ArrayLookup.nll"
		public: virtual AST* BaseClone();
#line 83 "../../../Source/Core/AST/ArrayLookup.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 94 "../../../Source/Core/AST/ArrayLookup.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 6 "../../../Source/Core/AST/ArrayLookup.nll"
		public: virtual ~ArrayLookup();
	};
}

