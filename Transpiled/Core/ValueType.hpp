#pragma once

#include "AST/TypeRef.hpp"
#include "../../../LangTranspiled/Shared/Vector/OwnedVector.hpp"

namespace NumberDuck
{
	namespace Secret
	{
		class ClassDecl;
		class GenericTypeDecl;
		class EnumDecl;
		class EnumDeclValue;
		class ValueType;
		class DelegateDecl;
		class FunctionDecl;
		class NamespaceNode;
		class Validator;
		class Token;
		class TypeRef;
		class InternalString;
	}
}
namespace NumberDuck
{
	namespace Secret
	{
		class ValueType
		{
			public: enum Type
			{
				VOID,
				INT,
				STRING,
				BOOL,
				CHAR,
				UNICHAR,
				INSTANCE,
				VOIDPTR,
				CLASS_DECL,
				CLASS_DECL_VALUE,
				ENUM_DECL,
				ENUM_DECL_VALUE,
				GENERIC_TYPE_DECL_VALUE,
				STATIC_ARRAY,
				NULL_VALUE,
				DELEGATE_DECL_VALUE,
				FUNCTION_DECL,
				NAMESPACE_NODE,
			};

			public: bool m_bConst;
			public: Type m_eType;
			public: ClassDecl* m_pClassDecl;
			public: TypeRef::PointerType m_ePointerType;
			public: GenericTypeDecl* m_pGenericTypeDecl;
			public: EnumDecl* m_pEnumDecl;
			public: EnumDeclValue* m_pEnumDeclValue;
			public: OwnedVector<ValueType*>* m_pGenericValueTypeVector;
			public: DelegateDecl* m_pDelegateDecl;
			public: FunctionDecl* m_pFunctionDecl;
			public: NamespaceNode* m_pNamespaceNode;
			public: ValueType(Type eType);
			public: ValueType* Clone();
			public: bool ValidateAssignable(ValueType* pTo, Validator* pValidator, Token* pToken);
			public: TypeRef* CreateTypeRef();
			public: virtual void StringifyType(InternalString* sOut);
			public: virtual ~ValueType();
		};
	}
}

