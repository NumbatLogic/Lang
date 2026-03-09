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
#line 4 "../../../Source/Core/OutputBuilder.nll"
	class OutputBuilder
	{
#line 6 "../../../Source/Core/OutputBuilder.nll"
		public: InternalString* m_sOut;
#line 8 "../../../Source/Core/OutputBuilder.nll"
		public: OutputBuilder();
#line 13 "../../../Source/Core/OutputBuilder.nll"
		public: void UpdateSourceLocation(AST::Language eLanguage, Token* pToken);
#line 4 "../../../Source/Core/OutputBuilder.nll"
		public: virtual ~OutputBuilder();
	};
}

