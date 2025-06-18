#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AccessLevel;
	class VarDecl;
	class MemberVarDecl;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class InternalString;
}
namespace NumbatLogic
{
	class MemberVarDecl : public AST
	{
		public: AccessLevel* m_pAccessLevel;
		public: bool m_bStatic;
		public: VarDecl* m_pVarDecl;
		public: MemberVarDecl();
		public: static MemberVarDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
	};
}

