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
	class InternalString;
}
namespace NumbatLogic
{
	class ClassDecl : public AST
	{
		public: Token* m_pNameToken;
		public: TypeRef* m_pBaseTypeRef;
		public: OwnedVector<GenericTypeDecl*>* m_pGenericTypeDeclVector;
		public: NamespaceNode* m_pNamespaceNode;
		protected: ClassDecl* m_pBaseClassDecl;
		protected: Token* m_pAccessLevelToken;
		protected: Token* m_pTypeToken;
		protected: Token* m_pConstructorAccessLevelToken;
		protected: Token* m_pConstructorTypeToken;
		public: ClassDecl();
		public: static ClassDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, AST* pParent);
		public: virtual void PreValidate(Validator* pValidator, OperatorExpr* pParent);
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
		public: virtual ClassDecl* FindClassDecl(const char* sTypeName, AST* pCallingChild);
		public: virtual AST* FindByName(const char* sxName, AST* pCallingChild);
		public: ClassDecl* GetBaseClassDecl();
		public: void StringifyTemplateThing(Language eLanguage, OutputFile eOutputFile, InternalString* sOut);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
		public: virtual ~ClassDecl();
	};
}

