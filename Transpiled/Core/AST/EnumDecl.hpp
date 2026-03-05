#pragma once

#include "AST.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
#include "EnumDeclValue.hpp"

namespace NumbatLogic
{
	class AST;
	class Token;
	template <class T>
	class Vector;
	class EnumDeclValue;
	class EnumDecl;
	class TokenContainer;
	class OffsetDatum;
	class InternalString;
}
namespace NumbatLogic
{
	class EnumDecl : public AST
	{
		public: Token* m_pNameToken;
		public: Vector<EnumDeclValue*>* m_pEnumDeclValueVector;
		public: EnumDecl();
		public: static EnumDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
		public: virtual ~EnumDecl();
	};
}

