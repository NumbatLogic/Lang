#pragma once

#include "../../../LangShared/Vector/CPP/Vector.hpp"
#include "AST/VarDecl.hpp"
#include "../../../LangShared/Transpiled/Vector/OwnedVector.hpp"
#include "Validator.hpp"

namespace NumbatLogic
{
	class InternalString;
	class Scope;
	template <class T>
	class Vector;
	class VarDecl;
	class Project;
	template <class T>
	class OwnedVector;
	class ValidatorError;
	class ValidatorScope;
	class NamespaceNode;
	class Resolver;
	class AST;
	class VarDeclDescope;
}
#line 0 "../../../Source/Core/Validator.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/Validator.nll"
	class ValidatorError
	{
#line 5 "../../../Source/Core/Validator.nll"
		public: InternalString* m_sError;
#line 6 "../../../Source/Core/Validator.nll"
		public: InternalString* m_sFile;
#line 7 "../../../Source/Core/Validator.nll"
		public: int m_nLine;
#line 8 "../../../Source/Core/Validator.nll"
		public: int m_nColumn;
#line 3 "../../../Source/Core/Validator.nll"
		public: ValidatorError();
#line 3 "../../../Source/Core/Validator.nll"
		public: virtual ~ValidatorError();
	};
#line 11 "../../../Source/Core/Validator.nll"
	class ValidatorScope
	{
#line 13 "../../../Source/Core/Validator.nll"
		public: Scope* m_pScope;
#line 14 "../../../Source/Core/Validator.nll"
		public: Vector<VarDecl*>* m_pVarDeclVector;
#line 16 "../../../Source/Core/Validator.nll"
		public: ValidatorScope(Scope* pScope);
#line 11 "../../../Source/Core/Validator.nll"
		public: virtual ~ValidatorScope();
	};
#line 23 "../../../Source/Core/Validator.nll"
	class Validator
	{
#line 25 "../../../Source/Core/Validator.nll"
		protected: Project* m_pProject;
#line 26 "../../../Source/Core/Validator.nll"
		protected: OwnedVector<ValidatorError*>* m_pValidatorErrorVector;
#line 27 "../../../Source/Core/Validator.nll"
		protected: OwnedVector<ValidatorScope*>* m_pValidatorScopeVector;
#line 29 "../../../Source/Core/Validator.nll"
		public: NamespaceNode* m_pCurrentNamespaceNode;
#line 32 "../../../Source/Core/Validator.nll"
		public: Resolver* m_pResolver;
#line 34 "../../../Source/Core/Validator.nll"
		public: Validator(Project* pProject);
#line 44 "../../../Source/Core/Validator.nll"
		protected: void PreparseNamespaces(NamespaceNode* pCurrentNode, AST* pAST);
#line 59 "../../../Source/Core/Validator.nll"
		public: bool Validate();
#line 113 "../../../Source/Core/Validator.nll"
		public: void AddError(const char* sError, InternalString* sFile, int nLine, int nColumn);
#line 127 "../../../Source/Core/Validator.nll"
		public: void ValidateSubtree(AST* pRoot);
#line 133 "../../../Source/Core/Validator.nll"
		public: void BeginScope(Scope* pScope);
#line 139 "../../../Source/Core/Validator.nll"
		public: void AddVarDecl(VarDecl* pVarDecl);
#line 153 "../../../Source/Core/Validator.nll"
		public: void EndScope(Scope* pScope);
#line 180 "../../../Source/Core/Validator.nll"
		public: void InjectCleanup(AST* pBreakOrContinueOrReturn);
#line 239 "../../../Source/Core/Validator.nll"
		public: void BeginNamespace(const char* sxName);
#line 245 "../../../Source/Core/Validator.nll"
		public: void EndNamespace(const char* sxName);
#line 23 "../../../Source/Core/Validator.nll"
		public: virtual ~Validator();
	};
}

