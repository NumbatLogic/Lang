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

#line 49 "../../../Source/Core/AST/OperatorExpr.nll"
	Token* OperatorExpr::GetFirstOperatorToken()
	{
#line 51 "../../../Source/Core/AST/OperatorExpr.nll"
		Assert::Plz(m_pFirstOperatorToken != 0);
#line 52 "../../../Source/Core/AST/OperatorExpr.nll"
		return m_pFirstOperatorToken;
	}

#line 55 "../../../Source/Core/AST/OperatorExpr.nll"
	OperatorExpr::OperatorType OperatorExpr::GetOperatorType()
	{
#line 57 "../../../Source/Core/AST/OperatorExpr.nll"
		return m_eOperatorType;
	}

#line 60 "../../../Source/Core/AST/OperatorExpr.nll"
	bool OperatorExpr::IsPostfix(OperatorExpr::OperatorType eOperatorType)
	{
#line 62 "../../../Source/Core/AST/OperatorExpr.nll"
		return (eOperatorType == OperatorType::DECREMENT || eOperatorType == OperatorType::INCREMENT);
	}

#line 65 "../../../Source/Core/AST/OperatorExpr.nll"
	int OperatorExpr::GetOperatorTokenCount(OperatorExpr::OperatorType eOp)
	{
#line 67 "../../../Source/Core/AST/OperatorExpr.nll"
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
#line 94 "../../../Source/Core/AST/OperatorExpr.nll"
		Assert::Plz(pFirst != 0);
#line 96 "../../../Source/Core/AST/OperatorExpr.nll"
		if (pThird != 0)
		{
#line 98 "../../../Source/Core/AST/OperatorExpr.nll"
			Assert::Plz(pSecond != 0);
#line 100 "../../../Source/Core/AST/OperatorExpr.nll"
			if (pFirst->m_eType == Token::Type::TOKEN_ANGLE_BRACKET_LEFT && pSecond->m_eType == Token::Type::TOKEN_ANGLE_BRACKET_LEFT && pThird->m_eType == Token::Type::TOKEN_EQUALS)
#line 101 "../../../Source/Core/AST/OperatorExpr.nll"
				return OperatorType::LEFT_SHIFT_ASSIGN;
#line 102 "../../../Source/Core/AST/OperatorExpr.nll"
			if (pFirst->m_eType == Token::Type::TOKEN_ANGLE_BRACKET_RIGHT && pSecond->m_eType == Token::Type::TOKEN_ANGLE_BRACKET_RIGHT && pThird->m_eType == Token::Type::TOKEN_EQUALS)
#line 103 "../../../Source/Core/AST/OperatorExpr.nll"
				return OperatorType::RIGHT_SHIFT_ASSIGN;
		}
#line 106 "../../../Source/Core/AST/OperatorExpr.nll"
		if (pSecond != 0)
		{
#line 108 "../../../Source/Core/AST/OperatorExpr.nll"
			if (pFirst->m_eType == Token::Type::TOKEN_ANGLE_BRACKET_RIGHT && pSecond->m_eType == Token::Type::TOKEN_ANGLE_BRACKET_RIGHT)
#line 109 "../../../Source/Core/AST/OperatorExpr.nll"
				return OperatorType::RIGHT_SHIFT;
#line 110 "../../../Source/Core/AST/OperatorExpr.nll"
			if (pFirst->m_eType == Token::Type::TOKEN_ANGLE_BRACKET_LEFT && pSecond->m_eType == Token::Type::TOKEN_ANGLE_BRACKET_LEFT)
#line 111 "../../../Source/Core/AST/OperatorExpr.nll"
				return OperatorType::LEFT_SHIFT;
#line 112 "../../../Source/Core/AST/OperatorExpr.nll"
			if (pFirst->m_eType == Token::Type::TOKEN_EQUALS && pSecond->m_eType == Token::Type::TOKEN_EQUALS)
#line 113 "../../../Source/Core/AST/OperatorExpr.nll"
				return OperatorType::EQUALITY;
#line 114 "../../../Source/Core/AST/OperatorExpr.nll"
			if (pFirst->m_eType == Token::Type::TOKEN_BANG && pSecond->m_eType == Token::Type::TOKEN_EQUALS)
#line 115 "../../../Source/Core/AST/OperatorExpr.nll"
				return OperatorType::INEQUALITY;
#line 116 "../../../Source/Core/AST/OperatorExpr.nll"
			if (pFirst->m_eType == Token::Type::TOKEN_ANGLE_BRACKET_LEFT && pSecond->m_eType == Token::Type::TOKEN_EQUALS)
#line 117 "../../../Source/Core/AST/OperatorExpr.nll"
				return OperatorType::LESS_THAN_OR_EQUAL;
#line 118 "../../../Source/Core/AST/OperatorExpr.nll"
			if (pFirst->m_eType == Token::Type::TOKEN_ANGLE_BRACKET_RIGHT && pSecond->m_eType == Token::Type::TOKEN_EQUALS)
#line 119 "../../../Source/Core/AST/OperatorExpr.nll"
				return OperatorType::GREATER_THAN_OR_EQUAL;
#line 120 "../../../Source/Core/AST/OperatorExpr.nll"
			if (pFirst->m_eType == Token::Type::TOKEN_PLUS && pSecond->m_eType == Token::Type::TOKEN_EQUALS)
#line 121 "../../../Source/Core/AST/OperatorExpr.nll"
				return OperatorType::ADD_ASSIGN;
#line 122 "../../../Source/Core/AST/OperatorExpr.nll"
			if (pFirst->m_eType == Token::Type::TOKEN_MINUS && pSecond->m_eType == Token::Type::TOKEN_EQUALS)
#line 123 "../../../Source/Core/AST/OperatorExpr.nll"
				return OperatorType::SUBTRACT_ASSIGN;
#line 124 "../../../Source/Core/AST/OperatorExpr.nll"
			if (pFirst->m_eType == Token::Type::TOKEN_STAR && pSecond->m_eType == Token::Type::TOKEN_EQUALS)
#line 125 "../../../Source/Core/AST/OperatorExpr.nll"
				return OperatorType::MULTIPLY_ASSIGN;
#line 126 "../../../Source/Core/AST/OperatorExpr.nll"
			if (pFirst->m_eType == Token::Type::TOKEN_DIVIDE && pSecond->m_eType == Token::Type::TOKEN_EQUALS)
#line 127 "../../../Source/Core/AST/OperatorExpr.nll"
				return OperatorType::DIVIDE_ASSIGN;
#line 128 "../../../Source/Core/AST/OperatorExpr.nll"
			if (pFirst->m_eType == Token::Type::TOKEN_BITWISE_AND && pSecond->m_eType == Token::Type::TOKEN_BITWISE_AND)
#line 129 "../../../Source/Core/AST/OperatorExpr.nll"
				return OperatorType::LOGICAL_AND;
#line 130 "../../../Source/Core/AST/OperatorExpr.nll"
			if (pFirst->m_eType == Token::Type::TOKEN_BITWISE_OR && pSecond->m_eType == Token::Type::TOKEN_BITWISE_OR)
#line 131 "../../../Source/Core/AST/OperatorExpr.nll"
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

#line 155 "../../../Source/Core/AST/OperatorExpr.nll"
	OperatorExpr::OperatorType OperatorExpr::PeekOperator(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
#line 157 "../../../Source/Core/AST/OperatorExpr.nll"
		Token* pFirst = pTokenContainer->Peek(pOffsetDatum);
#line 158 "../../../Source/Core/AST/OperatorExpr.nll"
		if (pFirst == 0)
#line 159 "../../../Source/Core/AST/OperatorExpr.nll"
			return OperatorType::UNKNOWN;
#line 160 "../../../Source/Core/AST/OperatorExpr.nll"
		pOffsetDatum->m_nOffset++;
#line 161 "../../../Source/Core/AST/OperatorExpr.nll"
		Token* pSecond = pTokenContainer->Peek(pOffsetDatum);
#line 162 "../../../Source/Core/AST/OperatorExpr.nll"
		pOffsetDatum->m_nOffset++;
#line 163 "../../../Source/Core/AST/OperatorExpr.nll"
		Token* pThird = pTokenContainer->Peek(pOffsetDatum);
#line 164 "../../../Source/Core/AST/OperatorExpr.nll"
		pOffsetDatum->m_nOffset -= 2;
#line 166 "../../../Source/Core/AST/OperatorExpr.nll"
		OperatorType eType = GetOperatorTypeFromTokens(pFirst, pSecond, pThird);
#line 167 "../../../Source/Core/AST/OperatorExpr.nll"
		if (eType == OperatorType::UNKNOWN)
#line 168 "../../../Source/Core/AST/OperatorExpr.nll"
			return OperatorType::UNKNOWN;
#line 169 "../../../Source/Core/AST/OperatorExpr.nll"
		pOffsetDatum->m_nOffset += GetOperatorTokenCount(eType);
#line 170 "../../../Source/Core/AST/OperatorExpr.nll"
		return eType;
	}

#line 173 "../../../Source/Core/AST/OperatorExpr.nll"
	OperatorExpr* OperatorExpr::Create(OperatorExpr::OperatorType eOperatorType, Token* pFirstOperatorToken, AST* pLeft, AST* pRight)
	{
#line 175 "../../../Source/Core/AST/OperatorExpr.nll"
		Assert::Plz(pLeft != 0);
#line 176 "../../../Source/Core/AST/OperatorExpr.nll"
		if (IsPostfix(eOperatorType))
#line 177 "../../../Source/Core/AST/OperatorExpr.nll"
			Assert::Plz(pRight == 0);
#line 179 "../../../Source/Core/AST/OperatorExpr.nll"
		OperatorExpr* pOperatorExpr = new OperatorExpr();
#line 181 "../../../Source/Core/AST/OperatorExpr.nll"
		AST* pOwnedLeft = pLeft;
#line 182 "../../../Source/Core/AST/OperatorExpr.nll"
		AST* pOwnedRight = pRight;
#line 184 "../../../Source/Core/AST/OperatorExpr.nll"
		pOperatorExpr->m_pFirstToken = pLeft->m_pFirstToken;
#line 185 "../../../Source/Core/AST/OperatorExpr.nll"
		pOperatorExpr->m_eOperatorType = eOperatorType;
#line 186 "../../../Source/Core/AST/OperatorExpr.nll"
		pOperatorExpr->m_pFirstOperatorToken = pFirstOperatorToken;
#line 187 "../../../Source/Core/AST/OperatorExpr.nll"
		pOperatorExpr->m_pLeft = pOwnedLeft;
#line 188 "../../../Source/Core/AST/OperatorExpr.nll"
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
#line 193 "../../../Source/Core/AST/OperatorExpr.nll"
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

#line 199 "../../../Source/Core/AST/OperatorExpr.nll"
	AST* OperatorExpr::BaseClone()
	{
#line 201 "../../../Source/Core/AST/OperatorExpr.nll"
		AST* pLeft = 0;
#line 202 "../../../Source/Core/AST/OperatorExpr.nll"
		AST* pRight = 0;
#line 204 "../../../Source/Core/AST/OperatorExpr.nll"
		if (m_pLeft != 0)
#line 205 "../../../Source/Core/AST/OperatorExpr.nll"
			pLeft = m_pLeft->BaseClone();
#line 207 "../../../Source/Core/AST/OperatorExpr.nll"
		if (m_pRight != 0)
#line 208 "../../../Source/Core/AST/OperatorExpr.nll"
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

#line 216 "../../../Source/Core/AST/OperatorExpr.nll"
	void OperatorExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
#line 234 "../../../Source/Core/AST/OperatorExpr.nll"
		if (m_pLeft != 0)
		{
#line 236 "../../../Source/Core/AST/OperatorExpr.nll"
			m_pLeft->Validate(pValidator, pParent);
#line 237 "../../../Source/Core/AST/OperatorExpr.nll"
			if (m_pLeft->m_pValueType == 0)
			{
#line 239 "../../../Source/Core/AST/OperatorExpr.nll"
				pValidator->AddError("No ValueType for left of operator: ", m_pLeft->m_pFirstToken->m_sFileName, m_pLeft->m_pFirstToken->m_nLine, m_pLeft->m_pFirstToken->m_nColumn);
#line 240 "../../../Source/Core/AST/OperatorExpr.nll"
				return;
			}
			else
			{
#line 244 "../../../Source/Core/AST/OperatorExpr.nll"
				Token* pOpToken = GetFirstOperatorToken();
#line 245 "../../../Source/Core/AST/OperatorExpr.nll"
				if (m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL || m_pLeft->m_pValueType->m_eType == ValueType::Type::ENUM_DECL || m_pLeft->m_pValueType->m_eType == ValueType::Type::NAMESPACE_NODE)
				{
#line 247 "../../../Source/Core/AST/OperatorExpr.nll"
					if (GetOperatorType() != OperatorType::SCOPE_RESOLUTION)
					{
#line 249 "../../../Source/Core/AST/OperatorExpr.nll"
						pValidator->AddError("Expected :: ", pOpToken->m_sFileName, pOpToken->m_nLine, pOpToken->m_nColumn);
#line 250 "../../../Source/Core/AST/OperatorExpr.nll"
						return;
					}
#line 252 "../../../Source/Core/AST/OperatorExpr.nll"
					if (m_pRight == 0)
					{
#line 254 "../../../Source/Core/AST/OperatorExpr.nll"
						pValidator->AddError("Expected right side of :: operator", pOpToken->m_sFileName, pOpToken->m_nLine, pOpToken->m_nColumn);
#line 255 "../../../Source/Core/AST/OperatorExpr.nll"
						return;
					}
#line 258 "../../../Source/Core/AST/OperatorExpr.nll"
					if (m_pRight->m_eType != AST::Type::AST_IDENTIFIER && m_pRight->m_eType != AST::Type::AST_OPERATOR_EXPR && m_pRight->m_eType != AST::Type::AST_FUNCTION_CALL && m_pRight->m_eType != AST::Type::AST_ARRAY_LOOKUP)
					{
#line 260 "../../../Source/Core/AST/OperatorExpr.nll"
						InternalString* sTemp = new InternalString("Unexpected right side of :: operator: ");
#line 261 "../../../Source/Core/AST/OperatorExpr.nll"
						m_pRight->StringifyType(sTemp);
#line 263 "../../../Source/Core/AST/OperatorExpr.nll"
						pValidator->AddError(sTemp->GetExternalString(), pOpToken->m_sFileName, pOpToken->m_nLine, pOpToken->m_nColumn);
						if (sTemp) delete sTemp;
#line 264 "../../../Source/Core/AST/OperatorExpr.nll"
						return;
					}
#line 267 "../../../Source/Core/AST/OperatorExpr.nll"
					m_pRight->Validate(pValidator, this);
#line 268 "../../../Source/Core/AST/OperatorExpr.nll"
					if (m_pRight->m_pValueType == 0)
					{
#line 270 "../../../Source/Core/AST/OperatorExpr.nll"
						pValidator->AddError("No ValueType for right of operator: ", m_pRight->m_pFirstToken->m_sFileName, m_pRight->m_pFirstToken->m_nLine, m_pRight->m_pFirstToken->m_nColumn);
#line 271 "../../../Source/Core/AST/OperatorExpr.nll"
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
#line 281 "../../../Source/Core/AST/OperatorExpr.nll"
					if (m_pLeft->m_pValueType->m_eType == ValueType::Type::GENERIC_TYPE_DECL_VALUE)
					{
#line 283 "../../../Source/Core/AST/OperatorExpr.nll"
						if (m_pLeft->m_pValueType->m_pGenericTypeDecl == 0)
						{
#line 285 "../../../Source/Core/AST/OperatorExpr.nll"
							pValidator->AddError(" set but m_pGenericTypeDecl is null???", pOpToken->m_sFileName, pOpToken->m_nLine, pOpToken->m_nColumn);
#line 286 "../../../Source/Core/AST/OperatorExpr.nll"
							return;
						}
					}
					else
#line 289 "../../../Source/Core/AST/OperatorExpr.nll"
						if (m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
						{
#line 291 "../../../Source/Core/AST/OperatorExpr.nll"
							if (m_pLeft->m_pValueType->m_pClassDecl == 0)
							{
#line 293 "../../../Source/Core/AST/OperatorExpr.nll"
								pValidator->AddError(" set but m_pClassDecl is null???", pOpToken->m_sFileName, pOpToken->m_nLine, pOpToken->m_nColumn);
#line 294 "../../../Source/Core/AST/OperatorExpr.nll"
								return;
							}
						}
						else
						{
#line 299 "../../../Source/Core/AST/OperatorExpr.nll"
							pValidator->AddError("Expected ValueType::Type::CLASS_DECL_VALUE or ValueType::Type::GENERIC_TYPE_DECL_VALUE on left of TOKEN_DOT operator", pOpToken->m_sFileName, pOpToken->m_nLine, pOpToken->m_nColumn);
#line 300 "../../../Source/Core/AST/OperatorExpr.nll"
							return;
						}
#line 303 "../../../Source/Core/AST/OperatorExpr.nll"
					m_pRight->Validate(pValidator, this);
#line 304 "../../../Source/Core/AST/OperatorExpr.nll"
					if (m_pRight->m_pValueType == 0)
					{
#line 306 "../../../Source/Core/AST/OperatorExpr.nll"
						pValidator->AddError("No ValueType for right of operator: ", m_pRight->m_pFirstToken->m_sFileName, m_pRight->m_pFirstToken->m_nLine, m_pRight->m_pFirstToken->m_nColumn);
#line 307 "../../../Source/Core/AST/OperatorExpr.nll"
						return;
					}
#line 310 "../../../Source/Core/AST/OperatorExpr.nll"
					m_pValueType = m_pRight->m_pValueType->Clone();
#line 311 "../../../Source/Core/AST/OperatorExpr.nll"
					return;
				}
#line 314 "../../../Source/Core/AST/OperatorExpr.nll"
				if (GetOperatorType() == OperatorType::ADDITION)
				{
#line 316 "../../../Source/Core/AST/OperatorExpr.nll"
					if (m_pLeft->m_pValueType->m_eType == ValueType::Type::STRING)
					{
#line 318 "../../../Source/Core/AST/OperatorExpr.nll"
						pValidator->AddError("Cannot concat strings with +", pOpToken->m_sFileName, pOpToken->m_nLine, pOpToken->m_nColumn);
#line 319 "../../../Source/Core/AST/OperatorExpr.nll"
						return;
					}
				}
#line 323 "../../../Source/Core/AST/OperatorExpr.nll"
				if (GetOperatorType() == OperatorType::EQUALITY || GetOperatorType() == OperatorType::INEQUALITY)
				{
#line 325 "../../../Source/Core/AST/OperatorExpr.nll"
					if (m_pRight == 0)
					{
#line 327 "../../../Source/Core/AST/OperatorExpr.nll"
						pValidator->AddError("Nohing on right side to compare?", pOpToken->m_sFileName, pOpToken->m_nLine, pOpToken->m_nColumn);
#line 328 "../../../Source/Core/AST/OperatorExpr.nll"
						return;
					}
#line 331 "../../../Source/Core/AST/OperatorExpr.nll"
					m_pRight->Validate(pValidator, this);
#line 333 "../../../Source/Core/AST/OperatorExpr.nll"
					if (m_pLeft->m_pValueType->m_eType == ValueType::Type::STRING && m_pRight->m_pValueType->m_eType == ValueType::Type::STRING)
					{
#line 335 "../../../Source/Core/AST/OperatorExpr.nll"
						pValidator->AddError("Cannot == or != strings use ExternalString::Equal", pOpToken->m_sFileName, pOpToken->m_nLine, pOpToken->m_nColumn);
#line 336 "../../../Source/Core/AST/OperatorExpr.nll"
						return;
					}
#line 339 "../../../Source/Core/AST/OperatorExpr.nll"
					m_pValueType = new ValueType(ValueType::Type::BOOL);
#line 340 "../../../Source/Core/AST/OperatorExpr.nll"
					return;
				}
#line 343 "../../../Source/Core/AST/OperatorExpr.nll"
				if (m_pRight != 0)
#line 344 "../../../Source/Core/AST/OperatorExpr.nll"
					m_pRight->Validate(pValidator, this);
#line 346 "../../../Source/Core/AST/OperatorExpr.nll"
				if (GetOperatorType() == OperatorType::ASSIGNMENT)
				{
#line 348 "../../../Source/Core/AST/OperatorExpr.nll"
					if (m_pRight->m_pValueType == 0)
					{
#line 350 "../../../Source/Core/AST/OperatorExpr.nll"
						pValidator->AddError("No ValueType for right of operator = ???", m_pRight->m_pFirstToken->m_sFileName, m_pRight->m_pFirstToken->m_nLine, m_pRight->m_pFirstToken->m_nColumn);
#line 351 "../../../Source/Core/AST/OperatorExpr.nll"
						return;
					}
#line 354 "../../../Source/Core/AST/OperatorExpr.nll"
					if (m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
					{
#line 356 "../../../Source/Core/AST/OperatorExpr.nll"
						if (m_pRight->m_pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
						{
#line 362 "../../../Source/Core/AST/OperatorExpr.nll"
							if (m_pLeft->m_pValueType->m_ePointerType == TypeRef::PointerType::OWNED && m_pRight->m_pValueType->m_ePointerType != TypeRef::PointerType::OWNED_PREASSSIGN)
							{
#line 364 "../../../Source/Core/AST/OperatorExpr.nll"
								InternalString* sTemp = new InternalString("Expected right side of = to be OWNED_PREASSSIGN (result of own). FROM[");
#line 365 "../../../Source/Core/AST/OperatorExpr.nll"
								m_pRight->m_pValueType->StringifyType(sTemp);
#line 366 "../../../Source/Core/AST/OperatorExpr.nll"
								if (m_pRight->m_pValueType->m_pClassDecl != 0)
								{
#line 368 "../../../Source/Core/AST/OperatorExpr.nll"
									sTemp->Append(" name=");
#line 369 "../../../Source/Core/AST/OperatorExpr.nll"
									sTemp->AppendString(m_pRight->m_pValueType->m_pClassDecl->m_pNameToken->GetString());
								}
#line 371 "../../../Source/Core/AST/OperatorExpr.nll"
								sTemp->Append(" ptr=");
#line 372 "../../../Source/Core/AST/OperatorExpr.nll"
								ValueType::StringifyPointerType(sTemp, m_pRight->m_pValueType->m_ePointerType);
#line 373 "../../../Source/Core/AST/OperatorExpr.nll"
								sTemp->Append("] TO[");
#line 374 "../../../Source/Core/AST/OperatorExpr.nll"
								m_pLeft->m_pValueType->StringifyType(sTemp);
#line 375 "../../../Source/Core/AST/OperatorExpr.nll"
								if (m_pLeft->m_pValueType->m_pClassDecl != 0)
								{
#line 377 "../../../Source/Core/AST/OperatorExpr.nll"
									sTemp->Append(" name=");
#line 378 "../../../Source/Core/AST/OperatorExpr.nll"
									sTemp->AppendString(m_pLeft->m_pValueType->m_pClassDecl->m_pNameToken->GetString());
								}
#line 380 "../../../Source/Core/AST/OperatorExpr.nll"
								sTemp->Append(" ptr=");
#line 381 "../../../Source/Core/AST/OperatorExpr.nll"
								ValueType::StringifyPointerType(sTemp, m_pLeft->m_pValueType->m_ePointerType);
#line 382 "../../../Source/Core/AST/OperatorExpr.nll"
								sTemp->Append("]");
#line 383 "../../../Source/Core/AST/OperatorExpr.nll"
								pValidator->AddError(sTemp->GetExternalString(), pOpToken->m_sFileName, pOpToken->m_nLine, pOpToken->m_nColumn);
								if (sTemp) delete sTemp;
#line 384 "../../../Source/Core/AST/OperatorExpr.nll"
								return;
							}
#line 387 "../../../Source/Core/AST/OperatorExpr.nll"
							if (m_pLeft->m_pValueType->m_ePointerType == TypeRef::PointerType::SHARED && m_pRight->m_pValueType->m_ePointerType == TypeRef::PointerType::OWNED_PREASSSIGN)
							{
#line 389 "../../../Source/Core/AST/OperatorExpr.nll"
								InternalString* sTemp = new InternalString("Can't store an owned pointer in a shared pointer. FROM[");
#line 390 "../../../Source/Core/AST/OperatorExpr.nll"
								m_pRight->m_pValueType->StringifyType(sTemp);
#line 391 "../../../Source/Core/AST/OperatorExpr.nll"
								if (m_pRight->m_pValueType->m_pClassDecl != 0)
								{
#line 393 "../../../Source/Core/AST/OperatorExpr.nll"
									sTemp->Append(" name=");
#line 394 "../../../Source/Core/AST/OperatorExpr.nll"
									sTemp->AppendString(m_pRight->m_pValueType->m_pClassDecl->m_pNameToken->GetString());
								}
#line 396 "../../../Source/Core/AST/OperatorExpr.nll"
								sTemp->Append(" ptr=");
#line 397 "../../../Source/Core/AST/OperatorExpr.nll"
								ValueType::StringifyPointerType(sTemp, m_pRight->m_pValueType->m_ePointerType);
#line 398 "../../../Source/Core/AST/OperatorExpr.nll"
								sTemp->Append("] TO[");
#line 399 "../../../Source/Core/AST/OperatorExpr.nll"
								m_pLeft->m_pValueType->StringifyType(sTemp);
#line 400 "../../../Source/Core/AST/OperatorExpr.nll"
								if (m_pLeft->m_pValueType->m_pClassDecl != 0)
								{
#line 402 "../../../Source/Core/AST/OperatorExpr.nll"
									sTemp->Append(" name=");
#line 403 "../../../Source/Core/AST/OperatorExpr.nll"
									sTemp->AppendString(m_pLeft->m_pValueType->m_pClassDecl->m_pNameToken->GetString());
								}
#line 405 "../../../Source/Core/AST/OperatorExpr.nll"
								sTemp->Append(" ptr=");
#line 406 "../../../Source/Core/AST/OperatorExpr.nll"
								ValueType::StringifyPointerType(sTemp, m_pLeft->m_pValueType->m_ePointerType);
#line 407 "../../../Source/Core/AST/OperatorExpr.nll"
								sTemp->Append("]");
#line 408 "../../../Source/Core/AST/OperatorExpr.nll"
								pValidator->AddError(sTemp->GetExternalString(), pOpToken->m_sFileName, pOpToken->m_nLine, pOpToken->m_nColumn);
								if (sTemp) delete sTemp;
#line 409 "../../../Source/Core/AST/OperatorExpr.nll"
								return;
							}
#line 412 "../../../Source/Core/AST/OperatorExpr.nll"
							if (m_pRight->m_pValueType->m_ePointerType == TypeRef::PointerType::TRANSITON)
							{
#line 414 "../../../Source/Core/AST/OperatorExpr.nll"
								InternalString* sTemp = new InternalString("Cannot store a TRANSITION pointer (need to `own` it). FROM[");
#line 415 "../../../Source/Core/AST/OperatorExpr.nll"
								m_pRight->m_pValueType->StringifyType(sTemp);
#line 416 "../../../Source/Core/AST/OperatorExpr.nll"
								if (m_pRight->m_pValueType->m_pClassDecl != 0)
								{
#line 418 "../../../Source/Core/AST/OperatorExpr.nll"
									sTemp->Append(" name=");
#line 419 "../../../Source/Core/AST/OperatorExpr.nll"
									sTemp->AppendString(m_pRight->m_pValueType->m_pClassDecl->m_pNameToken->GetString());
								}
#line 421 "../../../Source/Core/AST/OperatorExpr.nll"
								sTemp->Append(" ptr=");
#line 422 "../../../Source/Core/AST/OperatorExpr.nll"
								ValueType::StringifyPointerType(sTemp, m_pRight->m_pValueType->m_ePointerType);
#line 423 "../../../Source/Core/AST/OperatorExpr.nll"
								sTemp->Append("] TO[");
#line 424 "../../../Source/Core/AST/OperatorExpr.nll"
								m_pLeft->m_pValueType->StringifyType(sTemp);
#line 425 "../../../Source/Core/AST/OperatorExpr.nll"
								if (m_pLeft->m_pValueType->m_pClassDecl != 0)
								{
#line 427 "../../../Source/Core/AST/OperatorExpr.nll"
									sTemp->Append(" name=");
#line 428 "../../../Source/Core/AST/OperatorExpr.nll"
									sTemp->AppendString(m_pLeft->m_pValueType->m_pClassDecl->m_pNameToken->GetString());
								}
#line 430 "../../../Source/Core/AST/OperatorExpr.nll"
								sTemp->Append(" ptr=");
#line 431 "../../../Source/Core/AST/OperatorExpr.nll"
								ValueType::StringifyPointerType(sTemp, m_pLeft->m_pValueType->m_ePointerType);
#line 432 "../../../Source/Core/AST/OperatorExpr.nll"
								sTemp->Append("]");
#line 433 "../../../Source/Core/AST/OperatorExpr.nll"
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
#line 446 "../../../Source/Core/AST/OperatorExpr.nll"
								while (pBaseClassDecl != 0)
								{
#line 448 "../../../Source/Core/AST/OperatorExpr.nll"
									if (pBaseClassDecl == m_pLeft->m_pValueType->m_pClassDecl)
#line 449 "../../../Source/Core/AST/OperatorExpr.nll"
										break;
#line 450 "../../../Source/Core/AST/OperatorExpr.nll"
									pBaseClassDecl = pBaseClassDecl->GetBaseClassDecl(pValidator);
								}
#line 453 "../../../Source/Core/AST/OperatorExpr.nll"
								if (pBaseClassDecl != m_pLeft->m_pValueType->m_pClassDecl)
								{
#line 455 "../../../Source/Core/AST/OperatorExpr.nll"
									InternalString* sTemp = new InternalString("Can't assign ");
#line 456 "../../../Source/Core/AST/OperatorExpr.nll"
									sTemp->AppendString(m_pRight->m_pValueType->m_pClassDecl->m_pNameToken->GetString());
#line 457 "../../../Source/Core/AST/OperatorExpr.nll"
									sTemp->AppendString(" to ");
#line 458 "../../../Source/Core/AST/OperatorExpr.nll"
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
#line 466 "../../../Source/Core/AST/OperatorExpr.nll"
							if (m_pRight->m_pValueType->m_eType == ValueType::Type::NULL_VALUE)
							{
							}
							else
#line 470 "../../../Source/Core/AST/OperatorExpr.nll"
								if (m_pRight->m_pValueType->m_eType == ValueType::Type::GENERIC_TYPE_DECL_VALUE)
								{
								}
								else
								{
#line 476 "../../../Source/Core/AST/OperatorExpr.nll"
									pValidator->AddError("Expected right side of = to also be CLASS_DECL_VALUE or NULL_VALUE\n", pOpToken->m_sFileName, pOpToken->m_nLine, pOpToken->m_nColumn);
#line 477 "../../../Source/Core/AST/OperatorExpr.nll"
									return;
								}
					}
#line 481 "../../../Source/Core/AST/OperatorExpr.nll"
					m_pValueType = m_pLeft->m_pValueType->Clone();
#line 482 "../../../Source/Core/AST/OperatorExpr.nll"
					return;
				}
#line 487 "../../../Source/Core/AST/OperatorExpr.nll"
				m_pValueType = m_pLeft->m_pValueType->Clone();
#line 488 "../../../Source/Core/AST/OperatorExpr.nll"
				return;
			}
		}
#line 492 "../../../Source/Core/AST/OperatorExpr.nll"
		if (m_pRight != 0)
		{
#line 494 "../../../Source/Core/AST/OperatorExpr.nll"
			m_pRight->Validate(pValidator, 0);
#line 495 "../../../Source/Core/AST/OperatorExpr.nll"
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
#line 510 "../../../Source/Core/AST/OperatorExpr.nll"
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
#line 547 "../../../Source/Core/AST/OperatorExpr.nll"
		OperatorType eOp = GetOperatorType();
#line 548 "../../../Source/Core/AST/OperatorExpr.nll"
		const char* sPad = " ";
#line 549 "../../../Source/Core/AST/OperatorExpr.nll"
		if (eOp == OperatorType::DECREMENT || eOp == OperatorType::INCREMENT || eOp == OperatorType::MEMBER_ACCESS || eOp == OperatorType::SCOPE_RESOLUTION)
#line 550 "../../../Source/Core/AST/OperatorExpr.nll"
			sPad = "";
#line 552 "../../../Source/Core/AST/OperatorExpr.nll"
		const char* sOperator = GetOperatorString(eOp);
#line 553 "../../../Source/Core/AST/OperatorExpr.nll"
		if (eLanguage == AST::Language::CS && eOp == OperatorType::SCOPE_RESOLUTION)
#line 554 "../../../Source/Core/AST/OperatorExpr.nll"
			sOperator = ".";
#line 555 "../../../Source/Core/AST/OperatorExpr.nll"
		if (eLanguage == AST::Language::CPP && eOp == OperatorType::MEMBER_ACCESS)
		{
#line 557 "../../../Source/Core/AST/OperatorExpr.nll"
			sOperator = "->";
#line 558 "../../../Source/Core/AST/OperatorExpr.nll"
			if (m_pLeft->m_eType == AST::Type::BASE_EXPR)
#line 559 "../../../Source/Core/AST/OperatorExpr.nll"
				sOperator = "::";
		}
#line 562 "../../../Source/Core/AST/OperatorExpr.nll"
		m_pLeft->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 563 "../../../Source/Core/AST/OperatorExpr.nll"
		pOutputBuilder->m_sOut->Append(sPad);
#line 564 "../../../Source/Core/AST/OperatorExpr.nll"
		pOutputBuilder->m_sOut->Append(sOperator);
#line 566 "../../../Source/Core/AST/OperatorExpr.nll"
		if (m_pRight != 0)
		{
#line 568 "../../../Source/Core/AST/OperatorExpr.nll"
			pOutputBuilder->m_sOut->Append(sPad);
#line 569 "../../../Source/Core/AST/OperatorExpr.nll"
			m_pRight->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		}
	}

#line 3 "../../../Source/Core/AST/OperatorExpr.nll"
	OperatorExpr::~OperatorExpr()
	{
		if (m_pOwnedOperatorToken) delete m_pOwnedOperatorToken;
	}

}

