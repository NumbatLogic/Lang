namespace NumbatLogic
{
	class Project : AST
	{
		public Vector<TranslationUnit> m_pTranslationUnitVector;
		public NamespaceNode m_pRootNamespaceNode;
		public Project()
		{
			m_bCanDescend = true;
			m_pTranslationUnitVector = new Vector<TranslationUnit>();
			m_pRootNamespaceNode = new NamespaceNode(null, null);
		}

		public void AddFile(string sFile, OwnedVector<InternalString> sDefineVector)
		{
			for (int i = 0; i < m_pTranslationUnitVector.GetSize(); i++)
			{
				TranslationUnit pTestTranslationUnit = m_pTranslationUnitVector.Get(i);
				if (pTestTranslationUnit.m_sInFile.IsEqual(sFile))
				{
					return;
				}
			}
			TranslationUnit pTranslationUnit = TranslationUnit.Create(sFile, sDefineVector);
			if (pTranslationUnit == null)
			{
				Console.Log("unable to parse file");
				Console.Log(sFile);
				NumbatLogic.Assert.Plz(false);
				return;
			}
			m_pTranslationUnitVector.PushBack(pTranslationUnit);
			NumbatLogic.TranslationUnit __517218260 = pTranslationUnit;
			pTranslationUnit = null;
			AddChild(__517218260);
		}

		public void AddDirectory(string sDirectory, OwnedVector<InternalString> sDefineVector)
		{
			OwnedVector<InternalString> sFileVector = File.GetRecursiveFileVector(sDirectory);
			while (sFileVector.GetSize() > 0)
			{
				InternalString sFile = sFileVector.PopBack();
				AddFile(sFile.GetExternalString(), sDefineVector);
			}
		}

		public void FullValidate()
		{
			for (int i = 0; i < m_pTranslationUnitVector.GetSize(); i++)
			{
				TranslationUnit pTranslationUnit = m_pTranslationUnitVector.Get(i);
				if (pTranslationUnit.m_sInFile.EndsWith(".nll"))
				{
					pTranslationUnit.m_sInFile.Replace("../LangShared", "../LangShared/Transpiled");
					if (pTranslationUnit.m_sInFile.StartsWith("Shared"))
						pTranslationUnit.m_sInFile.Replace("Shared", "Source/Shared");
					else
						pTranslationUnit.m_sInFile.Replace("/Shared", "/Source/Shared");
				}
			}
			Validator pValidator = new Validator(this);
			if (!pValidator.Validate())
			{
			}
		}

		protected void RecurseNamespaces(AST pInAst, NamespaceDecl pSecretNamespace, TranslationUnit pSecretTranslationUnit)
		{
			if (pInAst.m_eType == AST.Type.AST_TRANSLATION_UNIT)
			{
				NumbatLogic.Assert.Plz(pSecretNamespace == null);
			}
			AST pChild = pInAst.m_pFirstChild;
			while (pChild != null)
			{
				if (pChild.m_eType == AST.Type.NAMESPACE_DECL)
				{
					NamespaceDecl pNamespaceDecl = (NamespaceDecl)(pChild);
					if (pNamespaceDecl.m_pNameToken.m_sValue.IsEqual("Secret"))
					{
						AST pNextChild = pChild;
						pNextChild = pChild.m_pNextSibling;
						AST pOwnedChild;
						pOwnedChild = pInAst.RemoveChild(pChild);
						NumbatLogic.Assert.Plz(pOwnedChild != null);
						if (pSecretNamespace == null)
						{
							NumbatLogic.AST __1730038664 = pOwnedChild;
							pOwnedChild = null;
							pSecretTranslationUnit.AddChild(__1730038664);
						}
						else
						{
							NumbatLogic.AST __1730038680 = pOwnedChild;
							pOwnedChild = null;
							pSecretNamespace.AddChild(__1730038680);
						}
						pChild = pNextChild;
						continue;
					}
					NamespaceDecl pNextSecretNamespace = new NamespaceDecl();
					pNextSecretNamespace.m_pFirstToken = pNamespaceDecl.m_pFirstToken;
					pNextSecretNamespace.m_pNameToken = pNamespaceDecl.m_pNameToken;
					pNextSecretNamespace.m_bSkipOutput = pNamespaceDecl.m_bSkipOutput;
					NamespaceDecl pTemp = pNextSecretNamespace;
					if (pSecretNamespace == null)
					{
						NumbatLogic.NamespaceDecl __1366095528 = pNextSecretNamespace;
						pNextSecretNamespace = null;
						pSecretTranslationUnit.AddChild(__1366095528);
					}
					else
					{
						NumbatLogic.NamespaceDecl __1366095544 = pNextSecretNamespace;
						pNextSecretNamespace = null;
						pSecretNamespace.AddChild(__1366095544);
					}
					RecurseNamespaces(pNamespaceDecl, pTemp, pSecretTranslationUnit);
				}
				pChild = pChild.m_pNextSibling;
			}
		}

		protected void NamespaceMerge(AST pParentAST)
		{
			AST pChild = pParentAST.m_pFirstChild;
			Vector<NamespaceDecl> pPreviousNamespaceDecls = new Vector<NamespaceDecl>();
			while (pChild != null)
			{
				if (pChild.m_eType == AST.Type.NAMESPACE_DECL)
				{
					NamespaceDecl pNamespaceDecl = (NamespaceDecl)(pChild);
					string sxName = pNamespaceDecl.m_pNameToken.m_sValue.GetExternalString();
					int i = 0;
					for (i = 0; i < pPreviousNamespaceDecls.GetSize(); i++)
					{
						NamespaceDecl pPreviousNamespace = pPreviousNamespaceDecls.Get(i);
						if (pPreviousNamespace.m_pNameToken.m_sValue.IsEqual(sxName) && pPreviousNamespace.m_bSkipOutput == pNamespaceDecl.m_bSkipOutput)
						{
							AST pNextSibling = pChild.m_pNextSibling;
							AST pOwnedChild;
							pOwnedChild = pParentAST.RemoveChild(pChild);
							AST pSubChild;
							NumbatLogic.AST __2872986608 = pOwnedChild.m_pFirstChild;
							pOwnedChild.m_pFirstChild = null;
							pSubChild = __2872986608;
							pOwnedChild.m_pLastChild = null;
							if (pSubChild != null)
							{
								pSubChild.m_pParent = pPreviousNamespace;
								if (pPreviousNamespace.m_pFirstChild == null)
								{
									NumbatLogic.AST __1095126008 = pSubChild;
									pSubChild = null;
									pPreviousNamespace.m_pFirstChild = __1095126008;
									pPreviousNamespace.m_pLastChild = pPreviousNamespace.m_pFirstChild;
								}
								else
								{
									NumbatLogic.AST __1095126004 = pSubChild;
									pSubChild = null;
									pPreviousNamespace.m_pLastChild.m_pNextSibling = __1095126004;
									pPreviousNamespace.m_pLastChild.m_pNextSibling.m_pPrevSibling = pPreviousNamespace.m_pLastChild;
								}
								while (pPreviousNamespace.m_pLastChild.m_pNextSibling != null)
								{
									pPreviousNamespace.m_pLastChild = pPreviousNamespace.m_pLastChild.m_pNextSibling;
									pPreviousNamespace.m_pLastChild.m_pParent = pPreviousNamespace;
								}
							}
							pChild = pNextSibling;
							break;
						}
					}
					if (i == pPreviousNamespaceDecls.GetSize())
					{
						pPreviousNamespaceDecls.PushBack(pNamespaceDecl);
					}
					else
					{
						continue;
					}
				}
				pChild = pChild.m_pNextSibling;
			}
			{
				for (int i = 0; i < pPreviousNamespaceDecls.GetSize(); i++)
				{
					NamespaceDecl pPreviousNamespace = pPreviousNamespaceDecls.Get(i);
					NamespaceMerge(pPreviousNamespace);
				}
			}
		}

		public void Amalgamate(string sAmalgamateFileName)
		{
			InternalString sSecretFileName = new InternalString(sAmalgamateFileName);
			sSecretFileName.Replace(".nll", "Secret.nll");
			TranslationUnit pSecretTranslationUnit = new TranslationUnit(sSecretFileName.GetExternalString());
			TranslationUnit pPublicTranslationUnit = new TranslationUnit(sAmalgamateFileName);
			while (m_pFirstChild != null)
			{
				AST pAST;
				pAST = RemoveChild(m_pFirstChild);
				TranslationUnit pTranslationUnit = (TranslationUnit)(pAST);
				bool bSkipOutput = pTranslationUnit.m_sInFile.EndsWith(".nll.def");
				while (pTranslationUnit.m_pTokenContainer.m_pTokenVector.GetSize() > 0)
				{
					Token pToken = pTranslationUnit.m_pTokenContainer.m_pTokenVector.PopFront();
					pToken.m_sFileName = pPublicTranslationUnit.m_sInFile;
					NumbatLogic.Token __84182384 = pToken;
					pToken = null;
					pPublicTranslationUnit.m_pTokenContainer.m_pTokenVector.PushBack(__84182384);
				}
				if (pPublicTranslationUnit.m_pFirstChild == null)
				{
					NumbatLogic.AST __2872986468 = pAST.m_pFirstChild;
					pAST.m_pFirstChild = null;
					pPublicTranslationUnit.m_pFirstChild = __2872986468;
					pPublicTranslationUnit.m_pLastChild = pPublicTranslationUnit.m_pFirstChild;
				}
				else
				{
					NumbatLogic.AST __2872986368 = pAST.m_pFirstChild;
					pAST.m_pFirstChild = null;
					pPublicTranslationUnit.m_pLastChild.m_pNextSibling = __2872986368;
					pPublicTranslationUnit.m_pLastChild = pPublicTranslationUnit.m_pLastChild.m_pNextSibling;
				}
				while (true)
				{
					pPublicTranslationUnit.m_pLastChild.m_pParent = pPublicTranslationUnit;
					pPublicTranslationUnit.m_pLastChild.m_bSkipOutput = bSkipOutput;
					if (pPublicTranslationUnit.m_pLastChild.m_pNextSibling == null)
						break;
					pPublicTranslationUnit.m_pLastChild = pPublicTranslationUnit.m_pLastChild.m_pNextSibling;
				}
			}
			while (m_pTranslationUnitVector.GetSize() > 0)
			{
				m_pTranslationUnitVector.PopBack();
			}
			NamespaceMerge(pPublicTranslationUnit);
			RecurseNamespaces(pPublicTranslationUnit, null, pSecretTranslationUnit);
			m_pTranslationUnitVector.PushBack(pSecretTranslationUnit);
			NumbatLogic.TranslationUnit __2068873020 = pSecretTranslationUnit;
			pSecretTranslationUnit = null;
			AddChild(__2068873020);
			m_pTranslationUnitVector.PushBack(pPublicTranslationUnit);
			NumbatLogic.TranslationUnit __2068873008 = pPublicTranslationUnit;
			pPublicTranslationUnit = null;
			AddChild(__2068873008);
		}

		public void Output(AST.Language eLanguage, OutputFile eOutputFile)
		{
			InternalString sOutFile = new InternalString("");
			InternalString sOut = new InternalString("");
			for (int i = 0; i < m_pTranslationUnitVector.GetSize(); i++)
			{
				TranslationUnit pTranslationUnit = m_pTranslationUnitVector.Get(i);
				sOutFile.Set(pTranslationUnit.m_sInFile.GetExternalString());
				if (sOutFile.EndsWith(".nll"))
				{
					TranslationUnit.ConvertFilePath(eLanguage, eOutputFile, sOutFile);
					string sxOutFile = sOutFile.GetExternalString();
					sOut.Set("");
					pTranslationUnit.Stringify(eLanguage, eOutputFile, 0, sOut);
					InternalString sDirectory = File.GetFileDirectory(sxOutFile);
					File.CreateDirectory(sDirectory.GetExternalString());
					InternalString sTestFile = File.GetContents(sxOutFile);
					if (sTestFile == null || !sOut.IsEqual(sTestFile.GetExternalString()))
					{
						File.PutContents(sxOutFile, sOut.GetExternalString());
					}
				}
			}
		}

		~Project()
		{
		}

	}
}

