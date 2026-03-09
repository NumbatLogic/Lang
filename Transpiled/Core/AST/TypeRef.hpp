#pragma once

#include "AST.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
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
#line 1 "../../../Source/Core/AST/TypeRef.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/TypeRef.nll"
	class TypeRef : public AST
	{
#line 6 "../../../Source/Core/AST/TypeRef.nll"
		public: enum PointerType
		{
			SHARED,
			OWNED,
			TRANSITON,
			OWNED_PREASSSIGN,
		};

#line 14 "../../../Source/Core/AST/TypeRef.nll"
		public: bool m_bConst;
#line 15 "../../../Source/Core/AST/TypeRef.nll"
		public: bool m_bRef;
#line 16 "../../../Source/Core/AST/TypeRef.nll"
		public: Token* m_pTypeToken;
#line 17 "../../../Source/Core/AST/TypeRef.nll"
		public: Vector<TypeRef*>* m_pGenericTypeRefVector;
#line 18 "../../../Source/Core/AST/TypeRef.nll"
		public: TypeRef* m_pChildTypeRef;
#line 19 "../../../Source/Core/AST/TypeRef.nll"
		public: PointerType m_ePointerType;
#line 21 "../../../Source/Core/AST/TypeRef.nll"
		public: Token* m_pCloneToken;
#line 23 "../../../Source/Core/AST/TypeRef.nll"
		public: AST* m_pFoundType;
#line 25 "../../../Source/Core/AST/TypeRef.nll"
		public: TypeRef();
#line 33 "../../../Source/Core/AST/TypeRef.nll"
		public: static TypeRef* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 169 "../../../Source/Core/AST/TypeRef.nll"
		public: ClassDecl* GetFoundClassDecl();
#line 176 "../../../Source/Core/AST/TypeRef.nll"
		protected: void ValidateClassDecl(Validator* pValidator, ClassDecl* pClassDecl, TypeRef* pThisOrChild);
#line 250 "../../../Source/Core/AST/TypeRef.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 414 "../../../Source/Core/AST/TypeRef.nll"
		public: TypeRef* Clone();
#line 443 "../../../Source/Core/AST/TypeRef.nll"
		public: virtual AST* BaseClone();
#line 448 "../../../Source/Core/AST/TypeRef.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 637 "../../../Source/Core/AST/TypeRef.nll"
		public: ValueType* GetRecursiveValueType(Resolver* pResolver);
#line 649 "../../../Source/Core/AST/TypeRef.nll"
		public: ValueType* CreateValueType(Resolver* pResolver);
#line 663 "../../../Source/Core/AST/TypeRef.nll"
		protected: ValueType* SetValueType(Resolver* pResolver);
#line 859 "../../../Source/Core/AST/TypeRef.nll"
		public: bool IsIntegral();
#line 871 "../../../Source/Core/AST/TypeRef.nll"
		public: bool IsInt();
#line 884 "../../../Source/Core/AST/TypeRef.nll"
		public: bool IsBool();
#line 889 "../../../Source/Core/AST/TypeRef.nll"
		public: bool IsFloat();
#line 894 "../../../Source/Core/AST/TypeRef.nll"
		public: bool IsDouble();
#line 4 "../../../Source/Core/AST/TypeRef.nll"
		public: virtual ~TypeRef();
	};
}

