#pragma once

#include "AST.hpp"
#include "../../../../LangShared/Transpiled/Vector/OwnedVector.hpp"
#include "GenericTypeDecl.hpp"

namespace NumbatLogic
{
	class Token;
	class TypeRef;
	template <class T>
	class OwnedVector;
	class GenericTypeDecl;
	class NamespaceNode;
	class ClassDecl;
	class TokenContainer;
	class OffsetDatum;
	class AST;
	class Validator;
	class OperatorExpr;
	class AccessLevel;
	class ParamDecl;
	class Scope;
	class TorDecl;
	class Resolver;
	class Symbol;
	class InternalString;
	class OutputBuilder;
}
#line 0 "../../../Source/Core/AST/ClassDecl.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/ClassDecl.nll"
	class ClassDecl : public AST
	{
#line 5 "../../../Source/Core/AST/ClassDecl.nll"
		public: Token* m_pNameToken;
#line 6 "../../../Source/Core/AST/ClassDecl.nll"
		public: bool m_bDisposable;
#line 7 "../../../Source/Core/AST/ClassDecl.nll"
		public: TypeRef* m_pBaseTypeRef;
#line 8 "../../../Source/Core/AST/ClassDecl.nll"
		public: OwnedVector<GenericTypeDecl*>* m_pGenericTypeDeclVector;
#line 9 "../../../Source/Core/AST/ClassDecl.nll"
		public: NamespaceNode* m_pNamespaceNode;
#line 11 "../../../Source/Core/AST/ClassDecl.nll"
		protected: ClassDecl* m_pBaseClassDecl;
#line 13 "../../../Source/Core/AST/ClassDecl.nll"
		protected: Token* m_pAccessLevelToken;
#line 14 "../../../Source/Core/AST/ClassDecl.nll"
		protected: Token* m_pTypeToken;
#line 16 "../../../Source/Core/AST/ClassDecl.nll"
		protected: Token* m_pConstructorAccessLevelToken;
#line 17 "../../../Source/Core/AST/ClassDecl.nll"
		protected: Token* m_pConstructorTypeToken;
#line 19 "../../../Source/Core/AST/ClassDecl.nll"
		public: ClassDecl();
#line 28 "../../../Source/Core/AST/ClassDecl.nll"
		public: static ClassDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, AST* pParent);
#line 186 "../../../Source/Core/AST/ClassDecl.nll"
		public: virtual void PreValidate(Validator* pValidator, OperatorExpr* pParent);
#line 191 "../../../Source/Core/AST/ClassDecl.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 336 "../../../Source/Core/AST/ClassDecl.nll"
		public: ClassDecl* GetBaseClassDeclForScopeLookup(Resolver* pResolver);
#line 387 "../../../Source/Core/AST/ClassDecl.nll"
		public: ClassDecl* GetBaseClassDecl(Validator* pValidator);
#line 411 "../../../Source/Core/AST/ClassDecl.nll"
		public: void AppendFullyQualifiedName(InternalString* sOut);
#line 427 "../../../Source/Core/AST/ClassDecl.nll"
		public: void StringifyTemplateThing(Language eLanguage, OutputFile eOutputFile, OutputBuilder* pOutputBuilder);
#line 440 "../../../Source/Core/AST/ClassDecl.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 3 "../../../Source/Core/AST/ClassDecl.nll"
		public: virtual ~ClassDecl();
	};
}

