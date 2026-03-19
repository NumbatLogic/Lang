#pragma once

#include "AST.hpp"
#include "../../../../LangShared/Transpiled/Vector/OwnedVector.hpp"
#include "GenericTypeDecl.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
#include "DecoratorCall.hpp"

namespace NumbatLogic
{
	class Token;
	class TypeRef;
	template <class T>
	class OwnedVector;
	class GenericTypeDecl;
	template <class T>
	class Vector;
	class DecoratorCall;
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
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
	class ClassDecl : public AST
	{
		public: Token* m_pNameToken;
		public: bool m_bDisposable;
		public: TypeRef* m_pBaseTypeRef;
		public: OwnedVector<GenericTypeDecl*>* m_pGenericTypeDeclVector;
		public: Vector<DecoratorCall*>* m_pDecoratorCallVector;
		public: NamespaceNode* m_pNamespaceNode;
#line 12 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
		protected: ClassDecl* m_pBaseClassDecl;
#line 14 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
		protected: Token* m_pAccessLevelToken;
		protected: Token* m_pTypeToken;
#line 17 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
		protected: Token* m_pConstructorAccessLevelToken;
		protected: Token* m_pConstructorTypeToken;
#line 20 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
		public: ClassDecl();
#line 30 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
		public: static ClassDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, AST* pParent);
#line 207 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
		public: virtual void PreValidate(Validator* pValidator, OperatorExpr* pParent);
#line 212 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 357 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
		public: ClassDecl* GetBaseClassDeclForScopeLookup(Resolver* pResolver);
#line 408 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
		public: ClassDecl* GetBaseClassDecl(Validator* pValidator);
#line 432 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
		public: void AppendFullyQualifiedName(AST::Language eLanguage, InternalString* sOut);
#line 452 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
		public: void StringifyTemplateThing(Language eLanguage, OutputFile eOutputFile, OutputBuilder* pOutputBuilder);
#line 465 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
		public: virtual ~ClassDecl();
	};
}

