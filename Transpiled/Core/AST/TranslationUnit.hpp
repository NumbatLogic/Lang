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
#line 1 "../../../Source/Core/AST/TranslationUnit.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/TranslationUnit.nll"
	class ClassDeclReference
	{
#line 6 "../../../Source/Core/AST/TranslationUnit.nll"
		public: ClassDecl* m_pClassDecl;
#line 7 "../../../Source/Core/AST/TranslationUnit.nll"
		public: AST::OutputFile m_eOutputFile;
#line 8 "../../../Source/Core/AST/TranslationUnit.nll"
		public: bool m_bForwardReference;
#line 4 "../../../Source/Core/AST/TranslationUnit.nll"
		public: ClassDeclReference();
	};
#line 11 "../../../Source/Core/AST/TranslationUnit.nll"
	class ReferenceNode
	{
#line 13 "../../../Source/Core/AST/TranslationUnit.nll"
		public: InternalString* m_sName;
#line 14 "../../../Source/Core/AST/TranslationUnit.nll"
		public: OwnedVector<ReferenceNode*>* m_pChildNodeVector;
#line 15 "../../../Source/Core/AST/TranslationUnit.nll"
		public: Vector<ClassDeclReference*>* m_pChildClassVector;
#line 17 "../../../Source/Core/AST/TranslationUnit.nll"
		public: ReferenceNode(const char* sxName);
#line 24 "../../../Source/Core/AST/TranslationUnit.nll"
		public: ReferenceNode* GetOrCreateChildNode(const char* sxName);
#line 40 "../../../Source/Core/AST/TranslationUnit.nll"
		public: void Stringify(AST::Language eLanguage, AST::OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 11 "../../../Source/Core/AST/TranslationUnit.nll"
		public: virtual ~ReferenceNode();
	};
#line 84 "../../../Source/Core/AST/TranslationUnit.nll"
	class TranslationUnit : public AST
	{
#line 86 "../../../Source/Core/AST/TranslationUnit.nll"
		public: InternalString* m_sInFile;
#line 87 "../../../Source/Core/AST/TranslationUnit.nll"
		public: TokenContainer* m_pTokenContainer;
#line 88 "../../../Source/Core/AST/TranslationUnit.nll"
		public: OwnedVector<ClassDeclReference*>* m_pClassDeclReferenceVector;
#line 90 "../../../Source/Core/AST/TranslationUnit.nll"
		public: TranslationUnit(const char* sInFile);
#line 100 "../../../Source/Core/AST/TranslationUnit.nll"
		public: static TranslationUnit* Create(const char* sInFile, OwnedVector<InternalString*>* sDefineVector);
#line 125 "../../../Source/Core/AST/TranslationUnit.nll"
		public: virtual void AddClassDeclReference(ClassDecl* pClassDecl, OutputFile eOutputFile, bool bForwardReference);
#line 155 "../../../Source/Core/AST/TranslationUnit.nll"
		public: static void ConvertFilePath(Language eLanguage, OutputFile eOutputFile, InternalString* sPath);
#line 238 "../../../Source/Core/AST/TranslationUnit.nll"
		public: InternalString* RetargetRelativePath(Language eLanguage, OutputFile eOutputFile, const char* sxFrom, const char* sxTo);
#line 297 "../../../Source/Core/AST/TranslationUnit.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 84 "../../../Source/Core/AST/TranslationUnit.nll"
		public: virtual ~TranslationUnit();
	};
}

