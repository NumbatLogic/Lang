#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class TypeRef;
	class ParamCall;
	class New;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class OutputBuilder;
}
#line 1 "../../../Source/Core/AST/New.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/New.nll"
	class New : public AST
	{
#line 6 "../../../Source/Core/AST/New.nll"
		public: TypeRef* m_pTypeRef;
#line 7 "../../../Source/Core/AST/New.nll"
		public: ParamCall* m_pParamCall;
#line 9 "../../../Source/Core/AST/New.nll"
		public: static New* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 50 "../../../Source/Core/AST/New.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 108 "../../../Source/Core/AST/New.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 4 "../../../Source/Core/AST/New.nll"
		public: New();
	};
}

