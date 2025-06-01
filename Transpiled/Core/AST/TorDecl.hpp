#pragma once

#include "AST.hpp"

namespace NumberDuck
{
	namespace Secret
	{
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
		class InternalString;
	}
}
namespace NumberDuck
{
	namespace Secret
	{
		class TorDecl : public AST
		{
			public: ClassDecl* m_pParentClassDecl;
			public: AccessLevel* m_pAccessLevel;
			public: Token* m_pTypeToken;
			public: ParamDecl* m_pParamDecl;
			public: ParamCall* m_pBaseParamCall;
			public: Scope* m_pScope;
			public: const char* m_sDisambiguate;
			public: static TorDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, ClassDecl* pParentClassDecl);
			public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
			public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
			public: TorDecl();
		};
	}
}

