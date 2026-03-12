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
#line 0 "../../../Source/Core/AST/BaseExpr.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/BaseExpr.nll"
	class BaseExpr : public AST
	{
		public: ClassDecl* m_pBaseClassDecl;
#line 7 "../../../Source/Core/AST/BaseExpr.nll"
		public: static BaseExpr* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 25 "../../../Source/Core/AST/BaseExpr.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 60 "../../../Source/Core/AST/BaseExpr.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 3 "../../../Source/Core/AST/BaseExpr.nll"
		public: BaseExpr();
	};
}

