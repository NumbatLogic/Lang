#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class ClassDecl;
	class BaseExpr;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class OutputBuilder;
}
#line 1 "../../../Source/Core/AST/BaseExpr.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/BaseExpr.nll"
	class BaseExpr : public AST
	{
#line 6 "../../../Source/Core/AST/BaseExpr.nll"
		public: ClassDecl* m_pBaseClassDecl;
#line 8 "../../../Source/Core/AST/BaseExpr.nll"
		public: static BaseExpr* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 26 "../../../Source/Core/AST/BaseExpr.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 61 "../../../Source/Core/AST/BaseExpr.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 4 "../../../Source/Core/AST/BaseExpr.nll"
		public: BaseExpr();
	};
}

