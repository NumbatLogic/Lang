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
#line 1 "../../../Source/Core/AST/AST.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/AST.nll"
#line 96 "../../../Source/Core/AST/AST.nll"
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
#line 98 "../../../Source/Core/AST/AST.nll"
		m_bStatement = false;
#line 99 "../../../Source/Core/AST/AST.nll"
		m_bSkipOutput = false;
	}

#line 102 "../../../Source/Core/AST/AST.nll"
	AST::~AST()
	{
		if (m_pFirstChild) delete m_pFirstChild;
		if (m_pNextSibling) delete m_pNextSibling;
		if (m_pValueType) delete m_pValueType;
	}

#line 106 "../../../Source/Core/AST/AST.nll"
	AST* AST::CreateFromTokenContainer(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		AST* pAst = 0;
#line 110 "../../../Source/Core/AST/AST.nll"
		pAst = FunctionDecl::TryCreate(pTokenContainer, pOffsetDatum, 0);
#line 111 "../../../Source/Core/AST/AST.nll"
		if (pAst != 0)
		{
			NumbatLogic::AST* __77877599 = pAst;
#line 112 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 112 "../../../Source/Core/AST/AST.nll"
			return __77877599;
		}
#line 114 "../../../Source/Core/AST/AST.nll"
		pAst = ClassDecl::TryCreate(pTokenContainer, pOffsetDatum, 0);
#line 115 "../../../Source/Core/AST/AST.nll"
		if (pAst != 0)
		{
			NumbatLogic::AST* __77877603 = pAst;
#line 116 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 116 "../../../Source/Core/AST/AST.nll"
			return __77877603;
		}
#line 118 "../../../Source/Core/AST/AST.nll"
		pAst = NamespaceDecl::TryCreate(pTokenContainer, pOffsetDatum);
#line 119 "../../../Source/Core/AST/AST.nll"
		if (pAst != 0)
		{
			NumbatLogic::AST* __77877607 = pAst;
#line 120 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 120 "../../../Source/Core/AST/AST.nll"
			return __77877607;
		}
#line 122 "../../../Source/Core/AST/AST.nll"
		pAst = CreateStatementFromTokenContainer(pTokenContainer, pOffsetDatum);
#line 123 "../../../Source/Core/AST/AST.nll"
		if (pAst != 0)
		{
			NumbatLogic::AST* __77943200 = pAst;
#line 124 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 124 "../../../Source/Core/AST/AST.nll"
			return __77943200;
		}
#line 126 "../../../Source/Core/AST/AST.nll"
		pAst = TryCreateExpression(pTokenContainer, pOffsetDatum);
#line 127 "../../../Source/Core/AST/AST.nll"
		if (pAst != 0)
		{
			NumbatLogic::AST* __77943204 = pAst;
#line 128 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 128 "../../../Source/Core/AST/AST.nll"
			return __77943204;
		}
		if (pAst) delete pAst;
#line 130 "../../../Source/Core/AST/AST.nll"
		return 0;
	}

#line 133 "../../../Source/Core/AST/AST.nll"
	AST* AST::CreateStatementFromTokenContainer(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		AST* pAst = 0;
#line 137 "../../../Source/Core/AST/AST.nll"
		pAst = ReturnStmt::TryCreate(pTokenContainer, pOffsetDatum);
#line 138 "../../../Source/Core/AST/AST.nll"
		if (pAst != 0)
		{
			NumbatLogic::AST* __78008804 = pAst;
#line 139 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 139 "../../../Source/Core/AST/AST.nll"
			return __78008804;
		}
#line 141 "../../../Source/Core/AST/AST.nll"
		pAst = BreakStmt::TryCreate(pTokenContainer, pOffsetDatum);
#line 142 "../../../Source/Core/AST/AST.nll"
		if (pAst != 0)
		{
			NumbatLogic::AST* __78074397 = pAst;
#line 143 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 143 "../../../Source/Core/AST/AST.nll"
			return __78074397;
		}
#line 145 "../../../Source/Core/AST/AST.nll"
		pAst = ContinueStmt::TryCreate(pTokenContainer, pOffsetDatum);
#line 146 "../../../Source/Core/AST/AST.nll"
		if (pAst != 0)
		{
			NumbatLogic::AST* __78074401 = pAst;
#line 147 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 147 "../../../Source/Core/AST/AST.nll"
			return __78074401;
		}
#line 149 "../../../Source/Core/AST/AST.nll"
		pAst = Scope::TryCreate(pTokenContainer, pOffsetDatum, false);
#line 150 "../../../Source/Core/AST/AST.nll"
		if (pAst != 0)
		{
			NumbatLogic::AST* __78139994 = pAst;
#line 151 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 151 "../../../Source/Core/AST/AST.nll"
			return __78139994;
		}
#line 153 "../../../Source/Core/AST/AST.nll"
		pAst = VarDecl::TryCreate(pTokenContainer, pOffsetDatum, false);
#line 154 "../../../Source/Core/AST/AST.nll"
		if (pAst != 0)
		{
			NumbatLogic::AST* __78139998 = pAst;
#line 155 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 155 "../../../Source/Core/AST/AST.nll"
			return __78139998;
		}
#line 157 "../../../Source/Core/AST/AST.nll"
		pAst = EnumDecl::TryCreate(pTokenContainer, pOffsetDatum);
#line 158 "../../../Source/Core/AST/AST.nll"
		if (pAst != 0)
		{
			NumbatLogic::AST* __78140002 = pAst;
#line 159 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 159 "../../../Source/Core/AST/AST.nll"
			return __78140002;
		}
#line 161 "../../../Source/Core/AST/AST.nll"
		pAst = DeleteStmt::TryCreate(pTokenContainer, pOffsetDatum);
#line 162 "../../../Source/Core/AST/AST.nll"
		if (pAst != 0)
		{
			NumbatLogic::AST* __78205595 = pAst;
#line 163 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 163 "../../../Source/Core/AST/AST.nll"
			return __78205595;
		}
#line 165 "../../../Source/Core/AST/AST.nll"
		pAst = IfStmt::TryCreate(pTokenContainer, pOffsetDatum);
#line 166 "../../../Source/Core/AST/AST.nll"
		if (pAst != 0)
		{
			NumbatLogic::AST* __78205599 = pAst;
#line 167 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 167 "../../../Source/Core/AST/AST.nll"
			return __78205599;
		}
#line 169 "../../../Source/Core/AST/AST.nll"
		pAst = ForStmt::TryCreate(pTokenContainer, pOffsetDatum);
#line 170 "../../../Source/Core/AST/AST.nll"
		if (pAst != 0)
		{
			NumbatLogic::AST* __78271192 = pAst;
#line 171 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 171 "../../../Source/Core/AST/AST.nll"
			return __78271192;
		}
#line 173 "../../../Source/Core/AST/AST.nll"
		pAst = WhileStmt::TryCreate(pTokenContainer, pOffsetDatum);
#line 174 "../../../Source/Core/AST/AST.nll"
		if (pAst != 0)
		{
			NumbatLogic::AST* __78271196 = pAst;
#line 175 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 175 "../../../Source/Core/AST/AST.nll"
			return __78271196;
		}
#line 177 "../../../Source/Core/AST/AST.nll"
		pAst = SwitchStmt::TryCreate(pTokenContainer, pOffsetDatum);
#line 178 "../../../Source/Core/AST/AST.nll"
		if (pAst != 0)
		{
			NumbatLogic::AST* __78271200 = pAst;
#line 179 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 179 "../../../Source/Core/AST/AST.nll"
			return __78271200;
		}
#line 181 "../../../Source/Core/AST/AST.nll"
		pAst = ExpressionStmt::TryCreate(pTokenContainer, pOffsetDatum);
#line 182 "../../../Source/Core/AST/AST.nll"
		if (pAst != 0)
		{
			NumbatLogic::AST* __78336793 = pAst;
#line 183 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 183 "../../../Source/Core/AST/AST.nll"
			return __78336793;
		}
		if (pAst) delete pAst;
#line 185 "../../../Source/Core/AST/AST.nll"
		return 0;
	}

#line 188 "../../../Source/Core/AST/AST.nll"
	AST* AST::TryCreateInnerExpression(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		AST* pAst = 0;
#line 192 "../../../Source/Core/AST/AST.nll"
		pAst = NumberExpr::TryCreate(pTokenContainer, pOffsetDatum);
#line 193 "../../../Source/Core/AST/AST.nll"
		if (pAst != 0)
		{
			NumbatLogic::AST* __78402393 = pAst;
#line 194 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 194 "../../../Source/Core/AST/AST.nll"
			return __78402393;
		}
#line 196 "../../../Source/Core/AST/AST.nll"
		pAst = BoolExpr::TryCreate(pTokenContainer, pOffsetDatum);
#line 197 "../../../Source/Core/AST/AST.nll"
		if (pAst != 0)
		{
			NumbatLogic::AST* __78402397 = pAst;
#line 198 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 198 "../../../Source/Core/AST/AST.nll"
			return __78402397;
		}
#line 200 "../../../Source/Core/AST/AST.nll"
		pAst = CharExpr::TryCreate(pTokenContainer, pOffsetDatum);
#line 201 "../../../Source/Core/AST/AST.nll"
		if (pAst != 0)
		{
			NumbatLogic::AST* __86073505 = pAst;
#line 202 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 202 "../../../Source/Core/AST/AST.nll"
			return __86073505;
		}
#line 204 "../../../Source/Core/AST/AST.nll"
		pAst = StringExpr::TryCreate(pTokenContainer, pOffsetDatum);
#line 205 "../../../Source/Core/AST/AST.nll"
		if (pAst != 0)
		{
			NumbatLogic::AST* __86073509 = pAst;
#line 206 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 206 "../../../Source/Core/AST/AST.nll"
			return __86073509;
		}
#line 208 "../../../Source/Core/AST/AST.nll"
		pAst = NullExpr::TryCreate(pTokenContainer, pOffsetDatum);
#line 209 "../../../Source/Core/AST/AST.nll"
		if (pAst != 0)
		{
			NumbatLogic::AST* __86073513 = pAst;
#line 210 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 210 "../../../Source/Core/AST/AST.nll"
			return __86073513;
		}
#line 212 "../../../Source/Core/AST/AST.nll"
		pAst = ThisExpr::TryCreate(pTokenContainer, pOffsetDatum);
#line 213 "../../../Source/Core/AST/AST.nll"
		if (pAst != 0)
		{
			NumbatLogic::AST* __86139106 = pAst;
#line 214 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 214 "../../../Source/Core/AST/AST.nll"
			return __86139106;
		}
#line 216 "../../../Source/Core/AST/AST.nll"
		pAst = BaseExpr::TryCreate(pTokenContainer, pOffsetDatum);
#line 217 "../../../Source/Core/AST/AST.nll"
		if (pAst != 0)
		{
			NumbatLogic::AST* __86139110 = pAst;
#line 218 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 218 "../../../Source/Core/AST/AST.nll"
			return __86139110;
		}
#line 220 "../../../Source/Core/AST/AST.nll"
		pAst = FunctionCall::TryCreate(pTokenContainer, pOffsetDatum);
#line 221 "../../../Source/Core/AST/AST.nll"
		if (pAst != 0)
		{
			NumbatLogic::AST* __86204703 = pAst;
#line 222 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 222 "../../../Source/Core/AST/AST.nll"
			return __86204703;
		}
#line 224 "../../../Source/Core/AST/AST.nll"
		pAst = New::TryCreate(pTokenContainer, pOffsetDatum);
#line 225 "../../../Source/Core/AST/AST.nll"
		if (pAst != 0)
		{
			NumbatLogic::AST* __86204707 = pAst;
#line 226 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 226 "../../../Source/Core/AST/AST.nll"
			return __86204707;
		}
#line 228 "../../../Source/Core/AST/AST.nll"
		pAst = CastExpr::TryCreate(pTokenContainer, pOffsetDatum);
#line 229 "../../../Source/Core/AST/AST.nll"
		if (pAst != 0)
		{
			NumbatLogic::AST* __86204711 = pAst;
#line 230 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 230 "../../../Source/Core/AST/AST.nll"
			return __86204711;
		}
#line 232 "../../../Source/Core/AST/AST.nll"
		pAst = TTHashExpr::TryCreate(pTokenContainer, pOffsetDatum);
#line 233 "../../../Source/Core/AST/AST.nll"
		if (pAst != 0)
		{
			NumbatLogic::AST* __86270304 = pAst;
#line 234 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 234 "../../../Source/Core/AST/AST.nll"
			return __86270304;
		}
#line 236 "../../../Source/Core/AST/AST.nll"
		pAst = Unary::TryCreate(pTokenContainer, pOffsetDatum);
#line 237 "../../../Source/Core/AST/AST.nll"
		if (pAst != 0)
		{
			NumbatLogic::AST* __86270308 = pAst;
#line 238 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 238 "../../../Source/Core/AST/AST.nll"
			return __86270308;
		}
#line 240 "../../../Source/Core/AST/AST.nll"
		pAst = Paren::TryCreate(pTokenContainer, pOffsetDatum);
#line 241 "../../../Source/Core/AST/AST.nll"
		if (pAst != 0)
		{
			NumbatLogic::AST* __86335901 = pAst;
#line 242 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 242 "../../../Source/Core/AST/AST.nll"
			return __86335901;
		}
#line 244 "../../../Source/Core/AST/AST.nll"
		pAst = ArrayLookup::TryCreate(pTokenContainer, pOffsetDatum);
#line 245 "../../../Source/Core/AST/AST.nll"
		if (pAst != 0)
		{
			NumbatLogic::AST* __86335905 = pAst;
#line 246 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 246 "../../../Source/Core/AST/AST.nll"
			return __86335905;
		}
#line 248 "../../../Source/Core/AST/AST.nll"
		pAst = StaticArray::TryCreate(pTokenContainer, pOffsetDatum);
#line 249 "../../../Source/Core/AST/AST.nll"
		if (pAst != 0)
		{
			NumbatLogic::AST* __86335909 = pAst;
#line 250 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 250 "../../../Source/Core/AST/AST.nll"
			return __86335909;
		}
#line 252 "../../../Source/Core/AST/AST.nll"
		pAst = OwnExpr::TryCreate(pTokenContainer, pOffsetDatum);
#line 253 "../../../Source/Core/AST/AST.nll"
		if (pAst != 0)
		{
			NumbatLogic::AST* __86401502 = pAst;
#line 254 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 254 "../../../Source/Core/AST/AST.nll"
			return __86401502;
		}
#line 256 "../../../Source/Core/AST/AST.nll"
		pAst = DisownExpr::TryCreate(pTokenContainer, pOffsetDatum);
#line 257 "../../../Source/Core/AST/AST.nll"
		if (pAst != 0)
		{
			NumbatLogic::AST* __86401506 = pAst;
#line 258 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 258 "../../../Source/Core/AST/AST.nll"
			return __86401506;
		}
#line 260 "../../../Source/Core/AST/AST.nll"
		pAst = RefExpr::TryCreate(pTokenContainer, pOffsetDatum);
#line 261 "../../../Source/Core/AST/AST.nll"
		if (pAst != 0)
		{
			NumbatLogic::AST* __86467099 = pAst;
#line 262 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 262 "../../../Source/Core/AST/AST.nll"
			return __86467099;
		}
#line 264 "../../../Source/Core/AST/AST.nll"
		pAst = Identifier::TryCreate(pTokenContainer, pOffsetDatum);
#line 265 "../../../Source/Core/AST/AST.nll"
		if (pAst != 0)
		{
			NumbatLogic::AST* __86467103 = pAst;
#line 266 "../../../Source/Core/AST/AST.nll"
			pAst = 0;
#line 266 "../../../Source/Core/AST/AST.nll"
			return __86467103;
		}
		if (pAst) delete pAst;
#line 268 "../../../Source/Core/AST/AST.nll"
		return 0;
	}

#line 271 "../../../Source/Core/AST/AST.nll"
	AST* AST::TryCreateExpression(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		AST* pLeft = TryCreateInnerExpression(pTokenContainer, pTempOffset);
#line 275 "../../../Source/Core/AST/AST.nll"
		if (pLeft != 0)
		{
			Token* pOperatorToken = pTokenContainer->Peek(pTempOffset);
#line 278 "../../../Source/Core/AST/AST.nll"
			if (pOperatorToken != 0 && pOperatorToken->m_eType == Token::Type::TOKEN_QUESTION_MARK)
			{
#line 280 "../../../Source/Core/AST/AST.nll"
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 281 "../../../Source/Core/AST/AST.nll"
				pOffsetDatum->Set(pTempOffset);
				NumbatLogic::AST* __3927602644 = pLeft;
#line 282 "../../../Source/Core/AST/AST.nll"
				pLeft = 0;
				if (pTempOffset) delete pTempOffset;
				if (pLeft) delete pLeft;
#line 282 "../../../Source/Core/AST/AST.nll"
				return TrinaryExpr::Create(__3927602644, pTokenContainer, pOffsetDatum);
			}
			OperatorExpr::OperatorType eOperatorType = OperatorExpr::PeekOperator(pTokenContainer, pTempOffset);
#line 286 "../../../Source/Core/AST/AST.nll"
			if (eOperatorType != OperatorExpr::OperatorType::UNKNOWN)
			{
#line 288 "../../../Source/Core/AST/AST.nll"
				if (OperatorExpr::IsPostfix(eOperatorType))
				{
#line 290 "../../../Source/Core/AST/AST.nll"
					pOffsetDatum->Set(pTempOffset);
					NumbatLogic::AST* __3927668242 = pLeft;
#line 291 "../../../Source/Core/AST/AST.nll"
					pLeft = 0;
					if (pTempOffset) delete pTempOffset;
					if (pLeft) delete pLeft;
#line 291 "../../../Source/Core/AST/AST.nll"
					return OperatorExpr::Create(eOperatorType, pOperatorToken, __3927668242, 0);
				}
				AST* pRight = TryCreateExpression(pTokenContainer, pTempOffset);
#line 295 "../../../Source/Core/AST/AST.nll"
				if (pRight != 0)
				{
#line 297 "../../../Source/Core/AST/AST.nll"
					pOffsetDatum->Set(pTempOffset);
					NumbatLogic::AST* __3927668249 = pLeft;
#line 298 "../../../Source/Core/AST/AST.nll"
					pLeft = 0;
					NumbatLogic::AST* __542787396 = pRight;
#line 298 "../../../Source/Core/AST/AST.nll"
					pRight = 0;
					if (pRight) delete pRight;
					if (pTempOffset) delete pTempOffset;
					if (pLeft) delete pLeft;
#line 298 "../../../Source/Core/AST/AST.nll"
					return OperatorExpr::Create(eOperatorType, pOperatorToken, __3927668249, __542787396);
				}
				InternalString* sTemp = new InternalString("Probably should have something after the operator??? ");
#line 303 "../../../Source/Core/AST/AST.nll"
				sTemp->Append(pOperatorToken->m_sFileName->GetExternalString());
#line 304 "../../../Source/Core/AST/AST.nll"
				sTemp->Append(":");
#line 305 "../../../Source/Core/AST/AST.nll"
				sTemp->AppendInt(pOperatorToken->m_nLine);
#line 306 "../../../Source/Core/AST/AST.nll"
				sTemp->Append(":");
#line 307 "../../../Source/Core/AST/AST.nll"
				sTemp->AppendInt(pOperatorToken->m_nColumn);
#line 308 "../../../Source/Core/AST/AST.nll"
				Console::Log(sTemp->GetExternalString());
#line 309 "../../../Source/Core/AST/AST.nll"
				Assert::Plz(false);
				if (pRight) delete pRight;
				if (sTemp) delete sTemp;
			}
#line 311 "../../../Source/Core/AST/AST.nll"
			pOffsetDatum->Set(pTempOffset);
			NumbatLogic::AST* __3935404956 = pLeft;
#line 312 "../../../Source/Core/AST/AST.nll"
			pLeft = 0;
			if (pTempOffset) delete pTempOffset;
#line 312 "../../../Source/Core/AST/AST.nll"
			return __3935404956;
		}
		if (pTempOffset) delete pTempOffset;
		if (pLeft) delete pLeft;
#line 314 "../../../Source/Core/AST/AST.nll"
		return 0;
	}

#line 317 "../../../Source/Core/AST/AST.nll"
	void AST::PreValidate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST* pChild = m_pFirstChild;
#line 320 "../../../Source/Core/AST/AST.nll"
		while (pChild != 0)
		{
			AST* pNextSibling = pChild->m_pNextSibling;
#line 324 "../../../Source/Core/AST/AST.nll"
			pChild->PreValidate(pValidator, 0);
#line 325 "../../../Source/Core/AST/AST.nll"
			pChild = pNextSibling;
		}
	}

#line 329 "../../../Source/Core/AST/AST.nll"
	void AST::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST* pChild = m_pFirstChild;
#line 332 "../../../Source/Core/AST/AST.nll"
		while (pChild != 0)
		{
			AST* pNextSibling = pChild->m_pNextSibling;
#line 336 "../../../Source/Core/AST/AST.nll"
			pChild->Validate(pValidator, 0);
#line 337 "../../../Source/Core/AST/AST.nll"
			pChild = pNextSibling;
		}
	}

#line 341 "../../../Source/Core/AST/AST.nll"
	void AST::AddChild(AST* pAst)
	{
#line 343 "../../../Source/Core/AST/AST.nll"
		pAst->m_pParent = this;
#line 345 "../../../Source/Core/AST/AST.nll"
		if (m_pFirstChild == 0)
		{
#line 347 "../../../Source/Core/AST/AST.nll"
			m_pFirstChild = pAst;
#line 348 "../../../Source/Core/AST/AST.nll"
			m_pLastChild = m_pFirstChild;
		}
		else
		{
#line 352 "../../../Source/Core/AST/AST.nll"
			m_pLastChild->m_pNextSibling = pAst;
#line 353 "../../../Source/Core/AST/AST.nll"
			m_pLastChild->m_pNextSibling->m_pPrevSibling = m_pLastChild;
#line 354 "../../../Source/Core/AST/AST.nll"
			m_pLastChild = m_pLastChild->m_pNextSibling;
		}
	}

#line 358 "../../../Source/Core/AST/AST.nll"
	void AST::AddChildFront(AST* pAst)
	{
#line 360 "../../../Source/Core/AST/AST.nll"
		if (m_pFirstChild == 0)
		{
#line 362 "../../../Source/Core/AST/AST.nll"
			AddChild(pAst);
#line 363 "../../../Source/Core/AST/AST.nll"
			return;
		}
#line 366 "../../../Source/Core/AST/AST.nll"
		pAst->m_pParent = this;
		NumbatLogic::AST* __1700709385 = m_pFirstChild;
#line 367 "../../../Source/Core/AST/AST.nll"
		m_pFirstChild = 0;
#line 367 "../../../Source/Core/AST/AST.nll"
		pAst->m_pNextSibling = __1700709385;
#line 368 "../../../Source/Core/AST/AST.nll"
		m_pFirstChild = pAst;
#line 369 "../../../Source/Core/AST/AST.nll"
		pAst->m_pNextSibling->m_pPrevSibling = m_pFirstChild;
	}

#line 372 "../../../Source/Core/AST/AST.nll"
	void AST::AddChildBefore(AST* pAst, AST* pBefore)
	{
#line 374 "../../../Source/Core/AST/AST.nll"
		Assert::Plz(pBefore->m_pParent == this);
#line 376 "../../../Source/Core/AST/AST.nll"
		pAst->m_pParent = this;
#line 378 "../../../Source/Core/AST/AST.nll"
		if (m_pFirstChild == pBefore)
		{
			NumbatLogic::AST* __1700774987 = m_pFirstChild;
#line 380 "../../../Source/Core/AST/AST.nll"
			m_pFirstChild = 0;
#line 380 "../../../Source/Core/AST/AST.nll"
			pAst->m_pNextSibling = __1700774987;
#line 381 "../../../Source/Core/AST/AST.nll"
			m_pFirstChild = pAst;
#line 382 "../../../Source/Core/AST/AST.nll"
			pBefore->m_pPrevSibling = m_pFirstChild;
		}
		else
		{
			NumbatLogic::AST* __96456765 = pBefore->m_pPrevSibling->m_pNextSibling;
#line 386 "../../../Source/Core/AST/AST.nll"
			pBefore->m_pPrevSibling->m_pNextSibling = 0;
#line 386 "../../../Source/Core/AST/AST.nll"
			pAst->m_pNextSibling = __96456765;
#line 387 "../../../Source/Core/AST/AST.nll"
			pAst->m_pPrevSibling = pBefore->m_pPrevSibling;
#line 388 "../../../Source/Core/AST/AST.nll"
			pBefore->m_pPrevSibling = (AST*)(pAst);
#line 389 "../../../Source/Core/AST/AST.nll"
			pAst->m_pPrevSibling->m_pNextSibling = pAst;
		}
	}

#line 393 "../../../Source/Core/AST/AST.nll"
	AST* AST::RemoveChild(AST* pChild)
	{
#line 395 "../../../Source/Core/AST/AST.nll"
		if (m_pFirstChild == pChild)
		{
			NumbatLogic::AST* __1700906182 = m_pFirstChild;
#line 397 "../../../Source/Core/AST/AST.nll"
			m_pFirstChild = 0;
			AST* pOwnedChild = __1700906182;
#line 398 "../../../Source/Core/AST/AST.nll"
			if (m_pLastChild == pOwnedChild)
#line 399 "../../../Source/Core/AST/AST.nll"
				m_pLastChild = 0;
			else
			{
				NumbatLogic::AST* __400431243 = pOwnedChild->m_pNextSibling;
#line 401 "../../../Source/Core/AST/AST.nll"
				pOwnedChild->m_pNextSibling = 0;
#line 401 "../../../Source/Core/AST/AST.nll"
				m_pFirstChild = __400431243;
			}
#line 402 "../../../Source/Core/AST/AST.nll"
			pOwnedChild->m_pParent = 0;
			NumbatLogic::AST* __2252725199 = pOwnedChild;
#line 403 "../../../Source/Core/AST/AST.nll"
			pOwnedChild = 0;
#line 403 "../../../Source/Core/AST/AST.nll"
			return __2252725199;
		}
		else
		{
			AST* pFindChild = m_pFirstChild;
#line 408 "../../../Source/Core/AST/AST.nll"
			while (pFindChild != 0)
			{
#line 410 "../../../Source/Core/AST/AST.nll"
				if (pFindChild->m_pNextSibling == pChild)
				{
					NumbatLogic::AST* __326915199 = pFindChild->m_pNextSibling;
#line 412 "../../../Source/Core/AST/AST.nll"
					pFindChild->m_pNextSibling = 0;
					AST* pOwnedChild = __326915199;
#line 413 "../../../Source/Core/AST/AST.nll"
					if (m_pLastChild == pOwnedChild)
#line 414 "../../../Source/Core/AST/AST.nll"
						m_pLastChild = pFindChild;
					else
					{
						NumbatLogic::AST* __400496847 = pOwnedChild->m_pNextSibling;
#line 416 "../../../Source/Core/AST/AST.nll"
						pOwnedChild->m_pNextSibling = 0;
#line 416 "../../../Source/Core/AST/AST.nll"
						pFindChild->m_pNextSibling = __400496847;
					}
#line 417 "../../../Source/Core/AST/AST.nll"
					pOwnedChild->m_pParent = 0;
					NumbatLogic::AST* __2252790803 = pOwnedChild;
#line 418 "../../../Source/Core/AST/AST.nll"
					pOwnedChild = 0;
#line 418 "../../../Source/Core/AST/AST.nll"
					return __2252790803;
				}
#line 421 "../../../Source/Core/AST/AST.nll"
				pFindChild = pFindChild->m_pNextSibling;
			}
		}
#line 425 "../../../Source/Core/AST/AST.nll"
		return 0;
	}

#line 429 "../../../Source/Core/AST/AST.nll"
	void AST::AddClassDeclReference(ClassDecl* pClassDecl, OutputFile eOutputFile, bool bForwardReference)
	{
#line 431 "../../../Source/Core/AST/AST.nll"
		if (m_pParent != 0)
#line 432 "../../../Source/Core/AST/AST.nll"
			m_pParent->AddClassDeclReference(pClassDecl, eOutputFile, bForwardReference);
	}

#line 436 "../../../Source/Core/AST/AST.nll"
	Project* AST::GetProject()
	{
		AST* p = this;
#line 439 "../../../Source/Core/AST/AST.nll"
		while (p != 0 && p->m_eType != AST::Type::AST_PROJECT)
#line 440 "../../../Source/Core/AST/AST.nll"
			p = p->m_pParent;
#line 441 "../../../Source/Core/AST/AST.nll"
		return p != 0 ? (Project*)(p) : 0;
	}

#line 444 "../../../Source/Core/AST/AST.nll"
	void AST::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 446 "../../../Source/Core/AST/AST.nll"
		pOutputBuilder->m_sOut->Append("???");
	}

#line 449 "../../../Source/Core/AST/AST.nll"
	AST* AST::BaseClone()
	{
		InternalString* sTemp = new InternalString("BaseClone() not setup for ");
#line 452 "../../../Source/Core/AST/AST.nll"
		StringifyType(sTemp);
#line 453 "../../../Source/Core/AST/AST.nll"
		Console::Log(sTemp->GetExternalString());
#line 454 "../../../Source/Core/AST/AST.nll"
		Assert::Plz(false);
		if (sTemp) delete sTemp;
#line 455 "../../../Source/Core/AST/AST.nll"
		return 0;
	}

#line 458 "../../../Source/Core/AST/AST.nll"
	AST* AST::GetParentStatement()
	{
		AST* pParent = m_pParent;
#line 461 "../../../Source/Core/AST/AST.nll"
		while (pParent != 0)
		{
#line 463 "../../../Source/Core/AST/AST.nll"
			if (pParent->m_bStatement)
#line 464 "../../../Source/Core/AST/AST.nll"
				break;
#line 465 "../../../Source/Core/AST/AST.nll"
			pParent = pParent->m_pParent;
		}
#line 468 "../../../Source/Core/AST/AST.nll"
		return pParent;
	}

#line 471 "../../../Source/Core/AST/AST.nll"
	void AST::StringifyType(InternalString* sOut)
	{
#line 473 "../../../Source/Core/AST/AST.nll"
		switch (m_eType)
		{
			case Type::AST_ACCESS_LEVEL:
			{
#line 475 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_ACCESS_LEVEL");
#line 475 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_ARRAY_LOOKUP:
			{
#line 476 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_ARRAY_LOOKUP");
#line 476 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_BOOL_EXPR:
			{
#line 477 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_BOOL_EXPR");
#line 477 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_BREAK_STMT:
			{
#line 478 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_BREAK_STMT");
#line 478 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_CAST_EXP:
			{
#line 479 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_CAST_EXP");
#line 479 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_CHAR:
			{
#line 480 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_CHAR");
#line 480 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_CLASS_DECL:
			{
#line 481 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_CLASS_DECL");
#line 481 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_CONTINUE_STMT:
			{
#line 482 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_CONTINUE_STMT");
#line 482 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_DELETE_STMT:
			{
#line 483 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_DELETE_STMT");
#line 483 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_DISOWN_EXP:
			{
#line 484 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_DISOWN_EXP");
#line 484 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_ENUM_DECL:
			{
#line 485 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_ENUM_DECL");
#line 485 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_EXPRESSION_STMT:
			{
#line 486 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_EXPRESSION_STMT");
#line 486 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_FOR_STMT:
			{
#line 487 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_FOR_STMT");
#line 487 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_FUNCTION_CALL:
			{
#line 488 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_FUNCTION_CALL");
#line 488 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_FUNCTION_DECL:
			{
#line 489 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_FUNCTION_DECL");
#line 489 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_GENERIC_TYPE_DECL:
			{
#line 490 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_GENERIC_TYPE_DECL");
#line 490 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_IDENTIFIER:
			{
#line 491 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_IDENTIFIER");
#line 491 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_IF_STMT:
			{
#line 492 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_IF_STMT");
#line 492 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_MEMBER_ENUM_DECL:
			{
#line 493 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_MEMBER_ENUM_DECL");
#line 493 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_MEMBER_FUNCTION_DECL:
			{
#line 494 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_MEMBER_FUNCTION_DECL");
#line 494 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_MEMBER_VAR_DECL:
			{
#line 495 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_MEMBER_VAR_DECL");
#line 495 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_NEW_EXP:
			{
#line 496 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_NEW_EXP");
#line 496 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_NUMBER:
			{
#line 497 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_NUMBER");
#line 497 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_OPERATOR_EXPR:
			{
#line 498 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_OPERATOR_EXPR");
#line 498 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_OWN_EXP:
			{
#line 499 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_OWN_EXP");
#line 499 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_PARAM_CALL:
			{
#line 500 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_PARAM_CALL");
#line 500 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_PARAM_DECL:
			{
#line 501 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_PARAM_DECL");
#line 501 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_PAREN:
			{
#line 502 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_PAREN");
#line 502 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_REF_EXPR:
			{
#line 503 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_REF_EXPR");
#line 503 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_RETURN_STMT:
			{
#line 504 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_RETURN_STMT");
#line 504 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_SCOPE:
			{
#line 505 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_SCOPE");
#line 505 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_STATIC_ARRAY:
			{
#line 506 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_STATIC_ARRAY");
#line 506 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_STRING:
			{
#line 507 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_STRING");
#line 507 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_SWITCH_STMT:
			{
#line 508 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_SWITCH_STMT");
#line 508 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_TOR_DECL:
			{
#line 509 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_TOR_DECL");
#line 509 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_TRANSLATION_UNIT:
			{
#line 510 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_TRANSLATION_UNIT");
#line 510 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_TTHASH_EXP:
			{
#line 511 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_TTHASH_EXP");
#line 511 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_TYPE_REF:
			{
#line 512 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_TYPE_REF");
#line 512 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_UNARY:
			{
#line 513 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_UNARY");
#line 513 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_VAR_DECL_DESCOPE:
			{
#line 514 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_VAR_DECL_DESCOPE");
#line 514 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_VAR_DECL:
			{
#line 515 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_VAR_DECL");
#line 515 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_WHILE_STMT:
			{
#line 516 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_WHILE_STMT");
#line 516 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::AST_PROJECT:
			{
#line 517 "../../../Source/Core/AST/AST.nll"
				sOut->Append("AST_PROJECT");
#line 517 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::BASE_EXPR:
			{
#line 518 "../../../Source/Core/AST/AST.nll"
				sOut->Append("BASE_EXPR");
#line 518 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::DELEGATE_DECL:
			{
#line 519 "../../../Source/Core/AST/AST.nll"
				sOut->Append("DELEGATE_DECL");
#line 519 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::ENUM_DECL_VALUE:
			{
#line 520 "../../../Source/Core/AST/AST.nll"
				sOut->Append("ENUM_DECL_VALUE");
#line 520 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::MEMBER_VARS_SET_DEFAULT_STMT:
			{
#line 521 "../../../Source/Core/AST/AST.nll"
				sOut->Append("MEMBER_VARS_SET_DEFAULT_STMT");
#line 521 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::NAMESPACE_DECL:
			{
#line 522 "../../../Source/Core/AST/AST.nll"
				sOut->Append("NAMESPACE_DECL");
#line 522 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::NULL_EXPR:
			{
#line 523 "../../../Source/Core/AST/AST.nll"
				sOut->Append("NULL_EXPR");
#line 523 "../../../Source/Core/AST/AST.nll"
				return;
			}

			case Type::THIS_EXPR:
			{
#line 524 "../../../Source/Core/AST/AST.nll"
				sOut->Append("THIS_EXPR");
#line 524 "../../../Source/Core/AST/AST.nll"
				return;
			}

		}
#line 527 "../../../Source/Core/AST/AST.nll"
		sOut->Append("???");
	}

}

