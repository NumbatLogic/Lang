#pragma once

#include "AST.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
#include "DecoratorCall.hpp"

namespace NumbatLogic
{
	class TypeRef;
	class Token;
	class AST;
	template <class T>
	class Vector;
	class DecoratorCall;
	class VarDecl;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class OutputBuilder;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
	class VarDecl : public AST
	{
		public: TypeRef* m_pTypeRef;
		public: Token* m_pNameToken;
		public: AST* m_pAssignment;
		public: bool m_bInline;
#line 10 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
		public: Vector<AST*>* m_pArraySizeVector;
#line 12 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
		public: Token* m_pOwnedNameToken;
		public: Vector<DecoratorCall*>* m_pDecoratorCallVector;
#line 15 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
		public: VarDecl();
#line 22 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
		public: static VarDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, bool bInline);
#line 130 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 183 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
		public: virtual ~VarDecl();
	};
}

