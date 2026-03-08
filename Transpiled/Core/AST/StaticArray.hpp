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
		public: StaticArray();
		public: static StaticArray* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* out);
	};
}

