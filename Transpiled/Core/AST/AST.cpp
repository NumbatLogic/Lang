#include "AST.hpp"
#include "../Token.hpp"
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
#include "Unary.hpp"
#include "Paren.hpp"
#include "ArrayLookup.hpp"
#include "StaticArray.hpp"
#include "OwnExpr.hpp"
#include "DisownExpr.hpp"
#include "Identifier.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "OperatorExpr.hpp"
#include "TrinaryExpr.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"

namespace NumbatLogic
{
	class ValueType;
	class AST;
	class FunctionDecl;
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
	class Unary;
	class Paren;
	class ArrayLookup;
	class StaticArray;
	class OwnExpr;
	class DisownExpr;
	class Identifier;
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class OperatorExpr;
	class TrinaryExpr;
	class ClassDecl;
	class Assert;
	class InternalString;
	class Console;
}
namespace NumbatLogic
{
	AST::AST()
	{
		m_eType = Type::AST_ACCESS_LEVEL;
		m_pFirstToken = 0;
		m_pParent = 0;
		m_pFirstChild = 0;
		m_pLastChild = 0;
		m_pPrevSibling = 0;
		m_pNextSibling = 0;
		m_bCanDescend = false;
		m_pValueType = 0;
		m_bStatement = false;
		m_bSkipOutput = false;
		m_bStatement = false;
		m_bSkipOutput = false;
	}

	AST::~AST()
	{
		if (m_pFirstChild) delete m_pFirstChild;
		if (m_pNextSibling) delete m_pNextSibling;
		if (m_pValueType) delete m_pValueType;
	}

	AST* AST::CreateFromTokenContainer(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		AST* pAst = 0;
		pAst = FunctionDecl::TryCreate(pTokenContainer, pOffsetDatum, 0);
		if (pAst != 0)
		{
			NumbatLogic::AST* __2357047103 = pAst;
			pAst = 0;
			return __2357047103;
		}
		pAst = ClassDecl::TryCreate(pTokenContainer, pOffsetDatum, 0);
		if (pAst != 0)
		{
			NumbatLogic::AST* __1216195698 = pAst;
			pAst = 0;
			return __1216195698;
		}
		pAst = NamespaceDecl::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __998082482 = pAst;
			pAst = 0;
			return __998082482;
		}
		pAst = CreateStatementFromTokenContainer(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __2273150700 = pAst;
			pAst = 0;
			return __2273150700;
		}
		pAst = TryCreateExpression(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __2591947929 = pAst;
			pAst = 0;
			return __2591947929;
		}
		if (pAst) delete pAst;
		return 0;
	}

	AST* AST::CreateStatementFromTokenContainer(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		AST* pAst = 0;
		pAst = ReturnStmt::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __1048433994 = pAst;
			pAst = 0;
			return __1048433994;
		}
		pAst = BreakStmt::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __2189284372 = pAst;
			pAst = 0;
			return __2189284372;
		}
		pAst = ContinueStmt::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __3413969726 = pAst;
			pAst = 0;
			return __3413969726;
		}
		pAst = Scope::TryCreate(pTokenContainer, pOffsetDatum, false);
		if (pAst != 0)
		{
			NumbatLogic::AST* __2004683360 = pAst;
			pAst = 0;
			return __2004683360;
		}
		pAst = VarDecl::TryCreate(pTokenContainer, pOffsetDatum, false);
		if (pAst != 0)
		{
			NumbatLogic::AST* __3011316013 = pAst;
			pAst = 0;
			return __3011316013;
		}
		pAst = EnumDecl::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __3229426413 = pAst;
			pAst = 0;
			return __3229426413;
		}
		pAst = DeleteStmt::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __2088575923 = pAst;
			pAst = 0;
			return __2088575923;
		}
		pAst = IfStmt::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __1635604934 = pAst;
			pAst = 0;
			return __1635604934;
		}
		pAst = ForStmt::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __3715979416 = pAst;
			pAst = 0;
			return __3715979416;
		}
		pAst = WhileStmt::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __427645909 = pAst;
			pAst = 0;
			return __427645909;
		}
		pAst = SwitchStmt::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __1786605589 = pAst;
			pAst = 0;
			return __1786605589;
		}
		pAst = ExpressionStmt::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __3598545227 = pAst;
			pAst = 0;
			return __3598545227;
		}
		if (pAst) delete pAst;
		return 0;
	}

	AST* AST::TryCreateInnerExpression(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		AST* pAst = 0;
		pAst = NumberExpr::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __2055005486 = pAst;
			pAst = 0;
			return __2055005486;
		}
		pAst = BoolExpr::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __3447508387 = pAst;
			pAst = 0;
			return __3447508387;
		}
		pAst = CharExpr::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __1904004349 = pAst;
			pAst = 0;
			return __1904004349;
		}
		pAst = StringExpr::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __3044855728 = pAst;
			pAst = 0;
			return __3044855728;
		}
		pAst = NullExpr::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __189636289 = pAst;
			pAst = 0;
			return __189636289;
		}
		pAst = ThisExpr::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __3075317663 = pAst;
			pAst = 0;
			return __3075317663;
		}
		pAst = BaseExpr::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __5093138 = pAst;
			pAst = 0;
			return __5093138;
		}
		pAst = FunctionCall::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __3159209548 = pAst;
			pAst = 0;
			return __3159209548;
		}
		pAst = New::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __2018358529 = pAst;
			pAst = 0;
			return __2018358529;
		}
		pAst = CastExpr::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __2706230329 = pAst;
			pAst = 0;
			return __2706230329;
		}
		pAst = Unary::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __491638119 = pAst;
			pAst = 0;
			return __491638119;
		}
		pAst = Paren::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __2857231850 = pAst;
			pAst = 0;
			return __2857231850;
		}
		pAst = ArrayLookup::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __374203572 = pAst;
			pAst = 0;
			return __374203572;
		}
		pAst = StaticArray::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __3528321017 = pAst;
			pAst = 0;
			return __3528321017;
		}
		pAst = OwnExpr::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __1598897054 = pAst;
			pAst = 0;
			return __1598897054;
		}
		pAst = DisownExpr::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __3813489344 = pAst;
			pAst = 0;
			return __3813489344;
		}
		pAst = Identifier::TryCreate(pTokenContainer, pOffsetDatum);
		if (pAst != 0)
		{
			NumbatLogic::AST* __1414337101 = pAst;
			pAst = 0;
			return __1414337101;
		}
		if (pAst) delete pAst;
		return 0;
	}

	AST* AST::TryCreateExpression(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		AST* pLeft = TryCreateInnerExpression(pTokenContainer, pTempOffset);
		if (pLeft != 0)
		{
			Token* pOperatorToken = pTokenContainer->Peek(pTempOffset);
			if (pOperatorToken != 0)
			{
				if (pOperatorToken->m_eType == Token::Type::TOKEN_MINUS_MINUS || pOperatorToken->m_eType == Token::Type::TOKEN_PLUS_PLUS)
				{
					pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
					pOffsetDatum->Set(pTempOffset);
					NumbatLogic::AST* __4127036928 = pLeft;
					pLeft = 0;
					if (pTempOffset) delete pTempOffset;
					if (pLeft) delete pLeft;
					return OperatorExpr::Create(pOperatorToken, __4127036928, 0);
				}
				if (pOperatorToken->m_eType == Token::Type::TOKEN_QUESTION_MARK)
				{
					pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
					pOffsetDatum->Set(pTempOffset);
					NumbatLogic::AST* __587043859 = pLeft;
					pLeft = 0;
					if (pTempOffset) delete pTempOffset;
					if (pLeft) delete pLeft;
					return TrinaryExpr::Create(__587043859, pTokenContainer, pOffsetDatum);
				}
				if (pOperatorToken->m_eType == Token::Type::TOKEN_AND || pOperatorToken->m_eType == Token::Type::TOKEN_ANGLE_BRACKET_LEFT || pOperatorToken->m_eType == Token::Type::TOKEN_ANGLE_BRACKET_LEFT_EQUALS || pOperatorToken->m_eType == Token::Type::TOKEN_ANGLE_BRACKET_RIGHT || pOperatorToken->m_eType == Token::Type::TOKEN_ANGLE_BRACKET_RIGHT_EQUALS || pOperatorToken->m_eType == Token::Type::TOKEN_BITWISE_AND || pOperatorToken->m_eType == Token::Type::TOKEN_BITWISE_OR || pOperatorToken->m_eType == Token::Type::TOKEN_CARET || pOperatorToken->m_eType == Token::Type::TOKEN_DIVIDE || pOperatorToken->m_eType == Token::Type::TOKEN_DOT || pOperatorToken->m_eType == Token::Type::TOKEN_DOUBLE_ANGLE_BRACKET_LEFT || pOperatorToken->m_eType == Token::Type::TOKEN_DOUBLE_ANGLE_BRACKET_RIGHT || pOperatorToken->m_eType == Token::Type::TOKEN_DOUBLE_COLON || pOperatorToken->m_eType == Token::Type::TOKEN_DOUBLE_EQUALS || pOperatorToken->m_eType == Token::Type::TOKEN_EQUALS || pOperatorToken->m_eType == Token::Type::TOKEN_MINUS || pOperatorToken->m_eType == Token::Type::TOKEN_MINUS_EQUALS || pOperatorToken->m_eType == Token::Type::TOKEN_NOT_EQUALS || pOperatorToken->m_eType == Token::Type::TOKEN_OR || pOperatorToken->m_eType == Token::Type::TOKEN_PLUS || pOperatorToken->m_eType == Token::Type::TOKEN_PLUS_EQUALS || pOperatorToken->m_eType == Token::Type::TOKEN_STAR || pOperatorToken->m_eType == Token::Type::TOKEN_MODULUS)
				{
					pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
					AST* pRight = TryCreateExpression(pTokenContainer, pTempOffset);
					if (pRight != 0)
					{
						pOffsetDatum->Set(pTempOffset);
						NumbatLogic::AST* __686649762 = pLeft;
						pLeft = 0;
						NumbatLogic::AST* __2223850361 = pRight;
						pRight = 0;
						if (pRight) delete pRight;
						if (pTempOffset) delete pTempOffset;
						if (pLeft) delete pLeft;
						return OperatorExpr::Create(pOperatorToken, __686649762, __2223850361);
					}
					if (pRight) delete pRight;
				}
			}
			pOffsetDatum->Set(pTempOffset);
			NumbatLogic::AST* __1710059603 = pLeft;
			pLeft = 0;
			if (pTempOffset) delete pTempOffset;
			return __1710059603;
		}
		if (pTempOffset) delete pTempOffset;
		if (pLeft) delete pLeft;
		return 0;
	}

	void AST::PreValidate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST* pChild = m_pFirstChild;
		while (pChild != 0)
		{
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
			AST* pNextSibling = pChild->m_pNextSibling;
			pChild->Validate(pValidator, 0);
			pChild = pNextSibling;
		}
	}

	ClassDecl* AST::FindClassDecl(const char* sTypeName, AST* pCallingChild)
	{
		if (pCallingChild != 0)
		{
			AST* pChild = m_pFirstChild;
			while (pChild != 0)
			{
				if (pChild != pCallingChild)
				{
					ClassDecl* pResult = pChild->FindClassDecl(sTypeName, 0);
					if (pResult != 0)
						return pResult;
				}
				pChild = pChild->m_pNextSibling;
			}
			if (m_pParent != 0)
				return m_pParent->FindClassDecl(sTypeName, this);
		}
		else
		{
			if (m_bCanDescend)
			{
				AST* pChild = m_pFirstChild;
				while (pChild != 0)
				{
					ClassDecl* pResult = pChild->FindClassDecl(sTypeName, 0);
					if (pResult != 0)
						return pResult;
					pChild = pChild->m_pNextSibling;
				}
			}
		}
		return 0;
	}

	AST* AST::FindByName(const char* sName, AST* pCallingChild)
	{
		if (pCallingChild != 0)
		{
			AST* pChild = m_pFirstChild;
			while (pChild != 0)
			{
				if (pChild != pCallingChild)
				{
					AST* pResult = pChild->FindByName(sName, 0);
					if (pResult != 0)
						return pResult;
				}
				pChild = pChild->m_pNextSibling;
			}
			if (m_pParent != 0)
				return m_pParent->FindByName(sName, this);
		}
		else
		{
			if (m_bCanDescend)
			{
				AST* pChild = m_pFirstChild;
				while (pChild != 0)
				{
					AST* pResult = pChild->FindByName(sName, 0);
					if (pResult != 0)
						return pResult;
					pChild = pChild->m_pNextSibling;
				}
			}
		}
		return 0;
	}

	void AST::AddChild(AST* pAst)
	{
		pAst->m_pParent = this;
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
		pAst->m_pParent = this;
		NumbatLogic::AST* __3364210159 = m_pFirstChild;
		m_pFirstChild = 0;
		pAst->m_pNextSibling = __3364210159;
		m_pFirstChild = pAst;
		pAst->m_pNextSibling->m_pPrevSibling = m_pFirstChild;
	}

	void AST::AddChildBefore(AST* pAst, AST* pBefore)
	{
		NumbatLogic::Assert::Plz(pBefore->m_pParent == this);
		pAst->m_pParent = this;
		if (m_pFirstChild == pBefore)
		{
			NumbatLogic::AST* __4135972830 = m_pFirstChild;
			m_pFirstChild = 0;
			pAst->m_pNextSibling = __4135972830;
			m_pFirstChild = pAst;
			pBefore->m_pPrevSibling = m_pFirstChild;
		}
		else
		{
			NumbatLogic::AST* __4280837940 = pBefore->m_pPrevSibling->m_pNextSibling;
			pBefore->m_pPrevSibling->m_pNextSibling = 0;
			pAst->m_pNextSibling = __4280837940;
			pAst->m_pPrevSibling = pBefore->m_pPrevSibling;
			pBefore->m_pPrevSibling = (AST*)(pAst);
			pAst->m_pPrevSibling->m_pNextSibling = pAst;
		}
	}

	AST* AST::RemoveChild(AST* pChild)
	{
		if (m_pFirstChild == pChild)
		{
			NumbatLogic::AST* __931511915 = m_pFirstChild;
			m_pFirstChild = 0;
			AST* pOwnedChild = __931511915;
			if (m_pLastChild == pOwnedChild)
				m_pLastChild = 0;
			else
			{
				NumbatLogic::AST* __1213399723 = pOwnedChild->m_pNextSibling;
				pOwnedChild->m_pNextSibling = 0;
				m_pFirstChild = __1213399723;
			}
			pOwnedChild->m_pParent = 0;
			NumbatLogic::AST* __2040457964 = pOwnedChild;
			pOwnedChild = 0;
			return __2040457964;
		}
		else
		{
			AST* pFindChild = m_pFirstChild;
			while (pFindChild != 0)
			{
				if (pFindChild->m_pNextSibling == pChild)
				{
					NumbatLogic::AST* __4069245639 = pFindChild->m_pNextSibling;
					pFindChild->m_pNextSibling = 0;
					AST* pOwnedChild = __4069245639;
					if (m_pLastChild == pOwnedChild)
						m_pLastChild = pFindChild;
					else
					{
						NumbatLogic::AST* __1968356607 = pOwnedChild->m_pNextSibling;
						pOwnedChild->m_pNextSibling = 0;
						pFindChild->m_pNextSibling = __1968356607;
					}
					pOwnedChild->m_pParent = 0;
					NumbatLogic::AST* __1637794401 = pOwnedChild;
					pOwnedChild = 0;
					return __1637794401;
				}
				pFindChild = pFindChild->m_pNextSibling;
			}
		}
		return 0;
	}

	void AST::AddClassDeclReference(ClassDecl* pClassDecl, OutputFile eOutputFile, bool bForwardReference)
	{
		if (m_pParent != 0)
			m_pParent->AddClassDeclReference(pClassDecl, eOutputFile, bForwardReference);
	}

	void AST::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		sOut->Append("???");
	}

	AST* AST::BaseClone()
	{
		InternalString* sTemp = new InternalString("BaseClone() not setup for ");
		StringifyType(sTemp);
		Console::Log(sTemp->GetExternalString());
		NumbatLogic::Assert::Plz(false);
		if (sTemp) delete sTemp;
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
		return pParent;
	}

	void AST::StringifyType(InternalString* sOut)
	{
		switch (m_eType)
		{
			case Type::AST_ACCESS_LEVEL:
			{
				sOut->Append("AST_ACCESS_LEVEL");
				return;
			}

			case Type::AST_ARRAY_LOOKUP:
			{
				sOut->Append("AST_ARRAY_LOOKUP");
				return;
			}

			case Type::AST_BOOL_EXPR:
			{
				sOut->Append("AST_BOOL_EXPR");
				return;
			}

			case Type::AST_BREAK_STMT:
			{
				sOut->Append("AST_BREAK_STMT");
				return;
			}

			case Type::AST_CAST_EXP:
			{
				sOut->Append("AST_CAST_EXP");
				return;
			}

			case Type::AST_CHAR:
			{
				sOut->Append("AST_CHAR");
				return;
			}

			case Type::AST_CLASS_DECL:
			{
				sOut->Append("AST_CLASS_DECL");
				return;
			}

			case Type::AST_CONTINUE_STMT:
			{
				sOut->Append("AST_CONTINUE_STMT");
				return;
			}

			case Type::AST_DELETE_STMT:
			{
				sOut->Append("AST_DELETE_STMT");
				return;
			}

			case Type::AST_DISOWN_EXP:
			{
				sOut->Append("AST_DISOWN_EXP");
				return;
			}

			case Type::AST_ENUM_DECL:
			{
				sOut->Append("AST_ENUM_DECL");
				return;
			}

			case Type::AST_EXPRESSION_STMT:
			{
				sOut->Append("AST_EXPRESSION_STMT");
				return;
			}

			case Type::AST_FOR_STMT:
			{
				sOut->Append("AST_FOR_STMT");
				return;
			}

			case Type::AST_FUNCTION_CALL:
			{
				sOut->Append("AST_FUNCTION_CALL");
				return;
			}

			case Type::AST_FUNCTION_DECL:
			{
				sOut->Append("AST_FUNCTION_DECL");
				return;
			}

			case Type::AST_GENERIC_TYPE_DECL:
			{
				sOut->Append("AST_GENERIC_TYPE_DECL");
				return;
			}

			case Type::AST_IDENTIFIER:
			{
				sOut->Append("AST_IDENTIFIER");
				return;
			}

			case Type::AST_IF_STMT:
			{
				sOut->Append("AST_IF_STMT");
				return;
			}

			case Type::AST_MEMBER_ENUM_DECL:
			{
				sOut->Append("AST_MEMBER_ENUM_DECL");
				return;
			}

			case Type::AST_MEMBER_FUNCTION_DECL:
			{
				sOut->Append("AST_MEMBER_FUNCTION_DECL");
				return;
			}

			case Type::AST_MEMBER_VAR_DECL:
			{
				sOut->Append("AST_MEMBER_VAR_DECL");
				return;
			}

			case Type::AST_NEW_EXP:
			{
				sOut->Append("AST_NEW_EXP");
				return;
			}

			case Type::AST_NUMBER:
			{
				sOut->Append("AST_NUMBER");
				return;
			}

			case Type::AST_OPERATOR_EXPR:
			{
				sOut->Append("AST_OPERATOR_EXPR");
				return;
			}

			case Type::AST_OWN_EXP:
			{
				sOut->Append("AST_OWN_EXP");
				return;
			}

			case Type::AST_PARAM_CALL:
			{
				sOut->Append("AST_PARAM_CALL");
				return;
			}

			case Type::AST_PARAM_DECL:
			{
				sOut->Append("AST_PARAM_DECL");
				return;
			}

			case Type::AST_PAREN:
			{
				sOut->Append("AST_PAREN");
				return;
			}

			case Type::AST_RETURN_STMT:
			{
				sOut->Append("AST_RETURN_STMT");
				return;
			}

			case Type::AST_SCOPE:
			{
				sOut->Append("AST_SCOPE");
				return;
			}

			case Type::AST_STATIC_ARRAY:
			{
				sOut->Append("AST_STATIC_ARRAY");
				return;
			}

			case Type::AST_STRING:
			{
				sOut->Append("AST_STRING");
				return;
			}

			case Type::AST_SWITCH_STMT:
			{
				sOut->Append("AST_SWITCH_STMT");
				return;
			}

			case Type::AST_TOR_DECL:
			{
				sOut->Append("AST_TOR_DECL");
				return;
			}

			case Type::AST_TRANSLATION_UNIT:
			{
				sOut->Append("AST_TRANSLATION_UNIT");
				return;
			}

			case Type::AST_TYPE_REF:
			{
				sOut->Append("AST_TYPE_REF");
				return;
			}

			case Type::AST_UNARY:
			{
				sOut->Append("AST_UNARY");
				return;
			}

			case Type::AST_VAR_DECL:
			{
				sOut->Append("AST_VAR_DECL");
				return;
			}

			case Type::AST_VAR_DECL_DESCOPE:
			{
				sOut->Append("AST_VAR_DECL_DESCOPE");
				return;
			}

			case Type::AST_WHILE_STMT:
			{
				sOut->Append("AST_WHILE_STMT");
				return;
			}

			case Type::BASE_EXPR:
			{
				sOut->Append("BASE_EXPR");
				return;
			}

			case Type::DELEGATE_DECL:
			{
				sOut->Append("DELEGATE_DECL");
				return;
			}

			case Type::ENUM_DECL_VALUE:
			{
				sOut->Append("ENUM_DECL_VALUE");
				return;
			}

			case Type::MEMBER_VARS_SET_DEFAULT_STMT:
			{
				sOut->Append("MEMBER_VARS_SET_DEFAULT_STMT");
				return;
			}

			case Type::NAMESPACE_DECL:
			{
				sOut->Append("NAMESPACE_DECL");
				return;
			}

			case Type::NULL_EXPR:
			{
				sOut->Append("NULL_EXPR");
				return;
			}

			case Type::THIS_EXPR:
			{
				sOut->Append("THIS_EXPR");
				return;
			}

		}
		sOut->Append("???");
	}

}

