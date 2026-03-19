#line 1 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
namespace NumbatLogic
{
	class AST
	{
		public enum Type
		{
			AST_ACCESS_LEVEL,
			AST_ARRAY_LOOKUP,
			AST_BOOL_EXPR,
			AST_BREAK_STMT,
			AST_CAST_EXP,
			AST_DECORATOR_CALL,
			AST_CHAR,
			AST_CLASS_DECL,
			AST_CONTINUE_STMT,
			AST_DELETE_STMT,
			AST_DISOWN_EXP,
			AST_ENUM_DECL,
			AST_EXPRESSION_STMT,
			AST_FOR_STMT,
			AST_FUNCTION_CALL,
			AST_FUNCTION_DECL,
			AST_GENERIC_TYPE_DECL,
			AST_IDENTIFIER,
			AST_IF_STMT,
			AST_MEMBER_CLASS_DECL,
			AST_MEMBER_ENUM_DECL,
			AST_MEMBER_FUNCTION_DECL,
			AST_MEMBER_VAR_DECL,
			AST_NEW_EXP,
			AST_NUMBER,
			AST_OPERATOR_EXPR,
			AST_OWN_EXP,
			AST_PARAM_CALL,
			AST_PARAM_DECL,
			AST_PAREN,
			AST_REF_EXPR,
			AST_RETURN_STMT,
			AST_SCOPE,
			AST_STATIC_ARRAY,
			AST_STRING,
			AST_SWITCH_STMT,
			AST_TOR_DECL,
			AST_TRANSLATION_UNIT,
			AST_TTHASH_EXP,
			AST_TYPE_REF,
			AST_UNARY,
			AST_VAR_DECL_DESCOPE,
			AST_VAR_DECL,
			AST_WHILE_STMT,
			AST_PROJECT,
			BASE_EXPR,
			DELEGATE_DECL,
			ENUM_DECL_VALUE,
			MEMBER_VARS_SET_DEFAULT_STMT,
			NAMESPACE_DECL,
			NULL_EXPR,
			THIS_EXPR,
		}

#line 60 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		public enum Language
		{
			NLL,
			NLL_DEF,
			CS,
			CPP,
			C,
			H,
			PHP,
		}

#line 70 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		public enum OutputFile
		{
			SOURCE,
			HEADER,
		}

#line 75 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		public Type m_eType;
		public Token m_pFirstToken;
#line 78 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		public AST m_pParent;
		public AST m_pFirstChild;
		public AST m_pLastChild;
		public AST m_pPrevSibling;
		public AST m_pNextSibling;
#line 85 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		public SymbolScope m_pSymbolScope;
#line 87 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		public bool m_bCanDescend;
#line 89 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		public ValueType m_pValueType;
#line 91 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		public bool m_bStatement;
#line 94 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		public bool m_bSkipOutput;
#line 96 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		public AST()
		{
			m_bStatement = false;
			m_bSkipOutput = false;
		}

		~AST()
		{
		}

		public static AST CreateFromTokenContainer(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			AST pAst = null;
#line 110 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst = FunctionDecl.TryCreate(pTokenContainer, pOffsetDatum, null);
			if (pAst != null)
			{
				NumbatLogic.AST __77877600 = pAst;
#line 112 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pAst = null;
#line 112 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return __77877600;
			}
			pAst = ClassDecl.TryCreate(pTokenContainer, pOffsetDatum, null);
			if (pAst != null)
			{
				NumbatLogic.AST __77877604 = pAst;
#line 116 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pAst = null;
#line 116 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return __77877604;
			}
			pAst = NamespaceDecl.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __77943197 = pAst;
#line 120 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pAst = null;
#line 120 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return __77943197;
			}
			pAst = CreateStatementFromTokenContainer(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __77943201 = pAst;
#line 124 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pAst = null;
#line 124 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return __77943201;
			}
			pAst = TryCreateExpression(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __77943205 = pAst;
#line 128 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pAst = null;
#line 128 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return __77943205;
			}
			return null;
		}

		public static AST CreateStatementFromTokenContainer(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			AST pAst = null;
#line 137 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst = ReturnStmt.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __78008805 = pAst;
#line 139 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pAst = null;
#line 139 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return __78008805;
			}
			pAst = BreakStmt.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __78074398 = pAst;
#line 143 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pAst = null;
#line 143 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return __78074398;
			}
			pAst = ContinueStmt.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __78074402 = pAst;
#line 147 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pAst = null;
#line 147 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return __78074402;
			}
			pAst = Scope.TryCreate(pTokenContainer, pOffsetDatum, false);
			if (pAst != null)
			{
				NumbatLogic.AST __78139995 = pAst;
#line 151 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pAst = null;
#line 151 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return __78139995;
			}
			pAst = VarDecl.TryCreate(pTokenContainer, pOffsetDatum, false);
			if (pAst != null)
			{
				NumbatLogic.AST __78139999 = pAst;
#line 155 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pAst = null;
#line 155 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return __78139999;
			}
			pAst = EnumDecl.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __78140003 = pAst;
#line 159 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pAst = null;
#line 159 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return __78140003;
			}
			pAst = DeleteStmt.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __78205596 = pAst;
#line 163 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pAst = null;
#line 163 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return __78205596;
			}
			pAst = IfStmt.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __78205600 = pAst;
#line 167 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pAst = null;
#line 167 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return __78205600;
			}
			pAst = ForStmt.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __78271193 = pAst;
#line 171 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pAst = null;
#line 171 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return __78271193;
			}
			pAst = WhileStmt.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __78271197 = pAst;
#line 175 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pAst = null;
#line 175 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return __78271197;
			}
			pAst = SwitchStmt.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __78271201 = pAst;
#line 179 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pAst = null;
#line 179 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return __78271201;
			}
			pAst = ExpressionStmt.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __78336794 = pAst;
#line 183 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pAst = null;
#line 183 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return __78336794;
			}
			return null;
		}

		protected static AST TryCreateInnerExpression(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			AST pAst = null;
#line 192 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst = NumberExpr.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __78402394 = pAst;
#line 194 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pAst = null;
#line 194 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return __78402394;
			}
			pAst = BoolExpr.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __78402398 = pAst;
#line 198 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pAst = null;
#line 198 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return __78402398;
			}
			pAst = CharExpr.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __86073506 = pAst;
#line 202 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pAst = null;
#line 202 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return __86073506;
			}
			pAst = StringExpr.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __86073510 = pAst;
#line 206 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pAst = null;
#line 206 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return __86073510;
			}
			pAst = NullExpr.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __86139103 = pAst;
#line 210 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pAst = null;
#line 210 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return __86139103;
			}
			pAst = ThisExpr.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __86139107 = pAst;
#line 214 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pAst = null;
#line 214 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return __86139107;
			}
			pAst = BaseExpr.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __86139111 = pAst;
#line 218 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pAst = null;
#line 218 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return __86139111;
			}
			pAst = FunctionCall.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __86204704 = pAst;
#line 222 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pAst = null;
#line 222 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return __86204704;
			}
			pAst = New.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __86204708 = pAst;
#line 226 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pAst = null;
#line 226 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return __86204708;
			}
			pAst = CastExpr.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __86270301 = pAst;
#line 230 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pAst = null;
#line 230 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return __86270301;
			}
			pAst = TTHashExpr.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __86270305 = pAst;
#line 234 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pAst = null;
#line 234 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return __86270305;
			}
			pAst = Unary.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __86270309 = pAst;
#line 238 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pAst = null;
#line 238 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return __86270309;
			}
			pAst = Paren.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __86335902 = pAst;
#line 242 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pAst = null;
#line 242 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return __86335902;
			}
			pAst = ArrayLookup.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __86335906 = pAst;
#line 246 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pAst = null;
#line 246 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return __86335906;
			}
			pAst = StaticArray.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __86401499 = pAst;
#line 250 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pAst = null;
#line 250 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return __86401499;
			}
			pAst = OwnExpr.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __86401503 = pAst;
#line 254 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pAst = null;
#line 254 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return __86401503;
			}
			pAst = DisownExpr.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __86401507 = pAst;
#line 258 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pAst = null;
#line 258 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return __86401507;
			}
			pAst = RefExpr.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __86467100 = pAst;
#line 262 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pAst = null;
#line 262 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return __86467100;
			}
			pAst = Identifier.TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != null)
			{
				NumbatLogic.AST __86467104 = pAst;
#line 266 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pAst = null;
#line 266 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return __86467104;
			}
			return null;
		}

		public static AST TryCreateExpression(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			AST pLeft = TryCreateInnerExpression(pTokenContainer, pTempOffset);
			if (pLeft != null)
			{
				Token pOperatorToken = pTokenContainer.Peek(pTempOffset);
				if (pOperatorToken != null && pOperatorToken.m_eType == Token.Type.TOKEN_QUESTION_MARK)
				{
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
					pOffsetDatum.Set(pTempOffset);
					NumbatLogic.AST __3927602645 = pLeft;
#line 282 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					pLeft = null;
#line 282 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return TrinaryExpr.Create(__3927602645, pTokenContainer, pOffsetDatum);
				}
#line 285 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				OperatorExpr.OperatorType eOperatorType = OperatorExpr.PeekOperator(pTokenContainer, pTempOffset);
				if (eOperatorType != OperatorExpr.OperatorType.UNKNOWN)
				{
					if (OperatorExpr.IsPostfix(eOperatorType))
					{
						pOffsetDatum.Set(pTempOffset);
						NumbatLogic.AST __3927668243 = pLeft;
#line 291 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
						pLeft = null;
#line 291 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
						return OperatorExpr.Create(eOperatorType, pOperatorToken, __3927668243, null);
					}
#line 294 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					AST pRight = TryCreateExpression(pTokenContainer, pTempOffset);
					if (pRight != null)
					{
						pOffsetDatum.Set(pTempOffset);
						NumbatLogic.AST __3927668250 = pLeft;
#line 298 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
						pLeft = null;
						NumbatLogic.AST __542787397 = pRight;
#line 298 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
						pRight = null;
#line 298 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
						return OperatorExpr.Create(eOperatorType, pOperatorToken, __3927668250, __542787397);
					}
#line 302 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					InternalString sTemp = new InternalString("Probably should have something after the operator??? ");
					sTemp.Append(pOperatorToken.m_sFileName.GetExternalString());
					sTemp.Append(":");
					sTemp.AppendInt(pOperatorToken.m_nLine);
					sTemp.Append(":");
					sTemp.AppendInt(pOperatorToken.m_nColumn);
					Console.Log(sTemp.GetExternalString());
					Assert.Plz(false);
				}
				pOffsetDatum.Set(pTempOffset);
				NumbatLogic.AST __3935404957 = pLeft;
#line 312 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pLeft = null;
#line 312 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return __3935404957;
			}
			return null;
		}

		public virtual void PreValidate(Validator pValidator, OperatorExpr pParent)
		{
			AST pChild = m_pFirstChild;
			while (pChild != null)
			{
#line 323 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				AST pNextSibling = pChild.m_pNextSibling;
				pChild.PreValidate(pValidator, null);
				pChild = pNextSibling;
			}
		}

		public virtual void Validate(Validator pValidator, OperatorExpr pParent)
		{
			AST pChild = m_pFirstChild;
			while (pChild != null)
			{
#line 335 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				AST pNextSibling = pChild.m_pNextSibling;
				pChild.Validate(pValidator, null);
				pChild = pNextSibling;
			}
		}

		public void AddChild(AST pAst)
		{
			pAst.m_pParent = this;
#line 345 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			if (m_pFirstChild == null)
			{
				m_pFirstChild = pAst;
				m_pLastChild = m_pFirstChild;
			}
			else
			{
				m_pLastChild.m_pNextSibling = pAst;
				m_pLastChild.m_pNextSibling.m_pPrevSibling = m_pLastChild;
				m_pLastChild = m_pLastChild.m_pNextSibling;
			}
		}

		public void AddChildFront(AST pAst)
		{
			if (m_pFirstChild == null)
			{
				AddChild(pAst);
				return;
			}
#line 366 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst.m_pParent = this;
			NumbatLogic.AST __1700709386 = m_pFirstChild;
#line 367 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			m_pFirstChild = null;
#line 367 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst.m_pNextSibling = __1700709386;
			m_pFirstChild = pAst;
			pAst.m_pNextSibling.m_pPrevSibling = m_pFirstChild;
		}

		public void AddChildBefore(AST pAst, AST pBefore)
		{
			Assert.Plz(pBefore.m_pParent == this);
#line 376 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst.m_pParent = this;
#line 378 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			if (m_pFirstChild == pBefore)
			{
				NumbatLogic.AST __1700840577 = m_pFirstChild;
#line 380 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				m_pFirstChild = null;
#line 380 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pAst.m_pNextSibling = __1700840577;
				m_pFirstChild = pAst;
				pBefore.m_pPrevSibling = m_pFirstChild;
			}
			else
			{
				NumbatLogic.AST __96456766 = pBefore.m_pPrevSibling.m_pNextSibling;
#line 386 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pBefore.m_pPrevSibling.m_pNextSibling = null;
#line 386 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pAst.m_pNextSibling = __96456766;
				pAst.m_pPrevSibling = pBefore.m_pPrevSibling;
				pBefore.m_pPrevSibling = (AST)(pAst);
				pAst.m_pPrevSibling.m_pNextSibling = pAst;
			}
		}

		public AST RemoveChild(AST pChild)
		{
			if (m_pFirstChild == pChild)
			{
				NumbatLogic.AST __1700906183 = m_pFirstChild;
#line 397 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				m_pFirstChild = null;
#line 397 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				AST pOwnedChild = __1700906183;
				if (m_pLastChild == pOwnedChild)
					m_pLastChild = null;
				else
				{
					NumbatLogic.AST __400431244 = pOwnedChild.m_pNextSibling;
#line 401 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					pOwnedChild.m_pNextSibling = null;
#line 401 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					m_pFirstChild = __400431244;
				}
#line 402 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pOwnedChild.m_pParent = null;
				NumbatLogic.AST __2252725200 = pOwnedChild;
#line 403 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pOwnedChild = null;
#line 403 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return __2252725200;
			}
			else
			{
				AST pFindChild = m_pFirstChild;
				while (pFindChild != null)
				{
					if (pFindChild.m_pNextSibling == pChild)
					{
						NumbatLogic.AST __326915200 = pFindChild.m_pNextSibling;
#line 412 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
						pFindChild.m_pNextSibling = null;
#line 412 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
						AST pOwnedChild = __326915200;
						if (m_pLastChild == pOwnedChild)
							m_pLastChild = pFindChild;
						else
						{
							NumbatLogic.AST __400496848 = pOwnedChild.m_pNextSibling;
#line 416 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
							pOwnedChild.m_pNextSibling = null;
#line 416 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
							pFindChild.m_pNextSibling = __400496848;
						}
#line 417 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
						pOwnedChild.m_pParent = null;
						NumbatLogic.AST __2252790804 = pOwnedChild;
#line 418 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
						pOwnedChild = null;
#line 418 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
						return __2252790804;
					}
#line 421 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					pFindChild = pFindChild.m_pNextSibling;
				}
			}
#line 425 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			return null;
		}

#line 429 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		public virtual void AddClassDeclReference(ClassDecl pClassDecl, OutputFile eOutputFile, bool bForwardReference)
		{
			if (m_pParent != null)
				m_pParent.AddClassDeclReference(pClassDecl, eOutputFile, bForwardReference);
		}

#line 436 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		public Project GetProject()
		{
			AST p = this;
			while (p != null && p.m_eType != AST.Type.AST_PROJECT)
				p = p.m_pParent;
			return p != null ? (Project)(p) : null;
		}

		public virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			pOutputBuilder.m_sOut.Append("???");
		}

		public virtual AST BaseClone()
		{
			InternalString sTemp = new InternalString("BaseClone() not setup for ");
			StringifyType(sTemp);
			Console.Log(sTemp.GetExternalString());
			Assert.Plz(false);
			return null;
		}

		public AST GetParentStatement()
		{
			AST pParent = m_pParent;
			while (pParent != null)
			{
				if (pParent.m_bStatement)
					break;
				pParent = pParent.m_pParent;
			}
#line 468 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			return pParent;
		}

		public virtual void StringifyType(InternalString sOut)
		{
			switch (m_eType)
			{
				case Type.AST_ACCESS_LEVEL:
				{
#line 475 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_ACCESS_LEVEL");
#line 475 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_ARRAY_LOOKUP:
				{
#line 476 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_ARRAY_LOOKUP");
#line 476 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_BOOL_EXPR:
				{
#line 477 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_BOOL_EXPR");
#line 477 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_BREAK_STMT:
				{
#line 478 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_BREAK_STMT");
#line 478 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_CAST_EXP:
				{
#line 479 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_CAST_EXP");
#line 479 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_CHAR:
				{
#line 480 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_CHAR");
#line 480 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_CLASS_DECL:
				{
#line 481 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_CLASS_DECL");
#line 481 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_CONTINUE_STMT:
				{
#line 482 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_CONTINUE_STMT");
#line 482 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_DELETE_STMT:
				{
#line 483 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_DELETE_STMT");
#line 483 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_DISOWN_EXP:
				{
#line 484 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_DISOWN_EXP");
#line 484 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_ENUM_DECL:
				{
#line 485 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_ENUM_DECL");
#line 485 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_EXPRESSION_STMT:
				{
#line 486 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_EXPRESSION_STMT");
#line 486 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_FOR_STMT:
				{
#line 487 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_FOR_STMT");
#line 487 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_FUNCTION_CALL:
				{
#line 488 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_FUNCTION_CALL");
#line 488 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_FUNCTION_DECL:
				{
#line 489 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_FUNCTION_DECL");
#line 489 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_GENERIC_TYPE_DECL:
				{
#line 490 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_GENERIC_TYPE_DECL");
#line 490 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_IDENTIFIER:
				{
#line 491 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_IDENTIFIER");
#line 491 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_IF_STMT:
				{
#line 492 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_IF_STMT");
#line 492 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_MEMBER_ENUM_DECL:
				{
#line 493 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_MEMBER_ENUM_DECL");
#line 493 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_MEMBER_FUNCTION_DECL:
				{
#line 494 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_MEMBER_FUNCTION_DECL");
#line 494 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_MEMBER_VAR_DECL:
				{
#line 495 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_MEMBER_VAR_DECL");
#line 495 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_NEW_EXP:
				{
#line 496 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_NEW_EXP");
#line 496 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_NUMBER:
				{
#line 497 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_NUMBER");
#line 497 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_OPERATOR_EXPR:
				{
#line 498 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_OPERATOR_EXPR");
#line 498 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_OWN_EXP:
				{
#line 499 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_OWN_EXP");
#line 499 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_PARAM_CALL:
				{
#line 500 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_PARAM_CALL");
#line 500 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_PARAM_DECL:
				{
#line 501 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_PARAM_DECL");
#line 501 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_PAREN:
				{
#line 502 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_PAREN");
#line 502 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_REF_EXPR:
				{
#line 503 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_REF_EXPR");
#line 503 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_RETURN_STMT:
				{
#line 504 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_RETURN_STMT");
#line 504 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_SCOPE:
				{
#line 505 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_SCOPE");
#line 505 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_STATIC_ARRAY:
				{
#line 506 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_STATIC_ARRAY");
#line 506 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_STRING:
				{
#line 507 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_STRING");
#line 507 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_SWITCH_STMT:
				{
#line 508 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_SWITCH_STMT");
#line 508 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_TOR_DECL:
				{
#line 509 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_TOR_DECL");
#line 509 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_TRANSLATION_UNIT:
				{
#line 510 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_TRANSLATION_UNIT");
#line 510 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_TTHASH_EXP:
				{
#line 511 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_TTHASH_EXP");
#line 511 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_TYPE_REF:
				{
#line 512 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_TYPE_REF");
#line 512 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_UNARY:
				{
#line 513 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_UNARY");
#line 513 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_VAR_DECL_DESCOPE:
				{
#line 514 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_VAR_DECL_DESCOPE");
#line 514 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_VAR_DECL:
				{
#line 515 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_VAR_DECL");
#line 515 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_WHILE_STMT:
				{
#line 516 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_WHILE_STMT");
#line 516 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.AST_PROJECT:
				{
#line 517 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("AST_PROJECT");
#line 517 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.BASE_EXPR:
				{
#line 518 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("BASE_EXPR");
#line 518 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.DELEGATE_DECL:
				{
#line 519 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("DELEGATE_DECL");
#line 519 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.ENUM_DECL_VALUE:
				{
#line 520 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("ENUM_DECL_VALUE");
#line 520 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.MEMBER_VARS_SET_DEFAULT_STMT:
				{
#line 521 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("MEMBER_VARS_SET_DEFAULT_STMT");
#line 521 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.NAMESPACE_DECL:
				{
#line 522 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("NAMESPACE_DECL");
#line 522 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.NULL_EXPR:
				{
#line 523 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("NULL_EXPR");
#line 523 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

				case Type.THIS_EXPR:
				{
#line 524 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					sOut.Append("THIS_EXPR");
#line 524 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return;
				}

			}
#line 527 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			sOut.Append("???");
		}

	}
}

