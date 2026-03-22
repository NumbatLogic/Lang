#include "AST.hpp"
#include "../Token.hpp"
#include "../Semantic/SymbolScope.hpp"
#include "../ValueType.hpp"
#include "FunctionDecl.hpp"
#include "ClassDecl.hpp"
#include "NamespaceDecl.hpp"
#include "ReturnStmt.hpp"
#include "BreakStmt.hpp"
#include "ContinueStmt.hpp"
#include "Scope.hpp"
#include "VarDecl.hpp"
#include "EnumDecl.hpp"
#include "DeleteStmt.hpp"
#include "IfStmt.hpp"
#include "ForStmt.hpp"
#include "WhileStmt.hpp"
#include "SwitchStmt.hpp"
#include "ExpressionStmt.hpp"
#include "NumberExpr.hpp"
#include "BoolExpr.hpp"
#include "CharExpr.hpp"
#include "StringExpr.hpp"
#include "NullExpr.hpp"
#include "ThisExpr.hpp"
#include "BaseExpr.hpp"
#include "FunctionCall.hpp"
#include "New.hpp"
#include "CastExpr.hpp"
#include "TTHashExpr.hpp"
#include "Unary.hpp"
#include "Paren.hpp"
#include "ArrayLookup.hpp"
#include "StaticArray.hpp"
#include "OwnExpr.hpp"
#include "DisownExpr.hpp"
#include "RefExpr.hpp"
#include "Identifier.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "TrinaryExpr.hpp"
#include "OperatorExpr.hpp"
#include "../../../../LangShared/Source/InternalString/CPP/InternalString.hpp"
#include "../../../../LangShared/Source/Console/CPP/Console.hpp"
#include "../../../../LangShared/Source/Assert/CPP/Assert.hpp"
#include "../OutputBuilder.hpp"

namespace NumbatLogic
{
	class SymbolScope;
	class ValueType;
	class AST;
	class FunctionDecl;
	class ClassDecl;
	class NamespaceDecl;
	class ReturnStmt;
	class BreakStmt;
	class ContinueStmt;
	class Scope;
	class VarDecl;
	class EnumDecl;
	class DeleteStmt;
	class IfStmt;
	class ForStmt;
	class WhileStmt;
	class SwitchStmt;
	class ExpressionStmt;
	class NumberExpr;
	class BoolExpr;
	class CharExpr;
	class StringExpr;
	class NullExpr;
	class ThisExpr;
	class BaseExpr;
	class FunctionCall;
	class New;
	class CastExpr;
	class TTHashExpr;
	class Unary;
	class Paren;
	class ArrayLookup;
	class StaticArray;
	class OwnExpr;
	class DisownExpr;
	class RefExpr;
	class Identifier;
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class TrinaryExpr;
	class OperatorExpr;
	class InternalString;
	class Console;
	class Assert;
	class Project;
	class OutputBuilder;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
#line 96 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
	AST::AST()
	{
		m_eType = Type::AST_ACCESS_LEVEL;
		m_pFirstToken = 0;
		m_pParent = 0;
		m_pFirstChild = 0;
		m_pLastChild = 0;
		m_pPrevSibling = 0;
		m_pNextSibling = 0;
		m_pSymbolScope = 0;
		m_bCanDescend = false;
		m_pValueType = 0;
		m_bStatement = false;
		m_bSkipOutput = false;
#line 98 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		m_bStatement = false;
		m_bSkipOutput = false;
	}

	AST::~AST()
	{
		if (m_pFirstChild) delete m_pFirstChild;
		if (m_pNextSibling) delete m_pNextSibling;
		if (m_pValueType) delete m_pValueType;
	}

#line 106 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
	AST* AST::CreateFromTokenContainer(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		AST* pAst = 0;
#line 110 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		pAst = FunctionDecl::TryCreate(pTokenContainer, pOffsetDatum, 0);
		if (pAst != 0)
		{
			NumbatLogic::AST* __77877600 = pAst;
#line 112 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst = 0;
#line 112 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			return __77877600;
		}
		pAst = ClassDecl::TryCreate(pTokenContainer, pOffsetDatum, 0);
		if (pAst != 0)
		{
			NumbatLogic::AST* __77877604 = pAst;
#line 116 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst = 0;
#line 116 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			return __77877604;
		}
		pAst = NamespaceDecl::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __77943197 = pAst;
#line 120 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst = 0;
#line 120 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			return __77943197;
		}
		pAst = CreateStatementFromTokenContainer(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __77943201 = pAst;
#line 124 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst = 0;
#line 124 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			return __77943201;
		}
		pAst = TryCreateExpression(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __77943205 = pAst;
#line 128 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst = 0;
#line 128 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			return __77943205;
		}
		if (pAst) delete pAst;
#line 130 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		return 0;
	}

	AST* AST::CreateStatementFromTokenContainer(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		AST* pAst = 0;
#line 137 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		pAst = ReturnStmt::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __78008805 = pAst;
#line 139 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst = 0;
#line 139 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			return __78008805;
		}
		pAst = BreakStmt::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __78074398 = pAst;
#line 143 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst = 0;
#line 143 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			return __78074398;
		}
		pAst = ContinueStmt::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __78074402 = pAst;
#line 147 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst = 0;
#line 147 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			return __78074402;
		}
		pAst = Scope::TryCreate(pTokenContainer, pOffsetDatum, false);
		if (pAst != 0)
		{
			NumbatLogic::AST* __78139995 = pAst;
#line 151 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst = 0;
#line 151 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			return __78139995;
		}
		pAst = VarDecl::TryCreate(pTokenContainer, pOffsetDatum, false);
		if (pAst != 0)
		{
			NumbatLogic::AST* __78139999 = pAst;
#line 155 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst = 0;
#line 155 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			return __78139999;
		}
		pAst = EnumDecl::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __78140003 = pAst;
#line 159 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst = 0;
#line 159 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			return __78140003;
		}
		pAst = DeleteStmt::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __78205596 = pAst;
#line 163 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst = 0;
#line 163 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			return __78205596;
		}
		pAst = IfStmt::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __78205600 = pAst;
#line 167 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst = 0;
#line 167 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			return __78205600;
		}
		pAst = ForStmt::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __78271193 = pAst;
#line 171 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst = 0;
#line 171 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			return __78271193;
		}
		pAst = WhileStmt::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __78271197 = pAst;
#line 175 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst = 0;
#line 175 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			return __78271197;
		}
		pAst = SwitchStmt::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __78271201 = pAst;
#line 179 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst = 0;
#line 179 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			return __78271201;
		}
		pAst = ExpressionStmt::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __78336794 = pAst;
#line 183 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst = 0;
#line 183 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			return __78336794;
		}
		if (pAst) delete pAst;
#line 185 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		return 0;
	}

	AST* AST::TryCreateInnerExpression(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		AST* pAst = 0;
#line 192 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		pAst = NumberExpr::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __78402394 = pAst;
#line 194 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst = 0;
#line 194 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			return __78402394;
		}
		pAst = BoolExpr::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __78402398 = pAst;
#line 198 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst = 0;
#line 198 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			return __78402398;
		}
		pAst = CharExpr::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __86073506 = pAst;
#line 202 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst = 0;
#line 202 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			return __86073506;
		}
		pAst = StringExpr::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __86073510 = pAst;
#line 206 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst = 0;
#line 206 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			return __86073510;
		}
		pAst = NullExpr::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __86139103 = pAst;
#line 210 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst = 0;
#line 210 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			return __86139103;
		}
		pAst = ThisExpr::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __86139107 = pAst;
#line 214 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst = 0;
#line 214 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			return __86139107;
		}
		pAst = BaseExpr::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __86139111 = pAst;
#line 218 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst = 0;
#line 218 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			return __86139111;
		}
		pAst = FunctionCall::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __86204704 = pAst;
#line 222 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst = 0;
#line 222 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			return __86204704;
		}
		pAst = New::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __86204708 = pAst;
#line 226 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst = 0;
#line 226 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			return __86204708;
		}
		pAst = CastExpr::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __86270301 = pAst;
#line 230 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst = 0;
#line 230 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			return __86270301;
		}
		pAst = TTHashExpr::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __86270305 = pAst;
#line 234 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst = 0;
#line 234 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			return __86270305;
		}
		pAst = Unary::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __86270309 = pAst;
#line 238 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst = 0;
#line 238 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			return __86270309;
		}
		pAst = Paren::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __86335902 = pAst;
#line 242 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst = 0;
#line 242 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			return __86335902;
		}
		pAst = ArrayLookup::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __86335906 = pAst;
#line 246 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst = 0;
#line 246 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			return __86335906;
		}
		pAst = StaticArray::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __86401499 = pAst;
#line 250 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst = 0;
#line 250 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			return __86401499;
		}
		pAst = OwnExpr::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __86401503 = pAst;
#line 254 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst = 0;
#line 254 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			return __86401503;
		}
		pAst = DisownExpr::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __86401507 = pAst;
#line 258 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst = 0;
#line 258 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			return __86401507;
		}
		pAst = RefExpr::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __86467100 = pAst;
#line 262 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst = 0;
#line 262 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			return __86467100;
		}
		pAst = Identifier::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __86467104 = pAst;
#line 266 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst = 0;
#line 266 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			return __86467104;
		}
		if (pAst) delete pAst;
#line 268 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		return 0;
	}

	AST* AST::TryCreateExpression(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		AST* pLeft = TryCreateInnerExpression(pTokenContainer, pTempOffset);
		if (pLeft != 0)
		{
			Token* pOperatorToken = pTokenContainer->Peek(pTempOffset);
			if (pOperatorToken != 0 && pOperatorToken->m_eType == Token::Type::TOKEN_QUESTION_MARK)
			{
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
				pOffsetDatum->Set(pTempOffset);
				NumbatLogic::AST* __3927602645 = pLeft;
#line 282 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pLeft = 0;
				if (pTempOffset) delete pTempOffset;
				if (pLeft) delete pLeft;
#line 282 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return TrinaryExpr::Create(__3927602645, pTokenContainer, pOffsetDatum);
			}
#line 285 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			OperatorExpr::OperatorType eOperatorType = OperatorExpr::PeekOperator(pTokenContainer, pTempOffset);
			if (eOperatorType != OperatorExpr::OperatorType::UNKNOWN)
			{
				if (OperatorExpr::IsPostfix(eOperatorType))
				{
					pOffsetDatum->Set(pTempOffset);
					NumbatLogic::AST* __3927668243 = pLeft;
#line 291 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					pLeft = 0;
					if (pTempOffset) delete pTempOffset;
					if (pLeft) delete pLeft;
#line 291 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return OperatorExpr::Create(eOperatorType, pOperatorToken, __3927668243, 0);
				}
#line 294 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				AST* pRight = TryCreateExpression(pTokenContainer, pTempOffset);
				if (pRight != 0)
				{
					pOffsetDatum->Set(pTempOffset);
					NumbatLogic::AST* __3927668250 = pLeft;
#line 298 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					pLeft = 0;
					NumbatLogic::AST* __542787397 = pRight;
#line 298 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					pRight = 0;
					if (pRight) delete pRight;
					if (pTempOffset) delete pTempOffset;
					if (pLeft) delete pLeft;
#line 298 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return OperatorExpr::Create(eOperatorType, pOperatorToken, __3927668250, __542787397);
				}
#line 302 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				InternalString* sTemp = new InternalString("Probably should have something after the operator??? ");
				sTemp->Append(pOperatorToken->m_sFileName->GetExternalString());
				sTemp->Append(":");
				sTemp->AppendInt(pOperatorToken->m_nLine);
				sTemp->Append(":");
				sTemp->AppendInt(pOperatorToken->m_nColumn);
				Console::Log(sTemp->GetExternalString());
				Assert::Plz(false);
				if (pRight) delete pRight;
				if (sTemp) delete sTemp;
			}
#line 311 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pOffsetDatum->Set(pTempOffset);
			NumbatLogic::AST* __3935404957 = pLeft;
#line 312 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pLeft = 0;
			if (pTempOffset) delete pTempOffset;
#line 312 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			return __3935404957;
		}
		if (pTempOffset) delete pTempOffset;
		if (pLeft) delete pLeft;
#line 314 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		return 0;
	}

	void AST::PreValidate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST* pChild = m_pFirstChild;
		while (pChild != 0)
		{
#line 323 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			AST* pNextSibling = pChild->m_pNextSibling;
			pChild->PreValidate(pValidator, 0);
			pChild = pNextSibling;
		}
	}

	void AST::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST* pChild = m_pFirstChild;
		while (pChild != 0)
		{
#line 335 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			AST* pNextSibling = pChild->m_pNextSibling;
			pChild->Validate(pValidator, 0);
			pChild = pNextSibling;
		}
	}

	void AST::AddChild(AST* pAst)
	{
		pAst->m_pParent = this;
#line 345 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		if (m_pFirstChild == 0)
		{
			m_pFirstChild = pAst;
			m_pLastChild = m_pFirstChild;
		}
		else
		{
			m_pLastChild->m_pNextSibling = pAst;
			m_pLastChild->m_pNextSibling->m_pPrevSibling = m_pLastChild;
			m_pLastChild = m_pLastChild->m_pNextSibling;
		}
	}

	void AST::AddChildFront(AST* pAst)
	{
		if (m_pFirstChild == 0)
		{
			AddChild(pAst);
			return;
		}
#line 366 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		pAst->m_pParent = this;
		NumbatLogic::AST* __1700709386 = m_pFirstChild;
#line 367 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		m_pFirstChild = 0;
#line 367 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		pAst->m_pNextSibling = __1700709386;
		m_pFirstChild = pAst;
		pAst->m_pNextSibling->m_pPrevSibling = m_pFirstChild;
	}

	void AST::AddChildBefore(AST* pAst, AST* pBefore)
	{
		Assert::Plz(pBefore->m_pParent == this);
#line 376 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		pAst->m_pParent = this;
#line 378 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		if (m_pFirstChild == pBefore)
		{
			NumbatLogic::AST* __1700840577 = m_pFirstChild;
#line 380 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			m_pFirstChild = 0;
#line 380 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst->m_pNextSibling = __1700840577;
			m_pFirstChild = pAst;
			pBefore->m_pPrevSibling = m_pFirstChild;
		}
		else
		{
			NumbatLogic::AST* __96456766 = pBefore->m_pPrevSibling->m_pNextSibling;
#line 386 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pBefore->m_pPrevSibling->m_pNextSibling = 0;
#line 386 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pAst->m_pNextSibling = __96456766;
			pAst->m_pPrevSibling = pBefore->m_pPrevSibling;
			pBefore->m_pPrevSibling = (AST*)(pAst);
			pAst->m_pPrevSibling->m_pNextSibling = pAst;
		}
	}

	AST* AST::RemoveChild(AST* pChild)
	{
		if (m_pFirstChild == pChild)
		{
			NumbatLogic::AST* __1700906183 = m_pFirstChild;
#line 397 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			m_pFirstChild = 0;
#line 397 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			AST* pOwnedChild = __1700906183;
			if (m_pLastChild == pOwnedChild)
				m_pLastChild = 0;
			else
			{
				NumbatLogic::AST* __400431244 = pOwnedChild->m_pNextSibling;
#line 401 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pOwnedChild->m_pNextSibling = 0;
#line 401 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				m_pFirstChild = __400431244;
			}
#line 402 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pOwnedChild->m_pParent = 0;
			NumbatLogic::AST* __2252725200 = pOwnedChild;
#line 403 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			pOwnedChild = 0;
#line 403 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
			return __2252725200;
		}
		else
		{
			AST* pFindChild = m_pFirstChild;
			while (pFindChild != 0)
			{
				if (pFindChild->m_pNextSibling == pChild)
				{
					NumbatLogic::AST* __326915200 = pFindChild->m_pNextSibling;
#line 412 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					pFindChild->m_pNextSibling = 0;
#line 412 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					AST* pOwnedChild = __326915200;
					if (m_pLastChild == pOwnedChild)
						m_pLastChild = pFindChild;
					else
					{
						NumbatLogic::AST* __400496848 = pOwnedChild->m_pNextSibling;
#line 416 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
						pOwnedChild->m_pNextSibling = 0;
#line 416 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
						pFindChild->m_pNextSibling = __400496848;
					}
#line 417 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					pOwnedChild->m_pParent = 0;
					NumbatLogic::AST* __2252790804 = pOwnedChild;
#line 418 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					pOwnedChild = 0;
#line 418 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
					return __2252790804;
				}
#line 421 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				pFindChild = pFindChild->m_pNextSibling;
			}
		}
#line 425 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		return 0;
	}

#line 429 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
	void AST::AddClassDeclReference(ClassDecl* pClassDecl, OutputFile eOutputFile, bool bForwardReference)
	{
		if (m_pParent != 0)
			m_pParent->AddClassDeclReference(pClassDecl, eOutputFile, bForwardReference);
	}

#line 436 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
	Project* AST::GetProject()
	{
		AST* p = this;
		while (p != 0 && p->m_eType != AST::Type::AST_PROJECT)
			p = p->m_pParent;
		return p != 0 ? (Project*)(p) : 0;
	}

	void AST::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		pOutputBuilder->m_sOut->Append("???");
	}

	AST* AST::BaseClone()
	{
		InternalString* sTemp = new InternalString("BaseClone() not setup for ");
		StringifyType(sTemp);
		Console::Log(sTemp->GetExternalString());
		Assert::Plz(false);
		if (sTemp) delete sTemp;
#line 455 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		return 0;
	}

	AST* AST::GetParentStatement()
	{
		AST* pParent = m_pParent;
		while (pParent != 0)
		{
			if (pParent->m_bStatement)
				break;
			pParent = pParent->m_pParent;
		}
#line 468 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		return pParent;
	}

	void AST::StringifyType(InternalString* sOut)
	{
		switch (m_eType)
		{
			case Type::AST_ACCESS_LEVEL:
			{
#line 475 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_ACCESS_LEVEL");
#line 475 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_ARRAY_LOOKUP:
			{
#line 476 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_ARRAY_LOOKUP");
#line 476 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_BOOL_EXPR:
			{
#line 477 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_BOOL_EXPR");
#line 477 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_BREAK_STMT:
			{
#line 478 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_BREAK_STMT");
#line 478 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_CAST_EXP:
			{
#line 479 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_CAST_EXP");
#line 479 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_CHAR:
			{
#line 480 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_CHAR");
#line 480 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_CLASS_DECL:
			{
#line 481 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_CLASS_DECL");
#line 481 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_CONTINUE_STMT:
			{
#line 482 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_CONTINUE_STMT");
#line 482 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_DELETE_STMT:
			{
#line 483 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_DELETE_STMT");
#line 483 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_DISOWN_EXP:
			{
#line 484 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_DISOWN_EXP");
#line 484 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_ENUM_DECL:
			{
#line 485 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_ENUM_DECL");
#line 485 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_EXPRESSION_STMT:
			{
#line 486 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_EXPRESSION_STMT");
#line 486 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_FOR_STMT:
			{
#line 487 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_FOR_STMT");
#line 487 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_FUNCTION_CALL:
			{
#line 488 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_FUNCTION_CALL");
#line 488 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_FUNCTION_DECL:
			{
#line 489 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_FUNCTION_DECL");
#line 489 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_GENERIC_TYPE_DECL:
			{
#line 490 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_GENERIC_TYPE_DECL");
#line 490 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_IDENTIFIER:
			{
#line 491 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_IDENTIFIER");
#line 491 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_IF_STMT:
			{
#line 492 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_IF_STMT");
#line 492 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_MEMBER_ENUM_DECL:
			{
#line 493 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_MEMBER_ENUM_DECL");
#line 493 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_MEMBER_FUNCTION_DECL:
			{
#line 494 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_MEMBER_FUNCTION_DECL");
#line 494 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_MEMBER_VAR_DECL:
			{
#line 495 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_MEMBER_VAR_DECL");
#line 495 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_NEW_EXP:
			{
#line 496 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_NEW_EXP");
#line 496 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_NUMBER:
			{
#line 497 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_NUMBER");
#line 497 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_OPERATOR_EXPR:
			{
#line 498 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_OPERATOR_EXPR");
#line 498 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_OWN_EXP:
			{
#line 499 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_OWN_EXP");
#line 499 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_PARAM_CALL:
			{
#line 500 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_PARAM_CALL");
#line 500 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_PARAM_DECL:
			{
#line 501 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_PARAM_DECL");
#line 501 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_PAREN:
			{
#line 502 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_PAREN");
#line 502 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_REF_EXPR:
			{
#line 503 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_REF_EXPR");
#line 503 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_RETURN_STMT:
			{
#line 504 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_RETURN_STMT");
#line 504 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_SCOPE:
			{
#line 505 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_SCOPE");
#line 505 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_STATIC_ARRAY:
			{
#line 506 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_STATIC_ARRAY");
#line 506 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_STRING:
			{
#line 507 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_STRING");
#line 507 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_SWITCH_STMT:
			{
#line 508 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_SWITCH_STMT");
#line 508 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_TOR_DECL:
			{
#line 509 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_TOR_DECL");
#line 509 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_TRANSLATION_UNIT:
			{
#line 510 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_TRANSLATION_UNIT");
#line 510 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_TTHASH_EXP:
			{
#line 511 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_TTHASH_EXP");
#line 511 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_TYPE_REF:
			{
#line 512 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_TYPE_REF");
#line 512 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_UNARY:
			{
#line 513 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_UNARY");
#line 513 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_VAR_DECL_DESCOPE:
			{
#line 514 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_VAR_DECL_DESCOPE");
#line 514 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_VAR_DECL:
			{
#line 515 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_VAR_DECL");
#line 515 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_WHILE_STMT:
			{
#line 516 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_WHILE_STMT");
#line 516 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_PROJECT:
			{
#line 517 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("AST_PROJECT");
#line 517 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::BASE_EXPR:
			{
#line 518 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("BASE_EXPR");
#line 518 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::DELEGATE_DECL:
			{
#line 519 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("DELEGATE_DECL");
#line 519 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::ENUM_DECL_VALUE:
			{
#line 520 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("ENUM_DECL_VALUE");
#line 520 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::MEMBER_VARS_SET_DEFAULT_STMT:
			{
#line 521 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("MEMBER_VARS_SET_DEFAULT_STMT");
#line 521 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::NAMESPACE_DECL:
			{
#line 522 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("NAMESPACE_DECL");
#line 522 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::NULL_EXPR:
			{
#line 523 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("NULL_EXPR");
#line 523 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

			case Type::THIS_EXPR:
			{
#line 524 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				sOut->Append("THIS_EXPR");
#line 524 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
				return;
			}

		}
#line 527 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		sOut->Append("???");
	}

}

