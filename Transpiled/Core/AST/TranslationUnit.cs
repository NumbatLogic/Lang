#line 1 "../../../Source/Core/AST/TranslationUnit.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/TranslationUnit.nll"
	class ClassDeclReference
	{
#line 6 "../../../Source/Core/AST/TranslationUnit.nll"
		public ClassDecl m_pClassDecl;
#line 7 "../../../Source/Core/AST/TranslationUnit.nll"
		public AST.OutputFile m_eOutputFile;
#line 8 "../../../Source/Core/AST/TranslationUnit.nll"
		public bool m_bForwardReference;
#line 4 "../../../Source/Core/AST/TranslationUnit.nll"
		public ClassDeclReference()
		{
		}

	}
#line 11 "../../../Source/Core/AST/TranslationUnit.nll"
	class ReferenceNode
	{
#line 13 "../../../Source/Core/AST/TranslationUnit.nll"
		public InternalString m_sName;
#line 14 "../../../Source/Core/AST/TranslationUnit.nll"
		public OwnedVector<ReferenceNode> m_pChildNodeVector;
#line 15 "../../../Source/Core/AST/TranslationUnit.nll"
		public Vector<ClassDeclReference> m_pChildClassVector;
#line 17 "../../../Source/Core/AST/TranslationUnit.nll"
		public ReferenceNode(string sxName)
		{
#line 19 "../../../Source/Core/AST/TranslationUnit.nll"
			m_sName = new InternalString(sxName);
#line 20 "../../../Source/Core/AST/TranslationUnit.nll"
			m_pChildNodeVector = new OwnedVector<ReferenceNode>();
#line 21 "../../../Source/Core/AST/TranslationUnit.nll"
			m_pChildClassVector = new Vector<ClassDeclReference>();
		}

#line 24 "../../../Source/Core/AST/TranslationUnit.nll"
		public ReferenceNode GetOrCreateChildNode(string sxName)
		{
			ReferenceNode pChild;
#line 27 "../../../Source/Core/AST/TranslationUnit.nll"
			for (int i = 0; i < m_pChildNodeVector.GetSize(); i++)
			{
#line 29 "../../../Source/Core/AST/TranslationUnit.nll"
				pChild = m_pChildNodeVector.Get(i);
#line 30 "../../../Source/Core/AST/TranslationUnit.nll"
				if (pChild.m_sName.IsEqual(sxName))
#line 31 "../../../Source/Core/AST/TranslationUnit.nll"
					return pChild;
			}
			ReferenceNode pCreatedChild = new ReferenceNode(sxName);
#line 35 "../../../Source/Core/AST/TranslationUnit.nll"
			pChild = pCreatedChild;
			NumbatLogic.ReferenceNode __2217859494 = pCreatedChild;
#line 36 "../../../Source/Core/AST/TranslationUnit.nll"
			pCreatedChild = null;
#line 36 "../../../Source/Core/AST/TranslationUnit.nll"
			m_pChildNodeVector.PushBack(__2217859494);
#line 37 "../../../Source/Core/AST/TranslationUnit.nll"
			return pChild;
		}

#line 40 "../../../Source/Core/AST/TranslationUnit.nll"
		public void Stringify(AST.Language eLanguage, AST.OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 42 "../../../Source/Core/AST/TranslationUnit.nll"
			if (!m_sName.IsEqual(""))
			{
#line 44 "../../../Source/Core/AST/TranslationUnit.nll"
				Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 45 "../../../Source/Core/AST/TranslationUnit.nll"
				pOutputBuilder.m_sOut.Append("namespace ");
#line 46 "../../../Source/Core/AST/TranslationUnit.nll"
				pOutputBuilder.m_sOut.Append(m_sName.GetExternalString());
#line 47 "../../../Source/Core/AST/TranslationUnit.nll"
				pOutputBuilder.m_sOut.Append("\n");
#line 48 "../../../Source/Core/AST/TranslationUnit.nll"
				Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 49 "../../../Source/Core/AST/TranslationUnit.nll"
				pOutputBuilder.m_sOut.Append("{\n");
#line 50 "../../../Source/Core/AST/TranslationUnit.nll"
				nDepth++;
			}
#line 53 "../../../Source/Core/AST/TranslationUnit.nll"
			for (int i = 0; i < m_pChildNodeVector.GetSize(); i++)
			{
				ReferenceNode pChild = m_pChildNodeVector.Get(i);
#line 56 "../../../Source/Core/AST/TranslationUnit.nll"
				pChild.Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
			}
#line 59 "../../../Source/Core/AST/TranslationUnit.nll"
			for (int i = 0; i < m_pChildClassVector.GetSize(); i++)
			{
				ClassDeclReference pChild = m_pChildClassVector.Get(i);
#line 62 "../../../Source/Core/AST/TranslationUnit.nll"
				if (pChild.m_pClassDecl.m_pGenericTypeDeclVector.GetSize() > 0)
				{
#line 64 "../../../Source/Core/AST/TranslationUnit.nll"
					Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 65 "../../../Source/Core/AST/TranslationUnit.nll"
					pChild.m_pClassDecl.StringifyTemplateThing(eLanguage, eOutputFile, pOutputBuilder);
#line 66 "../../../Source/Core/AST/TranslationUnit.nll"
					pOutputBuilder.m_sOut.Append("\n");
				}
#line 69 "../../../Source/Core/AST/TranslationUnit.nll"
				Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 70 "../../../Source/Core/AST/TranslationUnit.nll"
				pOutputBuilder.m_sOut.Append("class ");
#line 71 "../../../Source/Core/AST/TranslationUnit.nll"
				pChild.m_pClassDecl.m_pNameToken.Stringify(pOutputBuilder.m_sOut);
#line 72 "../../../Source/Core/AST/TranslationUnit.nll"
				pOutputBuilder.m_sOut.Append(";\n");
			}
#line 75 "../../../Source/Core/AST/TranslationUnit.nll"
			if (!m_sName.IsEqual(""))
			{
#line 77 "../../../Source/Core/AST/TranslationUnit.nll"
				nDepth--;
#line 78 "../../../Source/Core/AST/TranslationUnit.nll"
				Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 79 "../../../Source/Core/AST/TranslationUnit.nll"
				pOutputBuilder.m_sOut.Append("}\n");
			}
		}

#line 11 "../../../Source/Core/AST/TranslationUnit.nll"
		~ReferenceNode()
		{
		}

	}
#line 84 "../../../Source/Core/AST/TranslationUnit.nll"
	class TranslationUnit : AST
	{
#line 86 "../../../Source/Core/AST/TranslationUnit.nll"
		public InternalString m_sInFile;
#line 87 "../../../Source/Core/AST/TranslationUnit.nll"
		public TokenContainer m_pTokenContainer;
#line 88 "../../../Source/Core/AST/TranslationUnit.nll"
		public OwnedVector<ClassDeclReference> m_pClassDeclReferenceVector;
#line 90 "../../../Source/Core/AST/TranslationUnit.nll"
		public TranslationUnit(string sInFile)
		{
#line 92 "../../../Source/Core/AST/TranslationUnit.nll"
			m_sInFile = new InternalString(sInFile);
#line 93 "../../../Source/Core/AST/TranslationUnit.nll"
			m_eType = Type.AST_TRANSLATION_UNIT;
#line 94 "../../../Source/Core/AST/TranslationUnit.nll"
			m_bCanDescend = true;
#line 96 "../../../Source/Core/AST/TranslationUnit.nll"
			m_pTokenContainer = new TokenContainer();
#line 97 "../../../Source/Core/AST/TranslationUnit.nll"
			m_pClassDeclReferenceVector = new OwnedVector<ClassDeclReference>();
		}

#line 100 "../../../Source/Core/AST/TranslationUnit.nll"
		public static TranslationUnit Create(string sInFile, OwnedVector<InternalString> sDefineVector)
		{
			TranslationUnit pThis = new TranslationUnit(sInFile);
			InternalString sInput = File.GetContents(pThis.m_sInFile.GetExternalString());
#line 107 "../../../Source/Core/AST/TranslationUnit.nll"
			pThis.m_pTokenContainer.Tokenize(sInput.GetExternalString(), pThis.m_sInFile, sDefineVector);
#line 108 "../../../Source/Core/AST/TranslationUnit.nll"
			pThis.m_pTokenContainer.StripWhitespace();
			OffsetDatum pOffsetDatum = OffsetDatum.Create(null);
#line 113 "../../../Source/Core/AST/TranslationUnit.nll"
			while (pOffsetDatum.m_nOffset < pThis.m_pTokenContainer.m_pTokenVector.GetSize())
			{
				AST pAST = AST.CreateFromTokenContainer(pThis.m_pTokenContainer, pOffsetDatum);
#line 116 "../../../Source/Core/AST/TranslationUnit.nll"
				if (pAST == null)
				{
#line 117 "../../../Source/Core/AST/TranslationUnit.nll"
					break;
				}
				NumbatLogic.AST __3057539430 = pAST;
#line 119 "../../../Source/Core/AST/TranslationUnit.nll"
				pAST = null;
#line 119 "../../../Source/Core/AST/TranslationUnit.nll"
				pThis.AddChild(__3057539430);
			}
			NumbatLogic.TranslationUnit __2058438882 = pThis;
#line 122 "../../../Source/Core/AST/TranslationUnit.nll"
			pThis = null;
#line 122 "../../../Source/Core/AST/TranslationUnit.nll"
			return __2058438882;
		}

#line 125 "../../../Source/Core/AST/TranslationUnit.nll"
		public override void AddClassDeclReference(ClassDecl pClassDecl, OutputFile eOutputFile, bool bForwardReference)
		{
#line 127 "../../../Source/Core/AST/TranslationUnit.nll"
			for (int i = 0; i < m_pClassDeclReferenceVector.GetSize(); i++)
			{
				ClassDeclReference pTestClassDeclReference = m_pClassDeclReferenceVector.Get(i);
#line 130 "../../../Source/Core/AST/TranslationUnit.nll"
				if (pTestClassDeclReference.m_pClassDecl == pClassDecl && pTestClassDeclReference.m_eOutputFile == eOutputFile)
				{
#line 137 "../../../Source/Core/AST/TranslationUnit.nll"
					if (pTestClassDeclReference.m_bForwardReference == bForwardReference)
					{
#line 139 "../../../Source/Core/AST/TranslationUnit.nll"
						base.AddClassDeclReference(pClassDecl, eOutputFile, bForwardReference);
#line 140 "../../../Source/Core/AST/TranslationUnit.nll"
						return;
					}
				}
			}
			ClassDeclReference pClassDeclReference = new ClassDeclReference();
#line 146 "../../../Source/Core/AST/TranslationUnit.nll"
			pClassDeclReference.m_pClassDecl = pClassDecl;
#line 147 "../../../Source/Core/AST/TranslationUnit.nll"
			pClassDeclReference.m_eOutputFile = eOutputFile;
#line 148 "../../../Source/Core/AST/TranslationUnit.nll"
			pClassDeclReference.m_bForwardReference = bForwardReference;
			NumbatLogic.ClassDeclReference __3931805821 = pClassDeclReference;
#line 150 "../../../Source/Core/AST/TranslationUnit.nll"
			pClassDeclReference = null;
#line 150 "../../../Source/Core/AST/TranslationUnit.nll"
			m_pClassDeclReferenceVector.PushBack(__3931805821);
#line 152 "../../../Source/Core/AST/TranslationUnit.nll"
			base.AddClassDeclReference(pClassDecl, eOutputFile, bForwardReference);
		}

#line 155 "../../../Source/Core/AST/TranslationUnit.nll"
		public static void ConvertFilePath(Language eLanguage, OutputFile eOutputFile, InternalString sPath)
		{
#line 158 "../../../Source/Core/AST/TranslationUnit.nll"
			if (sPath.EndsWith(".nll.def"))
			{
				InternalString sFolder = new InternalString("");
				InternalString sFile = sPath.CreateClone();
#line 163 "../../../Source/Core/AST/TranslationUnit.nll"
				while (true)
				{
					int nIndex = sFile.FindChar('/');
#line 166 "../../../Source/Core/AST/TranslationUnit.nll"
					if (nIndex == -1)
#line 167 "../../../Source/Core/AST/TranslationUnit.nll"
						break;
					InternalString sTemp = sFile.CreateClone();
#line 170 "../../../Source/Core/AST/TranslationUnit.nll"
					sTemp.SubStr(0, nIndex + 1);
#line 171 "../../../Source/Core/AST/TranslationUnit.nll"
					sFolder.Append(sTemp.GetExternalString());
#line 172 "../../../Source/Core/AST/TranslationUnit.nll"
					sFile.CropFront(nIndex + 1);
				}
#line 175 "../../../Source/Core/AST/TranslationUnit.nll"
				switch (eLanguage)
				{
					case AST.Language.CS:
					{
#line 179 "../../../Source/Core/AST/TranslationUnit.nll"
						sFolder.Append("CS/");
#line 180 "../../../Source/Core/AST/TranslationUnit.nll"
						sFile.Replace(".nll.def", ".cs");
#line 181 "../../../Source/Core/AST/TranslationUnit.nll"
						break;
					}

					case AST.Language.CPP:
					{
#line 185 "../../../Source/Core/AST/TranslationUnit.nll"
						sFolder.Append("CPP/");
#line 186 "../../../Source/Core/AST/TranslationUnit.nll"
						if (eOutputFile == AST.OutputFile.SOURCE)
#line 187 "../../../Source/Core/AST/TranslationUnit.nll"
							sFile.Replace(".nll.def", ".cpp");
						else
#line 189 "../../../Source/Core/AST/TranslationUnit.nll"
							sFile.Replace(".nll.def", ".hpp");
#line 190 "../../../Source/Core/AST/TranslationUnit.nll"
						break;
					}

					case AST.Language.NLL:
					{
#line 194 "../../../Source/Core/AST/TranslationUnit.nll"
						break;
					}

					case AST.Language.NLL_DEF:
					{
#line 198 "../../../Source/Core/AST/TranslationUnit.nll"
						break;
					}

				}
#line 202 "../../../Source/Core/AST/TranslationUnit.nll"
				sPath.Set(sFolder.GetExternalString());
#line 203 "../../../Source/Core/AST/TranslationUnit.nll"
				sPath.Append(sFile.GetExternalString());
#line 204 "../../../Source/Core/AST/TranslationUnit.nll"
				return;
			}
#line 208 "../../../Source/Core/AST/TranslationUnit.nll"
			sPath.Replace("Source", "Transpiled");
#line 211 "../../../Source/Core/AST/TranslationUnit.nll"
			switch (eLanguage)
			{
				case AST.Language.CS:
				{
#line 215 "../../../Source/Core/AST/TranslationUnit.nll"
					sPath.Replace(".nll", ".cs");
#line 216 "../../../Source/Core/AST/TranslationUnit.nll"
					break;
				}

				case AST.Language.CPP:
				{
#line 220 "../../../Source/Core/AST/TranslationUnit.nll"
					if (eOutputFile == AST.OutputFile.SOURCE)
#line 221 "../../../Source/Core/AST/TranslationUnit.nll"
						sPath.Replace(".nll", ".cpp");
					else
#line 223 "../../../Source/Core/AST/TranslationUnit.nll"
						sPath.Replace(".nll", ".hpp");
#line 224 "../../../Source/Core/AST/TranslationUnit.nll"
					break;
				}

				case AST.Language.NLL:
				{
#line 228 "../../../Source/Core/AST/TranslationUnit.nll"
					break;
				}

				case AST.Language.NLL_DEF:
				{
#line 232 "../../../Source/Core/AST/TranslationUnit.nll"
					sPath.Replace(".nll", ".nll.def");
#line 233 "../../../Source/Core/AST/TranslationUnit.nll"
					break;
				}

			}
		}

#line 238 "../../../Source/Core/AST/TranslationUnit.nll"
		public InternalString RetargetRelativePath(Language eLanguage, OutputFile eOutputFile, string sxFrom, string sxTo)
		{
			InternalString sFrom = new InternalString(sxFrom);
			InternalString sTo = new InternalString(sxTo);
#line 243 "../../../Source/Core/AST/TranslationUnit.nll"
			ConvertFilePath(eLanguage, eOutputFile, sFrom);
#line 244 "../../../Source/Core/AST/TranslationUnit.nll"
			ConvertFilePath(eLanguage, eOutputFile, sTo);
			OwnedVector<InternalString> sFromVector = new OwnedVector<InternalString>();
			OwnedVector<InternalString> sToVector = new OwnedVector<InternalString>();
#line 249 "../../../Source/Core/AST/TranslationUnit.nll"
			while (true)
			{
				int nIndex = sFrom.FindChar('/');
#line 252 "../../../Source/Core/AST/TranslationUnit.nll"
				if (nIndex == -1)
#line 253 "../../../Source/Core/AST/TranslationUnit.nll"
					break;
				InternalString sTemp = sFrom.CreateClone();
#line 256 "../../../Source/Core/AST/TranslationUnit.nll"
				sTemp.SubStr(0, nIndex + 1);
#line 257 "../../../Source/Core/AST/TranslationUnit.nll"
				sFrom.CropFront(nIndex + 1);
				NumbatLogic.InternalString __2784973933 = sTemp;
#line 258 "../../../Source/Core/AST/TranslationUnit.nll"
				sTemp = null;
#line 258 "../../../Source/Core/AST/TranslationUnit.nll"
				sFromVector.PushBack(__2784973933);
			}
#line 261 "../../../Source/Core/AST/TranslationUnit.nll"
			while (true)
			{
				int nIndex = sTo.FindChar('/');
#line 264 "../../../Source/Core/AST/TranslationUnit.nll"
				if (nIndex == -1)
#line 265 "../../../Source/Core/AST/TranslationUnit.nll"
					break;
				InternalString sTemp = sTo.CreateClone();
#line 268 "../../../Source/Core/AST/TranslationUnit.nll"
				sTemp.SubStr(0, nIndex + 1);
#line 269 "../../../Source/Core/AST/TranslationUnit.nll"
				sTo.CropFront(nIndex + 1);
				NumbatLogic.InternalString __2785039534 = sTemp;
#line 270 "../../../Source/Core/AST/TranslationUnit.nll"
				sTemp = null;
#line 270 "../../../Source/Core/AST/TranslationUnit.nll"
				sToVector.PushBack(__2785039534);
			}
#line 274 "../../../Source/Core/AST/TranslationUnit.nll"
			while (true)
			{
#line 276 "../../../Source/Core/AST/TranslationUnit.nll"
				if (sFromVector.GetSize() == 0 || sToVector.GetSize() == 0)
#line 277 "../../../Source/Core/AST/TranslationUnit.nll"
					break;
#line 279 "../../../Source/Core/AST/TranslationUnit.nll"
				if (!sFromVector.Get(0).IsEqual(sToVector.Get(0).GetExternalString()))
#line 280 "../../../Source/Core/AST/TranslationUnit.nll"
					break;
#line 282 "../../../Source/Core/AST/TranslationUnit.nll"
				sFromVector.Erase(0);
#line 283 "../../../Source/Core/AST/TranslationUnit.nll"
				sToVector.Erase(0);
			}
			InternalString sOut = new InternalString("");
#line 288 "../../../Source/Core/AST/TranslationUnit.nll"
			for (int i = 0; i < sFromVector.GetSize(); i++)
#line 289 "../../../Source/Core/AST/TranslationUnit.nll"
				sOut.Append("../");
#line 290 "../../../Source/Core/AST/TranslationUnit.nll"
			for (int i = 0; i < sToVector.GetSize(); i++)
#line 291 "../../../Source/Core/AST/TranslationUnit.nll"
				sOut.Append(sToVector.Get(i).GetExternalString());
#line 293 "../../../Source/Core/AST/TranslationUnit.nll"
			sOut.Append(sTo.GetExternalString());
			NumbatLogic.InternalString __1173437905 = sOut;
#line 294 "../../../Source/Core/AST/TranslationUnit.nll"
			sOut = null;
#line 294 "../../../Source/Core/AST/TranslationUnit.nll"
			return __1173437905;
		}

#line 297 "../../../Source/Core/AST/TranslationUnit.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 299 "../../../Source/Core/AST/TranslationUnit.nll"
			if (eLanguage == AST.Language.CPP)
			{
#line 301 "../../../Source/Core/AST/TranslationUnit.nll"
				if (eOutputFile == AST.OutputFile.HEADER)
				{
#line 303 "../../../Source/Core/AST/TranslationUnit.nll"
					pOutputBuilder.m_sOut.Append("#pragma once\n\n");
				}
				OwnedVector<InternalString> sPreviousIncludes = new OwnedVector<InternalString>();
				ReferenceNode pRootReferenceNode = new ReferenceNode("");
#line 309 "../../../Source/Core/AST/TranslationUnit.nll"
				for (int i = 0; i < m_pClassDeclReferenceVector.GetSize(); i++)
				{
					ClassDeclReference pClassDeclReference = m_pClassDeclReferenceVector.Get(i);
#line 312 "../../../Source/Core/AST/TranslationUnit.nll"
					if (eOutputFile == pClassDeclReference.m_eOutputFile)
					{
						bool bOnlyInclude = !pClassDeclReference.m_bForwardReference;
#line 319 "../../../Source/Core/AST/TranslationUnit.nll"
						if (bOnlyInclude)
						{
#line 321 "../../../Source/Core/AST/TranslationUnit.nll"
							for (int j = 0; j < m_pClassDeclReferenceVector.GetSize(); j++)
							{
								ClassDeclReference pTestClassDeclReference = m_pClassDeclReferenceVector.Get(j);
#line 324 "../../../Source/Core/AST/TranslationUnit.nll"
								if (pTestClassDeclReference.m_pClassDecl == pClassDeclReference.m_pClassDecl)
								{
#line 326 "../../../Source/Core/AST/TranslationUnit.nll"
									if (pTestClassDeclReference.m_eOutputFile == pClassDeclReference.m_eOutputFile)
									{
#line 328 "../../../Source/Core/AST/TranslationUnit.nll"
										if (pTestClassDeclReference.m_bForwardReference)
										{
#line 330 "../../../Source/Core/AST/TranslationUnit.nll"
											bOnlyInclude = false;
#line 331 "../../../Source/Core/AST/TranslationUnit.nll"
											break;
										}
									}
								}
							}
						}
#line 338 "../../../Source/Core/AST/TranslationUnit.nll"
						if (pClassDeclReference.m_bForwardReference || bOnlyInclude)
						{
							Vector<InternalString> sNamespaceVector = new Vector<InternalString>();
							NamespaceNode pNamespaceNode = pClassDeclReference.m_pClassDecl.m_pNamespaceNode;
#line 342 "../../../Source/Core/AST/TranslationUnit.nll"
							while (pNamespaceNode != null && pNamespaceNode.m_sName != null)
							{
#line 344 "../../../Source/Core/AST/TranslationUnit.nll"
								sNamespaceVector.PushFront(pNamespaceNode.m_sName);
#line 345 "../../../Source/Core/AST/TranslationUnit.nll"
								pNamespaceNode = pNamespaceNode.m_pParent;
							}
							ReferenceNode pCurrentNode = pRootReferenceNode;
#line 350 "../../../Source/Core/AST/TranslationUnit.nll"
							for (int j = 0; j < sNamespaceVector.GetSize(); j++)
							{
								InternalString sNamespace = sNamespaceVector.Get(j);
#line 353 "../../../Source/Core/AST/TranslationUnit.nll"
								pCurrentNode = pCurrentNode.GetOrCreateChildNode(sNamespace.GetExternalString());
							}
#line 356 "../../../Source/Core/AST/TranslationUnit.nll"
							pCurrentNode.m_pChildClassVector.PushBack(pClassDeclReference);
						}
#line 359 "../../../Source/Core/AST/TranslationUnit.nll"
						if (!pClassDeclReference.m_bForwardReference)
						{
							bool bFound = false;
#line 362 "../../../Source/Core/AST/TranslationUnit.nll"
							for (int j = 0; j < sPreviousIncludes.GetSize(); j++)
							{
								InternalString sTemp = sPreviousIncludes.Get(j);
#line 365 "../../../Source/Core/AST/TranslationUnit.nll"
								if (sTemp.IsEqual(pClassDeclReference.m_pClassDecl.m_pNameToken.m_sFileName.GetExternalString()))
								{
#line 367 "../../../Source/Core/AST/TranslationUnit.nll"
									bFound = true;
#line 368 "../../../Source/Core/AST/TranslationUnit.nll"
									break;
								}
							}
#line 371 "../../../Source/Core/AST/TranslationUnit.nll"
							if (bFound)
#line 372 "../../../Source/Core/AST/TranslationUnit.nll"
								continue;
#line 373 "../../../Source/Core/AST/TranslationUnit.nll"
							sPreviousIncludes.PushBack(new InternalString(pClassDeclReference.m_pClassDecl.m_pNameToken.m_sFileName.GetExternalString()));
							InternalString sFixedPath = RetargetRelativePath(eLanguage, AST.OutputFile.HEADER, m_pFirstChild.m_pFirstToken.m_sFileName.GetExternalString(), pClassDeclReference.m_pClassDecl.m_pNameToken.m_sFileName.GetExternalString());
#line 376 "../../../Source/Core/AST/TranslationUnit.nll"
							pOutputBuilder.m_sOut.Append("#include \"");
#line 377 "../../../Source/Core/AST/TranslationUnit.nll"
							pOutputBuilder.m_sOut.Append(sFixedPath.GetExternalString());
#line 378 "../../../Source/Core/AST/TranslationUnit.nll"
							pOutputBuilder.m_sOut.Append("\"\n");
						}
					}
				}
#line 383 "../../../Source/Core/AST/TranslationUnit.nll"
				if (sPreviousIncludes.GetSize() > 0)
#line 384 "../../../Source/Core/AST/TranslationUnit.nll"
					pOutputBuilder.m_sOut.Append("\n");
#line 385 "../../../Source/Core/AST/TranslationUnit.nll"
				pRootReferenceNode.Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
			}
			AST pChild = m_pFirstChild;
#line 389 "../../../Source/Core/AST/TranslationUnit.nll"
			while (pChild != null)
			{
#line 391 "../../../Source/Core/AST/TranslationUnit.nll"
				if (!pChild.m_bSkipOutput)
				{
#line 393 "../../../Source/Core/AST/TranslationUnit.nll"
					pChild.Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
#line 394 "../../../Source/Core/AST/TranslationUnit.nll"
					pOutputBuilder.m_sOut.AppendChar('\n');
				}
#line 396 "../../../Source/Core/AST/TranslationUnit.nll"
				pChild = pChild.m_pNextSibling;
			}
		}

#line 84 "../../../Source/Core/AST/TranslationUnit.nll"
		~TranslationUnit()
		{
		}

	}
}

