#pragma once

#include "AST/AST.hpp"

namespace NumbatLogic
{
	class InternalString;
	class AST;
	class Token;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/OutputBuilder.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/OutputBuilder.nll"
	class OutputBuilder
	{
		public: InternalString* m_sOut;
		protected: int m_nLastOutOffset;
		protected: int m_nLastLine;
		protected: InternalString* m_sLastFileName;
#line 10 "/home/cliffya/git/Lang/Source/Core/OutputBuilder.nll"
		public: OutputBuilder();
#line 18 "/home/cliffya/git/Lang/Source/Core/OutputBuilder.nll"
		public: void UpdateSourceLocation(AST::Language eLanguage, Token* pToken);
#line 3 "/home/cliffya/git/Lang/Source/Core/OutputBuilder.nll"
		public: virtual ~OutputBuilder();
	};
}

