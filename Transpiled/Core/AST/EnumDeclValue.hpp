#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class Token;
	class EnumDeclValue;
	class TokenContainer;
	class OffsetDatum;
	class OutputBuilder;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/EnumDeclValue.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/EnumDeclValue.nll"
	class EnumDeclValue : public AST
	{
		public: AST* m_pForceValue;
#line 7 "/home/cliffya/git/Lang/Source/Core/AST/EnumDeclValue.nll"
		public: EnumDeclValue(Token* pFirstToken);
#line 13 "/home/cliffya/git/Lang/Source/Core/AST/EnumDeclValue.nll"
		public: static EnumDeclValue* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 43 "/home/cliffya/git/Lang/Source/Core/AST/EnumDeclValue.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/EnumDeclValue.nll"
		public: virtual ~EnumDeclValue();
	};
}

