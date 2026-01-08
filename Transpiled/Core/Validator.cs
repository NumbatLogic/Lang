namespace NumbatLogic
{
	class ValidatorError
	{
		public InternalString m_sError;
		public InternalString m_sFile;
		public int m_nLine;
		public int m_nColumn;
		public ValidatorError()
		{
		}

		~ValidatorError()
		{
		}

	}
	class ValidatorScope
	{
		public Scope m_pScope;
		public Vector<VarDecl> m_pVarDeclVector;
		public ValidatorScope(Scope pScope)
		{
			m_pScope = pScope;
			m_pVarDeclVector = new Vector<VarDecl>();
		}

		~ValidatorScope()
		{
		}

	}
	class Validator
	{
		protected Project m_pProject;
		protected OwnedVector<ValidatorError> m_pValidatorErrorVector;
		protected OwnedVector<ValidatorScope> m_pValidatorScopeVector;
		public NamespaceNode m_pCurrentNamespaceNode;
		public Validator(Project pProject)
		{
			m_pProject = pProject;
			m_pValidatorErrorVector = new OwnedVector<ValidatorError>();
			m_pValidatorScopeVector = new OwnedVector<ValidatorScope>();
			m_pCurrentNamespaceNode = pProject.m_pRootNamespaceNode;
		}

		protected void PreparseNamespaces(NamespaceNode pCurrentNode, AST pAST)
		{
			AST pChild = pAST.m_pFirstChild;
			while (pChild != null)
			{
				if (pChild.m_eType == AST.Type.NAMESPACE_DECL)
				{
					NamespaceDecl pNamespaceDecl = (NamespaceDecl)(pChild);
					NamespaceNode pNextNamespaceNode = pCurrentNode.GetOrCreateChild(pNamespaceDecl);
					PreparseNamespaces(pNextNamespaceNode, pChild);
				}
				pChild = pChild.m_pNextSibling;
			}
		}

		public bool Validate()
		{
			InternalString sTemp = new InternalString("");
			for (int i = 0; i < m_pProject.m_pTranslationUnitVector.GetSize(); i++)
			{
				TranslationUnit pTranslationUnit = m_pProject.m_pTranslationUnitVector.Get(i);
				PreparseNamespaces(m_pProject.m_pRootNamespaceNode, pTranslationUnit);
			}
			for (int i = 0; i < m_pProject.m_pTranslationUnitVector.GetSize(); i++)
			{
				TranslationUnit pTranslationUnit = m_pProject.m_pTranslationUnitVector.Get(i);
				pTranslationUnit.PreValidate(this, null);
			}
			for (int i = 0; i < m_pProject.m_pTranslationUnitVector.GetSize(); i++)
			{
				TranslationUnit pTranslationUnit = m_pProject.m_pTranslationUnitVector.Get(i);
				pTranslationUnit.Validate(this, null);
			}
			for (int i = 0; i < m_pValidatorErrorVector.GetSize(); i++)
			{
				ValidatorError pValidatorError = m_pValidatorErrorVector.Get(i);
				sTemp.Set(pValidatorError.m_sFile.GetExternalString());
				sTemp.Append(":");
				sTemp.AppendInt(pValidatorError.m_nLine);
				sTemp.Append(":");
				sTemp.AppendInt(pValidatorError.m_nColumn);
				sTemp.Append(" Error: ");
				sTemp.Append(pValidatorError.m_sError.GetExternalString());
				Console.Log(sTemp.GetExternalString());
			}
			if (m_pValidatorErrorVector.GetSize() > 0)
			{
				sTemp.Set("");
				sTemp.AppendInt(m_pValidatorErrorVector.GetSize());
				sTemp.Append(" errors");
				Console.Log(sTemp.GetExternalString());
			}
			return m_pValidatorErrorVector.GetSize() == 0;
		}

		public void AddError(string sError, InternalString sFile, int nLine, int nColumn)
		{
			ValidatorError pValidatorError = new ValidatorError();
			pValidatorError.m_sError = new InternalString(sError);
			if (sFile == null)
				pValidatorError.m_sFile = new InternalString("-- no file --");
			else
				pValidatorError.m_sFile = new InternalString(sFile.GetExternalString());
			pValidatorError.m_nLine = nLine;
			pValidatorError.m_nColumn = nColumn;
			NumbatLogic.ValidatorError __3001488363 = pValidatorError;
			pValidatorError = null;
			m_pValidatorErrorVector.PushBack(__3001488363);
		}

		public void BeginScope(Scope pScope)
		{
			ValidatorScope pValidatorScope = new ValidatorScope(pScope);
			NumbatLogic.ValidatorScope __3051975781 = pValidatorScope;
			pValidatorScope = null;
			m_pValidatorScopeVector.PushBack(__3051975781);
		}

		public void AddVarDecl(VarDecl pVarDecl)
		{
			ValueType pValueType = pVarDecl.m_pTypeRef.CreateValueType();
			if (pValueType != null)
				if (pValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE && pValueType.m_ePointerType == TypeRef.PointerType.OWNED)
				{
					int nIndex = m_pValidatorScopeVector.GetSize() - 1;
					NumbatLogic.Assert.Plz(nIndex >= 0);
					ValidatorScope pValidatorScope = m_pValidatorScopeVector.Get(nIndex);
					pValidatorScope.m_pVarDeclVector.PushBack(pVarDecl);
				}
		}

		public void EndScope(Scope pScope)
		{
			ValidatorScope pValidatorScope = m_pValidatorScopeVector.PopBack();
			NumbatLogic.Assert.Plz(pValidatorScope != null);
			NumbatLogic.Assert.Plz(pValidatorScope.m_pScope == pScope);
			AST pCheck = pScope;
			while (pCheck != null && pCheck.m_eType == AST.Type.AST_SCOPE)
			{
				pCheck = pCheck.m_pLastChild;
			}
			if (pCheck != null)
				if (pCheck.m_eType == AST.Type.AST_RETURN_STMT || pCheck.m_eType == AST.Type.AST_CONTINUE_STMT || pCheck.m_eType == AST.Type.AST_BREAK_STMT)
				{
					return;
				}
			if (pValidatorScope.m_pVarDeclVector.GetSize() > 0)
			{
				VarDeclDescope pVarDeclDescope = new VarDeclDescope();
				for (int i = 0; i < pValidatorScope.m_pVarDeclVector.GetSize(); i++)
				{
					VarDecl pVarDecl = pValidatorScope.m_pVarDeclVector.Get(i);
					pVarDeclDescope.m_pVarDeclVector.PushBack(pVarDecl);
				}
				NumbatLogic.VarDeclDescope __2690920449 = pVarDeclDescope;
				pVarDeclDescope = null;
				pScope.AddChild(__2690920449);
			}
		}

		public void InjectCleanup(AST pBreakOrContinueOrReturn)
		{
			Identifier pDisownedIdentifier = null;
			if (pBreakOrContinueOrReturn.m_eType == AST.Type.AST_RETURN_STMT)
			{
				ReturnStmt pReturnStmt = (ReturnStmt)(pBreakOrContinueOrReturn);
				if (pReturnStmt.m_pExpression != null && pReturnStmt.m_pExpression.m_eType == AST.Type.AST_DISOWN_EXP)
				{
					DisownExpr pDisownExpr = (DisownExpr)(pReturnStmt.m_pExpression);
					if (pDisownExpr.m_pExpression.m_eType == AST.Type.AST_IDENTIFIER)
					{
						pDisownedIdentifier = (Identifier)(pDisownExpr.m_pExpression);
					}
				}
			}
			VarDeclDescope pVarDeclDescope = new VarDeclDescope();
			for (int i = m_pValidatorScopeVector.GetSize() - 1; i >= 0; i--)
			{
				ValidatorScope pValidatorScope = m_pValidatorScopeVector.Get(i);
				for (int j = 0; j < pValidatorScope.m_pVarDeclVector.GetSize(); j++)
				{
					VarDecl pVarDecl = pValidatorScope.m_pVarDeclVector.Get(j);
					if (pDisownedIdentifier != null)
					{
						if (ExternalString.Equal(pVarDecl.m_pNameToken.GetString(), pDisownedIdentifier.m_pFirstToken.GetString()))
							continue;
					}
					pVarDeclDescope.m_pVarDeclVector.PushBack(pVarDecl);
				}
				if (pBreakOrContinueOrReturn.m_eType == AST.Type.AST_RETURN_STMT)
				{
					if (pValidatorScope.m_pScope.m_pParent.m_eType == AST.Type.AST_FUNCTION_DECL)
						break;
				}
				else
				{
					if (pValidatorScope.m_pScope.m_pParent.m_eType == AST.Type.AST_FOR_STMT || pValidatorScope.m_pScope.m_pParent.m_eType == AST.Type.AST_WHILE_STMT || pValidatorScope.m_pScope.m_pParent.m_eType == AST.Type.AST_SWITCH_STMT)
						break;
				}
			}
			if (pVarDeclDescope.m_pVarDeclVector.GetSize() > 0)
			{
				AST pParent = pBreakOrContinueOrReturn.m_pParent;
				NumbatLogic.VarDeclDescope __2698919553 = pVarDeclDescope;
				pVarDeclDescope = null;
				pParent.AddChildBefore(__2698919553, pBreakOrContinueOrReturn);
			}
		}

		public void BeginNamespace(string sxName)
		{
			m_pCurrentNamespaceNode = m_pCurrentNamespaceNode.GetChild(sxName);
			NumbatLogic.Assert.Plz(m_pCurrentNamespaceNode != null);
		}

		public void EndNamespace(string sxName)
		{
			NumbatLogic.Assert.Plz(m_pCurrentNamespaceNode.m_sName.IsEqual(sxName));
			NumbatLogic.Assert.Plz(m_pCurrentNamespaceNode.m_pParent != null);
			m_pCurrentNamespaceNode = m_pCurrentNamespaceNode.m_pParent;
		}

		~Validator()
		{
		}

	}
}

