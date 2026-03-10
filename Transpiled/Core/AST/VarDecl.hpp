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
#line 5 "../../../Source/Core/AST/VarDecl.nll"
		public: TypeRef* m_pTypeRef;
#line 6 "../../../Source/Core/AST/VarDecl.nll"
		public: Token* m_pNameToken;
#line 7 "../../../Source/Core/AST/VarDecl.nll"
		public: AST* m_pAssignment;
#line 8 "../../../Source/Core/AST/VarDecl.nll"
		public: bool m_bInline;
#line 10 "../../../Source/Core/AST/VarDecl.nll"
		public: Vector<AST*>* m_pArraySizeVector;
#line 12 "../../../Source/Core/AST/VarDecl.nll"
		public: Token* m_pOwnedNameToken;
#line 14 "../../../Source/Core/AST/VarDecl.nll"
		public: VarDecl();
#line 20 "../../../Source/Core/AST/VarDecl.nll"
		public: static VarDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, bool bInline);
#line 109 "../../../Source/Core/AST/VarDecl.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 162 "../../../Source/Core/AST/VarDecl.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 3 "../../../Source/Core/AST/VarDecl.nll"
		public: virtual ~VarDecl();
	};
}

