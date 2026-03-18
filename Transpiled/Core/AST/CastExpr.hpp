#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class TypeRef;
	class ParamCall;
	class CastExpr;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class OutputBuilder;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/CastExpr.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/CastExpr.nll"
	class CastExpr : public AST
	{
		public: TypeRef* m_pTypeRef;
		public: ParamCall* m_pParamCall;
#line 8 "/home/cliffya/git/Lang/Source/Core/AST/CastExpr.nll"
		public: CastExpr();
#line 13 "/home/cliffya/git/Lang/Source/Core/AST/CastExpr.nll"
		public: static CastExpr* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 52 "/home/cliffya/git/Lang/Source/Core/AST/CastExpr.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 97 "/home/cliffya/git/Lang/Source/Core/AST/CastExpr.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

