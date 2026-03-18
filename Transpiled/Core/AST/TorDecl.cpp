#include "TorDecl.hpp"
#include "../OffsetDatum.hpp"
#include "AccessLevel.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "ParamDecl.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "ParamCall.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "Scope.hpp"
#include "AST.hpp"
#include "ClassDecl.hpp"
#include "../Validator.hpp"
#include "../../../../LangShared/Transpiled/Vector/OwnedVector.hpp"
#include "../Util.hpp"
#include "../OutputBuilder.hpp"
#include "TypeRef.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class AccessLevel;
	class Token;
	class TokenContainer;
	class ParamDecl;
	class Console;
	class Assert;
	class TorDecl;
	class Scope;
	class ParamCall;
	class InternalString;
	class ClassDecl;
	class Validator;
	template <class T>
	class OwnedVector;
	class Util;
	class OutputBuilder;
	class TypeRef;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
#line 13 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
	TorDecl* TorDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, ClassDecl* pParentClassDecl)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 17 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
		AccessLevel* pAccessLevel = AccessLevel::TryCreate(pTokenContainer, pTempOffset);
		if (pAccessLevel == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
#line 19 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
			return 0;
		}
		Token* pTypeToken = pTokenContainer->Peek(pTempOffset);
		if (pTypeToken == 0 || pTypeToken->m_eType != Token::Type::TOKEN_KEYWORD_CONSTRUCT && pTypeToken->m_eType != Token::Type::TOKEN_KEYWORD_DESTRUCT)
		{
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
#line 23 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
			return 0;
		}
#line 24 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 26 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
		ParamDecl* pParamDecl = ParamDecl::TryCreate(pTokenContainer, pTempOffset);
		if (pParamDecl == 0)
		{
			Console::Log("expected ParamDecl");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
			if (pParamDecl) delete pParamDecl;
#line 32 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
			return 0;
		}
#line 35 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
		TorDecl* pTorDecl = new TorDecl();
#line 37 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
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
#line 48 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
				Token* pBase = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_BASE);
				if (pBase == 0)
				{
					Console::Log("expected base!");
					Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
					Assert::Plz(false);
					if (pTempOffset) delete pTempOffset;
					if (pAccessLevel) delete pAccessLevel;
					if (pParamDecl) delete pParamDecl;
					if (pTorDecl) delete pTorDecl;
					if (pScope) delete pScope;
#line 54 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
					return 0;
				}
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 58 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
				ParamCall* pParamCall = ParamCall::TryCreate(pTokenContainer, pTempOffset);
				if (pParamCall == 0)
				{
					InternalString* sTemp = new InternalString("expected ParamCall ");
					sTemp->Append(pTokenContainer->StringifyOffset(pTempOffset));
					Console::Log(sTemp->GetExternalString());
					Assert::Plz(false);
					if (sTemp) delete sTemp;
					if (pParamCall) delete pParamCall;
					if (pTempOffset) delete pTempOffset;
					if (pAccessLevel) delete pAccessLevel;
					if (pParamDecl) delete pParamDecl;
					if (pTorDecl) delete pTorDecl;
					if (pScope) delete pScope;
#line 65 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
					return 0;
				}
#line 68 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
				pTorDecl->m_pBaseParamCall = pParamCall;
				NumbatLogic::ParamCall* __1502913502 = pParamCall;
#line 69 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
				pParamCall = 0;
#line 69 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
				pTorDecl->AddChild(__1502913502);
				if (pParamCall) delete pParamCall;
			}
			pScope = Scope::TryCreate(pTokenContainer, pTempOffset, false);
			if (pScope == 0)
			{
				Console::Log("expected scope");
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
				Assert::Plz(false);
			}
		}
#line 81 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
		pTorDecl->m_eType = AST::Type::AST_TOR_DECL;
		pTorDecl->m_pParent = pParentClassDecl;
		pTorDecl->m_pParentClassDecl = pParentClassDecl;
		pTorDecl->m_pFirstToken = pTypeToken;
		pTorDecl->m_pAccessLevel = pAccessLevel;
		pTorDecl->m_pTypeToken = pTypeToken;
		pTorDecl->m_pParamDecl = pParamDecl;
		pTorDecl->m_pScope = pScope;
		pTorDecl->m_sDisambiguate = "";
		NumbatLogic::AccessLevel* __99271240 = pAccessLevel;
		pAccessLevel = 0;
#line 91 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
		pTorDecl->AddChild(__99271240);
		NumbatLogic::ParamDecl* __3703057184 = pParamDecl;
#line 92 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
		pParamDecl = 0;
#line 92 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
		pTorDecl->AddChild(__3703057184);
		if (pScope != 0)
		{
			NumbatLogic::Scope* __1530946527 = pScope;
#line 94 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
			pScope = 0;
#line 94 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
			pTorDecl->AddChild(__1530946527);
		}
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::TorDecl* __3519495631 = pTorDecl;
#line 97 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
		pTorDecl = 0;
		if (pTempOffset) delete pTempOffset;
		if (pAccessLevel) delete pAccessLevel;
		if (pParamDecl) delete pParamDecl;
		if (pScope) delete pScope;
#line 97 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
		return __3519495631;
	}

	void TorDecl::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
#line 106 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
		if (m_pParentClassDecl != 0 && m_pBaseParamCall != 0)
		{
#line 109 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
			ClassDecl* pBaseClass = m_pParentClassDecl->GetBaseClassDecl(pValidator);
#line 111 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
			if (pBaseClass == 0)
			{
				pValidator->AddError("no base class??", m_pBaseParamCall->m_pFirstToken->m_sFileName, m_pBaseParamCall->m_pFirstToken->m_nLine, m_pBaseParamCall->m_pFirstToken->m_nColumn);
				return;
			}
#line 117 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
			AST* pMember = pBaseClass->m_pFirstChild;
			while (pMember != 0)
			{
				if (pMember->m_eType == AST::Type::AST_TOR_DECL)
				{
					TorDecl* pTorDecl = (TorDecl*)(pMember);
					if (pTorDecl->m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_CONSTRUCT)
					{
						if (pTorDecl->m_pParamDecl->ValidateParamCall(m_pBaseParamCall, pValidator, false))
						{
							break;
						}
					}
				}
				pMember = pMember->m_pNextSibling;
			}
#line 134 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
			if (pMember == 0)
			{
				InternalString* sTemp = new InternalString("could not find a matching BASE constructor in ");
				sTemp->AppendString(pBaseClass->m_pNameToken->GetString());
				pValidator->AddError(sTemp->GetExternalString(), m_pBaseParamCall->m_pFirstToken->m_sFileName, m_pBaseParamCall->m_pFirstToken->m_nLine, m_pBaseParamCall->m_pFirstToken->m_nColumn);
				if (sTemp) delete sTemp;
#line 139 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
				return;
			}
		}
	}

	void TorDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		bool bGeneric = m_pParentClassDecl != 0 && m_pParentClassDecl->m_pGenericTypeDeclVector->GetSize() > 0;
#line 148 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
		if (bGeneric && eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE)
			return;
#line 152 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
		if (eLanguage == AST::Language::CS)
		{
			if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_DESTRUCT)
			{
				if (m_pParentClassDecl->m_bDisposable)
				{
					Util::Pad(nDepth, pOutputBuilder->m_sOut);
					pOutputBuilder->m_sOut->AppendChar('~');
					m_pParentClassDecl->m_pNameToken->Stringify(pOutputBuilder->m_sOut);
					pOutputBuilder->m_sOut->Append(m_sDisambiguate);
					m_pParamDecl->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
					pOutputBuilder->m_sOut->AppendChar('\n');
					Util::Pad(nDepth, pOutputBuilder->m_sOut);
					pOutputBuilder->m_sOut->Append("{\n");
					Util::Pad(nDepth + 1, pOutputBuilder->m_sOut);
					pOutputBuilder->m_sOut->Append("Dispose();\n");
					Util::Pad(nDepth, pOutputBuilder->m_sOut);
					pOutputBuilder->m_sOut->Append("}\n");
					pOutputBuilder->m_sOut->AppendChar('\n');
#line 172 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
					Util::Pad(nDepth, pOutputBuilder->m_sOut);
					pOutputBuilder->m_sOut->Append("public void Dispose()\n");
					Util::Pad(nDepth, pOutputBuilder->m_sOut);
					pOutputBuilder->m_sOut->Append("{\n");
#line 177 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
					nDepth++;
					m_pScope->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
					Util::Pad(nDepth, pOutputBuilder->m_sOut);
					pOutputBuilder->m_sOut->Append("System.GC.SuppressFinalize(this);\n");
#line 182 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
					nDepth--;
#line 184 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
					Util::Pad(nDepth, pOutputBuilder->m_sOut);
					pOutputBuilder->m_sOut->Append("}\n");
					pOutputBuilder->m_sOut->AppendChar('\n');
#line 188 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
					return;
				}
			}
		}
#line 193 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
		pOutputBuilder->UpdateSourceLocation(eLanguage, m_pFirstToken);
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 196 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
		if (!(eLanguage == AST::Language::CS && m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_DESTRUCT))
			if (!(eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE))
			{
				m_pAccessLevel->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
				if (eLanguage == AST::Language::CPP)
					pOutputBuilder->m_sOut->AppendChar(':');
				pOutputBuilder->m_sOut->AppendChar(' ');
			}
#line 205 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
		if (eLanguage == AST::Language::NLL_DEF)
		{
			if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_DESTRUCT)
				pOutputBuilder->m_sOut->Append("destruct");
			else
				pOutputBuilder->m_sOut->Append("construct");
		}
		else
		{
			if (eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE)
			{
				m_pParentClassDecl->m_pNameToken->Stringify(pOutputBuilder->m_sOut);
				pOutputBuilder->m_sOut->Append("::");
			}
#line 220 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
			if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_DESTRUCT)
			{
				if (eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::HEADER)
					pOutputBuilder->m_sOut->Append("virtual ");
#line 225 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
				pOutputBuilder->m_sOut->Append("~");
			}
#line 228 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
			m_pParentClassDecl->m_pNameToken->Stringify(pOutputBuilder->m_sOut);
		}
		pOutputBuilder->m_sOut->Append(m_sDisambiguate);
		m_pParamDecl->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 235 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
		if ((!bGeneric && eOutputFile == AST::OutputFile::HEADER) || eLanguage == AST::Language::NLL_DEF)
		{
			pOutputBuilder->m_sOut->Append(";\n");
			return;
		}
#line 241 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
		if (m_pScope == 0)
		{
			pOutputBuilder->m_sOut->AppendString(";\n");
		}
		else
		{
			if (m_pBaseParamCall != 0)
			{
				pOutputBuilder->m_sOut->Append(" : ");
				if (eLanguage == AST::Language::CPP)
					m_pParentClassDecl->m_pBaseTypeRef->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
				else
					pOutputBuilder->m_sOut->Append("base");
				m_pBaseParamCall->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			}
			pOutputBuilder->m_sOut->AppendChar('\n');
			m_pScope->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
			pOutputBuilder->m_sOut->AppendChar('\n');
		}
	}

#line 3 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
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

