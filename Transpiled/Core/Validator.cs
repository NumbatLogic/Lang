#line 1 "../../../Source/Core/Validator.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/Validator.nll"
	class ValidatorError
	{
#line 5 "../../../Source/Core/Validator.nll"
		public InternalString m_sError;
#line 6 "../../../Source/Core/Validator.nll"
		public InternalString m_sFile;
#line 7 "../../../Source/Core/Validator.nll"
		public int m_nLine;
#line 8 "../../../Source/Core/Validator.nll"
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
#line 13 "../../../Source/Core/Validator.nll"
		public Scope m_pScope;
#line 14 "../../../Source/Core/Validator.nll"
		public Vector<VarDecl> m_pVarDeclVector;
#line 16 "../../../Source/Core/Validator.nll"
		public ValidatorScope(Scope pScope)
		{
#line 18 "../../../Source/Core/Validator.nll"
			m_pScope = pScope;
#line 19 "../../../Source/Core/Validator.nll"
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
#line 25 "../../../Source/Core/Validator.nll"
		protected Project m_pProject;
#line 26 "../../../Source/Core/Validator.nll"
		protected OwnedVector<ValidatorError> m_pValidatorErrorVector;
#line 27 "../../../Source/Core/Validator.nll"
		protected OwnedVector<ValidatorScope> m_pValidatorScopeVector;
#line 29 "../../../Source/Core/Validator.nll"
		public NamespaceNode m_pCurrentNamespaceNode;
#line 32 "../../../Source/Core/Validator.nll"
		public Resolver m_pResolver;
#line 34 "../../../Source/Core/Validator.nll"
		public Validator(Project pProject)
		{
#line 36 "../../../Source/Core/Validator.nll"
			m_pProject = pProject;
#line 37 "../../../Source/Core/Validator.nll"
			m_pValidatorErrorVector = new OwnedVector<ValidatorError>();
#line 38 "../../../Source/Core/Validator.nll"
			m_pValidatorScopeVector = new OwnedVector<ValidatorScope>();
#line 39 "../../../Source/Core/Validator.nll"
			m_pCurrentNamespaceNode = pProject.m_pRootNamespaceNode;
#line 41 "../../../Source/Core/Validator.nll"
			m_pResolver = new Resolver();
		}

#line 44 "../../../Source/Core/Validator.nll"
		protected void PreparseNamespaces(NamespaceNode pCurrentNode, AST pAST)
		{
#line 46 "../../../Source/Core/Validator.nll"
			AST pChild = pAST.m_pFirstChild;
#line 47 "../../../Source/Core/Validator.nll"
			while (pChild != null)
			{
#line 49 "../../../Source/Core/Validator.nll"
				if (pChild.m_eType == AST.Type.NAMESPACE_DECL)
				{
#line 51 "../../../Source/Core/Validator.nll"
					NamespaceDecl pNamespaceDecl = (NamespaceDecl)(pChild);
#line 52 "../../../Source/Core/Validator.nll"
					NamespaceNode pNextNamespaceNode = pCurrentNode.GetOrCreateChild(pNamespaceDecl);
#line 53 "../../../Source/Core/Validator.nll"
					PreparseNamespaces(pNextNamespaceNode, pChild);
				}
#line 55 "../../../Source/Core/Validator.nll"
				pChild = pChild.m_pNextSibling;
			}
		}

#line 59 "../../../Source/Core/Validator.nll"
		public bool Validate()
		{
#line 61 "../../../Source/Core/Validator.nll"
			InternalString sTemp = new InternalString("");
#line 64 "../../../Source/Core/Validator.nll"
			for (int i = 0; i < m_pProject.m_pTranslationUnitVector.GetSize(); i++)
			{
#line 66 "../../../Source/Core/Validator.nll"
				TranslationUnit pTranslationUnit = m_pProject.m_pTranslationUnitVector.Get(i);
#line 67 "../../../Source/Core/Validator.nll"
				PreparseNamespaces(m_pProject.m_pRootNamespaceNode, pTranslationUnit);
			}
#line 71 "../../../Source/Core/Validator.nll"
			for (int i = 0; i < m_pProject.m_pTranslationUnitVector.GetSize(); i++)
			{
#line 73 "../../../Source/Core/Validator.nll"
				TranslationUnit pTranslationUnit = m_pProject.m_pTranslationUnitVector.Get(i);
#line 74 "../../../Source/Core/Validator.nll"
				m_pResolver.BuildForRoot(pTranslationUnit);
			}
#line 77 "../../../Source/Core/Validator.nll"
			for (int i = 0; i < m_pProject.m_pTranslationUnitVector.GetSize(); i++)
			{
#line 79 "../../../Source/Core/Validator.nll"
				TranslationUnit pTranslationUnit = m_pProject.m_pTranslationUnitVector.Get(i);
#line 80 "../../../Source/Core/Validator.nll"
				pTranslationUnit.PreValidate(this, null);
			}
#line 83 "../../../Source/Core/Validator.nll"
			for (int i = 0; i < m_pProject.m_pTranslationUnitVector.GetSize(); i++)
			{
#line 85 "../../../Source/Core/Validator.nll"
				TranslationUnit pTranslationUnit = m_pProject.m_pTranslationUnitVector.Get(i);
#line 86 "../../../Source/Core/Validator.nll"
				pTranslationUnit.Validate(this, null);
			}
#line 89 "../../../Source/Core/Validator.nll"
			for (int i = 0; i < m_pValidatorErrorVector.GetSize(); i++)
			{
#line 91 "../../../Source/Core/Validator.nll"
				ValidatorError pValidatorError = m_pValidatorErrorVector.Get(i);
#line 92 "../../../Source/Core/Validator.nll"
				sTemp.Set(pValidatorError.m_sFile.GetExternalString());
#line 93 "../../../Source/Core/Validator.nll"
				sTemp.Append(":");
#line 94 "../../../Source/Core/Validator.nll"
				sTemp.AppendInt(pValidatorError.m_nLine);
#line 95 "../../../Source/Core/Validator.nll"
				sTemp.Append(":");
#line 96 "../../../Source/Core/Validator.nll"
				sTemp.AppendInt(pValidatorError.m_nColumn);
#line 97 "../../../Source/Core/Validator.nll"
				sTemp.Append(" Error: ");
#line 98 "../../../Source/Core/Validator.nll"
				sTemp.Append(pValidatorError.m_sError.GetExternalString());
#line 99 "../../../Source/Core/Validator.nll"
				Console.Log(sTemp.GetExternalString());
			}
#line 102 "../../../Source/Core/Validator.nll"
			if (m_pValidatorErrorVector.GetSize() > 0)
			{
#line 104 "../../../Source/Core/Validator.nll"
				sTemp.Set("");
#line 105 "../../../Source/Core/Validator.nll"
				sTemp.AppendInt(m_pValidatorErrorVector.GetSize());
#line 106 "../../../Source/Core/Validator.nll"
				sTemp.Append(" errors");
#line 107 "../../../Source/Core/Validator.nll"
				Console.Log(sTemp.GetExternalString());
			}
#line 110 "../../../Source/Core/Validator.nll"
			return m_pValidatorErrorVector.GetSize() == 0;
		}

#line 113 "../../../Source/Core/Validator.nll"
		public void AddError(string sError, InternalString sFile, int nLine, int nColumn)
		{
#line 115 "../../../Source/Core/Validator.nll"
			ValidatorError pValidatorError = new ValidatorError();
#line 116 "../../../Source/Core/Validator.nll"
			pValidatorError.m_sError = new InternalString(sError);
#line 117 "../../../Source/Core/Validator.nll"
			if (sFile == null)
#line 118 "../../../Source/Core/Validator.nll"
				pValidatorError.m_sFile = new InternalString("-- no file --");
			else
#line 120 "../../../Source/Core/Validator.nll"
				pValidatorError.m_sFile = new InternalString(sFile.GetExternalString());
#line 121 "../../../Source/Core/Validator.nll"
			pValidatorError.m_nLine = nLine;
#line 122 "../../../Source/Core/Validator.nll"
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
#line 129 "../../../Source/Core/Validator.nll"
			pRoot.PreValidate(this, null);
#line 130 "../../../Source/Core/Validator.nll"
			pRoot.Validate(this, null);
		}

#line 133 "../../../Source/Core/Validator.nll"
		public void BeginScope(Scope pScope)
		{
#line 135 "../../../Source/Core/Validator.nll"
			ValidatorScope pValidatorScope = new ValidatorScope(pScope);
			NumbatLogic.ValidatorScope __3052106978 = pValidatorScope;
#line 136 "../../../Source/Core/Validator.nll"
			pValidatorScope = null;
#line 136 "../../../Source/Core/Validator.nll"
			m_pValidatorScopeVector.PushBack(__3052106978);
		}

#line 139 "../../../Source/Core/Validator.nll"
		public void AddVarDecl(VarDecl pVarDecl)
		{
#line 141 "../../../Source/Core/Validator.nll"
			ValueType pValueType = pVarDecl.m_pTypeRef.CreateValueType(m_pResolver);
#line 142 "../../../Source/Core/Validator.nll"
			if (pValueType != null)
#line 143 "../../../Source/Core/Validator.nll"
				if (pValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE && pValueType.m_ePointerType == TypeRef.PointerType.OWNED)
				{
#line 145 "../../../Source/Core/Validator.nll"
					int nIndex = m_pValidatorScopeVector.GetSize() - 1;
#line 146 "../../../Source/Core/Validator.nll"
					Assert.Plz(nIndex >= 0);
#line 148 "../../../Source/Core/Validator.nll"
					ValidatorScope pValidatorScope = m_pValidatorScopeVector.Get(nIndex);
#line 149 "../../../Source/Core/Validator.nll"
					pValidatorScope.m_pVarDeclVector.PushBack(pVarDecl);
				}
		}

#line 153 "../../../Source/Core/Validator.nll"
		public void EndScope(Scope pScope)
		{
#line 155 "../../../Source/Core/Validator.nll"
			ValidatorScope pValidatorScope = m_pValidatorScopeVector.PopBack();
#line 156 "../../../Source/Core/Validator.nll"
			Assert.Plz(pValidatorScope != null);
#line 157 "../../../Source/Core/Validator.nll"
			Assert.Plz(pValidatorScope.m_pScope == pScope);
#line 159 "../../../Source/Core/Validator.nll"
			AST pCheck = pScope;
#line 160 "../../../Source/Core/Validator.nll"
			while (pCheck != null && pCheck.m_eType == AST.Type.AST_SCOPE)
			{
#line 162 "../../../Source/Core/Validator.nll"
				pCheck = pCheck.m_pLastChild;
			}
#line 164 "../../../Source/Core/Validator.nll"
			if (pCheck != null)
#line 165 "../../../Source/Core/Validator.nll"
				if (pCheck.m_eType == AST.Type.AST_RETURN_STMT || pCheck.m_eType == AST.Type.AST_CONTINUE_STMT || pCheck.m_eType == AST.Type.AST_BREAK_STMT)
				{
#line 166 "../../../Source/Core/Validator.nll"
					return;
				}
#line 168 "../../../Source/Core/Validator.nll"
			if (pValidatorScope.m_pVarDeclVector.GetSize() > 0)
			{
#line 170 "../../../Source/Core/Validator.nll"
				VarDeclDescope pVarDeclDescope = new VarDeclDescope();
#line 171 "../../../Source/Core/Validator.nll"
				for (int i = 0; i < pValidatorScope.m_pVarDeclVector.GetSize(); i++)
				{
#line 173 "../../../Source/Core/Validator.nll"
					VarDecl pVarDecl = pValidatorScope.m_pVarDeclVector.Get(i);
#line 174 "../../../Source/Core/Validator.nll"
					pVarDeclDescope.m_pVarDeclVector.PushBack(pVarDecl);
				}
				NumbatLogic.VarDeclDescope __2691051646 = pVarDeclDescope;
#line 176 "../../../Source/Core/Validator.nll"
				pVarDeclDescope = null;
#line 176 "../../../Source/Core/Validator.nll"
				pScope.AddChild(__2691051646);
			}
		}

#line 180 "../../../Source/Core/Validator.nll"
		public void InjectCleanup(AST pBreakOrContinueOrReturn)
		{
#line 183 "../../../Source/Core/Validator.nll"
			Identifier pDisownedIdentifier = null;
#line 184 "../../../Source/Core/Validator.nll"
			if (pBreakOrContinueOrReturn.m_eType == AST.Type.AST_RETURN_STMT)
			{
#line 186 "../../../Source/Core/Validator.nll"
				ReturnStmt pReturnStmt = (ReturnStmt)(pBreakOrContinueOrReturn);
#line 188 "../../../Source/Core/Validator.nll"
				if (pReturnStmt.m_pExpression != null && pReturnStmt.m_pExpression.m_eType == AST.Type.AST_DISOWN_EXP)
				{
#line 190 "../../../Source/Core/Validator.nll"
					DisownExpr pDisownExpr = (DisownExpr)(pReturnStmt.m_pExpression);
#line 191 "../../../Source/Core/Validator.nll"
					if (pDisownExpr.m_pExpression.m_eType == AST.Type.AST_IDENTIFIER)
					{
#line 193 "../../../Source/Core/Validator.nll"
						pDisownedIdentifier = (Identifier)(pDisownExpr.m_pExpression);
					}
				}
			}
#line 199 "../../../Source/Core/Validator.nll"
			VarDeclDescope pVarDeclDescope = new VarDeclDescope();
#line 200 "../../../Source/Core/Validator.nll"
			for (int i = m_pValidatorScopeVector.GetSize() - 1; i >= 0; i--)
			{
#line 202 "../../../Source/Core/Validator.nll"
				ValidatorScope pValidatorScope = m_pValidatorScopeVector.Get(i);
#line 203 "../../../Source/Core/Validator.nll"
				for (int j = 0; j < pValidatorScope.m_pVarDeclVector.GetSize(); j++)
				{
#line 205 "../../../Source/Core/Validator.nll"
					VarDecl pVarDecl = pValidatorScope.m_pVarDeclVector.Get(j);
#line 206 "../../../Source/Core/Validator.nll"
					if (pDisownedIdentifier != null)
					{
#line 208 "../../../Source/Core/Validator.nll"
						if (ExternalString.Equal(pVarDecl.m_pNameToken.GetString(), pDisownedIdentifier.m_pFirstToken.GetString()))
#line 209 "../../../Source/Core/Validator.nll"
							continue;
					}
#line 211 "../../../Source/Core/Validator.nll"
					pVarDeclDescope.m_pVarDeclVector.PushBack(pVarDecl);
				}
#line 214 "../../../Source/Core/Validator.nll"
				if (pBreakOrContinueOrReturn.m_eType == AST.Type.AST_RETURN_STMT)
				{
#line 216 "../../../Source/Core/Validator.nll"
					if (pValidatorScope.m_pScope.m_pParent.m_eType == AST.Type.AST_FUNCTION_DECL)
#line 217 "../../../Source/Core/Validator.nll"
						break;
				}
				else
				{
#line 221 "../../../Source/Core/Validator.nll"
					if (pValidatorScope.m_pScope.m_pParent.m_eType == AST.Type.AST_FOR_STMT || pValidatorScope.m_pScope.m_pParent.m_eType == AST.Type.AST_WHILE_STMT || pValidatorScope.m_pScope.m_pParent.m_eType == AST.Type.AST_SWITCH_STMT)
#line 224 "../../../Source/Core/Validator.nll"
						break;
				}
			}
#line 228 "../../../Source/Core/Validator.nll"
			if (pVarDeclDescope.m_pVarDeclVector.GetSize() > 0)
			{
#line 230 "../../../Source/Core/Validator.nll"
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
#line 241 "../../../Source/Core/Validator.nll"
			m_pCurrentNamespaceNode = m_pCurrentNamespaceNode.GetChild(sxName);
#line 242 "../../../Source/Core/Validator.nll"
			Assert.Plz(m_pCurrentNamespaceNode != null);
		}

#line 245 "../../../Source/Core/Validator.nll"
		public void EndNamespace(string sxName)
		{
#line 247 "../../../Source/Core/Validator.nll"
			Assert.Plz(m_pCurrentNamespaceNode.m_sName.IsEqual(sxName));
#line 248 "../../../Source/Core/Validator.nll"
			Assert.Plz(m_pCurrentNamespaceNode.m_pParent != null);
#line 249 "../../../Source/Core/Validator.nll"
			m_pCurrentNamespaceNode = m_pCurrentNamespaceNode.m_pParent;
		}

#line 23 "../../../Source/Core/Validator.nll"
		~Validator()
		{
		}

	}
}

