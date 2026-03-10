#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class StaticArray;
	class TokenContainer;
	class OffsetDatum;
	class AST;
	class Validator;
	class OperatorExpr;
	class OutputBuilder;
}
#line 0 "../../../Source/Core/AST/StaticArray.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/StaticArray.nll"
	class StaticArray : public AST
	{
#line 5 "../../../Source/Core/AST/StaticArray.nll"
		public: StaticArray();
#line 10 "../../../Source/Core/AST/StaticArray.nll"
		public: static StaticArray* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 56 "../../../Source/Core/AST/StaticArray.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 62 "../../../Source/Core/AST/StaticArray.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

