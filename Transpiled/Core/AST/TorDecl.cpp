#include "TorDecl.hpp"
#include "../OffsetDatum.hpp"
#include "AccessLevel.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "ParamDecl.hpp"
#include "../../../Shared/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "ParamCall.hpp"
#include "../../../Shared/CPP/InternalString.hpp"
#include "Scope.hpp"
#include "AST.hpp"
#include "ClassDecl.hpp"
#include "../Validator.hpp"
#include "../../Shared/OwnedVector.hpp"
#include "../Util.hpp"

namespace NumberDuck
{
	namespace Secret
	{
		class OffsetDatum;
		class AccessLevel;
		class Token;
		class ParamDecl;
		class TorDecl;
		class Scope;
		class ParamCall;
		class InternalString;
		class ClassDecl;
		class AST;
	}
}
namespace NumberDuck
{
	namespace Secret
	{
		TorDecl* TorDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, ClassDecl* pParentClassDecl)
		{
			OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
			AccessLevel* pAccessLevel = AccessLevel::TryCreate(pTokenContainer, pTempOffset);
			if (pAccessLevel == 0)
			{
				if (pTempOffset) delete pTempOffset;
				if (pAccessLevel) delete pAccessLevel;
				return 0;
			}
			Token* pTypeToken = pTokenContainer->Peek(pTempOffset);
			if (pTypeToken == 0 || pTypeToken->m_eType != Token::Type::TOKEN_KEYWORD_CONSTRUCT && pTypeToken->m_eType != Token::Type::TOKEN_KEYWORD_DESTRUCT)
			{
				if (pTempOffset) delete pTempOffset;
				if (pAccessLevel) delete pAccessLevel;
				return 0;
			}
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
			ParamDecl* pParamDecl = ParamDecl::TryCreate(pTokenContainer, pTempOffset);
			if (pParamDecl == 0)
			{
				Console::Log("expected ParamDecl");
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
				NumbatLogic::Assert::Plz(false);
				{
					if (pTempOffset) delete pTempOffset;
					if (pAccessLevel) delete pAccessLevel;
					if (pParamDecl) delete pParamDecl;
					return 0;
				}
			}
			TorDecl* pTorDecl = new TorDecl();
			Scope* pScope = 0;
			Token* pSemicolon = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SEMICOLON);
			if (pSemicolon != 0)
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
			else
			{
				Token* pColon = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_COLON);
				if (pColon != 0)
				{
					pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
					Token* pBase = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_BASE);
					if (pBase == 0)
					{
						Console::Log("expected base!");
						Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
						NumbatLogic::Assert::Plz(false);
						{
							if (pTempOffset) delete pTempOffset;
							if (pAccessLevel) delete pAccessLevel;
							if (pParamDecl) delete pParamDecl;
							if (pTorDecl) delete pTorDecl;
							if (pScope) delete pScope;
							return 0;
						}
					}
					pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
					ParamCall* pParamCall = ParamCall::TryCreate(pTokenContainer, pTempOffset);
					if (pParamCall == 0)
					{
						InternalString* sTemp = new InternalString("expected ParamCall ");
						sTemp->Append(pTokenContainer->StringifyOffset(pTempOffset));
						Console::Log(sTemp->GetExternalString());
						NumbatLogic::Assert::Plz(false);
						{
							if (sTemp) delete sTemp;
							if (pParamCall) delete pParamCall;
							if (pTempOffset) delete pTempOffset;
							if (pAccessLevel) delete pAccessLevel;
							if (pParamDecl) delete pParamDecl;
							if (pTorDecl) delete pTorDecl;
							if (pScope) delete pScope;
							return 0;
						}
					}
					pTorDecl->m_pBaseParamCall = pParamCall;
					{
						NumberDuck::Secret::ParamCall* __3062759993 = pParamCall;
						pParamCall = 0;
						pTorDecl->AddChild(__3062759993);
					}
					if (pParamCall) delete pParamCall;
				}
				pScope = Scope::TryCreate(pTokenContainer, pTempOffset);
				if (pScope == 0)
				{
					Console::Log("expected scope");
					Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
					NumbatLogic::Assert::Plz(false);
				}
			}
			pTorDecl->m_eType = AST::Type::AST_TOR_DECL;
			pTorDecl->m_pParent = pParentClassDecl;
			pTorDecl->m_pParentClassDecl = pParentClassDecl;
			pTorDecl->m_pFirstToken = pTypeToken;
			pTorDecl->m_pAccessLevel = pAccessLevel;
			pTorDecl->m_pTypeToken = pTypeToken;
			pTorDecl->m_pParamDecl = pParamDecl;
			pTorDecl->m_pScope = pScope;
			pTorDecl->m_sDisambiguate = "";
			{
				NumberDuck::Secret::AccessLevel* __2194276919 = pAccessLevel;
				pAccessLevel = 0;
				pTorDecl->AddChild(__2194276919);
			}
			{
				NumberDuck::Secret::ParamDecl* __2049651157 = pParamDecl;
				pParamDecl = 0;
				pTorDecl->AddChild(__2049651157);
			}
			if (pScope != 0)
			{
				NumberDuck::Secret::Scope* __693694853 = pScope;
				pScope = 0;
				pTorDecl->AddChild(__693694853);
			}
			pOffsetDatum->Set(pTempOffset);
			{
				NumberDuck::Secret::TorDecl* __3416457985 = pTorDecl;
				pTorDecl = 0;
				{
					if (pTempOffset) delete pTempOffset;
					if (pAccessLevel) delete pAccessLevel;
					if (pParamDecl) delete pParamDecl;
					if (pScope) delete pScope;
					return __3416457985;
				}
			}
		}

		void TorDecl::Validate(Validator* pValidator, OperatorExpr* pParent)
		{
			AST::Validate(pValidator, pParent);
			if (m_pParentClassDecl != 0 && m_pBaseParamCall != 0)
			{
				ClassDecl* pBaseClass = m_pParentClassDecl->GetBaseClassDecl();
				if (pBaseClass == 0)
				{
					pValidator->AddError("no base class??", m_pBaseParamCall->m_pFirstToken->m_sFileName, m_pBaseParamCall->m_pFirstToken->m_nLine, m_pBaseParamCall->m_pFirstToken->m_nColumn);
					return;
				}
				AST* pMember = pBaseClass->m_pFirstChild;
				while (pMember != 0)
				{
					if (pMember->m_eType == AST::Type::AST_TOR_DECL)
					{
						TorDecl* pTorDecl = (TorDecl*)(pMember);
						if (pTorDecl->m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_CONSTRUCT)
						{
							if (pTorDecl->m_pParamDecl->ValidateParamCall(m_pBaseParamCall, 0))
							{
								break;
							}
						}
					}
					pMember = pMember->m_pNextSibling;
				}
				if (pMember == 0)
				{
					InternalString* sTemp = new InternalString("could not find a matching BASE constructor in ");
					sTemp->AppendString(pBaseClass->m_pNameToken->GetString());
					pValidator->AddError(sTemp->GetExternalString(), m_pBaseParamCall->m_pFirstToken->m_sFileName, m_pBaseParamCall->m_pFirstToken->m_nLine, m_pBaseParamCall->m_pFirstToken->m_nColumn);
					{
						if (sTemp) delete sTemp;
						return;
					}
				}
			}
		}

		void TorDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
		{
			bool bGeneric = m_pParentClassDecl != 0 && m_pParentClassDecl->m_pGenericTypeDeclVector->GetSize() > 0;
			if (bGeneric && eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE)
				return;
			Util::Pad(nDepth, sOut);
			if (!(eLanguage == AST::Language::CS && m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_DESTRUCT))
				if (!(eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE))
				{
					m_pAccessLevel->Stringify(eLanguage, eOutputFile, 0, sOut);
					if (eLanguage == AST::Language::CPP)
						sOut->AppendChar(':');
					sOut->AppendChar(' ');
				}
			if (eLanguage == AST::Language::NLL_DEF)
			{
				if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_DESTRUCT)
					sOut->Append("destruct");
				else
					sOut->Append("construct");
			}
			else
			{
				if (eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE)
				{
					m_pParentClassDecl->m_pNameToken->Stringify(sOut);
					sOut->Append("::");
				}
				if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_DESTRUCT)
				{
					if (eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::HEADER)
						sOut->Append("virtual ");
					sOut->Append("~");
				}
				m_pParentClassDecl->m_pNameToken->Stringify(sOut);
			}
			sOut->Append(m_sDisambiguate);
			m_pParamDecl->Stringify(eLanguage, eOutputFile, 0, sOut);
			if ((!bGeneric && eOutputFile == AST::OutputFile::HEADER) || eLanguage == AST::Language::NLL_DEF)
			{
				sOut->Append(";\n");
				return;
			}
			if (m_pScope == 0)
			{
				sOut->AppendString(";\n");
			}
			else
			{
				if (m_pBaseParamCall != 0)
				{
					sOut->Append(" : ");
					if (eLanguage == AST::Language::CPP)
						m_pParentClassDecl->m_pBaseToken->Stringify(sOut);
					else
						sOut->Append("base");
					m_pBaseParamCall->Stringify(eLanguage, eOutputFile, 0, sOut);
				}
				sOut->AppendChar('\n');
				m_pScope->Stringify(eLanguage, eOutputFile, nDepth, sOut);
				sOut->AppendChar('\n');
			}
		}

		TorDecl::TorDecl()
		{
			m_pParentClassDecl = 0;
			m_pAccessLevel = 0;
			m_pTypeToken = 0;
			m_pParamDecl = 0;
			m_pBaseParamCall = 0;
			m_pScope = 0;
			m_sDisambiguate = 0;
		}

	}
}

