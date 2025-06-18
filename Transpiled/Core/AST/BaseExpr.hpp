#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class ClassDecl;
	class BaseExpr;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class InternalString;
}
namespace NumbatLogic
{
	class BaseExpr : public AST
	{
		public: ClassDecl* m_pBaseClassDecl;
		public: static BaseExpr* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
		public: BaseExpr();
	};
}

