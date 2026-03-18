#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class StringExpr;
	class TTHashExpr;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class OutputBuilder;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/TTHashExpr.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/TTHashExpr.nll"
	class TTHashExpr : public AST
	{
		protected: StringExpr* m_pStringExpr;
#line 7 "/home/cliffya/git/Lang/Source/Core/AST/TTHashExpr.nll"
		public: TTHashExpr();
#line 12 "/home/cliffya/git/Lang/Source/Core/AST/TTHashExpr.nll"
		public: static TTHashExpr* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 60 "/home/cliffya/git/Lang/Source/Core/AST/TTHashExpr.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 65 "/home/cliffya/git/Lang/Source/Core/AST/TTHashExpr.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

