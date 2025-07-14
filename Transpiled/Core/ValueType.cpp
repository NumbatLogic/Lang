#include "ValueType.hpp"
#include "../LangShared/Vector/OwnedVector.hpp"
#include "AST/TypeRef.hpp"
#include "Validator.hpp"
#include "Token.hpp"
#include "../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "AST/ClassDecl.hpp"
#include "../../../LangShared/Vector/CPP/Vector.hpp"
#include "NamespaceNode.hpp"
#include "AST/GenericTypeDecl.hpp"
#include "../../../LangShared/Assert/CPP/Assert.hpp"
#include "AST/EnumDecl.hpp"
#include "AST/EnumDeclValue.hpp"
#include "AST/DelegateDecl.hpp"
#include "AST/FunctionDecl.hpp"

namespace NumbatLogic
{
	template <class T>
	class OwnedVector;
	class ValueType;
	class Validator;
	class Token;
	class TypeRef;
	class InternalString;
	class ClassDecl;
	template <class T>
	class Vector;
	class NamespaceNode;
	class GenericTypeDecl;
	class Assert;
	class EnumDecl;
	class EnumDeclValue;
	class DelegateDecl;
	class FunctionDecl;
}
namespace NumbatLogic
{
	ValueType::ValueType(Type eType)
	{
		m_bConst = false;
		m_eType = Type::VOID;
		m_pClassDecl = 0;
		m_ePointerType = TypeRef::PointerType::SHARED;
		m_pGenericTypeDecl = 0;
		m_pEnumDecl = 0;
		m_pEnumDeclValue = 0;
		m_pGenericValueTypeVector = 0;
		m_pDelegateDecl = 0;
		m_pFunctionDecl = 0;
		m_pNamespaceNode = 0;
		m_bConst = false;
		m_eType = eType;
		m_pGenericValueTypeVector = new OwnedVector<ValueType*>();
		m_ePointerType = TypeRef::PointerType::SHARED;
	}

	ValueType* ValueType::Clone()
	{
		ValueType* pValueType = new ValueType(m_eType);
		pValueType->m_bConst = m_bConst;
		pValueType->m_pClassDecl = m_pClassDecl;
		pValueType->m_ePointerType = m_ePointerType;
		pValueType->m_pGenericTypeDecl = m_pGenericTypeDecl;
		pValueType->m_pEnumDecl = m_pEnumDecl;
		pValueType->m_pEnumDeclValue = m_pEnumDeclValue;
		pValueType->m_pDelegateDecl = m_pDelegateDecl;
		pValueType->m_pFunctionDecl = m_pFunctionDecl;
		if (m_pGenericValueTypeVector != 0)
		{
			for (int i = 0; i < m_pGenericValueTypeVector->GetSize(); i++)
				pValueType->m_pGenericValueTypeVector->PushBack(m_pGenericValueTypeVector->Get(i)->Clone());
		}
		NumbatLogic::ValueType* __3239983008 = pValueType;
		pValueType = 0;
		return __3239983008;
	}

	bool ValueType::ValidateAssignable(ValueType* pTo, Validator* pValidator, Token* pToken)
	{
		if (pTo == 0)
		{
			if (pValidator != 0)
				pValidator->AddError("No pTo to compare to???", pToken->m_sFileName, pToken->m_nLine, pToken->m_nColumn);
			return false;
		}
		if (pTo->m_ePointerType != TypeRef::PointerType::OWNED && m_ePointerType == TypeRef::PointerType::OWNED_PREASSSIGN)
		{
			pValidator->AddError("Can't assign an owned pointer to a non-owned variable", pToken->m_sFileName, pToken->m_nLine, pToken->m_nColumn);
			return false;
		}
		if (pTo->m_ePointerType == TypeRef::PointerType::OWNED && (m_ePointerType != TypeRef::PointerType::OWNED_PREASSSIGN && m_eType != ValueType::Type::NULL_VALUE))
		{
			pValidator->AddError("Expected right side of = to be OWNED_PREASSSIGN (result of own)", pToken->m_sFileName, pToken->m_nLine, pToken->m_nColumn);
			return false;
		}
		else
			if (m_ePointerType == TypeRef::PointerType::TRANSITON)
			{
				pValidator->AddError("Cannot store a TRANSITION pointer (need to `own` it)", pToken->m_sFileName, pToken->m_nLine, pToken->m_nColumn);
				return false;
			}
		if ((m_pGenericValueTypeVector == 0) != (pTo->m_pGenericValueTypeVector == 0))
		{
			pValidator->AddError("m_pGenericValueTypeVector null mismatch", pToken->m_sFileName, pToken->m_nLine, pToken->m_nColumn);
			return false;
		}
		if (m_pGenericValueTypeVector != 0)
		{
			if (m_pGenericValueTypeVector->GetSize() != pTo->m_pGenericValueTypeVector->GetSize())
			{
				pValidator->AddError("m_pGenericValueTypeVector size mismatch", pToken->m_sFileName, pToken->m_nLine, pToken->m_nColumn);
				return false;
			}
			for (int i = 0; i < m_pGenericValueTypeVector->GetSize(); i++)
			{
				ValueType* pSubFrom = m_pGenericValueTypeVector->Get(i);
				ValueType* pSubTo = pTo->m_pGenericValueTypeVector->Get(i);
				if (pSubFrom->m_ePointerType != pSubTo->m_ePointerType)
				{
					pValidator->AddError("sub pointer type mismatch", pToken->m_sFileName, pToken->m_nLine, pToken->m_nColumn);
					return false;
				}
			}
		}
		return true;
	}

	TypeRef* ValueType::CreateTypeRef()
	{
		TypeRef* pTypeRef = new TypeRef();
		pTypeRef->m_bConst = m_bConst;
		pTypeRef->m_ePointerType = m_ePointerType;
		switch (m_eType)
		{
			case Type::CLASS_DECL_VALUE:
			{
				pTypeRef->m_pCloneToken = new Token();
				pTypeRef->m_pCloneToken->m_eType = Token::Type::TOKEN_IDENTIFIER;
				pTypeRef->m_pCloneToken->m_sValue = new InternalString(m_pClassDecl->m_pNameToken->m_sValue->GetExternalString());
				pTypeRef->m_pTypeToken = pTypeRef->m_pCloneToken;
				if (m_pGenericValueTypeVector != 0)
				{
					for (int i = 0; i < m_pGenericValueTypeVector->GetSize(); i++)
					{
						TypeRef* pGenericTypeRef = m_pGenericValueTypeVector->Get(i)->CreateTypeRef();
						pTypeRef->m_pGenericTypeRefVector->PushBack(pGenericTypeRef);
						NumbatLogic::TypeRef* __888078180 = pGenericTypeRef;
						pGenericTypeRef = 0;
						pTypeRef->AddChild(__888078180);
						if (pGenericTypeRef) delete pGenericTypeRef;
					}
				}
				NamespaceNode* pNamespaceNode = m_pClassDecl->m_pNamespaceNode;
				while (pNamespaceNode != 0 && pNamespaceNode->m_sName != 0)
				{
					TypeRef* pNamespaceTypeRef = new TypeRef();
					pNamespaceTypeRef->m_pCloneToken = new Token();
					pNamespaceTypeRef->m_pCloneToken->m_eType = Token::Type::TOKEN_IDENTIFIER;
					pNamespaceTypeRef->m_pCloneToken->m_sValue = new InternalString(pNamespaceNode->m_sName->GetExternalString());
					pNamespaceTypeRef->m_pTypeToken = pNamespaceTypeRef->m_pCloneToken;
					pNamespaceTypeRef->m_pChildTypeRef = pTypeRef;
					NumbatLogic::TypeRef* __1844115433 = pTypeRef;
					pTypeRef = 0;
					pNamespaceTypeRef->AddChild(__1844115433);
					NumbatLogic::TypeRef* __153808142 = pNamespaceTypeRef;
					pNamespaceTypeRef = 0;
					pTypeRef = __153808142;
					pNamespaceNode = pNamespaceNode->m_pParent;
					if (pNamespaceTypeRef) delete pNamespaceTypeRef;
				}
				NumbatLogic::TypeRef* __233495927 = pTypeRef;
				pTypeRef = 0;
				return __233495927;
			}

			case Type::GENERIC_TYPE_DECL_VALUE:
			{
				pTypeRef->m_pCloneToken = new Token();
				pTypeRef->m_pCloneToken->m_eType = Token::Type::TOKEN_IDENTIFIER;
				pTypeRef->m_pCloneToken->m_sValue = new InternalString(m_pGenericTypeDecl->m_pFirstToken->m_sValue->GetExternalString());
				pTypeRef->m_pTypeToken = pTypeRef->m_pCloneToken;
				NumbatLogic::TypeRef* __2901059164 = pTypeRef;
				pTypeRef = 0;
				return __2901059164;
			}

		}
		NumbatLogic::Assert::Plz(false);
		if (pTypeRef) delete pTypeRef;
		return 0;
	}

	void ValueType::StringifyType(InternalString* sOut)
	{
		switch (m_eType)
		{
			case Type::VOID:
			{
				sOut->Append("VOID");
				return;
			}

			case Type::INT:
			{
				sOut->Append("INT");
				return;
			}

			case Type::STRING:
			{
				sOut->Append("STRING");
				return;
			}

			case Type::BOOL:
			{
				sOut->Append("BOOL");
				return;
			}

			case Type::CHAR:
			{
				sOut->Append("CHAR");
				return;
			}

			case Type::UNICHAR:
			{
				sOut->Append("UNICHAR");
				return;
			}

			case Type::INSTANCE:
			{
				sOut->Append("INSTANCE");
				return;
			}

			case Type::VOIDPTR:
			{
				sOut->Append("VOIDPTR");
				return;
			}

			case Type::CLASS_DECL:
			{
				sOut->Append("CLASS_DECL");
				return;
			}

			case Type::CLASS_DECL_VALUE:
			{
				sOut->Append("CLASS_DECL_VALUE");
				return;
			}

			case Type::ENUM_DECL:
			{
				sOut->Append("ENUM_DECL");
				return;
			}

			case Type::ENUM_DECL_VALUE:
			{
				sOut->Append("ENUM_DECL_VALUE");
				return;
			}

			case Type::GENERIC_TYPE_DECL_VALUE:
			{
				sOut->Append("GENERIC_TYPE_DECL_VALUE");
				return;
			}

			case Type::STATIC_ARRAY:
			{
				sOut->Append("STATIC_ARRAY");
				return;
			}

			case Type::NULL_VALUE:
			{
				sOut->Append("NULL_VALUE");
				return;
			}

			case Type::DELEGATE_DECL_VALUE:
			{
				sOut->Append("DELEGATE_DECL_VALUE");
				return;
			}

			case Type::FUNCTION_DECL:
			{
				sOut->Append("FUNCTION_DECL");
				return;
			}

			case Type::NAMESPACE_NODE:
			{
				sOut->Append("NAMESPACE_NODE");
				return;
			}

		}
		sOut->Append("???");
	}

	ValueType::~ValueType()
	{
		if (m_pGenericValueTypeVector) delete m_pGenericValueTypeVector;
	}

}

