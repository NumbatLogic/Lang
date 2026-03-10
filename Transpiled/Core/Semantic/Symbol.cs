#line 1 "../../../Source/Core/Semantic/Symbol.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/Semantic/Symbol.nll"
	class Symbol
	{
#line 5 "../../../Source/Core/Semantic/Symbol.nll"
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

#line 19 "../../../Source/Core/Semantic/Symbol.nll"
		public Kind m_eKind;
#line 22 "../../../Source/Core/Semantic/Symbol.nll"
		public string m_sShortName;
#line 25 "../../../Source/Core/Semantic/Symbol.nll"
		public string m_sQualifiedName;
#line 28 "../../../Source/Core/Semantic/Symbol.nll"
		public AST m_pDeclAST;
#line 31 "../../../Source/Core/Semantic/Symbol.nll"
		public SymbolScope m_pScope;
#line 33 "../../../Source/Core/Semantic/Symbol.nll"
		public Symbol()
		{
#line 35 "../../../Source/Core/Semantic/Symbol.nll"
			m_eKind = Kind.VAR;
#line 36 "../../../Source/Core/Semantic/Symbol.nll"
			m_sShortName = "";
#line 37 "../../../Source/Core/Semantic/Symbol.nll"
			m_sQualifiedName = "";
#line 38 "../../../Source/Core/Semantic/Symbol.nll"
			m_pDeclAST = null;
#line 39 "../../../Source/Core/Semantic/Symbol.nll"
			m_pScope = null;
		}

	}
}

