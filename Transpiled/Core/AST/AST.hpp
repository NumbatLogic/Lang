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
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
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

#line 59 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
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

#line 69 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		public: enum OutputFile
		{
			SOURCE,
			HEADER,
		};

#line 74 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		public: Type m_eType;
		public: Token* m_pFirstToken;
#line 77 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		public: AST* m_pParent;
		public: AST* m_pFirstChild;
		public: AST* m_pLastChild;
		public: AST* m_pPrevSibling;
		public: AST* m_pNextSibling;
#line 84 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		public: SymbolScope* m_pSymbolScope;
#line 86 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		public: bool m_bCanDescend;
#line 88 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		public: ValueType* m_pValueType;
#line 90 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		public: bool m_bStatement;
#line 93 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		public: bool m_bSkipOutput;
#line 95 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		public: AST();
#line 101 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		public: virtual ~AST();
#line 105 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		public: static AST* CreateFromTokenContainer(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 132 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		public: static AST* CreateStatementFromTokenContainer(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 187 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		protected: static AST* TryCreateInnerExpression(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 270 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		public: static AST* TryCreateExpression(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 316 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		public: virtual void PreValidate(Validator* pValidator, OperatorExpr* pParent);
#line 328 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 340 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		public: void AddChild(AST* pAst);
#line 357 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		public: void AddChildFront(AST* pAst);
#line 371 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		public: void AddChildBefore(AST* pAst, AST* pBefore);
#line 392 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		public: AST* RemoveChild(AST* pChild);
#line 428 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		public: virtual void AddClassDeclReference(ClassDecl* pClassDecl, OutputFile eOutputFile, bool bForwardReference);
#line 435 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		public: Project* GetProject();
#line 443 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 448 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		public: virtual AST* BaseClone();
#line 457 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		public: AST* GetParentStatement();
#line 470 "/home/cliffya/git/Lang/Source/Core/AST/AST.nll"
		public: virtual void StringifyType(InternalString* sOut);
	};
}

