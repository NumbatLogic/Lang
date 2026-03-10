#include "MemberVarsSetDefaultStmt.hpp"
#include "AST.hpp"
#include "TorDecl.hpp"
#include "../Token.hpp"
#include "../Validator.hpp"
#include "MemberVarDecl.hpp"
#include "../Project.hpp"
#include "VarDecl.hpp"
#include "TypeRef.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
#include "../Util.hpp"
#include "../OutputBuilder.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"
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
#line 0 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
#line 5 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
	MemberVarsSetDefaultStmt::MemberVarsSetDefaultStmt()
	{
#line 7 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
		m_eType = AST::Type::MEMBER_VARS_SET_DEFAULT_STMT;
#line 8 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
		m_bStatement = true;
	}

#line 11 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
	void MemberVarsSetDefaultStmt::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
#line 13 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
		AST::Validate(pValidator, pParent);
#line 16 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
		if (m_pParent->m_eType == AST::Type::AST_SCOPE)
		{
#line 18 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
			if (m_pParent->m_pParent->m_eType == AST::Type::AST_TOR_DECL)
			{
#line 20 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
				TorDecl* pTorDecl = (TorDecl*)(m_pParent->m_pParent);
#line 21 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
				if (pTorDecl->m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_CONSTRUCT)
				{
#line 23 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
					if (m_pParent->m_pFirstChild != this)
					{
#line 25 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
						pValidator->AddError("MemberVarsSetDefaultStmt should be first child of constructor", 0, 0, 0);
#line 26 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
						return;
					}
#line 30 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
					if (pTorDecl->m_pParent->m_eType != AST::Type::AST_CLASS_DECL)
					{
#line 32 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
						pValidator->AddError("MemberVarsSetDefaultStmt parent constructor is not child of a class decl???", 0, 0, 0);
#line 33 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
						return;
					}
#line 36 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
					return;
				}
			}
		}
#line 41 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
		pValidator->AddError("Expected parent to be constructor", 0, 0, 0);
	}

#line 44 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
	void MemberVarsSetDefaultStmt::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 46 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
		if (eLanguage == AST::Language::CPP)
		{
#line 48 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
			AST* pChild = m_pParent->m_pParent->m_pParent->m_pFirstChild;
#line 49 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
			while (pChild != 0)
			{
#line 51 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
				if (pChild->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
				{
#line 53 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
					MemberVarDecl* pMemberVarDecl = (MemberVarDecl*)(pChild);
#line 55 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
					if (!pMemberVarDecl->m_bStatic)
					{
#line 57 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
						Project* pProject = GetProject();
#line 58 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
						if (pProject == 0 || pProject->m_pValidator == 0)
#line 59 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
							continue;
#line 60 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
						ValueType* pValueType = pMemberVarDecl->m_pVarDecl->m_pTypeRef->GetRecursiveValueType(pProject->m_pValidator->m_pResolver);
#line 62 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
						if (!pMemberVarDecl->m_pVarDecl->m_pTypeRef->m_bConst)
						{
#line 64 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
							if (pMemberVarDecl->m_pVarDecl->m_pArraySizeVector != 0)
							{
#line 66 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
								int nArraySizeSize = pMemberVarDecl->m_pVarDecl->m_pArraySizeVector->GetSize();
#line 67 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
								for (int i = 0; i < nArraySizeSize; i++)
								{
#line 69 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
									AST* pArraySize = pMemberVarDecl->m_pVarDecl->m_pArraySizeVector->Get(i);
#line 70 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
									Util::Pad(nDepth + i, pOutputBuilder->m_sOut);
#line 71 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
									pOutputBuilder->m_sOut->Append("for (int _x");
#line 72 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
									pOutputBuilder->m_sOut->AppendInt(i);
#line 73 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
									pOutputBuilder->m_sOut->Append(" = 0; _x");
#line 74 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
									pOutputBuilder->m_sOut->AppendInt(i);
#line 75 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
									pOutputBuilder->m_sOut->Append(" < ");
#line 76 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
									pArraySize->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 77 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
									pOutputBuilder->m_sOut->Append("; _x");
#line 78 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
									pOutputBuilder->m_sOut->AppendInt(i);
#line 79 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
									pOutputBuilder->m_sOut->Append("++)\n");
								}
#line 82 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
								Util::Pad(nDepth + nArraySizeSize, pOutputBuilder->m_sOut);
#line 83 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
								pOutputBuilder->m_sOut->AppendString(pMemberVarDecl->m_pVarDecl->m_pNameToken->GetString());
#line 85 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
								for (int i = 0; i < nArraySizeSize; i++)
								{
#line 87 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
									pOutputBuilder->m_sOut->Append("[_x");
#line 88 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
									pOutputBuilder->m_sOut->AppendInt(i);
#line 89 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
									pOutputBuilder->m_sOut->Append("]");
								}
#line 91 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
								pOutputBuilder->m_sOut->Append(" = ");
#line 94 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
								switch (pValueType->m_eType)
								{
									case ValueType::Type::INT:
									{
#line 98 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										pOutputBuilder->m_sOut->Append("0");
#line 99 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										break;
									}

									case ValueType::Type::BOOL:
									{
#line 103 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										pOutputBuilder->m_sOut->Append("false");
#line 104 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										break;
									}

									case ValueType::Type::CHAR:
									case ValueType::Type::UNICHAR:
									{
#line 109 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										pOutputBuilder->m_sOut->Append("'0'");
#line 110 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										break;
									}

									case ValueType::Type::CLASS_DECL_VALUE:
									case ValueType::Type::GENERIC_TYPE_DECL_VALUE:
									case ValueType::Type::DELEGATE_DECL_VALUE:
									case ValueType::Type::VOIDPTR:
									case ValueType::Type::STRING:
									{
#line 118 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										pOutputBuilder->m_sOut->Append("0");
#line 119 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										break;
									}

									case ValueType::Type::ENUM_DECL_VALUE:
									{
#line 123 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										if (pValueType->m_pEnumDecl == 0)
#line 124 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											pOutputBuilder->m_sOut->Append("no_m_pEnumDecl");
#line 125 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										EnumDeclValue* pEnumDeclValue = pValueType->m_pEnumDecl->m_pEnumDeclValueVector->Get(0);
#line 126 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										if (pValueType->m_pEnumDecl == 0)
#line 127 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											pOutputBuilder->m_sOut->Append("no_pEnumDeclValue");
#line 129 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										pMemberVarDecl->m_pVarDecl->m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 130 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										pOutputBuilder->m_sOut->Append("::");
#line 131 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										pEnumDeclValue->m_pFirstToken->Stringify(pOutputBuilder->m_sOut);
#line 132 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										break;
									}

									default:
									{
#line 136 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										pOutputBuilder->m_sOut->Append("???");
#line 137 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										pValueType->StringifyType(pOutputBuilder->m_sOut);
#line 138 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										break;
									}

								}
#line 141 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
								pOutputBuilder->m_sOut->Append(";\n");
							}
							else
							{
#line 146 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
								Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 147 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
								pOutputBuilder->m_sOut->AppendString(pMemberVarDecl->m_pVarDecl->m_pNameToken->GetString());
#line 148 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
								pOutputBuilder->m_sOut->Append(" = ");
#line 149 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
								switch (pValueType->m_eType)
								{
									case ValueType::Type::INT:
									{
#line 153 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										pOutputBuilder->m_sOut->Append("0");
#line 154 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										break;
									}

									case ValueType::Type::BOOL:
									{
#line 158 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										pOutputBuilder->m_sOut->Append("false");
#line 159 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										break;
									}

									case ValueType::Type::CHAR:
									case ValueType::Type::UNICHAR:
									{
#line 164 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										pOutputBuilder->m_sOut->Append("'0'");
#line 165 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										break;
									}

									case ValueType::Type::CLASS_DECL_VALUE:
									case ValueType::Type::GENERIC_TYPE_DECL_VALUE:
									case ValueType::Type::DELEGATE_DECL_VALUE:
									case ValueType::Type::VOIDPTR:
									case ValueType::Type::STRING:
									{
#line 173 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										pOutputBuilder->m_sOut->Append("0");
#line 174 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										break;
									}

									case ValueType::Type::ENUM_DECL_VALUE:
									{
#line 178 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										if (pValueType->m_pEnumDecl == 0)
#line 179 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											pOutputBuilder->m_sOut->Append("no_m_pEnumDecl");
#line 180 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										EnumDeclValue* pEnumDeclValue = pValueType->m_pEnumDecl->m_pEnumDeclValueVector->Get(0);
#line 181 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										if (pValueType->m_pEnumDecl == 0)
#line 182 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											pOutputBuilder->m_sOut->Append("no_pEnumDeclValue");
#line 184 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										pMemberVarDecl->m_pVarDecl->m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 185 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										pOutputBuilder->m_sOut->Append("::");
#line 186 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										pEnumDeclValue->m_pFirstToken->Stringify(pOutputBuilder->m_sOut);
#line 187 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										break;
									}

									default:
									{
#line 191 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										pOutputBuilder->m_sOut->Append("???");
#line 192 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										pValueType->StringifyType(pOutputBuilder->m_sOut);
#line 193 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										break;
									}

								}
#line 196 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
								pOutputBuilder->m_sOut->Append(";\n");
							}
						}
					}
				}
#line 201 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
				pChild = pChild->m_pNextSibling;
			}
		}
	}

}

