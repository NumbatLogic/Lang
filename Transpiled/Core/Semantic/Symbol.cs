#line 1 "../../../Source/Core/Semantic/Symbol.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/Semantic/Symbol.nll"
	class Symbol
	{
#line 6 "../../../Source/Core/Semantic/Symbol.nll"
		public enum Kind
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
		}

#line 20 "../../../Source/Core/Semantic/Symbol.nll"
		public Kind m_eKind;
#line 23 "../../../Source/Core/Semantic/Symbol.nll"
		public string m_sShortName;
#line 26 "../../../Source/Core/Semantic/Symbol.nll"
		public string m_sQualifiedName;
#line 29 "../../../Source/Core/Semantic/Symbol.nll"
		public AST m_pDeclAST;
#line 32 "../../../Source/Core/Semantic/Symbol.nll"
		public SymbolScope m_pScope;
#line 34 "../../../Source/Core/Semantic/Symbol.nll"
		public Symbol()
		{
#line 36 "../../../Source/Core/Semantic/Symbol.nll"
			m_eKind = Kind.VAR;
#line 37 "../../../Source/Core/Semantic/Symbol.nll"
			m_sShortName = "";
#line 38 "../../../Source/Core/Semantic/Symbol.nll"
			m_sQualifiedName = "";
#line 39 "../../../Source/Core/Semantic/Symbol.nll"
			m_pDeclAST = null;
#line 40 "../../../Source/Core/Semantic/Symbol.nll"
			m_pScope = null;
		}

	}
}

