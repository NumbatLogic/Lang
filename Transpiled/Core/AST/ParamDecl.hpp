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
#line 1 "../../../Source/Core/AST/ParamDecl.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/ParamDecl.nll"
	class ParamDecl : public AST
	{
#line 6 "../../../Source/Core/AST/ParamDecl.nll"
		public: Vector<VarDecl*>* m_pParamVector;
#line 8 "../../../Source/Core/AST/ParamDecl.nll"
		public: ParamDecl();
#line 15 "../../../Source/Core/AST/ParamDecl.nll"
		public: static ParamDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 63 "../../../Source/Core/AST/ParamDecl.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 92 "../../../Source/Core/AST/ParamDecl.nll"
		public: bool ValidateParamCall(ParamCall* pParamCall, Validator* pValidator, bool bReportErrors);
#line 213 "../../../Source/Core/AST/ParamDecl.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 4 "../../../Source/Core/AST/ParamDecl.nll"
		public: virtual ~ParamDecl();
	};
}

