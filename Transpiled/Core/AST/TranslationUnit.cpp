#include "TranslationUnit.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "../../../../LangShared/Transpiled/Vector/OwnedVector.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
#include "../Util.hpp"
#include "../OutputBuilder.hpp"
#include "ClassDecl.hpp"
#include "../Token.hpp"
#include "../TokenContainer.hpp"
#include "../../../../LangShared/File/CPP/File.hpp"
#include "../OffsetDatum.hpp"
#include "AST.hpp"
#include "../NamespaceNode.hpp"

namespace NumbatLogic
{
	class ReferenceNode;
	template <class T>
	class OwnedVector;
	class ClassDeclReference;
	template <class T>
	class Vector;
	class Util;
	class OutputBuilder;
	class ClassDecl;
	class Token;
	class AST;
	class TokenContainer;
	class InternalString;
	class TranslationUnit;
	class File;
	class OffsetDatum;
	class NamespaceNode;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
	ClassDeclReference::ClassDeclReference()
	{
		m_pClassDecl = 0;
		m_eOutputFile = AST::OutputFile::SOURCE;
		m_bForwardReference = false;
	}

#line 16 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
	ReferenceNode::ReferenceNode(const char* sxName)
	{
		m_sName = 0;
		m_pChildNodeVector = 0;
		m_pChildClassVector = 0;
#line 18 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		m_sName = new InternalString(sxName);
		m_pChildNodeVector = new OwnedVector<ReferenceNode*>();
		m_pChildClassVector = new Vector<ClassDeclReference*>();
	}

	ReferenceNode* ReferenceNode::GetOrCreateChildNode(const char* sxName)
	{
		ReferenceNode* pChild = 0;
		for (int i = 0; i < m_pChildNodeVector->GetSize(); i++)
		{
			pChild = m_pChildNodeVector->Get(i);
			if (pChild->m_sName->IsEqual(sxName))
				return pChild;
		}
#line 33 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		ReferenceNode* pCreatedChild = new ReferenceNode(sxName);
		pChild = pCreatedChild;
		NumbatLogic::ReferenceNode* __2217859494 = pCreatedChild;
#line 35 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		pCreatedChild = 0;
#line 35 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		m_pChildNodeVector->PushBack(__2217859494);
		if (pCreatedChild) delete pCreatedChild;
#line 36 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		return pChild;
	}

	void ReferenceNode::Stringify(AST::Language eLanguage, AST::OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		if (!m_sName->IsEqual(""))
		{
			Util::Pad(nDepth, pOutputBuilder->m_sOut);
			pOutputBuilder->m_sOut->Append("namespace ");
			pOutputBuilder->m_sOut->Append(m_sName->GetExternalString());
			pOutputBuilder->m_sOut->Append("\n");
			Util::Pad(nDepth, pOutputBuilder->m_sOut);
			pOutputBuilder->m_sOut->Append("{\n");
			nDepth++;
		}
#line 52 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		for (int i = 0; i < m_pChildNodeVector->GetSize(); i++)
		{
			ReferenceNode* pChild = m_pChildNodeVector->Get(i);
			pChild->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
		}
#line 58 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		for (int i = 0; i < m_pChildClassVector->GetSize(); i++)
		{
			ClassDeclReference* pChild = m_pChildClassVector->Get(i);
			if (pChild->m_pClassDecl->m_pGenericTypeDeclVector->GetSize() > 0)
			{
				Util::Pad(nDepth, pOutputBuilder->m_sOut);
				pChild->m_pClassDecl->StringifyTemplateThing(eLanguage, eOutputFile, pOutputBuilder);
				pOutputBuilder->m_sOut->Append("\n");
			}
#line 68 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
			Util::Pad(nDepth, pOutputBuilder->m_sOut);
			pOutputBuilder->m_sOut->Append("class ");
			pChild->m_pClassDecl->m_pNameToken->Stringify(pOutputBuilder->m_sOut);
			pOutputBuilder->m_sOut->Append(";\n");
		}
#line 74 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		if (!m_sName->IsEqual(""))
		{
			nDepth--;
			Util::Pad(nDepth, pOutputBuilder->m_sOut);
			pOutputBuilder->m_sOut->Append("}\n");
		}
	}

#line 10 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
	ReferenceNode::~ReferenceNode()
	{
		if (m_sName) delete m_sName;
		if (m_pChildNodeVector) delete m_pChildNodeVector;
		if (m_pChildClassVector) delete m_pChildClassVector;
	}

#line 83 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
#line 89 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
	TranslationUnit::TranslationUnit(const char* sInFile)
	{
		m_sInFile = 0;
		m_pTokenContainer = 0;
		m_pClassDeclReferenceVector = 0;
#line 91 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		m_sInFile = new InternalString(sInFile);
		m_eType = Type::AST_TRANSLATION_UNIT;
		m_bCanDescend = true;
#line 95 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		m_pTokenContainer = new TokenContainer();
		m_pClassDeclReferenceVector = new OwnedVector<ClassDeclReference*>();
	}

	TranslationUnit* TranslationUnit::Create(const char* sInFile, OwnedVector<InternalString*>* sDefineVector)
	{
		TranslationUnit* pThis = new TranslationUnit(sInFile);
#line 104 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		InternalString* sFullPath = File::GetFullPath(pThis->m_sInFile->GetExternalString());
		pThis->m_sInFile->Set(sFullPath->GetExternalString());
#line 107 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		InternalString* sInput = File::GetContents(pThis->m_sInFile->GetExternalString());
#line 110 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		pThis->m_pTokenContainer->Tokenize(sInput->GetExternalString(), pThis->m_sInFile, sDefineVector);
		pThis->m_pTokenContainer->StripWhitespace();
#line 113 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		OffsetDatum* pOffsetDatum = OffsetDatum::Create(0);
#line 116 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		while (pOffsetDatum->m_nOffset < pThis->m_pTokenContainer->m_pTokenVector->GetSize())
		{
			AST* pAST = AST::CreateFromTokenContainer(pThis->m_pTokenContainer, pOffsetDatum);
			if (pAST == 0)
			{
				if (pAST) delete pAST;
#line 120 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
				break;
			}
			NumbatLogic::AST* __3057605023 = pAST;
#line 122 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
			pAST = 0;
#line 122 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
			pThis->AddChild(__3057605023);
			if (pAST) delete pAST;
		}
		NumbatLogic::TranslationUnit* __2058438886 = pThis;
#line 125 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		pThis = 0;
		if (sFullPath) delete sFullPath;
		if (sInput) delete sInput;
		if (pOffsetDatum) delete pOffsetDatum;
#line 125 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		return __2058438886;
	}

	void TranslationUnit::AddClassDeclReference(ClassDecl* pClassDecl, OutputFile eOutputFile, bool bForwardReference)
	{
		for (int i = 0; i < m_pClassDeclReferenceVector->GetSize(); i++)
		{
			ClassDeclReference* pTestClassDeclReference = m_pClassDeclReferenceVector->Get(i);
			if (pTestClassDeclReference->m_pClassDecl == pClassDecl && pTestClassDeclReference->m_eOutputFile == eOutputFile)
			{
#line 140 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
				if (pTestClassDeclReference->m_bForwardReference == bForwardReference)
				{
					AST::AddClassDeclReference(pClassDecl, eOutputFile, bForwardReference);
					return;
				}
			}
		}
#line 148 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		ClassDeclReference* pClassDeclReference = new ClassDeclReference();
		pClassDeclReference->m_pClassDecl = pClassDecl;
		pClassDeclReference->m_eOutputFile = eOutputFile;
		pClassDeclReference->m_bForwardReference = bForwardReference;
		NumbatLogic::ClassDeclReference* __3931871414 = pClassDeclReference;
		pClassDeclReference = 0;
#line 153 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		m_pClassDeclReferenceVector->PushBack(__3931871414);
#line 155 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		AST::AddClassDeclReference(pClassDecl, eOutputFile, bForwardReference);
		if (pClassDeclReference) delete pClassDeclReference;
	}

#line 158 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
	void TranslationUnit::ConvertFilePath(Language eLanguage, OutputFile eOutputFile, InternalString* sPath)
	{
#line 161 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		if (sPath->EndsWith(".nll.def"))
		{
			InternalString* sFolder = new InternalString("");
			InternalString* sFile = sPath->CreateClone();
#line 166 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
			while (true)
			{
				int nIndex = sFile->FindChar('/');
				if (nIndex == -1)
					break;
#line 172 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
				InternalString* sTemp = sFile->CreateClone();
				sTemp->SubStr(0, nIndex + 1);
				sFolder->Append(sTemp->GetExternalString());
				sFile->CropFront(nIndex + 1);
				if (sTemp) delete sTemp;
			}
			switch (eLanguage)
			{
				case AST::Language::CS:
				{
					sFolder->Append("CS/");
					sFile->Replace(".nll.def", ".cs");
					break;
				}

				case AST::Language::CPP:
				{
#line 188 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
					sFolder->Append("CPP/");
					if (eOutputFile == AST::OutputFile::SOURCE)
						sFile->Replace(".nll.def", ".cpp");
					else
						sFile->Replace(".nll.def", ".hpp");
					break;
				}

				case AST::Language::NLL:
				{
#line 197 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
					break;
				}

				case AST::Language::NLL_DEF:
				{
#line 201 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
					break;
				}

			}
			sPath->Set(sFolder->GetExternalString());
			sPath->Append(sFile->GetExternalString());
			if (sFolder) delete sFolder;
			if (sFile) delete sFile;
#line 207 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
			return;
		}
#line 210 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		sPath->Replace("/LangShared/", "/LangShared/Transpiled/");
#line 213 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		sPath->Replace("Source", "Transpiled");
#line 216 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		switch (eLanguage)
		{
			case AST::Language::CS:
			{
				sPath->Replace(".nll", ".cs");
				break;
			}

			case AST::Language::CPP:
			{
#line 225 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
				if (eOutputFile == AST::OutputFile::SOURCE)
					sPath->Replace(".nll", ".cpp");
				else
					sPath->Replace(".nll", ".hpp");
				break;
			}

			case AST::Language::NLL:
			{
#line 233 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
				break;
			}

			case AST::Language::NLL_DEF:
			{
#line 237 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
				sPath->Replace(".nll", ".nll.def");
				break;
			}

		}
	}

#line 243 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
	InternalString* TranslationUnit::RetargetRelativePath(Language eLanguage, OutputFile eOutputFile, const char* sxFrom, const char* sxTo)
	{
		InternalString* sFrom = new InternalString(sxFrom);
		InternalString* sTo = new InternalString(sxTo);
#line 248 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		ConvertFilePath(eLanguage, eOutputFile, sFrom);
		ConvertFilePath(eLanguage, eOutputFile, sTo);
#line 251 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		OwnedVector<InternalString*>* sFromVector = new OwnedVector<InternalString*>();
		OwnedVector<InternalString*>* sToVector = new OwnedVector<InternalString*>();
#line 254 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		while (true)
		{
			int nIndex = sFrom->FindChar('/');
			if (nIndex == -1)
				break;
#line 260 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
			InternalString* sTemp = sFrom->CreateClone();
			sTemp->SubStr(0, nIndex + 1);
			sFrom->CropFront(nIndex + 1);
			NumbatLogic::InternalString* __2785039528 = sTemp;
#line 263 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
			sTemp = 0;
#line 263 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
			sFromVector->PushBack(__2785039528);
			if (sTemp) delete sTemp;
		}
		while (true)
		{
			int nIndex = sTo->FindChar('/');
			if (nIndex == -1)
				break;
#line 272 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
			InternalString* sTemp = sTo->CreateClone();
			sTemp->SubStr(0, nIndex + 1);
			sTo->CropFront(nIndex + 1);
			NumbatLogic::InternalString* __2785105129 = sTemp;
#line 275 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
			sTemp = 0;
#line 275 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
			sToVector->PushBack(__2785105129);
			if (sTemp) delete sTemp;
		}
#line 279 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		while (true)
		{
			if (sFromVector->GetSize() == 0 || sToVector->GetSize() == 0)
				break;
#line 284 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
			if (!sFromVector->Get(0)->IsEqual(sToVector->Get(0)->GetExternalString()))
				break;
#line 287 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
			sFromVector->Erase(0);
			sToVector->Erase(0);
		}
#line 291 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		InternalString* sOut = new InternalString("");
#line 293 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		for (int i = 0; i < sFromVector->GetSize(); i++)
			sOut->Append("../");
		for (int i = 0; i < sToVector->GetSize(); i++)
			sOut->Append(sToVector->Get(i)->GetExternalString());
#line 298 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		sOut->Append(sTo->GetExternalString());
		NumbatLogic::InternalString* __1173437911 = sOut;
#line 299 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		sOut = 0;
		if (sFrom) delete sFrom;
		if (sTo) delete sTo;
		if (sFromVector) delete sFromVector;
		if (sToVector) delete sToVector;
#line 299 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		return __1173437911;
	}

	void TranslationUnit::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		if (eLanguage == AST::Language::CPP)
		{
			if (eOutputFile == AST::OutputFile::HEADER)
			{
				pOutputBuilder->m_sOut->Append("#pragma once\n\n");
			}
#line 311 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
			OwnedVector<InternalString*>* sPreviousIncludes = new OwnedVector<InternalString*>();
			ReferenceNode* pRootReferenceNode = new ReferenceNode("");
#line 314 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
			for (int i = 0; i < m_pClassDeclReferenceVector->GetSize(); i++)
			{
				ClassDeclReference* pClassDeclReference = m_pClassDeclReferenceVector->Get(i);
				if (eOutputFile == pClassDeclReference->m_eOutputFile)
				{
#line 323 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
					bool bOnlyInclude = !pClassDeclReference->m_bForwardReference;
					if (bOnlyInclude)
					{
						for (int j = 0; j < m_pClassDeclReferenceVector->GetSize(); j++)
						{
							ClassDeclReference* pTestClassDeclReference = m_pClassDeclReferenceVector->Get(j);
							if (pTestClassDeclReference->m_pClassDecl == pClassDeclReference->m_pClassDecl)
							{
								if (pTestClassDeclReference->m_eOutputFile == pClassDeclReference->m_eOutputFile)
								{
									if (pTestClassDeclReference->m_bForwardReference)
									{
										bOnlyInclude = false;
										break;
									}
								}
							}
						}
					}
#line 343 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
					if (pClassDeclReference->m_bForwardReference || bOnlyInclude)
					{
						Vector<InternalString*>* sNamespaceVector = new Vector<InternalString*>();
						NamespaceNode* pNamespaceNode = pClassDeclReference->m_pClassDecl->m_pNamespaceNode;
						while (pNamespaceNode != 0 && pNamespaceNode->m_sName != 0)
						{
							sNamespaceVector->PushFront(pNamespaceNode->m_sName);
							pNamespaceNode = pNamespaceNode->m_pParent;
						}
#line 354 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
						ReferenceNode* pCurrentNode = pRootReferenceNode;
						for (int j = 0; j < sNamespaceVector->GetSize(); j++)
						{
							InternalString* sNamespace = sNamespaceVector->Get(j);
							pCurrentNode = pCurrentNode->GetOrCreateChildNode(sNamespace->GetExternalString());
						}
#line 361 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
						pCurrentNode->m_pChildClassVector->PushBack(pClassDeclReference);
						if (sNamespaceVector) delete sNamespaceVector;
					}
					if (!pClassDeclReference->m_bForwardReference)
					{
						bool bFound = false;
						for (int j = 0; j < sPreviousIncludes->GetSize(); j++)
						{
							InternalString* sTemp = sPreviousIncludes->Get(j);
							if (sTemp->IsEqual(pClassDeclReference->m_pClassDecl->m_pNameToken->m_sFileName->GetExternalString()))
							{
								bFound = true;
								break;
							}
						}
						if (bFound)
							continue;
						sPreviousIncludes->PushBack(new InternalString(pClassDeclReference->m_pClassDecl->m_pNameToken->m_sFileName->GetExternalString()));
#line 380 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
						InternalString* sFixedPath = RetargetRelativePath(eLanguage, AST::OutputFile::HEADER, m_pFirstChild->m_pFirstToken->m_sFileName->GetExternalString(), pClassDeclReference->m_pClassDecl->m_pNameToken->m_sFileName->GetExternalString());
						pOutputBuilder->m_sOut->Append("#include \"");
						pOutputBuilder->m_sOut->Append(sFixedPath->GetExternalString());
						pOutputBuilder->m_sOut->Append("\"\n");
						if (sFixedPath) delete sFixedPath;
					}
				}
			}
			if (sPreviousIncludes->GetSize() > 0)
				pOutputBuilder->m_sOut->Append("\n");
			pRootReferenceNode->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
			if (sPreviousIncludes) delete sPreviousIncludes;
			if (pRootReferenceNode) delete pRootReferenceNode;
		}
#line 393 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		AST* pChild = m_pFirstChild;
		while (pChild != 0)
		{
			if (!pChild->m_bSkipOutput)
			{
				pChild->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
				pOutputBuilder->m_sOut->AppendChar('\n');
			}
			pChild = pChild->m_pNextSibling;
		}
	}

#line 83 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
	TranslationUnit::~TranslationUnit()
	{
		if (m_sInFile) delete m_sInFile;
		if (m_pTokenContainer) delete m_pTokenContainer;
		if (m_pClassDeclReferenceVector) delete m_pClassDeclReferenceVector;
	}

}

