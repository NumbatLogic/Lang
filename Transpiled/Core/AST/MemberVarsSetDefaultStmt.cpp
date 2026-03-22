#include "MemberVarsSetDefaultStmt.hpp"
#include "AST.hpp"
#include "TorDecl.hpp"
#include "../Token.hpp"
#include "../Validator.hpp"
#include "MemberVarDecl.hpp"
#include "../Project.hpp"
#include "VarDecl.hpp"
#include "TypeRef.hpp"
#include "../../../../LangShared/Source/Vector/CPP/Vector.hpp"
#include "../Util.hpp"
#include "../OutputBuilder.hpp"
#include "../../../../LangShared/Source/InternalString/CPP/InternalString.hpp"
#include "../ValueType.hpp"
#include "EnumDecl.hpp"
#include "EnumDeclValue.hpp"

namespace NumbatLogic
{
	class MemberVarsSetDefaultStmt;
	class AST;
	class TorDecl;
	class Token;
	class Validator;
	class MemberVarDecl;
	class Project;
	class ValueType;
	class VarDecl;
	class TypeRef;
	template <class T>
	class Vector;
	class Util;
	class OutputBuilder;
	class InternalString;
	class EnumDeclValue;
	class EnumDecl;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarsSetDefaultStmt.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarsSetDefaultStmt.nll"
#line 5 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarsSetDefaultStmt.nll"
	MemberVarsSetDefaultStmt::MemberVarsSetDefaultStmt()
	{
		m_eType = AST::Type::MEMBER_VARS_SET_DEFAULT_STMT;
		m_bStatement = true;
	}

	void MemberVarsSetDefaultStmt::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
#line 16 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarsSetDefaultStmt.nll"
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
#line 30 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarsSetDefaultStmt.nll"
					if (pTorDecl->m_pParent->m_eType != AST::Type::AST_CLASS_DECL)
					{
						pValidator->AddError("MemberVarsSetDefaultStmt parent constructor is not child of a class decl???", 0, 0, 0);
						return;
					}
#line 36 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarsSetDefaultStmt.nll"
					return;
				}
			}
		}
#line 41 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarsSetDefaultStmt.nll"
		pValidator->AddError("Expected parent to be constructor", 0, 0, 0);
	}

	void MemberVarsSetDefaultStmt::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		if (eLanguage == AST::Language::CPP)
		{
			AST* pChild = m_pParent->m_pParent->m_pParent->m_pFirstChild;
			while (pChild != 0)
			{
				if (pChild->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
				{
					MemberVarDecl* pMemberVarDecl = (MemberVarDecl*)(pChild);
#line 55 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarsSetDefaultStmt.nll"
					if (!pMemberVarDecl->m_bStatic)
					{
						Project* pProject = GetProject();
						if (pProject == 0 || pProject->m_pValidator == 0)
							continue;
						ValueType* pValueType = pMemberVarDecl->m_pVarDecl->m_pTypeRef->GetRecursiveValueType(pProject->m_pValidator->m_pResolver);
#line 62 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarsSetDefaultStmt.nll"
						if (!pMemberVarDecl->m_pVarDecl->m_pTypeRef->m_bConst)
						{
							if (pMemberVarDecl->m_pVarDecl->m_pArraySizeVector != 0)
							{
								int nArraySizeSize = pMemberVarDecl->m_pVarDecl->m_pArraySizeVector->GetSize();
								for (int i = 0; i < nArraySizeSize; i++)
								{
									AST* pArraySize = pMemberVarDecl->m_pVarDecl->m_pArraySizeVector->Get(i);
									Util::Pad(nDepth + i, pOutputBuilder->m_sOut);
									pOutputBuilder->m_sOut->Append("for (int _x");
									pOutputBuilder->m_sOut->AppendInt(i);
									pOutputBuilder->m_sOut->Append(" = 0; _x");
									pOutputBuilder->m_sOut->AppendInt(i);
									pOutputBuilder->m_sOut->Append(" < ");
									pArraySize->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
									pOutputBuilder->m_sOut->Append("; _x");
									pOutputBuilder->m_sOut->AppendInt(i);
									pOutputBuilder->m_sOut->Append("++)\n");
								}
#line 82 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarsSetDefaultStmt.nll"
								Util::Pad(nDepth + nArraySizeSize, pOutputBuilder->m_sOut);
								pOutputBuilder->m_sOut->AppendString(pMemberVarDecl->m_pVarDecl->m_pNameToken->GetString());
#line 85 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarsSetDefaultStmt.nll"
								for (int i = 0; i < nArraySizeSize; i++)
								{
									pOutputBuilder->m_sOut->Append("[_x");
									pOutputBuilder->m_sOut->AppendInt(i);
									pOutputBuilder->m_sOut->Append("]");
								}
								pOutputBuilder->m_sOut->Append(" = ");
#line 94 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarsSetDefaultStmt.nll"
								switch (pValueType->m_eType)
								{
									case ValueType::Type::INT:
									{
										pOutputBuilder->m_sOut->Append("0");
										break;
									}

									case ValueType::Type::BOOL:
									{
#line 103 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										pOutputBuilder->m_sOut->Append("false");
										break;
									}

									case ValueType::Type::CHAR:
									case ValueType::Type::UNICHAR:
									{
#line 109 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										pOutputBuilder->m_sOut->Append("'0'");
										break;
									}

									case ValueType::Type::CLASS_DECL_VALUE:
									case ValueType::Type::GENERIC_TYPE_DECL_VALUE:
									case ValueType::Type::DELEGATE_DECL_VALUE:
									case ValueType::Type::VOIDPTR:
									case ValueType::Type::STRING:
									{
#line 118 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										pOutputBuilder->m_sOut->Append("0");
										break;
									}

									case ValueType::Type::ENUM_DECL_VALUE:
									{
#line 123 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										if (pValueType->m_pEnumDecl == 0)
											pOutputBuilder->m_sOut->Append("no_m_pEnumDecl");
										EnumDeclValue* pEnumDeclValue = pValueType->m_pEnumDecl->m_pEnumDeclValueVector->Get(0);
										if (pValueType->m_pEnumDecl == 0)
											pOutputBuilder->m_sOut->Append("no_pEnumDeclValue");
#line 129 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										pMemberVarDecl->m_pVarDecl->m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
										pOutputBuilder->m_sOut->Append("::");
										pEnumDeclValue->m_pFirstToken->Stringify(pOutputBuilder->m_sOut);
										break;
									}

									default:
									{
#line 136 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										pOutputBuilder->m_sOut->Append("???");
										pValueType->StringifyType(pOutputBuilder->m_sOut);
										break;
									}

								}
#line 141 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarsSetDefaultStmt.nll"
								pOutputBuilder->m_sOut->Append(";\n");
							}
							else
							{
#line 146 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarsSetDefaultStmt.nll"
								Util::Pad(nDepth, pOutputBuilder->m_sOut);
								pOutputBuilder->m_sOut->AppendString(pMemberVarDecl->m_pVarDecl->m_pNameToken->GetString());
								pOutputBuilder->m_sOut->Append(" = ");
								switch (pValueType->m_eType)
								{
									case ValueType::Type::INT:
									{
										pOutputBuilder->m_sOut->Append("0");
										break;
									}

									case ValueType::Type::BOOL:
									{
#line 158 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										pOutputBuilder->m_sOut->Append("false");
										break;
									}

									case ValueType::Type::CHAR:
									case ValueType::Type::UNICHAR:
									{
#line 164 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										pOutputBuilder->m_sOut->Append("'0'");
										break;
									}

									case ValueType::Type::CLASS_DECL_VALUE:
									case ValueType::Type::GENERIC_TYPE_DECL_VALUE:
									case ValueType::Type::DELEGATE_DECL_VALUE:
									case ValueType::Type::VOIDPTR:
									case ValueType::Type::STRING:
									{
#line 173 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										pOutputBuilder->m_sOut->Append("0");
										break;
									}

									case ValueType::Type::ENUM_DECL_VALUE:
									{
#line 178 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										if (pValueType->m_pEnumDecl == 0)
											pOutputBuilder->m_sOut->Append("no_m_pEnumDecl");
										EnumDeclValue* pEnumDeclValue = pValueType->m_pEnumDecl->m_pEnumDeclValueVector->Get(0);
										if (pValueType->m_pEnumDecl == 0)
											pOutputBuilder->m_sOut->Append("no_pEnumDeclValue");
#line 184 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										pMemberVarDecl->m_pVarDecl->m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
										pOutputBuilder->m_sOut->Append("::");
										pEnumDeclValue->m_pFirstToken->Stringify(pOutputBuilder->m_sOut);
										break;
									}

									default:
									{
#line 191 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										pOutputBuilder->m_sOut->Append("???");
										pValueType->StringifyType(pOutputBuilder->m_sOut);
										break;
									}

								}
#line 196 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarsSetDefaultStmt.nll"
								pOutputBuilder->m_sOut->Append(";\n");
							}
						}
					}
				}
				pChild = pChild->m_pNextSibling;
			}
		}
	}

}

