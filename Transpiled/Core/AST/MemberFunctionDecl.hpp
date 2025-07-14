#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class ClassDecl;
	class AccessLevel;
	class FunctionDecl;
	class MemberFunctionDecl;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class InternalString;
}
namespace NumbatLogic
{
	class MemberFunctionDecl : public AST
	{
		public: ClassDecl* m_pParentClassDecl;
		public: AccessLevel* m_pAccessLevel;
		public: FunctionDecl* m_pFunctionDecl;
		public: bool m_bStatic;
		public: bool m_bVirtual;
		public: bool m_bOverride;
		public: MemberFunctionDecl();
		public: static MemberFunctionDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, ClassDecl* pParentClassDecl);
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
	};
}

