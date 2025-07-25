#include "MemberVarsSetDefaultStmt.hpp"
#include "AST.hpp"
#include "TorDecl.hpp"
#include "../Token.hpp"
#include "../Validator.hpp"
#include "MemberVarDecl.hpp"
#include "VarDecl.hpp"
#include "TypeRef.hpp"
#include "../Util.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "../ValueType.hpp"
#include "EnumDecl.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
#include "EnumDeclValue.hpp"

namespace NumbatLogic
{
	class MemberVarsSetDefaultStmt;
	class TorDecl;
	class Token;
	class Validator;
	class AST;
	class MemberVarDecl;
	class ValueType;
	class VarDecl;
	class TypeRef;
	class Util;
	class InternalString;
	class EnumDeclValue;
	class EnumDecl;
	template <class T>
	class Vector;
}
namespace NumbatLogic
{
	MemberVarsSetDefaultStmt::MemberVarsSetDefaultStmt()
	{
		m_eType = AST::Type::MEMBER_VARS_SET_DEFAULT_STMT;
		m_bStatement = true;
	}

	void MemberVarsSetDefaultStmt::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
		if (m_pParent->m_eType == AST::Type::AST_SCOPE)
		{
			if (m_pParent->m_pParent->m_eType == AST::Type::AST_TOR_DECL)
			{
				TorDecl* pTorDecl = (TorDecl*)(m_pParent->m_pParent);
				if (pTorDecl->m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_CONSTRUCT)
				{
					if (m_pParent->m_pFirstChild != this)
					{
						pValidator->AddError("MemberVarsSetDefaultStmt should be first child of constructor", 0, 0, 0);
						return;
					}
					if (pTorDecl->m_pParent->m_eType != AST::Type::AST_CLASS_DECL)
					{
						pValidator->AddError("MemberVarsSetDefaultStmt parent constructor is not child of a class decl???", 0, 0, 0);
						return;
					}
					return;
				}
			}
		}
		pValidator->AddError("Expected parent to be constructor", 0, 0, 0);
	}

	void MemberVarsSetDefaultStmt::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		if (eLanguage == AST::Language::CPP)
		{
			AST* pChild = m_pParent->m_pParent->m_pParent->m_pFirstChild;
			while (pChild != 0)
			{
				if (pChild->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
				{
					MemberVarDecl* pMemberVarDecl = (MemberVarDecl*)(pChild);
					ValueType* pValueType = pMemberVarDecl->m_pVarDecl->m_pTypeRef->GetRecursiveValueType();
					if (!pMemberVarDecl->m_pVarDecl->m_pTypeRef->m_bConst)
					{
						if (pMemberVarDecl->m_pVarDecl->m_pArraySize != 0)
						{
							Util::Pad(nDepth, sOut);
							sOut->Append("for (int _x = 0; _x < ");
							pMemberVarDecl->m_pVarDecl->m_pArraySize->Stringify(eLanguage, eOutputFile, 0, sOut);
							sOut->Append("; _x++) ");
							sOut->AppendString(pMemberVarDecl->m_pVarDecl->m_pNameToken->GetString());
							sOut->Append("[_x] = ");
							switch (pValueType->m_eType)
							{
								case ValueType::Type::INT:
								{
									sOut->Append("0");
									break;
								}

								case ValueType::Type::BOOL:
								{
									sOut->Append("false");
									break;
								}

								case ValueType::Type::CHAR:
								case ValueType::Type::UNICHAR:
								{
									sOut->Append("'0'");
									break;
								}

								case ValueType::Type::CLASS_DECL_VALUE:
								case ValueType::Type::GENERIC_TYPE_DECL_VALUE:
								case ValueType::Type::DELEGATE_DECL_VALUE:
								case ValueType::Type::VOIDPTR:
								case ValueType::Type::STRING:
								{
									sOut->Append("0");
									break;
								}

								case ValueType::Type::ENUM_DECL_VALUE:
								{
									if (pValueType->m_pEnumDecl == 0)
										sOut->Append("no_m_pEnumDecl");
									EnumDeclValue* pEnumDeclValue = pValueType->m_pEnumDecl->m_pEnumDeclValueVector->Get(0);
									if (pValueType->m_pEnumDecl == 0)
										sOut->Append("no_pEnumDeclValue");
									pMemberVarDecl->m_pVarDecl->m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, sOut);
									sOut->Append("::");
									pEnumDeclValue->m_pFirstToken->Stringify(sOut);
									break;
								}

								default:
								{
									sOut->Append("???");
									pValueType->StringifyType(sOut);
									break;
								}

							}
							sOut->Append(";\n");
						}
						else
						{
							Util::Pad(nDepth, sOut);
							sOut->AppendString(pMemberVarDecl->m_pVarDecl->m_pNameToken->GetString());
							sOut->Append(" = ");
							switch (pValueType->m_eType)
							{
								case ValueType::Type::INT:
								{
									sOut->Append("0");
									break;
								}

								case ValueType::Type::BOOL:
								{
									sOut->Append("false");
									break;
								}

								case ValueType::Type::CHAR:
								case ValueType::Type::UNICHAR:
								{
									sOut->Append("'0'");
									break;
								}

								case ValueType::Type::CLASS_DECL_VALUE:
								case ValueType::Type::GENERIC_TYPE_DECL_VALUE:
								case ValueType::Type::DELEGATE_DECL_VALUE:
								case ValueType::Type::VOIDPTR:
								case ValueType::Type::STRING:
								{
									sOut->Append("0");
									break;
								}

								case ValueType::Type::ENUM_DECL_VALUE:
								{
									if (pValueType->m_pEnumDecl == 0)
										sOut->Append("no_m_pEnumDecl");
									EnumDeclValue* pEnumDeclValue = pValueType->m_pEnumDecl->m_pEnumDeclValueVector->Get(0);
									if (pValueType->m_pEnumDecl == 0)
										sOut->Append("no_pEnumDeclValue");
									pMemberVarDecl->m_pVarDecl->m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, sOut);
									sOut->Append("::");
									pEnumDeclValue->m_pFirstToken->Stringify(sOut);
									break;
								}

								default:
								{
									sOut->Append("???");
									pValueType->StringifyType(sOut);
									break;
								}

							}
							sOut->Append(";\n");
						}
					}
				}
				pChild = pChild->m_pNextSibling;
			}
		}
	}

}

