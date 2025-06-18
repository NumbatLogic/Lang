#pragma once

#include "AST.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
#include "VarDecl.hpp"

namespace NumbatLogic
{
	class VarDecl;
	class ParamDecl;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class ParamCall;
	class InternalString;
}
namespace NumbatLogic
{
	class ParamDecl : public AST
	{
		public: Vector<VarDecl*>* m_pParamVector;
		public: ParamDecl();
		public: static ParamDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
		public: bool ValidateParamCall(ParamCall* pParamCall, Validator* pValidator);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
		public: virtual ~ParamDecl();
	};
}

