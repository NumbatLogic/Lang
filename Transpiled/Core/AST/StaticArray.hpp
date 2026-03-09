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
#line 1 "../../../Source/Core/AST/StaticArray.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/StaticArray.nll"
	class StaticArray : public AST
	{
#line 6 "../../../Source/Core/AST/StaticArray.nll"
		public: StaticArray();
#line 11 "../../../Source/Core/AST/StaticArray.nll"
		public: static StaticArray* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 57 "../../../Source/Core/AST/StaticArray.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 63 "../../../Source/Core/AST/StaticArray.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

