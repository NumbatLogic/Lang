#line 1 "../../../Source/Core/Validator.nll"
namespace NumbatLogic
{
	class ValidatorError
	{
		public InternalString m_sError;
		public InternalString m_sFile;
		public int m_nLine;
		public int m_nColumn;
#line 3 "../../../Source/Core/Validator.nll"
		public ValidatorError()
		{
		}

#line 3 "../../../Source/Core/Validator.nll"
		~ValidatorError()
		{
		}

	}
#line 11 "../../../Source/Core/Validator.nll"
	class ValidatorScope
	{
		public Scope m_pScope;
		public Vector<VarDecl> m_pVarDeclVector;
#line 16 "../../../Source/Core/Validator.nll"
		public ValidatorScope(Scope pScope)
		{
			m_pScope = pScope;
			m_pVarDeclVector = new Vector<VarDecl>();
		}

#line 11 "../../../Source/Core/Validator.nll"
		~ValidatorScope()
		{
		}

	}
#line 23 "../../../Source/Core/Validator.nll"
	class Validator
	{
		protected Project m_pProject;
		protected OwnedVector<ValidatorError> m_pValidatorErrorVector;
		protected OwnedVector<ValidatorScope> m_pValidatorScopeVector;
#line 29 "../../../Source/Core/Validator.nll"
		public NamespaceNode m_pCurrentNamespaceNode;
#line 32 "../../../Source/Core/Validator.nll"
		public Resolver m_pResolver;
#line 34 "../../../Source/Core/Validator.nll"
		public Validator(Project pProject)
		{
			m_pProject = pProject;
			m_pValidatorErrorVector = new OwnedVector<ValidatorError>();
			m_pValidatorScopeVector = new OwnedVector<ValidatorScope>();
			m_pCurrentNamespaceNode = pProject.m_pRootNamespaceNode;
#line 41 "../../../Source/Core/Validator.nll"
			m_pResolver = new Resolver();
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
#line 64 "../../../Source/Core/Validator.nll"
			for (int i = 0; i < m_pProject.m_pTranslationUnitVector.GetSize(); i++)
			{
				TranslationUnit pTranslationUnit = m_pProject.m_pTranslationUnitVector.Get(i);
				PreparseNamespaces(m_pProject.m_pRootNamespaceNode, pTranslationUnit);
			}
#line 71 "../../../Source/Core/Validator.nll"
			for (int i = 0; i < m_pProject.m_pTranslationUnitVector.GetSize(); i++)
			{
				TranslationUnit pTranslationUnit = m_pProject.m_pTranslationUnitVector.Get(i);
				m_pResolver.BuildForRoot(pTranslationUnit);
			}
#line 77 "../../../Source/Core/Validator.nll"
			for (int i = 0; i < m_pProject.m_pTranslationUnitVector.GetSize(); i++)
			{
				TranslationUnit pTranslationUnit = m_pProject.m_pTranslationUnitVector.Get(i);
				pTranslationUnit.PreValidate(this, null);
			}
#line 83 "../../../Source/Core/Validator.nll"
			for (int i = 0; i < m_pProject.m_pTranslationUnitVector.GetSize(); i++)
			{
				TranslationUnit pTranslationUnit = m_pProject.m_pTranslationUnitVector.Get(i);
				pTranslationUnit.Validate(this, null);
			}
#line 89 "../../../Source/Core/Validator.nll"
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
#line 102 "../../../Source/Core/Validator.nll"
			if (m_pValidatorErrorVector.GetSize() > 0)
			{
				sTemp.Set("");
				sTemp.AppendInt(m_pValidatorErrorVector.GetSize());
				sTemp.Append(" errors");
				Console.Log(sTemp.GetExternalString());
			}
#line 110 "../../../Source/Core/Validator.nll"
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
			NumbatLogic.ValidatorError __3001553964 = pValidatorError;
#line 123 "../../../Source/Core/Validator.nll"
			pValidatorError = null;
#line 123 "../../../Source/Core/Validator.nll"
			m_pValidatorErrorVector.PushBack(__3001553964);
		}

#line 127 "../../../Source/Core/Validator.nll"
		public void ValidateSubtree(AST pRoot)
		{
			pRoot.PreValidate(this, null);
			pRoot.Validate(this, null);
		}

		public void BeginScope(Scope pScope)
		{
			ValidatorScope pValidatorScope = new ValidatorScope(pScope);
			NumbatLogic.ValidatorScope __3052106978 = pValidatorScope;
#line 136 "../../../Source/Core/Validator.nll"
			pValidatorScope = null;
#line 136 "../../../Source/Core/Validator.nll"
			m_pValidatorScopeVector.PushBack(__3052106978);
		}

		public void AddVarDecl(VarDecl pVarDecl)
		{
			ValueType pValueType = pVarDecl.m_pTypeRef.CreateValueType(m_pResolver);
			if (pValueType != null)
				if (pValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE && pValueType.m_ePointerType == TypeRef.PointerType.OWNED)
				{
					int nIndex = m_pValidatorScopeVector.GetSize() - 1;
					Assert.Plz(nIndex >= 0);
#line 148 "../../../Source/Core/Validator.nll"
					ValidatorScope pValidatorScope = m_pValidatorScopeVector.Get(nIndex);
					pValidatorScope.m_pVarDeclVector.PushBack(pVarDecl);
				}
		}

		public void EndScope(Scope pScope)
		{
			ValidatorScope pValidatorScope = m_pValidatorScopeVector.PopBack();
			Assert.Plz(pValidatorScope != null);
			Assert.Plz(pValidatorScope.m_pScope == pScope);
#line 159 "../../../Source/Core/Validator.nll"
			AST pCheck = pScope;
			while (pCheck != null && pCheck.m_eType == AST.Type.AST_SCOPE)
			{
				pCheck = pCheck.m_pLastChild;
			}
			if (pCheck != null)
				if (pCheck.m_eType == AST.Type.AST_RETURN_STMT || pCheck.m_eType == AST.Type.AST_CONTINUE_STMT || pCheck.m_eType == AST.Type.AST_BREAK_STMT)
				{
#line 166 "../../../Source/Core/Validator.nll"
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
				NumbatLogic.VarDeclDescope __2691051646 = pVarDeclDescope;
#line 176 "../../../Source/Core/Validator.nll"
				pVarDeclDescope = null;
#line 176 "../../../Source/Core/Validator.nll"
				pScope.AddChild(__2691051646);
			}
		}

		public void InjectCleanup(AST pBreakOrContinueOrReturn)
		{
#line 183 "../../../Source/Core/Validator.nll"
			Identifier pDisownedIdentifier = null;
			if (pBreakOrContinueOrReturn.m_eType == AST.Type.AST_RETURN_STMT)
			{
				ReturnStmt pReturnStmt = (ReturnStmt)(pBreakOrContinueOrReturn);
#line 188 "../../../Source/Core/Validator.nll"
				if (pReturnStmt.m_pExpression != null && pReturnStmt.m_pExpression.m_eType == AST.Type.AST_DISOWN_EXP)
				{
					DisownExpr pDisownExpr = (DisownExpr)(pReturnStmt.m_pExpression);
					if (pDisownExpr.m_pExpression.m_eType == AST.Type.AST_IDENTIFIER)
					{
						pDisownedIdentifier = (Identifier)(pDisownExpr.m_pExpression);
					}
				}
			}
#line 199 "../../../Source/Core/Validator.nll"
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
#line 214 "../../../Source/Core/Validator.nll"
				if (pBreakOrContinueOrReturn.m_eType == AST.Type.AST_RETURN_STMT)
				{
					if (pValidatorScope.m_pScope.m_pParent.m_eType == AST.Type.AST_FUNCTION_DECL)
						break;
				}
				else
				{
					if (pValidatorScope.m_pScope.m_pParent.m_eType == AST.Type.AST_FOR_STMT || pValidatorScope.m_pScope.m_pParent.m_eType == AST.Type.AST_WHILE_STMT || pValidatorScope.m_pScope.m_pParent.m_eType == AST.Type.AST_SWITCH_STMT)
#line 224 "../../../Source/Core/Validator.nll"
						break;
				}
			}
#line 228 "../../../Source/Core/Validator.nll"
			if (pVarDeclDescope.m_pVarDeclVector.GetSize() > 0)
			{
				AST pParent = pBreakOrContinueOrReturn.m_pParent;
				NumbatLogic.VarDeclDescope __2699050750 = pVarDeclDescope;
#line 231 "../../../Source/Core/Validator.nll"
				pVarDeclDescope = null;
#line 231 "../../../Source/Core/Validator.nll"
				pParent.AddChildBefore(__2699050750, pBreakOrContinueOrReturn);
			}
		}

#line 239 "../../../Source/Core/Validator.nll"
		public void BeginNamespace(string sxName)
		{
			m_pCurrentNamespaceNode = m_pCurrentNamespaceNode.GetChild(sxName);
			Assert.Plz(m_pCurrentNamespaceNode != null);
		}

		public void EndNamespace(string sxName)
		{
			Assert.Plz(m_pCurrentNamespaceNode.m_sName.IsEqual(sxName));
			Assert.Plz(m_pCurrentNamespaceNode.m_pParent != null);
			m_pCurrentNamespaceNode = m_pCurrentNamespaceNode.m_pParent;
		}

#line 23 "../../../Source/Core/Validator.nll"
		~Validator()
		{
		}

	}
}

