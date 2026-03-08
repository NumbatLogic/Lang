#include "OperatorExpr.hpp"
#include "AST.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "../Token.hpp"
#include "../TokenContainer.hpp"
#include "../OffsetDatum.hpp"
#include "../Validator.hpp"
#include "../ValueType.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "TypeRef.hpp"
#include "ClassDecl.hpp"

namespace NumbatLogic
{
	class AST;
	class Assert;
	class Token;
	class TokenContainer;
	class OffsetDatum;
	class OperatorExpr;
	class Validator;
	class ValueType;
	class InternalString;
	class TypeRef;
	class ClassDecl;
}
namespace NumbatLogic
{
	OperatorExpr::OperatorExpr()
	{
		m_eOperatorType = OperatorExpr::OperatorType::LOGICAL_AND;
		m_pFirstOperatorToken = 0;
		m_pOwnedOperatorToken = 0;
		m_pLeft = 0;
		m_pRight = 0;
		m_eType = AST::Type::AST_OPERATOR_EXPR;
	}

	Token* OperatorExpr::GetFirstOperatorToken()
	{
		Assert::Plz(m_pFirstOperatorToken != 0);
		return m_pFirstOperatorToken;
	}

	OperatorExpr::OperatorType OperatorExpr::GetOperatorType()
	{
		return m_eOperatorType;
	}

	bool OperatorExpr::IsPostfix(OperatorExpr::OperatorType eOperatorType)
	{
		return (eOperatorType == OperatorType::DECREMENT || eOperatorType == OperatorType::INCREMENT);
	}

	int OperatorExpr::GetOperatorTokenCount(OperatorExpr::OperatorType eOp)
	{
		switch (eOp)
		{
			case OperatorType::UNKNOWN:
			{
				return 0;
			}

			case OperatorType::LEFT_SHIFT:
			case OperatorType::RIGHT_SHIFT:
			case OperatorType::EQUALITY:
			case OperatorType::INEQUALITY:
			case OperatorType::LESS_THAN_OR_EQUAL:
			case OperatorType::GREATER_THAN_OR_EQUAL:
			case OperatorType::ADD_ASSIGN:
			case OperatorType::SUBTRACT_ASSIGN:
			case OperatorType::LOGICAL_AND:
			case OperatorType::LOGICAL_OR:
			{
				return 2;
			}

			default:
			{
				return 1;
			}

		}
	}

	OperatorExpr::OperatorType OperatorExpr::GetOperatorTypeFromTokens(Token* pFirst, Token* pSecond)
	{
		Assert::Plz(pFirst != 0);
		if (pSecond != 0)
		{
			if (pFirst->m_eType == Token::Type::TOKEN_ANGLE_BRACKET_RIGHT && pSecond->m_eType == Token::Type::TOKEN_ANGLE_BRACKET_RIGHT)
				return OperatorType::RIGHT_SHIFT;
			if (pFirst->m_eType == Token::Type::TOKEN_ANGLE_BRACKET_LEFT && pSecond->m_eType == Token::Type::TOKEN_ANGLE_BRACKET_LEFT)
				return OperatorType::LEFT_SHIFT;
			if (pFirst->m_eType == Token::Type::TOKEN_EQUALS && pSecond->m_eType == Token::Type::TOKEN_EQUALS)
				return OperatorType::EQUALITY;
			if (pFirst->m_eType == Token::Type::TOKEN_BANG && pSecond->m_eType == Token::Type::TOKEN_EQUALS)
				return OperatorType::INEQUALITY;
			if (pFirst->m_eType == Token::Type::TOKEN_ANGLE_BRACKET_LEFT && pSecond->m_eType == Token::Type::TOKEN_EQUALS)
				return OperatorType::LESS_THAN_OR_EQUAL;
			if (pFirst->m_eType == Token::Type::TOKEN_ANGLE_BRACKET_RIGHT && pSecond->m_eType == Token::Type::TOKEN_EQUALS)
				return OperatorType::GREATER_THAN_OR_EQUAL;
			if (pFirst->m_eType == Token::Type::TOKEN_PLUS && pSecond->m_eType == Token::Type::TOKEN_EQUALS)
				return OperatorType::ADD_ASSIGN;
			if (pFirst->m_eType == Token::Type::TOKEN_MINUS && pSecond->m_eType == Token::Type::TOKEN_EQUALS)
				return OperatorType::SUBTRACT_ASSIGN;
			if (pFirst->m_eType == Token::Type::TOKEN_BITWISE_AND && pSecond->m_eType == Token::Type::TOKEN_BITWISE_AND)
				return OperatorType::LOGICAL_AND;
			if (pFirst->m_eType == Token::Type::TOKEN_BITWISE_OR && pSecond->m_eType == Token::Type::TOKEN_BITWISE_OR)
				return OperatorType::LOGICAL_OR;
		}
		switch (pFirst->m_eType)
		{
			case Token::Type::TOKEN_ANGLE_BRACKET_LEFT:
			{
				return OperatorType::LESS_THAN;
			}

			case Token::Type::TOKEN_ANGLE_BRACKET_RIGHT:
			{
				return OperatorType::GREATER_THAN;
			}

			case Token::Type::TOKEN_BITWISE_AND:
			{
				return OperatorType::BITWISE_AND;
			}

			case Token::Type::TOKEN_BITWISE_OR:
			{
				return OperatorType::BITWISE_OR;
			}

			case Token::Type::TOKEN_CARET:
			{
				return OperatorType::BITWISE_XOR;
			}

			case Token::Type::TOKEN_DIVIDE:
			{
				return OperatorType::DIVISION;
			}

			case Token::Type::TOKEN_DOT:
			{
				return OperatorType::MEMBER_ACCESS;
			}

			case Token::Type::TOKEN_DOUBLE_COLON:
			{
				return OperatorType::SCOPE_RESOLUTION;
			}

			case Token::Type::TOKEN_EQUALS:
			{
				return OperatorType::ASSIGNMENT;
			}

			case Token::Type::TOKEN_MINUS:
			{
				return OperatorType::SUBTRACTION;
			}

			case Token::Type::TOKEN_MINUS_MINUS:
			{
				return OperatorType::DECREMENT;
			}

			case Token::Type::TOKEN_MODULUS:
			{
				return OperatorType::MODULO;
			}

			case Token::Type::TOKEN_PLUS:
			{
				return OperatorType::ADDITION;
			}

			case Token::Type::TOKEN_PLUS_PLUS:
			{
				return OperatorType::INCREMENT;
			}

			case Token::Type::TOKEN_STAR:
			{
				return OperatorType::MULTIPLICATION;
			}

		}
		return OperatorType::UNKNOWN;
	}

	OperatorExpr::OperatorType OperatorExpr::PeekOperator(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		Token* pFirst = pTokenContainer->Peek(pOffsetDatum);
		if (pFirst == 0)
			return OperatorType::UNKNOWN;
		pOffsetDatum->m_nOffset++;
		Token* pSecond = pTokenContainer->Peek(pOffsetDatum);
		pOffsetDatum->m_nOffset--;
		OperatorType eType = GetOperatorTypeFromTokens(pFirst, pSecond);
		if (eType == OperatorType::UNKNOWN)
			return OperatorType::UNKNOWN;
		pOffsetDatum->m_nOffset += GetOperatorTokenCount(eType);
		return eType;
	}

	OperatorExpr* OperatorExpr::Create(OperatorExpr::OperatorType eOperatorType, Token* pFirstOperatorToken, AST* pLeft, AST* pRight)
	{
		Assert::Plz(pLeft != 0);
		if (IsPostfix(eOperatorType))
			Assert::Plz(pRight == 0);
		OperatorExpr* pOperatorExpr = new OperatorExpr();
		AST* pOwnedLeft = pLeft;
		AST* pOwnedRight = pRight;
		pOperatorExpr->m_pFirstToken = pLeft->m_pFirstToken;
		pOperatorExpr->m_eOperatorType = eOperatorType;
		pOperatorExpr->m_pFirstOperatorToken = pFirstOperatorToken;
		pOperatorExpr->m_pLeft = pOwnedLeft;
		pOperatorExpr->m_pRight = pOwnedRight;
		if (pLeft != 0)
		{
			NumbatLogic::AST* __4182507189 = pOwnedLeft;
			pOwnedLeft = 0;
			pOperatorExpr->AddChild(__4182507189);
		}
		if (pRight != 0)
		{
			NumbatLogic::AST* __2506675437 = pOwnedRight;
			pOwnedRight = 0;
			pOperatorExpr->AddChild(__2506675437);
		}
		NumbatLogic::OperatorExpr* __2365975170 = pOperatorExpr;
		pOperatorExpr = 0;
		if (pOwnedLeft) delete pOwnedLeft;
		if (pOwnedRight) delete pOwnedRight;
		return __2365975170;
	}

	AST* OperatorExpr::BaseClone()
	{
		AST* pLeft = 0;
		AST* pRight = 0;
		if (m_pLeft != 0)
			pLeft = m_pLeft->BaseClone();
		if (m_pRight != 0)
			pRight = m_pRight->BaseClone();
		Token* pOwnedClone = GetFirstOperatorToken()->Clone();
		NumbatLogic::AST* __3919341144 = pLeft;
		pLeft = 0;
		NumbatLogic::AST* __534460291 = pRight;
		pRight = 0;
		OperatorExpr* pResult = OperatorExpr::Create(m_eOperatorType, pOwnedClone, __3919341144, __534460291);
		NumbatLogic::Token* __417939336 = pOwnedClone;
		pOwnedClone = 0;
		pResult->m_pOwnedOperatorToken = __417939336;
		NumbatLogic::OperatorExpr* __3068673700 = pResult;
		pResult = 0;
		if (pLeft) delete pLeft;
		if (pRight) delete pRight;
		if (pOwnedClone) delete pOwnedClone;
		return __3068673700;
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
				Token* pOpToken = GetFirstOperatorToken();
				if (m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL || m_pLeft->m_pValueType->m_eType == ValueType::Type::ENUM_DECL || m_pLeft->m_pValueType->m_eType == ValueType::Type::NAMESPACE_NODE)
				{
					if (GetOperatorType() != OperatorType::SCOPE_RESOLUTION)
					{
						pValidator->AddError("Expected :: ", pOpToken->m_sFileName, pOpToken->m_nLine, pOpToken->m_nColumn);
						return;
					}
					if (m_pRight == 0)
					{
						pValidator->AddError("Expected right side of :: operator", pOpToken->m_sFileName, pOpToken->m_nLine, pOpToken->m_nColumn);
						return;
					}
					if (m_pRight->m_eType != AST::Type::AST_IDENTIFIER && m_pRight->m_eType != AST::Type::AST_OPERATOR_EXPR && m_pRight->m_eType != AST::Type::AST_FUNCTION_CALL && m_pRight->m_eType != AST::Type::AST_ARRAY_LOOKUP)
					{
						InternalString* sTemp = new InternalString("Unexpected right side of :: operator: ");
						m_pRight->StringifyType(sTemp);
						pValidator->AddError(sTemp->GetExternalString(), pOpToken->m_sFileName, pOpToken->m_nLine, pOpToken->m_nColumn);
						if (sTemp) delete sTemp;
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
				if (GetOperatorType() == OperatorType::MEMBER_ACCESS)
				{
					if (m_pLeft->m_pValueType->m_eType == ValueType::Type::GENERIC_TYPE_DECL_VALUE)
					{
						if (m_pLeft->m_pValueType->m_pGenericTypeDecl == 0)
						{
							pValidator->AddError(" set but m_pGenericTypeDecl is null???", pOpToken->m_sFileName, pOpToken->m_nLine, pOpToken->m_nColumn);
							return;
						}
					}
					else
						if (m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
						{
							if (m_pLeft->m_pValueType->m_pClassDecl == 0)
							{
								pValidator->AddError(" set but m_pClassDecl is null???", pOpToken->m_sFileName, pOpToken->m_nLine, pOpToken->m_nColumn);
								return;
							}
						}
						else
						{
							pValidator->AddError("Expected ValueType::Type::CLASS_DECL_VALUE or ValueType::Type::GENERIC_TYPE_DECL_VALUE on left of TOKEN_DOT operator", pOpToken->m_sFileName, pOpToken->m_nLine, pOpToken->m_nColumn);
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
				if (GetOperatorType() == OperatorType::ADDITION)
				{
					if (m_pLeft->m_pValueType->m_eType == ValueType::Type::STRING)
					{
						pValidator->AddError("Cannot concat strings with +", pOpToken->m_sFileName, pOpToken->m_nLine, pOpToken->m_nColumn);
						return;
					}
				}
				if (GetOperatorType() == OperatorType::EQUALITY || GetOperatorType() == OperatorType::INEQUALITY)
				{
					if (m_pRight == 0)
					{
						pValidator->AddError("Nohing on right side to compare?", pOpToken->m_sFileName, pOpToken->m_nLine, pOpToken->m_nColumn);
						return;
					}
					m_pRight->Validate(pValidator, this);
					if (m_pLeft->m_pValueType->m_eType == ValueType::Type::STRING && m_pRight->m_pValueType->m_eType == ValueType::Type::STRING)
					{
						pValidator->AddError("Cannot == or != strings use ExternalString::Equal", pOpToken->m_sFileName, pOpToken->m_nLine, pOpToken->m_nColumn);
						return;
					}
					m_pValueType = new ValueType(ValueType::Type::BOOL);
					return;
				}
				if (m_pRight != 0)
					m_pRight->Validate(pValidator, this);
				if (GetOperatorType() == OperatorType::ASSIGNMENT)
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
								InternalString* sTemp = new InternalString("Expected right side of = to be OWNED_PREASSSIGN (result of own). FROM[");
								m_pRight->m_pValueType->StringifyType(sTemp);
								if (m_pRight->m_pValueType->m_pClassDecl != 0)
								{
									sTemp->Append(" name=");
									sTemp->AppendString(m_pRight->m_pValueType->m_pClassDecl->m_pNameToken->GetString());
								}
								sTemp->Append(" ptr=");
								ValueType::StringifyPointerType(sTemp, m_pRight->m_pValueType->m_ePointerType);
								sTemp->Append("] TO[");
								m_pLeft->m_pValueType->StringifyType(sTemp);
								if (m_pLeft->m_pValueType->m_pClassDecl != 0)
								{
									sTemp->Append(" name=");
									sTemp->AppendString(m_pLeft->m_pValueType->m_pClassDecl->m_pNameToken->GetString());
								}
								sTemp->Append(" ptr=");
								ValueType::StringifyPointerType(sTemp, m_pLeft->m_pValueType->m_ePointerType);
								sTemp->Append("]");
								pValidator->AddError(sTemp->GetExternalString(), pOpToken->m_sFileName, pOpToken->m_nLine, pOpToken->m_nColumn);
								if (sTemp) delete sTemp;
								return;
							}
							if (m_pLeft->m_pValueType->m_ePointerType == TypeRef::PointerType::SHARED && m_pRight->m_pValueType->m_ePointerType == TypeRef::PointerType::OWNED_PREASSSIGN)
							{
								InternalString* sTemp = new InternalString("Can't store an owned pointer in a shared pointer. FROM[");
								m_pRight->m_pValueType->StringifyType(sTemp);
								if (m_pRight->m_pValueType->m_pClassDecl != 0)
								{
									sTemp->Append(" name=");
									sTemp->AppendString(m_pRight->m_pValueType->m_pClassDecl->m_pNameToken->GetString());
								}
								sTemp->Append(" ptr=");
								ValueType::StringifyPointerType(sTemp, m_pRight->m_pValueType->m_ePointerType);
								sTemp->Append("] TO[");
								m_pLeft->m_pValueType->StringifyType(sTemp);
								if (m_pLeft->m_pValueType->m_pClassDecl != 0)
								{
									sTemp->Append(" name=");
									sTemp->AppendString(m_pLeft->m_pValueType->m_pClassDecl->m_pNameToken->GetString());
								}
								sTemp->Append(" ptr=");
								ValueType::StringifyPointerType(sTemp, m_pLeft->m_pValueType->m_ePointerType);
								sTemp->Append("]");
								pValidator->AddError(sTemp->GetExternalString(), pOpToken->m_sFileName, pOpToken->m_nLine, pOpToken->m_nColumn);
								if (sTemp) delete sTemp;
								return;
							}
							if (m_pRight->m_pValueType->m_ePointerType == TypeRef::PointerType::TRANSITON)
							{
								InternalString* sTemp = new InternalString("Cannot store a TRANSITION pointer (need to `own` it). FROM[");
								m_pRight->m_pValueType->StringifyType(sTemp);
								if (m_pRight->m_pValueType->m_pClassDecl != 0)
								{
									sTemp->Append(" name=");
									sTemp->AppendString(m_pRight->m_pValueType->m_pClassDecl->m_pNameToken->GetString());
								}
								sTemp->Append(" ptr=");
								ValueType::StringifyPointerType(sTemp, m_pRight->m_pValueType->m_ePointerType);
								sTemp->Append("] TO[");
								m_pLeft->m_pValueType->StringifyType(sTemp);
								if (m_pLeft->m_pValueType->m_pClassDecl != 0)
								{
									sTemp->Append(" name=");
									sTemp->AppendString(m_pLeft->m_pValueType->m_pClassDecl->m_pNameToken->GetString());
								}
								sTemp->Append(" ptr=");
								ValueType::StringifyPointerType(sTemp, m_pLeft->m_pValueType->m_ePointerType);
								sTemp->Append("]");
								pValidator->AddError(sTemp->GetExternalString(), pOpToken->m_sFileName, pOpToken->m_nLine, pOpToken->m_nColumn);
								if (sTemp) delete sTemp;
								return;
							}
							if (m_pLeft->m_pValueType->m_pClassDecl != m_pRight->m_pValueType->m_pClassDecl)
							{
								AddClassDeclReference(m_pRight->m_pValueType->m_pClassDecl, AST::OutputFile::SOURCE, false);
								ClassDecl* pBaseClassDecl = m_pRight->m_pValueType->m_pClassDecl->GetBaseClassDecl(pValidator);
								while (pBaseClassDecl != 0)
								{
									if (pBaseClassDecl == m_pLeft->m_pValueType->m_pClassDecl)
										break;
									pBaseClassDecl = pBaseClassDecl->GetBaseClassDecl(pValidator);
								}
								if (pBaseClassDecl != m_pLeft->m_pValueType->m_pClassDecl)
								{
									InternalString* sTemp = new InternalString("Can't assign ");
									sTemp->AppendString(m_pRight->m_pValueType->m_pClassDecl->m_pNameToken->GetString());
									sTemp->AppendString(" to ");
									sTemp->AppendString(m_pLeft->m_pValueType->m_pClassDecl->m_pNameToken->GetString());
									pValidator->AddError(sTemp->GetExternalString(), pOpToken->m_sFileName, pOpToken->m_nLine, pOpToken->m_nColumn);
									if (sTemp) delete sTemp;
									return;
								}
							}
						}
						else
							if (m_pRight->m_pValueType->m_eType == ValueType::Type::NULL_VALUE)
							{
							}
							else
								if (m_pRight->m_pValueType->m_eType == ValueType::Type::GENERIC_TYPE_DECL_VALUE)
								{
								}
								else
								{
									pValidator->AddError("Expected right side of = to also be CLASS_DECL_VALUE or NULL_VALUE\n", pOpToken->m_sFileName, pOpToken->m_nLine, pOpToken->m_nColumn);
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

	const char* OperatorExpr::GetOperatorString(OperatorExpr::OperatorType eOperatorType)
	{
		switch (eOperatorType)
		{
			case OperatorType::LOGICAL_AND:
			{
				return "&&";
			}

			case OperatorType::LESS_THAN:
			{
				return "<";
			}

			case OperatorType::LESS_THAN_OR_EQUAL:
			{
				return "<=";
			}

			case OperatorType::GREATER_THAN:
			{
				return ">";
			}

			case OperatorType::GREATER_THAN_OR_EQUAL:
			{
				return ">=";
			}

			case OperatorType::BITWISE_AND:
			{
				return "&";
			}

			case OperatorType::BITWISE_OR:
			{
				return "|";
			}

			case OperatorType::BITWISE_XOR:
			{
				return "^";
			}

			case OperatorType::DIVISION:
			{
				return "/";
			}

			case OperatorType::MEMBER_ACCESS:
			{
				return ".";
			}

			case OperatorType::LEFT_SHIFT:
			{
				return "<<";
			}

			case OperatorType::RIGHT_SHIFT:
			{
				return ">>";
			}

			case OperatorType::SCOPE_RESOLUTION:
			{
				return "::";
			}

			case OperatorType::EQUALITY:
			{
				return "==";
			}

			case OperatorType::ASSIGNMENT:
			{
				return "=";
			}

			case OperatorType::SUBTRACTION:
			{
				return "-";
			}

			case OperatorType::SUBTRACT_ASSIGN:
			{
				return "-=";
			}

			case OperatorType::DECREMENT:
			{
				return "--";
			}

			case OperatorType::MODULO:
			{
				return "%";
			}

			case OperatorType::INEQUALITY:
			{
				return "!=";
			}

			case OperatorType::LOGICAL_OR:
			{
				return "||";
			}

			case OperatorType::ADDITION:
			{
				return "+";
			}

			case OperatorType::ADD_ASSIGN:
			{
				return "+=";
			}

			case OperatorType::INCREMENT:
			{
				return "++";
			}

			case OperatorType::MULTIPLICATION:
			{
				return "*";
			}

			default:
			{
				return "?";
			}

		}
	}

	void OperatorExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		OperatorType eOp = GetOperatorType();
		const char* sPad = " ";
		if (eOp == OperatorType::DECREMENT || eOp == OperatorType::INCREMENT || eOp == OperatorType::MEMBER_ACCESS || eOp == OperatorType::SCOPE_RESOLUTION)
			sPad = "";
		const char* sOperator = GetOperatorString(eOp);
		if (eLanguage == AST::Language::CS && eOp == OperatorType::SCOPE_RESOLUTION)
			sOperator = ".";
		if (eLanguage == AST::Language::CPP && eOp == OperatorType::MEMBER_ACCESS)
		{
			sOperator = "->";
			if (m_pLeft->m_eType == AST::Type::BASE_EXPR)
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

