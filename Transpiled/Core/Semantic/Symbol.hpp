#pragma once

namespace NumbatLogic
{
	class AST;
	class SymbolScope;
}
#line 0 "../../../Source/Core/Semantic/Symbol.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/Semantic/Symbol.nll"
	class Symbol
	{
#line 5 "../../../Source/Core/Semantic/Symbol.nll"
		public: enum Kind
		{
			NAMESPACE,
			CLASS,
			ENUM,
			GENERIC_PARAM,
			FUNCTION,
			DELEGATE,
			METHOD,
			VAR,
			PARAM,
			ENUM_VALUE,
		};

#line 19 "../../../Source/Core/Semantic/Symbol.nll"
		public: Kind m_eKind;
#line 22 "../../../Source/Core/Semantic/Symbol.nll"
		public: const char* m_sShortName;
#line 25 "../../../Source/Core/Semantic/Symbol.nll"
		public: const char* m_sQualifiedName;
#line 28 "../../../Source/Core/Semantic/Symbol.nll"
		public: AST* m_pDeclAST;
#line 31 "../../../Source/Core/Semantic/Symbol.nll"
		public: SymbolScope* m_pScope;
#line 33 "../../../Source/Core/Semantic/Symbol.nll"
		public: Symbol();
	};
}

