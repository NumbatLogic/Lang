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
#line 0 "../../../Source/Core/AST/TranslationUnit.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/TranslationUnit.nll"
	ClassDeclReference::ClassDeclReference()
	{
		m_pClassDecl = 0;
		m_eOutputFile = AST::OutputFile::SOURCE;
		m_bForwardReference = false;
	}

#line 10 "../../../Source/Core/AST/TranslationUnit.nll"
	ReferenceNode::ReferenceNode(const char* sxName)
	{
		m_sName = 0;
		m_pChildNodeVector = 0;
		m_pChildClassVector = 0;
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
		ReferenceNode* pCreatedChild = new ReferenceNode(sxName);
		pChild = pCreatedChild;
		NumbatLogic::ReferenceNode* __2217859494 = pCreatedChild;
		pCreatedChild = 0;
		m_pChildNodeVector->PushBack(__2217859494);
		if (pCreatedChild) delete pCreatedChild;
		return pChild;
	}

	void ReferenceNode::Stringify(AST::Language eLanguage, AST::OutputFile eOutputFile, int nDepth, OutputBuilder* out)
	{
		if (!m_sName->IsEqual(""))
		{
			Util::Pad(nDepth, out->m_sOut);
			out->m_sOut->Append("namespace ");
			out->m_sOut->Append(m_sName->GetExternalString());
			out->m_sOut->Append("\n");
			Util::Pad(nDepth, out->m_sOut);
			out->m_sOut->Append("{\n");
			nDepth++;
		}
		for (int i = 0; i < m_pChildNodeVector->GetSize(); i++)
		{
			ReferenceNode* pChild = m_pChildNodeVector->Get(i);
			pChild->Stringify(eLanguage, eOutputFile, nDepth, out);
		}
		for (int i = 0; i < m_pChildClassVector->GetSize(); i++)
		{
			ClassDeclReference* pChild = m_pChildClassVector->Get(i);
			if (pChild->m_pClassDecl->m_pGenericTypeDeclVector->GetSize() > 0)
			{
				Util::Pad(nDepth, out->m_sOut);
				pChild->m_pClassDecl->StringifyTemplateThing(eLanguage, eOutputFile, out);
				out->m_sOut->Append("\n");
			}
			Util::Pad(nDepth, out->m_sOut);
			out->m_sOut->Append("class ");
			pChild->m_pClassDecl->m_pNameToken->Stringify(out->m_sOut);
			out->m_sOut->Append(";\n");
		}
		if (!m_sName->IsEqual(""))
		{
			nDepth--;
			Util::Pad(nDepth, out->m_sOut);
			out->m_sOut->Append("}\n");
		}
	}

	ReferenceNode::~ReferenceNode()
	{
		if (m_sName) delete m_sName;
		if (m_pChildNodeVector) delete m_pChildNodeVector;
		if (m_pChildClassVector) delete m_pChildClassVector;
	}

#line 83 "../../../Source/Core/AST/TranslationUnit.nll"
	TranslationUnit::TranslationUnit(const char* sInFile)
	{
		m_sInFile = 0;
		m_pTokenContainer = 0;
		m_pClassDeclReferenceVector = 0;
		m_sInFile = new InternalString(sInFile);
		m_eType = Type::AST_TRANSLATION_UNIT;
		m_bCanDescend = true;
		m_pTokenContainer = new TokenContainer();
		m_pClassDeclReferenceVector = new OwnedVector<ClassDeclReference*>();
	}

	TranslationUnit* TranslationUnit::Create(const char* sInFile, OwnedVector<InternalString*>* sDefineVector)
	{
		TranslationUnit* pThis = new TranslationUnit(sInFile);
		InternalString* sInput = File::GetContents(pThis->m_sInFile->GetExternalString());
		pThis->m_pTokenContainer->Tokenize(sInput->GetExternalString(), pThis->m_sInFile, sDefineVector);
		pThis->m_pTokenContainer->StripWhitespace();
		OffsetDatum* pOffsetDatum = OffsetDatum::Create(0);
		while (pOffsetDatum->m_nOffset < pThis->m_pTokenContainer->m_pTokenVector->GetSize())
		{
			AST* pAST = AST::CreateFromTokenContainer(pThis->m_pTokenContainer, pOffsetDatum);
			if (pAST == 0)
			{
				if (pAST) delete pAST;
#line 116 "../../../Source/Core/AST/TranslationUnit.nll"
				break;
			}
			NumbatLogic::AST* __3057539430 = pAST;
			pAST = 0;
			pThis->AddChild(__3057539430);
			if (pAST) delete pAST;
		}
		NumbatLogic::TranslationUnit* __2058438882 = pThis;
		pThis = 0;
		if (sInput) delete sInput;
		if (pOffsetDatum) delete pOffsetDatum;
		return __2058438882;
	}

	void TranslationUnit::AddClassDeclReference(ClassDecl* pClassDecl, OutputFile eOutputFile, bool bForwardReference)
	{
		for (int i = 0; i < m_pClassDeclReferenceVector->GetSize(); i++)
		{
			ClassDeclReference* pTestClassDeclReference = m_pClassDeclReferenceVector->Get(i);
			if (pTestClassDeclReference->m_pClassDecl == pClassDecl && pTestClassDeclReference->m_eOutputFile == eOutputFile)
			{
				if (pTestClassDeclReference->m_bForwardReference == bForwardReference)
				{
					AST::AddClassDeclReference(pClassDecl, eOutputFile, bForwardReference);
					return;
				}
			}
		}
		ClassDeclReference* pClassDeclReference = new ClassDeclReference();
		pClassDeclReference->m_pClassDecl = pClassDecl;
		pClassDeclReference->m_eOutputFile = eOutputFile;
		pClassDeclReference->m_bForwardReference = bForwardReference;
		NumbatLogic::ClassDeclReference* __3931805821 = pClassDeclReference;
		pClassDeclReference = 0;
		m_pClassDeclReferenceVector->PushBack(__3931805821);
		AST::AddClassDeclReference(pClassDecl, eOutputFile, bForwardReference);
		if (pClassDeclReference) delete pClassDeclReference;
	}

	void TranslationUnit::ConvertFilePath(Language eLanguage, OutputFile eOutputFile, InternalString* sPath)
	{
		if (sPath->EndsWith(".nll.def"))
		{
			InternalString* sFolder = new InternalString("");
			InternalString* sFile = sPath->CreateClone();
			while (true)
			{
				int nIndex = sFile->FindChar('/');
				if (nIndex == -1)
#line 166 "../../../Source/Core/AST/TranslationUnit.nll"
					break;
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
#line 180 "../../../Source/Core/AST/TranslationUnit.nll"
					break;
				}

				case AST::Language::CPP:
				{
					sFolder->Append("CPP/");
					if (eOutputFile == AST::OutputFile::SOURCE)
						sFile->Replace(".nll.def", ".cpp");
					else
						sFile->Replace(".nll.def", ".hpp");
#line 189 "../../../Source/Core/AST/TranslationUnit.nll"
					break;
				}

				case AST::Language::NLL:
				{
#line 193 "../../../Source/Core/AST/TranslationUnit.nll"
					break;
				}

				case AST::Language::NLL_DEF:
				{
#line 197 "../../../Source/Core/AST/TranslationUnit.nll"
					break;
				}

			}
			sPath->Set(sFolder->GetExternalString());
			sPath->Append(sFile->GetExternalString());
			if (sFolder) delete sFolder;
			if (sFile) delete sFile;
			return;
		}
		sPath->Replace("Source", "Transpiled");
		switch (eLanguage)
		{
			case AST::Language::CS:
			{
				sPath->Replace(".nll", ".cs");
#line 215 "../../../Source/Core/AST/TranslationUnit.nll"
				break;
			}

			case AST::Language::CPP:
			{
				if (eOutputFile == AST::OutputFile::SOURCE)
					sPath->Replace(".nll", ".cpp");
				else
					sPath->Replace(".nll", ".hpp");
#line 223 "../../../Source/Core/AST/TranslationUnit.nll"
				break;
			}

			case AST::Language::NLL:
			{
#line 227 "../../../Source/Core/AST/TranslationUnit.nll"
				break;
			}

			case AST::Language::NLL_DEF:
			{
				sPath->Replace(".nll", ".nll.def");
#line 232 "../../../Source/Core/AST/TranslationUnit.nll"
				break;
			}

		}
	}

	InternalString* TranslationUnit::RetargetRelativePath(Language eLanguage, OutputFile eOutputFile, const char* sxFrom, const char* sxTo)
	{
		InternalString* sFrom = new InternalString(sxFrom);
		InternalString* sTo = new InternalString(sxTo);
		ConvertFilePath(eLanguage, eOutputFile, sFrom);
		ConvertFilePath(eLanguage, eOutputFile, sTo);
		OwnedVector<InternalString*>* sFromVector = new OwnedVector<InternalString*>();
		OwnedVector<InternalString*>* sToVector = new OwnedVector<InternalString*>();
		while (true)
		{
			int nIndex = sFrom->FindChar('/');
			if (nIndex == -1)
#line 252 "../../../Source/Core/AST/TranslationUnit.nll"
				break;
			InternalString* sTemp = sFrom->CreateClone();
			sTemp->SubStr(0, nIndex + 1);
			sFrom->CropFront(nIndex + 1);
			NumbatLogic::InternalString* __2784973933 = sTemp;
			sTemp = 0;
			sFromVector->PushBack(__2784973933);
			if (sTemp) delete sTemp;
		}
		while (true)
		{
			int nIndex = sTo->FindChar('/');
			if (nIndex == -1)
#line 264 "../../../Source/Core/AST/TranslationUnit.nll"
				break;
			InternalString* sTemp = sTo->CreateClone();
			sTemp->SubStr(0, nIndex + 1);
			sTo->CropFront(nIndex + 1);
			NumbatLogic::InternalString* __2785039534 = sTemp;
			sTemp = 0;
			sToVector->PushBack(__2785039534);
			if (sTemp) delete sTemp;
		}
		while (true)
		{
			if (sFromVector->GetSize() == 0 || sToVector->GetSize() == 0)
#line 276 "../../../Source/Core/AST/TranslationUnit.nll"
				break;
			if (!sFromVector->Get(0)->IsEqual(sToVector->Get(0)->GetExternalString()))
#line 279 "../../../Source/Core/AST/TranslationUnit.nll"
				break;
			sFromVector->Erase(0);
			sToVector->Erase(0);
		}
		InternalString* sOut = new InternalString("");
		for (int i = 0; i < sFromVector->GetSize(); i++)
			sOut->Append("../");
		for (int i = 0; i < sToVector->GetSize(); i++)
			sOut->Append(sToVector->Get(i)->GetExternalString());
		sOut->Append(sTo->GetExternalString());
		NumbatLogic::InternalString* __1173437905 = sOut;
		sOut = 0;
		if (sFrom) delete sFrom;
		if (sTo) delete sTo;
		if (sFromVector) delete sFromVector;
		if (sToVector) delete sToVector;
		return __1173437905;
	}

	void TranslationUnit::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* out)
	{
		if (eLanguage == AST::Language::CPP)
		{
			if (eOutputFile == AST::OutputFile::HEADER)
			{
				out->m_sOut->Append("#pragma once\n\n");
			}
			OwnedVector<InternalString*>* sPreviousIncludes = new OwnedVector<InternalString*>();
			ReferenceNode* pRootReferenceNode = new ReferenceNode("");
			for (int i = 0; i < m_pClassDeclReferenceVector->GetSize(); i++)
			{
				ClassDeclReference* pClassDeclReference = m_pClassDeclReferenceVector->Get(i);
				if (eOutputFile == pClassDeclReference->m_eOutputFile)
				{
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
#line 330 "../../../Source/Core/AST/TranslationUnit.nll"
										break;
									}
								}
							}
						}
					}
					if (pClassDeclReference->m_bForwardReference || bOnlyInclude)
					{
						Vector<InternalString*>* sNamespaceVector = new Vector<InternalString*>();
						NamespaceNode* pNamespaceNode = pClassDeclReference->m_pClassDecl->m_pNamespaceNode;
						while (pNamespaceNode != 0 && pNamespaceNode->m_sName != 0)
						{
							sNamespaceVector->PushFront(pNamespaceNode->m_sName);
							pNamespaceNode = pNamespaceNode->m_pParent;
						}
						ReferenceNode* pCurrentNode = pRootReferenceNode;
						for (int j = 0; j < sNamespaceVector->GetSize(); j++)
						{
							InternalString* sNamespace = sNamespaceVector->Get(j);
							pCurrentNode = pCurrentNode->GetOrCreateChildNode(sNamespace->GetExternalString());
						}
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
#line 367 "../../../Source/Core/AST/TranslationUnit.nll"
								break;
							}
						}
						if (bFound)
							continue;
						sPreviousIncludes->PushBack(new InternalString(pClassDeclReference->m_pClassDecl->m_pNameToken->m_sFileName->GetExternalString()));
						InternalString* sFixedPath = RetargetRelativePath(eLanguage, AST::OutputFile::HEADER, m_pFirstChild->m_pFirstToken->m_sFileName->GetExternalString(), pClassDeclReference->m_pClassDecl->m_pNameToken->m_sFileName->GetExternalString());
						out->m_sOut->Append("#include \"");
						out->m_sOut->Append(sFixedPath->GetExternalString());
						out->m_sOut->Append("\"\n");
						if (sFixedPath) delete sFixedPath;
					}
				}
			}
			if (sPreviousIncludes->GetSize() > 0)
				out->m_sOut->Append("\n");
			pRootReferenceNode->Stringify(eLanguage, eOutputFile, nDepth, out);
			if (sPreviousIncludes) delete sPreviousIncludes;
			if (pRootReferenceNode) delete pRootReferenceNode;
		}
		AST* pChild = m_pFirstChild;
		while (pChild != 0)
		{
			if (!pChild->m_bSkipOutput)
			{
				pChild->Stringify(eLanguage, eOutputFile, nDepth, out);
				out->m_sOut->AppendChar('\n');
			}
			pChild = pChild->m_pNextSibling;
		}
	}

	TranslationUnit::~TranslationUnit()
	{
		if (m_sInFile) delete m_sInFile;
		if (m_pTokenContainer) delete m_pTokenContainer;
		if (m_pClassDeclReferenceVector) delete m_pClassDeclReferenceVector;
	}

}

