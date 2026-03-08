#pragma once

#include "AST.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"

namespace NumbatLogic
{
	class TypeRef;
	class Token;
	class AST;
	template <class T>
	class Vector;
	class VarDecl;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class OutputBuilder;
}
#line 0 "../../../Source/Core/AST/VarDecl.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/VarDecl.nll"
	class VarDecl : public AST
	{
		public: TypeRef* m_pTypeRef;
		public: Token* m_pNameToken;
		public: AST* m_pAssignment;
		public: bool m_bInline;
		public: Vector<AST*>* m_pArraySizeVector;
		public: Token* m_pOwnedNameToken;
		public: VarDecl();
		public: static VarDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, bool bInline);
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* out);
		public: virtual ~VarDecl();
	};
}

