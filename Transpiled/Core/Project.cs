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
			NumbatLogic.TranslationUnit __2210841974 = pTranslationUnit;
			pTranslationUnit = null;
			AddChild(__2210841974);
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
					pTranslationUnit.m_sInFile.Replace("../LangShared", "Source/LangShared");
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
							NumbatLogic.AST __2966060645 = pOwnedChild;
							pOwnedChild = null;
							pSecretTranslationUnit.AddChild(__2966060645);
						}
						else
						{
							NumbatLogic.AST __2966060645 = pOwnedChild;
							pOwnedChild = null;
							pSecretNamespace.AddChild(__2966060645);
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
						NumbatLogic.NamespaceDecl __1887985763 = pNextSecretNamespace;
						pNextSecretNamespace = null;
						pSecretTranslationUnit.AddChild(__1887985763);
					}
					else
					{
						NumbatLogic.NamespaceDecl __1887985763 = pNextSecretNamespace;
						pNextSecretNamespace = null;
						pSecretNamespace.AddChild(__1887985763);
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
					int i;
					for (i = 0; i < pPreviousNamespaceDecls.GetSize(); i++)
					{
						NamespaceDecl pPreviousNamespace = pPreviousNamespaceDecls.Get(i);
						if (pPreviousNamespace.m_pNameToken.m_sValue.IsEqual(sxName) && pPreviousNamespace.m_bSkipOutput == pNamespaceDecl.m_bSkipOutput)
						{
							AST pNextSibling = pChild.m_pNextSibling;
							AST pOwnedChild;
							pOwnedChild = pParentAST.RemoveChild(pChild);
							AST pSubChild;
							NumbatLogic.AST __2177070729 = pOwnedChild.m_pFirstChild;
							pOwnedChild.m_pFirstChild = null;
							pSubChild = __2177070729;
							pOwnedChild.m_pLastChild = null;
							if (pSubChild != null)
							{
								pSubChild.m_pParent = pPreviousNamespace;
								if (pPreviousNamespace.m_pFirstChild == null)
								{
									NumbatLogic.AST __446723994 = pSubChild;
									pSubChild = null;
									pPreviousNamespace.m_pFirstChild = __446723994;
									pPreviousNamespace.m_pLastChild = pPreviousNamespace.m_pFirstChild;
								}
								else
								{
									NumbatLogic.AST __446723994 = pSubChild;
									pSubChild = null;
									pPreviousNamespace.m_pLastChild.m_pNextSibling = __446723994;
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
					NumbatLogic.Token __522985997 = pToken;
					pToken = null;
					pPublicTranslationUnit.m_pTokenContainer.m_pTokenVector.PushBack(__522985997);
				}
				if (pPublicTranslationUnit.m_pFirstChild == null)
				{
					NumbatLogic.AST __2318169564 = pAST.m_pFirstChild;
					pAST.m_pFirstChild = null;
					pPublicTranslationUnit.m_pFirstChild = __2318169564;
					pPublicTranslationUnit.m_pLastChild = pPublicTranslationUnit.m_pFirstChild;
				}
				else
				{
					NumbatLogic.AST __2318169564 = pAST.m_pFirstChild;
					pAST.m_pFirstChild = null;
					pPublicTranslationUnit.m_pLastChild.m_pNextSibling = __2318169564;
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
			NumbatLogic.TranslationUnit __3345516770 = pSecretTranslationUnit;
			pSecretTranslationUnit = null;
			AddChild(__3345516770);
			m_pTranslationUnitVector.PushBack(pPublicTranslationUnit);
			NumbatLogic.TranslationUnit __1414343230 = pPublicTranslationUnit;
			pPublicTranslationUnit = null;
			AddChild(__1414343230);
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

