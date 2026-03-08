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
		public: AST* m_pExpression;
		public: Vector<AST*>* m_pIndexExpressionVector;
		public: ArrayLookup();
		public: static ArrayLookup* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
		public: virtual AST* BaseClone();
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* out);
		public: virtual ~ArrayLookup();
	};
}

