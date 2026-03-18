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

		public void AddDirectory(string sDirectory, OwnedVector<InternalString> sDefineVector)
		{
			OwnedVector<InternalString> pAllowedSuffixVector = new OwnedVector<InternalString>();
			pAllowedSuffixVector.PushBack(new InternalString(".nll"));
			pAllowedSuffixVector.PushBack(new InternalString(".nll.def"));
#line 51 "/home/cliffya/git/Lang/Source/Core/Project.nll"
			OwnedVector<InternalString> sFileVector = File.GetRecursiveFileVector(sDirectory, pAllowedSuffixVector);
#line 53 "/home/cliffya/git/Lang/Source/Core/Project.nll"
			while (sFileVector.GetSize() > 0)
			{
				InternalString sFile = sFileVector.PopBack();
				AddFile(sFile.GetExternalString(), sDefineVector);
			}
		}

		public void FullValidate()
		{
#line 64 "/home/cliffya/git/Lang/Source/Core/Project.nll"
			for (int i = 0; i < m_pTranslationUnitVector.GetSize(); i++)
			{
				TranslationUnit pTranslationUnit = m_pTranslationUnitVector.Get(i);
				if (pTranslationUnit.m_sInFile.EndsWith(".nll"))
				{
					if (pTranslationUnit.m_sInFile.StartsWith("Shared"))
						pTranslationUnit.m_sInFile.Replace("Shared", "Source/Shared");
					else
						pTranslationUnit.m_sInFile.Replace("/Shared", "/Source/Shared");
				}
			}
#line 77 "/home/cliffya/git/Lang/Source/Core/Project.nll"
			m_pValidator = new Validator(this);
			if (!m_pValidator.Validate())
			{
			}
		}

#line 84 "/home/cliffya/git/Lang/Source/Core/Project.nll"
		protected void RecurseNamespaces(AST pInAst, NamespaceDecl pSecretNamespace, TranslationUnit pSecretTranslationUnit)
		{
			if (pInAst.m_eType == AST.Type.AST_TRANSLATION_UNIT)
			{
				Assert.Plz(pSecretNamespace == null);
			}
#line 91 "/home/cliffya/git/Lang/Source/Core/Project.nll"
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
#line 102 "/home/cliffya/git/Lang/Source/Core/Project.nll"
						AST pOwnedChild;
						pOwnedChild = pInAst.RemoveChild(pChild);
#line 105 "/home/cliffya/git/Lang/Source/Core/Project.nll"
						Assert.Plz(pOwnedChild != null);
#line 107 "/home/cliffya/git/Lang/Source/Core/Project.nll"
						if (pSecretNamespace == null)
						{
							NumbatLogic.AST __2227940691 = pOwnedChild;
#line 109 "/home/cliffya/git/Lang/Source/Core/Project.nll"
							pOwnedChild = null;
#line 109 "/home/cliffya/git/Lang/Source/Core/Project.nll"
							pSecretTranslationUnit.AddChild(__2227940691);
						}
						else
						{
							NumbatLogic.AST __2228006284 = pOwnedChild;
#line 113 "/home/cliffya/git/Lang/Source/Core/Project.nll"
							pOwnedChild = null;
#line 113 "/home/cliffya/git/Lang/Source/Core/Project.nll"
							pSecretNamespace.AddChild(__2228006284);
						}
#line 116 "/home/cliffya/git/Lang/Source/Core/Project.nll"
						pChild = pNextChild;
						continue;
					}
#line 121 "/home/cliffya/git/Lang/Source/Core/Project.nll"
					NamespaceDecl pNextSecretNamespace = new NamespaceDecl();
					pNextSecretNamespace.m_pFirstToken = pNamespaceDecl.m_pFirstToken;
					pNextSecretNamespace.m_pNameToken = pNamespaceDecl.m_pNameToken;
					pNextSecretNamespace.m_bSkipOutput = pNamespaceDecl.m_bSkipOutput;
#line 126 "/home/cliffya/git/Lang/Source/Core/Project.nll"
					NamespaceDecl pTemp = pNextSecretNamespace;
					if (pSecretNamespace == null)
					{
						NumbatLogic.NamespaceDecl __4258634960 = pNextSecretNamespace;
#line 129 "/home/cliffya/git/Lang/Source/Core/Project.nll"
						pNextSecretNamespace = null;
#line 129 "/home/cliffya/git/Lang/Source/Core/Project.nll"
						pSecretTranslationUnit.AddChild(__4258634960);
					}
					else
					{
						NumbatLogic.NamespaceDecl __4258700553 = pNextSecretNamespace;
#line 133 "/home/cliffya/git/Lang/Source/Core/Project.nll"
						pNextSecretNamespace = null;
#line 133 "/home/cliffya/git/Lang/Source/Core/Project.nll"
						pSecretNamespace.AddChild(__4258700553);
					}
#line 136 "/home/cliffya/git/Lang/Source/Core/Project.nll"
					RecurseNamespaces(pNamespaceDecl, pTemp, pSecretTranslationUnit);
				}
#line 139 "/home/cliffya/git/Lang/Source/Core/Project.nll"
				pChild = pChild.m_pNextSibling;
			}
		}

		protected void NamespaceMerge(AST pParentAST)
		{
			AST pChild = pParentAST.m_pFirstChild;
			Vector<NamespaceDecl> pPreviousNamespaceDecls = new Vector<NamespaceDecl>();
#line 148 "/home/cliffya/git/Lang/Source/Core/Project.nll"
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
#line 164 "/home/cliffya/git/Lang/Source/Core/Project.nll"
							AST pSubChild;
							NumbatLogic.AST __2552901758 = pOwnedChild.m_pFirstChild;
#line 165 "/home/cliffya/git/Lang/Source/Core/Project.nll"
							pOwnedChild.m_pFirstChild = null;
#line 165 "/home/cliffya/git/Lang/Source/Core/Project.nll"
							pSubChild = __2552901758;
							pOwnedChild.m_pLastChild = null;
#line 168 "/home/cliffya/git/Lang/Source/Core/Project.nll"
							if (pSubChild != null)
							{
								pSubChild.m_pParent = pPreviousNamespace;
								if (pPreviousNamespace.m_pFirstChild == null)
								{
									NumbatLogic.AST __2417772609 = pSubChild;
#line 173 "/home/cliffya/git/Lang/Source/Core/Project.nll"
									pSubChild = null;
#line 173 "/home/cliffya/git/Lang/Source/Core/Project.nll"
									pPreviousNamespace.m_pFirstChild = __2417772609;
									pPreviousNamespace.m_pLastChild = pPreviousNamespace.m_pFirstChild;
								}
								else
								{
									NumbatLogic.AST __2417772614 = pSubChild;
#line 178 "/home/cliffya/git/Lang/Source/Core/Project.nll"
									pSubChild = null;
#line 178 "/home/cliffya/git/Lang/Source/Core/Project.nll"
									pPreviousNamespace.m_pLastChild.m_pNextSibling = __2417772614;
									pPreviousNamespace.m_pLastChild.m_pNextSibling.m_pPrevSibling = pPreviousNamespace.m_pLastChild;
								}
#line 182 "/home/cliffya/git/Lang/Source/Core/Project.nll"
								while (pPreviousNamespace.m_pLastChild.m_pNextSibling != null)
								{
									pPreviousNamespace.m_pLastChild = pPreviousNamespace.m_pLastChild.m_pNextSibling;
									pPreviousNamespace.m_pLastChild.m_pParent = pPreviousNamespace;
								}
							}
#line 189 "/home/cliffya/git/Lang/Source/Core/Project.nll"
							pChild = pNextSibling;
							break;
						}
					}
#line 194 "/home/cliffya/git/Lang/Source/Core/Project.nll"
					if (i == pPreviousNamespaceDecls.GetSize())
					{
						pPreviousNamespaceDecls.PushBack(pNamespaceDecl);
					}
					else
					{
						continue;
					}
				}
#line 204 "/home/cliffya/git/Lang/Source/Core/Project.nll"
				pChild = pChild.m_pNextSibling;
			}
			{
#line 208 "/home/cliffya/git/Lang/Source/Core/Project.nll"
				for (int i = 0; i < pPreviousNamespaceDecls.GetSize(); i++)
				{
					NamespaceDecl pPreviousNamespace = pPreviousNamespaceDecls.Get(i);
					NamespaceMerge(pPreviousNamespace);
				}
			}
		}

		public void Amalgamate(string sAmalgamateFileName)
		{
#line 219 "/home/cliffya/git/Lang/Source/Core/Project.nll"
			InternalString sSecretFileName = new InternalString(sAmalgamateFileName);
			sSecretFileName.Replace(".nll", "Secret.nll");
			TranslationUnit pSecretTranslationUnit = new TranslationUnit(sSecretFileName.GetExternalString());
			TranslationUnit pPublicTranslationUnit = new TranslationUnit(sAmalgamateFileName);
#line 224 "/home/cliffya/git/Lang/Source/Core/Project.nll"
			while (m_pFirstChild != null)
			{
				AST pAST;
				pAST = RemoveChild(m_pFirstChild);
#line 229 "/home/cliffya/git/Lang/Source/Core/Project.nll"
				TranslationUnit pTranslationUnit = (TranslationUnit)(pAST);
				bool bSkipOutput = pTranslationUnit.m_sInFile.EndsWith(".nll.def");
#line 233 "/home/cliffya/git/Lang/Source/Core/Project.nll"
				while (pTranslationUnit.m_pTokenContainer.m_pTokenVector.GetSize() > 0)
				{
					Token pToken = pTranslationUnit.m_pTokenContainer.m_pTokenVector.PopFront();
					pToken.m_sFileName = pPublicTranslationUnit.m_sInFile;
					NumbatLogic.Token __3778855885 = pToken;
#line 237 "/home/cliffya/git/Lang/Source/Core/Project.nll"
					pToken = null;
#line 237 "/home/cliffya/git/Lang/Source/Core/Project.nll"
					pPublicTranslationUnit.m_pTokenContainer.m_pTokenVector.PushBack(__3778855885);
				}
#line 240 "/home/cliffya/git/Lang/Source/Core/Project.nll"
				if (pPublicTranslationUnit.m_pFirstChild == null)
				{
					NumbatLogic.AST __4061799017 = pAST.m_pFirstChild;
#line 242 "/home/cliffya/git/Lang/Source/Core/Project.nll"
					pAST.m_pFirstChild = null;
#line 242 "/home/cliffya/git/Lang/Source/Core/Project.nll"
					pPublicTranslationUnit.m_pFirstChild = __4061799017;
					pPublicTranslationUnit.m_pLastChild = pPublicTranslationUnit.m_pFirstChild;
				}
				else
				{
					NumbatLogic.AST __4061799022 = pAST.m_pFirstChild;
#line 247 "/home/cliffya/git/Lang/Source/Core/Project.nll"
					pAST.m_pFirstChild = null;
#line 247 "/home/cliffya/git/Lang/Source/Core/Project.nll"
					pPublicTranslationUnit.m_pLastChild.m_pNextSibling = __4061799022;
					pPublicTranslationUnit.m_pLastChild = pPublicTranslationUnit.m_pLastChild.m_pNextSibling;
				}
#line 251 "/home/cliffya/git/Lang/Source/Core/Project.nll"
				while (true)
				{
					pPublicTranslationUnit.m_pLastChild.m_pParent = pPublicTranslationUnit;
					pPublicTranslationUnit.m_pLastChild.m_bSkipOutput = bSkipOutput;
#line 256 "/home/cliffya/git/Lang/Source/Core/Project.nll"
					if (pPublicTranslationUnit.m_pLastChild.m_pNextSibling == null)
						break;
#line 259 "/home/cliffya/git/Lang/Source/Core/Project.nll"
					pPublicTranslationUnit.m_pLastChild = pPublicTranslationUnit.m_pLastChild.m_pNextSibling;
				}
			}
#line 263 "/home/cliffya/git/Lang/Source/Core/Project.nll"
			while (m_pTranslationUnitVector.GetSize() > 0)
			{
				m_pTranslationUnitVector.PopBack();
			}
#line 268 "/home/cliffya/git/Lang/Source/Core/Project.nll"
			NamespaceMerge(pPublicTranslationUnit);
#line 271 "/home/cliffya/git/Lang/Source/Core/Project.nll"
			RecurseNamespaces(pPublicTranslationUnit, null, pSecretTranslationUnit);
#line 273 "/home/cliffya/git/Lang/Source/Core/Project.nll"
			m_pTranslationUnitVector.PushBack(pSecretTranslationUnit);
			NumbatLogic.TranslationUnit __1635259258 = pSecretTranslationUnit;
#line 274 "/home/cliffya/git/Lang/Source/Core/Project.nll"
			pSecretTranslationUnit = null;
#line 274 "/home/cliffya/git/Lang/Source/Core/Project.nll"
			AddChild(__1635259258);
#line 276 "/home/cliffya/git/Lang/Source/Core/Project.nll"
			m_pTranslationUnitVector.PushBack(pPublicTranslationUnit);
			NumbatLogic.TranslationUnit __623321718 = pPublicTranslationUnit;
#line 277 "/home/cliffya/git/Lang/Source/Core/Project.nll"
			pPublicTranslationUnit = null;
#line 277 "/home/cliffya/git/Lang/Source/Core/Project.nll"
			AddChild(__623321718);
		}

		public void Output(AST.Language eLanguage, OutputFile eOutputFile)
		{
			InternalString sOutFile = new InternalString("");
			OutputBuilder pOut = new OutputBuilder();
#line 286 "/home/cliffya/git/Lang/Source/Core/Project.nll"
			for (int i = 0; i < m_pTranslationUnitVector.GetSize(); i++)
			{
				TranslationUnit pTranslationUnit = m_pTranslationUnitVector.Get(i);
				sOutFile.Set(pTranslationUnit.m_sInFile.GetExternalString());
#line 291 "/home/cliffya/git/Lang/Source/Core/Project.nll"
				if (sOutFile.EndsWith(".nll"))
				{
					TranslationUnit.ConvertFilePath(eLanguage, eOutputFile, sOutFile);
#line 295 "/home/cliffya/git/Lang/Source/Core/Project.nll"
					string sxOutFile = sOutFile.GetExternalString();
#line 297 "/home/cliffya/git/Lang/Source/Core/Project.nll"
					pOut.m_sOut.Set("");
					pTranslationUnit.Stringify(eLanguage, eOutputFile, 0, pOut);
#line 300 "/home/cliffya/git/Lang/Source/Core/Project.nll"
					InternalString sDirectory = File.GetFileDirectory(sxOutFile);
					File.CreateDirectory(sDirectory.GetExternalString());
#line 304 "/home/cliffya/git/Lang/Source/Core/Project.nll"
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

