#pragma once

#include "AST.hpp"
#include "../../LangShared/Vector/OwnedVector.hpp"
#include "TranslationUnit.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"

namespace NumbatLogic
{
	class ClassDecl;
	class AST;
	class InternalString;
	template <class T>
	class OwnedVector;
	class ReferenceNode;
	template <class T>
	class Vector;
	class ClassDeclReference;
	class TokenContainer;
	class TranslationUnit;
}
namespace NumbatLogic
{
	class ClassDeclReference
	{
		public: ClassDecl* m_pClassDecl;
		public: AST::OutputFile m_eOutputFile;
		public: bool m_bForwardReference;
		public: ClassDeclReference();
	};
	class ReferenceNode
	{
		public: InternalString* m_sName;
		public: OwnedVector<ReferenceNode*>* m_pChildNodeVector;
		public: Vector<ClassDeclReference*>* m_pChildClassVector;
		public: ReferenceNode(const char* sxName);
		public: ReferenceNode* GetOrCreateChildNode(const char* sxName);
		public: void Stringify(AST::Language eLanguage, AST::OutputFile eOutputFile, int nDepth, InternalString* sOut);
		public: virtual ~ReferenceNode();
	};
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
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
		public: virtual ~TranslationUnit();
	};
}

