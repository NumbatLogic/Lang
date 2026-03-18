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
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/New.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/New.nll"
	class New : public AST
	{
		public: TypeRef* m_pTypeRef;
		public: ParamCall* m_pParamCall;
#line 8 "/home/cliffya/git/Lang/Source/Core/AST/New.nll"
		public: static New* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 49 "/home/cliffya/git/Lang/Source/Core/AST/New.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 107 "/home/cliffya/git/Lang/Source/Core/AST/New.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/New.nll"
		public: New();
	};
}

