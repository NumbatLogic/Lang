#include "Project.hpp"
#include "../../Shared/CPP/Vector.hpp"
#include "AST/TranslationUnit.hpp"
#include "NamespaceNode.hpp"
#include "../../Shared/CPP/InternalString.hpp"
#include "../../Shared/CPP/Console.hpp"
#include "../../../LangShared/Assert/CPP/Assert.hpp"
#include "../Shared/OwnedVector.hpp"
#include "../../Shared/CPP/File.hpp"
#include "Validator.hpp"
#include "AST/AST.hpp"
#include "AST/NamespaceDecl.hpp"
#include "Token.hpp"
#include "TokenContainer.hpp"

namespace NumberDuck
{
	namespace Secret
	{
		class TranslationUnit;
		class InternalString;
		class Validator;
		class AST;
		class NamespaceDecl;
		class Token;
	}
}
namespace NumberDuck
{
	namespace Secret
	{
		Project::Project()
		{
			m_pTranslationUnitVector = 0;
			m_pRootNamespaceNode = 0;
			m_bCanDescend = true;
			m_pTranslationUnitVector = new Vector<TranslationUnit*>();
			m_pRootNamespaceNode = new NamespaceNode(0, 0);
		}

		void Project::AddFile(const char* sFile, OwnedVector<InternalString*>* sDefineVector)
		{
			for (int i = 0; i < m_pTranslationUnitVector->GetSize(); i++)
			{
				TranslationUnit* pTestTranslationUnit = m_pTranslationUnitVector->Get(i);
				if (pTestTranslationUnit->m_sInFile->IsEqual(sFile))
				{
					return;
				}
			}
			TranslationUnit* pTranslationUnit = TranslationUnit::Create(sFile, sDefineVector);
			if (pTranslationUnit == 0)
			{
				Console::Log("unable to parse file");
				Console::Log(sFile);
				NumbatLogic::Assert::Plz(false);
				{
					if (pTranslationUnit) delete pTranslationUnit;
					return;
				}
			}
			m_pTranslationUnitVector->PushBack(pTranslationUnit);
			{
				NumberDuck::Secret::TranslationUnit* __3109799593 = pTranslationUnit;
				pTranslationUnit = 0;
				AddChild(__3109799593);
			}
			if (pTranslationUnit) delete pTranslationUnit;
		}

		void Project::AddDirectory(const char* sDirectory, OwnedVector<InternalString*>* sDefineVector)
		{
			OwnedVector<InternalString*>* sFileVector = File::GetRecursiveFileVector(sDirectory);
			while (sFileVector->GetSize() > 0)
			{
				InternalString* sFile = sFileVector->PopBack();
				AddFile(sFile->GetExternalString(), sDefineVector);
				if (sFile) delete sFile;
			}
			if (sFileVector) delete sFileVector;
		}

		void Project::FullValidate()
		{
			for (int i = 0; i < m_pTranslationUnitVector->GetSize(); i++)
			{
				TranslationUnit* pTranslationUnit = m_pTranslationUnitVector->Get(i);
				if (pTranslationUnit->m_sInFile->EndsWith(".nll"))
				{
					pTranslationUnit->m_sInFile->Replace("../LangShared", "Source/LangShared");
					if (pTranslationUnit->m_sInFile->StartsWith("Shared"))
						pTranslationUnit->m_sInFile->Replace("Shared", "Source/Shared");
					else
						pTranslationUnit->m_sInFile->Replace("/Shared", "/Source/Shared");
				}
			}
			Validator* pValidator = new Validator(this);
			if (!pValidator->Validate())
			{
			}
			if (pValidator) delete pValidator;
		}

		void Project::RecurseNamespaces(AST* pInAst, NamespaceDecl* pSecretNamespace, TranslationUnit* pSecretTranslationUnit)
		{
			if (pInAst->m_eType == AST::Type::AST_TRANSLATION_UNIT)
			{
				NumbatLogic::Assert::Plz(pSecretNamespace == 0);
			}
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
						AST* pOwnedChild = 0;
						pOwnedChild = pInAst->RemoveChild(pChild);
						NumbatLogic::Assert::Plz(pOwnedChild != 0);
						if (pSecretNamespace == 0)
						{
							{
								NumberDuck::Secret::AST* __3216022957 = pOwnedChild;
								pOwnedChild = 0;
								pSecretTranslationUnit->AddChild(__3216022957);
							}
						}
						else
						{
							{
								NumberDuck::Secret::AST* __3216022957 = pOwnedChild;
								pOwnedChild = 0;
								pSecretNamespace->AddChild(__3216022957);
							}
						}
						pChild = pNextChild;
						{
							if (pOwnedChild) delete pOwnedChild;
							continue;
						}
					}
					NamespaceDecl* pNextSecretNamespace = new NamespaceDecl();
					pNextSecretNamespace->m_pFirstToken = pNamespaceDecl->m_pFirstToken;
					pNextSecretNamespace->m_pNameToken = pNamespaceDecl->m_pNameToken;
					pNextSecretNamespace->m_bSkipOutput = pNamespaceDecl->m_bSkipOutput;
					NamespaceDecl* pTemp = pNextSecretNamespace;
					if (pSecretNamespace == 0)
					{
						{
							NumberDuck::Secret::NamespaceDecl* __1799401907 = pNextSecretNamespace;
							pNextSecretNamespace = 0;
							pSecretTranslationUnit->AddChild(__1799401907);
						}
					}
					else
					{
						{
							NumberDuck::Secret::NamespaceDecl* __1799401907 = pNextSecretNamespace;
							pNextSecretNamespace = 0;
							pSecretNamespace->AddChild(__1799401907);
						}
					}
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
			while (pChild != 0)
			{
				if (pChild->m_eType == AST::Type::NAMESPACE_DECL)
				{
					NamespaceDecl* pNamespaceDecl = (NamespaceDecl*)(pChild);
					const char* sxName = pNamespaceDecl->m_pNameToken->m_sValue->GetExternalString();
					int i;
					for (i = 0; i < pPreviousNamespaceDecls->GetSize(); i++)
					{
						NamespaceDecl* pPreviousNamespace = pPreviousNamespaceDecls->Get(i);
						if (pPreviousNamespace->m_pNameToken->m_sValue->IsEqual(sxName) && pPreviousNamespace->m_bSkipOutput == pNamespaceDecl->m_bSkipOutput)
						{
							AST* pNextSibling = pChild->m_pNextSibling;
							AST* pOwnedChild = 0;
							pOwnedChild = pParentAST->RemoveChild(pChild);
							AST* pSubChild = 0;
							{
								NumberDuck::Secret::AST* __1159247422 = pOwnedChild->m_pFirstChild;
								pOwnedChild->m_pFirstChild = 0;
								pSubChild = __1159247422;
							}
							pOwnedChild->m_pLastChild = 0;
							if (pSubChild != 0)
							{
								pSubChild->m_pParent = pPreviousNamespace;
								if (pPreviousNamespace->m_pFirstChild == 0)
								{
									{
										NumberDuck::Secret::AST* __3883565950 = pSubChild;
										pSubChild = 0;
										pPreviousNamespace->m_pFirstChild = __3883565950;
									}
									pPreviousNamespace->m_pLastChild = pPreviousNamespace->m_pFirstChild;
								}
								else
								{
									{
										NumberDuck::Secret::AST* __3883565950 = pSubChild;
										pSubChild = 0;
										pPreviousNamespace->m_pLastChild->m_pNextSibling = __3883565950;
									}
									pPreviousNamespace->m_pLastChild->m_pNextSibling->m_pPrevSibling = pPreviousNamespace->m_pLastChild;
								}
								while (pPreviousNamespace->m_pLastChild->m_pNextSibling != 0)
								{
									pPreviousNamespace->m_pLastChild = pPreviousNamespace->m_pLastChild->m_pNextSibling;
									pPreviousNamespace->m_pLastChild->m_pParent = pPreviousNamespace;
								}
							}
							pChild = pNextSibling;
							{
								if (pOwnedChild) delete pOwnedChild;
								if (pSubChild) delete pSubChild;
								break;
							}
						}
					}
					if (i == pPreviousNamespaceDecls->GetSize())
					{
						pPreviousNamespaceDecls->PushBack(pNamespaceDecl);
					}
					else
					{
						continue;
					}
				}
				pChild = pChild->m_pNextSibling;
			}
			{
				for (int i = 0; i < pPreviousNamespaceDecls->GetSize(); i++)
				{
					NamespaceDecl* pPreviousNamespace = pPreviousNamespaceDecls->Get(i);
					NamespaceMerge(pPreviousNamespace);
				}
			}
			if (pPreviousNamespaceDecls) delete pPreviousNamespaceDecls;
		}

		void Project::Amalgamate(const char* sAmalgamateFileName)
		{
			InternalString* sSecretFileName = new InternalString(sAmalgamateFileName);
			sSecretFileName->Replace(".nll", "Secret.nll");
			TranslationUnit* pSecretTranslationUnit = new TranslationUnit(sSecretFileName->GetExternalString());
			TranslationUnit* pPublicTranslationUnit = new TranslationUnit(sAmalgamateFileName);
			while (m_pFirstChild != 0)
			{
				AST* pAST = 0;
				pAST = RemoveChild(m_pFirstChild);
				TranslationUnit* pTranslationUnit = (TranslationUnit*)(pAST);
				bool bSkipOutput = pTranslationUnit->m_sInFile->EndsWith(".nll.def");
				while (pTranslationUnit->m_pTokenContainer->m_pTokenVector->GetSize() > 0)
				{
					Token* pToken = pTranslationUnit->m_pTokenContainer->m_pTokenVector->PopFront();
					pToken->m_sFileName = pPublicTranslationUnit->m_sInFile;
					{
						NumberDuck::Secret::Token* __2538616708 = pToken;
						pToken = 0;
						pPublicTranslationUnit->m_pTokenContainer->m_pTokenVector->PushBack(__2538616708);
					}
					if (pToken) delete pToken;
				}
				if (pPublicTranslationUnit->m_pFirstChild == 0)
				{
					{
						NumberDuck::Secret::AST* __2615021536 = pAST->m_pFirstChild;
						pAST->m_pFirstChild = 0;
						pPublicTranslationUnit->m_pFirstChild = __2615021536;
					}
					pPublicTranslationUnit->m_pLastChild = pPublicTranslationUnit->m_pFirstChild;
				}
				else
				{
					{
						NumberDuck::Secret::AST* __2615021536 = pAST->m_pFirstChild;
						pAST->m_pFirstChild = 0;
						pPublicTranslationUnit->m_pLastChild->m_pNextSibling = __2615021536;
					}
					pPublicTranslationUnit->m_pLastChild = pPublicTranslationUnit->m_pLastChild->m_pNextSibling;
				}
				while (true)
				{
					pPublicTranslationUnit->m_pLastChild->m_pParent = pPublicTranslationUnit;
					pPublicTranslationUnit->m_pLastChild->m_bSkipOutput = bSkipOutput;
					if (pPublicTranslationUnit->m_pLastChild->m_pNextSibling == 0)
						break;
					pPublicTranslationUnit->m_pLastChild = pPublicTranslationUnit->m_pLastChild->m_pNextSibling;
				}
				if (pAST) delete pAST;
			}
			while (m_pTranslationUnitVector->GetSize() > 0)
			{
				m_pTranslationUnitVector->PopBack();
			}
			NamespaceMerge(pPublicTranslationUnit);
			RecurseNamespaces(pPublicTranslationUnit, 0, pSecretTranslationUnit);
			m_pTranslationUnitVector->PushBack(pSecretTranslationUnit);
			{
				NumberDuck::Secret::TranslationUnit* __254684446 = pSecretTranslationUnit;
				pSecretTranslationUnit = 0;
				AddChild(__254684446);
			}
			m_pTranslationUnitVector->PushBack(pPublicTranslationUnit);
			{
				NumberDuck::Secret::TranslationUnit* __3324259267 = pPublicTranslationUnit;
				pPublicTranslationUnit = 0;
				AddChild(__3324259267);
			}
			if (sSecretFileName) delete sSecretFileName;
			if (pSecretTranslationUnit) delete pSecretTranslationUnit;
			if (pPublicTranslationUnit) delete pPublicTranslationUnit;
		}

		void Project::Output(AST::Language eLanguage, OutputFile eOutputFile)
		{
			InternalString* sOutFile = new InternalString("");
			InternalString* sOut = new InternalString("");
			for (int i = 0; i < m_pTranslationUnitVector->GetSize(); i++)
			{
				TranslationUnit* pTranslationUnit = m_pTranslationUnitVector->Get(i);
				sOutFile->Set(pTranslationUnit->m_sInFile->GetExternalString());
				if (sOutFile->EndsWith(".nll"))
				{
					TranslationUnit::ConvertFilePath(eLanguage, eOutputFile, sOutFile);
					const char* sxOutFile = sOutFile->GetExternalString();
					sOut->Set("");
					pTranslationUnit->Stringify(eLanguage, eOutputFile, 0, sOut);
					InternalString* sDirectory = File::GetFileDirectory(sxOutFile);
					File::CreateDirectory(sDirectory->GetExternalString());
					InternalString* sTestFile = File::GetContents(sxOutFile);
					if (sTestFile == 0 || !sOut->IsEqual(sTestFile->GetExternalString()))
					{
						File::PutContents(sxOutFile, sOut->GetExternalString());
					}
					if (sDirectory) delete sDirectory;
					if (sTestFile) delete sTestFile;
				}
			}
			if (sOutFile) delete sOutFile;
			if (sOut) delete sOut;
		}

		Project::~Project()
		{
			if (m_pTranslationUnitVector) delete m_pTranslationUnitVector;
			if (m_pRootNamespaceNode) delete m_pRootNamespaceNode;
		}

	}
}

