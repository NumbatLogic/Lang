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
	class InternalString;
}
namespace NumbatLogic
{
	class New : public AST
	{
		public: TypeRef* m_pTypeRef;
		public: ParamCall* m_pParamCall;
		public: static New* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
		public: New();
	};
}

