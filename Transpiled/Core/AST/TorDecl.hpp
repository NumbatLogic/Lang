#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class ClassDecl;
	class AccessLevel;
	class Token;
	class ParamDecl;
	class ParamCall;
	class Scope;
	class TorDecl;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class OutputBuilder;
}
#line 1 "../../../Source/Core/AST/TorDecl.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/TorDecl.nll"
	class TorDecl : public AST
	{
#line 6 "../../../Source/Core/AST/TorDecl.nll"
		public: ClassDecl* m_pParentClassDecl;
#line 7 "../../../Source/Core/AST/TorDecl.nll"
		public: AccessLevel* m_pAccessLevel;
#line 8 "../../../Source/Core/AST/TorDecl.nll"
		public: Token* m_pTypeToken;
#line 9 "../../../Source/Core/AST/TorDecl.nll"
		public: ParamDecl* m_pParamDecl;
#line 10 "../../../Source/Core/AST/TorDecl.nll"
		public: ParamCall* m_pBaseParamCall;
#line 11 "../../../Source/Core/AST/TorDecl.nll"
		public: Scope* m_pScope;
#line 12 "../../../Source/Core/AST/TorDecl.nll"
		public: const char* m_sDisambiguate;
#line 14 "../../../Source/Core/AST/TorDecl.nll"
		public: static TorDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, ClassDecl* pParentClassDecl);
#line 101 "../../../Source/Core/AST/TorDecl.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 145 "../../../Source/Core/AST/TorDecl.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 4 "../../../Source/Core/AST/TorDecl.nll"
		public: TorDecl();
	};
}

