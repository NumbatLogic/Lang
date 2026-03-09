#line 1 "../../../Source/Core/AST/OperatorExpr.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/OperatorExpr.nll"
	class OperatorExpr : AST
	{
#line 6 "../../../Source/Core/AST/OperatorExpr.nll"
		public enum OperatorType
		{
			LOGICAL_AND,
			LESS_THAN,
			LESS_THAN_OR_EQUAL,
			GREATER_THAN,
			GREATER_THAN_OR_EQUAL,
			BITWISE_AND,
			BITWISE_OR,
			BITWISE_XOR,
			DIVISION,
			MEMBER_ACCESS,
			LEFT_SHIFT,
			RIGHT_SHIFT,
			SCOPE_RESOLUTION,
			EQUALITY,
			ASSIGNMENT,
			SUBTRACTION,
			SUBTRACT_ASSIGN,
			DECREMENT,
			MODULO,
			INEQUALITY,
			LOGICAL_OR,
			ADDITION,
			ADD_ASSIGN,
			INCREMENT,
			MULTIPLICATION,
			MULTIPLY_ASSIGN,
			DIVIDE_ASSIGN,
			LEFT_SHIFT_ASSIGN,
			RIGHT_SHIFT_ASSIGN,
			UNKNOWN,
		}

#line 39 "../../../Source/Core/AST/OperatorExpr.nll"
		public OperatorExpr.OperatorType m_eOperatorType;
#line 40 "../../../Source/Core/AST/OperatorExpr.nll"
		public Token m_pFirstOperatorToken;
#line 41 "../../../Source/Core/AST/OperatorExpr.nll"
		public Token m_pOwnedOperatorToken;
#line 42 "../../../Source/Core/AST/OperatorExpr.nll"
		public AST m_pLeft;
#line 43 "../../../Source/Core/AST/OperatorExpr.nll"
		public AST m_pRight;
#line 45 "../../../Source/Core/AST/OperatorExpr.nll"
		public OperatorExpr()
		{
#line 47 "../../../Source/Core/AST/OperatorExpr.nll"
			m_eType = AST.Type.AST_OPERATOR_EXPR;
		}

#line 50 "../../../Source/Core/AST/OperatorExpr.nll"
		public Token GetFirstOperatorToken()
		{
#line 52 "../../../Source/Core/AST/OperatorExpr.nll"
			Assert.Plz(m_pFirstOperatorToken != null);
#line 53 "../../../Source/Core/AST/OperatorExpr.nll"
			return m_pFirstOperatorToken;
		}

#line 56 "../../../Source/Core/AST/OperatorExpr.nll"
		public OperatorExpr.OperatorType GetOperatorType()
		{
#line 58 "../../../Source/Core/AST/OperatorExpr.nll"
			return m_eOperatorType;
		}

#line 61 "../../../Source/Core/AST/OperatorExpr.nll"
		public static bool IsPostfix(OperatorExpr.OperatorType eOperatorType)
		{
#line 63 "../../../Source/Core/AST/OperatorExpr.nll"
			return (eOperatorType == OperatorType.DECREMENT || eOperatorType == OperatorType.INCREMENT);
		}

#line 66 "../../../Source/Core/AST/OperatorExpr.nll"
		protected static int GetOperatorTokenCount(OperatorExpr.OperatorType eOp)
		{
#line 68 "../../../Source/Core/AST/OperatorExpr.nll"
			switch (eOp)
			{
				case OperatorType.UNKNOWN:
				{
#line 71 "../../../Source/Core/AST/OperatorExpr.nll"
					return 0;
				}

				case OperatorType.LEFT_SHIFT:
				case OperatorType.RIGHT_SHIFT:
				case OperatorType.EQUALITY:
				case OperatorType.INEQUALITY:
				case OperatorType.LESS_THAN_OR_EQUAL:
				case OperatorType.GREATER_THAN_OR_EQUAL:
				case OperatorType.ADD_ASSIGN:
				case OperatorType.SUBTRACT_ASSIGN:
				case OperatorType.MULTIPLY_ASSIGN:
				case OperatorType.DIVIDE_ASSIGN:
				case OperatorType.LOGICAL_AND:
				case OperatorType.LOGICAL_OR:
				{
#line 84 "../../../Source/Core/AST/OperatorExpr.nll"
					return 2;
				}

				case OperatorType.LEFT_SHIFT_ASSIGN:
				case OperatorType.RIGHT_SHIFT_ASSIGN:
				{
#line 87 "../../../Source/Core/AST/OperatorExpr.nll"
					return 3;
				}

				default:
				{
#line 89 "../../../Source/Core/AST/OperatorExpr.nll"
					return 1;
				}

			}
		}

#line 93 "../../../Source/Core/AST/OperatorExpr.nll"
		protected static OperatorExpr.OperatorType GetOperatorTypeFromTokens(Token pFirst, Token pSecond, Token pThird)
		{
#line 95 "../../../Source/Core/AST/OperatorExpr.nll"
			Assert.Plz(pFirst != null);
#line 97 "../../../Source/Core/AST/OperatorExpr.nll"
			if (pThird != null)
			{
#line 99 "../../../Source/Core/AST/OperatorExpr.nll"
				Assert.Plz(pSecond != null);
#line 101 "../../../Source/Core/AST/OperatorExpr.nll"
				if (pFirst.m_eType == Token.Type.TOKEN_ANGLE_BRACKET_LEFT && pSecond.m_eType == Token.Type.TOKEN_ANGLE_BRACKET_LEFT && pThird.m_eType == Token.Type.TOKEN_EQUALS)
#line 102 "../../../Source/Core/AST/OperatorExpr.nll"
					return OperatorType.LEFT_SHIFT_ASSIGN;
#line 103 "../../../Source/Core/AST/OperatorExpr.nll"
				if (pFirst.m_eType == Token.Type.TOKEN_ANGLE_BRACKET_RIGHT && pSecond.m_eType == Token.Type.TOKEN_ANGLE_BRACKET_RIGHT && pThird.m_eType == Token.Type.TOKEN_EQUALS)
#line 104 "../../../Source/Core/AST/OperatorExpr.nll"
					return OperatorType.RIGHT_SHIFT_ASSIGN;
			}
#line 107 "../../../Source/Core/AST/OperatorExpr.nll"
			if (pSecond != null)
			{
#line 109 "../../../Source/Core/AST/OperatorExpr.nll"
				if (pFirst.m_eType == Token.Type.TOKEN_ANGLE_BRACKET_RIGHT && pSecond.m_eType == Token.Type.TOKEN_ANGLE_BRACKET_RIGHT)
#line 110 "../../../Source/Core/AST/OperatorExpr.nll"
					return OperatorType.RIGHT_SHIFT;
#line 111 "../../../Source/Core/AST/OperatorExpr.nll"
				if (pFirst.m_eType == Token.Type.TOKEN_ANGLE_BRACKET_LEFT && pSecond.m_eType == Token.Type.TOKEN_ANGLE_BRACKET_LEFT)
#line 112 "../../../Source/Core/AST/OperatorExpr.nll"
					return OperatorType.LEFT_SHIFT;
#line 113 "../../../Source/Core/AST/OperatorExpr.nll"
				if (pFirst.m_eType == Token.Type.TOKEN_EQUALS && pSecond.m_eType == Token.Type.TOKEN_EQUALS)
#line 114 "../../../Source/Core/AST/OperatorExpr.nll"
					return OperatorType.EQUALITY;
#line 115 "../../../Source/Core/AST/OperatorExpr.nll"
				if (pFirst.m_eType == Token.Type.TOKEN_BANG && pSecond.m_eType == Token.Type.TOKEN_EQUALS)
#line 116 "../../../Source/Core/AST/OperatorExpr.nll"
					return OperatorType.INEQUALITY;
#line 117 "../../../Source/Core/AST/OperatorExpr.nll"
				if (pFirst.m_eType == Token.Type.TOKEN_ANGLE_BRACKET_LEFT && pSecond.m_eType == Token.Type.TOKEN_EQUALS)
#line 118 "../../../Source/Core/AST/OperatorExpr.nll"
					return OperatorType.LESS_THAN_OR_EQUAL;
#line 119 "../../../Source/Core/AST/OperatorExpr.nll"
				if (pFirst.m_eType == Token.Type.TOKEN_ANGLE_BRACKET_RIGHT && pSecond.m_eType == Token.Type.TOKEN_EQUALS)
#line 120 "../../../Source/Core/AST/OperatorExpr.nll"
					return OperatorType.GREATER_THAN_OR_EQUAL;
#line 121 "../../../Source/Core/AST/OperatorExpr.nll"
				if (pFirst.m_eType == Token.Type.TOKEN_PLUS && pSecond.m_eType == Token.Type.TOKEN_EQUALS)
#line 122 "../../../Source/Core/AST/OperatorExpr.nll"
					return OperatorType.ADD_ASSIGN;
#line 123 "../../../Source/Core/AST/OperatorExpr.nll"
				if (pFirst.m_eType == Token.Type.TOKEN_MINUS && pSecond.m_eType == Token.Type.TOKEN_EQUALS)
#line 124 "../../../Source/Core/AST/OperatorExpr.nll"
					return OperatorType.SUBTRACT_ASSIGN;
#line 125 "../../../Source/Core/AST/OperatorExpr.nll"
				if (pFirst.m_eType == Token.Type.TOKEN_STAR && pSecond.m_eType == Token.Type.TOKEN_EQUALS)
#line 126 "../../../Source/Core/AST/OperatorExpr.nll"
					return OperatorType.MULTIPLY_ASSIGN;
#line 127 "../../../Source/Core/AST/OperatorExpr.nll"
				if (pFirst.m_eType == Token.Type.TOKEN_DIVIDE && pSecond.m_eType == Token.Type.TOKEN_EQUALS)
#line 128 "../../../Source/Core/AST/OperatorExpr.nll"
					return OperatorType.DIVIDE_ASSIGN;
#line 129 "../../../Source/Core/AST/OperatorExpr.nll"
				if (pFirst.m_eType == Token.Type.TOKEN_BITWISE_AND && pSecond.m_eType == Token.Type.TOKEN_BITWISE_AND)
#line 130 "../../../Source/Core/AST/OperatorExpr.nll"
					return OperatorType.LOGICAL_AND;
#line 131 "../../../Source/Core/AST/OperatorExpr.nll"
				if (pFirst.m_eType == Token.Type.TOKEN_BITWISE_OR && pSecond.m_eType == Token.Type.TOKEN_BITWISE_OR)
#line 132 "../../../Source/Core/AST/OperatorExpr.nll"
					return OperatorType.LOGICAL_OR;
			}
#line 135 "../../../Source/Core/AST/OperatorExpr.nll"
			switch (pFirst.m_eType)
			{
				case Token.Type.TOKEN_ANGLE_BRACKET_LEFT:
				{
#line 137 "../../../Source/Core/AST/OperatorExpr.nll"
					return OperatorType.LESS_THAN;
				}

				case Token.Type.TOKEN_ANGLE_BRACKET_RIGHT:
				{
#line 138 "../../../Source/Core/AST/OperatorExpr.nll"
					return OperatorType.GREATER_THAN;
				}

				case Token.Type.TOKEN_BITWISE_AND:
				{
#line 139 "../../../Source/Core/AST/OperatorExpr.nll"
					return OperatorType.BITWISE_AND;
				}

				case Token.Type.TOKEN_BITWISE_OR:
				{
#line 140 "../../../Source/Core/AST/OperatorExpr.nll"
					return OperatorType.BITWISE_OR;
				}

				case Token.Type.TOKEN_CARET:
				{
#line 141 "../../../Source/Core/AST/OperatorExpr.nll"
					return OperatorType.BITWISE_XOR;
				}

				case Token.Type.TOKEN_DIVIDE:
				{
#line 142 "../../../Source/Core/AST/OperatorExpr.nll"
					return OperatorType.DIVISION;
				}

				case Token.Type.TOKEN_DOT:
				{
#line 143 "../../../Source/Core/AST/OperatorExpr.nll"
					return OperatorType.MEMBER_ACCESS;
				}

				case Token.Type.TOKEN_DOUBLE_COLON:
				{
#line 144 "../../../Source/Core/AST/OperatorExpr.nll"
					return OperatorType.SCOPE_RESOLUTION;
				}

				case Token.Type.TOKEN_EQUALS:
				{
#line 145 "../../../Source/Core/AST/OperatorExpr.nll"
					return OperatorType.ASSIGNMENT;
				}

				case Token.Type.TOKEN_MINUS:
				{
#line 146 "../../../Source/Core/AST/OperatorExpr.nll"
					return OperatorType.SUBTRACTION;
				}

				case Token.Type.TOKEN_MINUS_MINUS:
				{
#line 147 "../../../Source/Core/AST/OperatorExpr.nll"
					return OperatorType.DECREMENT;
				}

				case Token.Type.TOKEN_MODULUS:
				{
#line 148 "../../../Source/Core/AST/OperatorExpr.nll"
					return OperatorType.MODULO;
				}

				case Token.Type.TOKEN_PLUS:
				{
#line 149 "../../../Source/Core/AST/OperatorExpr.nll"
					return OperatorType.ADDITION;
				}

				case Token.Type.TOKEN_PLUS_PLUS:
				{
#line 150 "../../../Source/Core/AST/OperatorExpr.nll"
					return OperatorType.INCREMENT;
				}

				case Token.Type.TOKEN_STAR:
				{
#line 151 "../../../Source/Core/AST/OperatorExpr.nll"
					return OperatorType.MULTIPLICATION;
				}

			}
#line 153 "../../../Source/Core/AST/OperatorExpr.nll"
			return OperatorType.UNKNOWN;
		}

#line 156 "../../../Source/Core/AST/OperatorExpr.nll"
		public static OperatorExpr.OperatorType PeekOperator(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			Token pFirst = pTokenContainer.Peek(pOffsetDatum);
#line 159 "../../../Source/Core/AST/OperatorExpr.nll"
			if (pFirst == null)
#line 160 "../../../Source/Core/AST/OperatorExpr.nll"
				return OperatorType.UNKNOWN;
#line 161 "../../../Source/Core/AST/OperatorExpr.nll"
			pOffsetDatum.m_nOffset++;
			Token pSecond = pTokenContainer.Peek(pOffsetDatum);
#line 163 "../../../Source/Core/AST/OperatorExpr.nll"
			pOffsetDatum.m_nOffset++;
			Token pThird = pTokenContainer.Peek(pOffsetDatum);
#line 165 "../../../Source/Core/AST/OperatorExpr.nll"
			pOffsetDatum.m_nOffset -= 2;
			OperatorType eType = GetOperatorTypeFromTokens(pFirst, pSecond, pThird);
#line 168 "../../../Source/Core/AST/OperatorExpr.nll"
			if (eType == OperatorType.UNKNOWN)
#line 169 "../../../Source/Core/AST/OperatorExpr.nll"
				return OperatorType.UNKNOWN;
#line 170 "../../../Source/Core/AST/OperatorExpr.nll"
			pOffsetDatum.m_nOffset += GetOperatorTokenCount(eType);
#line 171 "../../../Source/Core/AST/OperatorExpr.nll"
			return eType;
		}

#line 174 "../../../Source/Core/AST/OperatorExpr.nll"
		public static OperatorExpr Create(OperatorExpr.OperatorType eOperatorType, Token pFirstOperatorToken, AST pLeft, AST pRight)
		{
#line 176 "../../../Source/Core/AST/OperatorExpr.nll"
			Assert.Plz(pLeft != null);
#line 177 "../../../Source/Core/AST/OperatorExpr.nll"
			if (IsPostfix(eOperatorType))
#line 178 "../../../Source/Core/AST/OperatorExpr.nll"
				Assert.Plz(pRight == null);
			OperatorExpr pOperatorExpr = new OperatorExpr();
			AST pOwnedLeft = pLeft;
			AST pOwnedRight = pRight;
#line 185 "../../../Source/Core/AST/OperatorExpr.nll"
			pOperatorExpr.m_pFirstToken = pLeft.m_pFirstToken;
#line 186 "../../../Source/Core/AST/OperatorExpr.nll"
			pOperatorExpr.m_eOperatorType = eOperatorType;
#line 187 "../../../Source/Core/AST/OperatorExpr.nll"
			pOperatorExpr.m_pFirstOperatorToken = pFirstOperatorToken;
#line 188 "../../../Source/Core/AST/OperatorExpr.nll"
			pOperatorExpr.m_pLeft = pOwnedLeft;
#line 189 "../../../Source/Core/AST/OperatorExpr.nll"
			pOperatorExpr.m_pRight = pOwnedRight;
#line 191 "../../../Source/Core/AST/OperatorExpr.nll"
			if (pLeft != null)
			{
				NumbatLogic.AST __4182703981 = pOwnedLeft;
#line 192 "../../../Source/Core/AST/OperatorExpr.nll"
				pOwnedLeft = null;
#line 192 "../../../Source/Core/AST/OperatorExpr.nll"
				pOperatorExpr.AddChild(__4182703981);
			}
#line 194 "../../../Source/Core/AST/OperatorExpr.nll"
			if (pRight != null)
			{
				NumbatLogic.AST __2506872229 = pOwnedRight;
#line 195 "../../../Source/Core/AST/OperatorExpr.nll"
				pOwnedRight = null;
#line 195 "../../../Source/Core/AST/OperatorExpr.nll"
				pOperatorExpr.AddChild(__2506872229);
			}
			NumbatLogic.OperatorExpr __2366106373 = pOperatorExpr;
#line 197 "../../../Source/Core/AST/OperatorExpr.nll"
			pOperatorExpr = null;
#line 197 "../../../Source/Core/AST/OperatorExpr.nll"
			return __2366106373;
		}

#line 200 "../../../Source/Core/AST/OperatorExpr.nll"
		public override AST BaseClone()
		{
			AST pLeft = null;
			AST pRight = null;
#line 205 "../../../Source/Core/AST/OperatorExpr.nll"
			if (m_pLeft != null)
#line 206 "../../../Source/Core/AST/OperatorExpr.nll"
				pLeft = m_pLeft.BaseClone();
#line 208 "../../../Source/Core/AST/OperatorExpr.nll"
			if (m_pRight != null)
#line 209 "../../../Source/Core/AST/OperatorExpr.nll"
				pRight = m_pRight.BaseClone();
			Token pOwnedClone = GetFirstOperatorToken().Clone();
			NumbatLogic.AST __3927143451 = pLeft;
#line 212 "../../../Source/Core/AST/OperatorExpr.nll"
			pLeft = null;
			NumbatLogic.AST __542262598 = pRight;
#line 212 "../../../Source/Core/AST/OperatorExpr.nll"
			pRight = null;
			OperatorExpr pResult = OperatorExpr.Create(m_eOperatorType, pOwnedClone, __3927143451, __542262598);
			NumbatLogic.Token __425741643 = pOwnedClone;
#line 213 "../../../Source/Core/AST/OperatorExpr.nll"
			pOwnedClone = null;
#line 213 "../../../Source/Core/AST/OperatorExpr.nll"
			pResult.m_pOwnedOperatorToken = __425741643;
			NumbatLogic.OperatorExpr __3076476007 = pResult;
#line 214 "../../../Source/Core/AST/OperatorExpr.nll"
			pResult = null;
#line 214 "../../../Source/Core/AST/OperatorExpr.nll"
			return __3076476007;
		}

#line 217 "../../../Source/Core/AST/OperatorExpr.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
#line 235 "../../../Source/Core/AST/OperatorExpr.nll"
			if (m_pLeft != null)
			{
#line 237 "../../../Source/Core/AST/OperatorExpr.nll"
				m_pLeft.Validate(pValidator, pParent);
#line 238 "../../../Source/Core/AST/OperatorExpr.nll"
				if (m_pLeft.m_pValueType == null)
				{
#line 240 "../../../Source/Core/AST/OperatorExpr.nll"
					pValidator.AddError("No ValueType for left of operator: ", m_pLeft.m_pFirstToken.m_sFileName, m_pLeft.m_pFirstToken.m_nLine, m_pLeft.m_pFirstToken.m_nColumn);
#line 241 "../../../Source/Core/AST/OperatorExpr.nll"
					return;
				}
				else
				{
					Token pOpToken = GetFirstOperatorToken();
#line 246 "../../../Source/Core/AST/OperatorExpr.nll"
					if (m_pLeft.m_pValueType.m_eType == ValueType.Type.CLASS_DECL || m_pLeft.m_pValueType.m_eType == ValueType.Type.ENUM_DECL || m_pLeft.m_pValueType.m_eType == ValueType.Type.NAMESPACE_NODE)
					{
#line 248 "../../../Source/Core/AST/OperatorExpr.nll"
						if (GetOperatorType() != OperatorType.SCOPE_RESOLUTION)
						{
#line 250 "../../../Source/Core/AST/OperatorExpr.nll"
							pValidator.AddError("Expected :: ", pOpToken.m_sFileName, pOpToken.m_nLine, pOpToken.m_nColumn);
#line 251 "../../../Source/Core/AST/OperatorExpr.nll"
							return;
						}
#line 253 "../../../Source/Core/AST/OperatorExpr.nll"
						if (m_pRight == null)
						{
#line 255 "../../../Source/Core/AST/OperatorExpr.nll"
							pValidator.AddError("Expected right side of :: operator", pOpToken.m_sFileName, pOpToken.m_nLine, pOpToken.m_nColumn);
#line 256 "../../../Source/Core/AST/OperatorExpr.nll"
							return;
						}
#line 259 "../../../Source/Core/AST/OperatorExpr.nll"
						if (m_pRight.m_eType != AST.Type.AST_IDENTIFIER && m_pRight.m_eType != AST.Type.AST_OPERATOR_EXPR && m_pRight.m_eType != AST.Type.AST_FUNCTION_CALL && m_pRight.m_eType != AST.Type.AST_ARRAY_LOOKUP)
						{
							InternalString sTemp = new InternalString("Unexpected right side of :: operator: ");
#line 262 "../../../Source/Core/AST/OperatorExpr.nll"
							m_pRight.StringifyType(sTemp);
#line 264 "../../../Source/Core/AST/OperatorExpr.nll"
							pValidator.AddError(sTemp.GetExternalString(), pOpToken.m_sFileName, pOpToken.m_nLine, pOpToken.m_nColumn);
#line 265 "../../../Source/Core/AST/OperatorExpr.nll"
							return;
						}
#line 268 "../../../Source/Core/AST/OperatorExpr.nll"
						m_pRight.Validate(pValidator, this);
#line 269 "../../../Source/Core/AST/OperatorExpr.nll"
						if (m_pRight.m_pValueType == null)
						{
#line 271 "../../../Source/Core/AST/OperatorExpr.nll"
							pValidator.AddError("No ValueType for right of operator: ", m_pRight.m_pFirstToken.m_sFileName, m_pRight.m_pFirstToken.m_nLine, m_pRight.m_pFirstToken.m_nColumn);
#line 272 "../../../Source/Core/AST/OperatorExpr.nll"
							return;
						}
#line 275 "../../../Source/Core/AST/OperatorExpr.nll"
						m_pValueType = m_pRight.m_pValueType.Clone();
#line 277 "../../../Source/Core/AST/OperatorExpr.nll"
						return;
					}
#line 280 "../../../Source/Core/AST/OperatorExpr.nll"
					if (GetOperatorType() == OperatorType.MEMBER_ACCESS)
					{
#line 282 "../../../Source/Core/AST/OperatorExpr.nll"
						if (m_pLeft.m_pValueType.m_eType == ValueType.Type.GENERIC_TYPE_DECL_VALUE)
						{
#line 284 "../../../Source/Core/AST/OperatorExpr.nll"
							if (m_pLeft.m_pValueType.m_pGenericTypeDecl == null)
							{
#line 286 "../../../Source/Core/AST/OperatorExpr.nll"
								pValidator.AddError(" set but m_pGenericTypeDecl is null???", pOpToken.m_sFileName, pOpToken.m_nLine, pOpToken.m_nColumn);
#line 287 "../../../Source/Core/AST/OperatorExpr.nll"
								return;
							}
						}
						else
#line 290 "../../../Source/Core/AST/OperatorExpr.nll"
							if (m_pLeft.m_pValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE)
							{
#line 292 "../../../Source/Core/AST/OperatorExpr.nll"
								if (m_pLeft.m_pValueType.m_pClassDecl == null)
								{
#line 294 "../../../Source/Core/AST/OperatorExpr.nll"
									pValidator.AddError(" set but m_pClassDecl is null???", pOpToken.m_sFileName, pOpToken.m_nLine, pOpToken.m_nColumn);
#line 295 "../../../Source/Core/AST/OperatorExpr.nll"
									return;
								}
							}
							else
							{
#line 300 "../../../Source/Core/AST/OperatorExpr.nll"
								pValidator.AddError("Expected ValueType::Type::CLASS_DECL_VALUE or ValueType::Type::GENERIC_TYPE_DECL_VALUE on left of TOKEN_DOT operator", pOpToken.m_sFileName, pOpToken.m_nLine, pOpToken.m_nColumn);
#line 301 "../../../Source/Core/AST/OperatorExpr.nll"
								return;
							}
#line 304 "../../../Source/Core/AST/OperatorExpr.nll"
						m_pRight.Validate(pValidator, this);
#line 305 "../../../Source/Core/AST/OperatorExpr.nll"
						if (m_pRight.m_pValueType == null)
						{
#line 307 "../../../Source/Core/AST/OperatorExpr.nll"
							pValidator.AddError("No ValueType for right of operator: ", m_pRight.m_pFirstToken.m_sFileName, m_pRight.m_pFirstToken.m_nLine, m_pRight.m_pFirstToken.m_nColumn);
#line 308 "../../../Source/Core/AST/OperatorExpr.nll"
							return;
						}
#line 311 "../../../Source/Core/AST/OperatorExpr.nll"
						m_pValueType = m_pRight.m_pValueType.Clone();
#line 312 "../../../Source/Core/AST/OperatorExpr.nll"
						return;
					}
#line 315 "../../../Source/Core/AST/OperatorExpr.nll"
					if (GetOperatorType() == OperatorType.ADDITION)
					{
#line 317 "../../../Source/Core/AST/OperatorExpr.nll"
						if (m_pLeft.m_pValueType.m_eType == ValueType.Type.STRING)
						{
#line 319 "../../../Source/Core/AST/OperatorExpr.nll"
							pValidator.AddError("Cannot concat strings with +", pOpToken.m_sFileName, pOpToken.m_nLine, pOpToken.m_nColumn);
#line 320 "../../../Source/Core/AST/OperatorExpr.nll"
							return;
						}
					}
#line 324 "../../../Source/Core/AST/OperatorExpr.nll"
					if (GetOperatorType() == OperatorType.EQUALITY || GetOperatorType() == OperatorType.INEQUALITY)
					{
#line 326 "../../../Source/Core/AST/OperatorExpr.nll"
						if (m_pRight == null)
						{
#line 328 "../../../Source/Core/AST/OperatorExpr.nll"
							pValidator.AddError("Nohing on right side to compare?", pOpToken.m_sFileName, pOpToken.m_nLine, pOpToken.m_nColumn);
#line 329 "../../../Source/Core/AST/OperatorExpr.nll"
							return;
						}
#line 332 "../../../Source/Core/AST/OperatorExpr.nll"
						m_pRight.Validate(pValidator, this);
#line 334 "../../../Source/Core/AST/OperatorExpr.nll"
						if (m_pLeft.m_pValueType.m_eType == ValueType.Type.STRING && m_pRight.m_pValueType.m_eType == ValueType.Type.STRING)
						{
#line 336 "../../../Source/Core/AST/OperatorExpr.nll"
							pValidator.AddError("Cannot == or != strings use ExternalString::Equal", pOpToken.m_sFileName, pOpToken.m_nLine, pOpToken.m_nColumn);
#line 337 "../../../Source/Core/AST/OperatorExpr.nll"
							return;
						}
#line 340 "../../../Source/Core/AST/OperatorExpr.nll"
						m_pValueType = new ValueType(ValueType.Type.BOOL);
#line 341 "../../../Source/Core/AST/OperatorExpr.nll"
						return;
					}
#line 344 "../../../Source/Core/AST/OperatorExpr.nll"
					if (m_pRight != null)
#line 345 "../../../Source/Core/AST/OperatorExpr.nll"
						m_pRight.Validate(pValidator, this);
#line 347 "../../../Source/Core/AST/OperatorExpr.nll"
					if (GetOperatorType() == OperatorType.ASSIGNMENT)
					{
#line 349 "../../../Source/Core/AST/OperatorExpr.nll"
						if (m_pRight.m_pValueType == null)
						{
#line 351 "../../../Source/Core/AST/OperatorExpr.nll"
							pValidator.AddError("No ValueType for right of operator = ???", m_pRight.m_pFirstToken.m_sFileName, m_pRight.m_pFirstToken.m_nLine, m_pRight.m_pFirstToken.m_nColumn);
#line 352 "../../../Source/Core/AST/OperatorExpr.nll"
							return;
						}
#line 355 "../../../Source/Core/AST/OperatorExpr.nll"
						if (m_pLeft.m_pValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE)
						{
#line 357 "../../../Source/Core/AST/OperatorExpr.nll"
							if (m_pRight.m_pValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE)
							{
#line 363 "../../../Source/Core/AST/OperatorExpr.nll"
								if (m_pLeft.m_pValueType.m_ePointerType == TypeRef.PointerType.OWNED && m_pRight.m_pValueType.m_ePointerType != TypeRef.PointerType.OWNED_PREASSSIGN)
								{
									InternalString sTemp = new InternalString("Expected right side of = to be OWNED_PREASSSIGN (result of own). FROM[");
#line 366 "../../../Source/Core/AST/OperatorExpr.nll"
									m_pRight.m_pValueType.StringifyType(sTemp);
#line 367 "../../../Source/Core/AST/OperatorExpr.nll"
									if (m_pRight.m_pValueType.m_pClassDecl != null)
									{
#line 369 "../../../Source/Core/AST/OperatorExpr.nll"
										sTemp.Append(" name=");
#line 370 "../../../Source/Core/AST/OperatorExpr.nll"
										sTemp.AppendString(m_pRight.m_pValueType.m_pClassDecl.m_pNameToken.GetString());
									}
#line 372 "../../../Source/Core/AST/OperatorExpr.nll"
									sTemp.Append(" ptr=");
#line 373 "../../../Source/Core/AST/OperatorExpr.nll"
									ValueType.StringifyPointerType(sTemp, m_pRight.m_pValueType.m_ePointerType);
#line 374 "../../../Source/Core/AST/OperatorExpr.nll"
									sTemp.Append("] TO[");
#line 375 "../../../Source/Core/AST/OperatorExpr.nll"
									m_pLeft.m_pValueType.StringifyType(sTemp);
#line 376 "../../../Source/Core/AST/OperatorExpr.nll"
									if (m_pLeft.m_pValueType.m_pClassDecl != null)
									{
#line 378 "../../../Source/Core/AST/OperatorExpr.nll"
										sTemp.Append(" name=");
#line 379 "../../../Source/Core/AST/OperatorExpr.nll"
										sTemp.AppendString(m_pLeft.m_pValueType.m_pClassDecl.m_pNameToken.GetString());
									}
#line 381 "../../../Source/Core/AST/OperatorExpr.nll"
									sTemp.Append(" ptr=");
#line 382 "../../../Source/Core/AST/OperatorExpr.nll"
									ValueType.StringifyPointerType(sTemp, m_pLeft.m_pValueType.m_ePointerType);
#line 383 "../../../Source/Core/AST/OperatorExpr.nll"
									sTemp.Append("]");
#line 384 "../../../Source/Core/AST/OperatorExpr.nll"
									pValidator.AddError(sTemp.GetExternalString(), pOpToken.m_sFileName, pOpToken.m_nLine, pOpToken.m_nColumn);
#line 385 "../../../Source/Core/AST/OperatorExpr.nll"
									return;
								}
#line 388 "../../../Source/Core/AST/OperatorExpr.nll"
								if (m_pLeft.m_pValueType.m_ePointerType == TypeRef.PointerType.SHARED && m_pRight.m_pValueType.m_ePointerType == TypeRef.PointerType.OWNED_PREASSSIGN)
								{
									InternalString sTemp = new InternalString("Can't store an owned pointer in a shared pointer. FROM[");
#line 391 "../../../Source/Core/AST/OperatorExpr.nll"
									m_pRight.m_pValueType.StringifyType(sTemp);
#line 392 "../../../Source/Core/AST/OperatorExpr.nll"
									if (m_pRight.m_pValueType.m_pClassDecl != null)
									{
#line 394 "../../../Source/Core/AST/OperatorExpr.nll"
										sTemp.Append(" name=");
#line 395 "../../../Source/Core/AST/OperatorExpr.nll"
										sTemp.AppendString(m_pRight.m_pValueType.m_pClassDecl.m_pNameToken.GetString());
									}
#line 397 "../../../Source/Core/AST/OperatorExpr.nll"
									sTemp.Append(" ptr=");
#line 398 "../../../Source/Core/AST/OperatorExpr.nll"
									ValueType.StringifyPointerType(sTemp, m_pRight.m_pValueType.m_ePointerType);
#line 399 "../../../Source/Core/AST/OperatorExpr.nll"
									sTemp.Append("] TO[");
#line 400 "../../../Source/Core/AST/OperatorExpr.nll"
									m_pLeft.m_pValueType.StringifyType(sTemp);
#line 401 "../../../Source/Core/AST/OperatorExpr.nll"
									if (m_pLeft.m_pValueType.m_pClassDecl != null)
									{
#line 403 "../../../Source/Core/AST/OperatorExpr.nll"
										sTemp.Append(" name=");
#line 404 "../../../Source/Core/AST/OperatorExpr.nll"
										sTemp.AppendString(m_pLeft.m_pValueType.m_pClassDecl.m_pNameToken.GetString());
									}
#line 406 "../../../Source/Core/AST/OperatorExpr.nll"
									sTemp.Append(" ptr=");
#line 407 "../../../Source/Core/AST/OperatorExpr.nll"
									ValueType.StringifyPointerType(sTemp, m_pLeft.m_pValueType.m_ePointerType);
#line 408 "../../../Source/Core/AST/OperatorExpr.nll"
									sTemp.Append("]");
#line 409 "../../../Source/Core/AST/OperatorExpr.nll"
									pValidator.AddError(sTemp.GetExternalString(), pOpToken.m_sFileName, pOpToken.m_nLine, pOpToken.m_nColumn);
#line 410 "../../../Source/Core/AST/OperatorExpr.nll"
									return;
								}
#line 413 "../../../Source/Core/AST/OperatorExpr.nll"
								if (m_pRight.m_pValueType.m_ePointerType == TypeRef.PointerType.TRANSITON)
								{
									InternalString sTemp = new InternalString("Cannot store a TRANSITION pointer (need to `own` it). FROM[");
#line 416 "../../../Source/Core/AST/OperatorExpr.nll"
									m_pRight.m_pValueType.StringifyType(sTemp);
#line 417 "../../../Source/Core/AST/OperatorExpr.nll"
									if (m_pRight.m_pValueType.m_pClassDecl != null)
									{
#line 419 "../../../Source/Core/AST/OperatorExpr.nll"
										sTemp.Append(" name=");
#line 420 "../../../Source/Core/AST/OperatorExpr.nll"
										sTemp.AppendString(m_pRight.m_pValueType.m_pClassDecl.m_pNameToken.GetString());
									}
#line 422 "../../../Source/Core/AST/OperatorExpr.nll"
									sTemp.Append(" ptr=");
#line 423 "../../../Source/Core/AST/OperatorExpr.nll"
									ValueType.StringifyPointerType(sTemp, m_pRight.m_pValueType.m_ePointerType);
#line 424 "../../../Source/Core/AST/OperatorExpr.nll"
									sTemp.Append("] TO[");
#line 425 "../../../Source/Core/AST/OperatorExpr.nll"
									m_pLeft.m_pValueType.StringifyType(sTemp);
#line 426 "../../../Source/Core/AST/OperatorExpr.nll"
									if (m_pLeft.m_pValueType.m_pClassDecl != null)
									{
#line 428 "../../../Source/Core/AST/OperatorExpr.nll"
										sTemp.Append(" name=");
#line 429 "../../../Source/Core/AST/OperatorExpr.nll"
										sTemp.AppendString(m_pLeft.m_pValueType.m_pClassDecl.m_pNameToken.GetString());
									}
#line 431 "../../../Source/Core/AST/OperatorExpr.nll"
									sTemp.Append(" ptr=");
#line 432 "../../../Source/Core/AST/OperatorExpr.nll"
									ValueType.StringifyPointerType(sTemp, m_pLeft.m_pValueType.m_ePointerType);
#line 433 "../../../Source/Core/AST/OperatorExpr.nll"
									sTemp.Append("]");
#line 434 "../../../Source/Core/AST/OperatorExpr.nll"
									pValidator.AddError(sTemp.GetExternalString(), pOpToken.m_sFileName, pOpToken.m_nLine, pOpToken.m_nColumn);
#line 435 "../../../Source/Core/AST/OperatorExpr.nll"
									return;
								}
#line 440 "../../../Source/Core/AST/OperatorExpr.nll"
								if (m_pLeft.m_pValueType.m_pClassDecl != m_pRight.m_pValueType.m_pClassDecl)
								{
#line 443 "../../../Source/Core/AST/OperatorExpr.nll"
									AddClassDeclReference(m_pRight.m_pValueType.m_pClassDecl, AST.OutputFile.SOURCE, false);
									ClassDecl pBaseClassDecl = m_pRight.m_pValueType.m_pClassDecl.GetBaseClassDecl(pValidator);
#line 447 "../../../Source/Core/AST/OperatorExpr.nll"
									while (pBaseClassDecl != null)
									{
#line 449 "../../../Source/Core/AST/OperatorExpr.nll"
										if (pBaseClassDecl == m_pLeft.m_pValueType.m_pClassDecl)
#line 450 "../../../Source/Core/AST/OperatorExpr.nll"
											break;
#line 451 "../../../Source/Core/AST/OperatorExpr.nll"
										pBaseClassDecl = pBaseClassDecl.GetBaseClassDecl(pValidator);
									}
#line 454 "../../../Source/Core/AST/OperatorExpr.nll"
									if (pBaseClassDecl != m_pLeft.m_pValueType.m_pClassDecl)
									{
										InternalString sTemp = new InternalString("Can't assign ");
#line 457 "../../../Source/Core/AST/OperatorExpr.nll"
										sTemp.AppendString(m_pRight.m_pValueType.m_pClassDecl.m_pNameToken.GetString());
#line 458 "../../../Source/Core/AST/OperatorExpr.nll"
										sTemp.AppendString(" to ");
#line 459 "../../../Source/Core/AST/OperatorExpr.nll"
										sTemp.AppendString(m_pLeft.m_pValueType.m_pClassDecl.m_pNameToken.GetString());
#line 461 "../../../Source/Core/AST/OperatorExpr.nll"
										pValidator.AddError(sTemp.GetExternalString(), pOpToken.m_sFileName, pOpToken.m_nLine, pOpToken.m_nColumn);
#line 462 "../../../Source/Core/AST/OperatorExpr.nll"
										return;
									}
								}
							}
							else
#line 467 "../../../Source/Core/AST/OperatorExpr.nll"
								if (m_pRight.m_pValueType.m_eType == ValueType.Type.NULL_VALUE)
								{
								}
								else
#line 471 "../../../Source/Core/AST/OperatorExpr.nll"
									if (m_pRight.m_pValueType.m_eType == ValueType.Type.GENERIC_TYPE_DECL_VALUE)
									{
									}
									else
									{
#line 477 "../../../Source/Core/AST/OperatorExpr.nll"
										pValidator.AddError("Expected right side of = to also be CLASS_DECL_VALUE or NULL_VALUE\n", pOpToken.m_sFileName, pOpToken.m_nLine, pOpToken.m_nColumn);
#line 478 "../../../Source/Core/AST/OperatorExpr.nll"
										return;
									}
						}
#line 482 "../../../Source/Core/AST/OperatorExpr.nll"
						m_pValueType = m_pLeft.m_pValueType.Clone();
#line 483 "../../../Source/Core/AST/OperatorExpr.nll"
						return;
					}
#line 488 "../../../Source/Core/AST/OperatorExpr.nll"
					m_pValueType = m_pLeft.m_pValueType.Clone();
#line 489 "../../../Source/Core/AST/OperatorExpr.nll"
					return;
				}
			}
#line 493 "../../../Source/Core/AST/OperatorExpr.nll"
			if (m_pRight != null)
			{
#line 495 "../../../Source/Core/AST/OperatorExpr.nll"
				m_pRight.Validate(pValidator, null);
#line 496 "../../../Source/Core/AST/OperatorExpr.nll"
				if (m_pRight.m_pValueType == null)
				{
				}
			}
#line 502 "../../../Source/Core/AST/OperatorExpr.nll"
			if (m_pParent != null)
			{
			}
		}

#line 509 "../../../Source/Core/AST/OperatorExpr.nll"
		protected static string GetOperatorString(OperatorExpr.OperatorType eOperatorType)
		{
#line 511 "../../../Source/Core/AST/OperatorExpr.nll"
			switch (eOperatorType)
			{
				case OperatorType.LOGICAL_AND:
				{
#line 513 "../../../Source/Core/AST/OperatorExpr.nll"
					return "&&";
				}

				case OperatorType.LESS_THAN:
				{
#line 514 "../../../Source/Core/AST/OperatorExpr.nll"
					return "<";
				}

				case OperatorType.LESS_THAN_OR_EQUAL:
				{
#line 515 "../../../Source/Core/AST/OperatorExpr.nll"
					return "<=";
				}

				case OperatorType.GREATER_THAN:
				{
#line 516 "../../../Source/Core/AST/OperatorExpr.nll"
					return ">";
				}

				case OperatorType.GREATER_THAN_OR_EQUAL:
				{
#line 517 "../../../Source/Core/AST/OperatorExpr.nll"
					return ">=";
				}

				case OperatorType.BITWISE_AND:
				{
#line 518 "../../../Source/Core/AST/OperatorExpr.nll"
					return "&";
				}

				case OperatorType.BITWISE_OR:
				{
#line 519 "../../../Source/Core/AST/OperatorExpr.nll"
					return "|";
				}

				case OperatorType.BITWISE_XOR:
				{
#line 520 "../../../Source/Core/AST/OperatorExpr.nll"
					return "^";
				}

				case OperatorType.DIVISION:
				{
#line 521 "../../../Source/Core/AST/OperatorExpr.nll"
					return "/";
				}

				case OperatorType.MEMBER_ACCESS:
				{
#line 522 "../../../Source/Core/AST/OperatorExpr.nll"
					return ".";
				}

				case OperatorType.LEFT_SHIFT:
				{
#line 523 "../../../Source/Core/AST/OperatorExpr.nll"
					return "<<";
				}

				case OperatorType.RIGHT_SHIFT:
				{
#line 524 "../../../Source/Core/AST/OperatorExpr.nll"
					return ">>";
				}

				case OperatorType.SCOPE_RESOLUTION:
				{
#line 525 "../../../Source/Core/AST/OperatorExpr.nll"
					return "::";
				}

				case OperatorType.EQUALITY:
				{
#line 526 "../../../Source/Core/AST/OperatorExpr.nll"
					return "==";
				}

				case OperatorType.ASSIGNMENT:
				{
#line 527 "../../../Source/Core/AST/OperatorExpr.nll"
					return "=";
				}

				case OperatorType.SUBTRACTION:
				{
#line 528 "../../../Source/Core/AST/OperatorExpr.nll"
					return "-";
				}

				case OperatorType.SUBTRACT_ASSIGN:
				{
#line 529 "../../../Source/Core/AST/OperatorExpr.nll"
					return "-=";
				}

				case OperatorType.DECREMENT:
				{
#line 530 "../../../Source/Core/AST/OperatorExpr.nll"
					return "--";
				}

				case OperatorType.MODULO:
				{
#line 531 "../../../Source/Core/AST/OperatorExpr.nll"
					return "%";
				}

				case OperatorType.INEQUALITY:
				{
#line 532 "../../../Source/Core/AST/OperatorExpr.nll"
					return "!=";
				}

				case OperatorType.LOGICAL_OR:
				{
#line 533 "../../../Source/Core/AST/OperatorExpr.nll"
					return "||";
				}

				case OperatorType.ADDITION:
				{
#line 534 "../../../Source/Core/AST/OperatorExpr.nll"
					return "+";
				}

				case OperatorType.ADD_ASSIGN:
				{
#line 535 "../../../Source/Core/AST/OperatorExpr.nll"
					return "+=";
				}

				case OperatorType.INCREMENT:
				{
#line 536 "../../../Source/Core/AST/OperatorExpr.nll"
					return "++";
				}

				case OperatorType.MULTIPLICATION:
				{
#line 537 "../../../Source/Core/AST/OperatorExpr.nll"
					return "*";
				}

				case OperatorType.MULTIPLY_ASSIGN:
				{
#line 538 "../../../Source/Core/AST/OperatorExpr.nll"
					return "*=";
				}

				case OperatorType.DIVIDE_ASSIGN:
				{
#line 539 "../../../Source/Core/AST/OperatorExpr.nll"
					return "/=";
				}

				case OperatorType.LEFT_SHIFT_ASSIGN:
				{
#line 540 "../../../Source/Core/AST/OperatorExpr.nll"
					return "<<=";
				}

				case OperatorType.RIGHT_SHIFT_ASSIGN:
				{
#line 541 "../../../Source/Core/AST/OperatorExpr.nll"
					return ">>=";
				}

				default:
				{
#line 542 "../../../Source/Core/AST/OperatorExpr.nll"
					return "?";
				}

			}
		}

#line 546 "../../../Source/Core/AST/OperatorExpr.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			OperatorType eOp = GetOperatorType();
			string sPad = " ";
#line 550 "../../../Source/Core/AST/OperatorExpr.nll"
			if (eOp == OperatorType.DECREMENT || eOp == OperatorType.INCREMENT || eOp == OperatorType.MEMBER_ACCESS || eOp == OperatorType.SCOPE_RESOLUTION)
#line 551 "../../../Source/Core/AST/OperatorExpr.nll"
				sPad = "";
			string sOperator = GetOperatorString(eOp);
#line 554 "../../../Source/Core/AST/OperatorExpr.nll"
			if (eLanguage == AST.Language.CS && eOp == OperatorType.SCOPE_RESOLUTION)
#line 555 "../../../Source/Core/AST/OperatorExpr.nll"
				sOperator = ".";
#line 556 "../../../Source/Core/AST/OperatorExpr.nll"
			if (eLanguage == AST.Language.CPP && eOp == OperatorType.MEMBER_ACCESS)
			{
#line 558 "../../../Source/Core/AST/OperatorExpr.nll"
				sOperator = "->";
#line 559 "../../../Source/Core/AST/OperatorExpr.nll"
				if (m_pLeft.m_eType == AST.Type.BASE_EXPR)
#line 560 "../../../Source/Core/AST/OperatorExpr.nll"
					sOperator = "::";
			}
#line 563 "../../../Source/Core/AST/OperatorExpr.nll"
			m_pLeft.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 564 "../../../Source/Core/AST/OperatorExpr.nll"
			pOutputBuilder.m_sOut.Append(sPad);
#line 565 "../../../Source/Core/AST/OperatorExpr.nll"
			pOutputBuilder.m_sOut.Append(sOperator);
#line 567 "../../../Source/Core/AST/OperatorExpr.nll"
			if (m_pRight != null)
			{
#line 569 "../../../Source/Core/AST/OperatorExpr.nll"
				pOutputBuilder.m_sOut.Append(sPad);
#line 570 "../../../Source/Core/AST/OperatorExpr.nll"
				m_pRight.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			}
		}

#line 4 "../../../Source/Core/AST/OperatorExpr.nll"
		~OperatorExpr()
		{
		}

	}
}

