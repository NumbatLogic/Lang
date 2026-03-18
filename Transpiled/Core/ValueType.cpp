#include "ValueType.hpp"
#include "../../../LangShared/Transpiled/Vector/OwnedVector.hpp"
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
	class ValueType;
	template <class T>
	class OwnedVector;
	class Validator;
	class Token;
	class InternalString;
	class TypeRef;
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
#line 0 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
#line 57 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
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
#line 59 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
		m_bConst = false;
		m_eType = eType;
		m_pGenericValueTypeVector = new OwnedVector<ValueType*>();
		m_ePointerType = TypeRef::PointerType::SHARED;
	}

	ValueType* ValueType::Clone()
	{
		ValueType* pValueType = new ValueType(m_eType);
#line 69 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
		pValueType->m_bConst = m_bConst;
#line 71 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
		pValueType->m_pClassDecl = m_pClassDecl;
		pValueType->m_ePointerType = m_ePointerType;
		pValueType->m_pGenericTypeDecl = m_pGenericTypeDecl;
#line 75 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
		pValueType->m_pEnumDecl = m_pEnumDecl;
		pValueType->m_pEnumDeclValue = m_pEnumDeclValue;
#line 78 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
		pValueType->m_pDelegateDecl = m_pDelegateDecl;
		pValueType->m_pFunctionDecl = m_pFunctionDecl;
#line 81 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
		if (m_pGenericValueTypeVector != 0)
		{
			for (int i = 0; i < m_pGenericValueTypeVector->GetSize(); i++)
				pValueType->m_pGenericValueTypeVector->PushBack(m_pGenericValueTypeVector->Get(i)->Clone());
		}
		NumbatLogic::ValueType* __1751098362 = pValueType;
		pValueType = 0;
#line 87 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
		return __1751098362;
	}

	bool ValueType::ValidateAssignable(ValueType* pTo, Validator* pValidator, Token* pToken)
	{
		if (pTo == 0)
		{
			if (pValidator != 0)
				pValidator->AddError("No pTo to compare to???", pToken->m_sFileName, pToken->m_nLine, pToken->m_nColumn);
			return false;
		}
#line 109 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
		if (pTo->m_ePointerType != TypeRef::PointerType::OWNED && m_ePointerType == TypeRef::PointerType::OWNED_PREASSSIGN)
		{
			InternalString* sTemp = new InternalString("Can't assign an owned pointer to a non-owned variable. FROM[");
			StringifyType(sTemp);
			sTemp->Append(" ptr=");
			StringifyPointerType(sTemp, m_ePointerType);
			sTemp->Append("] TO[");
			pTo->StringifyType(sTemp);
			sTemp->Append(" ptr=");
			StringifyPointerType(sTemp, pTo->m_ePointerType);
			sTemp->Append("]");
			pValidator->AddError(sTemp->GetExternalString(), pToken->m_sFileName, pToken->m_nLine, pToken->m_nColumn);
			if (sTemp) delete sTemp;
#line 121 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
			return false;
		}
#line 124 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
		if (pTo->m_ePointerType == TypeRef::PointerType::OWNED && (m_ePointerType != TypeRef::PointerType::OWNED_PREASSSIGN && m_eType != ValueType::Type::NULL_VALUE))
		{
			InternalString* sTemp = new InternalString("Expected right side of = to be OWNED_PREASSSIGN (result of own). FROM[");
			StringifyType(sTemp);
			sTemp->Append(" ptr=");
			StringifyPointerType(sTemp, m_ePointerType);
			sTemp->Append("] TO[");
			pTo->StringifyType(sTemp);
			sTemp->Append(" ptr=");
			StringifyPointerType(sTemp, pTo->m_ePointerType);
			sTemp->Append("]");
			pValidator->AddError(sTemp->GetExternalString(), pToken->m_sFileName, pToken->m_nLine, pToken->m_nColumn);
			if (sTemp) delete sTemp;
#line 136 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
			return false;
		}
		else
#line 138 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
			if (m_ePointerType == TypeRef::PointerType::TRANSITON)
			{
				InternalString* sTemp = new InternalString("Cannot store a TRANSITION pointer (need to `own` it). FROM[");
				StringifyType(sTemp);
				sTemp->Append(" ptr=");
				StringifyPointerType(sTemp, m_ePointerType);
				sTemp->Append("] TO[");
				pTo->StringifyType(sTemp);
				sTemp->Append(" ptr=");
				StringifyPointerType(sTemp, pTo->m_ePointerType);
				sTemp->Append("]");
				pValidator->AddError(sTemp->GetExternalString(), pToken->m_sFileName, pToken->m_nLine, pToken->m_nColumn);
				if (sTemp) delete sTemp;
#line 150 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				return false;
			}
#line 154 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
		if ((m_pGenericValueTypeVector == 0) != (pTo->m_pGenericValueTypeVector == 0))
		{
			pValidator->AddError("m_pGenericValueTypeVector null mismatch", pToken->m_sFileName, pToken->m_nLine, pToken->m_nColumn);
			return false;
		}
#line 160 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
		if (m_pGenericValueTypeVector != 0)
		{
			if (m_pGenericValueTypeVector->GetSize() != pTo->m_pGenericValueTypeVector->GetSize())
			{
				pValidator->AddError("m_pGenericValueTypeVector size mismatch", pToken->m_sFileName, pToken->m_nLine, pToken->m_nColumn);
				return false;
			}
#line 168 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
			for (int i = 0; i < m_pGenericValueTypeVector->GetSize(); i++)
			{
				ValueType* pSubFrom = m_pGenericValueTypeVector->Get(i);
				ValueType* pSubTo = pTo->m_pGenericValueTypeVector->Get(i);
#line 185 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				if (pSubFrom->m_ePointerType != pSubTo->m_ePointerType)
				{
					pValidator->AddError("sub pointer type mismatch", pToken->m_sFileName, pToken->m_nLine, pToken->m_nColumn);
					return false;
				}
			}
		}
#line 194 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
		return true;
	}

	TypeRef* ValueType::CreateTypeRef()
	{
		TypeRef* pTypeRef = new TypeRef();
		pTypeRef->m_bConst = m_bConst;
		pTypeRef->m_ePointerType = m_ePointerType;
#line 203 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
		switch (m_eType)
		{
			case Type::CLASS_DECL_VALUE:
			{
				pTypeRef->m_pCloneToken = new Token();
				pTypeRef->m_pCloneToken->m_eType = Token::Type::TOKEN_IDENTIFIER;
				pTypeRef->m_pCloneToken->m_sValue = new InternalString(m_pClassDecl->m_pNameToken->m_sValue->GetExternalString());
				pTypeRef->m_pTypeToken = pTypeRef->m_pCloneToken;
#line 213 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				if (m_pGenericValueTypeVector != 0)
				{
					for (int i = 0; i < m_pGenericValueTypeVector->GetSize(); i++)
					{
						TypeRef* pGenericTypeRef = m_pGenericValueTypeVector->Get(i)->CreateTypeRef();
						pTypeRef->m_pGenericTypeRefVector->PushBack(pGenericTypeRef);
						NumbatLogic::TypeRef* __3752644072 = pGenericTypeRef;
#line 219 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
						pGenericTypeRef = 0;
#line 219 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
						pTypeRef->AddChild(__3752644072);
						if (pGenericTypeRef) delete pGenericTypeRef;
					}
				}
#line 225 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				NamespaceNode* pNamespaceNode = m_pClassDecl->m_pNamespaceNode;
				while (pNamespaceNode != 0 && pNamespaceNode->m_sName != 0)
				{
					TypeRef* pNamespaceTypeRef = new TypeRef();
#line 230 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
					pNamespaceTypeRef->m_pCloneToken = new Token();
					pNamespaceTypeRef->m_pCloneToken->m_eType = Token::Type::TOKEN_IDENTIFIER;
					pNamespaceTypeRef->m_pCloneToken->m_sValue = new InternalString(pNamespaceNode->m_sName->GetExternalString());
					pNamespaceTypeRef->m_pTypeToken = pNamespaceTypeRef->m_pCloneToken;
#line 235 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
					pNamespaceTypeRef->m_pChildTypeRef = pTypeRef;
					NumbatLogic::TypeRef* __975974828 = pTypeRef;
#line 236 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
					pTypeRef = 0;
#line 236 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
					pNamespaceTypeRef->AddChild(__975974828);
					NumbatLogic::TypeRef* __2554801001 = pNamespaceTypeRef;
					pNamespaceTypeRef = 0;
#line 238 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
					pTypeRef = __2554801001;
#line 240 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
					pNamespaceNode = pNamespaceNode->m_pParent;
					if (pNamespaceTypeRef) delete pNamespaceTypeRef;
				}
				NumbatLogic::TypeRef* __976040424 = pTypeRef;
#line 243 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				pTypeRef = 0;
#line 243 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				return __976040424;
			}

			case Type::GENERIC_TYPE_DECL_VALUE:
			{
#line 247 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				pTypeRef->m_pCloneToken = new Token();
				pTypeRef->m_pCloneToken->m_eType = Token::Type::TOKEN_IDENTIFIER;
				pTypeRef->m_pCloneToken->m_sValue = new InternalString(m_pGenericTypeDecl->m_pFirstToken->m_sValue->GetExternalString());
				pTypeRef->m_pTypeToken = pTypeRef->m_pCloneToken;
				NumbatLogic::TypeRef* __976106021 = pTypeRef;
#line 251 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				pTypeRef = 0;
#line 251 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				return __976106021;
			}

		}
		Assert::Plz(false);
		if (pTypeRef) delete pTypeRef;
#line 256 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
		return 0;
	}

	void ValueType::StringifyType(InternalString* sOut)
	{
		switch (m_eType)
		{
			case Type::VOID:
			{
#line 263 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				sOut->Append("VOID");
#line 263 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				return;
			}

			case Type::INT:
			{
#line 264 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				sOut->Append("INT");
#line 264 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				return;
			}

			case Type::STRING:
			{
#line 265 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				sOut->Append("STRING");
#line 265 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				return;
			}

			case Type::BOOL:
			{
#line 266 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				sOut->Append("BOOL");
#line 266 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				return;
			}

			case Type::CHAR:
			{
#line 267 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				sOut->Append("CHAR");
#line 267 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				return;
			}

			case Type::UNICHAR:
			{
#line 268 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				sOut->Append("UNICHAR");
#line 268 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				return;
			}

			case Type::INSTANCE:
			{
#line 269 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				sOut->Append("INSTANCE");
#line 269 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				return;
			}

			case Type::VOIDPTR:
			{
#line 270 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				sOut->Append("VOIDPTR");
#line 270 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				return;
			}

			case Type::CLASS_DECL:
			{
#line 271 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				sOut->Append("CLASS_DECL");
#line 271 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				return;
			}

			case Type::CLASS_DECL_VALUE:
			{
#line 272 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				sOut->Append("CLASS_DECL_VALUE");
#line 272 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				return;
			}

			case Type::ENUM_DECL:
			{
#line 273 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				sOut->Append("ENUM_DECL");
#line 273 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				return;
			}

			case Type::ENUM_DECL_VALUE:
			{
#line 274 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				sOut->Append("ENUM_DECL_VALUE");
#line 274 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				return;
			}

			case Type::GENERIC_TYPE_DECL_VALUE:
			{
#line 275 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				sOut->Append("GENERIC_TYPE_DECL_VALUE");
#line 275 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				return;
			}

			case Type::STATIC_ARRAY:
			{
#line 276 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				sOut->Append("STATIC_ARRAY");
#line 276 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				return;
			}

			case Type::NULL_VALUE:
			{
#line 277 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				sOut->Append("NULL_VALUE");
#line 277 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				return;
			}

			case Type::DELEGATE_DECL_VALUE:
			{
#line 278 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				sOut->Append("DELEGATE_DECL_VALUE");
#line 278 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				return;
			}

			case Type::FUNCTION_DECL:
			{
#line 279 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				sOut->Append("FUNCTION_DECL");
#line 279 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				return;
			}

			case Type::NAMESPACE_NODE:
			{
#line 280 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				sOut->Append("NAMESPACE_NODE");
#line 280 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				return;
			}

		}
#line 282 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
		sOut->Append("???");
	}

	void ValueType::StringifyPointerType(InternalString* sOut, TypeRef::PointerType ePointerType)
	{
		switch (ePointerType)
		{
			case TypeRef::PointerType::SHARED:
			{
#line 289 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				sOut->Append("SHARED");
#line 289 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				return;
			}

			case TypeRef::PointerType::OWNED:
			{
#line 290 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				sOut->Append("OWNED");
#line 290 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				return;
			}

			case TypeRef::PointerType::TRANSITON:
			{
#line 291 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				sOut->Append("TRANSITON");
#line 291 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				return;
			}

			case TypeRef::PointerType::OWNED_PREASSSIGN:
			{
#line 292 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				sOut->Append("OWNED_PREASSSIGN");
#line 292 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
				return;
			}

		}
#line 294 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
		sOut->Append("UNKNOWN_PTR");
	}

#line 3 "/home/cliffya/git/Lang/Source/Core/ValueType.nll"
	ValueType::~ValueType()
	{
		if (m_pGenericValueTypeVector) delete m_pGenericValueTypeVector;
	}

}

