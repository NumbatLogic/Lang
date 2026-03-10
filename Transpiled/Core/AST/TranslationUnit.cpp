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
#line 3 "../../../Source/Core/AST/TranslationUnit.nll"
	ClassDeclReference::ClassDeclReference()
	{
		m_pClassDecl = 0;
		m_eOutputFile = AST::OutputFile::SOURCE;
		m_bForwardReference = false;
	}

#line 10 "../../../Source/Core/AST/TranslationUnit.nll"
#line 16 "../../../Source/Core/AST/TranslationUnit.nll"
	ReferenceNode::ReferenceNode(const char* sxName)
	{
		m_sName = 0;
		m_pChildNodeVector = 0;
		m_pChildClassVector = 0;
#line 18 "../../../Source/Core/AST/TranslationUnit.nll"
		m_sName = new InternalString(sxName);
#line 19 "../../../Source/Core/AST/TranslationUnit.nll"
		m_pChildNodeVector = new OwnedVector<ReferenceNode*>();
#line 20 "../../../Source/Core/AST/TranslationUnit.nll"
		m_pChildClassVector = new Vector<ClassDeclReference*>();
	}

#line 23 "../../../Source/Core/AST/TranslationUnit.nll"
	ReferenceNode* ReferenceNode::GetOrCreateChildNode(const char* sxName)
	{
		ReferenceNode* pChild = 0;
#line 26 "../../../Source/Core/AST/TranslationUnit.nll"
		for (int i = 0; i < m_pChildNodeVector->GetSize(); i++)
		{
#line 28 "../../../Source/Core/AST/TranslationUnit.nll"
			pChild = m_pChildNodeVector->Get(i);
#line 29 "../../../Source/Core/AST/TranslationUnit.nll"
			if (pChild->m_sName->IsEqual(sxName))
#line 30 "../../../Source/Core/AST/TranslationUnit.nll"
				return pChild;
		}
		ReferenceNode* pCreatedChild = new ReferenceNode(sxName);
#line 34 "../../../Source/Core/AST/TranslationUnit.nll"
		pChild = pCreatedChild;
		NumbatLogic::ReferenceNode* __2217859494 = pCreatedChild;
#line 35 "../../../Source/Core/AST/TranslationUnit.nll"
		pCreatedChild = 0;
#line 35 "../../../Source/Core/AST/TranslationUnit.nll"
		m_pChildNodeVector->PushBack(__2217859494);
		if (pCreatedChild) delete pCreatedChild;
#line 36 "../../../Source/Core/AST/TranslationUnit.nll"
		return pChild;
	}

#line 39 "../../../Source/Core/AST/TranslationUnit.nll"
	void ReferenceNode::Stringify(AST::Language eLanguage, AST::OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 41 "../../../Source/Core/AST/TranslationUnit.nll"
		if (!m_sName->IsEqual(""))
		{
#line 43 "../../../Source/Core/AST/TranslationUnit.nll"
			Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 44 "../../../Source/Core/AST/TranslationUnit.nll"
			pOutputBuilder->m_sOut->Append("namespace ");
#line 45 "../../../Source/Core/AST/TranslationUnit.nll"
			pOutputBuilder->m_sOut->Append(m_sName->GetExternalString());
#line 46 "../../../Source/Core/AST/TranslationUnit.nll"
			pOutputBuilder->m_sOut->Append("\n");
#line 47 "../../../Source/Core/AST/TranslationUnit.nll"
			Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 48 "../../../Source/Core/AST/TranslationUnit.nll"
			pOutputBuilder->m_sOut->Append("{\n");
#line 49 "../../../Source/Core/AST/TranslationUnit.nll"
			nDepth++;
		}
#line 52 "../../../Source/Core/AST/TranslationUnit.nll"
		for (int i = 0; i < m_pChildNodeVector->GetSize(); i++)
		{
			ReferenceNode* pChild = m_pChildNodeVector->Get(i);
#line 55 "../../../Source/Core/AST/TranslationUnit.nll"
			pChild->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
		}
#line 58 "../../../Source/Core/AST/TranslationUnit.nll"
		for (int i = 0; i < m_pChildClassVector->GetSize(); i++)
		{
			ClassDeclReference* pChild = m_pChildClassVector->Get(i);
#line 61 "../../../Source/Core/AST/TranslationUnit.nll"
			if (pChild->m_pClassDecl->m_pGenericTypeDeclVector->GetSize() > 0)
			{
#line 63 "../../../Source/Core/AST/TranslationUnit.nll"
				Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 64 "../../../Source/Core/AST/TranslationUnit.nll"
				pChild->m_pClassDecl->StringifyTemplateThing(eLanguage, eOutputFile, pOutputBuilder);
#line 65 "../../../Source/Core/AST/TranslationUnit.nll"
				pOutputBuilder->m_sOut->Append("\n");
			}
#line 68 "../../../Source/Core/AST/TranslationUnit.nll"
			Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 69 "../../../Source/Core/AST/TranslationUnit.nll"
			pOutputBuilder->m_sOut->Append("class ");
#line 70 "../../../Source/Core/AST/TranslationUnit.nll"
			pChild->m_pClassDecl->m_pNameToken->Stringify(pOutputBuilder->m_sOut);
#line 71 "../../../Source/Core/AST/TranslationUnit.nll"
			pOutputBuilder->m_sOut->Append(";\n");
		}
#line 74 "../../../Source/Core/AST/TranslationUnit.nll"
		if (!m_sName->IsEqual(""))
		{
#line 76 "../../../Source/Core/AST/TranslationUnit.nll"
			nDepth--;
#line 77 "../../../Source/Core/AST/TranslationUnit.nll"
			Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 78 "../../../Source/Core/AST/TranslationUnit.nll"
			pOutputBuilder->m_sOut->Append("}\n");
		}
	}

#line 10 "../../../Source/Core/AST/TranslationUnit.nll"
	ReferenceNode::~ReferenceNode()
	{
		if (m_sName) delete m_sName;
		if (m_pChildNodeVector) delete m_pChildNodeVector;
		if (m_pChildClassVector) delete m_pChildClassVector;
	}

#line 83 "../../../Source/Core/AST/TranslationUnit.nll"
#line 89 "../../../Source/Core/AST/TranslationUnit.nll"
	TranslationUnit::TranslationUnit(const char* sInFile)
	{
		m_sInFile = 0;
		m_pTokenContainer = 0;
		m_pClassDeclReferenceVector = 0;
#line 91 "../../../Source/Core/AST/TranslationUnit.nll"
		m_sInFile = new InternalString(sInFile);
#line 92 "../../../Source/Core/AST/TranslationUnit.nll"
		m_eType = Type::AST_TRANSLATION_UNIT;
#line 93 "../../../Source/Core/AST/TranslationUnit.nll"
		m_bCanDescend = true;
#line 95 "../../../Source/Core/AST/TranslationUnit.nll"
		m_pTokenContainer = new TokenContainer();
#line 96 "../../../Source/Core/AST/TranslationUnit.nll"
		m_pClassDeclReferenceVector = new OwnedVector<ClassDeclReference*>();
	}

#line 99 "../../../Source/Core/AST/TranslationUnit.nll"
	TranslationUnit* TranslationUnit::Create(const char* sInFile, OwnedVector<InternalString*>* sDefineVector)
	{
		TranslationUnit* pThis = new TranslationUnit(sInFile);
		InternalString* sInput = File::GetContents(pThis->m_sInFile->GetExternalString());
#line 106 "../../../Source/Core/AST/TranslationUnit.nll"
		pThis->m_pTokenContainer->Tokenize(sInput->GetExternalString(), pThis->m_sInFile, sDefineVector);
#line 107 "../../../Source/Core/AST/TranslationUnit.nll"
		pThis->m_pTokenContainer->StripWhitespace();
		OffsetDatum* pOffsetDatum = OffsetDatum::Create(0);
#line 112 "../../../Source/Core/AST/TranslationUnit.nll"
		while (pOffsetDatum->m_nOffset < pThis->m_pTokenContainer->m_pTokenVector->GetSize())
		{
			AST* pAST = AST::CreateFromTokenContainer(pThis->m_pTokenContainer, pOffsetDatum);
#line 115 "../../../Source/Core/AST/TranslationUnit.nll"
			if (pAST == 0)
			{
				if (pAST) delete pAST;
#line 116 "../../../Source/Core/AST/TranslationUnit.nll"
				break;
			}
			NumbatLogic::AST* __3057539430 = pAST;
#line 118 "../../../Source/Core/AST/TranslationUnit.nll"
			pAST = 0;
#line 118 "../../../Source/Core/AST/TranslationUnit.nll"
			pThis->AddChild(__3057539430);
			if (pAST) delete pAST;
		}
		NumbatLogic::TranslationUnit* __2058438882 = pThis;
#line 121 "../../../Source/Core/AST/TranslationUnit.nll"
		pThis = 0;
		if (sInput) delete sInput;
		if (pOffsetDatum) delete pOffsetDatum;
#line 121 "../../../Source/Core/AST/TranslationUnit.nll"
		return __2058438882;
	}

#line 124 "../../../Source/Core/AST/TranslationUnit.nll"
	void TranslationUnit::AddClassDeclReference(ClassDecl* pClassDecl, OutputFile eOutputFile, bool bForwardReference)
	{
#line 126 "../../../Source/Core/AST/TranslationUnit.nll"
		for (int i = 0; i < m_pClassDeclReferenceVector->GetSize(); i++)
		{
			ClassDeclReference* pTestClassDeclReference = m_pClassDeclReferenceVector->Get(i);
#line 129 "../../../Source/Core/AST/TranslationUnit.nll"
			if (pTestClassDeclReference->m_pClassDecl == pClassDecl && pTestClassDeclReference->m_eOutputFile == eOutputFile)
			{
#line 136 "../../../Source/Core/AST/TranslationUnit.nll"
				if (pTestClassDeclReference->m_bForwardReference == bForwardReference)
				{
#line 138 "../../../Source/Core/AST/TranslationUnit.nll"
					AST::AddClassDeclReference(pClassDecl, eOutputFile, bForwardReference);
#line 139 "../../../Source/Core/AST/TranslationUnit.nll"
					return;
				}
			}
		}
		ClassDeclReference* pClassDeclReference = new ClassDeclReference();
#line 145 "../../../Source/Core/AST/TranslationUnit.nll"
		pClassDeclReference->m_pClassDecl = pClassDecl;
#line 146 "../../../Source/Core/AST/TranslationUnit.nll"
		pClassDeclReference->m_eOutputFile = eOutputFile;
#line 147 "../../../Source/Core/AST/TranslationUnit.nll"
		pClassDeclReference->m_bForwardReference = bForwardReference;
		NumbatLogic::ClassDeclReference* __3931805821 = pClassDeclReference;
#line 149 "../../../Source/Core/AST/TranslationUnit.nll"
		pClassDeclReference = 0;
#line 149 "../../../Source/Core/AST/TranslationUnit.nll"
		m_pClassDeclReferenceVector->PushBack(__3931805821);
#line 151 "../../../Source/Core/AST/TranslationUnit.nll"
		AST::AddClassDeclReference(pClassDecl, eOutputFile, bForwardReference);
		if (pClassDeclReference) delete pClassDeclReference;
	}

#line 154 "../../../Source/Core/AST/TranslationUnit.nll"
	void TranslationUnit::ConvertFilePath(Language eLanguage, OutputFile eOutputFile, InternalString* sPath)
	{
#line 157 "../../../Source/Core/AST/TranslationUnit.nll"
		if (sPath->EndsWith(".nll.def"))
		{
			InternalString* sFolder = new InternalString("");
			InternalString* sFile = sPath->CreateClone();
#line 162 "../../../Source/Core/AST/TranslationUnit.nll"
			while (true)
			{
				int nIndex = sFile->FindChar('/');
#line 165 "../../../Source/Core/AST/TranslationUnit.nll"
				if (nIndex == -1)
#line 166 "../../../Source/Core/AST/TranslationUnit.nll"
					break;
				InternalString* sTemp = sFile->CreateClone();
#line 169 "../../../Source/Core/AST/TranslationUnit.nll"
				sTemp->SubStr(0, nIndex + 1);
#line 170 "../../../Source/Core/AST/TranslationUnit.nll"
				sFolder->Append(sTemp->GetExternalString());
#line 171 "../../../Source/Core/AST/TranslationUnit.nll"
				sFile->CropFront(nIndex + 1);
				if (sTemp) delete sTemp;
			}
#line 174 "../../../Source/Core/AST/TranslationUnit.nll"
			switch (eLanguage)
			{
				case AST::Language::CS:
				{
#line 178 "../../../Source/Core/AST/TranslationUnit.nll"
					sFolder->Append("CS/");
#line 179 "../../../Source/Core/AST/TranslationUnit.nll"
					sFile->Replace(".nll.def", ".cs");
#line 180 "../../../Source/Core/AST/TranslationUnit.nll"
					break;
				}

				case AST::Language::CPP:
				{
#line 184 "../../../Source/Core/AST/TranslationUnit.nll"
					sFolder->Append("CPP/");
#line 185 "../../../Source/Core/AST/TranslationUnit.nll"
					if (eOutputFile == AST::OutputFile::SOURCE)
#line 186 "../../../Source/Core/AST/TranslationUnit.nll"
						sFile->Replace(".nll.def", ".cpp");
					else
#line 188 "../../../Source/Core/AST/TranslationUnit.nll"
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
#line 201 "../../../Source/Core/AST/TranslationUnit.nll"
			sPath->Set(sFolder->GetExternalString());
#line 202 "../../../Source/Core/AST/TranslationUnit.nll"
			sPath->Append(sFile->GetExternalString());
			if (sFolder) delete sFolder;
			if (sFile) delete sFile;
#line 203 "../../../Source/Core/AST/TranslationUnit.nll"
			return;
		}
#line 207 "../../../Source/Core/AST/TranslationUnit.nll"
		sPath->Replace("Source", "Transpiled");
#line 210 "../../../Source/Core/AST/TranslationUnit.nll"
		switch (eLanguage)
		{
			case AST::Language::CS:
			{
#line 214 "../../../Source/Core/AST/TranslationUnit.nll"
				sPath->Replace(".nll", ".cs");
#line 215 "../../../Source/Core/AST/TranslationUnit.nll"
				break;
			}

			case AST::Language::CPP:
			{
#line 219 "../../../Source/Core/AST/TranslationUnit.nll"
				if (eOutputFile == AST::OutputFile::SOURCE)
#line 220 "../../../Source/Core/AST/TranslationUnit.nll"
					sPath->Replace(".nll", ".cpp");
				else
#line 222 "../../../Source/Core/AST/TranslationUnit.nll"
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
#line 231 "../../../Source/Core/AST/TranslationUnit.nll"
				sPath->Replace(".nll", ".nll.def");
#line 232 "../../../Source/Core/AST/TranslationUnit.nll"
				break;
			}

		}
	}

#line 237 "../../../Source/Core/AST/TranslationUnit.nll"
	InternalString* TranslationUnit::RetargetRelativePath(Language eLanguage, OutputFile eOutputFile, const char* sxFrom, const char* sxTo)
	{
		InternalString* sFrom = new InternalString(sxFrom);
		InternalString* sTo = new InternalString(sxTo);
#line 242 "../../../Source/Core/AST/TranslationUnit.nll"
		ConvertFilePath(eLanguage, eOutputFile, sFrom);
#line 243 "../../../Source/Core/AST/TranslationUnit.nll"
		ConvertFilePath(eLanguage, eOutputFile, sTo);
		OwnedVector<InternalString*>* sFromVector = new OwnedVector<InternalString*>();
		OwnedVector<InternalString*>* sToVector = new OwnedVector<InternalString*>();
#line 248 "../../../Source/Core/AST/TranslationUnit.nll"
		while (true)
		{
			int nIndex = sFrom->FindChar('/');
#line 251 "../../../Source/Core/AST/TranslationUnit.nll"
			if (nIndex == -1)
#line 252 "../../../Source/Core/AST/TranslationUnit.nll"
				break;
			InternalString* sTemp = sFrom->CreateClone();
#line 255 "../../../Source/Core/AST/TranslationUnit.nll"
			sTemp->SubStr(0, nIndex + 1);
#line 256 "../../../Source/Core/AST/TranslationUnit.nll"
			sFrom->CropFront(nIndex + 1);
			NumbatLogic::InternalString* __2784973933 = sTemp;
#line 257 "../../../Source/Core/AST/TranslationUnit.nll"
			sTemp = 0;
#line 257 "../../../Source/Core/AST/TranslationUnit.nll"
			sFromVector->PushBack(__2784973933);
			if (sTemp) delete sTemp;
		}
#line 260 "../../../Source/Core/AST/TranslationUnit.nll"
		while (true)
		{
			int nIndex = sTo->FindChar('/');
#line 263 "../../../Source/Core/AST/TranslationUnit.nll"
			if (nIndex == -1)
#line 264 "../../../Source/Core/AST/TranslationUnit.nll"
				break;
			InternalString* sTemp = sTo->CreateClone();
#line 267 "../../../Source/Core/AST/TranslationUnit.nll"
			sTemp->SubStr(0, nIndex + 1);
#line 268 "../../../Source/Core/AST/TranslationUnit.nll"
			sTo->CropFront(nIndex + 1);
			NumbatLogic::InternalString* __2785039534 = sTemp;
#line 269 "../../../Source/Core/AST/TranslationUnit.nll"
			sTemp = 0;
#line 269 "../../../Source/Core/AST/TranslationUnit.nll"
			sToVector->PushBack(__2785039534);
			if (sTemp) delete sTemp;
		}
#line 273 "../../../Source/Core/AST/TranslationUnit.nll"
		while (true)
		{
#line 275 "../../../Source/Core/AST/TranslationUnit.nll"
			if (sFromVector->GetSize() == 0 || sToVector->GetSize() == 0)
#line 276 "../../../Source/Core/AST/TranslationUnit.nll"
				break;
#line 278 "../../../Source/Core/AST/TranslationUnit.nll"
			if (!sFromVector->Get(0)->IsEqual(sToVector->Get(0)->GetExternalString()))
#line 279 "../../../Source/Core/AST/TranslationUnit.nll"
				break;
#line 281 "../../../Source/Core/AST/TranslationUnit.nll"
			sFromVector->Erase(0);
#line 282 "../../../Source/Core/AST/TranslationUnit.nll"
			sToVector->Erase(0);
		}
		InternalString* sOut = new InternalString("");
#line 287 "../../../Source/Core/AST/TranslationUnit.nll"
		for (int i = 0; i < sFromVector->GetSize(); i++)
#line 288 "../../../Source/Core/AST/TranslationUnit.nll"
			sOut->Append("../");
#line 289 "../../../Source/Core/AST/TranslationUnit.nll"
		for (int i = 0; i < sToVector->GetSize(); i++)
#line 290 "../../../Source/Core/AST/TranslationUnit.nll"
			sOut->Append(sToVector->Get(i)->GetExternalString());
#line 292 "../../../Source/Core/AST/TranslationUnit.nll"
		sOut->Append(sTo->GetExternalString());
		NumbatLogic::InternalString* __1173437905 = sOut;
#line 293 "../../../Source/Core/AST/TranslationUnit.nll"
		sOut = 0;
		if (sFrom) delete sFrom;
		if (sTo) delete sTo;
		if (sFromVector) delete sFromVector;
		if (sToVector) delete sToVector;
#line 293 "../../../Source/Core/AST/TranslationUnit.nll"
		return __1173437905;
	}

#line 296 "../../../Source/Core/AST/TranslationUnit.nll"
	void TranslationUnit::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 298 "../../../Source/Core/AST/TranslationUnit.nll"
		if (eLanguage == AST::Language::CPP)
		{
#line 300 "../../../Source/Core/AST/TranslationUnit.nll"
			if (eOutputFile == AST::OutputFile::HEADER)
			{
#line 302 "../../../Source/Core/AST/TranslationUnit.nll"
				pOutputBuilder->m_sOut->Append("#pragma once\n\n");
			}
			OwnedVector<InternalString*>* sPreviousIncludes = new OwnedVector<InternalString*>();
			ReferenceNode* pRootReferenceNode = new ReferenceNode("");
#line 308 "../../../Source/Core/AST/TranslationUnit.nll"
			for (int i = 0; i < m_pClassDeclReferenceVector->GetSize(); i++)
			{
				ClassDeclReference* pClassDeclReference = m_pClassDeclReferenceVector->Get(i);
#line 311 "../../../Source/Core/AST/TranslationUnit.nll"
				if (eOutputFile == pClassDeclReference->m_eOutputFile)
				{
					bool bOnlyInclude = !pClassDeclReference->m_bForwardReference;
#line 318 "../../../Source/Core/AST/TranslationUnit.nll"
					if (bOnlyInclude)
					{
#line 320 "../../../Source/Core/AST/TranslationUnit.nll"
						for (int j = 0; j < m_pClassDeclReferenceVector->GetSize(); j++)
						{
							ClassDeclReference* pTestClassDeclReference = m_pClassDeclReferenceVector->Get(j);
#line 323 "../../../Source/Core/AST/TranslationUnit.nll"
							if (pTestClassDeclReference->m_pClassDecl == pClassDeclReference->m_pClassDecl)
							{
#line 325 "../../../Source/Core/AST/TranslationUnit.nll"
								if (pTestClassDeclReference->m_eOutputFile == pClassDeclReference->m_eOutputFile)
								{
#line 327 "../../../Source/Core/AST/TranslationUnit.nll"
									if (pTestClassDeclReference->m_bForwardReference)
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
					if (pClassDeclReference->m_bForwardReference || bOnlyInclude)
					{
						Vector<InternalString*>* sNamespaceVector = new Vector<InternalString*>();
						NamespaceNode* pNamespaceNode = pClassDeclReference->m_pClassDecl->m_pNamespaceNode;
#line 341 "../../../Source/Core/AST/TranslationUnit.nll"
						while (pNamespaceNode != 0 && pNamespaceNode->m_sName != 0)
						{
#line 343 "../../../Source/Core/AST/TranslationUnit.nll"
							sNamespaceVector->PushFront(pNamespaceNode->m_sName);
#line 344 "../../../Source/Core/AST/TranslationUnit.nll"
							pNamespaceNode = pNamespaceNode->m_pParent;
						}
						ReferenceNode* pCurrentNode = pRootReferenceNode;
#line 349 "../../../Source/Core/AST/TranslationUnit.nll"
						for (int j = 0; j < sNamespaceVector->GetSize(); j++)
						{
							InternalString* sNamespace = sNamespaceVector->Get(j);
#line 352 "../../../Source/Core/AST/TranslationUnit.nll"
							pCurrentNode = pCurrentNode->GetOrCreateChildNode(sNamespace->GetExternalString());
						}
#line 355 "../../../Source/Core/AST/TranslationUnit.nll"
						pCurrentNode->m_pChildClassVector->PushBack(pClassDeclReference);
						if (sNamespaceVector) delete sNamespaceVector;
					}
#line 358 "../../../Source/Core/AST/TranslationUnit.nll"
					if (!pClassDeclReference->m_bForwardReference)
					{
						bool bFound = false;
#line 361 "../../../Source/Core/AST/TranslationUnit.nll"
						for (int j = 0; j < sPreviousIncludes->GetSize(); j++)
						{
							InternalString* sTemp = sPreviousIncludes->Get(j);
#line 364 "../../../Source/Core/AST/TranslationUnit.nll"
							if (sTemp->IsEqual(pClassDeclReference->m_pClassDecl->m_pNameToken->m_sFileName->GetExternalString()))
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
						sPreviousIncludes->PushBack(new InternalString(pClassDeclReference->m_pClassDecl->m_pNameToken->m_sFileName->GetExternalString()));
						InternalString* sFixedPath = RetargetRelativePath(eLanguage, AST::OutputFile::HEADER, m_pFirstChild->m_pFirstToken->m_sFileName->GetExternalString(), pClassDeclReference->m_pClassDecl->m_pNameToken->m_sFileName->GetExternalString());
#line 375 "../../../Source/Core/AST/TranslationUnit.nll"
						pOutputBuilder->m_sOut->Append("#include \"");
#line 376 "../../../Source/Core/AST/TranslationUnit.nll"
						pOutputBuilder->m_sOut->Append(sFixedPath->GetExternalString());
#line 377 "../../../Source/Core/AST/TranslationUnit.nll"
						pOutputBuilder->m_sOut->Append("\"\n");
						if (sFixedPath) delete sFixedPath;
					}
				}
			}
#line 382 "../../../Source/Core/AST/TranslationUnit.nll"
			if (sPreviousIncludes->GetSize() > 0)
#line 383 "../../../Source/Core/AST/TranslationUnit.nll"
				pOutputBuilder->m_sOut->Append("\n");
#line 384 "../../../Source/Core/AST/TranslationUnit.nll"
			pRootReferenceNode->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
			if (sPreviousIncludes) delete sPreviousIncludes;
			if (pRootReferenceNode) delete pRootReferenceNode;
		}
		AST* pChild = m_pFirstChild;
#line 388 "../../../Source/Core/AST/TranslationUnit.nll"
		while (pChild != 0)
		{
#line 390 "../../../Source/Core/AST/TranslationUnit.nll"
			if (!pChild->m_bSkipOutput)
			{
#line 392 "../../../Source/Core/AST/TranslationUnit.nll"
				pChild->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
#line 393 "../../../Source/Core/AST/TranslationUnit.nll"
				pOutputBuilder->m_sOut->AppendChar('\n');
			}
#line 395 "../../../Source/Core/AST/TranslationUnit.nll"
			pChild = pChild->m_pNextSibling;
		}
	}

#line 83 "../../../Source/Core/AST/TranslationUnit.nll"
	TranslationUnit::~TranslationUnit()
	{
		if (m_sInFile) delete m_sInFile;
		if (m_pTokenContainer) delete m_pTokenContainer;
		if (m_pClassDeclReferenceVector) delete m_pClassDeclReferenceVector;
	}

}

