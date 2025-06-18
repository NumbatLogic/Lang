#pragma once

#include "AST.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
#include "TypeRef.hpp"

namespace NumbatLogic
{
	class Token;
	class TypeRef;
	class AST;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class ClassDecl;
	class OperatorExpr;
	class InternalString;
	class ValueType;
}
namespace NumbatLogic
{
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
		public: Token* m_pTypeToken;
		public: Vector<TypeRef*>* m_pGenericTypeRefVector;
		public: TypeRef* m_pChildTypeRef;
		public: PointerType m_ePointerType;
		public: Token* m_pCloneToken;
		protected: AST* m_pFoundType;
		public: TypeRef();
		public: static TypeRef* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
		protected: void ValidateClassDecl(Validator* pValidator, ClassDecl* pClassDecl, TypeRef* pThisOrChild);
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
		public: TypeRef* Clone();
		public: virtual AST* BaseClone();
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
		public: ValueType* GetRecursiveValueType();
		public: ValueType* CreateValueType();
		protected: ValueType* SetValueType();
		public: virtual ~TypeRef();
	};
}

