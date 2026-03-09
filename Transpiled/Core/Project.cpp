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
#line 1 "../../../Source/Core/Project.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/Project.nll"
#line 10 "../../../Source/Core/Project.nll"
	Project::Project()
	{
		m_pTranslationUnitVector = 0;
		m_pRootNamespaceNode = 0;
		m_pValidator = 0;
#line 12 "../../../Source/Core/Project.nll"
		m_eType = AST::Type::AST_PROJECT;
#line 13 "../../../Source/Core/Project.nll"
		m_bCanDescend = true;
#line 14 "../../../Source/Core/Project.nll"
		m_pTranslationUnitVector = new Vector<TranslationUnit*>();
#line 15 "../../../Source/Core/Project.nll"
		m_pRootNamespaceNode = new NamespaceNode(0, 0);
#line 16 "../../../Source/Core/Project.nll"
		m_pValidator = 0;
	}

#line 19 "../../../Source/Core/Project.nll"
	void Project::AddFile(const char* sFile, OwnedVector<InternalString*>* sDefineVector)
	{
#line 21 "../../../Source/Core/Project.nll"
		for (int i = 0; i < m_pTranslationUnitVector->GetSize(); i++)
		{
			TranslationUnit* pTestTranslationUnit = m_pTranslationUnitVector->Get(i);
#line 24 "../../../Source/Core/Project.nll"
			if (pTestTranslationUnit->m_sInFile->IsEqual(sFile))
			{
#line 28 "../../../Source/Core/Project.nll"
				return;
			}
		}
		TranslationUnit* pTranslationUnit = TranslationUnit::Create(sFile, sDefineVector);
#line 34 "../../../Source/Core/Project.nll"
		if (pTranslationUnit == 0)
		{
#line 36 "../../../Source/Core/Project.nll"
			Console::Log("unable to parse file");
#line 37 "../../../Source/Core/Project.nll"
			Console::Log(sFile);
#line 38 "../../../Source/Core/Project.nll"
			Assert::Plz(false);
			if (pTranslationUnit) delete pTranslationUnit;
#line 39 "../../../Source/Core/Project.nll"
			return;
		}
#line 42 "../../../Source/Core/Project.nll"
		m_pTranslationUnitVector->PushBack(pTranslationUnit);
		NumbatLogic::TranslationUnit* __1501017379 = pTranslationUnit;
#line 43 "../../../Source/Core/Project.nll"
		pTranslationUnit = 0;
#line 43 "../../../Source/Core/Project.nll"
		AddChild(__1501017379);
		if (pTranslationUnit) delete pTranslationUnit;
	}

#line 46 "../../../Source/Core/Project.nll"
	void Project::AddDirectory(const char* sDirectory, OwnedVector<InternalString*>* sDefineVector)
	{
		OwnedVector<InternalString*>* sFileVector = File::GetRecursiveFileVector(sDirectory);
#line 50 "../../../Source/Core/Project.nll"
		while (sFileVector->GetSize() > 0)
		{
			InternalString* sFile = sFileVector->PopBack();
#line 53 "../../../Source/Core/Project.nll"
			AddFile(sFile->GetExternalString(), sDefineVector);
			if (sFile) delete sFile;
		}
		if (sFileVector) delete sFileVector;
	}

#line 57 "../../../Source/Core/Project.nll"
	void Project::FullValidate()
	{
#line 60 "../../../Source/Core/Project.nll"
		for (int i = 0; i < m_pTranslationUnitVector->GetSize(); i++)
		{
			TranslationUnit* pTranslationUnit = m_pTranslationUnitVector->Get(i);
#line 63 "../../../Source/Core/Project.nll"
			if (pTranslationUnit->m_sInFile->EndsWith(".nll"))
			{
#line 65 "../../../Source/Core/Project.nll"
				pTranslationUnit->m_sInFile->Replace("../LangShared", "../LangShared/Transpiled");
#line 66 "../../../Source/Core/Project.nll"
				if (pTranslationUnit->m_sInFile->StartsWith("Shared"))
#line 67 "../../../Source/Core/Project.nll"
					pTranslationUnit->m_sInFile->Replace("Shared", "Source/Shared");
				else
#line 69 "../../../Source/Core/Project.nll"
					pTranslationUnit->m_sInFile->Replace("/Shared", "/Source/Shared");
			}
		}
#line 74 "../../../Source/Core/Project.nll"
		m_pValidator = new Validator(this);
#line 75 "../../../Source/Core/Project.nll"
		if (!m_pValidator->Validate())
		{
		}
	}

#line 81 "../../../Source/Core/Project.nll"
	void Project::RecurseNamespaces(AST* pInAst, NamespaceDecl* pSecretNamespace, TranslationUnit* pSecretTranslationUnit)
	{
#line 83 "../../../Source/Core/Project.nll"
		if (pInAst->m_eType == AST::Type::AST_TRANSLATION_UNIT)
		{
#line 85 "../../../Source/Core/Project.nll"
			Assert::Plz(pSecretNamespace == 0);
		}
		AST* pChild = pInAst->m_pFirstChild;
#line 89 "../../../Source/Core/Project.nll"
		while (pChild != 0)
		{
#line 91 "../../../Source/Core/Project.nll"
			if (pChild->m_eType == AST::Type::NAMESPACE_DECL)
			{
				NamespaceDecl* pNamespaceDecl = (NamespaceDecl*)(pChild);
#line 94 "../../../Source/Core/Project.nll"
				if (pNamespaceDecl->m_pNameToken->m_sValue->IsEqual("Secret"))
				{
					AST* pNextChild = pChild;
#line 97 "../../../Source/Core/Project.nll"
					pNextChild = pChild->m_pNextSibling;
					AST* pOwnedChild = 0;
#line 100 "../../../Source/Core/Project.nll"
					pOwnedChild = pInAst->RemoveChild(pChild);
#line 102 "../../../Source/Core/Project.nll"
					Assert::Plz(pOwnedChild != 0);
#line 104 "../../../Source/Core/Project.nll"
					if (pSecretNamespace == 0)
					{
						NumbatLogic::AST* __2227940687 = pOwnedChild;
#line 106 "../../../Source/Core/Project.nll"
						pOwnedChild = 0;
#line 106 "../../../Source/Core/Project.nll"
						pSecretTranslationUnit->AddChild(__2227940687);
					}
					else
					{
						NumbatLogic::AST* __2227940691 = pOwnedChild;
#line 110 "../../../Source/Core/Project.nll"
						pOwnedChild = 0;
#line 110 "../../../Source/Core/Project.nll"
						pSecretNamespace->AddChild(__2227940691);
					}
#line 113 "../../../Source/Core/Project.nll"
					pChild = pNextChild;
					if (pOwnedChild) delete pOwnedChild;
#line 114 "../../../Source/Core/Project.nll"
					continue;
				}
				NamespaceDecl* pNextSecretNamespace = new NamespaceDecl();
#line 119 "../../../Source/Core/Project.nll"
				pNextSecretNamespace->m_pFirstToken = pNamespaceDecl->m_pFirstToken;
#line 120 "../../../Source/Core/Project.nll"
				pNextSecretNamespace->m_pNameToken = pNamespaceDecl->m_pNameToken;
#line 121 "../../../Source/Core/Project.nll"
				pNextSecretNamespace->m_bSkipOutput = pNamespaceDecl->m_bSkipOutput;
				NamespaceDecl* pTemp = pNextSecretNamespace;
#line 124 "../../../Source/Core/Project.nll"
				if (pSecretNamespace == 0)
				{
					NumbatLogic::NamespaceDecl* __4258634956 = pNextSecretNamespace;
#line 126 "../../../Source/Core/Project.nll"
					pNextSecretNamespace = 0;
#line 126 "../../../Source/Core/Project.nll"
					pSecretTranslationUnit->AddChild(__4258634956);
				}
				else
				{
					NumbatLogic::NamespaceDecl* __4258634960 = pNextSecretNamespace;
#line 130 "../../../Source/Core/Project.nll"
					pNextSecretNamespace = 0;
#line 130 "../../../Source/Core/Project.nll"
					pSecretNamespace->AddChild(__4258634960);
				}
#line 133 "../../../Source/Core/Project.nll"
				RecurseNamespaces(pNamespaceDecl, pTemp, pSecretTranslationUnit);
				if (pNextSecretNamespace) delete pNextSecretNamespace;
			}
#line 136 "../../../Source/Core/Project.nll"
			pChild = pChild->m_pNextSibling;
		}
	}

#line 140 "../../../Source/Core/Project.nll"
	void Project::NamespaceMerge(AST* pParentAST)
	{
		AST* pChild = pParentAST->m_pFirstChild;
		Vector<NamespaceDecl*>* pPreviousNamespaceDecls = new Vector<NamespaceDecl*>();
#line 145 "../../../Source/Core/Project.nll"
		while (pChild != 0)
		{
#line 147 "../../../Source/Core/Project.nll"
			if (pChild->m_eType == AST::Type::NAMESPACE_DECL)
			{
				NamespaceDecl* pNamespaceDecl = (NamespaceDecl*)(pChild);
				const char* sxName = pNamespaceDecl->m_pNameToken->m_sValue->GetExternalString();
				int i = 0;
#line 152 "../../../Source/Core/Project.nll"
				for (i = 0; i < pPreviousNamespaceDecls->GetSize(); i++)
				{
					NamespaceDecl* pPreviousNamespace = pPreviousNamespaceDecls->Get(i);
#line 155 "../../../Source/Core/Project.nll"
					if (pPreviousNamespace->m_pNameToken->m_sValue->IsEqual(sxName) && pPreviousNamespace->m_bSkipOutput == pNamespaceDecl->m_bSkipOutput)
					{
						AST* pNextSibling = pChild->m_pNextSibling;
						AST* pOwnedChild = 0;
#line 159 "../../../Source/Core/Project.nll"
						pOwnedChild = pParentAST->RemoveChild(pChild);
						AST* pSubChild = 0;
						NumbatLogic::AST* __2552901754 = pOwnedChild->m_pFirstChild;
#line 162 "../../../Source/Core/Project.nll"
						pOwnedChild->m_pFirstChild = 0;
#line 162 "../../../Source/Core/Project.nll"
						pSubChild = __2552901754;
#line 163 "../../../Source/Core/Project.nll"
						pOwnedChild->m_pLastChild = 0;
#line 165 "../../../Source/Core/Project.nll"
						if (pSubChild != 0)
						{
#line 167 "../../../Source/Core/Project.nll"
							pSubChild->m_pParent = pPreviousNamespace;
#line 168 "../../../Source/Core/Project.nll"
							if (pPreviousNamespace->m_pFirstChild == 0)
							{
								NumbatLogic::AST* __2417707016 = pSubChild;
#line 170 "../../../Source/Core/Project.nll"
								pSubChild = 0;
#line 170 "../../../Source/Core/Project.nll"
								pPreviousNamespace->m_pFirstChild = __2417707016;
#line 171 "../../../Source/Core/Project.nll"
								pPreviousNamespace->m_pLastChild = pPreviousNamespace->m_pFirstChild;
							}
							else
							{
								NumbatLogic::AST* __2417772610 = pSubChild;
#line 175 "../../../Source/Core/Project.nll"
								pSubChild = 0;
#line 175 "../../../Source/Core/Project.nll"
								pPreviousNamespace->m_pLastChild->m_pNextSibling = __2417772610;
#line 176 "../../../Source/Core/Project.nll"
								pPreviousNamespace->m_pLastChild->m_pNextSibling->m_pPrevSibling = pPreviousNamespace->m_pLastChild;
							}
#line 179 "../../../Source/Core/Project.nll"
							while (pPreviousNamespace->m_pLastChild->m_pNextSibling != 0)
							{
#line 181 "../../../Source/Core/Project.nll"
								pPreviousNamespace->m_pLastChild = pPreviousNamespace->m_pLastChild->m_pNextSibling;
#line 182 "../../../Source/Core/Project.nll"
								pPreviousNamespace->m_pLastChild->m_pParent = pPreviousNamespace;
							}
						}
#line 186 "../../../Source/Core/Project.nll"
						pChild = pNextSibling;
						if (pOwnedChild) delete pOwnedChild;
						if (pSubChild) delete pSubChild;
#line 187 "../../../Source/Core/Project.nll"
						break;
					}
				}
#line 191 "../../../Source/Core/Project.nll"
				if (i == pPreviousNamespaceDecls->GetSize())
				{
#line 193 "../../../Source/Core/Project.nll"
					pPreviousNamespaceDecls->PushBack(pNamespaceDecl);
				}
				else
				{
#line 197 "../../../Source/Core/Project.nll"
					continue;
				}
			}
#line 201 "../../../Source/Core/Project.nll"
			pChild = pChild->m_pNextSibling;
		}
		{
#line 205 "../../../Source/Core/Project.nll"
			for (int i = 0; i < pPreviousNamespaceDecls->GetSize(); i++)
			{
				NamespaceDecl* pPreviousNamespace = pPreviousNamespaceDecls->Get(i);
#line 208 "../../../Source/Core/Project.nll"
				NamespaceMerge(pPreviousNamespace);
			}
		}
		if (pPreviousNamespaceDecls) delete pPreviousNamespaceDecls;
	}

#line 213 "../../../Source/Core/Project.nll"
	void Project::Amalgamate(const char* sAmalgamateFileName)
	{
		InternalString* sSecretFileName = new InternalString(sAmalgamateFileName);
#line 217 "../../../Source/Core/Project.nll"
		sSecretFileName->Replace(".nll", "Secret.nll");
		TranslationUnit* pSecretTranslationUnit = new TranslationUnit(sSecretFileName->GetExternalString());
		TranslationUnit* pPublicTranslationUnit = new TranslationUnit(sAmalgamateFileName);
#line 221 "../../../Source/Core/Project.nll"
		while (m_pFirstChild != 0)
		{
			AST* pAST = 0;
#line 224 "../../../Source/Core/Project.nll"
			pAST = RemoveChild(m_pFirstChild);
			TranslationUnit* pTranslationUnit = (TranslationUnit*)(pAST);
			bool bSkipOutput = pTranslationUnit->m_sInFile->EndsWith(".nll.def");
#line 230 "../../../Source/Core/Project.nll"
			while (pTranslationUnit->m_pTokenContainer->m_pTokenVector->GetSize() > 0)
			{
				Token* pToken = pTranslationUnit->m_pTokenContainer->m_pTokenVector->PopFront();
#line 233 "../../../Source/Core/Project.nll"
				pToken->m_sFileName = pPublicTranslationUnit->m_sInFile;
				NumbatLogic::Token* __3778855881 = pToken;
#line 234 "../../../Source/Core/Project.nll"
				pToken = 0;
#line 234 "../../../Source/Core/Project.nll"
				pPublicTranslationUnit->m_pTokenContainer->m_pTokenVector->PushBack(__3778855881);
				if (pToken) delete pToken;
			}
#line 237 "../../../Source/Core/Project.nll"
			if (pPublicTranslationUnit->m_pFirstChild == 0)
			{
				NumbatLogic::AST* __4061733424 = pAST->m_pFirstChild;
#line 239 "../../../Source/Core/Project.nll"
				pAST->m_pFirstChild = 0;
#line 239 "../../../Source/Core/Project.nll"
				pPublicTranslationUnit->m_pFirstChild = __4061733424;
#line 240 "../../../Source/Core/Project.nll"
				pPublicTranslationUnit->m_pLastChild = pPublicTranslationUnit->m_pFirstChild;
			}
			else
			{
				NumbatLogic::AST* __4061799018 = pAST->m_pFirstChild;
#line 244 "../../../Source/Core/Project.nll"
				pAST->m_pFirstChild = 0;
#line 244 "../../../Source/Core/Project.nll"
				pPublicTranslationUnit->m_pLastChild->m_pNextSibling = __4061799018;
#line 245 "../../../Source/Core/Project.nll"
				pPublicTranslationUnit->m_pLastChild = pPublicTranslationUnit->m_pLastChild->m_pNextSibling;
			}
#line 248 "../../../Source/Core/Project.nll"
			while (true)
			{
#line 250 "../../../Source/Core/Project.nll"
				pPublicTranslationUnit->m_pLastChild->m_pParent = pPublicTranslationUnit;
#line 251 "../../../Source/Core/Project.nll"
				pPublicTranslationUnit->m_pLastChild->m_bSkipOutput = bSkipOutput;
#line 253 "../../../Source/Core/Project.nll"
				if (pPublicTranslationUnit->m_pLastChild->m_pNextSibling == 0)
#line 254 "../../../Source/Core/Project.nll"
					break;
#line 256 "../../../Source/Core/Project.nll"
				pPublicTranslationUnit->m_pLastChild = pPublicTranslationUnit->m_pLastChild->m_pNextSibling;
			}
			if (pAST) delete pAST;
		}
#line 260 "../../../Source/Core/Project.nll"
		while (m_pTranslationUnitVector->GetSize() > 0)
		{
#line 262 "../../../Source/Core/Project.nll"
			m_pTranslationUnitVector->PopBack();
		}
#line 265 "../../../Source/Core/Project.nll"
		NamespaceMerge(pPublicTranslationUnit);
#line 268 "../../../Source/Core/Project.nll"
		RecurseNamespaces(pPublicTranslationUnit, 0, pSecretTranslationUnit);
#line 270 "../../../Source/Core/Project.nll"
		m_pTranslationUnitVector->PushBack(pSecretTranslationUnit);
		NumbatLogic::TranslationUnit* __1635259254 = pSecretTranslationUnit;
#line 271 "../../../Source/Core/Project.nll"
		pSecretTranslationUnit = 0;
#line 271 "../../../Source/Core/Project.nll"
		AddChild(__1635259254);
#line 273 "../../../Source/Core/Project.nll"
		m_pTranslationUnitVector->PushBack(pPublicTranslationUnit);
		NumbatLogic::TranslationUnit* __623321714 = pPublicTranslationUnit;
#line 274 "../../../Source/Core/Project.nll"
		pPublicTranslationUnit = 0;
#line 274 "../../../Source/Core/Project.nll"
		AddChild(__623321714);
		if (sSecretFileName) delete sSecretFileName;
		if (pSecretTranslationUnit) delete pSecretTranslationUnit;
		if (pPublicTranslationUnit) delete pPublicTranslationUnit;
	}

#line 277 "../../../Source/Core/Project.nll"
	void Project::Output(AST::Language eLanguage, OutputFile eOutputFile)
	{
		InternalString* sOutFile = new InternalString("");
		OutputBuilder* out = new OutputBuilder();
#line 283 "../../../Source/Core/Project.nll"
		for (int i = 0; i < m_pTranslationUnitVector->GetSize(); i++)
		{
			TranslationUnit* pTranslationUnit = m_pTranslationUnitVector->Get(i);
#line 286 "../../../Source/Core/Project.nll"
			sOutFile->Set(pTranslationUnit->m_sInFile->GetExternalString());
#line 288 "../../../Source/Core/Project.nll"
			if (sOutFile->EndsWith(".nll"))
			{
#line 290 "../../../Source/Core/Project.nll"
				TranslationUnit::ConvertFilePath(eLanguage, eOutputFile, sOutFile);
				const char* sxOutFile = sOutFile->GetExternalString();
#line 294 "../../../Source/Core/Project.nll"
				out->m_sOut->Set("");
#line 295 "../../../Source/Core/Project.nll"
				pTranslationUnit->Stringify(eLanguage, eOutputFile, 0, out);
				InternalString* sDirectory = File::GetFileDirectory(sxOutFile);
#line 298 "../../../Source/Core/Project.nll"
				File::CreateDirectory(sDirectory->GetExternalString());
				InternalString* sTestFile = File::GetContents(sxOutFile);
#line 302 "../../../Source/Core/Project.nll"
				if (sTestFile == 0 || !out->m_sOut->IsEqual(sTestFile->GetExternalString()))
				{
#line 304 "../../../Source/Core/Project.nll"
					File::PutContents(sxOutFile, out->m_sOut->GetExternalString());
				}
				if (sDirectory) delete sDirectory;
				if (sTestFile) delete sTestFile;
			}
		}
		if (sOutFile) delete sOutFile;
		if (out) delete out;
	}

#line 4 "../../../Source/Core/Project.nll"
	Project::~Project()
	{
		if (m_pTranslationUnitVector) delete m_pTranslationUnitVector;
		if (m_pRootNamespaceNode) delete m_pRootNamespaceNode;
		if (m_pValidator) delete m_pValidator;
	}

}

