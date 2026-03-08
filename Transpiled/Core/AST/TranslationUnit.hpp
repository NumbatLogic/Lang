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
		public: ClassDecl* m_pClassDecl;
		public: AST::OutputFile m_eOutputFile;
		public: bool m_bForwardReference;
		public: ClassDeclReference();
	};
#line 10 "../../../Source/Core/AST/TranslationUnit.nll"
	class ReferenceNode
	{
		public: InternalString* m_sName;
		public: OwnedVector<ReferenceNode*>* m_pChildNodeVector;
		public: Vector<ClassDeclReference*>* m_pChildClassVector;
		public: ReferenceNode(const char* sxName);
		public: ReferenceNode* GetOrCreateChildNode(const char* sxName);
		public: void Stringify(AST::Language eLanguage, AST::OutputFile eOutputFile, int nDepth, OutputBuilder* out);
		public: virtual ~ReferenceNode();
	};
#line 83 "../../../Source/Core/AST/TranslationUnit.nll"
	class TranslationUnit : public AST
	{
		public: InternalString* m_sInFile;
		public: TokenContainer* m_pTokenContainer;
		public: OwnedVector<ClassDeclReference*>* m_pClassDeclReferenceVector;
		public: TranslationUnit(const char* sInFile);
		public: static TranslationUnit* Create(const char* sInFile, OwnedVector<InternalString*>* sDefineVector);
		public: virtual void AddClassDeclReference(ClassDecl* pClassDecl, OutputFile eOutputFile, bool bForwardReference);
		public: static void ConvertFilePath(Language eLanguage, OutputFile eOutputFile, InternalString* sPath);
		public: InternalString* RetargetRelativePath(Language eLanguage, OutputFile eOutputFile, const char* sxFrom, const char* sxTo);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* out);
		public: virtual ~TranslationUnit();
	};
}

