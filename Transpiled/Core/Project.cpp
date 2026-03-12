#include "Project.hpp"
#include "AST/AST.hpp"
#include "AST/TranslationUnit.hpp"
#include "../../../LangShared/Vector/CPP/Vector.hpp"
#include "NamespaceNode.hpp"
#include "../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "../../../LangShared/Console/CPP/Console.hpp"
#include "../../../LangShared/Assert/CPP/Assert.hpp"
#include "../../../LangShared/Transpiled/Vector/OwnedVector.hpp"
#include "../../../LangShared/File/CPP/File.hpp"
#include "Validator.hpp"
#include "AST/NamespaceDecl.hpp"
#include "Token.hpp"
#include "TokenContainer.hpp"
#include "OutputBuilder.hpp"

namespace NumbatLogic
{
	class Project;
	class AST;
	class TranslationUnit;
	template <class T>
	class Vector;
	class NamespaceNode;
	class InternalString;
	class Console;
	class Assert;
	template <class T>
	class OwnedVector;
	class File;
	class Validator;
	class NamespaceDecl;
	class TokenContainer;
	class Token;
	class OutputBuilder;
}
#line 0 "../../../Source/Core/Project.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/Project.nll"
#line 9 "../../../Source/Core/Project.nll"
	Project::Project()
	{
		m_pTranslationUnitVector = 0;
		m_pRootNamespaceNode = 0;
		m_pValidator = 0;
#line 11 "../../../Source/Core/Project.nll"
		m_eType = AST::Type::AST_PROJECT;
		m_bCanDescend = true;
		m_pTranslationUnitVector = new Vector<TranslationUnit*>();
		m_pRootNamespaceNode = new NamespaceNode(0, 0);
		m_pValidator = 0;
	}

	void Project::AddFile(const char* sFile, OwnedVector<InternalString*>* sDefineVector)
	{
		for (int i = 0; i < m_pTranslationUnitVector->GetSize(); i++)
		{
			TranslationUnit* pTestTranslationUnit = m_pTranslationUnitVector->Get(i);
			if (pTestTranslationUnit->m_sInFile->IsEqual(sFile))
			{
#line 27 "../../../Source/Core/Project.nll"
				return;
			}
		}
#line 31 "../../../Source/Core/Project.nll"
		TranslationUnit* pTranslationUnit = TranslationUnit::Create(sFile, sDefineVector);
#line 33 "../../../Source/Core/Project.nll"
		if (pTranslationUnit == 0)
		{
			Console::Log("unable to parse file");
			Console::Log(sFile);
			Assert::Plz(false);
			if (pTranslationUnit) delete pTranslationUnit;
#line 38 "../../../Source/Core/Project.nll"
			return;
		}
#line 41 "../../../Source/Core/Project.nll"
		m_pTranslationUnitVector->PushBack(pTranslationUnit);
		NumbatLogic::TranslationUnit* __1501017379 = pTranslationUnit;
#line 42 "../../../Source/Core/Project.nll"
		pTranslationUnit = 0;
#line 42 "../../../Source/Core/Project.nll"
		AddChild(__1501017379);
		if (pTranslationUnit) delete pTranslationUnit;
	}

#line 45 "../../../Source/Core/Project.nll"
	void Project::AddDirectory(const char* sDirectory, OwnedVector<InternalString*>* sDefineVector)
	{
		OwnedVector<InternalString*>* sFileVector = File::GetRecursiveFileVector(sDirectory);
#line 49 "../../../Source/Core/Project.nll"
		while (sFileVector->GetSize() > 0)
		{
			InternalString* sFile = sFileVector->PopBack();
			AddFile(sFile->GetExternalString(), sDefineVector);
			if (sFile) delete sFile;
		}
		if (sFileVector) delete sFileVector;
	}

#line 56 "../../../Source/Core/Project.nll"
	void Project::FullValidate()
	{
#line 59 "../../../Source/Core/Project.nll"
		for (int i = 0; i < m_pTranslationUnitVector->GetSize(); i++)
		{
			TranslationUnit* pTranslationUnit = m_pTranslationUnitVector->Get(i);
			if (pTranslationUnit->m_sInFile->EndsWith(".nll"))
			{
				pTranslationUnit->m_sInFile->Replace("../LangShared", "../LangShared/Transpiled");
				if (pTranslationUnit->m_sInFile->StartsWith("Shared"))
					pTranslationUnit->m_sInFile->Replace("Shared", "Source/Shared");
				else
					pTranslationUnit->m_sInFile->Replace("/Shared", "/Source/Shared");
			}
		}
#line 73 "../../../Source/Core/Project.nll"
		m_pValidator = new Validator(this);
		if (!m_pValidator->Validate())
		{
		}
	}

#line 80 "../../../Source/Core/Project.nll"
	void Project::RecurseNamespaces(AST* pInAst, NamespaceDecl* pSecretNamespace, TranslationUnit* pSecretTranslationUnit)
	{
		if (pInAst->m_eType == AST::Type::AST_TRANSLATION_UNIT)
		{
			Assert::Plz(pSecretNamespace == 0);
		}
#line 87 "../../../Source/Core/Project.nll"
		AST* pChild = pInAst->m_pFirstChild;
		while (pChild != 0)
		{
			if (pChild->m_eType == AST::Type::NAMESPACE_DECL)
			{
				NamespaceDecl* pNamespaceDecl = (NamespaceDecl*)(pChild);
				if (pNamespaceDecl->m_pNameToken->m_sValue->IsEqual("Secret"))
				{
					AST* pNextChild = pChild;
					pNextChild = pChild->m_pNextSibling;
#line 98 "../../../Source/Core/Project.nll"
					AST* pOwnedChild = 0;
					pOwnedChild = pInAst->RemoveChild(pChild);
#line 101 "../../../Source/Core/Project.nll"
					Assert::Plz(pOwnedChild != 0);
#line 103 "../../../Source/Core/Project.nll"
					if (pSecretNamespace == 0)
					{
						NumbatLogic::AST* __2227940687 = pOwnedChild;
#line 105 "../../../Source/Core/Project.nll"
						pOwnedChild = 0;
#line 105 "../../../Source/Core/Project.nll"
						pSecretTranslationUnit->AddChild(__2227940687);
					}
					else
					{
						NumbatLogic::AST* __2227940691 = pOwnedChild;
#line 109 "../../../Source/Core/Project.nll"
						pOwnedChild = 0;
#line 109 "../../../Source/Core/Project.nll"
						pSecretNamespace->AddChild(__2227940691);
					}
#line 112 "../../../Source/Core/Project.nll"
					pChild = pNextChild;
					if (pOwnedChild) delete pOwnedChild;
#line 113 "../../../Source/Core/Project.nll"
					continue;
				}
#line 117 "../../../Source/Core/Project.nll"
				NamespaceDecl* pNextSecretNamespace = new NamespaceDecl();
				pNextSecretNamespace->m_pFirstToken = pNamespaceDecl->m_pFirstToken;
				pNextSecretNamespace->m_pNameToken = pNamespaceDecl->m_pNameToken;
				pNextSecretNamespace->m_bSkipOutput = pNamespaceDecl->m_bSkipOutput;
#line 122 "../../../Source/Core/Project.nll"
				NamespaceDecl* pTemp = pNextSecretNamespace;
				if (pSecretNamespace == 0)
				{
					NumbatLogic::NamespaceDecl* __4258634956 = pNextSecretNamespace;
#line 125 "../../../Source/Core/Project.nll"
					pNextSecretNamespace = 0;
#line 125 "../../../Source/Core/Project.nll"
					pSecretTranslationUnit->AddChild(__4258634956);
				}
				else
				{
					NumbatLogic::NamespaceDecl* __4258634960 = pNextSecretNamespace;
#line 129 "../../../Source/Core/Project.nll"
					pNextSecretNamespace = 0;
#line 129 "../../../Source/Core/Project.nll"
					pSecretNamespace->AddChild(__4258634960);
				}
#line 132 "../../../Source/Core/Project.nll"
				RecurseNamespaces(pNamespaceDecl, pTemp, pSecretTranslationUnit);
				if (pNextSecretNamespace) delete pNextSecretNamespace;
			}
			pChild = pChild->m_pNextSibling;
		}
	}

	void Project::NamespaceMerge(AST* pParentAST)
	{
		AST* pChild = pParentAST->m_pFirstChild;
		Vector<NamespaceDecl*>* pPreviousNamespaceDecls = new Vector<NamespaceDecl*>();
#line 144 "../../../Source/Core/Project.nll"
		while (pChild != 0)
		{
			if (pChild->m_eType == AST::Type::NAMESPACE_DECL)
			{
				NamespaceDecl* pNamespaceDecl = (NamespaceDecl*)(pChild);
				const char* sxName = pNamespaceDecl->m_pNameToken->m_sValue->GetExternalString();
				int i = 0;
				for (i = 0; i < pPreviousNamespaceDecls->GetSize(); i++)
				{
					NamespaceDecl* pPreviousNamespace = pPreviousNamespaceDecls->Get(i);
					if (pPreviousNamespace->m_pNameToken->m_sValue->IsEqual(sxName) && pPreviousNamespace->m_bSkipOutput == pNamespaceDecl->m_bSkipOutput)
					{
						AST* pNextSibling = pChild->m_pNextSibling;
						AST* pOwnedChild = 0;
						pOwnedChild = pParentAST->RemoveChild(pChild);
#line 160 "../../../Source/Core/Project.nll"
						AST* pSubChild = 0;
						NumbatLogic::AST* __2552901754 = pOwnedChild->m_pFirstChild;
#line 161 "../../../Source/Core/Project.nll"
						pOwnedChild->m_pFirstChild = 0;
#line 161 "../../../Source/Core/Project.nll"
						pSubChild = __2552901754;
						pOwnedChild->m_pLastChild = 0;
#line 164 "../../../Source/Core/Project.nll"
						if (pSubChild != 0)
						{
							pSubChild->m_pParent = pPreviousNamespace;
							if (pPreviousNamespace->m_pFirstChild == 0)
							{
								NumbatLogic::AST* __2417707016 = pSubChild;
#line 169 "../../../Source/Core/Project.nll"
								pSubChild = 0;
#line 169 "../../../Source/Core/Project.nll"
								pPreviousNamespace->m_pFirstChild = __2417707016;
								pPreviousNamespace->m_pLastChild = pPreviousNamespace->m_pFirstChild;
							}
							else
							{
								NumbatLogic::AST* __2417772610 = pSubChild;
#line 174 "../../../Source/Core/Project.nll"
								pSubChild = 0;
#line 174 "../../../Source/Core/Project.nll"
								pPreviousNamespace->m_pLastChild->m_pNextSibling = __2417772610;
								pPreviousNamespace->m_pLastChild->m_pNextSibling->m_pPrevSibling = pPreviousNamespace->m_pLastChild;
							}
#line 178 "../../../Source/Core/Project.nll"
							while (pPreviousNamespace->m_pLastChild->m_pNextSibling != 0)
							{
								pPreviousNamespace->m_pLastChild = pPreviousNamespace->m_pLastChild->m_pNextSibling;
								pPreviousNamespace->m_pLastChild->m_pParent = pPreviousNamespace;
							}
						}
#line 185 "../../../Source/Core/Project.nll"
						pChild = pNextSibling;
						if (pOwnedChild) delete pOwnedChild;
						if (pSubChild) delete pSubChild;
#line 186 "../../../Source/Core/Project.nll"
						break;
					}
				}
#line 190 "../../../Source/Core/Project.nll"
				if (i == pPreviousNamespaceDecls->GetSize())
				{
					pPreviousNamespaceDecls->PushBack(pNamespaceDecl);
				}
				else
				{
					continue;
				}
			}
#line 200 "../../../Source/Core/Project.nll"
			pChild = pChild->m_pNextSibling;
		}
		{
#line 204 "../../../Source/Core/Project.nll"
			for (int i = 0; i < pPreviousNamespaceDecls->GetSize(); i++)
			{
				NamespaceDecl* pPreviousNamespace = pPreviousNamespaceDecls->Get(i);
				NamespaceMerge(pPreviousNamespace);
			}
		}
		if (pPreviousNamespaceDecls) delete pPreviousNamespaceDecls;
	}

#line 212 "../../../Source/Core/Project.nll"
	void Project::Amalgamate(const char* sAmalgamateFileName)
	{
#line 215 "../../../Source/Core/Project.nll"
		InternalString* sSecretFileName = new InternalString(sAmalgamateFileName);
		sSecretFileName->Replace(".nll", "Secret.nll");
		TranslationUnit* pSecretTranslationUnit = new TranslationUnit(sSecretFileName->GetExternalString());
		TranslationUnit* pPublicTranslationUnit = new TranslationUnit(sAmalgamateFileName);
#line 220 "../../../Source/Core/Project.nll"
		while (m_pFirstChild != 0)
		{
			AST* pAST = 0;
			pAST = RemoveChild(m_pFirstChild);
#line 225 "../../../Source/Core/Project.nll"
			TranslationUnit* pTranslationUnit = (TranslationUnit*)(pAST);
			bool bSkipOutput = pTranslationUnit->m_sInFile->EndsWith(".nll.def");
#line 229 "../../../Source/Core/Project.nll"
			while (pTranslationUnit->m_pTokenContainer->m_pTokenVector->GetSize() > 0)
			{
				Token* pToken = pTranslationUnit->m_pTokenContainer->m_pTokenVector->PopFront();
				pToken->m_sFileName = pPublicTranslationUnit->m_sInFile;
				NumbatLogic::Token* __3778855881 = pToken;
#line 233 "../../../Source/Core/Project.nll"
				pToken = 0;
#line 233 "../../../Source/Core/Project.nll"
				pPublicTranslationUnit->m_pTokenContainer->m_pTokenVector->PushBack(__3778855881);
				if (pToken) delete pToken;
			}
			if (pPublicTranslationUnit->m_pFirstChild == 0)
			{
				NumbatLogic::AST* __4061733424 = pAST->m_pFirstChild;
#line 238 "../../../Source/Core/Project.nll"
				pAST->m_pFirstChild = 0;
#line 238 "../../../Source/Core/Project.nll"
				pPublicTranslationUnit->m_pFirstChild = __4061733424;
				pPublicTranslationUnit->m_pLastChild = pPublicTranslationUnit->m_pFirstChild;
			}
			else
			{
				NumbatLogic::AST* __4061799018 = pAST->m_pFirstChild;
#line 243 "../../../Source/Core/Project.nll"
				pAST->m_pFirstChild = 0;
#line 243 "../../../Source/Core/Project.nll"
				pPublicTranslationUnit->m_pLastChild->m_pNextSibling = __4061799018;
				pPublicTranslationUnit->m_pLastChild = pPublicTranslationUnit->m_pLastChild->m_pNextSibling;
			}
#line 247 "../../../Source/Core/Project.nll"
			while (true)
			{
				pPublicTranslationUnit->m_pLastChild->m_pParent = pPublicTranslationUnit;
				pPublicTranslationUnit->m_pLastChild->m_bSkipOutput = bSkipOutput;
#line 252 "../../../Source/Core/Project.nll"
				if (pPublicTranslationUnit->m_pLastChild->m_pNextSibling == 0)
					break;
#line 255 "../../../Source/Core/Project.nll"
				pPublicTranslationUnit->m_pLastChild = pPublicTranslationUnit->m_pLastChild->m_pNextSibling;
			}
			if (pAST) delete pAST;
		}
		while (m_pTranslationUnitVector->GetSize() > 0)
		{
			m_pTranslationUnitVector->PopBack();
		}
#line 264 "../../../Source/Core/Project.nll"
		NamespaceMerge(pPublicTranslationUnit);
#line 267 "../../../Source/Core/Project.nll"
		RecurseNamespaces(pPublicTranslationUnit, 0, pSecretTranslationUnit);
#line 269 "../../../Source/Core/Project.nll"
		m_pTranslationUnitVector->PushBack(pSecretTranslationUnit);
		NumbatLogic::TranslationUnit* __1635259254 = pSecretTranslationUnit;
#line 270 "../../../Source/Core/Project.nll"
		pSecretTranslationUnit = 0;
#line 270 "../../../Source/Core/Project.nll"
		AddChild(__1635259254);
#line 272 "../../../Source/Core/Project.nll"
		m_pTranslationUnitVector->PushBack(pPublicTranslationUnit);
		NumbatLogic::TranslationUnit* __623321714 = pPublicTranslationUnit;
#line 273 "../../../Source/Core/Project.nll"
		pPublicTranslationUnit = 0;
#line 273 "../../../Source/Core/Project.nll"
		AddChild(__623321714);
		if (sSecretFileName) delete sSecretFileName;
		if (pSecretTranslationUnit) delete pSecretTranslationUnit;
		if (pPublicTranslationUnit) delete pPublicTranslationUnit;
	}

#line 276 "../../../Source/Core/Project.nll"
	void Project::Output(AST::Language eLanguage, OutputFile eOutputFile)
	{
		InternalString* sOutFile = new InternalString("");
		OutputBuilder* pOut = new OutputBuilder();
#line 282 "../../../Source/Core/Project.nll"
		for (int i = 0; i < m_pTranslationUnitVector->GetSize(); i++)
		{
			TranslationUnit* pTranslationUnit = m_pTranslationUnitVector->Get(i);
			sOutFile->Set(pTranslationUnit->m_sInFile->GetExternalString());
#line 287 "../../../Source/Core/Project.nll"
			if (sOutFile->EndsWith(".nll"))
			{
				TranslationUnit::ConvertFilePath(eLanguage, eOutputFile, sOutFile);
#line 291 "../../../Source/Core/Project.nll"
				const char* sxOutFile = sOutFile->GetExternalString();
#line 293 "../../../Source/Core/Project.nll"
				pOut->m_sOut->Set("");
				pTranslationUnit->Stringify(eLanguage, eOutputFile, 0, pOut);
#line 296 "../../../Source/Core/Project.nll"
				InternalString* sDirectory = File::GetFileDirectory(sxOutFile);
				File::CreateDirectory(sDirectory->GetExternalString());
#line 300 "../../../Source/Core/Project.nll"
				InternalString* sTestFile = File::GetContents(sxOutFile);
				if (sTestFile == 0 || !pOut->m_sOut->IsEqual(sTestFile->GetExternalString()))
				{
					File::PutContents(sxOutFile, pOut->m_sOut->GetExternalString());
				}
				if (sDirectory) delete sDirectory;
				if (sTestFile) delete sTestFile;
			}
		}
		if (sOutFile) delete sOutFile;
		if (pOut) delete pOut;
	}

#line 3 "../../../Source/Core/Project.nll"
	Project::~Project()
	{
		if (m_pTranslationUnitVector) delete m_pTranslationUnitVector;
		if (m_pRootNamespaceNode) delete m_pRootNamespaceNode;
		if (m_pValidator) delete m_pValidator;
	}

}

