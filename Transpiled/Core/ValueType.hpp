#pragma once

#include "AST/TypeRef.hpp"
#include "../../../LangShared/Transpiled/Vector/OwnedVector.hpp"
#include "ValueType.hpp"

namespace NumbatLogic
{
	class ClassDecl;
	class GenericTypeDecl;
	class EnumDecl;
	class EnumDeclValue;
	template <class T>
	class OwnedVector;
	class ValueType;
	class DelegateDecl;
	class FunctionDecl;
	class NamespaceNode;
	class Validator;
	class Token;
	class TypeRef;
	class InternalString;
}
#line 1 "../../../Source/Core/ValueType.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/ValueType.nll"
	class ValueType
	{
#line 6 "../../../Source/Core/ValueType.nll"
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

#line 37 "../../../Source/Core/ValueType.nll"
		public: bool m_bConst;
#line 38 "../../../Source/Core/ValueType.nll"
		public: Type m_eType;
#line 40 "../../../Source/Core/ValueType.nll"
		public: ClassDecl* m_pClassDecl;
#line 41 "../../../Source/Core/ValueType.nll"
		public: TypeRef::PointerType m_ePointerType;
#line 43 "../../../Source/Core/ValueType.nll"
		public: GenericTypeDecl* m_pGenericTypeDecl;
#line 45 "../../../Source/Core/ValueType.nll"
		public: EnumDecl* m_pEnumDecl;
#line 46 "../../../Source/Core/ValueType.nll"
		public: EnumDeclValue* m_pEnumDeclValue;
#line 49 "../../../Source/Core/ValueType.nll"
		public: OwnedVector<ValueType*>* m_pGenericValueTypeVector;
#line 51 "../../../Source/Core/ValueType.nll"
		public: DelegateDecl* m_pDelegateDecl;
#line 53 "../../../Source/Core/ValueType.nll"
		public: FunctionDecl* m_pFunctionDecl;
#line 55 "../../../Source/Core/ValueType.nll"
		public: NamespaceNode* m_pNamespaceNode;
#line 58 "../../../Source/Core/ValueType.nll"
		public: ValueType(Type eType);
#line 66 "../../../Source/Core/ValueType.nll"
		public: ValueType* Clone();
#line 91 "../../../Source/Core/ValueType.nll"
		public: bool ValidateAssignable(ValueType* pTo, Validator* pValidator, Token* pToken);
#line 198 "../../../Source/Core/ValueType.nll"
		public: TypeRef* CreateTypeRef();
#line 260 "../../../Source/Core/ValueType.nll"
		public: virtual void StringifyType(InternalString* sOut);
#line 286 "../../../Source/Core/ValueType.nll"
		public: static void StringifyPointerType(InternalString* sOut, TypeRef::PointerType ePointerType);
#line 4 "../../../Source/Core/ValueType.nll"
		public: virtual ~ValueType();
	};
}

