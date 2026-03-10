#line 1 "../../../Source/Core/AST/TranslationUnit.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/TranslationUnit.nll"
	class ClassDeclReference
	{
#line 5 "../../../Source/Core/AST/TranslationUnit.nll"
		public ClassDecl m_pClassDecl;
#line 6 "../../../Source/Core/AST/TranslationUnit.nll"
		public AST.OutputFile m_eOutputFile;
#line 7 "../../../Source/Core/AST/TranslationUnit.nll"
		public bool m_bForwardReference;
#line 3 "../../../Source/Core/AST/TranslationUnit.nll"
		public ClassDeclReference()
		{
		}

	}
#line 10 "../../../Source/Core/AST/TranslationUnit.nll"
	class ReferenceNode
	{
#line 12 "../../../Source/Core/AST/TranslationUnit.nll"
		public InternalString m_sName;
#line 13 "../../../Source/Core/AST/TranslationUnit.nll"
		public OwnedVector<ReferenceNode> m_pChildNodeVector;
#line 14 "../../../Source/Core/AST/TranslationUnit.nll"
		public Vector<ClassDeclReference> m_pChildClassVector;
#line 16 "../../../Source/Core/AST/TranslationUnit.nll"
		public ReferenceNode(string sxName)
		{
#line 18 "../../../Source/Core/AST/TranslationUnit.nll"
			m_sName = new InternalString(sxName);
#line 19 "../../../Source/Core/AST/TranslationUnit.nll"
			m_pChildNodeVector = new OwnedVector<ReferenceNode>();
#line 20 "../../../Source/Core/AST/TranslationUnit.nll"
			m_pChildClassVector = new Vector<ClassDeclReference>();
		}

#line 23 "../../../Source/Core/AST/TranslationUnit.nll"
		public ReferenceNode GetOrCreateChildNode(string sxName)
		{
#line 25 "../../../Source/Core/AST/TranslationUnit.nll"
			ReferenceNode pChild;
#line 26 "../../../Source/Core/AST/TranslationUnit.nll"
			for (int i = 0; i < m_pChildNodeVector.GetSize(); i++)
			{
#line 28 "../../../Source/Core/AST/TranslationUnit.nll"
				pChild = m_pChildNodeVector.Get(i);
#line 29 "../../../Source/Core/AST/TranslationUnit.nll"
				if (pChild.m_sName.IsEqual(sxName))
#line 30 "../../../Source/Core/AST/TranslationUnit.nll"
					return pChild;
			}
#line 33 "../../../Source/Core/AST/TranslationUnit.nll"
			ReferenceNode pCreatedChild = new ReferenceNode(sxName);
#line 34 "../../../Source/Core/AST/TranslationUnit.nll"
			pChild = pCreatedChild;
			NumbatLogic.ReferenceNode __2217859494 = pCreatedChild;
#line 35 "../../../Source/Core/AST/TranslationUnit.nll"
			pCreatedChild = null;
#line 35 "../../../Source/Core/AST/TranslationUnit.nll"
			m_pChildNodeVector.PushBack(__2217859494);
#line 36 "../../../Source/Core/AST/TranslationUnit.nll"
			return pChild;
		}

#line 39 "../../../Source/Core/AST/TranslationUnit.nll"
		public void Stringify(AST.Language eLanguage, AST.OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 41 "../../../Source/Core/AST/TranslationUnit.nll"
			if (!m_sName.IsEqual(""))
			{
#line 43 "../../../Source/Core/AST/TranslationUnit.nll"
				Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 44 "../../../Source/Core/AST/TranslationUnit.nll"
				pOutputBuilder.m_sOut.Append("namespace ");
#line 45 "../../../Source/Core/AST/TranslationUnit.nll"
				pOutputBuilder.m_sOut.Append(m_sName.GetExternalString());
#line 46 "../../../Source/Core/AST/TranslationUnit.nll"
				pOutputBuilder.m_sOut.Append("\n");
#line 47 "../../../Source/Core/AST/TranslationUnit.nll"
				Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 48 "../../../Source/Core/AST/TranslationUnit.nll"
				pOutputBuilder.m_sOut.Append("{\n");
#line 49 "../../../Source/Core/AST/TranslationUnit.nll"
				nDepth++;
			}
#line 52 "../../../Source/Core/AST/TranslationUnit.nll"
			for (int i = 0; i < m_pChildNodeVector.GetSize(); i++)
			{
#line 54 "../../../Source/Core/AST/TranslationUnit.nll"
				ReferenceNode pChild = m_pChildNodeVector.Get(i);
#line 55 "../../../Source/Core/AST/TranslationUnit.nll"
				pChild.Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
			}
#line 58 "../../../Source/Core/AST/TranslationUnit.nll"
			for (int i = 0; i < m_pChildClassVector.GetSize(); i++)
			{
#line 60 "../../../Source/Core/AST/TranslationUnit.nll"
				ClassDeclReference pChild = m_pChildClassVector.Get(i);
#line 61 "../../../Source/Core/AST/TranslationUnit.nll"
				if (pChild.m_pClassDecl.m_pGenericTypeDeclVector.GetSize() > 0)
				{
#line 63 "../../../Source/Core/AST/TranslationUnit.nll"
					Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 64 "../../../Source/Core/AST/TranslationUnit.nll"
					pChild.m_pClassDecl.StringifyTemplateThing(eLanguage, eOutputFile, pOutputBuilder);
#line 65 "../../../Source/Core/AST/TranslationUnit.nll"
					pOutputBuilder.m_sOut.Append("\n");
				}
#line 68 "../../../Source/Core/AST/TranslationUnit.nll"
				Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 69 "../../../Source/Core/AST/TranslationUnit.nll"
				pOutputBuilder.m_sOut.Append("class ");
#line 70 "../../../Source/Core/AST/TranslationUnit.nll"
				pChild.m_pClassDecl.m_pNameToken.Stringify(pOutputBuilder.m_sOut);
#line 71 "../../../Source/Core/AST/TranslationUnit.nll"
				pOutputBuilder.m_sOut.Append(";\n");
			}
#line 74 "../../../Source/Core/AST/TranslationUnit.nll"
			if (!m_sName.IsEqual(""))
			{
#line 76 "../../../Source/Core/AST/TranslationUnit.nll"
				nDepth--;
#line 77 "../../../Source/Core/AST/TranslationUnit.nll"
				Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 78 "../../../Source/Core/AST/TranslationUnit.nll"
				pOutputBuilder.m_sOut.Append("}\n");
			}
		}

#line 10 "../../../Source/Core/AST/TranslationUnit.nll"
		~ReferenceNode()
		{
		}

	}
#line 83 "../../../Source/Core/AST/TranslationUnit.nll"
	class TranslationUnit : AST
	{
#line 85 "../../../Source/Core/AST/TranslationUnit.nll"
		public InternalString m_sInFile;
#line 86 "../../../Source/Core/AST/TranslationUnit.nll"
		public TokenContainer m_pTokenContainer;
#line 87 "../../../Source/Core/AST/TranslationUnit.nll"
		public OwnedVector<ClassDeclReference> m_pClassDeclReferenceVector;
#line 89 "../../../Source/Core/AST/TranslationUnit.nll"
		public TranslationUnit(string sInFile)
		{
#line 91 "../../../Source/Core/AST/TranslationUnit.nll"
			m_sInFile = new InternalString(sInFile);
#line 92 "../../../Source/Core/AST/TranslationUnit.nll"
			m_eType = Type.AST_TRANSLATION_UNIT;
#line 93 "../../../Source/Core/AST/TranslationUnit.nll"
			m_bCanDescend = true;
#line 95 "../../../Source/Core/AST/TranslationUnit.nll"
			m_pTokenContainer = new TokenContainer();
#line 96 "../../../Source/Core/AST/TranslationUnit.nll"
			m_pClassDeclReferenceVector = new OwnedVector<ClassDeclReference>();
		}

#line 99 "../../../Source/Core/AST/TranslationUnit.nll"
		public static TranslationUnit Create(string sInFile, OwnedVector<InternalString> sDefineVector)
		{
#line 101 "../../../Source/Core/AST/TranslationUnit.nll"
			TranslationUnit pThis = new TranslationUnit(sInFile);
#line 103 "../../../Source/Core/AST/TranslationUnit.nll"
			InternalString sInput = File.GetContents(pThis.m_sInFile.GetExternalString());
#line 106 "../../../Source/Core/AST/TranslationUnit.nll"
			pThis.m_pTokenContainer.Tokenize(sInput.GetExternalString(), pThis.m_sInFile, sDefineVector);
#line 107 "../../../Source/Core/AST/TranslationUnit.nll"
			pThis.m_pTokenContainer.StripWhitespace();
#line 109 "../../../Source/Core/AST/TranslationUnit.nll"
			OffsetDatum pOffsetDatum = OffsetDatum.Create(null);
#line 112 "../../../Source/Core/AST/TranslationUnit.nll"
			while (pOffsetDatum.m_nOffset < pThis.m_pTokenContainer.m_pTokenVector.GetSize())
			{
#line 114 "../../../Source/Core/AST/TranslationUnit.nll"
				AST pAST = AST.CreateFromTokenContainer(pThis.m_pTokenContainer, pOffsetDatum);
#line 115 "../../../Source/Core/AST/TranslationUnit.nll"
				if (pAST == null)
				{
#line 116 "../../../Source/Core/AST/TranslationUnit.nll"
					break;
				}
				NumbatLogic.AST __3057539430 = pAST;
#line 118 "../../../Source/Core/AST/TranslationUnit.nll"
				pAST = null;
#line 118 "../../../Source/Core/AST/TranslationUnit.nll"
				pThis.AddChild(__3057539430);
			}
			NumbatLogic.TranslationUnit __2058438882 = pThis;
#line 121 "../../../Source/Core/AST/TranslationUnit.nll"
			pThis = null;
#line 121 "../../../Source/Core/AST/TranslationUnit.nll"
			return __2058438882;
		}

#line 124 "../../../Source/Core/AST/TranslationUnit.nll"
		public override void AddClassDeclReference(ClassDecl pClassDecl, OutputFile eOutputFile, bool bForwardReference)
		{
#line 126 "../../../Source/Core/AST/TranslationUnit.nll"
			for (int i = 0; i < m_pClassDeclReferenceVector.GetSize(); i++)
			{
#line 128 "../../../Source/Core/AST/TranslationUnit.nll"
				ClassDeclReference pTestClassDeclReference = m_pClassDeclReferenceVector.Get(i);
#line 129 "../../../Source/Core/AST/TranslationUnit.nll"
				if (pTestClassDeclReference.m_pClassDecl == pClassDecl && pTestClassDeclReference.m_eOutputFile == eOutputFile)
				{
#line 136 "../../../Source/Core/AST/TranslationUnit.nll"
					if (pTestClassDeclReference.m_bForwardReference == bForwardReference)
					{
#line 138 "../../../Source/Core/AST/TranslationUnit.nll"
						base.AddClassDeclReference(pClassDecl, eOutputFile, bForwardReference);
#line 139 "../../../Source/Core/AST/TranslationUnit.nll"
						return;
					}
				}
			}
#line 144 "../../../Source/Core/AST/TranslationUnit.nll"
			ClassDeclReference pClassDeclReference = new ClassDeclReference();
#line 145 "../../../Source/Core/AST/TranslationUnit.nll"
			pClassDeclReference.m_pClassDecl = pClassDecl;
#line 146 "../../../Source/Core/AST/TranslationUnit.nll"
			pClassDeclReference.m_eOutputFile = eOutputFile;
#line 147 "../../../Source/Core/AST/TranslationUnit.nll"
			pClassDeclReference.m_bForwardReference = bForwardReference;
			NumbatLogic.ClassDeclReference __3931805821 = pClassDeclReference;
#line 149 "../../../Source/Core/AST/TranslationUnit.nll"
			pClassDeclReference = null;
#line 149 "../../../Source/Core/AST/TranslationUnit.nll"
			m_pClassDeclReferenceVector.PushBack(__3931805821);
#line 151 "../../../Source/Core/AST/TranslationUnit.nll"
			base.AddClassDeclReference(pClassDecl, eOutputFile, bForwardReference);
		}

#line 154 "../../../Source/Core/AST/TranslationUnit.nll"
		public static void ConvertFilePath(Language eLanguage, OutputFile eOutputFile, InternalString sPath)
		{
#line 157 "../../../Source/Core/AST/TranslationUnit.nll"
			if (sPath.EndsWith(".nll.def"))
			{
#line 159 "../../../Source/Core/AST/TranslationUnit.nll"
				InternalString sFolder = new InternalString("");
#line 160 "../../../Source/Core/AST/TranslationUnit.nll"
				InternalString sFile = sPath.CreateClone();
#line 162 "../../../Source/Core/AST/TranslationUnit.nll"
				while (true)
				{
#line 164 "../../../Source/Core/AST/TranslationUnit.nll"
					int nIndex = sFile.FindChar('/');
#line 165 "../../../Source/Core/AST/TranslationUnit.nll"
					if (nIndex == -1)
#line 166 "../../../Source/Core/AST/TranslationUnit.nll"
						break;
#line 168 "../../../Source/Core/AST/TranslationUnit.nll"
					InternalString sTemp = sFile.CreateClone();
#line 169 "../../../Source/Core/AST/TranslationUnit.nll"
					sTemp.SubStr(0, nIndex + 1);
#line 170 "../../../Source/Core/AST/TranslationUnit.nll"
					sFolder.Append(sTemp.GetExternalString());
#line 171 "../../../Source/Core/AST/TranslationUnit.nll"
					sFile.CropFront(nIndex + 1);
				}
#line 174 "../../../Source/Core/AST/TranslationUnit.nll"
				switch (eLanguage)
				{
					case AST.Language.CS:
					{
#line 178 "../../../Source/Core/AST/TranslationUnit.nll"
						sFolder.Append("CS/");
#line 179 "../../../Source/Core/AST/TranslationUnit.nll"
						sFile.Replace(".nll.def", ".cs");
#line 180 "../../../Source/Core/AST/TranslationUnit.nll"
						break;
					}

					case AST.Language.CPP:
					{
#line 184 "../../../Source/Core/AST/TranslationUnit.nll"
						sFolder.Append("CPP/");
#line 185 "../../../Source/Core/AST/TranslationUnit.nll"
						if (eOutputFile == AST.OutputFile.SOURCE)
#line 186 "../../../Source/Core/AST/TranslationUnit.nll"
							sFile.Replace(".nll.def", ".cpp");
						else
#line 188 "../../../Source/Core/AST/TranslationUnit.nll"
							sFile.Replace(".nll.def", ".hpp");
#line 189 "../../../Source/Core/AST/TranslationUnit.nll"
						break;
					}

					case AST.Language.NLL:
					{
#line 193 "../../../Source/Core/AST/TranslationUnit.nll"
						break;
					}

					case AST.Language.NLL_DEF:
					{
#line 197 "../../../Source/Core/AST/TranslationUnit.nll"
						break;
					}

				}
#line 201 "../../../Source/Core/AST/TranslationUnit.nll"
				sPath.Set(sFolder.GetExternalString());
#line 202 "../../../Source/Core/AST/TranslationUnit.nll"
				sPath.Append(sFile.GetExternalString());
#line 203 "../../../Source/Core/AST/TranslationUnit.nll"
				return;
			}
#line 207 "../../../Source/Core/AST/TranslationUnit.nll"
			sPath.Replace("Source", "Transpiled");
#line 210 "../../../Source/Core/AST/TranslationUnit.nll"
			switch (eLanguage)
			{
				case AST.Language.CS:
				{
#line 214 "../../../Source/Core/AST/TranslationUnit.nll"
					sPath.Replace(".nll", ".cs");
#line 215 "../../../Source/Core/AST/TranslationUnit.nll"
					break;
				}

				case AST.Language.CPP:
				{
#line 219 "../../../Source/Core/AST/TranslationUnit.nll"
					if (eOutputFile == AST.OutputFile.SOURCE)
#line 220 "../../../Source/Core/AST/TranslationUnit.nll"
						sPath.Replace(".nll", ".cpp");
					else
#line 222 "../../../Source/Core/AST/TranslationUnit.nll"
						sPath.Replace(".nll", ".hpp");
#line 223 "../../../Source/Core/AST/TranslationUnit.nll"
					break;
				}

				case AST.Language.NLL:
				{
#line 227 "../../../Source/Core/AST/TranslationUnit.nll"
					break;
				}

				case AST.Language.NLL_DEF:
				{
#line 231 "../../../Source/Core/AST/TranslationUnit.nll"
					sPath.Replace(".nll", ".nll.def");
#line 232 "../../../Source/Core/AST/TranslationUnit.nll"
					break;
				}

			}
		}

#line 237 "../../../Source/Core/AST/TranslationUnit.nll"
		public InternalString RetargetRelativePath(Language eLanguage, OutputFile eOutputFile, string sxFrom, string sxTo)
		{
#line 239 "../../../Source/Core/AST/TranslationUnit.nll"
			InternalString sFrom = new InternalString(sxFrom);
#line 240 "../../../Source/Core/AST/TranslationUnit.nll"
			InternalString sTo = new InternalString(sxTo);
#line 242 "../../../Source/Core/AST/TranslationUnit.nll"
			ConvertFilePath(eLanguage, eOutputFile, sFrom);
#line 243 "../../../Source/Core/AST/TranslationUnit.nll"
			ConvertFilePath(eLanguage, eOutputFile, sTo);
#line 245 "../../../Source/Core/AST/TranslationUnit.nll"
			OwnedVector<InternalString> sFromVector = new OwnedVector<InternalString>();
#line 246 "../../../Source/Core/AST/TranslationUnit.nll"
			OwnedVector<InternalString> sToVector = new OwnedVector<InternalString>();
#line 248 "../../../Source/Core/AST/TranslationUnit.nll"
			while (true)
			{
#line 250 "../../../Source/Core/AST/TranslationUnit.nll"
				int nIndex = sFrom.FindChar('/');
#line 251 "../../../Source/Core/AST/TranslationUnit.nll"
				if (nIndex == -1)
#line 252 "../../../Source/Core/AST/TranslationUnit.nll"
					break;
#line 254 "../../../Source/Core/AST/TranslationUnit.nll"
				InternalString sTemp = sFrom.CreateClone();
#line 255 "../../../Source/Core/AST/TranslationUnit.nll"
				sTemp.SubStr(0, nIndex + 1);
#line 256 "../../../Source/Core/AST/TranslationUnit.nll"
				sFrom.CropFront(nIndex + 1);
				NumbatLogic.InternalString __2784973933 = sTemp;
#line 257 "../../../Source/Core/AST/TranslationUnit.nll"
				sTemp = null;
#line 257 "../../../Source/Core/AST/TranslationUnit.nll"
				sFromVector.PushBack(__2784973933);
			}
#line 260 "../../../Source/Core/AST/TranslationUnit.nll"
			while (true)
			{
#line 262 "../../../Source/Core/AST/TranslationUnit.nll"
				int nIndex = sTo.FindChar('/');
#line 263 "../../../Source/Core/AST/TranslationUnit.nll"
				if (nIndex == -1)
#line 264 "../../../Source/Core/AST/TranslationUnit.nll"
					break;
#line 266 "../../../Source/Core/AST/TranslationUnit.nll"
				InternalString sTemp = sTo.CreateClone();
#line 267 "../../../Source/Core/AST/TranslationUnit.nll"
				sTemp.SubStr(0, nIndex + 1);
#line 268 "../../../Source/Core/AST/TranslationUnit.nll"
				sTo.CropFront(nIndex + 1);
				NumbatLogic.InternalString __2785039534 = sTemp;
#line 269 "../../../Source/Core/AST/TranslationUnit.nll"
				sTemp = null;
#line 269 "../../../Source/Core/AST/TranslationUnit.nll"
				sToVector.PushBack(__2785039534);
			}
#line 273 "../../../Source/Core/AST/TranslationUnit.nll"
			while (true)
			{
#line 275 "../../../Source/Core/AST/TranslationUnit.nll"
				if (sFromVector.GetSize() == 0 || sToVector.GetSize() == 0)
#line 276 "../../../Source/Core/AST/TranslationUnit.nll"
					break;
#line 278 "../../../Source/Core/AST/TranslationUnit.nll"
				if (!sFromVector.Get(0).IsEqual(sToVector.Get(0).GetExternalString()))
#line 279 "../../../Source/Core/AST/TranslationUnit.nll"
					break;
#line 281 "../../../Source/Core/AST/TranslationUnit.nll"
				sFromVector.Erase(0);
#line 282 "../../../Source/Core/AST/TranslationUnit.nll"
				sToVector.Erase(0);
			}
#line 285 "../../../Source/Core/AST/TranslationUnit.nll"
			InternalString sOut = new InternalString("");
#line 287 "../../../Source/Core/AST/TranslationUnit.nll"
			for (int i = 0; i < sFromVector.GetSize(); i++)
#line 288 "../../../Source/Core/AST/TranslationUnit.nll"
				sOut.Append("../");
#line 289 "../../../Source/Core/AST/TranslationUnit.nll"
			for (int i = 0; i < sToVector.GetSize(); i++)
#line 290 "../../../Source/Core/AST/TranslationUnit.nll"
				sOut.Append(sToVector.Get(i).GetExternalString());
#line 292 "../../../Source/Core/AST/TranslationUnit.nll"
			sOut.Append(sTo.GetExternalString());
			NumbatLogic.InternalString __1173437905 = sOut;
#line 293 "../../../Source/Core/AST/TranslationUnit.nll"
			sOut = null;
#line 293 "../../../Source/Core/AST/TranslationUnit.nll"
			return __1173437905;
		}

#line 296 "../../../Source/Core/AST/TranslationUnit.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 298 "../../../Source/Core/AST/TranslationUnit.nll"
			if (eLanguage == AST.Language.CPP)
			{
#line 300 "../../../Source/Core/AST/TranslationUnit.nll"
				if (eOutputFile == AST.OutputFile.HEADER)
				{
#line 302 "../../../Source/Core/AST/TranslationUnit.nll"
					pOutputBuilder.m_sOut.Append("#pragma once\n\n");
				}
#line 305 "../../../Source/Core/AST/TranslationUnit.nll"
				OwnedVector<InternalString> sPreviousIncludes = new OwnedVector<InternalString>();
#line 306 "../../../Source/Core/AST/TranslationUnit.nll"
				ReferenceNode pRootReferenceNode = new ReferenceNode("");
#line 308 "../../../Source/Core/AST/TranslationUnit.nll"
				for (int i = 0; i < m_pClassDeclReferenceVector.GetSize(); i++)
				{
#line 310 "../../../Source/Core/AST/TranslationUnit.nll"
					ClassDeclReference pClassDeclReference = m_pClassDeclReferenceVector.Get(i);
#line 311 "../../../Source/Core/AST/TranslationUnit.nll"
					if (eOutputFile == pClassDeclReference.m_eOutputFile)
					{
#line 317 "../../../Source/Core/AST/TranslationUnit.nll"
						bool bOnlyInclude = !pClassDeclReference.m_bForwardReference;
#line 318 "../../../Source/Core/AST/TranslationUnit.nll"
						if (bOnlyInclude)
						{
#line 320 "../../../Source/Core/AST/TranslationUnit.nll"
							for (int j = 0; j < m_pClassDeclReferenceVector.GetSize(); j++)
							{
#line 322 "../../../Source/Core/AST/TranslationUnit.nll"
								ClassDeclReference pTestClassDeclReference = m_pClassDeclReferenceVector.Get(j);
#line 323 "../../../Source/Core/AST/TranslationUnit.nll"
								if (pTestClassDeclReference.m_pClassDecl == pClassDeclReference.m_pClassDecl)
								{
#line 325 "../../../Source/Core/AST/TranslationUnit.nll"
									if (pTestClassDeclReference.m_eOutputFile == pClassDeclReference.m_eOutputFile)
									{
#line 327 "../../../Source/Core/AST/TranslationUnit.nll"
										if (pTestClassDeclReference.m_bForwardReference)
										{
#line 329 "../../../Source/Core/AST/TranslationUnit.nll"
											bOnlyInclude = false;
#line 330 "../../../Source/Core/AST/TranslationUnit.nll"
											break;
										}
									}
								}
							}
						}
#line 337 "../../../Source/Core/AST/TranslationUnit.nll"
						if (pClassDeclReference.m_bForwardReference || bOnlyInclude)
						{
#line 339 "../../../Source/Core/AST/TranslationUnit.nll"
							Vector<InternalString> sNamespaceVector = new Vector<InternalString>();
#line 340 "../../../Source/Core/AST/TranslationUnit.nll"
							NamespaceNode pNamespaceNode = pClassDeclReference.m_pClassDecl.m_pNamespaceNode;
#line 341 "../../../Source/Core/AST/TranslationUnit.nll"
							while (pNamespaceNode != null && pNamespaceNode.m_sName != null)
							{
#line 343 "../../../Source/Core/AST/TranslationUnit.nll"
								sNamespaceVector.PushFront(pNamespaceNode.m_sName);
#line 344 "../../../Source/Core/AST/TranslationUnit.nll"
								pNamespaceNode = pNamespaceNode.m_pParent;
							}
#line 348 "../../../Source/Core/AST/TranslationUnit.nll"
							ReferenceNode pCurrentNode = pRootReferenceNode;
#line 349 "../../../Source/Core/AST/TranslationUnit.nll"
							for (int j = 0; j < sNamespaceVector.GetSize(); j++)
							{
#line 351 "../../../Source/Core/AST/TranslationUnit.nll"
								InternalString sNamespace = sNamespaceVector.Get(j);
#line 352 "../../../Source/Core/AST/TranslationUnit.nll"
								pCurrentNode = pCurrentNode.GetOrCreateChildNode(sNamespace.GetExternalString());
							}
#line 355 "../../../Source/Core/AST/TranslationUnit.nll"
							pCurrentNode.m_pChildClassVector.PushBack(pClassDeclReference);
						}
#line 358 "../../../Source/Core/AST/TranslationUnit.nll"
						if (!pClassDeclReference.m_bForwardReference)
						{
#line 360 "../../../Source/Core/AST/TranslationUnit.nll"
							bool bFound = false;
#line 361 "../../../Source/Core/AST/TranslationUnit.nll"
							for (int j = 0; j < sPreviousIncludes.GetSize(); j++)
							{
#line 363 "../../../Source/Core/AST/TranslationUnit.nll"
								InternalString sTemp = sPreviousIncludes.Get(j);
#line 364 "../../../Source/Core/AST/TranslationUnit.nll"
								if (sTemp.IsEqual(pClassDeclReference.m_pClassDecl.m_pNameToken.m_sFileName.GetExternalString()))
								{
#line 366 "../../../Source/Core/AST/TranslationUnit.nll"
									bFound = true;
#line 367 "../../../Source/Core/AST/TranslationUnit.nll"
									break;
								}
							}
#line 370 "../../../Source/Core/AST/TranslationUnit.nll"
							if (bFound)
#line 371 "../../../Source/Core/AST/TranslationUnit.nll"
								continue;
#line 372 "../../../Source/Core/AST/TranslationUnit.nll"
							sPreviousIncludes.PushBack(new InternalString(pClassDeclReference.m_pClassDecl.m_pNameToken.m_sFileName.GetExternalString()));
#line 374 "../../../Source/Core/AST/TranslationUnit.nll"
							InternalString sFixedPath = RetargetRelativePath(eLanguage, AST.OutputFile.HEADER, m_pFirstChild.m_pFirstToken.m_sFileName.GetExternalString(), pClassDeclReference.m_pClassDecl.m_pNameToken.m_sFileName.GetExternalString());
#line 375 "../../../Source/Core/AST/TranslationUnit.nll"
							pOutputBuilder.m_sOut.Append("#include \"");
#line 376 "../../../Source/Core/AST/TranslationUnit.nll"
							pOutputBuilder.m_sOut.Append(sFixedPath.GetExternalString());
#line 377 "../../../Source/Core/AST/TranslationUnit.nll"
							pOutputBuilder.m_sOut.Append("\"\n");
						}
					}
				}
#line 382 "../../../Source/Core/AST/TranslationUnit.nll"
				if (sPreviousIncludes.GetSize() > 0)
#line 383 "../../../Source/Core/AST/TranslationUnit.nll"
					pOutputBuilder.m_sOut.Append("\n");
#line 384 "../../../Source/Core/AST/TranslationUnit.nll"
				pRootReferenceNode.Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
			}
#line 387 "../../../Source/Core/AST/TranslationUnit.nll"
			AST pChild = m_pFirstChild;
#line 388 "../../../Source/Core/AST/TranslationUnit.nll"
			while (pChild != null)
			{
#line 390 "../../../Source/Core/AST/TranslationUnit.nll"
				if (!pChild.m_bSkipOutput)
				{
#line 392 "../../../Source/Core/AST/TranslationUnit.nll"
					pChild.Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
#line 393 "../../../Source/Core/AST/TranslationUnit.nll"
					pOutputBuilder.m_sOut.AppendChar('\n');
				}
#line 395 "../../../Source/Core/AST/TranslationUnit.nll"
				pChild = pChild.m_pNextSibling;
			}
		}

#line 83 "../../../Source/Core/AST/TranslationUnit.nll"
		~TranslationUnit()
		{
		}

	}
}

