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
#line 0 "../../../Source/Core/AST/TorDecl.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/TorDecl.nll"
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
			Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
			if (pParamDecl) delete pParamDecl;
			return 0;
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
					Assert::Plz(false);
					if (pTempOffset) delete pTempOffset;
					if (pAccessLevel) delete pAccessLevel;
					if (pParamDecl) delete pParamDecl;
					if (pTorDecl) delete pTorDecl;
					if (pScope) delete pScope;
					return 0;
				}
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
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
					return 0;
				}
				pTorDecl->m_pBaseParamCall = pParamCall;
				NumbatLogic::ParamCall* __1502913502 = pParamCall;
				pParamCall = 0;
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
		pTorDecl->AddChild(__99271240);
		NumbatLogic::ParamDecl* __3703057184 = pParamDecl;
		pParamDecl = 0;
		pTorDecl->AddChild(__3703057184);
		if (pScope != 0)
		{
			NumbatLogic::Scope* __1530946527 = pScope;
			pScope = 0;
			pTorDecl->AddChild(__1530946527);
		}
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::TorDecl* __3519495631 = pTorDecl;
		pTorDecl = 0;
		if (pTempOffset) delete pTempOffset;
		if (pAccessLevel) delete pAccessLevel;
		if (pParamDecl) delete pParamDecl;
		if (pScope) delete pScope;
		return __3519495631;
	}

	void TorDecl::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
		if (m_pParentClassDecl != 0 && m_pBaseParamCall != 0)
		{
			ClassDecl* pBaseClass = m_pParentClassDecl->GetBaseClassDecl(pValidator);
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
						if (pTorDecl->m_pParamDecl->ValidateParamCall(m_pBaseParamCall, pValidator, false))
						{
#line 127 "../../../Source/Core/AST/TorDecl.nll"
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
				if (sTemp) delete sTemp;
				return;
			}
		}
	}

	void TorDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* out)
	{
		bool bGeneric = m_pParentClassDecl != 0 && m_pParentClassDecl->m_pGenericTypeDeclVector->GetSize() > 0;
		if (bGeneric && eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE)
			return;
		if (eLanguage == AST::Language::CS)
		{
			if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_DESTRUCT)
			{
				if (m_pParentClassDecl->m_bDisposable)
				{
					Util::Pad(nDepth, out->m_sOut);
					out->m_sOut->AppendChar('~');
					m_pParentClassDecl->m_pNameToken->Stringify(out->m_sOut);
					out->m_sOut->Append(m_sDisambiguate);
					m_pParamDecl->Stringify(eLanguage, eOutputFile, 0, out);
					out->m_sOut->AppendChar('\n');
					Util::Pad(nDepth, out->m_sOut);
					out->m_sOut->Append("{\n");
					Util::Pad(nDepth + 1, out->m_sOut);
					out->m_sOut->Append("Dispose();\n");
					Util::Pad(nDepth, out->m_sOut);
					out->m_sOut->Append("}\n");
					out->m_sOut->AppendChar('\n');
					Util::Pad(nDepth, out->m_sOut);
					out->m_sOut->Append("public void Dispose()\n");
					Util::Pad(nDepth, out->m_sOut);
					out->m_sOut->Append("{\n");
					nDepth++;
					m_pScope->Stringify(eLanguage, eOutputFile, nDepth, out);
					Util::Pad(nDepth, out->m_sOut);
					out->m_sOut->Append("System.GC.SuppressFinalize(this);\n");
					nDepth--;
					Util::Pad(nDepth, out->m_sOut);
					out->m_sOut->Append("}\n");
					out->m_sOut->AppendChar('\n');
					return;
				}
			}
		}
		Util::Pad(nDepth, out->m_sOut);
		if (!(eLanguage == AST::Language::CS && m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_DESTRUCT))
			if (!(eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE))
			{
				m_pAccessLevel->Stringify(eLanguage, eOutputFile, 0, out);
				if (eLanguage == AST::Language::CPP)
					out->m_sOut->AppendChar(':');
				out->m_sOut->AppendChar(' ');
			}
		if (eLanguage == AST::Language::NLL_DEF)
		{
			if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_DESTRUCT)
				out->m_sOut->Append("destruct");
			else
				out->m_sOut->Append("construct");
		}
		else
		{
			if (eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE)
			{
				m_pParentClassDecl->m_pNameToken->Stringify(out->m_sOut);
				out->m_sOut->Append("::");
			}
			if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_DESTRUCT)
			{
				if (eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::HEADER)
					out->m_sOut->Append("virtual ");
				out->m_sOut->Append("~");
			}
			m_pParentClassDecl->m_pNameToken->Stringify(out->m_sOut);
		}
		out->m_sOut->Append(m_sDisambiguate);
		m_pParamDecl->Stringify(eLanguage, eOutputFile, 0, out);
		if ((!bGeneric && eOutputFile == AST::OutputFile::HEADER) || eLanguage == AST::Language::NLL_DEF)
		{
			out->m_sOut->Append(";\n");
			return;
		}
		if (m_pScope == 0)
		{
			out->m_sOut->AppendString(";\n");
		}
		else
		{
			if (m_pBaseParamCall != 0)
			{
				out->m_sOut->Append(" : ");
				if (eLanguage == AST::Language::CPP)
					m_pParentClassDecl->m_pBaseTypeRef->Stringify(eLanguage, eOutputFile, 0, out);
				else
					out->m_sOut->Append("base");
				m_pBaseParamCall->Stringify(eLanguage, eOutputFile, 0, out);
			}
			out->m_sOut->AppendChar('\n');
			m_pScope->Stringify(eLanguage, eOutputFile, nDepth, out);
			out->m_sOut->AppendChar('\n');
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

