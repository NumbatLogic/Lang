namespace NumbatLogic
{
	class Identifier : AST
	{
		public Token m_pNameToken;
		public static Identifier TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token pToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_IDENTIFIER);
			if (pToken == null)
			{
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			Identifier pIdentifier = new Identifier();
			pIdentifier.m_eType = AST.Type.AST_IDENTIFIER;
			pIdentifier.m_pNameToken = pToken;
			pIdentifier.m_pFirstToken = pToken;
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.Identifier __1754534835 = pIdentifier;
			pIdentifier = null;
			return __1754534835;
		}

		public override AST BaseClone()
		{
			Identifier pIdentifier = new Identifier();
			pIdentifier.m_eType = m_eType;
			pIdentifier.m_pNameToken = m_pNameToken;
			pIdentifier.m_pFirstToken = m_pFirstToken;
			NumbatLogic.Identifier __2459187919 = pIdentifier;
			pIdentifier = null;
			return __2459187919;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			string sName = m_pNameToken.GetString();
			AST pAST = null;
			AST pBase = this;
			AST pChild = this;
			if (pParent != null)
			{
				if (pParent.m_pOperatorToken.m_eType == Token.Type.TOKEN_DOT && pParent.m_pLeft.m_pValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE)
				{
					AddClassDeclReference(pParent.m_pLeft.m_pValueType.m_pClassDecl, AST.OutputFile.SOURCE, false);
					pBase = pParent.m_pLeft.m_pValueType.m_pClassDecl;
					pChild = null;
				}
				else
					if (pParent.m_pOperatorToken.m_eType == Token.Type.TOKEN_DOUBLE_COLON)
					{
						if (pParent.m_pLeft.m_pValueType.m_eType == ValueType.Type.CLASS_DECL)
						{
							AddClassDeclReference(pParent.m_pLeft.m_pValueType.m_pClassDecl, AST.OutputFile.SOURCE, false);
							pBase = pParent.m_pLeft.m_pValueType.m_pClassDecl;
							pChild = null;
						}
						else
							if (pParent.m_pLeft.m_pValueType.m_eType == ValueType.Type.ENUM_DECL)
							{
								pBase = pParent.m_pLeft.m_pValueType.m_pEnumDecl;
								pChild = null;
							}
							else
								if (pParent.m_pLeft.m_pValueType.m_eType == ValueType.Type.NAMESPACE_NODE)
								{
									Vector<NamespaceDecl> pNamespaceDeclVector = pParent.m_pLeft.m_pValueType.m_pNamespaceNode.m_pNamespaceDeclVector;
									for (int i = 0; i < pNamespaceDeclVector.GetSize(); i++)
									{
										NamespaceDecl pNamespaceDecl = pNamespaceDeclVector.Get(i);
										pAST = pNamespaceDecl.FindByName(sName, null);
										if (pAST != null)
											break;
									}
								}
								else
								{
									pValidator.AddError("Unexpected left of ::", m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
									return;
								}
					}
			}
			if (pAST == null)
				pAST = pBase.FindByName(sName, pChild);
			if (pAST == null)
			{
				InternalString sTemp = new InternalString("Identifier Unbeknownst! ");
				sTemp.Append(sName);
				if (pParent != null)
					sTemp.Append(" has parent");
				sTemp.Append(" base: ");
				pBase.StringifyType(sTemp);
				pValidator.AddError(sTemp.GetExternalString(), m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
				return;
			}
			if (pAST.m_eType == AST.Type.AST_CLASS_DECL)
			{
				m_pValueType = new ValueType(ValueType.Type.CLASS_DECL);
				m_pValueType.m_pClassDecl = (ClassDecl)(pAST);
				AddClassDeclReference(m_pValueType.m_pClassDecl, AST.OutputFile.SOURCE, false);
				AST pCheckParent = m_pParent;
				AST pCurrent = this;
				for (int i = 0; i < 5; i++)
				{
					if (pCheckParent == null)
						break;
					if (pCheckParent.m_eType == AST.Type.AST_VAR_DECL)
					{
						VarDecl pVarDecl = (VarDecl)(pCheckParent);
						bool bInArraySize = false;
						if (pVarDecl.m_pArraySizeVector != null)
						{
							for (int j = 0; j < pVarDecl.m_pArraySizeVector.GetSize(); j++)
							{
								if (pCurrent == pVarDecl.m_pArraySizeVector.Get(j))
								{
									bInArraySize = true;
									break;
								}
							}
						}
						if (bInArraySize && pVarDecl.m_pParent != null && pVarDecl.m_pParent.m_eType == AST.Type.AST_MEMBER_VAR_DECL)
							AddClassDeclReference(m_pValueType.m_pClassDecl, AST.OutputFile.HEADER, false);
						if (pCurrent == pVarDecl.m_pAssignment && pVarDecl.m_pParent != null && pVarDecl.m_pParent.m_eType == AST.Type.AST_MEMBER_VAR_DECL)
						{
							MemberVarDecl pMemberVarDecl = (MemberVarDecl)(pVarDecl.m_pParent);
							if (pMemberVarDecl.m_bStatic)
								AddClassDeclReference(m_pValueType.m_pClassDecl, AST.OutputFile.HEADER, false);
						}
						break;
					}
					pCurrent = pCheckParent;
					pCheckParent = pCheckParent.m_pParent;
				}
				return;
			}
			if (pAST.m_eType == AST.Type.AST_ENUM_DECL)
			{
				m_pValueType = new ValueType(ValueType.Type.ENUM_DECL);
				m_pValueType.m_pEnumDecl = (EnumDecl)(pAST);
				return;
			}
			if (pAST.m_eType == AST.Type.ENUM_DECL_VALUE)
			{
				m_pValueType = new ValueType(ValueType.Type.ENUM_DECL_VALUE);
				m_pValueType.m_pEnumDeclValue = (EnumDeclValue)(pAST);
				return;
			}
			if (pAST.m_eType == AST.Type.AST_VAR_DECL)
			{
				VarDecl pVarDecl = (VarDecl)(pAST);
				m_pValueType = pVarDecl.m_pTypeRef.CreateValueType();
				if (m_pValueType == null)
				{
					pValidator.AddError("Could not create ValueType for VarDecl", m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
					return;
				}
				if (m_pValueType.m_eType == ValueType.Type.GENERIC_TYPE_DECL_VALUE)
				{
					if (pParent != null)
					{
						if (pParent.m_pOperatorToken.m_eType == Token.Type.TOKEN_DOT && pParent.m_pLeft.m_pValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE)
						{
							if (pParent.m_pLeft.m_pValueType.m_pGenericValueTypeVector != null)
							{
								if (pParent.m_pLeft.m_pValueType.m_pGenericValueTypeVector.GetSize() > 0)
								{
									ValueType pGenericValueType = pParent.m_pLeft.m_pValueType.m_pGenericValueTypeVector.Get(0);
									if (pGenericValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE)
									{
										ValueType pOldValueType;
										NumbatLogic.ValueType __470108787 = m_pValueType;
										m_pValueType = null;
										pOldValueType = __470108787;
										m_pValueType = pGenericValueType.Clone();
										m_pValueType.m_ePointerType = pOldValueType.m_ePointerType;
									}
								}
							}
						}
					}
				}
				return;
			}
			if (pAST.m_eType == AST.Type.AST_FUNCTION_DECL)
			{
				m_pValueType = new ValueType(ValueType.Type.FUNCTION_DECL);
				m_pValueType.m_pFunctionDecl = (FunctionDecl)(pAST);
				return;
			}
			if (pAST.m_eType == AST.Type.NAMESPACE_DECL)
			{
				m_pValueType = new ValueType(ValueType.Type.NAMESPACE_NODE);
				m_pValueType.m_pNamespaceNode = ((NamespaceDecl)(pAST)).m_pNamespaceNode;
				return;
			}
			{
				InternalString sTemp = new InternalString("say what? ");
				pAST.StringifyType(sTemp);
				pValidator.AddError(sTemp.GetExternalString(), m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
			}
			base.Validate(pValidator, pParent);
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			m_pNameToken.Stringify(sOut);
		}

		public Identifier()
		{
		}

	}
}

