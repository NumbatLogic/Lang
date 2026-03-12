#pragma once

#include "AST.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
#include "VarDecl.hpp"

namespace NumbatLogic
{
	class AST;
	template <class T>
	class Vector;
	class VarDecl;
	class ParamDecl;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class ParamCall;
	class OutputBuilder;
}
#line 0 "../../../Source/Core/AST/ParamDecl.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/ParamDecl.nll"
	class ParamDecl : public AST
	{
		public: Vector<VarDecl*>* m_pParamVector;
#line 7 "../../../Source/Core/AST/ParamDecl.nll"
		public: ParamDecl();
#line 14 "../../../Source/Core/AST/ParamDecl.nll"
		public: static ParamDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 62 "../../../Source/Core/AST/ParamDecl.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 91 "../../../Source/Core/AST/ParamDecl.nll"
		public: bool ValidateParamCall(ParamCall* pParamCall, Validator* pValidator, bool bReportErrors);
#line 212 "../../../Source/Core/AST/ParamDecl.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 3 "../../../Source/Core/AST/ParamDecl.nll"
		public: virtual ~ParamDecl();
	};
}

