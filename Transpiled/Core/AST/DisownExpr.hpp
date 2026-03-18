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
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
	class DisownExpr : public AST
	{
		public: AST* m_pExpression;
		public: InternalString* m_sTempVarName;
#line 8 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
		public: DisownExpr();
#line 13 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
		public: static DisownExpr* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 40 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 155 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
		public: virtual ~DisownExpr();
	};
}

