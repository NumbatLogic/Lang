#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class NullExpr;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class OutputBuilder;
}
#line 0 "../../../Source/Core/AST/NullExpr.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/NullExpr.nll"
	class NullExpr : public AST
	{
		public: NullExpr();
		public: static NullExpr* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* out);
	};
}

