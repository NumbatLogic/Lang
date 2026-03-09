#pragma once

namespace NumbatLogic
{
	class Token;
	class AST;
	class SymbolScope;
	class ValueType;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class ClassDecl;
	class Project;
	class OutputBuilder;
	class InternalString;
}
#line 1 "../../../Source/Core/AST/AST.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/AST.nll"
	class AST
	{
#line 6 "../../../Source/Core/AST/AST.nll"
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
			AST_REF_EXPR,
			AST_RETURN_STMT,
			AST_SCOPE,
			AST_STATIC_ARRAY,
			AST_STRING,
			AST_SWITCH_STMT,
			AST_TOR_DECL,
			AST_TRANSLATION_UNIT,
			AST_TTHASH_EXP,
			AST_TYPE_REF,
			AST_UNARY,
			AST_VAR_DECL_DESCOPE,
			AST_VAR_DECL,
			AST_WHILE_STMT,
			AST_PROJECT,
			BASE_EXPR,
			DELEGATE_DECL,
			ENUM_DECL_VALUE,
			MEMBER_VARS_SET_DEFAULT_STMT,
			NAMESPACE_DECL,
			NULL_EXPR,
			THIS_EXPR,
		};

#line 60 "../../../Source/Core/AST/AST.nll"
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

#line 70 "../../../Source/Core/AST/AST.nll"
		public: enum OutputFile
		{
			SOURCE,
			HEADER,
		};

#line 75 "../../../Source/Core/AST/AST.nll"
		public: Type m_eType;
#line 76 "../../../Source/Core/AST/AST.nll"
		public: Token* m_pFirstToken;
#line 78 "../../../Source/Core/AST/AST.nll"
		public: AST* m_pParent;
#line 79 "../../../Source/Core/AST/AST.nll"
		public: AST* m_pFirstChild;
#line 80 "../../../Source/Core/AST/AST.nll"
		public: AST* m_pLastChild;
#line 81 "../../../Source/Core/AST/AST.nll"
		public: AST* m_pPrevSibling;
#line 82 "../../../Source/Core/AST/AST.nll"
		public: AST* m_pNextSibling;
#line 85 "../../../Source/Core/AST/AST.nll"
		public: SymbolScope* m_pSymbolScope;
#line 87 "../../../Source/Core/AST/AST.nll"
		public: bool m_bCanDescend;
#line 89 "../../../Source/Core/AST/AST.nll"
		public: ValueType* m_pValueType;
#line 91 "../../../Source/Core/AST/AST.nll"
		public: bool m_bStatement;
#line 94 "../../../Source/Core/AST/AST.nll"
		public: bool m_bSkipOutput;
#line 96 "../../../Source/Core/AST/AST.nll"
		public: AST();
#line 102 "../../../Source/Core/AST/AST.nll"
		public: virtual ~AST();
#line 106 "../../../Source/Core/AST/AST.nll"
		public: static AST* CreateFromTokenContainer(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 133 "../../../Source/Core/AST/AST.nll"
		public: static AST* CreateStatementFromTokenContainer(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 188 "../../../Source/Core/AST/AST.nll"
		protected: static AST* TryCreateInnerExpression(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 271 "../../../Source/Core/AST/AST.nll"
		public: static AST* TryCreateExpression(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 317 "../../../Source/Core/AST/AST.nll"
		public: virtual void PreValidate(Validator* pValidator, OperatorExpr* pParent);
#line 329 "../../../Source/Core/AST/AST.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 341 "../../../Source/Core/AST/AST.nll"
		public: void AddChild(AST* pAst);
#line 358 "../../../Source/Core/AST/AST.nll"
		public: void AddChildFront(AST* pAst);
#line 372 "../../../Source/Core/AST/AST.nll"
		public: void AddChildBefore(AST* pAst, AST* pBefore);
#line 393 "../../../Source/Core/AST/AST.nll"
		public: AST* RemoveChild(AST* pChild);
#line 429 "../../../Source/Core/AST/AST.nll"
		public: virtual void AddClassDeclReference(ClassDecl* pClassDecl, OutputFile eOutputFile, bool bForwardReference);
#line 436 "../../../Source/Core/AST/AST.nll"
		public: Project* GetProject();
#line 444 "../../../Source/Core/AST/AST.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 449 "../../../Source/Core/AST/AST.nll"
		public: virtual AST* BaseClone();
#line 458 "../../../Source/Core/AST/AST.nll"
		public: AST* GetParentStatement();
#line 471 "../../../Source/Core/AST/AST.nll"
		public: virtual void StringifyType(InternalString* sOut);
	};
}

