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
#line 13 "../../../Source/Core/AST/TorDecl.nll"
	TorDecl* TorDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, ClassDecl* pParentClassDecl)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		AccessLevel* pAccessLevel = AccessLevel::TryCreate(pTokenContainer, pTempOffset);
#line 18 "../../../Source/Core/AST/TorDecl.nll"
		if (pAccessLevel == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
#line 19 "../../../Source/Core/AST/TorDecl.nll"
			return 0;
		}
		Token* pTypeToken = pTokenContainer->Peek(pTempOffset);
#line 22 "../../../Source/Core/AST/TorDecl.nll"
		if (pTypeToken == 0 || pTypeToken->m_eType != Token::Type::TOKEN_KEYWORD_CONSTRUCT && pTypeToken->m_eType != Token::Type::TOKEN_KEYWORD_DESTRUCT)
		{
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
#line 23 "../../../Source/Core/AST/TorDecl.nll"
			return 0;
		}
#line 24 "../../../Source/Core/AST/TorDecl.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		ParamDecl* pParamDecl = ParamDecl::TryCreate(pTokenContainer, pTempOffset);
#line 27 "../../../Source/Core/AST/TorDecl.nll"
		if (pParamDecl == 0)
		{
#line 29 "../../../Source/Core/AST/TorDecl.nll"
			Console::Log("expected ParamDecl");
#line 30 "../../../Source/Core/AST/TorDecl.nll"
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 31 "../../../Source/Core/AST/TorDecl.nll"
			Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
			if (pParamDecl) delete pParamDecl;
#line 32 "../../../Source/Core/AST/TorDecl.nll"
			return 0;
		}
		TorDecl* pTorDecl = new TorDecl();
		Scope* pScope = 0;
		Token* pSemicolon = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SEMICOLON);
#line 39 "../../../Source/Core/AST/TorDecl.nll"
		if (pSemicolon != 0)
#line 40 "../../../Source/Core/AST/TorDecl.nll"
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		else
		{
			Token* pColon = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_COLON);
#line 44 "../../../Source/Core/AST/TorDecl.nll"
			if (pColon != 0)
			{
#line 46 "../../../Source/Core/AST/TorDecl.nll"
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
				Token* pBase = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_BASE);
#line 49 "../../../Source/Core/AST/TorDecl.nll"
				if (pBase == 0)
				{
#line 51 "../../../Source/Core/AST/TorDecl.nll"
					Console::Log("expected base!");
#line 52 "../../../Source/Core/AST/TorDecl.nll"
					Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 53 "../../../Source/Core/AST/TorDecl.nll"
					Assert::Plz(false);
					if (pTempOffset) delete pTempOffset;
					if (pAccessLevel) delete pAccessLevel;
					if (pParamDecl) delete pParamDecl;
					if (pTorDecl) delete pTorDecl;
					if (pScope) delete pScope;
#line 54 "../../../Source/Core/AST/TorDecl.nll"
					return 0;
				}
#line 56 "../../../Source/Core/AST/TorDecl.nll"
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
				ParamCall* pParamCall = ParamCall::TryCreate(pTokenContainer, pTempOffset);
#line 59 "../../../Source/Core/AST/TorDecl.nll"
				if (pParamCall == 0)
				{
					InternalString* sTemp = new InternalString("expected ParamCall ");
#line 62 "../../../Source/Core/AST/TorDecl.nll"
					sTemp->Append(pTokenContainer->StringifyOffset(pTempOffset));
#line 63 "../../../Source/Core/AST/TorDecl.nll"
					Console::Log(sTemp->GetExternalString());
#line 64 "../../../Source/Core/AST/TorDecl.nll"
					Assert::Plz(false);
					if (sTemp) delete sTemp;
					if (pParamCall) delete pParamCall;
					if (pTempOffset) delete pTempOffset;
					if (pAccessLevel) delete pAccessLevel;
					if (pParamDecl) delete pParamDecl;
					if (pTorDecl) delete pTorDecl;
					if (pScope) delete pScope;
#line 65 "../../../Source/Core/AST/TorDecl.nll"
					return 0;
				}
#line 68 "../../../Source/Core/AST/TorDecl.nll"
				pTorDecl->m_pBaseParamCall = pParamCall;
				NumbatLogic::ParamCall* __1502913502 = pParamCall;
#line 69 "../../../Source/Core/AST/TorDecl.nll"
				pParamCall = 0;
#line 69 "../../../Source/Core/AST/TorDecl.nll"
				pTorDecl->AddChild(__1502913502);
				if (pParamCall) delete pParamCall;
			}
#line 72 "../../../Source/Core/AST/TorDecl.nll"
			pScope = Scope::TryCreate(pTokenContainer, pTempOffset, false);
#line 73 "../../../Source/Core/AST/TorDecl.nll"
			if (pScope == 0)
			{
#line 75 "../../../Source/Core/AST/TorDecl.nll"
				Console::Log("expected scope");
#line 76 "../../../Source/Core/AST/TorDecl.nll"
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 77 "../../../Source/Core/AST/TorDecl.nll"
				Assert::Plz(false);
			}
		}
#line 81 "../../../Source/Core/AST/TorDecl.nll"
		pTorDecl->m_eType = AST::Type::AST_TOR_DECL;
#line 82 "../../../Source/Core/AST/TorDecl.nll"
		pTorDecl->m_pParent = pParentClassDecl;
#line 83 "../../../Source/Core/AST/TorDecl.nll"
		pTorDecl->m_pParentClassDecl = pParentClassDecl;
#line 84 "../../../Source/Core/AST/TorDecl.nll"
		pTorDecl->m_pFirstToken = pTypeToken;
#line 85 "../../../Source/Core/AST/TorDecl.nll"
		pTorDecl->m_pAccessLevel = pAccessLevel;
#line 86 "../../../Source/Core/AST/TorDecl.nll"
		pTorDecl->m_pTypeToken = pTypeToken;
#line 87 "../../../Source/Core/AST/TorDecl.nll"
		pTorDecl->m_pParamDecl = pParamDecl;
#line 88 "../../../Source/Core/AST/TorDecl.nll"
		pTorDecl->m_pScope = pScope;
#line 89 "../../../Source/Core/AST/TorDecl.nll"
		pTorDecl->m_sDisambiguate = "";
		NumbatLogic::AccessLevel* __99271240 = pAccessLevel;
#line 91 "../../../Source/Core/AST/TorDecl.nll"
		pAccessLevel = 0;
#line 91 "../../../Source/Core/AST/TorDecl.nll"
		pTorDecl->AddChild(__99271240);
		NumbatLogic::ParamDecl* __3703057184 = pParamDecl;
#line 92 "../../../Source/Core/AST/TorDecl.nll"
		pParamDecl = 0;
#line 92 "../../../Source/Core/AST/TorDecl.nll"
		pTorDecl->AddChild(__3703057184);
#line 93 "../../../Source/Core/AST/TorDecl.nll"
		if (pScope != 0)
		{
			NumbatLogic::Scope* __1530946527 = pScope;
#line 94 "../../../Source/Core/AST/TorDecl.nll"
			pScope = 0;
#line 94 "../../../Source/Core/AST/TorDecl.nll"
			pTorDecl->AddChild(__1530946527);
		}
#line 96 "../../../Source/Core/AST/TorDecl.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::TorDecl* __3519495631 = pTorDecl;
#line 97 "../../../Source/Core/AST/TorDecl.nll"
		pTorDecl = 0;
		if (pTempOffset) delete pTempOffset;
		if (pAccessLevel) delete pAccessLevel;
		if (pParamDecl) delete pParamDecl;
		if (pScope) delete pScope;
#line 97 "../../../Source/Core/AST/TorDecl.nll"
		return __3519495631;
	}

#line 100 "../../../Source/Core/AST/TorDecl.nll"
	void TorDecl::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
#line 102 "../../../Source/Core/AST/TorDecl.nll"
		AST::Validate(pValidator, pParent);
#line 106 "../../../Source/Core/AST/TorDecl.nll"
		if (m_pParentClassDecl != 0 && m_pBaseParamCall != 0)
		{
			ClassDecl* pBaseClass = m_pParentClassDecl->GetBaseClassDecl(pValidator);
#line 111 "../../../Source/Core/AST/TorDecl.nll"
			if (pBaseClass == 0)
			{
#line 113 "../../../Source/Core/AST/TorDecl.nll"
				pValidator->AddError("no base class??", m_pBaseParamCall->m_pFirstToken->m_sFileName, m_pBaseParamCall->m_pFirstToken->m_nLine, m_pBaseParamCall->m_pFirstToken->m_nColumn);
#line 114 "../../../Source/Core/AST/TorDecl.nll"
				return;
			}
			AST* pMember = pBaseClass->m_pFirstChild;
#line 118 "../../../Source/Core/AST/TorDecl.nll"
			while (pMember != 0)
			{
#line 120 "../../../Source/Core/AST/TorDecl.nll"
				if (pMember->m_eType == AST::Type::AST_TOR_DECL)
				{
					TorDecl* pTorDecl = (TorDecl*)(pMember);
#line 123 "../../../Source/Core/AST/TorDecl.nll"
					if (pTorDecl->m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_CONSTRUCT)
					{
#line 125 "../../../Source/Core/AST/TorDecl.nll"
						if (pTorDecl->m_pParamDecl->ValidateParamCall(m_pBaseParamCall, pValidator, false))
						{
#line 127 "../../../Source/Core/AST/TorDecl.nll"
							break;
						}
					}
				}
#line 131 "../../../Source/Core/AST/TorDecl.nll"
				pMember = pMember->m_pNextSibling;
			}
#line 134 "../../../Source/Core/AST/TorDecl.nll"
			if (pMember == 0)
			{
				InternalString* sTemp = new InternalString("could not find a matching BASE constructor in ");
#line 137 "../../../Source/Core/AST/TorDecl.nll"
				sTemp->AppendString(pBaseClass->m_pNameToken->GetString());
#line 138 "../../../Source/Core/AST/TorDecl.nll"
				pValidator->AddError(sTemp->GetExternalString(), m_pBaseParamCall->m_pFirstToken->m_sFileName, m_pBaseParamCall->m_pFirstToken->m_nLine, m_pBaseParamCall->m_pFirstToken->m_nColumn);
				if (sTemp) delete sTemp;
#line 139 "../../../Source/Core/AST/TorDecl.nll"
				return;
			}
		}
	}

#line 144 "../../../Source/Core/AST/TorDecl.nll"
	void TorDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		bool bGeneric = m_pParentClassDecl != 0 && m_pParentClassDecl->m_pGenericTypeDeclVector->GetSize() > 0;
#line 148 "../../../Source/Core/AST/TorDecl.nll"
		if (bGeneric && eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE)
#line 149 "../../../Source/Core/AST/TorDecl.nll"
			return;
#line 152 "../../../Source/Core/AST/TorDecl.nll"
		if (eLanguage == AST::Language::CS)
		{
#line 154 "../../../Source/Core/AST/TorDecl.nll"
			if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_DESTRUCT)
			{
#line 156 "../../../Source/Core/AST/TorDecl.nll"
				if (m_pParentClassDecl->m_bDisposable)
				{
#line 158 "../../../Source/Core/AST/TorDecl.nll"
					Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 159 "../../../Source/Core/AST/TorDecl.nll"
					pOutputBuilder->m_sOut->AppendChar('~');
#line 160 "../../../Source/Core/AST/TorDecl.nll"
					m_pParentClassDecl->m_pNameToken->Stringify(pOutputBuilder->m_sOut);
#line 161 "../../../Source/Core/AST/TorDecl.nll"
					pOutputBuilder->m_sOut->Append(m_sDisambiguate);
#line 162 "../../../Source/Core/AST/TorDecl.nll"
					m_pParamDecl->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 163 "../../../Source/Core/AST/TorDecl.nll"
					pOutputBuilder->m_sOut->AppendChar('\n');
#line 164 "../../../Source/Core/AST/TorDecl.nll"
					Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 165 "../../../Source/Core/AST/TorDecl.nll"
					pOutputBuilder->m_sOut->Append("{\n");
#line 166 "../../../Source/Core/AST/TorDecl.nll"
					Util::Pad(nDepth + 1, pOutputBuilder->m_sOut);
#line 167 "../../../Source/Core/AST/TorDecl.nll"
					pOutputBuilder->m_sOut->Append("Dispose();\n");
#line 168 "../../../Source/Core/AST/TorDecl.nll"
					Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 169 "../../../Source/Core/AST/TorDecl.nll"
					pOutputBuilder->m_sOut->Append("}\n");
#line 170 "../../../Source/Core/AST/TorDecl.nll"
					pOutputBuilder->m_sOut->AppendChar('\n');
#line 172 "../../../Source/Core/AST/TorDecl.nll"
					Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 173 "../../../Source/Core/AST/TorDecl.nll"
					pOutputBuilder->m_sOut->Append("public void Dispose()\n");
#line 174 "../../../Source/Core/AST/TorDecl.nll"
					Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 175 "../../../Source/Core/AST/TorDecl.nll"
					pOutputBuilder->m_sOut->Append("{\n");
#line 177 "../../../Source/Core/AST/TorDecl.nll"
					nDepth++;
#line 178 "../../../Source/Core/AST/TorDecl.nll"
					m_pScope->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
#line 179 "../../../Source/Core/AST/TorDecl.nll"
					Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 180 "../../../Source/Core/AST/TorDecl.nll"
					pOutputBuilder->m_sOut->Append("System.GC.SuppressFinalize(this);\n");
#line 182 "../../../Source/Core/AST/TorDecl.nll"
					nDepth--;
#line 184 "../../../Source/Core/AST/TorDecl.nll"
					Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 185 "../../../Source/Core/AST/TorDecl.nll"
					pOutputBuilder->m_sOut->Append("}\n");
#line 186 "../../../Source/Core/AST/TorDecl.nll"
					pOutputBuilder->m_sOut->AppendChar('\n');
#line 188 "../../../Source/Core/AST/TorDecl.nll"
					return;
				}
			}
		}
#line 193 "../../../Source/Core/AST/TorDecl.nll"
		pOutputBuilder->UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 194 "../../../Source/Core/AST/TorDecl.nll"
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 196 "../../../Source/Core/AST/TorDecl.nll"
		if (!(eLanguage == AST::Language::CS && m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_DESTRUCT))
#line 197 "../../../Source/Core/AST/TorDecl.nll"
			if (!(eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE))
			{
#line 199 "../../../Source/Core/AST/TorDecl.nll"
				m_pAccessLevel->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 200 "../../../Source/Core/AST/TorDecl.nll"
				if (eLanguage == AST::Language::CPP)
#line 201 "../../../Source/Core/AST/TorDecl.nll"
					pOutputBuilder->m_sOut->AppendChar(':');
#line 202 "../../../Source/Core/AST/TorDecl.nll"
				pOutputBuilder->m_sOut->AppendChar(' ');
			}
#line 205 "../../../Source/Core/AST/TorDecl.nll"
		if (eLanguage == AST::Language::NLL_DEF)
		{
#line 207 "../../../Source/Core/AST/TorDecl.nll"
			if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_DESTRUCT)
#line 208 "../../../Source/Core/AST/TorDecl.nll"
				pOutputBuilder->m_sOut->Append("destruct");
			else
#line 210 "../../../Source/Core/AST/TorDecl.nll"
				pOutputBuilder->m_sOut->Append("construct");
		}
		else
		{
#line 214 "../../../Source/Core/AST/TorDecl.nll"
			if (eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE)
			{
#line 216 "../../../Source/Core/AST/TorDecl.nll"
				m_pParentClassDecl->m_pNameToken->Stringify(pOutputBuilder->m_sOut);
#line 217 "../../../Source/Core/AST/TorDecl.nll"
				pOutputBuilder->m_sOut->Append("::");
			}
#line 220 "../../../Source/Core/AST/TorDecl.nll"
			if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_DESTRUCT)
			{
#line 222 "../../../Source/Core/AST/TorDecl.nll"
				if (eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::HEADER)
#line 223 "../../../Source/Core/AST/TorDecl.nll"
					pOutputBuilder->m_sOut->Append("virtual ");
#line 225 "../../../Source/Core/AST/TorDecl.nll"
				pOutputBuilder->m_sOut->Append("~");
			}
#line 228 "../../../Source/Core/AST/TorDecl.nll"
			m_pParentClassDecl->m_pNameToken->Stringify(pOutputBuilder->m_sOut);
		}
#line 230 "../../../Source/Core/AST/TorDecl.nll"
		pOutputBuilder->m_sOut->Append(m_sDisambiguate);
#line 231 "../../../Source/Core/AST/TorDecl.nll"
		m_pParamDecl->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 235 "../../../Source/Core/AST/TorDecl.nll"
		if ((!bGeneric && eOutputFile == AST::OutputFile::HEADER) || eLanguage == AST::Language::NLL_DEF)
		{
#line 237 "../../../Source/Core/AST/TorDecl.nll"
			pOutputBuilder->m_sOut->Append(";\n");
#line 238 "../../../Source/Core/AST/TorDecl.nll"
			return;
		}
#line 241 "../../../Source/Core/AST/TorDecl.nll"
		if (m_pScope == 0)
		{
#line 243 "../../../Source/Core/AST/TorDecl.nll"
			pOutputBuilder->m_sOut->AppendString(";\n");
		}
		else
		{
#line 247 "../../../Source/Core/AST/TorDecl.nll"
			if (m_pBaseParamCall != 0)
			{
#line 249 "../../../Source/Core/AST/TorDecl.nll"
				pOutputBuilder->m_sOut->Append(" : ");
#line 250 "../../../Source/Core/AST/TorDecl.nll"
				if (eLanguage == AST::Language::CPP)
#line 251 "../../../Source/Core/AST/TorDecl.nll"
					m_pParentClassDecl->m_pBaseTypeRef->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
				else
#line 253 "../../../Source/Core/AST/TorDecl.nll"
					pOutputBuilder->m_sOut->Append("base");
#line 254 "../../../Source/Core/AST/TorDecl.nll"
				m_pBaseParamCall->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			}
#line 256 "../../../Source/Core/AST/TorDecl.nll"
			pOutputBuilder->m_sOut->AppendChar('\n');
#line 257 "../../../Source/Core/AST/TorDecl.nll"
			m_pScope->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
#line 258 "../../../Source/Core/AST/TorDecl.nll"
			pOutputBuilder->m_sOut->AppendChar('\n');
		}
	}

#line 3 "../../../Source/Core/AST/TorDecl.nll"
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

