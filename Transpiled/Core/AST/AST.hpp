#pragma once

namespace NumbatLogic
{
	class Token;
	class AST;
	class ValueType;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class ClassDecl;
	class InternalString;
}
namespace NumbatLogic
{
	class AST
	{
		public: enum Type
		{
			AST_ACCESS_LEVEL,
			AST_ARRAY_LOOKUP,
			AST_BOOL_EXPR,
			AST_BREAK_STMT,
			AST_CAST_EXP,
			AST_CHAR,
			AST_CLASS_DECL,
			AST_CONTINUE_STMT,
			AST_DELETE_STMT,
			AST_DISOWN_EXP,
			AST_ENUM_DECL,
			AST_EXPRESSION_STMT,
			AST_FOR_STMT,
			AST_FUNCTION_CALL,
			AST_FUNCTION_DECL,
			AST_GENERIC_TYPE_DECL,
			AST_IDENTIFIER,
			AST_IF_STMT,
			AST_MEMBER_CLASS_DECL,
			AST_MEMBER_ENUM_DECL,
			AST_MEMBER_FUNCTION_DECL,
			AST_MEMBER_VAR_DECL,
			AST_NEW_EXP,
			AST_NUMBER,
			AST_OPERATOR_EXPR,
			AST_OWN_EXP,
			AST_PARAM_CALL,
			AST_PARAM_DECL,
			AST_PAREN,
			AST_RETURN_STMT,
			AST_SCOPE,
			AST_STATIC_ARRAY,
			AST_STRING,
			AST_SWITCH_STMT,
			AST_TOR_DECL,
			AST_TRANSLATION_UNIT,
			AST_TYPE_REF,
			AST_UNARY,
			AST_VAR_DECL,
			AST_VAR_DECL_DESCOPE,
			AST_WHILE_STMT,
			BASE_EXPR,
			DELEGATE_DECL,
			ENUM_DECL_VALUE,
			MEMBER_VARS_SET_DEFAULT_STMT,
			NAMESPACE_DECL,
			NULL_EXPR,
			THIS_EXPR,
		};

		public: enum Language
		{
			NLL,
			NLL_DEF,
			CS,
			CPP,
			C,
			H,
			PHP,
		};

		public: enum OutputFile
		{
			SOURCE,
			HEADER,
		};

		public: Type m_eType;
		public: Token* m_pFirstToken;
		public: AST* m_pParent;
		public: AST* m_pFirstChild;
		public: AST* m_pLastChild;
		public: AST* m_pPrevSibling;
		public: AST* m_pNextSibling;
		public: bool m_bCanDescend;
		public: ValueType* m_pValueType;
		public: bool m_bStatement;
		public: bool m_bSkipOutput;
		public: AST();
		public: virtual ~AST();
		public: static AST* CreateFromTokenContainer(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
		public: static AST* CreateStatementFromTokenContainer(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
		protected: static AST* TryCreateInnerExpression(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
		public: static AST* TryCreateExpression(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
		public: virtual void PreValidate(Validator* pValidator, OperatorExpr* pParent);
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
		public: virtual ClassDecl* FindClassDecl(const char* sTypeName, AST* pCallingChild);
		public: virtual AST* FindByName(const char* sName, AST* pCallingChild);
		public: void AddChild(AST* pAst);
		public: void AddChildFront(AST* pAst);
		public: void AddChildBefore(AST* pAst, AST* pBefore);
		public: AST* RemoveChild(AST* pChild);
		public: virtual void AddClassDeclReference(ClassDecl* pClassDecl, OutputFile eOutputFile, bool bForwardReference);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
		public: virtual AST* BaseClone();
		public: AST* GetParentStatement();
		public: virtual void StringifyType(InternalString* sOut);
	};
}

