#pragma once

#include "AST.hpp"
#include "../../../../LangShared/Transpiled/Vector/OwnedVector.hpp"
#include "TranslationUnit.hpp"
#include "../../../../LangShared/Source/Vector/CPP/Vector.hpp"

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
	class FunctionDecl;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
	class ClassDeclReference
	{
		public: ClassDecl* m_pClassDecl;
		public: AST::OutputFile m_eOutputFile;
		public: bool m_bForwardReference;
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		public: ClassDeclReference();
	};
#line 10 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
	class ReferenceNode
	{
		public: InternalString* m_sName;
		public: OwnedVector<ReferenceNode*>* m_pChildNodeVector;
		public: Vector<ClassDeclReference*>* m_pChildClassVector;
#line 16 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		public: ReferenceNode(const char* sxName);
#line 23 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		public: ReferenceNode* GetOrCreateChildNode(const char* sxName);
#line 39 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		public: void Stringify(AST::Language eLanguage, AST::OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 10 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		public: virtual ~ReferenceNode();
	};
#line 83 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
	class TranslationUnit : public AST
	{
		public: InternalString* m_sInFile;
		public: TokenContainer* m_pTokenContainer;
		public: OwnedVector<ClassDeclReference*>* m_pClassDeclReferenceVector;
#line 89 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		public: TranslationUnit(const char* sInFile);
#line 99 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		public: static TranslationUnit* Create(const char* sInFile, OwnedVector<InternalString*>* sDefineVector);
#line 128 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		public: virtual void AddClassDeclReference(ClassDecl* pClassDecl, OutputFile eOutputFile, bool bForwardReference);
#line 158 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		public: static void ConvertFilePath(Language eLanguage, OutputFile eOutputFile, InternalString* sPath);
#line 240 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		public: InternalString* RetargetRelativePath(Language eLanguage, OutputFile eOutputFile, const char* sxFrom, const char* sxTo);
#line 299 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		protected: FunctionDecl* FindEntryPointFunction(AST* pNode);
#line 326 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 83 "/home/cliffya/git/Lang/Source/Core/AST/TranslationUnit.nll"
		public: virtual ~TranslationUnit();
	};
}

