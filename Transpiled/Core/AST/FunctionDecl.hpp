#pragma once

#include "AST.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
#include "DecoratorCall.hpp"

namespace NumbatLogic
{
	class TypeRef;
	class Token;
	class ParamDecl;
	class Scope;
	template <class T>
	class Vector;
	class DecoratorCall;
	class FunctionDecl;
	class TokenContainer;
	class OffsetDatum;
	class AST;
	class Validator;
	class OperatorExpr;
	class InternalString;
	class OutputBuilder;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
	class FunctionDecl : public AST
	{
		public: TypeRef* m_pTypeRef;
		public: Token* m_pNameToken;
		public: const char* m_sMangledName;
		public: ParamDecl* m_pParamDecl;
		public: bool m_bConst;
		public: Scope* m_pScope;
		public: Vector<DecoratorCall*>* m_pDecoratorCallVector;
#line 13 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
		public: FunctionDecl();
#line 18 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
		public: static FunctionDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, AST* pParent);
#line 106 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 131 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
		public: void AppendFullyQualifiedName(Language eLanguage, InternalString* sOut);
#line 153 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
		public: virtual ~FunctionDecl();
	};
}

