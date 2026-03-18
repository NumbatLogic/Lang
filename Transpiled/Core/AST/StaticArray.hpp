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
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/StaticArray.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/StaticArray.nll"
	class StaticArray : public AST
	{
		public: StaticArray();
#line 10 "/home/cliffya/git/Lang/Source/Core/AST/StaticArray.nll"
		public: static StaticArray* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 56 "/home/cliffya/git/Lang/Source/Core/AST/StaticArray.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 62 "/home/cliffya/git/Lang/Source/Core/AST/StaticArray.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

