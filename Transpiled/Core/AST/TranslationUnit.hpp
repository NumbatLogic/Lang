#pragma once

#include "AST.hpp"
#include "../../../../LangShared/Transpiled/Vector/OwnedVector.hpp"
#include "TranslationUnit.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"

namespace NumbatLogic
{
	class ClassDecl;
	class InternalString;
	template <class T>
	class OwnedVector;
	class ReferenceNode;
	template <class T>
	class Vector;
	class ClassDeclReference;
	class OutputBuilder;
	class TokenContainer;
	class TranslationUnit;
	class AST;
}
#line 0 "../../../Source/Core/AST/TranslationUnit.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/TranslationUnit.nll"
	class ClassDeclReference
	{
#line 5 "../../../Source/Core/AST/TranslationUnit.nll"
		public: ClassDecl* m_pClassDecl;
#line 6 "../../../Source/Core/AST/TranslationUnit.nll"
		public: AST::OutputFile m_eOutputFile;
#line 7 "../../../Source/Core/AST/TranslationUnit.nll"
		public: bool m_bForwardReference;
#line 3 "../../../Source/Core/AST/TranslationUnit.nll"
		public: ClassDeclReference();
	};
#line 10 "../../../Source/Core/AST/TranslationUnit.nll"
	class ReferenceNode
	{
#line 12 "../../../Source/Core/AST/TranslationUnit.nll"
		public: InternalString* m_sName;
#line 13 "../../../Source/Core/AST/TranslationUnit.nll"
		public: OwnedVector<ReferenceNode*>* m_pChildNodeVector;
#line 14 "../../../Source/Core/AST/TranslationUnit.nll"
		public: Vector<ClassDeclReference*>* m_pChildClassVector;
#line 16 "../../../Source/Core/AST/TranslationUnit.nll"
		public: ReferenceNode(const char* sxName);
#line 23 "../../../Source/Core/AST/TranslationUnit.nll"
		public: ReferenceNode* GetOrCreateChildNode(const char* sxName);
#line 39 "../../../Source/Core/AST/TranslationUnit.nll"
		public: void Stringify(AST::Language eLanguage, AST::OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 10 "../../../Source/Core/AST/TranslationUnit.nll"
		public: virtual ~ReferenceNode();
	};
#line 83 "../../../Source/Core/AST/TranslationUnit.nll"
	class TranslationUnit : public AST
	{
#line 85 "../../../Source/Core/AST/TranslationUnit.nll"
		public: InternalString* m_sInFile;
#line 86 "../../../Source/Core/AST/TranslationUnit.nll"
		public: TokenContainer* m_pTokenContainer;
#line 87 "../../../Source/Core/AST/TranslationUnit.nll"
		public: OwnedVector<ClassDeclReference*>* m_pClassDeclReferenceVector;
#line 89 "../../../Source/Core/AST/TranslationUnit.nll"
		public: TranslationUnit(const char* sInFile);
#line 99 "../../../Source/Core/AST/TranslationUnit.nll"
		public: static TranslationUnit* Create(const char* sInFile, OwnedVector<InternalString*>* sDefineVector);
#line 124 "../../../Source/Core/AST/TranslationUnit.nll"
		public: virtual void AddClassDeclReference(ClassDecl* pClassDecl, OutputFile eOutputFile, bool bForwardReference);
#line 154 "../../../Source/Core/AST/TranslationUnit.nll"
		public: static void ConvertFilePath(Language eLanguage, OutputFile eOutputFile, InternalString* sPath);
#line 237 "../../../Source/Core/AST/TranslationUnit.nll"
		public: InternalString* RetargetRelativePath(Language eLanguage, OutputFile eOutputFile, const char* sxFrom, const char* sxTo);
#line 296 "../../../Source/Core/AST/TranslationUnit.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 83 "../../../Source/Core/AST/TranslationUnit.nll"
		public: virtual ~TranslationUnit();
	};
}

