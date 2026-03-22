#line 1 "/home/cliffya/git/Lang/Source/Core/Project.nll"
namespace NumbatLogic
{
	class Project : AST
	{
		public Vector<TranslationUnit> m_pTranslationUnitVector;
		public NamespaceNode m_pRootNamespaceNode;
		public Validator m_pValidator;
#line 9 "/home/cliffya/git/Lang/Source/Core/Project.nll"
		public Project()
		{
			m_eType = AST.Type.AST_PROJECT;
			m_bCanDescend = true;
			m_pTranslationUnitVector = new Vector<TranslationUnit>();
			m_pRootNamespaceNode = new NamespaceNode(null, null);
			m_pValidator = null;
		}

		public void AddFile(string sFile, OwnedVector<InternalString> sDefineVector)
		{
			for (int i = 0; i < m_pTranslationUnitVector.GetSize(); i++)
			{
				TranslationUnit pTestTranslationUnit = m_pTranslationUnitVector.Get(i);
				if (pTestTranslationUnit.m_sInFile.IsEqual(sFile))
				{
#line 27 "/home/cliffya/git/Lang/Source/Core/Project.nll"
					return;
				}
			}
#line 31 "/home/cliffya/git/Lang/Source/Core/Project.nll"
			TranslationUnit pTranslationUnit = TranslationUnit.Create(sFile, sDefineVector);
#line 33 "/home/cliffya/git/Lang/Source/Core/Project.nll"
			if (pTranslationUnit == null)
			{
				Console.Log("unable to parse file");
				Console.Log(sFile);
				Assert.Plz(false);
				return;
			}
#line 41 "/home/cliffya/git/Lang/Source/Core/Project.nll"
			m_pTranslationUnitVector.PushBack(pTranslationUnit);
			NumbatLogic.TranslationUnit __1501017379 = pTranslationUnit;
#line 42 "/home/cliffya/git/Lang/Source/Core/Project.nll"
			pTranslationUnit = null;
#line 42 "/home/cliffya/git/Lang/Source/Core/Project.nll"
			AddChild(__1501017379);
		}

		public bool AddDirectory(string sDirectory, OwnedVector<InternalString> sDefineVector)
		{
			OwnedVector<InternalString> pAllowedSuffixVector = new OwnedVector<InternalString>();
			pAllowedSuffixVector.PushBack(new InternalString(".nll"));
			pAllowedSuffixVector.PushBack(new InternalString(".nll.def"));
#line 51 "/home/cliffya/git/Lang/Source/Core/Project.nll"
			OwnedVector<InternalString> sFileVector = File.GetRecursiveFileVector(sDirectory, pAllowedSuffixVector);
#line 53 "/home/cliffya/git/Lang/Source/Core/Project.nll"
			if (sFileVector == null)
			{
				return false;
			}
#line 58 "/home/cliffya/git/Lang/Source/Core/Project.nll"
			while (sFileVector.GetSize() > 0)
			{
				InternalString sFile = sFileVector.PopBack();
				AddFile(sFile.GetExternalString(), sDefineVector);
			}
			return true;
		}

		public void FullValidate()
		{
#line 69 "/home/cliffya/git/Lang/Source/Core/Project.nll"
			m_pValidator = new Validator(this);
			if (!m_pValidator.Validate())
			{
			}
		}

#line 76 "/home/cliffya/git/Lang/Source/Core/Project.nll"
		protected void RecurseNamespaces(AST pInAst, NamespaceDecl pSecretNamespace, TranslationUnit pSecretTranslationUnit)
		{
			if (pInAst.m_eType == AST.Type.AST_TRANSLATION_UNIT)
			{
				Assert.Plz(pSecretNamespace == null);
			}
#line 83 "/home/cliffya/git/Lang/Source/Core/Project.nll"
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
#line 94 "/home/cliffya/git/Lang/Source/Core/Project.nll"
						AST pOwnedChild;
						pOwnedChild = pInAst.RemoveChild(pChild);
#line 97 "/home/cliffya/git/Lang/Source/Core/Project.nll"
						Assert.Plz(pOwnedChild != null);
#line 99 "/home/cliffya/git/Lang/Source/Core/Project.nll"
						if (pSecretNamespace == null)
						{
							NumbatLogic.AST __2227940683 = pOwnedChild;
#line 101 "/home/cliffya/git/Lang/Source/Core/Project.nll"
							pOwnedChild = null;
#line 101 "/home/cliffya/git/Lang/Source/Core/Project.nll"
							pSecretTranslationUnit.AddChild(__2227940683);
						}
						else
						{
							NumbatLogic.AST __2227940687 = pOwnedChild;
#line 105 "/home/cliffya/git/Lang/Source/Core/Project.nll"
							pOwnedChild = null;
#line 105 "/home/cliffya/git/Lang/Source/Core/Project.nll"
							pSecretNamespace.AddChild(__2227940687);
						}
#line 108 "/home/cliffya/git/Lang/Source/Core/Project.nll"
						pChild = pNextChild;
						continue;
					}
#line 113 "/home/cliffya/git/Lang/Source/Core/Project.nll"
					NamespaceDecl pNextSecretNamespace = new NamespaceDecl();
					pNextSecretNamespace.m_pFirstToken = pNamespaceDecl.m_pFirstToken;
					pNextSecretNamespace.m_pNameToken = pNamespaceDecl.m_pNameToken;
					pNextSecretNamespace.m_bSkipOutput = pNamespaceDecl.m_bSkipOutput;
#line 118 "/home/cliffya/git/Lang/Source/Core/Project.nll"
					NamespaceDecl pTemp = pNextSecretNamespace;
					if (pSecretNamespace == null)
					{
						NumbatLogic.NamespaceDecl __4258634952 = pNextSecretNamespace;
#line 121 "/home/cliffya/git/Lang/Source/Core/Project.nll"
						pNextSecretNamespace = null;
#line 121 "/home/cliffya/git/Lang/Source/Core/Project.nll"
						pSecretTranslationUnit.AddChild(__4258634952);
					}
					else
					{
						NumbatLogic.NamespaceDecl __4258634956 = pNextSecretNamespace;
#line 125 "/home/cliffya/git/Lang/Source/Core/Project.nll"
						pNextSecretNamespace = null;
#line 125 "/home/cliffya/git/Lang/Source/Core/Project.nll"
						pSecretNamespace.AddChild(__4258634956);
					}
#line 128 "/home/cliffya/git/Lang/Source/Core/Project.nll"
					RecurseNamespaces(pNamespaceDecl, pTemp, pSecretTranslationUnit);
				}
#line 131 "/home/cliffya/git/Lang/Source/Core/Project.nll"
				pChild = pChild.m_pNextSibling;
			}
		}

		protected void NamespaceMerge(AST pParentAST)
		{
			AST pChild = pParentAST.m_pFirstChild;
			Vector<NamespaceDecl> pPreviousNamespaceDecls = new Vector<NamespaceDecl>();
#line 140 "/home/cliffya/git/Lang/Source/Core/Project.nll"
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
#line 156 "/home/cliffya/git/Lang/Source/Core/Project.nll"
							AST pSubChild;
							NumbatLogic.AST __2552836161 = pOwnedChild.m_pFirstChild;
#line 157 "/home/cliffya/git/Lang/Source/Core/Project.nll"
							pOwnedChild.m_pFirstChild = null;
#line 157 "/home/cliffya/git/Lang/Source/Core/Project.nll"
							pSubChild = __2552836161;
							pOwnedChild.m_pLastChild = null;
#line 160 "/home/cliffya/git/Lang/Source/Core/Project.nll"
							if (pSubChild != null)
							{
								pSubChild.m_pParent = pPreviousNamespace;
								if (pPreviousNamespace.m_pFirstChild == null)
								{
									NumbatLogic.AST __2417707012 = pSubChild;
#line 165 "/home/cliffya/git/Lang/Source/Core/Project.nll"
									pSubChild = null;
#line 165 "/home/cliffya/git/Lang/Source/Core/Project.nll"
									pPreviousNamespace.m_pFirstChild = __2417707012;
									pPreviousNamespace.m_pLastChild = pPreviousNamespace.m_pFirstChild;
								}
								else
								{
									NumbatLogic.AST __2417772606 = pSubChild;
#line 170 "/home/cliffya/git/Lang/Source/Core/Project.nll"
									pSubChild = null;
#line 170 "/home/cliffya/git/Lang/Source/Core/Project.nll"
									pPreviousNamespace.m_pLastChild.m_pNextSibling = __2417772606;
									pPreviousNamespace.m_pLastChild.m_pNextSibling.m_pPrevSibling = pPreviousNamespace.m_pLastChild;
								}
#line 174 "/home/cliffya/git/Lang/Source/Core/Project.nll"
								while (pPreviousNamespace.m_pLastChild.m_pNextSibling != null)
								{
									pPreviousNamespace.m_pLastChild = pPreviousNamespace.m_pLastChild.m_pNextSibling;
									pPreviousNamespace.m_pLastChild.m_pParent = pPreviousNamespace;
								}
							}
#line 181 "/home/cliffya/git/Lang/Source/Core/Project.nll"
							pChild = pNextSibling;
							break;
						}
					}
#line 186 "/home/cliffya/git/Lang/Source/Core/Project.nll"
					if (i == pPreviousNamespaceDecls.GetSize())
					{
						pPreviousNamespaceDecls.PushBack(pNamespaceDecl);
					}
					else
					{
						continue;
					}
				}
#line 196 "/home/cliffya/git/Lang/Source/Core/Project.nll"
				pChild = pChild.m_pNextSibling;
			}
			{
#line 200 "/home/cliffya/git/Lang/Source/Core/Project.nll"
				for (int i = 0; i < pPreviousNamespaceDecls.GetSize(); i++)
				{
					NamespaceDecl pPreviousNamespace = pPreviousNamespaceDecls.Get(i);
					NamespaceMerge(pPreviousNamespace);
				}
			}
		}

		public void Amalgamate(string sAmalgamateFileName)
		{
#line 211 "/home/cliffya/git/Lang/Source/Core/Project.nll"
			InternalString sSecretFileName = new InternalString(sAmalgamateFileName);
			sSecretFileName.Replace(".nll", "Secret.nll");
			TranslationUnit pSecretTranslationUnit = new TranslationUnit(sSecretFileName.GetExternalString());
			TranslationUnit pPublicTranslationUnit = new TranslationUnit(sAmalgamateFileName);
#line 216 "/home/cliffya/git/Lang/Source/Core/Project.nll"
			while (m_pFirstChild != null)
			{
				AST pAST;
				pAST = RemoveChild(m_pFirstChild);
#line 221 "/home/cliffya/git/Lang/Source/Core/Project.nll"
				TranslationUnit pTranslationUnit = (TranslationUnit)(pAST);
				bool bSkipOutput = pTranslationUnit.m_sInFile.EndsWith(".nll.def");
#line 225 "/home/cliffya/git/Lang/Source/Core/Project.nll"
				while (pTranslationUnit.m_pTokenContainer.m_pTokenVector.GetSize() > 0)
				{
					Token pToken = pTranslationUnit.m_pTokenContainer.m_pTokenVector.PopFront();
					pToken.m_sFileName = pPublicTranslationUnit.m_sInFile;
					NumbatLogic.Token __3778790288 = pToken;
#line 229 "/home/cliffya/git/Lang/Source/Core/Project.nll"
					pToken = null;
#line 229 "/home/cliffya/git/Lang/Source/Core/Project.nll"
					pPublicTranslationUnit.m_pTokenContainer.m_pTokenVector.PushBack(__3778790288);
				}
#line 232 "/home/cliffya/git/Lang/Source/Core/Project.nll"
				if (pPublicTranslationUnit.m_pFirstChild == null)
				{
					NumbatLogic.AST __4061733420 = pAST.m_pFirstChild;
#line 234 "/home/cliffya/git/Lang/Source/Core/Project.nll"
					pAST.m_pFirstChild = null;
#line 234 "/home/cliffya/git/Lang/Source/Core/Project.nll"
					pPublicTranslationUnit.m_pFirstChild = __4061733420;
					pPublicTranslationUnit.m_pLastChild = pPublicTranslationUnit.m_pFirstChild;
				}
				else
				{
					NumbatLogic.AST __4061733425 = pAST.m_pFirstChild;
#line 239 "/home/cliffya/git/Lang/Source/Core/Project.nll"
					pAST.m_pFirstChild = null;
#line 239 "/home/cliffya/git/Lang/Source/Core/Project.nll"
					pPublicTranslationUnit.m_pLastChild.m_pNextSibling = __4061733425;
					pPublicTranslationUnit.m_pLastChild = pPublicTranslationUnit.m_pLastChild.m_pNextSibling;
				}
#line 243 "/home/cliffya/git/Lang/Source/Core/Project.nll"
				while (true)
				{
					pPublicTranslationUnit.m_pLastChild.m_pParent = pPublicTranslationUnit;
					pPublicTranslationUnit.m_pLastChild.m_bSkipOutput = bSkipOutput;
#line 248 "/home/cliffya/git/Lang/Source/Core/Project.nll"
					if (pPublicTranslationUnit.m_pLastChild.m_pNextSibling == null)
						break;
#line 251 "/home/cliffya/git/Lang/Source/Core/Project.nll"
					pPublicTranslationUnit.m_pLastChild = pPublicTranslationUnit.m_pLastChild.m_pNextSibling;
				}
			}
#line 255 "/home/cliffya/git/Lang/Source/Core/Project.nll"
			while (m_pTranslationUnitVector.GetSize() > 0)
			{
				m_pTranslationUnitVector.PopBack();
			}
#line 260 "/home/cliffya/git/Lang/Source/Core/Project.nll"
			NamespaceMerge(pPublicTranslationUnit);
#line 263 "/home/cliffya/git/Lang/Source/Core/Project.nll"
			RecurseNamespaces(pPublicTranslationUnit, null, pSecretTranslationUnit);
#line 265 "/home/cliffya/git/Lang/Source/Core/Project.nll"
			m_pTranslationUnitVector.PushBack(pSecretTranslationUnit);
			NumbatLogic.TranslationUnit __1635193661 = pSecretTranslationUnit;
#line 266 "/home/cliffya/git/Lang/Source/Core/Project.nll"
			pSecretTranslationUnit = null;
#line 266 "/home/cliffya/git/Lang/Source/Core/Project.nll"
			AddChild(__1635193661);
#line 268 "/home/cliffya/git/Lang/Source/Core/Project.nll"
			m_pTranslationUnitVector.PushBack(pPublicTranslationUnit);
			NumbatLogic.TranslationUnit __623256121 = pPublicTranslationUnit;
#line 269 "/home/cliffya/git/Lang/Source/Core/Project.nll"
			pPublicTranslationUnit = null;
#line 269 "/home/cliffya/git/Lang/Source/Core/Project.nll"
			AddChild(__623256121);
		}

		public void Output(AST.Language eLanguage, OutputFile eOutputFile)
		{
			InternalString sOutFile = new InternalString("");
			OutputBuilder pOut = new OutputBuilder();
#line 278 "/home/cliffya/git/Lang/Source/Core/Project.nll"
			for (int i = 0; i < m_pTranslationUnitVector.GetSize(); i++)
			{
				TranslationUnit pTranslationUnit = m_pTranslationUnitVector.Get(i);
				sOutFile.Set(pTranslationUnit.m_sInFile.GetExternalString());
#line 283 "/home/cliffya/git/Lang/Source/Core/Project.nll"
				if (sOutFile.EndsWith(".nll"))
				{
					TranslationUnit.ConvertFilePath(eLanguage, eOutputFile, sOutFile);
#line 287 "/home/cliffya/git/Lang/Source/Core/Project.nll"
					string sxOutFile = sOutFile.GetExternalString();
#line 289 "/home/cliffya/git/Lang/Source/Core/Project.nll"
					pOut.m_sOut.Set("");
					pTranslationUnit.Stringify(eLanguage, eOutputFile, 0, pOut);
#line 292 "/home/cliffya/git/Lang/Source/Core/Project.nll"
					InternalString sDirectory = File.GetFileDirectory(sxOutFile);
					File.CreateDirectory(sDirectory.GetExternalString());
#line 296 "/home/cliffya/git/Lang/Source/Core/Project.nll"
					InternalString sTestFile = File.GetContents(sxOutFile);
					if (sTestFile == null || !pOut.m_sOut.IsEqual(sTestFile.GetExternalString()))
					{
						File.PutContents(sxOutFile, pOut.m_sOut.GetExternalString());
					}
				}
			}
		}

#line 3 "/home/cliffya/git/Lang/Source/Core/Project.nll"
		~Project()
		{
		}

	}
}

