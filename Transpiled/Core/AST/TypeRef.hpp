#pragma once

#include "AST.hpp"
#include "../../../../LangShared/Source/Vector/CPP/Vector.hpp"
#include "TypeRef.hpp"

namespace NumbatLogic
{
	class Token;
	template <class T>
	class Vector;
	class TypeRef;
	class AST;
	class TokenContainer;
	class OffsetDatum;
	class ClassDecl;
	class Validator;
	class OperatorExpr;
	class Symbol;
	class OutputBuilder;
	class ValueType;
	class Resolver;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/TypeRef.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/TypeRef.nll"
	class TypeRef : public AST
	{
		public: enum PointerType
		{
			SHARED,
			OWNED,
			TRANSITON,
			OWNED_PREASSSIGN,
		};

		public: bool m_bConst;
		public: bool m_bRef;
		public: Token* m_pTypeToken;
		public: Vector<TypeRef*>* m_pGenericTypeRefVector;
		public: TypeRef* m_pChildTypeRef;
		public: PointerType m_ePointerType;
#line 20 "/home/cliffya/git/Lang/Source/Core/AST/TypeRef.nll"
		public: Token* m_pCloneToken;
#line 22 "/home/cliffya/git/Lang/Source/Core/AST/TypeRef.nll"
		public: AST* m_pFoundType;
#line 24 "/home/cliffya/git/Lang/Source/Core/AST/TypeRef.nll"
		public: TypeRef();
#line 32 "/home/cliffya/git/Lang/Source/Core/AST/TypeRef.nll"
		public: static TypeRef* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 168 "/home/cliffya/git/Lang/Source/Core/AST/TypeRef.nll"
		public: ClassDecl* GetFoundClassDecl();
#line 175 "/home/cliffya/git/Lang/Source/Core/AST/TypeRef.nll"
		protected: void ValidateClassDecl(Validator* pValidator, ClassDecl* pClassDecl, TypeRef* pThisOrChild);
#line 249 "/home/cliffya/git/Lang/Source/Core/AST/TypeRef.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 413 "/home/cliffya/git/Lang/Source/Core/AST/TypeRef.nll"
		public: TypeRef* Clone();
#line 442 "/home/cliffya/git/Lang/Source/Core/AST/TypeRef.nll"
		public: virtual AST* BaseClone();
#line 447 "/home/cliffya/git/Lang/Source/Core/AST/TypeRef.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 635 "/home/cliffya/git/Lang/Source/Core/AST/TypeRef.nll"
		public: ValueType* GetRecursiveValueType(Resolver* pResolver);
#line 647 "/home/cliffya/git/Lang/Source/Core/AST/TypeRef.nll"
		public: ValueType* CreateValueType(Resolver* pResolver);
#line 661 "/home/cliffya/git/Lang/Source/Core/AST/TypeRef.nll"
		protected: ValueType* SetValueType(Resolver* pResolver);
#line 857 "/home/cliffya/git/Lang/Source/Core/AST/TypeRef.nll"
		public: bool IsIntegral();
#line 869 "/home/cliffya/git/Lang/Source/Core/AST/TypeRef.nll"
		public: bool IsInt();
#line 882 "/home/cliffya/git/Lang/Source/Core/AST/TypeRef.nll"
		public: bool IsBool();
#line 887 "/home/cliffya/git/Lang/Source/Core/AST/TypeRef.nll"
		public: bool IsFloat();
#line 892 "/home/cliffya/git/Lang/Source/Core/AST/TypeRef.nll"
		public: bool IsDouble();
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/TypeRef.nll"
		public: virtual ~TypeRef();
	};
}

