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
#include "../OutputBuilder.hpp"

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
	class OutputBuilder;
}
#line 0 "../../../Source/Core/AST/OperatorExpr.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/OperatorExpr.nll"
#line 44 "../../../Source/Core/AST/OperatorExpr.nll"
	OperatorExpr::OperatorExpr()
	{
		m_eOperatorType = OperatorExpr::OperatorType::LOGICAL_AND;
		m_pFirstOperatorToken = 0;
		m_pOwnedOperatorToken = 0;
		m_pLeft = 0;
		m_pRight = 0;
#line 46 "../../../Source/Core/AST/OperatorExpr.nll"
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
#line 70 "../../../Source/Core/AST/OperatorExpr.nll"
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
			case OperatorType::MULTIPLY_ASSIGN:
			case OperatorType::DIVIDE_ASSIGN:
			case OperatorType::LOGICAL_AND:
			case OperatorType::LOGICAL_OR:
			{
#line 83 "../../../Source/Core/AST/OperatorExpr.nll"
				return 2;
			}

			case OperatorType::LEFT_SHIFT_ASSIGN:
			case OperatorType::RIGHT_SHIFT_ASSIGN:
			{
#line 86 "../../../Source/Core/AST/OperatorExpr.nll"
				return 3;
			}

			default:
			{
#line 88 "../../../Source/Core/AST/OperatorExpr.nll"
				return 1;
			}

		}
	}

#line 92 "../../../Source/Core/AST/OperatorExpr.nll"
	OperatorExpr::OperatorType OperatorExpr::GetOperatorTypeFromTokens(Token* pFirst, Token* pSecond, Token* pThird)
	{
		Assert::Plz(pFirst != 0);
#line 96 "../../../Source/Core/AST/OperatorExpr.nll"
		if (pThird != 0)
		{
			Assert::Plz(pSecond != 0);
#line 100 "../../../Source/Core/AST/OperatorExpr.nll"
			if (pFirst->m_eType == Token::Type::TOKEN_ANGLE_BRACKET_LEFT && pSecond->m_eType == Token::Type::TOKEN_ANGLE_BRACKET_LEFT && pThird->m_eType == Token::Type::TOKEN_EQUALS)
				return OperatorType::LEFT_SHIFT_ASSIGN;
			if (pFirst->m_eType == Token::Type::TOKEN_ANGLE_BRACKET_RIGHT && pSecond->m_eType == Token::Type::TOKEN_ANGLE_BRACKET_RIGHT && pThird->m_eType == Token::Type::TOKEN_EQUALS)
				return OperatorType::RIGHT_SHIFT_ASSIGN;
		}
#line 106 "../../../Source/Core/AST/OperatorExpr.nll"
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
			if (pFirst->m_eType == Token::Type::TOKEN_STAR && pSecond->m_eType == Token::Type::TOKEN_EQUALS)
				return OperatorType::MULTIPLY_ASSIGN;
			if (pFirst->m_eType == Token::Type::TOKEN_DIVIDE && pSecond->m_eType == Token::Type::TOKEN_EQUALS)
				return OperatorType::DIVIDE_ASSIGN;
			if (pFirst->m_eType == Token::Type::TOKEN_BITWISE_AND && pSecond->m_eType == Token::Type::TOKEN_BITWISE_AND)
				return OperatorType::LOGICAL_AND;
			if (pFirst->m_eType == Token::Type::TOKEN_BITWISE_OR && pSecond->m_eType == Token::Type::TOKEN_BITWISE_OR)
				return OperatorType::LOGICAL_OR;
		}
#line 134 "../../../Source/Core/AST/OperatorExpr.nll"
		switch (pFirst->m_eType)
		{
			case Token::Type::TOKEN_ANGLE_BRACKET_LEFT:
			{
#line 136 "../../../Source/Core/AST/OperatorExpr.nll"
				return OperatorType::LESS_THAN;
			}

			case Token::Type::TOKEN_ANGLE_BRACKET_RIGHT:
			{
#line 137 "../../../Source/Core/AST/OperatorExpr.nll"
				return OperatorType::GREATER_THAN;
			}

			case Token::Type::TOKEN_BITWISE_AND:
			{
#line 138 "../../../Source/Core/AST/OperatorExpr.nll"
				return OperatorType::BITWISE_AND;
			}

			case Token::Type::TOKEN_BITWISE_OR:
			{
#line 139 "../../../Source/Core/AST/OperatorExpr.nll"
				return OperatorType::BITWISE_OR;
			}

			case Token::Type::TOKEN_CARET:
			{
#line 140 "../../../Source/Core/AST/OperatorExpr.nll"
				return OperatorType::BITWISE_XOR;
			}

			case Token::Type::TOKEN_DIVIDE:
			{
#line 141 "../../../Source/Core/AST/OperatorExpr.nll"
				return OperatorType::DIVISION;
			}

			case Token::Type::TOKEN_DOT:
			{
#line 142 "../../../Source/Core/AST/OperatorExpr.nll"
				return OperatorType::MEMBER_ACCESS;
			}

			case Token::Type::TOKEN_DOUBLE_COLON:
			{
#line 143 "../../../Source/Core/AST/OperatorExpr.nll"
				return OperatorType::SCOPE_RESOLUTION;
			}

			case Token::Type::TOKEN_EQUALS:
			{
#line 144 "../../../Source/Core/AST/OperatorExpr.nll"
				return OperatorType::ASSIGNMENT;
			}

			case Token::Type::TOKEN_MINUS:
			{
#line 145 "../../../Source/Core/AST/OperatorExpr.nll"
				return OperatorType::SUBTRACTION;
			}

			case Token::Type::TOKEN_MINUS_MINUS:
			{
#line 146 "../../../Source/Core/AST/OperatorExpr.nll"
				return OperatorType::DECREMENT;
			}

			case Token::Type::TOKEN_MODULUS:
			{
#line 147 "../../../Source/Core/AST/OperatorExpr.nll"
				return OperatorType::MODULO;
			}

			case Token::Type::TOKEN_PLUS:
			{
#line 148 "../../../Source/Core/AST/OperatorExpr.nll"
				return OperatorType::ADDITION;
			}

			case Token::Type::TOKEN_PLUS_PLUS:
			{
#line 149 "../../../Source/Core/AST/OperatorExpr.nll"
				return OperatorType::INCREMENT;
			}

			case Token::Type::TOKEN_STAR:
			{
#line 150 "../../../Source/Core/AST/OperatorExpr.nll"
				return OperatorType::MULTIPLICATION;
			}

		}
#line 152 "../../../Source/Core/AST/OperatorExpr.nll"
		return OperatorType::UNKNOWN;
	}

	OperatorExpr::OperatorType OperatorExpr::PeekOperator(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		Token* pFirst = pTokenContainer->Peek(pOffsetDatum);
		if (pFirst == 0)
			return OperatorType::UNKNOWN;
		pOffsetDatum->m_nOffset++;
		Token* pSecond = pTokenContainer->Peek(pOffsetDatum);
		pOffsetDatum->m_nOffset++;
		Token* pThird = pTokenContainer->Peek(pOffsetDatum);
		pOffsetDatum->m_nOffset -= 2;
#line 166 "../../../Source/Core/AST/OperatorExpr.nll"
		OperatorType eType = GetOperatorTypeFromTokens(pFirst, pSecond, pThird);
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
#line 179 "../../../Source/Core/AST/OperatorExpr.nll"
		OperatorExpr* pOperatorExpr = new OperatorExpr();
#line 181 "../../../Source/Core/AST/OperatorExpr.nll"
		AST* pOwnedLeft = pLeft;
		AST* pOwnedRight = pRight;
#line 184 "../../../Source/Core/AST/OperatorExpr.nll"
		pOperatorExpr->m_pFirstToken = pLeft->m_pFirstToken;
		pOperatorExpr->m_eOperatorType = eOperatorType;
		pOperatorExpr->m_pFirstOperatorToken = pFirstOperatorToken;
		pOperatorExpr->m_pLeft = pOwnedLeft;
		pOperatorExpr->m_pRight = pOwnedRight;
#line 190 "../../../Source/Core/AST/OperatorExpr.nll"
		if (pLeft != 0)
		{
			NumbatLogic::AST* __4182703981 = pOwnedLeft;
#line 191 "../../../Source/Core/AST/OperatorExpr.nll"
			pOwnedLeft = 0;
#line 191 "../../../Source/Core/AST/OperatorExpr.nll"
			pOperatorExpr->AddChild(__4182703981);
		}
		if (pRight != 0)
		{
			NumbatLogic::AST* __2506872229 = pOwnedRight;
#line 194 "../../../Source/Core/AST/OperatorExpr.nll"
			pOwnedRight = 0;
#line 194 "../../../Source/Core/AST/OperatorExpr.nll"
			pOperatorExpr->AddChild(__2506872229);
		}
		NumbatLogic::OperatorExpr* __2366106373 = pOperatorExpr;
#line 196 "../../../Source/Core/AST/OperatorExpr.nll"
		pOperatorExpr = 0;
		if (pOwnedLeft) delete pOwnedLeft;
		if (pOwnedRight) delete pOwnedRight;
#line 196 "../../../Source/Core/AST/OperatorExpr.nll"
		return __2366106373;
	}

	AST* OperatorExpr::BaseClone()
	{
		AST* pLeft = 0;
		AST* pRight = 0;
#line 204 "../../../Source/Core/AST/OperatorExpr.nll"
		if (m_pLeft != 0)
			pLeft = m_pLeft->BaseClone();
#line 207 "../../../Source/Core/AST/OperatorExpr.nll"
		if (m_pRight != 0)
			pRight = m_pRight->BaseClone();
#line 210 "../../../Source/Core/AST/OperatorExpr.nll"
		Token* pOwnedClone = GetFirstOperatorToken()->Clone();
		NumbatLogic::AST* __3927143451 = pLeft;
#line 211 "../../../Source/Core/AST/OperatorExpr.nll"
		pLeft = 0;
		NumbatLogic::AST* __542262598 = pRight;
#line 211 "../../../Source/Core/AST/OperatorExpr.nll"
		pRight = 0;
#line 211 "../../../Source/Core/AST/OperatorExpr.nll"
		OperatorExpr* pResult = OperatorExpr::Create(m_eOperatorType, pOwnedClone, __3927143451, __542262598);
		NumbatLogic::Token* __425741643 = pOwnedClone;
#line 212 "../../../Source/Core/AST/OperatorExpr.nll"
		pOwnedClone = 0;
#line 212 "../../../Source/Core/AST/OperatorExpr.nll"
		pResult->m_pOwnedOperatorToken = __425741643;
		NumbatLogic::OperatorExpr* __3076476007 = pResult;
#line 213 "../../../Source/Core/AST/OperatorExpr.nll"
		pResult = 0;
		if (pLeft) delete pLeft;
		if (pRight) delete pRight;
		if (pOwnedClone) delete pOwnedClone;
#line 213 "../../../Source/Core/AST/OperatorExpr.nll"
		return __3076476007;
	}

	void OperatorExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
#line 234 "../../../Source/Core/AST/OperatorExpr.nll"
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
#line 258 "../../../Source/Core/AST/OperatorExpr.nll"
					if (m_pRight->m_eType != AST::Type::AST_IDENTIFIER && m_pRight->m_eType != AST::Type::AST_OPERATOR_EXPR && m_pRight->m_eType != AST::Type::AST_FUNCTION_CALL && m_pRight->m_eType != AST::Type::AST_ARRAY_LOOKUP)
					{
						InternalString* sTemp = new InternalString("Unexpected right side of :: operator: ");
						m_pRight->StringifyType(sTemp);
#line 263 "../../../Source/Core/AST/OperatorExpr.nll"
						pValidator->AddError(sTemp->GetExternalString(), pOpToken->m_sFileName, pOpToken->m_nLine, pOpToken->m_nColumn);
						if (sTemp) delete sTemp;
#line 264 "../../../Source/Core/AST/OperatorExpr.nll"
						return;
					}
#line 267 "../../../Source/Core/AST/OperatorExpr.nll"
					m_pRight->Validate(pValidator, this);
					if (m_pRight->m_pValueType == 0)
					{
						pValidator->AddError("No ValueType for right of operator: ", m_pRight->m_pFirstToken->m_sFileName, m_pRight->m_pFirstToken->m_nLine, m_pRight->m_pFirstToken->m_nColumn);
						return;
					}
#line 274 "../../../Source/Core/AST/OperatorExpr.nll"
					m_pValueType = m_pRight->m_pValueType->Clone();
#line 276 "../../../Source/Core/AST/OperatorExpr.nll"
					return;
				}
#line 279 "../../../Source/Core/AST/OperatorExpr.nll"
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
#line 289 "../../../Source/Core/AST/OperatorExpr.nll"
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
#line 303 "../../../Source/Core/AST/OperatorExpr.nll"
					m_pRight->Validate(pValidator, this);
					if (m_pRight->m_pValueType == 0)
					{
						pValidator->AddError("No ValueType for right of operator: ", m_pRight->m_pFirstToken->m_sFileName, m_pRight->m_pFirstToken->m_nLine, m_pRight->m_pFirstToken->m_nColumn);
						return;
					}
#line 310 "../../../Source/Core/AST/OperatorExpr.nll"
					m_pValueType = m_pRight->m_pValueType->Clone();
					return;
				}
#line 314 "../../../Source/Core/AST/OperatorExpr.nll"
				if (GetOperatorType() == OperatorType::ADDITION)
				{
					if (m_pLeft->m_pValueType->m_eType == ValueType::Type::STRING)
					{
						pValidator->AddError("Cannot concat strings with +", pOpToken->m_sFileName, pOpToken->m_nLine, pOpToken->m_nColumn);
						return;
					}
				}
#line 323 "../../../Source/Core/AST/OperatorExpr.nll"
				if (GetOperatorType() == OperatorType::EQUALITY || GetOperatorType() == OperatorType::INEQUALITY)
				{
					if (m_pRight == 0)
					{
						pValidator->AddError("Nohing on right side to compare?", pOpToken->m_sFileName, pOpToken->m_nLine, pOpToken->m_nColumn);
						return;
					}
#line 331 "../../../Source/Core/AST/OperatorExpr.nll"
					m_pRight->Validate(pValidator, this);
#line 333 "../../../Source/Core/AST/OperatorExpr.nll"
					if (m_pLeft->m_pValueType->m_eType == ValueType::Type::STRING && m_pRight->m_pValueType->m_eType == ValueType::Type::STRING)
					{
						pValidator->AddError("Cannot == or != strings use ExternalString::Equal", pOpToken->m_sFileName, pOpToken->m_nLine, pOpToken->m_nColumn);
						return;
					}
#line 339 "../../../Source/Core/AST/OperatorExpr.nll"
					m_pValueType = new ValueType(ValueType::Type::BOOL);
					return;
				}
#line 343 "../../../Source/Core/AST/OperatorExpr.nll"
				if (m_pRight != 0)
					m_pRight->Validate(pValidator, this);
#line 346 "../../../Source/Core/AST/OperatorExpr.nll"
				if (GetOperatorType() == OperatorType::ASSIGNMENT)
				{
					if (m_pRight->m_pValueType == 0)
					{
						pValidator->AddError("No ValueType for right of operator = ???", m_pRight->m_pFirstToken->m_sFileName, m_pRight->m_pFirstToken->m_nLine, m_pRight->m_pFirstToken->m_nColumn);
						return;
					}
#line 354 "../../../Source/Core/AST/OperatorExpr.nll"
					if (m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
					{
						if (m_pRight->m_pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
						{
#line 362 "../../../Source/Core/AST/OperatorExpr.nll"
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
#line 384 "../../../Source/Core/AST/OperatorExpr.nll"
								return;
							}
#line 387 "../../../Source/Core/AST/OperatorExpr.nll"
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
#line 409 "../../../Source/Core/AST/OperatorExpr.nll"
								return;
							}
#line 412 "../../../Source/Core/AST/OperatorExpr.nll"
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
#line 434 "../../../Source/Core/AST/OperatorExpr.nll"
								return;
							}
#line 439 "../../../Source/Core/AST/OperatorExpr.nll"
							if (m_pLeft->m_pValueType->m_pClassDecl != m_pRight->m_pValueType->m_pClassDecl)
							{
#line 442 "../../../Source/Core/AST/OperatorExpr.nll"
								AddClassDeclReference(m_pRight->m_pValueType->m_pClassDecl, AST::OutputFile::SOURCE, false);
#line 445 "../../../Source/Core/AST/OperatorExpr.nll"
								ClassDecl* pBaseClassDecl = m_pRight->m_pValueType->m_pClassDecl->GetBaseClassDecl(pValidator);
								while (pBaseClassDecl != 0)
								{
									if (pBaseClassDecl == m_pLeft->m_pValueType->m_pClassDecl)
										break;
									pBaseClassDecl = pBaseClassDecl->GetBaseClassDecl(pValidator);
								}
#line 453 "../../../Source/Core/AST/OperatorExpr.nll"
								if (pBaseClassDecl != m_pLeft->m_pValueType->m_pClassDecl)
								{
									InternalString* sTemp = new InternalString("Can't assign ");
									sTemp->AppendString(m_pRight->m_pValueType->m_pClassDecl->m_pNameToken->GetString());
									sTemp->AppendString(" to ");
									sTemp->AppendString(m_pLeft->m_pValueType->m_pClassDecl->m_pNameToken->GetString());
#line 460 "../../../Source/Core/AST/OperatorExpr.nll"
									pValidator->AddError(sTemp->GetExternalString(), pOpToken->m_sFileName, pOpToken->m_nLine, pOpToken->m_nColumn);
									if (sTemp) delete sTemp;
#line 461 "../../../Source/Core/AST/OperatorExpr.nll"
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
#line 476 "../../../Source/Core/AST/OperatorExpr.nll"
									pValidator->AddError("Expected right side of = to also be CLASS_DECL_VALUE or NULL_VALUE\n", pOpToken->m_sFileName, pOpToken->m_nLine, pOpToken->m_nColumn);
									return;
								}
					}
#line 481 "../../../Source/Core/AST/OperatorExpr.nll"
					m_pValueType = m_pLeft->m_pValueType->Clone();
					return;
				}
#line 487 "../../../Source/Core/AST/OperatorExpr.nll"
				m_pValueType = m_pLeft->m_pValueType->Clone();
				return;
			}
		}
#line 492 "../../../Source/Core/AST/OperatorExpr.nll"
		if (m_pRight != 0)
		{
			m_pRight->Validate(pValidator, 0);
			if (m_pRight->m_pValueType == 0)
			{
			}
		}
#line 501 "../../../Source/Core/AST/OperatorExpr.nll"
		if (m_pParent != 0)
		{
		}
	}

#line 508 "../../../Source/Core/AST/OperatorExpr.nll"
	const char* OperatorExpr::GetOperatorString(OperatorExpr::OperatorType eOperatorType)
	{
		switch (eOperatorType)
		{
			case OperatorType::LOGICAL_AND:
			{
#line 512 "../../../Source/Core/AST/OperatorExpr.nll"
				return "&&";
			}

			case OperatorType::LESS_THAN:
			{
#line 513 "../../../Source/Core/AST/OperatorExpr.nll"
				return "<";
			}

			case OperatorType::LESS_THAN_OR_EQUAL:
			{
#line 514 "../../../Source/Core/AST/OperatorExpr.nll"
				return "<=";
			}

			case OperatorType::GREATER_THAN:
			{
#line 515 "../../../Source/Core/AST/OperatorExpr.nll"
				return ">";
			}

			case OperatorType::GREATER_THAN_OR_EQUAL:
			{
#line 516 "../../../Source/Core/AST/OperatorExpr.nll"
				return ">=";
			}

			case OperatorType::BITWISE_AND:
			{
#line 517 "../../../Source/Core/AST/OperatorExpr.nll"
				return "&";
			}

			case OperatorType::BITWISE_OR:
			{
#line 518 "../../../Source/Core/AST/OperatorExpr.nll"
				return "|";
			}

			case OperatorType::BITWISE_XOR:
			{
#line 519 "../../../Source/Core/AST/OperatorExpr.nll"
				return "^";
			}

			case OperatorType::DIVISION:
			{
#line 520 "../../../Source/Core/AST/OperatorExpr.nll"
				return "/";
			}

			case OperatorType::MEMBER_ACCESS:
			{
#line 521 "../../../Source/Core/AST/OperatorExpr.nll"
				return ".";
			}

			case OperatorType::LEFT_SHIFT:
			{
#line 522 "../../../Source/Core/AST/OperatorExpr.nll"
				return "<<";
			}

			case OperatorType::RIGHT_SHIFT:
			{
#line 523 "../../../Source/Core/AST/OperatorExpr.nll"
				return ">>";
			}

			case OperatorType::SCOPE_RESOLUTION:
			{
#line 524 "../../../Source/Core/AST/OperatorExpr.nll"
				return "::";
			}

			case OperatorType::EQUALITY:
			{
#line 525 "../../../Source/Core/AST/OperatorExpr.nll"
				return "==";
			}

			case OperatorType::ASSIGNMENT:
			{
#line 526 "../../../Source/Core/AST/OperatorExpr.nll"
				return "=";
			}

			case OperatorType::SUBTRACTION:
			{
#line 527 "../../../Source/Core/AST/OperatorExpr.nll"
				return "-";
			}

			case OperatorType::SUBTRACT_ASSIGN:
			{
#line 528 "../../../Source/Core/AST/OperatorExpr.nll"
				return "-=";
			}

			case OperatorType::DECREMENT:
			{
#line 529 "../../../Source/Core/AST/OperatorExpr.nll"
				return "--";
			}

			case OperatorType::MODULO:
			{
#line 530 "../../../Source/Core/AST/OperatorExpr.nll"
				return "%";
			}

			case OperatorType::INEQUALITY:
			{
#line 531 "../../../Source/Core/AST/OperatorExpr.nll"
				return "!=";
			}

			case OperatorType::LOGICAL_OR:
			{
#line 532 "../../../Source/Core/AST/OperatorExpr.nll"
				return "||";
			}

			case OperatorType::ADDITION:
			{
#line 533 "../../../Source/Core/AST/OperatorExpr.nll"
				return "+";
			}

			case OperatorType::ADD_ASSIGN:
			{
#line 534 "../../../Source/Core/AST/OperatorExpr.nll"
				return "+=";
			}

			case OperatorType::INCREMENT:
			{
#line 535 "../../../Source/Core/AST/OperatorExpr.nll"
				return "++";
			}

			case OperatorType::MULTIPLICATION:
			{
#line 536 "../../../Source/Core/AST/OperatorExpr.nll"
				return "*";
			}

			case OperatorType::MULTIPLY_ASSIGN:
			{
#line 537 "../../../Source/Core/AST/OperatorExpr.nll"
				return "*=";
			}

			case OperatorType::DIVIDE_ASSIGN:
			{
#line 538 "../../../Source/Core/AST/OperatorExpr.nll"
				return "/=";
			}

			case OperatorType::LEFT_SHIFT_ASSIGN:
			{
#line 539 "../../../Source/Core/AST/OperatorExpr.nll"
				return "<<=";
			}

			case OperatorType::RIGHT_SHIFT_ASSIGN:
			{
#line 540 "../../../Source/Core/AST/OperatorExpr.nll"
				return ">>=";
			}

			default:
			{
#line 541 "../../../Source/Core/AST/OperatorExpr.nll"
				return "?";
			}

		}
	}

#line 545 "../../../Source/Core/AST/OperatorExpr.nll"
	void OperatorExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		OperatorType eOp = GetOperatorType();
		const char* sPad = " ";
		if (eOp == OperatorType::DECREMENT || eOp == OperatorType::INCREMENT || eOp == OperatorType::MEMBER_ACCESS || eOp == OperatorType::SCOPE_RESOLUTION)
			sPad = "";
#line 552 "../../../Source/Core/AST/OperatorExpr.nll"
		const char* sOperator = GetOperatorString(eOp);
		if (eLanguage == AST::Language::CS && eOp == OperatorType::SCOPE_RESOLUTION)
			sOperator = ".";
		if (eLanguage == AST::Language::CPP && eOp == OperatorType::MEMBER_ACCESS)
		{
			sOperator = "->";
			if (m_pLeft->m_eType == AST::Type::BASE_EXPR)
				sOperator = "::";
		}
#line 562 "../../../Source/Core/AST/OperatorExpr.nll"
		m_pLeft->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		pOutputBuilder->m_sOut->Append(sPad);
		pOutputBuilder->m_sOut->Append(sOperator);
#line 566 "../../../Source/Core/AST/OperatorExpr.nll"
		if (m_pRight != 0)
		{
			pOutputBuilder->m_sOut->Append(sPad);
			m_pRight->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		}
	}

#line 3 "../../../Source/Core/AST/OperatorExpr.nll"
	OperatorExpr::~OperatorExpr()
	{
		if (m_pOwnedOperatorToken) delete m_pOwnedOperatorToken;
	}

}

