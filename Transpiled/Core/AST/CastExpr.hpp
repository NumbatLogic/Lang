#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class TypeRef;
	class ParamCall;
	class CastExpr;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class InternalString;
}
namespace NumbatLogic
{
	class CastExpr : public AST
	{
		public: TypeRef* m_pTypeRef;
		public: ParamCall* m_pParamCall;
		public: CastExpr();
		public: static CastExpr* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
	};
}

