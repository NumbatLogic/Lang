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
#line 1 "../../../Source/Core/AST/ClassDecl.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/ClassDecl.nll"
	class ClassDecl : public AST
	{
#line 6 "../../../Source/Core/AST/ClassDecl.nll"
		public: Token* m_pNameToken;
#line 7 "../../../Source/Core/AST/ClassDecl.nll"
		public: bool m_bDisposable;
#line 8 "../../../Source/Core/AST/ClassDecl.nll"
		public: TypeRef* m_pBaseTypeRef;
#line 9 "../../../Source/Core/AST/ClassDecl.nll"
		public: OwnedVector<GenericTypeDecl*>* m_pGenericTypeDeclVector;
#line 10 "../../../Source/Core/AST/ClassDecl.nll"
		public: NamespaceNode* m_pNamespaceNode;
#line 12 "../../../Source/Core/AST/ClassDecl.nll"
		protected: ClassDecl* m_pBaseClassDecl;
#line 14 "../../../Source/Core/AST/ClassDecl.nll"
		protected: Token* m_pAccessLevelToken;
#line 15 "../../../Source/Core/AST/ClassDecl.nll"
		protected: Token* m_pTypeToken;
#line 17 "../../../Source/Core/AST/ClassDecl.nll"
		protected: Token* m_pConstructorAccessLevelToken;
#line 18 "../../../Source/Core/AST/ClassDecl.nll"
		protected: Token* m_pConstructorTypeToken;
#line 20 "../../../Source/Core/AST/ClassDecl.nll"
		public: ClassDecl();
#line 29 "../../../Source/Core/AST/ClassDecl.nll"
		public: static ClassDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, AST* pParent);
#line 187 "../../../Source/Core/AST/ClassDecl.nll"
		public: virtual void PreValidate(Validator* pValidator, OperatorExpr* pParent);
#line 192 "../../../Source/Core/AST/ClassDecl.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 337 "../../../Source/Core/AST/ClassDecl.nll"
		public: ClassDecl* GetBaseClassDeclForScopeLookup(Resolver* pResolver);
#line 388 "../../../Source/Core/AST/ClassDecl.nll"
		public: ClassDecl* GetBaseClassDecl(Validator* pValidator);
#line 412 "../../../Source/Core/AST/ClassDecl.nll"
		public: void AppendFullyQualifiedName(InternalString* sOut);
#line 428 "../../../Source/Core/AST/ClassDecl.nll"
		public: void StringifyTemplateThing(Language eLanguage, OutputFile eOutputFile, OutputBuilder* pOutputBuilder);
#line 441 "../../../Source/Core/AST/ClassDecl.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 4 "../../../Source/Core/AST/ClassDecl.nll"
		public: virtual ~ClassDecl();
	};
}

