#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class InternalString;
	class DisownExpr;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class Token;
	class TypeRef;
	class VarDecl;
	class NullExpr;
	class ExpressionStmt;
	class OutputBuilder;
}
#line 1 "../../../Source/Core/AST/DisownExpr.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/DisownExpr.nll"
	class DisownExpr : public AST
	{
#line 6 "../../../Source/Core/AST/DisownExpr.nll"
		public: AST* m_pExpression;
#line 7 "../../../Source/Core/AST/DisownExpr.nll"
		public: InternalString* m_sTempVarName;
#line 9 "../../../Source/Core/AST/DisownExpr.nll"
		public: DisownExpr();
#line 14 "../../../Source/Core/AST/DisownExpr.nll"
		public: static DisownExpr* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 41 "../../../Source/Core/AST/DisownExpr.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 156 "../../../Source/Core/AST/DisownExpr.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 4 "../../../Source/Core/AST/DisownExpr.nll"
		public: virtual ~DisownExpr();
	};
}

