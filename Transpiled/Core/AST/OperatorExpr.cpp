#include "OperatorExpr.hpp"
#include "AST.hpp"
#include "../Validator.hpp"
#include "../Token.hpp"
#include "../ValueType.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "TypeRef.hpp"
#include "ClassDecl.hpp"

namespace NumbatLogic
{
	class OperatorExpr;
	class AST;
	class InternalString;
	class ClassDecl;
}
namespace NumbatLogic
{
	OperatorExpr::OperatorExpr()
	{
		m_pOperatorToken = 0;
		m_pLeft = 0;
		m_pRight = 0;
		m_pOwnedOperatorToken = 0;
		m_eType = AST::Type::AST_OPERATOR_EXPR;
	}

	OperatorExpr* OperatorExpr::Create(Token* pOperatorToken, AST* pLeft, AST* pRight)
	{
		OperatorExpr* pOperatorExpr = new OperatorExpr();
		AST* pOwnedLeft = pLeft;
		AST* pOwnedRight = pRight;
		pOperatorExpr->m_pFirstToken = pLeft->m_pFirstToken;
		pOperatorExpr->m_pOperatorToken = pOperatorToken;
		pOperatorExpr->m_pLeft = pOwnedLeft;
		pOperatorExpr->m_pRight = pOwnedRight;
		if (pLeft != 0)
		{
			NumbatLogic::AST* __2216975023 = pOwnedLeft;
			pOwnedLeft = 0;
			pOperatorExpr->AddChild(__2216975023);
		}
		if (pRight != 0)
		{
			NumbatLogic::AST* __766380242 = pOwnedRight;
			pOwnedRight = 0;
			pOperatorExpr->AddChild(__766380242);
		}
		{
			NumbatLogic::OperatorExpr* __304301329 = pOperatorExpr;
			pOperatorExpr = 0;
			{
				if (pOwnedLeft) delete pOwnedLeft;
				if (pOwnedRight) delete pOwnedRight;
				return __304301329;
			}
		}
	}

	AST* OperatorExpr::BaseClone()
	{
		AST* pLeft = 0;
		AST* pRight = 0;
		if (m_pLeft != 0)
			pLeft = m_pLeft->BaseClone();
		if (m_pRight != 0)
			pRight = m_pRight->BaseClone();
		{
			NumbatLogic::AST* __2461073728 = pLeft;
			pLeft = 0;
			{
				NumbatLogic::AST* __1625873296 = pRight;
				pRight = 0;
				{
					if (pLeft) delete pLeft;
					if (pRight) delete pRight;
					return Create(m_pOperatorToken, __2461073728, __1625873296);
				}
			}
		}
	}

	void OperatorExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		if (m_pLeft != 0)
		{
			m_pLeft->Validate(pValidator, pParent);
			if (m_pLeft->m_pValueType == 0)
			{
				pValidator->AddError("No ValueType for left of operator: ", m_pLeft->m_pFirstToken->m_sFileName, m_pLeft->m_pFirstToken->m_nLine, m_pLeft->m_pFirstToken->m_nColumn);
				return;
			}
			else
			{
				if (m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL || m_pLeft->m_pValueType->m_eType == ValueType::Type::ENUM_DECL || m_pLeft->m_pValueType->m_eType == ValueType::Type::NAMESPACE_NODE)
				{
					if (m_pOperatorToken->m_eType != Token::Type::TOKEN_DOUBLE_COLON)
					{
						pValidator->AddError("Expected TOKEN_DOUBLE_COLON ", m_pOperatorToken->m_sFileName, m_pOperatorToken->m_nLine, m_pOperatorToken->m_nColumn);
						return;
					}
					if (m_pRight == 0)
					{
						pValidator->AddError("Expected right side of TOKEN_DOUBLE_COLON operator", m_pOperatorToken->m_sFileName, m_pOperatorToken->m_nLine, m_pOperatorToken->m_nColumn);
						return;
					}
					if (m_pRight->m_eType != AST::Type::AST_IDENTIFIER && m_pRight->m_eType != AST::Type::AST_OPERATOR_EXPR && m_pRight->m_eType != AST::Type::AST_FUNCTION_CALL && m_pRight->m_eType != AST::Type::AST_ARRAY_LOOKUP)
					{
						InternalString* sTemp = new InternalString("Unexpected right side of TOKEN_DOUBLE_COLON operator: ");
						m_pRight->StringifyType(sTemp);
						pValidator->AddError(sTemp->GetExternalString(), m_pOperatorToken->m_sFileName, m_pOperatorToken->m_nLine, m_pOperatorToken->m_nColumn);
						{
							if (sTemp) delete sTemp;
							return;
						}
					}
					m_pRight->Validate(pValidator, this);
					if (m_pRight->m_pValueType == 0)
					{
						pValidator->AddError("No ValueType for right of operator: ", m_pRight->m_pFirstToken->m_sFileName, m_pRight->m_pFirstToken->m_nLine, m_pRight->m_pFirstToken->m_nColumn);
						return;
					}
					m_pValueType = m_pRight->m_pValueType->Clone();
					return;
				}
				if (m_pOperatorToken->m_eType == Token::Type::TOKEN_DOT)
				{
					if (m_pLeft->m_pValueType->m_eType == ValueType::Type::GENERIC_TYPE_DECL_VALUE)
					{
						if (m_pLeft->m_pValueType->m_pGenericTypeDecl == 0)
						{
							pValidator->AddError(" set but m_pGenericTypeDecl is null???", m_pOperatorToken->m_sFileName, m_pOperatorToken->m_nLine, m_pOperatorToken->m_nColumn);
							return;
						}
					}
					else if (m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
					{
						if (m_pLeft->m_pValueType->m_pClassDecl == 0)
						{
							pValidator->AddError(" set but m_pClassDecl is null???", m_pOperatorToken->m_sFileName, m_pOperatorToken->m_nLine, m_pOperatorToken->m_nColumn);
							return;
						}
					}
					else
					{
						pValidator->AddError("Expected ValueType::Type::CLASS_DECL_VALUE or ValueType::Type::GENERIC_TYPE_DECL_VALUE on left of TOKEN_DOT operator", m_pOperatorToken->m_sFileName, m_pOperatorToken->m_nLine, m_pOperatorToken->m_nColumn);
						return;
					}
					m_pRight->Validate(pValidator, this);
					if (m_pRight->m_pValueType == 0)
					{
						pValidator->AddError("No ValueType for right of operator: ", m_pRight->m_pFirstToken->m_sFileName, m_pRight->m_pFirstToken->m_nLine, m_pRight->m_pFirstToken->m_nColumn);
						return;
					}
					m_pValueType = m_pRight->m_pValueType->Clone();
					return;
				}
				if (m_pOperatorToken->m_eType == Token::Type::TOKEN_PLUS)
				{
					if (m_pLeft->m_pValueType->m_eType == ValueType::Type::STRING)
					{
						pValidator->AddError("Cannot concat strings with +", m_pOperatorToken->m_sFileName, m_pOperatorToken->m_nLine, m_pOperatorToken->m_nColumn);
						return;
					}
				}
				if (m_pOperatorToken->m_eType == Token::Type::TOKEN_DOUBLE_EQUALS || m_pOperatorToken->m_eType == Token::Type::TOKEN_NOT_EQUALS)
				{
					if (m_pRight == 0)
					{
						pValidator->AddError("Nohing on right side to compare?", m_pOperatorToken->m_sFileName, m_pOperatorToken->m_nLine, m_pOperatorToken->m_nColumn);
						return;
					}
					m_pRight->Validate(pValidator, this);
					if (m_pLeft->m_pValueType->m_eType == ValueType::Type::STRING && m_pRight->m_pValueType->m_eType == ValueType::Type::STRING)
					{
						pValidator->AddError("Cannot == or != strings use ExternalString::Equal", m_pOperatorToken->m_sFileName, m_pOperatorToken->m_nLine, m_pOperatorToken->m_nColumn);
						return;
					}
					m_pValueType = new ValueType(ValueType::Type::BOOL);
					return;
				}
				if (m_pRight != 0)
					m_pRight->Validate(pValidator, this);
				if (m_pOperatorToken->m_eType == Token::Type::TOKEN_EQUALS)
				{
					if (m_pRight->m_pValueType == 0)
					{
						pValidator->AddError("No ValueType for right of operator = ???", m_pRight->m_pFirstToken->m_sFileName, m_pRight->m_pFirstToken->m_nLine, m_pRight->m_pFirstToken->m_nColumn);
						return;
					}
					if (m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
					{
						if (m_pRight->m_pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
						{
							if (m_pLeft->m_pValueType->m_ePointerType == TypeRef::PointerType::OWNED && m_pRight->m_pValueType->m_ePointerType != TypeRef::PointerType::OWNED_PREASSSIGN)
							{
								pValidator->AddError("Expected right side of = to be OWNED_PREASSSIGN (result of own)", m_pOperatorToken->m_sFileName, m_pOperatorToken->m_nLine, m_pOperatorToken->m_nColumn);
								return;
							}
							if (m_pLeft->m_pValueType->m_ePointerType == TypeRef::PointerType::SHARED && m_pRight->m_pValueType->m_ePointerType == TypeRef::PointerType::OWNED_PREASSSIGN)
							{
								pValidator->AddError("Can't store an owned pointer in a shared pointer", m_pOperatorToken->m_sFileName, m_pOperatorToken->m_nLine, m_pOperatorToken->m_nColumn);
								return;
							}
							if (m_pRight->m_pValueType->m_ePointerType == TypeRef::PointerType::TRANSITON)
							{
								pValidator->AddError("Cannot store a TRANSITION pointer (need to `own` it)", m_pOperatorToken->m_sFileName, m_pOperatorToken->m_nLine, m_pOperatorToken->m_nColumn);
								return;
							}
							if (m_pLeft->m_pValueType->m_pClassDecl != m_pRight->m_pValueType->m_pClassDecl)
							{
								AddClassDeclReference(m_pRight->m_pValueType->m_pClassDecl, AST::OutputFile::SOURCE, false);
								ClassDecl* pBaseClassDecl = m_pRight->m_pValueType->m_pClassDecl->GetBaseClassDecl();
								while (pBaseClassDecl != 0)
								{
									if (pBaseClassDecl == m_pLeft->m_pValueType->m_pClassDecl)
										break;
									pBaseClassDecl = pBaseClassDecl->GetBaseClassDecl();
								}
								if (pBaseClassDecl != m_pLeft->m_pValueType->m_pClassDecl)
								{
									InternalString* sTemp = new InternalString("Can't assign ");
									sTemp->AppendString(m_pRight->m_pValueType->m_pClassDecl->m_pNameToken->GetString());
									sTemp->AppendString(" to ");
									sTemp->AppendString(m_pLeft->m_pValueType->m_pClassDecl->m_pNameToken->GetString());
									pValidator->AddError(sTemp->GetExternalString(), m_pOperatorToken->m_sFileName, m_pOperatorToken->m_nLine, m_pOperatorToken->m_nColumn);
									{
										if (sTemp) delete sTemp;
										return;
									}
								}
							}
						}
						else if (m_pRight->m_pValueType->m_eType == ValueType::Type::NULL_VALUE)
						{
						}
						else if (m_pRight->m_pValueType->m_eType == ValueType::Type::GENERIC_TYPE_DECL_VALUE)
						{
						}
						else
						{
							pValidator->AddError("Expected right side of = to also be CLASS_DECL_VALUE or NULL_VALUE\n", m_pOperatorToken->m_sFileName, m_pOperatorToken->m_nLine, m_pOperatorToken->m_nColumn);
							return;
						}
					}
					m_pValueType = m_pLeft->m_pValueType->Clone();
					return;
				}
				m_pValueType = m_pLeft->m_pValueType->Clone();
				return;
			}
		}
		if (m_pRight != 0)
		{
			m_pRight->Validate(pValidator, 0);
			if (m_pRight->m_pValueType == 0)
			{
			}
		}
		if (m_pParent != 0)
		{
		}
	}

	void OperatorExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		const char* sPad = " ";
		if (m_pOperatorToken->m_eType == Token::Type::TOKEN_MINUS_MINUS || m_pOperatorToken->m_eType == Token::Type::TOKEN_PLUS_PLUS || m_pOperatorToken->m_eType == Token::Type::TOKEN_DOT || m_pOperatorToken->m_eType == Token::Type::TOKEN_DOUBLE_COLON)
			sPad = "";
		const char* sOperator = m_pOperatorToken->GetString();
		if (eLanguage == AST::Language::CS && m_pOperatorToken->m_eType == Token::Type::TOKEN_DOUBLE_COLON)
			sOperator = ".";
		if (eLanguage == AST::Language::CPP && m_pOperatorToken->m_eType == Token::Type::TOKEN_DOT)
		{
			sOperator = "->";
			if (m_pLeft != 0 && m_pLeft->m_eType == AST::Type::BASE_EXPR)
				sOperator = "::";
		}
		m_pLeft->Stringify(eLanguage, eOutputFile, 0, sOut);
		sOut->Append(sPad);
		sOut->Append(sOperator);
		if (m_pRight != 0)
		{
			sOut->Append(sPad);
			m_pRight->Stringify(eLanguage, eOutputFile, 0, sOut);
		}
	}

	OperatorExpr::~OperatorExpr()
	{
		if (m_pOwnedOperatorToken) delete m_pOwnedOperatorToken;
	}

}

