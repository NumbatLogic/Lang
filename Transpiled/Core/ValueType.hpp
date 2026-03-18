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
#line 0 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
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

#line 36 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
		public: bool m_bConst;
		public: Type m_eType;
#line 39 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
		public: ClassDecl* m_pClassDecl;
		public: TypeRef::PointerType m_ePointerType;
#line 42 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
		public: GenericTypeDecl* m_pGenericTypeDecl;
#line 44 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
		public: EnumDecl* m_pEnumDecl;
		public: EnumDeclValue* m_pEnumDeclValue;
#line 48 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
		public: OwnedVector<ValueType*>* m_pGenericValueTypeVector;
#line 50 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
		public: DelegateDecl* m_pDelegateDecl;
#line 52 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
		public: FunctionDecl* m_pFunctionDecl;
#line 54 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
		public: NamespaceNode* m_pNamespaceNode;
#line 57 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
		public: ValueType(Type eType);
#line 65 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
		public: ValueType* Clone();
#line 90 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
		public: bool ValidateAssignable(ValueType* pTo, Validator* pValidator, Token* pToken);
#line 197 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
		public: TypeRef* CreateTypeRef();
#line 259 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
		public: virtual void StringifyType(InternalString* sOut);
#line 285 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
		public: static void StringifyPointerType(InternalString* sOut, TypeRef::PointerType ePointerType);
#line 3 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
		public: virtual ~ValueType();
	};
}

