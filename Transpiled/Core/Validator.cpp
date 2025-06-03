#include "Validator.hpp"
#include "../../Shared/CPP/InternalString.hpp"
#include "../../Shared/CPP/Vector.hpp"
#include "AST/VarDecl.hpp"
#include "AST/Scope.hpp"
#include "../Shared/OwnedVector.hpp"
#include "Project.hpp"
#include "AST/AST.hpp"
#include "NamespaceNode.hpp"
#include "AST/TranslationUnit.hpp"
#include "../../Shared/CPP/Console.hpp"
#include "AST/TypeRef.hpp"
#include "ValueType.hpp"
#include "../../Source/Package/nll-Assert/CPP/Assert.hpp"
#include "AST/VarDeclDescope.hpp"
#include "AST/ReturnStmt.hpp"
#include "AST/DisownExpr.hpp"
#include "../../Shared/CPP/ExternalString.hpp"
#include "Token.hpp"
#include "AST/Identifier.hpp"

namespace NumberDuck
{
	namespace Secret
	{
		class VarDecl;
		class ValidatorError;
		class ValidatorScope;
		class AST;
		class NamespaceDecl;
		class NamespaceNode;
		class InternalString;
		class TranslationUnit;
		class ValueType;
		class VarDeclDescope;
		class Identifier;
		class ReturnStmt;
		class DisownExpr;
		class Scope;
	}
}
namespace NumberDuck
{
	namespace Secret
	{
		ValidatorError::ValidatorError()
		{
			m_sError = 0;
			m_sFile = 0;
			m_nLine = 0;
			m_nColumn = 0;
		}

		ValidatorError::~ValidatorError()
		{
			if (m_sError) delete m_sError;
			if (m_sFile) delete m_sFile;
		}

		ValidatorScope::ValidatorScope(Scope* pScope)
		{
			m_pScope = 0;
			m_pVarDeclVector = 0;
			m_pScope = pScope;
			m_pVarDeclVector = new Vector<VarDecl*>();
		}

		ValidatorScope::~ValidatorScope()
		{
			if (m_pVarDeclVector) delete m_pVarDeclVector;
		}

		Validator::Validator(Project* pProject)
		{
			m_pProject = 0;
			m_pValidatorErrorVector = 0;
			m_pValidatorScopeVector = 0;
			m_pCurrentNamespaceNode = 0;
			m_pProject = pProject;
			m_pValidatorErrorVector = new OwnedVector<ValidatorError*>();
			m_pValidatorScopeVector = new OwnedVector<ValidatorScope*>();
			m_pCurrentNamespaceNode = pProject->m_pRootNamespaceNode;
		}

		void Validator::PreparseNamespaces(NamespaceNode* pCurrentNode, AST* pAST)
		{
			AST* pChild = pAST->m_pFirstChild;
			while (pChild != 0)
			{
				if (pChild->m_eType == AST::Type::NAMESPACE_DECL)
				{
					NamespaceDecl* pNamespaceDecl = (NamespaceDecl*)(pChild);
					NamespaceNode* pNextNamespaceNode = pCurrentNode->GetOrCreateChild(pNamespaceDecl);
					PreparseNamespaces(pNextNamespaceNode, pChild);
				}
				pChild = pChild->m_pNextSibling;
			}
		}

		bool Validator::Validate()
		{
			InternalString* sTemp = new InternalString("");
			for (int i = 0; i < m_pProject->m_pTranslationUnitVector->GetSize(); i++)
			{
				TranslationUnit* pTranslationUnit = m_pProject->m_pTranslationUnitVector->Get(i);
				PreparseNamespaces(m_pProject->m_pRootNamespaceNode, pTranslationUnit);
			}
			for (int i = 0; i < m_pProject->m_pTranslationUnitVector->GetSize(); i++)
			{
				TranslationUnit* pTranslationUnit = m_pProject->m_pTranslationUnitVector->Get(i);
				pTranslationUnit->PreValidate(this, 0);
			}
			for (int i = 0; i < m_pProject->m_pTranslationUnitVector->GetSize(); i++)
			{
				TranslationUnit* pTranslationUnit = m_pProject->m_pTranslationUnitVector->Get(i);
				pTranslationUnit->Validate(this, 0);
			}
			for (int i = 0; i < m_pValidatorErrorVector->GetSize(); i++)
			{
				ValidatorError* pValidatorError = m_pValidatorErrorVector->Get(i);
				sTemp->Set(pValidatorError->m_sFile->GetExternalString());
				sTemp->Append(":");
				sTemp->AppendInt(pValidatorError->m_nLine);
				sTemp->Append(":");
				sTemp->AppendInt(pValidatorError->m_nColumn);
				sTemp->Append(" - ");
				sTemp->Append(pValidatorError->m_sError->GetExternalString());
				Console::Log(sTemp->GetExternalString());
			}
			if (m_pValidatorErrorVector->GetSize() > 0)
			{
				sTemp->Set("");
				sTemp->AppendInt(m_pValidatorErrorVector->GetSize());
				sTemp->Append(" errors");
				Console::Log(sTemp->GetExternalString());
			}
			{
				if (sTemp) delete sTemp;
				return m_pValidatorErrorVector->GetSize() == 0;
			}
		}

		void Validator::AddError(const char* sError, InternalString* sFile, int nLine, int nColumn)
		{
			ValidatorError* pValidatorError = new ValidatorError();
			pValidatorError->m_sError = new InternalString(sError);
			if (sFile == 0)
				pValidatorError->m_sFile = new InternalString("-- no file --");
			else
				pValidatorError->m_sFile = new InternalString(sFile->GetExternalString());
			pValidatorError->m_nLine = nLine;
			pValidatorError->m_nColumn = nColumn;
			{
				NumberDuck::Secret::ValidatorError* __3836503360 = pValidatorError;
				pValidatorError = 0;
				m_pValidatorErrorVector->PushBack(__3836503360);
			}
			if (pValidatorError) delete pValidatorError;
		}

		void Validator::BeginScope(Scope* pScope)
		{
			ValidatorScope* pValidatorScope = new ValidatorScope(pScope);
			{
				NumberDuck::Secret::ValidatorScope* __2371446692 = pValidatorScope;
				pValidatorScope = 0;
				m_pValidatorScopeVector->PushBack(__2371446692);
			}
			if (pValidatorScope) delete pValidatorScope;
		}

		void Validator::AddVarDecl(VarDecl* pVarDecl)
		{
			ValueType* pValueType = pVarDecl->m_pTypeRef->CreateValueType();
			if (pValueType != 0)
				if (pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE && pValueType->m_ePointerType == TypeRef::PointerType::OWNED)
				{
					int nIndex = m_pValidatorScopeVector->GetSize() - 1;
					NumbatLogic::Assert::Plz(nIndex >= 0);
					ValidatorScope* pValidatorScope = m_pValidatorScopeVector->Get(nIndex);
					pValidatorScope->m_pVarDeclVector->PushBack(pVarDecl);
				}
			if (pValueType) delete pValueType;
		}

		void Validator::EndScope(Scope* pScope)
		{
			ValidatorScope* pValidatorScope = m_pValidatorScopeVector->PopBack();
			NumbatLogic::Assert::Plz(pValidatorScope != 0);
			NumbatLogic::Assert::Plz(pValidatorScope->m_pScope == pScope);
			AST* pCheck = pScope;
			while (pCheck != 0 && pCheck->m_eType == AST::Type::AST_SCOPE)
			{
				pCheck = pCheck->m_pLastChild;
			}
			if (pCheck != 0)
				if (pCheck->m_eType == AST::Type::AST_RETURN_STMT || pCheck->m_eType == AST::Type::AST_CONTINUE_STMT || pCheck->m_eType == AST::Type::AST_BREAK_STMT)
				{
					if (pValidatorScope) delete pValidatorScope;
					return;
				}
			if (pValidatorScope->m_pVarDeclVector->GetSize() > 0)
			{
				VarDeclDescope* pVarDeclDescope = new VarDeclDescope(false);
				for (int i = 0; i < pValidatorScope->m_pVarDeclVector->GetSize(); i++)
				{
					VarDecl* pVarDecl = pValidatorScope->m_pVarDeclVector->Get(i);
					pVarDeclDescope->m_pVarDeclVector->PushBack(pVarDecl);
				}
				{
					NumberDuck::Secret::VarDeclDescope* __4129538314 = pVarDeclDescope;
					pVarDeclDescope = 0;
					pScope->AddChild(__4129538314);
				}
				if (pVarDeclDescope) delete pVarDeclDescope;
			}
			if (pValidatorScope) delete pValidatorScope;
		}

		void Validator::InjectCleanup(AST* pBreakOrContinueOrReturn)
		{
			Identifier* pDisownedIdentifier = 0;
			if (pBreakOrContinueOrReturn->m_eType == AST::Type::AST_RETURN_STMT)
			{
				ReturnStmt* pReturnStmt = (ReturnStmt*)(pBreakOrContinueOrReturn);
				if (pReturnStmt->m_pExpression != 0 && pReturnStmt->m_pExpression->m_eType == AST::Type::AST_DISOWN_EXP)
				{
					DisownExpr* pDisownExpr = (DisownExpr*)(pReturnStmt->m_pExpression);
					if (pDisownExpr->m_pExpression->m_eType == AST::Type::AST_IDENTIFIER)
					{
						pDisownedIdentifier = (Identifier*)(pDisownExpr->m_pExpression);
					}
				}
			}
			VarDeclDescope* pVarDeclDescope = new VarDeclDescope(false);
			for (int i = m_pValidatorScopeVector->GetSize() - 1; i >= 0; i--)
			{
				ValidatorScope* pValidatorScope = m_pValidatorScopeVector->Get(i);
				for (int j = 0; j < pValidatorScope->m_pVarDeclVector->GetSize(); j++)
				{
					VarDecl* pVarDecl = pValidatorScope->m_pVarDeclVector->Get(j);
					if (pDisownedIdentifier != 0)
					{
						if (ExternalString::Equal(pVarDecl->m_pNameToken->GetString(), pDisownedIdentifier->m_pFirstToken->GetString()))
							continue;
					}
					pVarDeclDescope->m_pVarDeclVector->PushBack(pVarDecl);
				}
				if (pBreakOrContinueOrReturn->m_eType == AST::Type::AST_RETURN_STMT)
				{
					if (pValidatorScope->m_pScope->m_pParent->m_eType == AST::Type::AST_FUNCTION_DECL)
						break;
				}
				else
				{
					if (pValidatorScope->m_pScope->m_pParent->m_eType == AST::Type::AST_FOR_STMT || pValidatorScope->m_pScope->m_pParent->m_eType == AST::Type::AST_WHILE_STMT || pValidatorScope->m_pScope->m_pParent->m_eType == AST::Type::AST_SWITCH_STMT)
						break;
				}
			}
			if (pVarDeclDescope->m_pVarDeclVector->GetSize() > 0)
			{
				AST* pParent = pBreakOrContinueOrReturn->m_pParent;
				Scope* pScope = new Scope();
				{
					NumberDuck::Secret::VarDeclDescope* __4129538314 = pVarDeclDescope;
					pVarDeclDescope = 0;
					pScope->AddChild(__4129538314);
				}
				AST* pOwnedBreakOrContinueOrReturn = 0;
				AST* pDisownedScope = 0;
				if (pParent->m_pFirstChild == pBreakOrContinueOrReturn)
				{
					{
						NumberDuck::Secret::AST* __1269199543 = pParent->m_pFirstChild;
						pParent->m_pFirstChild = 0;
						pOwnedBreakOrContinueOrReturn = __1269199543;
					}
					{
						NumberDuck::Secret::Scope* __693694853 = pScope;
						pScope = 0;
						pParent->m_pFirstChild = __693694853;
					}
					pDisownedScope = pParent->m_pFirstChild;
				}
				else
				{
					{
						NumberDuck::Secret::AST* __650031855 = pBreakOrContinueOrReturn->m_pPrevSibling->m_pNextSibling;
						pBreakOrContinueOrReturn->m_pPrevSibling->m_pNextSibling = 0;
						pOwnedBreakOrContinueOrReturn = __650031855;
					}
					{
						NumberDuck::Secret::Scope* __693694853 = pScope;
						pScope = 0;
						pBreakOrContinueOrReturn->m_pPrevSibling->m_pNextSibling = __693694853;
					}
					pDisownedScope = pBreakOrContinueOrReturn->m_pPrevSibling->m_pNextSibling;
					pDisownedScope->m_pPrevSibling = pOwnedBreakOrContinueOrReturn->m_pPrevSibling;
					pOwnedBreakOrContinueOrReturn->m_pPrevSibling = 0;
				}
				if (pParent->m_pLastChild == pBreakOrContinueOrReturn)
				{
					pParent->m_pLastChild = pDisownedScope;
				}
				else
				{
					{
						NumberDuck::Secret::AST* __2124115737 = pBreakOrContinueOrReturn->m_pNextSibling;
						pBreakOrContinueOrReturn->m_pNextSibling = 0;
						pDisownedScope->m_pNextSibling = __2124115737;
					}
					pDisownedScope->m_pNextSibling->m_pPrevSibling = pDisownedScope;
					pBreakOrContinueOrReturn->m_pNextSibling = 0;
				}
				{
					NumberDuck::Secret::AST* __2336879980 = pOwnedBreakOrContinueOrReturn;
					pOwnedBreakOrContinueOrReturn = 0;
					pDisownedScope->AddChild(__2336879980);
				}
				if (pScope) delete pScope;
				if (pOwnedBreakOrContinueOrReturn) delete pOwnedBreakOrContinueOrReturn;
			}
			if (pVarDeclDescope) delete pVarDeclDescope;
		}

		void Validator::BeginNamespace(const char* sxName)
		{
			m_pCurrentNamespaceNode = m_pCurrentNamespaceNode->GetChild(sxName);
			NumbatLogic::Assert::Plz(m_pCurrentNamespaceNode != 0);
		}

		void Validator::EndNamespace(const char* sxName)
		{
			NumbatLogic::Assert::Plz(m_pCurrentNamespaceNode->m_sName->IsEqual(sxName));
			NumbatLogic::Assert::Plz(m_pCurrentNamespaceNode->m_pParent != 0);
			m_pCurrentNamespaceNode = m_pCurrentNamespaceNode->m_pParent;
		}

		Validator::~Validator()
		{
			if (m_pValidatorErrorVector) delete m_pValidatorErrorVector;
			if (m_pValidatorScopeVector) delete m_pValidatorScopeVector;
		}

	}
}

