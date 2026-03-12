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
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
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
#line 0 "../../../Source/Core/AST/AST.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/AST.nll"
#line 95 "../../../Source/Core/AST/AST.nll"
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
#line 97 "../../../Source/Core/AST/AST.nll"
		m_bStatement = false;
		m_bSkipOutput = false;
	}

	AST::~AST()
	{
		if (m_pFirstChild) delete m_pFirstChild;
		if (m_pNextSibling) delete m_pNextSibling;
		if (m_pValueType) delete m_pValueType;
	}

#line 105 "../../../Source/Core/AST/AST.nll"
	AST* AST::CreateFromTokenContainer(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		AST* pAst = 0;
#line 109 "../../../Source/Core/AST/AST.nll"
		pAst = FunctionDecl::TryCreate(pTokenContainer, pOffsetDatum, 0);
		if (pAst != 0)
		{
			NumbatLogic::AST* __77877599 = pAst;
#line 111 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 111 "../../../Source/Core/AST/AST.nll"
			return __77877599;
		}
		pAst = ClassDecl::TryCreate(pTokenContainer, pOffsetDatum, 0);
		if (pAst != 0)
		{
			NumbatLogic::AST* __77877603 = pAst;
#line 115 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 115 "../../../Source/Core/AST/AST.nll"
			return __77877603;
		}
		pAst = NamespaceDecl::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __77877607 = pAst;
#line 119 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 119 "../../../Source/Core/AST/AST.nll"
			return __77877607;
		}
		pAst = CreateStatementFromTokenContainer(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __77943200 = pAst;
#line 123 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 123 "../../../Source/Core/AST/AST.nll"
			return __77943200;
		}
		pAst = TryCreateExpression(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __77943204 = pAst;
#line 127 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 127 "../../../Source/Core/AST/AST.nll"
			return __77943204;
		}
		if (pAst) delete pAst;
#line 129 "../../../Source/Core/AST/AST.nll"
		return 0;
	}

	AST* AST::CreateStatementFromTokenContainer(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		AST* pAst = 0;
#line 136 "../../../Source/Core/AST/AST.nll"
		pAst = ReturnStmt::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __78008804 = pAst;
#line 138 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 138 "../../../Source/Core/AST/AST.nll"
			return __78008804;
		}
		pAst = BreakStmt::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __78074397 = pAst;
#line 142 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 142 "../../../Source/Core/AST/AST.nll"
			return __78074397;
		}
		pAst = ContinueStmt::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __78074401 = pAst;
#line 146 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 146 "../../../Source/Core/AST/AST.nll"
			return __78074401;
		}
		pAst = Scope::TryCreate(pTokenContainer, pOffsetDatum, false);
		if (pAst != 0)
		{
			NumbatLogic::AST* __78139994 = pAst;
#line 150 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 150 "../../../Source/Core/AST/AST.nll"
			return __78139994;
		}
		pAst = VarDecl::TryCreate(pTokenContainer, pOffsetDatum, false);
		if (pAst != 0)
		{
			NumbatLogic::AST* __78139998 = pAst;
#line 154 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 154 "../../../Source/Core/AST/AST.nll"
			return __78139998;
		}
		pAst = EnumDecl::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __78140002 = pAst;
#line 158 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 158 "../../../Source/Core/AST/AST.nll"
			return __78140002;
		}
		pAst = DeleteStmt::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __78205595 = pAst;
#line 162 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 162 "../../../Source/Core/AST/AST.nll"
			return __78205595;
		}
		pAst = IfStmt::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __78205599 = pAst;
#line 166 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 166 "../../../Source/Core/AST/AST.nll"
			return __78205599;
		}
		pAst = ForStmt::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __78271192 = pAst;
#line 170 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 170 "../../../Source/Core/AST/AST.nll"
			return __78271192;
		}
		pAst = WhileStmt::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __78271196 = pAst;
#line 174 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 174 "../../../Source/Core/AST/AST.nll"
			return __78271196;
		}
		pAst = SwitchStmt::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __78271200 = pAst;
#line 178 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 178 "../../../Source/Core/AST/AST.nll"
			return __78271200;
		}
		pAst = ExpressionStmt::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __78336793 = pAst;
#line 182 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 182 "../../../Source/Core/AST/AST.nll"
			return __78336793;
		}
		if (pAst) delete pAst;
#line 184 "../../../Source/Core/AST/AST.nll"
		return 0;
	}

	AST* AST::TryCreateInnerExpression(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		AST* pAst = 0;
#line 191 "../../../Source/Core/AST/AST.nll"
		pAst = NumberExpr::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __78402393 = pAst;
#line 193 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 193 "../../../Source/Core/AST/AST.nll"
			return __78402393;
		}
		pAst = BoolExpr::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __78402397 = pAst;
#line 197 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 197 "../../../Source/Core/AST/AST.nll"
			return __78402397;
		}
		pAst = CharExpr::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __86073505 = pAst;
#line 201 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 201 "../../../Source/Core/AST/AST.nll"
			return __86073505;
		}
		pAst = StringExpr::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __86073509 = pAst;
#line 205 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 205 "../../../Source/Core/AST/AST.nll"
			return __86073509;
		}
		pAst = NullExpr::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __86073513 = pAst;
#line 209 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 209 "../../../Source/Core/AST/AST.nll"
			return __86073513;
		}
		pAst = ThisExpr::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __86139106 = pAst;
#line 213 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 213 "../../../Source/Core/AST/AST.nll"
			return __86139106;
		}
		pAst = BaseExpr::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __86139110 = pAst;
#line 217 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 217 "../../../Source/Core/AST/AST.nll"
			return __86139110;
		}
		pAst = FunctionCall::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __86204703 = pAst;
#line 221 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 221 "../../../Source/Core/AST/AST.nll"
			return __86204703;
		}
		pAst = New::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __86204707 = pAst;
#line 225 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 225 "../../../Source/Core/AST/AST.nll"
			return __86204707;
		}
		pAst = CastExpr::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __86204711 = pAst;
#line 229 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 229 "../../../Source/Core/AST/AST.nll"
			return __86204711;
		}
		pAst = TTHashExpr::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __86270304 = pAst;
#line 233 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 233 "../../../Source/Core/AST/AST.nll"
			return __86270304;
		}
		pAst = Unary::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __86270308 = pAst;
#line 237 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 237 "../../../Source/Core/AST/AST.nll"
			return __86270308;
		}
		pAst = Paren::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __86335901 = pAst;
#line 241 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 241 "../../../Source/Core/AST/AST.nll"
			return __86335901;
		}
		pAst = ArrayLookup::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __86335905 = pAst;
#line 245 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 245 "../../../Source/Core/AST/AST.nll"
			return __86335905;
		}
		pAst = StaticArray::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __86335909 = pAst;
#line 249 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 249 "../../../Source/Core/AST/AST.nll"
			return __86335909;
		}
		pAst = OwnExpr::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __86401502 = pAst;
#line 253 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 253 "../../../Source/Core/AST/AST.nll"
			return __86401502;
		}
		pAst = DisownExpr::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __86401506 = pAst;
#line 257 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 257 "../../../Source/Core/AST/AST.nll"
			return __86401506;
		}
		pAst = RefExpr::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __86467099 = pAst;
#line 261 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 261 "../../../Source/Core/AST/AST.nll"
			return __86467099;
		}
		pAst = Identifier::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __86467103 = pAst;
#line 265 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 265 "../../../Source/Core/AST/AST.nll"
			return __86467103;
		}
		if (pAst) delete pAst;
#line 267 "../../../Source/Core/AST/AST.nll"
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
				NumbatLogic::AST* __3927602644 = pLeft;
#line 281 "../../../Source/Core/AST/AST.nll"
				pLeft = 0;
				if (pTempOffset) delete pTempOffset;
				if (pLeft) delete pLeft;
#line 281 "../../../Source/Core/AST/AST.nll"
				return TrinaryExpr::Create(__3927602644, pTokenContainer, pOffsetDatum);
			}
#line 284 "../../../Source/Core/AST/AST.nll"
			OperatorExpr::OperatorType eOperatorType = OperatorExpr::PeekOperator(pTokenContainer, pTempOffset);
			if (eOperatorType != OperatorExpr::OperatorType::UNKNOWN)
			{
				if (OperatorExpr::IsPostfix(eOperatorType))
				{
					pOffsetDatum->Set(pTempOffset);
					NumbatLogic::AST* __3927668242 = pLeft;
#line 290 "../../../Source/Core/AST/AST.nll"
					pLeft = 0;
					if (pTempOffset) delete pTempOffset;
					if (pLeft) delete pLeft;
#line 290 "../../../Source/Core/AST/AST.nll"
					return OperatorExpr::Create(eOperatorType, pOperatorToken, __3927668242, 0);
				}
#line 293 "../../../Source/Core/AST/AST.nll"
				AST* pRight = TryCreateExpression(pTokenContainer, pTempOffset);
				if (pRight != 0)
				{
					pOffsetDatum->Set(pTempOffset);
					NumbatLogic::AST* __3927668249 = pLeft;
#line 297 "../../../Source/Core/AST/AST.nll"
					pLeft = 0;
					NumbatLogic::AST* __542787396 = pRight;
#line 297 "../../../Source/Core/AST/AST.nll"
					pRight = 0;
					if (pRight) delete pRight;
					if (pTempOffset) delete pTempOffset;
					if (pLeft) delete pLeft;
#line 297 "../../../Source/Core/AST/AST.nll"
					return OperatorExpr::Create(eOperatorType, pOperatorToken, __3927668249, __542787396);
				}
#line 301 "../../../Source/Core/AST/AST.nll"
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
#line 310 "../../../Source/Core/AST/AST.nll"
			pOffsetDatum->Set(pTempOffset);
			NumbatLogic::AST* __3935404956 = pLeft;
#line 311 "../../../Source/Core/AST/AST.nll"
			pLeft = 0;
			if (pTempOffset) delete pTempOffset;
#line 311 "../../../Source/Core/AST/AST.nll"
			return __3935404956;
		}
		if (pTempOffset) delete pTempOffset;
		if (pLeft) delete pLeft;
#line 313 "../../../Source/Core/AST/AST.nll"
		return 0;
	}

	void AST::PreValidate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST* pChild = m_pFirstChild;
		while (pChild != 0)
		{
#line 322 "../../../Source/Core/AST/AST.nll"
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
#line 334 "../../../Source/Core/AST/AST.nll"
			AST* pNextSibling = pChild->m_pNextSibling;
			pChild->Validate(pValidator, 0);
			pChild = pNextSibling;
		}
	}

	void AST::AddChild(AST* pAst)
	{
		pAst->m_pParent = this;
#line 344 "../../../Source/Core/AST/AST.nll"
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
#line 365 "../../../Source/Core/AST/AST.nll"
		pAst->m_pParent = this;
		NumbatLogic::AST* __1700709385 = m_pFirstChild;
#line 366 "../../../Source/Core/AST/AST.nll"
		m_pFirstChild = 0;
#line 366 "../../../Source/Core/AST/AST.nll"
		pAst->m_pNextSibling = __1700709385;
		m_pFirstChild = pAst;
		pAst->m_pNextSibling->m_pPrevSibling = m_pFirstChild;
	}

	void AST::AddChildBefore(AST* pAst, AST* pBefore)
	{
		Assert::Plz(pBefore->m_pParent == this);
#line 375 "../../../Source/Core/AST/AST.nll"
		pAst->m_pParent = this;
#line 377 "../../../Source/Core/AST/AST.nll"
		if (m_pFirstChild == pBefore)
		{
			NumbatLogic::AST* __1700774987 = m_pFirstChild;
#line 379 "../../../Source/Core/AST/AST.nll"
			m_pFirstChild = 0;
#line 379 "../../../Source/Core/AST/AST.nll"
			pAst->m_pNextSibling = __1700774987;
			m_pFirstChild = pAst;
			pBefore->m_pPrevSibling = m_pFirstChild;
		}
		else
		{
			NumbatLogic::AST* __96456765 = pBefore->m_pPrevSibling->m_pNextSibling;
#line 385 "../../../Source/Core/AST/AST.nll"
			pBefore->m_pPrevSibling->m_pNextSibling = 0;
#line 385 "../../../Source/Core/AST/AST.nll"
			pAst->m_pNextSibling = __96456765;
			pAst->m_pPrevSibling = pBefore->m_pPrevSibling;
			pBefore->m_pPrevSibling = (AST*)(pAst);
			pAst->m_pPrevSibling->m_pNextSibling = pAst;
		}
	}

	AST* AST::RemoveChild(AST* pChild)
	{
		if (m_pFirstChild == pChild)
		{
			NumbatLogic::AST* __1700906182 = m_pFirstChild;
#line 396 "../../../Source/Core/AST/AST.nll"
			m_pFirstChild = 0;
#line 396 "../../../Source/Core/AST/AST.nll"
			AST* pOwnedChild = __1700906182;
			if (m_pLastChild == pOwnedChild)
				m_pLastChild = 0;
			else
			{
				NumbatLogic::AST* __400431243 = pOwnedChild->m_pNextSibling;
#line 400 "../../../Source/Core/AST/AST.nll"
				pOwnedChild->m_pNextSibling = 0;
#line 400 "../../../Source/Core/AST/AST.nll"
				m_pFirstChild = __400431243;
			}
#line 401 "../../../Source/Core/AST/AST.nll"
			pOwnedChild->m_pParent = 0;
			NumbatLogic::AST* __2252725199 = pOwnedChild;
#line 402 "../../../Source/Core/AST/AST.nll"
			pOwnedChild = 0;
#line 402 "../../../Source/Core/AST/AST.nll"
			return __2252725199;
		}
		else
		{
			AST* pFindChild = m_pFirstChild;
			while (pFindChild != 0)
			{
				if (pFindChild->m_pNextSibling == pChild)
				{
					NumbatLogic::AST* __326915199 = pFindChild->m_pNextSibling;
#line 411 "../../../Source/Core/AST/AST.nll"
					pFindChild->m_pNextSibling = 0;
#line 411 "../../../Source/Core/AST/AST.nll"
					AST* pOwnedChild = __326915199;
					if (m_pLastChild == pOwnedChild)
						m_pLastChild = pFindChild;
					else
					{
						NumbatLogic::AST* __400496847 = pOwnedChild->m_pNextSibling;
#line 415 "../../../Source/Core/AST/AST.nll"
						pOwnedChild->m_pNextSibling = 0;
#line 415 "../../../Source/Core/AST/AST.nll"
						pFindChild->m_pNextSibling = __400496847;
					}
#line 416 "../../../Source/Core/AST/AST.nll"
					pOwnedChild->m_pParent = 0;
					NumbatLogic::AST* __2252790803 = pOwnedChild;
#line 417 "../../../Source/Core/AST/AST.nll"
					pOwnedChild = 0;
#line 417 "../../../Source/Core/AST/AST.nll"
					return __2252790803;
				}
#line 420 "../../../Source/Core/AST/AST.nll"
				pFindChild = pFindChild->m_pNextSibling;
			}
		}
#line 424 "../../../Source/Core/AST/AST.nll"
		return 0;
	}

#line 428 "../../../Source/Core/AST/AST.nll"
	void AST::AddClassDeclReference(ClassDecl* pClassDecl, OutputFile eOutputFile, bool bForwardReference)
	{
		if (m_pParent != 0)
			m_pParent->AddClassDeclReference(pClassDecl, eOutputFile, bForwardReference);
	}

#line 435 "../../../Source/Core/AST/AST.nll"
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
#line 454 "../../../Source/Core/AST/AST.nll"
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
#line 467 "../../../Source/Core/AST/AST.nll"
		return pParent;
	}

	void AST::StringifyType(InternalString* sOut)
	{
		switch (m_eType)
		{
			case Type::AST_ACCESS_LEVEL:
			{
#line 474 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_ACCESS_LEVEL");
#line 474 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_ARRAY_LOOKUP:
			{
#line 475 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_ARRAY_LOOKUP");
#line 475 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_BOOL_EXPR:
			{
#line 476 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_BOOL_EXPR");
#line 476 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_BREAK_STMT:
			{
#line 477 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_BREAK_STMT");
#line 477 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_CAST_EXP:
			{
#line 478 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_CAST_EXP");
#line 478 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_CHAR:
			{
#line 479 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_CHAR");
#line 479 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_CLASS_DECL:
			{
#line 480 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_CLASS_DECL");
#line 480 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_CONTINUE_STMT:
			{
#line 481 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_CONTINUE_STMT");
#line 481 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_DELETE_STMT:
			{
#line 482 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_DELETE_STMT");
#line 482 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_DISOWN_EXP:
			{
#line 483 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_DISOWN_EXP");
#line 483 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_ENUM_DECL:
			{
#line 484 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_ENUM_DECL");
#line 484 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_EXPRESSION_STMT:
			{
#line 485 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_EXPRESSION_STMT");
#line 485 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_FOR_STMT:
			{
#line 486 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_FOR_STMT");
#line 486 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_FUNCTION_CALL:
			{
#line 487 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_FUNCTION_CALL");
#line 487 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_FUNCTION_DECL:
			{
#line 488 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_FUNCTION_DECL");
#line 488 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_GENERIC_TYPE_DECL:
			{
#line 489 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_GENERIC_TYPE_DECL");
#line 489 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_IDENTIFIER:
			{
#line 490 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_IDENTIFIER");
#line 490 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_IF_STMT:
			{
#line 491 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_IF_STMT");
#line 491 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_MEMBER_ENUM_DECL:
			{
#line 492 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_MEMBER_ENUM_DECL");
#line 492 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_MEMBER_FUNCTION_DECL:
			{
#line 493 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_MEMBER_FUNCTION_DECL");
#line 493 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_MEMBER_VAR_DECL:
			{
#line 494 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_MEMBER_VAR_DECL");
#line 494 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_NEW_EXP:
			{
#line 495 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_NEW_EXP");
#line 495 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_NUMBER:
			{
#line 496 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_NUMBER");
#line 496 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_OPERATOR_EXPR:
			{
#line 497 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_OPERATOR_EXPR");
#line 497 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_OWN_EXP:
			{
#line 498 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_OWN_EXP");
#line 498 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_PARAM_CALL:
			{
#line 499 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_PARAM_CALL");
#line 499 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_PARAM_DECL:
			{
#line 500 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_PARAM_DECL");
#line 500 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_PAREN:
			{
#line 501 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_PAREN");
#line 501 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_REF_EXPR:
			{
#line 502 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_REF_EXPR");
#line 502 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_RETURN_STMT:
			{
#line 503 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_RETURN_STMT");
#line 503 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_SCOPE:
			{
#line 504 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_SCOPE");
#line 504 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_STATIC_ARRAY:
			{
#line 505 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_STATIC_ARRAY");
#line 505 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_STRING:
			{
#line 506 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_STRING");
#line 506 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_SWITCH_STMT:
			{
#line 507 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_SWITCH_STMT");
#line 507 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_TOR_DECL:
			{
#line 508 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_TOR_DECL");
#line 508 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_TRANSLATION_UNIT:
			{
#line 509 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_TRANSLATION_UNIT");
#line 509 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_TTHASH_EXP:
			{
#line 510 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_TTHASH_EXP");
#line 510 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_TYPE_REF:
			{
#line 511 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_TYPE_REF");
#line 511 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_UNARY:
			{
#line 512 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_UNARY");
#line 512 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_VAR_DECL_DESCOPE:
			{
#line 513 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_VAR_DECL_DESCOPE");
#line 513 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_VAR_DECL:
			{
#line 514 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_VAR_DECL");
#line 514 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_WHILE_STMT:
			{
#line 515 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_WHILE_STMT");
#line 515 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_PROJECT:
			{
#line 516 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_PROJECT");
#line 516 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::BASE_EXPR:
			{
#line 517 "../../../Source/Core/AST/AST.nll"
				sOut->Append("BASE_EXPR");
#line 517 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::DELEGATE_DECL:
			{
#line 518 "../../../Source/Core/AST/AST.nll"
				sOut->Append("DELEGATE_DECL");
#line 518 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::ENUM_DECL_VALUE:
			{
#line 519 "../../../Source/Core/AST/AST.nll"
				sOut->Append("ENUM_DECL_VALUE");
#line 519 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::MEMBER_VARS_SET_DEFAULT_STMT:
			{
#line 520 "../../../Source/Core/AST/AST.nll"
				sOut->Append("MEMBER_VARS_SET_DEFAULT_STMT");
#line 520 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::NAMESPACE_DECL:
			{
#line 521 "../../../Source/Core/AST/AST.nll"
				sOut->Append("NAMESPACE_DECL");
#line 521 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::NULL_EXPR:
			{
#line 522 "../../../Source/Core/AST/AST.nll"
				sOut->Append("NULL_EXPR");
#line 522 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::THIS_EXPR:
			{
#line 523 "../../../Source/Core/AST/AST.nll"
				sOut->Append("THIS_EXPR");
#line 523 "../../../Source/Core/AST/AST.nll"
				return;
			}

		}
#line 526 "../../../Source/Core/AST/AST.nll"
		sOut->Append("???");
	}

}

