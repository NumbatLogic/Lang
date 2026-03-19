#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class Token;
	class ParamCall;
	class DecoratorCall;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class OutputBuilder;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
	class DecoratorCall : public AST
	{
		public: enum DecoratorType
		{
			UNKNOWN,
			DUMMY,
			ENTRY_POINT,
		};

		public: DecoratorType m_eDecoratorType;
		public: Token* m_pDecoratorNameToken;
		public: ParamCall* m_pParamCall;
#line 16 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
		public: static DecoratorCall* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 55 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 78 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
		public: DecoratorCall();
	};
}

