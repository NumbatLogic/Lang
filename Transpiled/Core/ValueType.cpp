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
#line 0 "../../../Source/Core/ValueType.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/ValueType.nll"
#line 57 "../../../Source/Core/ValueType.nll"
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
#line 59 "../../../Source/Core/ValueType.nll"
		m_bConst = false;
#line 60 "../../../Source/Core/ValueType.nll"
		m_eType = eType;
#line 61 "../../../Source/Core/ValueType.nll"
		m_pGenericValueTypeVector = new OwnedVector<ValueType*>();
#line 62 "../../../Source/Core/ValueType.nll"
		m_ePointerType = TypeRef::PointerType::SHARED;
	}

#line 65 "../../../Source/Core/ValueType.nll"
	ValueType* ValueType::Clone()
	{
		ValueType* pValueType = new ValueType(m_eType);
#line 69 "../../../Source/Core/ValueType.nll"
		pValueType->m_bConst = m_bConst;
#line 71 "../../../Source/Core/ValueType.nll"
		pValueType->m_pClassDecl = m_pClassDecl;
#line 72 "../../../Source/Core/ValueType.nll"
		pValueType->m_ePointerType = m_ePointerType;
#line 73 "../../../Source/Core/ValueType.nll"
		pValueType->m_pGenericTypeDecl = m_pGenericTypeDecl;
#line 75 "../../../Source/Core/ValueType.nll"
		pValueType->m_pEnumDecl = m_pEnumDecl;
#line 76 "../../../Source/Core/ValueType.nll"
		pValueType->m_pEnumDeclValue = m_pEnumDeclValue;
#line 78 "../../../Source/Core/ValueType.nll"
		pValueType->m_pDelegateDecl = m_pDelegateDecl;
#line 79 "../../../Source/Core/ValueType.nll"
		pValueType->m_pFunctionDecl = m_pFunctionDecl;
#line 81 "../../../Source/Core/ValueType.nll"
		if (m_pGenericValueTypeVector != 0)
		{
#line 83 "../../../Source/Core/ValueType.nll"
			for (int i = 0; i < m_pGenericValueTypeVector->GetSize(); i++)
#line 84 "../../../Source/Core/ValueType.nll"
				pValueType->m_pGenericValueTypeVector->PushBack(m_pGenericValueTypeVector->Get(i)->Clone());
		}
		NumbatLogic::ValueType* __1751098362 = pValueType;
#line 87 "../../../Source/Core/ValueType.nll"
		pValueType = 0;
#line 87 "../../../Source/Core/ValueType.nll"
		return __1751098362;
	}

#line 90 "../../../Source/Core/ValueType.nll"
	bool ValueType::ValidateAssignable(ValueType* pTo, Validator* pValidator, Token* pToken)
	{
#line 92 "../../../Source/Core/ValueType.nll"
		if (pTo == 0)
		{
#line 94 "../../../Source/Core/ValueType.nll"
			if (pValidator != 0)
#line 95 "../../../Source/Core/ValueType.nll"
				pValidator->AddError("No pTo to compare to???", pToken->m_sFileName, pToken->m_nLine, pToken->m_nColumn);
#line 96 "../../../Source/Core/ValueType.nll"
			return false;
		}
#line 109 "../../../Source/Core/ValueType.nll"
		if (pTo->m_ePointerType != TypeRef::PointerType::OWNED && m_ePointerType == TypeRef::PointerType::OWNED_PREASSSIGN)
		{
			InternalString* sTemp = new InternalString("Can't assign an owned pointer to a non-owned variable. FROM[");
#line 112 "../../../Source/Core/ValueType.nll"
			StringifyType(sTemp);
#line 113 "../../../Source/Core/ValueType.nll"
			sTemp->Append(" ptr=");
#line 114 "../../../Source/Core/ValueType.nll"
			StringifyPointerType(sTemp, m_ePointerType);
#line 115 "../../../Source/Core/ValueType.nll"
			sTemp->Append("] TO[");
#line 116 "../../../Source/Core/ValueType.nll"
			pTo->StringifyType(sTemp);
#line 117 "../../../Source/Core/ValueType.nll"
			sTemp->Append(" ptr=");
#line 118 "../../../Source/Core/ValueType.nll"
			StringifyPointerType(sTemp, pTo->m_ePointerType);
#line 119 "../../../Source/Core/ValueType.nll"
			sTemp->Append("]");
#line 120 "../../../Source/Core/ValueType.nll"
			pValidator->AddError(sTemp->GetExternalString(), pToken->m_sFileName, pToken->m_nLine, pToken->m_nColumn);
			if (sTemp) delete sTemp;
#line 121 "../../../Source/Core/ValueType.nll"
			return false;
		}
#line 124 "../../../Source/Core/ValueType.nll"
		if (pTo->m_ePointerType == TypeRef::PointerType::OWNED && (m_ePointerType != TypeRef::PointerType::OWNED_PREASSSIGN && m_eType != ValueType::Type::NULL_VALUE))
		{
			InternalString* sTemp = new InternalString("Expected right side of = to be OWNED_PREASSSIGN (result of own). FROM[");
#line 127 "../../../Source/Core/ValueType.nll"
			StringifyType(sTemp);
#line 128 "../../../Source/Core/ValueType.nll"
			sTemp->Append(" ptr=");
#line 129 "../../../Source/Core/ValueType.nll"
			StringifyPointerType(sTemp, m_ePointerType);
#line 130 "../../../Source/Core/ValueType.nll"
			sTemp->Append("] TO[");
#line 131 "../../../Source/Core/ValueType.nll"
			pTo->StringifyType(sTemp);
#line 132 "../../../Source/Core/ValueType.nll"
			sTemp->Append(" ptr=");
#line 133 "../../../Source/Core/ValueType.nll"
			StringifyPointerType(sTemp, pTo->m_ePointerType);
#line 134 "../../../Source/Core/ValueType.nll"
			sTemp->Append("]");
#line 135 "../../../Source/Core/ValueType.nll"
			pValidator->AddError(sTemp->GetExternalString(), pToken->m_sFileName, pToken->m_nLine, pToken->m_nColumn);
			if (sTemp) delete sTemp;
#line 136 "../../../Source/Core/ValueType.nll"
			return false;
		}
		else
#line 138 "../../../Source/Core/ValueType.nll"
			if (m_ePointerType == TypeRef::PointerType::TRANSITON)
			{
				InternalString* sTemp = new InternalString("Cannot store a TRANSITION pointer (need to `own` it). FROM[");
#line 141 "../../../Source/Core/ValueType.nll"
				StringifyType(sTemp);
#line 142 "../../../Source/Core/ValueType.nll"
				sTemp->Append(" ptr=");
#line 143 "../../../Source/Core/ValueType.nll"
				StringifyPointerType(sTemp, m_ePointerType);
#line 144 "../../../Source/Core/ValueType.nll"
				sTemp->Append("] TO[");
#line 145 "../../../Source/Core/ValueType.nll"
				pTo->StringifyType(sTemp);
#line 146 "../../../Source/Core/ValueType.nll"
				sTemp->Append(" ptr=");
#line 147 "../../../Source/Core/ValueType.nll"
				StringifyPointerType(sTemp, pTo->m_ePointerType);
#line 148 "../../../Source/Core/ValueType.nll"
				sTemp->Append("]");
#line 149 "../../../Source/Core/ValueType.nll"
				pValidator->AddError(sTemp->GetExternalString(), pToken->m_sFileName, pToken->m_nLine, pToken->m_nColumn);
				if (sTemp) delete sTemp;
#line 150 "../../../Source/Core/ValueType.nll"
				return false;
			}
#line 154 "../../../Source/Core/ValueType.nll"
		if ((m_pGenericValueTypeVector == 0) != (pTo->m_pGenericValueTypeVector == 0))
		{
#line 156 "../../../Source/Core/ValueType.nll"
			pValidator->AddError("m_pGenericValueTypeVector null mismatch", pToken->m_sFileName, pToken->m_nLine, pToken->m_nColumn);
#line 157 "../../../Source/Core/ValueType.nll"
			return false;
		}
#line 160 "../../../Source/Core/ValueType.nll"
		if (m_pGenericValueTypeVector != 0)
		{
#line 162 "../../../Source/Core/ValueType.nll"
			if (m_pGenericValueTypeVector->GetSize() != pTo->m_pGenericValueTypeVector->GetSize())
			{
#line 164 "../../../Source/Core/ValueType.nll"
				pValidator->AddError("m_pGenericValueTypeVector size mismatch", pToken->m_sFileName, pToken->m_nLine, pToken->m_nColumn);
#line 165 "../../../Source/Core/ValueType.nll"
				return false;
			}
#line 168 "../../../Source/Core/ValueType.nll"
			for (int i = 0; i < m_pGenericValueTypeVector->GetSize(); i++)
			{
				ValueType* pSubFrom = m_pGenericValueTypeVector->Get(i);
				ValueType* pSubTo = pTo->m_pGenericValueTypeVector->Get(i);
#line 185 "../../../Source/Core/ValueType.nll"
				if (pSubFrom->m_ePointerType != pSubTo->m_ePointerType)
				{
#line 187 "../../../Source/Core/ValueType.nll"
					pValidator->AddError("sub pointer type mismatch", pToken->m_sFileName, pToken->m_nLine, pToken->m_nColumn);
#line 188 "../../../Source/Core/ValueType.nll"
					return false;
				}
			}
		}
#line 194 "../../../Source/Core/ValueType.nll"
		return true;
	}

#line 197 "../../../Source/Core/ValueType.nll"
	TypeRef* ValueType::CreateTypeRef()
	{
		TypeRef* pTypeRef = new TypeRef();
#line 200 "../../../Source/Core/ValueType.nll"
		pTypeRef->m_bConst = m_bConst;
#line 201 "../../../Source/Core/ValueType.nll"
		pTypeRef->m_ePointerType = m_ePointerType;
#line 203 "../../../Source/Core/ValueType.nll"
		switch (m_eType)
		{
			case Type::CLASS_DECL_VALUE:
			{
#line 207 "../../../Source/Core/ValueType.nll"
				pTypeRef->m_pCloneToken = new Token();
#line 208 "../../../Source/Core/ValueType.nll"
				pTypeRef->m_pCloneToken->m_eType = Token::Type::TOKEN_IDENTIFIER;
#line 209 "../../../Source/Core/ValueType.nll"
				pTypeRef->m_pCloneToken->m_sValue = new InternalString(m_pClassDecl->m_pNameToken->m_sValue->GetExternalString());
#line 210 "../../../Source/Core/ValueType.nll"
				pTypeRef->m_pTypeToken = pTypeRef->m_pCloneToken;
#line 213 "../../../Source/Core/ValueType.nll"
				if (m_pGenericValueTypeVector != 0)
				{
#line 215 "../../../Source/Core/ValueType.nll"
					for (int i = 0; i < m_pGenericValueTypeVector->GetSize(); i++)
					{
						TypeRef* pGenericTypeRef = m_pGenericValueTypeVector->Get(i)->CreateTypeRef();
#line 218 "../../../Source/Core/ValueType.nll"
						pTypeRef->m_pGenericTypeRefVector->PushBack(pGenericTypeRef);
						NumbatLogic::TypeRef* __3752644072 = pGenericTypeRef;
#line 219 "../../../Source/Core/ValueType.nll"
						pGenericTypeRef = 0;
#line 219 "../../../Source/Core/ValueType.nll"
						pTypeRef->AddChild(__3752644072);
						if (pGenericTypeRef) delete pGenericTypeRef;
					}
				}
				NamespaceNode* pNamespaceNode = m_pClassDecl->m_pNamespaceNode;
#line 226 "../../../Source/Core/ValueType.nll"
				while (pNamespaceNode != 0 && pNamespaceNode->m_sName != 0)
				{
					TypeRef* pNamespaceTypeRef = new TypeRef();
#line 230 "../../../Source/Core/ValueType.nll"
					pNamespaceTypeRef->m_pCloneToken = new Token();
#line 231 "../../../Source/Core/ValueType.nll"
					pNamespaceTypeRef->m_pCloneToken->m_eType = Token::Type::TOKEN_IDENTIFIER;
#line 232 "../../../Source/Core/ValueType.nll"
					pNamespaceTypeRef->m_pCloneToken->m_sValue = new InternalString(pNamespaceNode->m_sName->GetExternalString());
#line 233 "../../../Source/Core/ValueType.nll"
					pNamespaceTypeRef->m_pTypeToken = pNamespaceTypeRef->m_pCloneToken;
#line 235 "../../../Source/Core/ValueType.nll"
					pNamespaceTypeRef->m_pChildTypeRef = pTypeRef;
					NumbatLogic::TypeRef* __975974828 = pTypeRef;
#line 236 "../../../Source/Core/ValueType.nll"
					pTypeRef = 0;
#line 236 "../../../Source/Core/ValueType.nll"
					pNamespaceTypeRef->AddChild(__975974828);
					NumbatLogic::TypeRef* __2554801001 = pNamespaceTypeRef;
#line 238 "../../../Source/Core/ValueType.nll"
					pNamespaceTypeRef = 0;
#line 238 "../../../Source/Core/ValueType.nll"
					pTypeRef = __2554801001;
#line 240 "../../../Source/Core/ValueType.nll"
					pNamespaceNode = pNamespaceNode->m_pParent;
					if (pNamespaceTypeRef) delete pNamespaceTypeRef;
				}
				NumbatLogic::TypeRef* __976040424 = pTypeRef;
#line 243 "../../../Source/Core/ValueType.nll"
				pTypeRef = 0;
#line 243 "../../../Source/Core/ValueType.nll"
				return __976040424;
			}

			case Type::GENERIC_TYPE_DECL_VALUE:
			{
#line 247 "../../../Source/Core/ValueType.nll"
				pTypeRef->m_pCloneToken = new Token();
#line 248 "../../../Source/Core/ValueType.nll"
				pTypeRef->m_pCloneToken->m_eType = Token::Type::TOKEN_IDENTIFIER;
#line 249 "../../../Source/Core/ValueType.nll"
				pTypeRef->m_pCloneToken->m_sValue = new InternalString(m_pGenericTypeDecl->m_pFirstToken->m_sValue->GetExternalString());
#line 250 "../../../Source/Core/ValueType.nll"
				pTypeRef->m_pTypeToken = pTypeRef->m_pCloneToken;
				NumbatLogic::TypeRef* __976106021 = pTypeRef;
#line 251 "../../../Source/Core/ValueType.nll"
				pTypeRef = 0;
#line 251 "../../../Source/Core/ValueType.nll"
				return __976106021;
			}

		}
#line 255 "../../../Source/Core/ValueType.nll"
		Assert::Plz(false);
		if (pTypeRef) delete pTypeRef;
#line 256 "../../../Source/Core/ValueType.nll"
		return 0;
	}

#line 259 "../../../Source/Core/ValueType.nll"
	void ValueType::StringifyType(InternalString* sOut)
	{
#line 261 "../../../Source/Core/ValueType.nll"
		switch (m_eType)
		{
			case Type::VOID:
			{
#line 263 "../../../Source/Core/ValueType.nll"
				sOut->Append("VOID");
#line 263 "../../../Source/Core/ValueType.nll"
				return;
			}

			case Type::INT:
			{
#line 264 "../../../Source/Core/ValueType.nll"
				sOut->Append("INT");
#line 264 "../../../Source/Core/ValueType.nll"
				return;
			}

			case Type::STRING:
			{
#line 265 "../../../Source/Core/ValueType.nll"
				sOut->Append("STRING");
#line 265 "../../../Source/Core/ValueType.nll"
				return;
			}

			case Type::BOOL:
			{
#line 266 "../../../Source/Core/ValueType.nll"
				sOut->Append("BOOL");
#line 266 "../../../Source/Core/ValueType.nll"
				return;
			}

			case Type::CHAR:
			{
#line 267 "../../../Source/Core/ValueType.nll"
				sOut->Append("CHAR");
#line 267 "../../../Source/Core/ValueType.nll"
				return;
			}

			case Type::UNICHAR:
			{
#line 268 "../../../Source/Core/ValueType.nll"
				sOut->Append("UNICHAR");
#line 268 "../../../Source/Core/ValueType.nll"
				return;
			}

			case Type::INSTANCE:
			{
#line 269 "../../../Source/Core/ValueType.nll"
				sOut->Append("INSTANCE");
#line 269 "../../../Source/Core/ValueType.nll"
				return;
			}

			case Type::VOIDPTR:
			{
#line 270 "../../../Source/Core/ValueType.nll"
				sOut->Append("VOIDPTR");
#line 270 "../../../Source/Core/ValueType.nll"
				return;
			}

			case Type::CLASS_DECL:
			{
#line 271 "../../../Source/Core/ValueType.nll"
				sOut->Append("CLASS_DECL");
#line 271 "../../../Source/Core/ValueType.nll"
				return;
			}

			case Type::CLASS_DECL_VALUE:
			{
#line 272 "../../../Source/Core/ValueType.nll"
				sOut->Append("CLASS_DECL_VALUE");
#line 272 "../../../Source/Core/ValueType.nll"
				return;
			}

			case Type::ENUM_DECL:
			{
#line 273 "../../../Source/Core/ValueType.nll"
				sOut->Append("ENUM_DECL");
#line 273 "../../../Source/Core/ValueType.nll"
				return;
			}

			case Type::ENUM_DECL_VALUE:
			{
#line 274 "../../../Source/Core/ValueType.nll"
				sOut->Append("ENUM_DECL_VALUE");
#line 274 "../../../Source/Core/ValueType.nll"
				return;
			}

			case Type::GENERIC_TYPE_DECL_VALUE:
			{
#line 275 "../../../Source/Core/ValueType.nll"
				sOut->Append("GENERIC_TYPE_DECL_VALUE");
#line 275 "../../../Source/Core/ValueType.nll"
				return;
			}

			case Type::STATIC_ARRAY:
			{
#line 276 "../../../Source/Core/ValueType.nll"
				sOut->Append("STATIC_ARRAY");
#line 276 "../../../Source/Core/ValueType.nll"
				return;
			}

			case Type::NULL_VALUE:
			{
#line 277 "../../../Source/Core/ValueType.nll"
				sOut->Append("NULL_VALUE");
#line 277 "../../../Source/Core/ValueType.nll"
				return;
			}

			case Type::DELEGATE_DECL_VALUE:
			{
#line 278 "../../../Source/Core/ValueType.nll"
				sOut->Append("DELEGATE_DECL_VALUE");
#line 278 "../../../Source/Core/ValueType.nll"
				return;
			}

			case Type::FUNCTION_DECL:
			{
#line 279 "../../../Source/Core/ValueType.nll"
				sOut->Append("FUNCTION_DECL");
#line 279 "../../../Source/Core/ValueType.nll"
				return;
			}

			case Type::NAMESPACE_NODE:
			{
#line 280 "../../../Source/Core/ValueType.nll"
				sOut->Append("NAMESPACE_NODE");
#line 280 "../../../Source/Core/ValueType.nll"
				return;
			}

		}
#line 282 "../../../Source/Core/ValueType.nll"
		sOut->Append("???");
	}

#line 285 "../../../Source/Core/ValueType.nll"
	void ValueType::StringifyPointerType(InternalString* sOut, TypeRef::PointerType ePointerType)
	{
#line 287 "../../../Source/Core/ValueType.nll"
		switch (ePointerType)
		{
			case TypeRef::PointerType::SHARED:
			{
#line 289 "../../../Source/Core/ValueType.nll"
				sOut->Append("SHARED");
#line 289 "../../../Source/Core/ValueType.nll"
				return;
			}

			case TypeRef::PointerType::OWNED:
			{
#line 290 "../../../Source/Core/ValueType.nll"
				sOut->Append("OWNED");
#line 290 "../../../Source/Core/ValueType.nll"
				return;
			}

			case TypeRef::PointerType::TRANSITON:
			{
#line 291 "../../../Source/Core/ValueType.nll"
				sOut->Append("TRANSITON");
#line 291 "../../../Source/Core/ValueType.nll"
				return;
			}

			case TypeRef::PointerType::OWNED_PREASSSIGN:
			{
#line 292 "../../../Source/Core/ValueType.nll"
				sOut->Append("OWNED_PREASSSIGN");
#line 292 "../../../Source/Core/ValueType.nll"
				return;
			}

		}
#line 294 "../../../Source/Core/ValueType.nll"
		sOut->Append("UNKNOWN_PTR");
	}

#line 3 "../../../Source/Core/ValueType.nll"
	ValueType::~ValueType()
	{
		if (m_pGenericValueTypeVector) delete m_pGenericValueTypeVector;
	}

}

