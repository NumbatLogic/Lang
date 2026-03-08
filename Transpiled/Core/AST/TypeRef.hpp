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
#line 0 "../../../Source/Core/AST/TypeRef.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/TypeRef.nll"
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
		public: Token* m_pCloneToken;
		public: AST* m_pFoundType;
		public: TypeRef();
		public: static TypeRef* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
		public: ClassDecl* GetFoundClassDecl();
		protected: void ValidateClassDecl(Validator* pValidator, ClassDecl* pClassDecl, TypeRef* pThisOrChild);
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
		public: TypeRef* Clone();
		public: virtual AST* BaseClone();
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* out);
		public: ValueType* GetRecursiveValueType(Resolver* pResolver);
		public: ValueType* CreateValueType(Resolver* pResolver);
		protected: ValueType* SetValueType(Resolver* pResolver);
		public: bool IsIntegral();
		public: bool IsInt();
		public: bool IsBool();
		public: bool IsFloat();
		public: bool IsDouble();
		public: virtual ~TypeRef();
	};
}

