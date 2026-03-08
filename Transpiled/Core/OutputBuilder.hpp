#pragma once

#include "AST/AST.hpp"

namespace NumbatLogic
{
	class InternalString;
	class AST;
	class Token;
}
#line 1 "../../../Source/Core/OutputBuilder.nll"
namespace NumbatLogic
{
	class OutputBuilder
	{
		public: InternalString* m_sOut;
		public: OutputBuilder();
		public: void OutputSourceLocation(AST::Language eLanguage, Token* pToken);
		public: virtual ~OutputBuilder();
	};
}

