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
#line 12 "../../../Source/Core/Project.nll"
		m_bCanDescend = true;
#line 13 "../../../Source/Core/Project.nll"
		m_pTranslationUnitVector = new Vector<TranslationUnit*>();
#line 14 "../../../Source/Core/Project.nll"
		m_pRootNamespaceNode = new NamespaceNode(0, 0);
#line 15 "../../../Source/Core/Project.nll"
		m_pValidator = 0;
	}

#line 18 "../../../Source/Core/Project.nll"
	void Project::AddFile(const char* sFile, OwnedVector<InternalString*>* sDefineVector)
	{
#line 20 "../../../Source/Core/Project.nll"
		for (int i = 0; i < m_pTranslationUnitVector->GetSize(); i++)
		{
#line 22 "../../../Source/Core/Project.nll"
			TranslationUnit* pTestTranslationUnit = m_pTranslationUnitVector->Get(i);
#line 23 "../../../Source/Core/Project.nll"
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
#line 35 "../../../Source/Core/Project.nll"
			Console::Log("unable to parse file");
#line 36 "../../../Source/Core/Project.nll"
			Console::Log(sFile);
#line 37 "../../../Source/Core/Project.nll"
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
#line 47 "../../../Source/Core/Project.nll"
		OwnedVector<InternalString*>* sFileVector = File::GetRecursiveFileVector(sDirectory);
#line 49 "../../../Source/Core/Project.nll"
		while (sFileVector->GetSize() > 0)
		{
#line 51 "../../../Source/Core/Project.nll"
			InternalString* sFile = sFileVector->PopBack();
#line 52 "../../../Source/Core/Project.nll"
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
#line 61 "../../../Source/Core/Project.nll"
			TranslationUnit* pTranslationUnit = m_pTranslationUnitVector->Get(i);
#line 62 "../../../Source/Core/Project.nll"
			if (pTranslationUnit->m_sInFile->EndsWith(".nll"))
			{
#line 64 "../../../Source/Core/Project.nll"
				pTranslationUnit->m_sInFile->Replace("../LangShared", "../LangShared/Transpiled");
#line 65 "../../../Source/Core/Project.nll"
				if (pTranslationUnit->m_sInFile->StartsWith("Shared"))
#line 66 "../../../Source/Core/Project.nll"
					pTranslationUnit->m_sInFile->Replace("Shared", "Source/Shared");
				else
#line 68 "../../../Source/Core/Project.nll"
					pTranslationUnit->m_sInFile->Replace("/Shared", "/Source/Shared");
			}
		}
#line 73 "../../../Source/Core/Project.nll"
		m_pValidator = new Validator(this);
#line 74 "../../../Source/Core/Project.nll"
		if (!m_pValidator->Validate())
		{
		}
	}

#line 80 "../../../Source/Core/Project.nll"
	void Project::RecurseNamespaces(AST* pInAst, NamespaceDecl* pSecretNamespace, TranslationUnit* pSecretTranslationUnit)
	{
#line 82 "../../../Source/Core/Project.nll"
		if (pInAst->m_eType == AST::Type::AST_TRANSLATION_UNIT)
		{
#line 84 "../../../Source/Core/Project.nll"
			Assert::Plz(pSecretNamespace == 0);
		}
#line 87 "../../../Source/Core/Project.nll"
		AST* pChild = pInAst->m_pFirstChild;
#line 88 "../../../Source/Core/Project.nll"
		while (pChild != 0)
		{
#line 90 "../../../Source/Core/Project.nll"
			if (pChild->m_eType == AST::Type::NAMESPACE_DECL)
			{
#line 92 "../../../Source/Core/Project.nll"
				NamespaceDecl* pNamespaceDecl = (NamespaceDecl*)(pChild);
#line 93 "../../../Source/Core/Project.nll"
				if (pNamespaceDecl->m_pNameToken->m_sValue->IsEqual("Secret"))
				{
#line 95 "../../../Source/Core/Project.nll"
					AST* pNextChild = pChild;
#line 96 "../../../Source/Core/Project.nll"
					pNextChild = pChild->m_pNextSibling;
#line 98 "../../../Source/Core/Project.nll"
					AST* pOwnedChild = 0;
#line 99 "../../../Source/Core/Project.nll"
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
#line 118 "../../../Source/Core/Project.nll"
				pNextSecretNamespace->m_pFirstToken = pNamespaceDecl->m_pFirstToken;
#line 119 "../../../Source/Core/Project.nll"
				pNextSecretNamespace->m_pNameToken = pNamespaceDecl->m_pNameToken;
#line 120 "../../../Source/Core/Project.nll"
				pNextSecretNamespace->m_bSkipOutput = pNamespaceDecl->m_bSkipOutput;
#line 122 "../../../Source/Core/Project.nll"
				NamespaceDecl* pTemp = pNextSecretNamespace;
#line 123 "../../../Source/Core/Project.nll"
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
#line 135 "../../../Source/Core/Project.nll"
			pChild = pChild->m_pNextSibling;
		}
	}

#line 139 "../../../Source/Core/Project.nll"
	void Project::NamespaceMerge(AST* pParentAST)
	{
#line 141 "../../../Source/Core/Project.nll"
		AST* pChild = pParentAST->m_pFirstChild;
#line 142 "../../../Source/Core/Project.nll"
		Vector<NamespaceDecl*>* pPreviousNamespaceDecls = new Vector<NamespaceDecl*>();
#line 144 "../../../Source/Core/Project.nll"
		while (pChild != 0)
		{
#line 146 "../../../Source/Core/Project.nll"
			if (pChild->m_eType == AST::Type::NAMESPACE_DECL)
			{
#line 148 "../../../Source/Core/Project.nll"
				NamespaceDecl* pNamespaceDecl = (NamespaceDecl*)(pChild);
#line 149 "../../../Source/Core/Project.nll"
				const char* sxName = pNamespaceDecl->m_pNameToken->m_sValue->GetExternalString();
#line 150 "../../../Source/Core/Project.nll"
				int i = 0;
#line 151 "../../../Source/Core/Project.nll"
				for (i = 0; i < pPreviousNamespaceDecls->GetSize(); i++)
				{
#line 153 "../../../Source/Core/Project.nll"
					NamespaceDecl* pPreviousNamespace = pPreviousNamespaceDecls->Get(i);
#line 154 "../../../Source/Core/Project.nll"
					if (pPreviousNamespace->m_pNameToken->m_sValue->IsEqual(sxName) && pPreviousNamespace->m_bSkipOutput == pNamespaceDecl->m_bSkipOutput)
					{
#line 156 "../../../Source/Core/Project.nll"
						AST* pNextSibling = pChild->m_pNextSibling;
#line 157 "../../../Source/Core/Project.nll"
						AST* pOwnedChild = 0;
#line 158 "../../../Source/Core/Project.nll"
						pOwnedChild = pParentAST->RemoveChild(pChild);
#line 160 "../../../Source/Core/Project.nll"
						AST* pSubChild = 0;
						NumbatLogic::AST* __2552901754 = pOwnedChild->m_pFirstChild;
#line 161 "../../../Source/Core/Project.nll"
						pOwnedChild->m_pFirstChild = 0;
#line 161 "../../../Source/Core/Project.nll"
						pSubChild = __2552901754;
#line 162 "../../../Source/Core/Project.nll"
						pOwnedChild->m_pLastChild = 0;
#line 164 "../../../Source/Core/Project.nll"
						if (pSubChild != 0)
						{
#line 166 "../../../Source/Core/Project.nll"
							pSubChild->m_pParent = pPreviousNamespace;
#line 167 "../../../Source/Core/Project.nll"
							if (pPreviousNamespace->m_pFirstChild == 0)
							{
								NumbatLogic::AST* __2417707016 = pSubChild;
#line 169 "../../../Source/Core/Project.nll"
								pSubChild = 0;
#line 169 "../../../Source/Core/Project.nll"
								pPreviousNamespace->m_pFirstChild = __2417707016;
#line 170 "../../../Source/Core/Project.nll"
								pPreviousNamespace->m_pLastChild = pPreviousNamespace->m_pFirstChild;
							}
							else
							{
								NumbatLogic::AST* __2417772610 = pSubChild;
#line 174 "../../../Source/Core/Project.nll"
								pSubChild = 0;
#line 174 "../../../Source/Core/Project.nll"
								pPreviousNamespace->m_pLastChild->m_pNextSibling = __2417772610;
#line 175 "../../../Source/Core/Project.nll"
								pPreviousNamespace->m_pLastChild->m_pNextSibling->m_pPrevSibling = pPreviousNamespace->m_pLastChild;
							}
#line 178 "../../../Source/Core/Project.nll"
							while (pPreviousNamespace->m_pLastChild->m_pNextSibling != 0)
							{
#line 180 "../../../Source/Core/Project.nll"
								pPreviousNamespace->m_pLastChild = pPreviousNamespace->m_pLastChild->m_pNextSibling;
#line 181 "../../../Source/Core/Project.nll"
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
#line 192 "../../../Source/Core/Project.nll"
					pPreviousNamespaceDecls->PushBack(pNamespaceDecl);
				}
				else
				{
#line 196 "../../../Source/Core/Project.nll"
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
#line 206 "../../../Source/Core/Project.nll"
				NamespaceDecl* pPreviousNamespace = pPreviousNamespaceDecls->Get(i);
#line 207 "../../../Source/Core/Project.nll"
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
#line 216 "../../../Source/Core/Project.nll"
		sSecretFileName->Replace(".nll", "Secret.nll");
#line 217 "../../../Source/Core/Project.nll"
		TranslationUnit* pSecretTranslationUnit = new TranslationUnit(sSecretFileName->GetExternalString());
#line 218 "../../../Source/Core/Project.nll"
		TranslationUnit* pPublicTranslationUnit = new TranslationUnit(sAmalgamateFileName);
#line 220 "../../../Source/Core/Project.nll"
		while (m_pFirstChild != 0)
		{
#line 222 "../../../Source/Core/Project.nll"
			AST* pAST = 0;
#line 223 "../../../Source/Core/Project.nll"
			pAST = RemoveChild(m_pFirstChild);
#line 225 "../../../Source/Core/Project.nll"
			TranslationUnit* pTranslationUnit = (TranslationUnit*)(pAST);
#line 226 "../../../Source/Core/Project.nll"
			bool bSkipOutput = pTranslationUnit->m_sInFile->EndsWith(".nll.def");
#line 229 "../../../Source/Core/Project.nll"
			while (pTranslationUnit->m_pTokenContainer->m_pTokenVector->GetSize() > 0)
			{
#line 231 "../../../Source/Core/Project.nll"
				Token* pToken = pTranslationUnit->m_pTokenContainer->m_pTokenVector->PopFront();
#line 232 "../../../Source/Core/Project.nll"
				pToken->m_sFileName = pPublicTranslationUnit->m_sInFile;
				NumbatLogic::Token* __3778855881 = pToken;
#line 233 "../../../Source/Core/Project.nll"
				pToken = 0;
#line 233 "../../../Source/Core/Project.nll"
				pPublicTranslationUnit->m_pTokenContainer->m_pTokenVector->PushBack(__3778855881);
				if (pToken) delete pToken;
			}
#line 236 "../../../Source/Core/Project.nll"
			if (pPublicTranslationUnit->m_pFirstChild == 0)
			{
				NumbatLogic::AST* __4061733424 = pAST->m_pFirstChild;
#line 238 "../../../Source/Core/Project.nll"
				pAST->m_pFirstChild = 0;
#line 238 "../../../Source/Core/Project.nll"
				pPublicTranslationUnit->m_pFirstChild = __4061733424;
#line 239 "../../../Source/Core/Project.nll"
				pPublicTranslationUnit->m_pLastChild = pPublicTranslationUnit->m_pFirstChild;
			}
			else
			{
				NumbatLogic::AST* __4061799018 = pAST->m_pFirstChild;
#line 243 "../../../Source/Core/Project.nll"
				pAST->m_pFirstChild = 0;
#line 243 "../../../Source/Core/Project.nll"
				pPublicTranslationUnit->m_pLastChild->m_pNextSibling = __4061799018;
#line 244 "../../../Source/Core/Project.nll"
				pPublicTranslationUnit->m_pLastChild = pPublicTranslationUnit->m_pLastChild->m_pNextSibling;
			}
#line 247 "../../../Source/Core/Project.nll"
			while (true)
			{
#line 249 "../../../Source/Core/Project.nll"
				pPublicTranslationUnit->m_pLastChild->m_pParent = pPublicTranslationUnit;
#line 250 "../../../Source/Core/Project.nll"
				pPublicTranslationUnit->m_pLastChild->m_bSkipOutput = bSkipOutput;
#line 252 "../../../Source/Core/Project.nll"
				if (pPublicTranslationUnit->m_pLastChild->m_pNextSibling == 0)
#line 253 "../../../Source/Core/Project.nll"
					break;
#line 255 "../../../Source/Core/Project.nll"
				pPublicTranslationUnit->m_pLastChild = pPublicTranslationUnit->m_pLastChild->m_pNextSibling;
			}
			if (pAST) delete pAST;
		}
#line 259 "../../../Source/Core/Project.nll"
		while (m_pTranslationUnitVector->GetSize() > 0)
		{
#line 261 "../../../Source/Core/Project.nll"
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
#line 278 "../../../Source/Core/Project.nll"
		InternalString* sOutFile = new InternalString("");
#line 279 "../../../Source/Core/Project.nll"
		OutputBuilder* pOut = new OutputBuilder();
#line 282 "../../../Source/Core/Project.nll"
		for (int i = 0; i < m_pTranslationUnitVector->GetSize(); i++)
		{
#line 284 "../../../Source/Core/Project.nll"
			TranslationUnit* pTranslationUnit = m_pTranslationUnitVector->Get(i);
#line 285 "../../../Source/Core/Project.nll"
			sOutFile->Set(pTranslationUnit->m_sInFile->GetExternalString());
#line 287 "../../../Source/Core/Project.nll"
			if (sOutFile->EndsWith(".nll"))
			{
#line 289 "../../../Source/Core/Project.nll"
				TranslationUnit::ConvertFilePath(eLanguage, eOutputFile, sOutFile);
#line 291 "../../../Source/Core/Project.nll"
				const char* sxOutFile = sOutFile->GetExternalString();
#line 293 "../../../Source/Core/Project.nll"
				pOut->m_sOut->Set("");
#line 294 "../../../Source/Core/Project.nll"
				pTranslationUnit->Stringify(eLanguage, eOutputFile, 0, pOut);
#line 296 "../../../Source/Core/Project.nll"
				InternalString* sDirectory = File::GetFileDirectory(sxOutFile);
#line 297 "../../../Source/Core/Project.nll"
				File::CreateDirectory(sDirectory->GetExternalString());
#line 300 "../../../Source/Core/Project.nll"
				InternalString* sTestFile = File::GetContents(sxOutFile);
#line 301 "../../../Source/Core/Project.nll"
				if (sTestFile == 0 || !pOut->m_sOut->IsEqual(sTestFile->GetExternalString()))
				{
#line 303 "../../../Source/Core/Project.nll"
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

