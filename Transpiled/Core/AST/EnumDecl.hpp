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
	class OutputBuilder;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/EnumDecl.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/EnumDecl.nll"
	class EnumDecl : public AST
	{
		public: Token* m_pNameToken;
		public: Vector<EnumDeclValue*>* m_pEnumDeclValueVector;
#line 8 "/home/cliffya/git/Lang/Source/Core/AST/EnumDecl.nll"
		public: EnumDecl();
#line 13 "/home/cliffya/git/Lang/Source/Core/AST/EnumDecl.nll"
		public: static EnumDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 79 "/home/cliffya/git/Lang/Source/Core/AST/EnumDecl.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/EnumDecl.nll"
		public: virtual ~EnumDecl();
	};
}

