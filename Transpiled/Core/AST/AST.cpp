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
#include "../../../Shared/CPP/InternalString.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"

namespace NumberDuck
{
	namespace Secret
	{
		class AST;
		class OffsetDatum;
		class Token;
		class ClassDecl;
		class InternalString;
	}
}
namespace NumberDuck
{
	namespace Secret
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
				NumberDuck::Secret::AST* __4200063409 = pAst;
				pAst = 0;
				return __4200063409;
			}
			pAst = ClassDecl::TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != 0)
			{
				NumberDuck::Secret::AST* __4200063409 = pAst;
				pAst = 0;
				return __4200063409;
			}
			pAst = NamespaceDecl::TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != 0)
			{
				NumberDuck::Secret::AST* __4200063409 = pAst;
				pAst = 0;
				return __4200063409;
			}
			pAst = CreateStatementFromTokenContainer(pTokenContainer, pOffsetDatum);
			if (pAst != 0)
			{
				NumberDuck::Secret::AST* __4200063409 = pAst;
				pAst = 0;
				return __4200063409;
			}
			pAst = TryCreateExpression(pTokenContainer, pOffsetDatum);
			if (pAst != 0)
			{
				NumberDuck::Secret::AST* __4200063409 = pAst;
				pAst = 0;
				return __4200063409;
			}
			{
				if (pAst) delete pAst;
				return 0;
			}
		}

		AST* AST::CreateStatementFromTokenContainer(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
		{
			AST* pAst = 0;
			pAst = ReturnStmt::TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != 0)
			{
				NumberDuck::Secret::AST* __4200063409 = pAst;
				pAst = 0;
				return __4200063409;
			}
			pAst = BreakStmt::TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != 0)
			{
				NumberDuck::Secret::AST* __4200063409 = pAst;
				pAst = 0;
				return __4200063409;
			}
			pAst = ContinueStmt::TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != 0)
			{
				NumberDuck::Secret::AST* __4200063409 = pAst;
				pAst = 0;
				return __4200063409;
			}
			pAst = Scope::TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != 0)
			{
				NumberDuck::Secret::AST* __4200063409 = pAst;
				pAst = 0;
				return __4200063409;
			}
			pAst = VarDecl::TryCreate(pTokenContainer, pOffsetDatum, false);
			if (pAst != 0)
			{
				NumberDuck::Secret::AST* __4200063409 = pAst;
				pAst = 0;
				return __4200063409;
			}
			pAst = EnumDecl::TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != 0)
			{
				NumberDuck::Secret::AST* __4200063409 = pAst;
				pAst = 0;
				return __4200063409;
			}
			pAst = DeleteStmt::TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != 0)
			{
				NumberDuck::Secret::AST* __4200063409 = pAst;
				pAst = 0;
				return __4200063409;
			}
			pAst = IfStmt::TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != 0)
			{
				NumberDuck::Secret::AST* __4200063409 = pAst;
				pAst = 0;
				return __4200063409;
			}
			pAst = ForStmt::TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != 0)
			{
				NumberDuck::Secret::AST* __4200063409 = pAst;
				pAst = 0;
				return __4200063409;
			}
			pAst = WhileStmt::TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != 0)
			{
				NumberDuck::Secret::AST* __4200063409 = pAst;
				pAst = 0;
				return __4200063409;
			}
			pAst = SwitchStmt::TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != 0)
			{
				NumberDuck::Secret::AST* __4200063409 = pAst;
				pAst = 0;
				return __4200063409;
			}
			pAst = ExpressionStmt::TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != 0)
			{
				NumberDuck::Secret::AST* __4200063409 = pAst;
				pAst = 0;
				return __4200063409;
			}
			{
				if (pAst) delete pAst;
				return 0;
			}
		}

		AST* AST::TryCreateInnerExpression(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
		{
			AST* pAst = 0;
			pAst = NumberExpr::TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != 0)
			{
				NumberDuck::Secret::AST* __4200063409 = pAst;
				pAst = 0;
				return __4200063409;
			}
			pAst = BoolExpr::TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != 0)
			{
				NumberDuck::Secret::AST* __4200063409 = pAst;
				pAst = 0;
				return __4200063409;
			}
			pAst = CharExpr::TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != 0)
			{
				NumberDuck::Secret::AST* __4200063409 = pAst;
				pAst = 0;
				return __4200063409;
			}
			pAst = StringExpr::TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != 0)
			{
				NumberDuck::Secret::AST* __4200063409 = pAst;
				pAst = 0;
				return __4200063409;
			}
			pAst = NullExpr::TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != 0)
			{
				NumberDuck::Secret::AST* __4200063409 = pAst;
				pAst = 0;
				return __4200063409;
			}
			pAst = ThisExpr::TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != 0)
			{
				NumberDuck::Secret::AST* __4200063409 = pAst;
				pAst = 0;
				return __4200063409;
			}
			pAst = BaseExpr::TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != 0)
			{
				NumberDuck::Secret::AST* __4200063409 = pAst;
				pAst = 0;
				return __4200063409;
			}
			pAst = FunctionCall::TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != 0)
			{
				NumberDuck::Secret::AST* __4200063409 = pAst;
				pAst = 0;
				return __4200063409;
			}
			pAst = New::TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != 0)
			{
				NumberDuck::Secret::AST* __4200063409 = pAst;
				pAst = 0;
				return __4200063409;
			}
			pAst = CastExpr::TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != 0)
			{
				NumberDuck::Secret::AST* __4200063409 = pAst;
				pAst = 0;
				return __4200063409;
			}
			pAst = Unary::TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != 0)
			{
				NumberDuck::Secret::AST* __4200063409 = pAst;
				pAst = 0;
				return __4200063409;
			}
			pAst = Paren::TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != 0)
			{
				NumberDuck::Secret::AST* __4200063409 = pAst;
				pAst = 0;
				return __4200063409;
			}
			pAst = ArrayLookup::TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != 0)
			{
				NumberDuck::Secret::AST* __4200063409 = pAst;
				pAst = 0;
				return __4200063409;
			}
			pAst = StaticArray::TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != 0)
			{
				NumberDuck::Secret::AST* __4200063409 = pAst;
				pAst = 0;
				return __4200063409;
			}
			pAst = OwnExpr::TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != 0)
			{
				NumberDuck::Secret::AST* __4200063409 = pAst;
				pAst = 0;
				return __4200063409;
			}
			pAst = DisownExpr::TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != 0)
			{
				NumberDuck::Secret::AST* __4200063409 = pAst;
				pAst = 0;
				return __4200063409;
			}
			pAst = Identifier::TryCreate(pTokenContainer, pOffsetDatum);
			if (pAst != 0)
			{
				NumberDuck::Secret::AST* __4200063409 = pAst;
				pAst = 0;
				return __4200063409;
			}
			{
				if (pAst) delete pAst;
				return 0;
			}
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
						{
							NumberDuck::Secret::AST* __2461073728 = pLeft;
							pLeft = 0;
							{
								if (pTempOffset) delete pTempOffset;
								if (pLeft) delete pLeft;
								return OperatorExpr::Create(pOperatorToken, __2461073728, 0);
							}
						}
					}
					if (pOperatorToken->m_eType == Token::Type::TOKEN_QUESTION_MARK)
					{
						pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
						pOffsetDatum->Set(pTempOffset);
						{
							NumberDuck::Secret::AST* __2461073728 = pLeft;
							pLeft = 0;
							{
								if (pTempOffset) delete pTempOffset;
								if (pLeft) delete pLeft;
								return TrinaryExpr::Create(__2461073728, pTokenContainer, pOffsetDatum);
							}
						}
					}
					if (pOperatorToken->m_eType == Token::Type::TOKEN_AND || pOperatorToken->m_eType == Token::Type::TOKEN_ANGLE_BRACKET_LEFT || pOperatorToken->m_eType == Token::Type::TOKEN_ANGLE_BRACKET_LEFT_EQUALS || pOperatorToken->m_eType == Token::Type::TOKEN_ANGLE_BRACKET_RIGHT || pOperatorToken->m_eType == Token::Type::TOKEN_ANGLE_BRACKET_RIGHT_EQUALS || pOperatorToken->m_eType == Token::Type::TOKEN_BITWISE_AND || pOperatorToken->m_eType == Token::Type::TOKEN_BITWISE_OR || pOperatorToken->m_eType == Token::Type::TOKEN_CARET || pOperatorToken->m_eType == Token::Type::TOKEN_DIVIDE || pOperatorToken->m_eType == Token::Type::TOKEN_DOT || pOperatorToken->m_eType == Token::Type::TOKEN_DOUBLE_ANGLE_BRACKET_LEFT || pOperatorToken->m_eType == Token::Type::TOKEN_DOUBLE_ANGLE_BRACKET_RIGHT || pOperatorToken->m_eType == Token::Type::TOKEN_DOUBLE_COLON || pOperatorToken->m_eType == Token::Type::TOKEN_DOUBLE_EQUALS || pOperatorToken->m_eType == Token::Type::TOKEN_EQUALS || pOperatorToken->m_eType == Token::Type::TOKEN_MINUS || pOperatorToken->m_eType == Token::Type::TOKEN_MINUS_EQUALS || pOperatorToken->m_eType == Token::Type::TOKEN_NOT_EQUALS || pOperatorToken->m_eType == Token::Type::TOKEN_OR || pOperatorToken->m_eType == Token::Type::TOKEN_PLUS || pOperatorToken->m_eType == Token::Type::TOKEN_PLUS_EQUALS || pOperatorToken->m_eType == Token::Type::TOKEN_STAR || pOperatorToken->m_eType == Token::Type::TOKEN_MODULUS)
					{
						pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
						AST* pRight = TryCreateExpression(pTokenContainer, pTempOffset);
						if (pRight != 0)
						{
							pOffsetDatum->Set(pTempOffset);
							{
								NumberDuck::Secret::AST* __2461073728 = pLeft;
								pLeft = 0;
								{
									NumberDuck::Secret::AST* __1625873296 = pRight;
									pRight = 0;
									{
										if (pRight) delete pRight;
										if (pTempOffset) delete pTempOffset;
										if (pLeft) delete pLeft;
										return OperatorExpr::Create(pOperatorToken, __2461073728, __1625873296);
									}
								}
							}
						}
						if (pRight) delete pRight;
					}
				}
				pOffsetDatum->Set(pTempOffset);
				{
					NumberDuck::Secret::AST* __2461073728 = pLeft;
					pLeft = 0;
					{
						if (pTempOffset) delete pTempOffset;
						return __2461073728;
					}
				}
			}
			{
				if (pTempOffset) delete pTempOffset;
				if (pLeft) delete pLeft;
				return 0;
			}
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
			{
				NumberDuck::Secret::AST* __1962663712 = m_pFirstChild;
				m_pFirstChild = 0;
				pAst->m_pNextSibling = __1962663712;
			}
			m_pFirstChild = pAst;
			pAst->m_pNextSibling->m_pPrevSibling = m_pFirstChild;
		}

		AST* AST::RemoveChild(AST* pChild)
		{
			if (m_pFirstChild == pChild)
			{
				AST* pOwnedChild = 0;
				{
					NumberDuck::Secret::AST* __1962663712 = m_pFirstChild;
					m_pFirstChild = 0;
					pOwnedChild = __1962663712;
				}
				if (m_pLastChild == pOwnedChild)
					m_pLastChild = 0;
				else
				{
					NumberDuck::Secret::AST* __585396278 = pOwnedChild->m_pNextSibling;
					pOwnedChild->m_pNextSibling = 0;
					m_pFirstChild = __585396278;
				}
				pOwnedChild->m_pParent = 0;
				{
					NumberDuck::Secret::AST* __3216022957 = pOwnedChild;
					pOwnedChild = 0;
					return __3216022957;
				}
			}
			else
			{
				AST* pFindChild = m_pFirstChild;
				while (pFindChild != 0)
				{
					if (pFindChild->m_pNextSibling == pChild)
					{
						AST* pOwnedChild = 0;
						{
							NumberDuck::Secret::AST* __4143530587 = pFindChild->m_pNextSibling;
							pFindChild->m_pNextSibling = 0;
							pOwnedChild = __4143530587;
						}
						if (m_pLastChild == pOwnedChild)
							m_pLastChild = pFindChild;
						else
						{
							NumberDuck::Secret::AST* __585396278 = pOwnedChild->m_pNextSibling;
							pOwnedChild->m_pNextSibling = 0;
							pFindChild->m_pNextSibling = __585396278;
						}
						pOwnedChild->m_pParent = 0;
						{
							NumberDuck::Secret::AST* __3216022957 = pOwnedChild;
							pOwnedChild = 0;
							return __3216022957;
						}
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
			{
				if (sTemp) delete sTemp;
				return 0;
			}
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
}

