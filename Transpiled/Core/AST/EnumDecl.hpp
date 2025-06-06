#pragma once

#include "AST.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"

namespace NumberDuck
{
	namespace Secret
	{
		class Token;
		class EnumDeclValue;
		class EnumDecl;
		class TokenContainer;
		class OffsetDatum;
		class AST;
		class InternalString;
	}
}
namespace NumberDuck
{
	namespace Secret
	{
		class EnumDecl : public AST
		{
			public: Token* m_pNameToken;
			public: Vector<EnumDeclValue*>* m_pEnumDeclValueVector;
			public: EnumDecl();
			public: static EnumDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
			public: virtual AST* FindByName(const char* sxName, AST* pCallingChild);
			public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
			public: virtual ~EnumDecl();
		};
	}
}

