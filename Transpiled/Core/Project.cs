#line 1 "../../../Source/Core/Project.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/Project.nll"
	class Project : AST
	{
#line 5 "../../../Source/Core/Project.nll"
		public Vector<TranslationUnit> m_pTranslationUnitVector;
#line 6 "../../../Source/Core/Project.nll"
		public NamespaceNode m_pRootNamespaceNode;
#line 7 "../../../Source/Core/Project.nll"
		public Validator m_pValidator;
#line 9 "../../../Source/Core/Project.nll"
		public Project()
		{
#line 11 "../../../Source/Core/Project.nll"
			m_eType = AST.Type.AST_PROJECT;
#line 12 "../../../Source/Core/Project.nll"
			m_bCanDescend = true;
#line 13 "../../../Source/Core/Project.nll"
			m_pTranslationUnitVector = new Vector<TranslationUnit>();
#line 14 "../../../Source/Core/Project.nll"
			m_pRootNamespaceNode = new NamespaceNode(null, null);
#line 15 "../../../Source/Core/Project.nll"
			m_pValidator = null;
		}

#line 18 "../../../Source/Core/Project.nll"
		public void AddFile(string sFile, OwnedVector<InternalString> sDefineVector)
		{
#line 20 "../../../Source/Core/Project.nll"
			for (int i = 0; i < m_pTranslationUnitVector.GetSize(); i++)
			{
#line 22 "../../../Source/Core/Project.nll"
				TranslationUnit pTestTranslationUnit = m_pTranslationUnitVector.Get(i);
#line 23 "../../../Source/Core/Project.nll"
				if (pTestTranslationUnit.m_sInFile.IsEqual(sFile))
				{
#line 27 "../../../Source/Core/Project.nll"
					return;
				}
			}
#line 31 "../../../Source/Core/Project.nll"
			TranslationUnit pTranslationUnit = TranslationUnit.Create(sFile, sDefineVector);
#line 33 "../../../Source/Core/Project.nll"
			if (pTranslationUnit == null)
			{
#line 35 "../../../Source/Core/Project.nll"
				Console.Log("unable to parse file");
#line 36 "../../../Source/Core/Project.nll"
				Console.Log(sFile);
#line 37 "../../../Source/Core/Project.nll"
				Assert.Plz(false);
#line 38 "../../../Source/Core/Project.nll"
				return;
			}
#line 41 "../../../Source/Core/Project.nll"
			m_pTranslationUnitVector.PushBack(pTranslationUnit);
			NumbatLogic.TranslationUnit __1501017379 = pTranslationUnit;
#line 42 "../../../Source/Core/Project.nll"
			pTranslationUnit = null;
#line 42 "../../../Source/Core/Project.nll"
			AddChild(__1501017379);
		}

#line 45 "../../../Source/Core/Project.nll"
		public void AddDirectory(string sDirectory, OwnedVector<InternalString> sDefineVector)
		{
#line 47 "../../../Source/Core/Project.nll"
			OwnedVector<InternalString> sFileVector = File.GetRecursiveFileVector(sDirectory);
#line 49 "../../../Source/Core/Project.nll"
			while (sFileVector.GetSize() > 0)
			{
#line 51 "../../../Source/Core/Project.nll"
				InternalString sFile = sFileVector.PopBack();
#line 52 "../../../Source/Core/Project.nll"
				AddFile(sFile.GetExternalString(), sDefineVector);
			}
		}

#line 56 "../../../Source/Core/Project.nll"
		public void FullValidate()
		{
#line 59 "../../../Source/Core/Project.nll"
			for (int i = 0; i < m_pTranslationUnitVector.GetSize(); i++)
			{
#line 61 "../../../Source/Core/Project.nll"
				TranslationUnit pTranslationUnit = m_pTranslationUnitVector.Get(i);
#line 62 "../../../Source/Core/Project.nll"
				if (pTranslationUnit.m_sInFile.EndsWith(".nll"))
				{
#line 64 "../../../Source/Core/Project.nll"
					pTranslationUnit.m_sInFile.Replace("../LangShared", "../LangShared/Transpiled");
#line 65 "../../../Source/Core/Project.nll"
					if (pTranslationUnit.m_sInFile.StartsWith("Shared"))
#line 66 "../../../Source/Core/Project.nll"
						pTranslationUnit.m_sInFile.Replace("Shared", "Source/Shared");
					else
#line 68 "../../../Source/Core/Project.nll"
						pTranslationUnit.m_sInFile.Replace("/Shared", "/Source/Shared");
				}
			}
#line 73 "../../../Source/Core/Project.nll"
			m_pValidator = new Validator(this);
#line 74 "../../../Source/Core/Project.nll"
			if (!m_pValidator.Validate())
			{
			}
		}

#line 80 "../../../Source/Core/Project.nll"
		protected void RecurseNamespaces(AST pInAst, NamespaceDecl pSecretNamespace, TranslationUnit pSecretTranslationUnit)
		{
#line 82 "../../../Source/Core/Project.nll"
			if (pInAst.m_eType == AST.Type.AST_TRANSLATION_UNIT)
			{
#line 84 "../../../Source/Core/Project.nll"
				Assert.Plz(pSecretNamespace == null);
			}
#line 87 "../../../Source/Core/Project.nll"
			AST pChild = pInAst.m_pFirstChild;
#line 88 "../../../Source/Core/Project.nll"
			while (pChild != null)
			{
#line 90 "../../../Source/Core/Project.nll"
				if (pChild.m_eType == AST.Type.NAMESPACE_DECL)
				{
#line 92 "../../../Source/Core/Project.nll"
					NamespaceDecl pNamespaceDecl = (NamespaceDecl)(pChild);
#line 93 "../../../Source/Core/Project.nll"
					if (pNamespaceDecl.m_pNameToken.m_sValue.IsEqual("Secret"))
					{
#line 95 "../../../Source/Core/Project.nll"
						AST pNextChild = pChild;
#line 96 "../../../Source/Core/Project.nll"
						pNextChild = pChild.m_pNextSibling;
#line 98 "../../../Source/Core/Project.nll"
						AST pOwnedChild;
#line 99 "../../../Source/Core/Project.nll"
						pOwnedChild = pInAst.RemoveChild(pChild);
#line 101 "../../../Source/Core/Project.nll"
						Assert.Plz(pOwnedChild != null);
#line 103 "../../../Source/Core/Project.nll"
						if (pSecretNamespace == null)
						{
							NumbatLogic.AST __2227940687 = pOwnedChild;
#line 105 "../../../Source/Core/Project.nll"
							pOwnedChild = null;
#line 105 "../../../Source/Core/Project.nll"
							pSecretTranslationUnit.AddChild(__2227940687);
						}
						else
						{
							NumbatLogic.AST __2227940691 = pOwnedChild;
#line 109 "../../../Source/Core/Project.nll"
							pOwnedChild = null;
#line 109 "../../../Source/Core/Project.nll"
							pSecretNamespace.AddChild(__2227940691);
						}
#line 112 "../../../Source/Core/Project.nll"
						pChild = pNextChild;
#line 113 "../../../Source/Core/Project.nll"
						continue;
					}
#line 117 "../../../Source/Core/Project.nll"
					NamespaceDecl pNextSecretNamespace = new NamespaceDecl();
#line 118 "../../../Source/Core/Project.nll"
					pNextSecretNamespace.m_pFirstToken = pNamespaceDecl.m_pFirstToken;
#line 119 "../../../Source/Core/Project.nll"
					pNextSecretNamespace.m_pNameToken = pNamespaceDecl.m_pNameToken;
#line 120 "../../../Source/Core/Project.nll"
					pNextSecretNamespace.m_bSkipOutput = pNamespaceDecl.m_bSkipOutput;
#line 122 "../../../Source/Core/Project.nll"
					NamespaceDecl pTemp = pNextSecretNamespace;
#line 123 "../../../Source/Core/Project.nll"
					if (pSecretNamespace == null)
					{
						NumbatLogic.NamespaceDecl __4258634956 = pNextSecretNamespace;
#line 125 "../../../Source/Core/Project.nll"
						pNextSecretNamespace = null;
#line 125 "../../../Source/Core/Project.nll"
						pSecretTranslationUnit.AddChild(__4258634956);
					}
					else
					{
						NumbatLogic.NamespaceDecl __4258634960 = pNextSecretNamespace;
#line 129 "../../../Source/Core/Project.nll"
						pNextSecretNamespace = null;
#line 129 "../../../Source/Core/Project.nll"
						pSecretNamespace.AddChild(__4258634960);
					}
#line 132 "../../../Source/Core/Project.nll"
					RecurseNamespaces(pNamespaceDecl, pTemp, pSecretTranslationUnit);
				}
#line 135 "../../../Source/Core/Project.nll"
				pChild = pChild.m_pNextSibling;
			}
		}

#line 139 "../../../Source/Core/Project.nll"
		protected void NamespaceMerge(AST pParentAST)
		{
#line 141 "../../../Source/Core/Project.nll"
			AST pChild = pParentAST.m_pFirstChild;
#line 142 "../../../Source/Core/Project.nll"
			Vector<NamespaceDecl> pPreviousNamespaceDecls = new Vector<NamespaceDecl>();
#line 144 "../../../Source/Core/Project.nll"
			while (pChild != null)
			{
#line 146 "../../../Source/Core/Project.nll"
				if (pChild.m_eType == AST.Type.NAMESPACE_DECL)
				{
#line 148 "../../../Source/Core/Project.nll"
					NamespaceDecl pNamespaceDecl = (NamespaceDecl)(pChild);
#line 149 "../../../Source/Core/Project.nll"
					string sxName = pNamespaceDecl.m_pNameToken.m_sValue.GetExternalString();
#line 150 "../../../Source/Core/Project.nll"
					int i = 0;
#line 151 "../../../Source/Core/Project.nll"
					for (i = 0; i < pPreviousNamespaceDecls.GetSize(); i++)
					{
#line 153 "../../../Source/Core/Project.nll"
						NamespaceDecl pPreviousNamespace = pPreviousNamespaceDecls.Get(i);
#line 154 "../../../Source/Core/Project.nll"
						if (pPreviousNamespace.m_pNameToken.m_sValue.IsEqual(sxName) && pPreviousNamespace.m_bSkipOutput == pNamespaceDecl.m_bSkipOutput)
						{
#line 156 "../../../Source/Core/Project.nll"
							AST pNextSibling = pChild.m_pNextSibling;
#line 157 "../../../Source/Core/Project.nll"
							AST pOwnedChild;
#line 158 "../../../Source/Core/Project.nll"
							pOwnedChild = pParentAST.RemoveChild(pChild);
#line 160 "../../../Source/Core/Project.nll"
							AST pSubChild;
							NumbatLogic.AST __2552901754 = pOwnedChild.m_pFirstChild;
#line 161 "../../../Source/Core/Project.nll"
							pOwnedChild.m_pFirstChild = null;
#line 161 "../../../Source/Core/Project.nll"
							pSubChild = __2552901754;
#line 162 "../../../Source/Core/Project.nll"
							pOwnedChild.m_pLastChild = null;
#line 164 "../../../Source/Core/Project.nll"
							if (pSubChild != null)
							{
#line 166 "../../../Source/Core/Project.nll"
								pSubChild.m_pParent = pPreviousNamespace;
#line 167 "../../../Source/Core/Project.nll"
								if (pPreviousNamespace.m_pFirstChild == null)
								{
									NumbatLogic.AST __2417707016 = pSubChild;
#line 169 "../../../Source/Core/Project.nll"
									pSubChild = null;
#line 169 "../../../Source/Core/Project.nll"
									pPreviousNamespace.m_pFirstChild = __2417707016;
#line 170 "../../../Source/Core/Project.nll"
									pPreviousNamespace.m_pLastChild = pPreviousNamespace.m_pFirstChild;
								}
								else
								{
									NumbatLogic.AST __2417772610 = pSubChild;
#line 174 "../../../Source/Core/Project.nll"
									pSubChild = null;
#line 174 "../../../Source/Core/Project.nll"
									pPreviousNamespace.m_pLastChild.m_pNextSibling = __2417772610;
#line 175 "../../../Source/Core/Project.nll"
									pPreviousNamespace.m_pLastChild.m_pNextSibling.m_pPrevSibling = pPreviousNamespace.m_pLastChild;
								}
#line 178 "../../../Source/Core/Project.nll"
								while (pPreviousNamespace.m_pLastChild.m_pNextSibling != null)
								{
#line 180 "../../../Source/Core/Project.nll"
									pPreviousNamespace.m_pLastChild = pPreviousNamespace.m_pLastChild.m_pNextSibling;
#line 181 "../../../Source/Core/Project.nll"
									pPreviousNamespace.m_pLastChild.m_pParent = pPreviousNamespace;
								}
							}
#line 185 "../../../Source/Core/Project.nll"
							pChild = pNextSibling;
#line 186 "../../../Source/Core/Project.nll"
							break;
						}
					}
#line 190 "../../../Source/Core/Project.nll"
					if (i == pPreviousNamespaceDecls.GetSize())
					{
#line 192 "../../../Source/Core/Project.nll"
						pPreviousNamespaceDecls.PushBack(pNamespaceDecl);
					}
					else
					{
#line 196 "../../../Source/Core/Project.nll"
						continue;
					}
				}
#line 200 "../../../Source/Core/Project.nll"
				pChild = pChild.m_pNextSibling;
			}
			{
#line 204 "../../../Source/Core/Project.nll"
				for (int i = 0; i < pPreviousNamespaceDecls.GetSize(); i++)
				{
#line 206 "../../../Source/Core/Project.nll"
					NamespaceDecl pPreviousNamespace = pPreviousNamespaceDecls.Get(i);
#line 207 "../../../Source/Core/Project.nll"
					NamespaceMerge(pPreviousNamespace);
				}
			}
		}

#line 212 "../../../Source/Core/Project.nll"
		public void Amalgamate(string sAmalgamateFileName)
		{
#line 215 "../../../Source/Core/Project.nll"
			InternalString sSecretFileName = new InternalString(sAmalgamateFileName);
#line 216 "../../../Source/Core/Project.nll"
			sSecretFileName.Replace(".nll", "Secret.nll");
#line 217 "../../../Source/Core/Project.nll"
			TranslationUnit pSecretTranslationUnit = new TranslationUnit(sSecretFileName.GetExternalString());
#line 218 "../../../Source/Core/Project.nll"
			TranslationUnit pPublicTranslationUnit = new TranslationUnit(sAmalgamateFileName);
#line 220 "../../../Source/Core/Project.nll"
			while (m_pFirstChild != null)
			{
#line 222 "../../../Source/Core/Project.nll"
				AST pAST;
#line 223 "../../../Source/Core/Project.nll"
				pAST = RemoveChild(m_pFirstChild);
#line 225 "../../../Source/Core/Project.nll"
				TranslationUnit pTranslationUnit = (TranslationUnit)(pAST);
#line 226 "../../../Source/Core/Project.nll"
				bool bSkipOutput = pTranslationUnit.m_sInFile.EndsWith(".nll.def");
#line 229 "../../../Source/Core/Project.nll"
				while (pTranslationUnit.m_pTokenContainer.m_pTokenVector.GetSize() > 0)
				{
#line 231 "../../../Source/Core/Project.nll"
					Token pToken = pTranslationUnit.m_pTokenContainer.m_pTokenVector.PopFront();
#line 232 "../../../Source/Core/Project.nll"
					pToken.m_sFileName = pPublicTranslationUnit.m_sInFile;
					NumbatLogic.Token __3778855881 = pToken;
#line 233 "../../../Source/Core/Project.nll"
					pToken = null;
#line 233 "../../../Source/Core/Project.nll"
					pPublicTranslationUnit.m_pTokenContainer.m_pTokenVector.PushBack(__3778855881);
				}
#line 236 "../../../Source/Core/Project.nll"
				if (pPublicTranslationUnit.m_pFirstChild == null)
				{
					NumbatLogic.AST __4061733424 = pAST.m_pFirstChild;
#line 238 "../../../Source/Core/Project.nll"
					pAST.m_pFirstChild = null;
#line 238 "../../../Source/Core/Project.nll"
					pPublicTranslationUnit.m_pFirstChild = __4061733424;
#line 239 "../../../Source/Core/Project.nll"
					pPublicTranslationUnit.m_pLastChild = pPublicTranslationUnit.m_pFirstChild;
				}
				else
				{
					NumbatLogic.AST __4061799018 = pAST.m_pFirstChild;
#line 243 "../../../Source/Core/Project.nll"
					pAST.m_pFirstChild = null;
#line 243 "../../../Source/Core/Project.nll"
					pPublicTranslationUnit.m_pLastChild.m_pNextSibling = __4061799018;
#line 244 "../../../Source/Core/Project.nll"
					pPublicTranslationUnit.m_pLastChild = pPublicTranslationUnit.m_pLastChild.m_pNextSibling;
				}
#line 247 "../../../Source/Core/Project.nll"
				while (true)
				{
#line 249 "../../../Source/Core/Project.nll"
					pPublicTranslationUnit.m_pLastChild.m_pParent = pPublicTranslationUnit;
#line 250 "../../../Source/Core/Project.nll"
					pPublicTranslationUnit.m_pLastChild.m_bSkipOutput = bSkipOutput;
#line 252 "../../../Source/Core/Project.nll"
					if (pPublicTranslationUnit.m_pLastChild.m_pNextSibling == null)
#line 253 "../../../Source/Core/Project.nll"
						break;
#line 255 "../../../Source/Core/Project.nll"
					pPublicTranslationUnit.m_pLastChild = pPublicTranslationUnit.m_pLastChild.m_pNextSibling;
				}
			}
#line 259 "../../../Source/Core/Project.nll"
			while (m_pTranslationUnitVector.GetSize() > 0)
			{
#line 261 "../../../Source/Core/Project.nll"
				m_pTranslationUnitVector.PopBack();
			}
#line 264 "../../../Source/Core/Project.nll"
			NamespaceMerge(pPublicTranslationUnit);
#line 267 "../../../Source/Core/Project.nll"
			RecurseNamespaces(pPublicTranslationUnit, null, pSecretTranslationUnit);
#line 269 "../../../Source/Core/Project.nll"
			m_pTranslationUnitVector.PushBack(pSecretTranslationUnit);
			NumbatLogic.TranslationUnit __1635259254 = pSecretTranslationUnit;
#line 270 "../../../Source/Core/Project.nll"
			pSecretTranslationUnit = null;
#line 270 "../../../Source/Core/Project.nll"
			AddChild(__1635259254);
#line 272 "../../../Source/Core/Project.nll"
			m_pTranslationUnitVector.PushBack(pPublicTranslationUnit);
			NumbatLogic.TranslationUnit __623321714 = pPublicTranslationUnit;
#line 273 "../../../Source/Core/Project.nll"
			pPublicTranslationUnit = null;
#line 273 "../../../Source/Core/Project.nll"
			AddChild(__623321714);
		}

#line 276 "../../../Source/Core/Project.nll"
		public void Output(AST.Language eLanguage, OutputFile eOutputFile)
		{
#line 278 "../../../Source/Core/Project.nll"
			InternalString sOutFile = new InternalString("");
#line 279 "../../../Source/Core/Project.nll"
			OutputBuilder pOut = new OutputBuilder();
#line 282 "../../../Source/Core/Project.nll"
			for (int i = 0; i < m_pTranslationUnitVector.GetSize(); i++)
			{
#line 284 "../../../Source/Core/Project.nll"
				TranslationUnit pTranslationUnit = m_pTranslationUnitVector.Get(i);
#line 285 "../../../Source/Core/Project.nll"
				sOutFile.Set(pTranslationUnit.m_sInFile.GetExternalString());
#line 287 "../../../Source/Core/Project.nll"
				if (sOutFile.EndsWith(".nll"))
				{
#line 289 "../../../Source/Core/Project.nll"
					TranslationUnit.ConvertFilePath(eLanguage, eOutputFile, sOutFile);
#line 291 "../../../Source/Core/Project.nll"
					string sxOutFile = sOutFile.GetExternalString();
#line 293 "../../../Source/Core/Project.nll"
					pOut.m_sOut.Set("");
#line 294 "../../../Source/Core/Project.nll"
					pTranslationUnit.Stringify(eLanguage, eOutputFile, 0, pOut);
#line 296 "../../../Source/Core/Project.nll"
					InternalString sDirectory = File.GetFileDirectory(sxOutFile);
#line 297 "../../../Source/Core/Project.nll"
					File.CreateDirectory(sDirectory.GetExternalString());
#line 300 "../../../Source/Core/Project.nll"
					InternalString sTestFile = File.GetContents(sxOutFile);
#line 301 "../../../Source/Core/Project.nll"
					if (sTestFile == null || !pOut.m_sOut.IsEqual(sTestFile.GetExternalString()))
					{
#line 303 "../../../Source/Core/Project.nll"
						File.PutContents(sxOutFile, pOut.m_sOut.GetExternalString());
					}
				}
			}
		}

#line 3 "../../../Source/Core/Project.nll"
		~Project()
		{
		}

	}
}

