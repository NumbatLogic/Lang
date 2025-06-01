#pragma once

#include "AST.hpp"

namespace NumberDuck
{
	namespace Secret
	{
		class AccessLevel;
		class FunctionDecl;
		class DelegateDecl;
		class TokenContainer;
		class OffsetDatum;
		class ClassDecl;
		class AST;
		class InternalString;
	}
}
namespace NumberDuck
{
	namespace Secret
	{
		class DelegateDecl : public AST
		{
			public: AccessLevel* m_pAccessLevel;
			public: FunctionDecl* m_pFunctionDecl;
			public: DelegateDecl();
			public: static DelegateDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, ClassDecl* pParentClassDecl);
			public: virtual AST* FindByName(const char* sxName, AST* pCallingChild);
			public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
		};
	}
}

