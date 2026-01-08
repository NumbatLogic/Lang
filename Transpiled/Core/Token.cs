namespace NumbatLogic
{
	class Token
	{
		public enum Type
		{
			TOKEN_AND,
			TOKEN_ANGLE_BRACKET_LEFT_EQUALS,
			TOKEN_ANGLE_BRACKET_LEFT,
			TOKEN_ANGLE_BRACKET_RIGHT_EQUALS,
			TOKEN_ANGLE_BRACKET_RIGHT,
			TOKEN_BANG,
			TOKEN_BITWISE_AND,
			TOKEN_BITWISE_OR,
			TOKEN_CARET,
			TOKEN_CARRIGE_RETURN,
			TOKEN_CHAR_UNTERMINATED,
			TOKEN_CHAR,
			TOKEN_COLON,
			TOKEN_COMMA,
			TOKEN_CURLY_BRACE_LEFT,
			TOKEN_CURLY_BRACE_RIGHT,
			TOKEN_DIVIDE,
			TOKEN_DOT,
			TOKEN_DOUBLE_ANGLE_BRACKET_LEFT,
			TOKEN_DOUBLE_ANGLE_BRACKET_RIGHT,
			TOKEN_DOUBLE_COLON,
			TOKEN_DOUBLE_EQUALS,
			TOKEN_EQUALS,
			TOKEN_IDENTIFIER,
			TOKEN_KEYWORD_BASE,
			TOKEN_KEYWORD_BOOL,
			TOKEN_KEYWORD_BREAK,
			TOKEN_KEYWORD_CASE,
			TOKEN_KEYWORD_CAST,
			TOKEN_KEYWORD_CLASS,
			TOKEN_KEYWORD_CONST,
			TOKEN_KEYWORD_CONSTRUCT,
			TOKEN_KEYWORD_CONTINUE,
			TOKEN_KEYWORD_DEFAULT,
			TOKEN_KEYWORD_DELEGATE,
			TOKEN_KEYWORD_DELETE,
			TOKEN_KEYWORD_DESTRUCT,
			TOKEN_KEYWORD_DISOWN,
			TOKEN_KEYWORD_DISPOSABLE,
			TOKEN_KEYWORD_DOUBLE,
			TOKEN_KEYWORD_ELSE,
			TOKEN_KEYWORD_ENUM,
			TOKEN_KEYWORD_FALSE,
			TOKEN_KEYWORD_FLOAT,
			TOKEN_KEYWORD_FOR,
			TOKEN_KEYWORD_IF,
			TOKEN_KEYWORD_INT,
			TOKEN_KEYWORD_INT16,
			TOKEN_KEYWORD_INT32,
			TOKEN_KEYWORD_INT8,
			TOKEN_KEYWORD_NAMESPACE,
			TOKEN_KEYWORD_NEW,
			TOKEN_KEYWORD_NULL,
			TOKEN_KEYWORD_OVERRIDE,
			TOKEN_KEYWORD_OWN,
			TOKEN_KEYWORD_PRIVATE,
			TOKEN_KEYWORD_PUBLIC,
			TOKEN_KEYWORD_REF,
			TOKEN_KEYWORD_RETURN,
			TOKEN_KEYWORD_STATIC,
			TOKEN_KEYWORD_STRING,
			TOKEN_KEYWORD_SWITCH,
			TOKEN_KEYWORD_THIS,
			TOKEN_KEYWORD_TRUE,
			TOKEN_KEYWORD_TTHASH,
			TOKEN_KEYWORD_UINT,
			TOKEN_KEYWORD_UINT16,
			TOKEN_KEYWORD_UINT32,
			TOKEN_KEYWORD_UINT64,
			TOKEN_KEYWORD_UINT8,
			TOKEN_KEYWORD_UNICHAR,
			TOKEN_KEYWORD_USING,
			TOKEN_KEYWORD_VIRTUAL,
			TOKEN_KEYWORD_VOID,
			TOKEN_KEYWORD_VOIDPTR,
			TOKEN_KEYWORD_WHILE,
			TOKEN_MINUS_EQUALS,
			TOKEN_MINUS_MINUS,
			TOKEN_MINUS,
			TOKEN_MODULUS,
			TOKEN_NEW_LINE,
			TOKEN_NOT_EQUALS,
			TOKEN_NUMBER,
			TOKEN_OR,
			TOKEN_PARENTHESIS_LEFT,
			TOKEN_PARENTHESIS_RIGHT,
			TOKEN_PLUS_EQUALS,
			TOKEN_PLUS_PLUS,
			TOKEN_PLUS,
			TOKEN_QUESTION_MARK,
			TOKEN_SEMICOLON,
			TOKEN_SPACE,
			TOKEN_SQUARE_BRACKET_LEFT,
			TOKEN_SQUARE_BRACKET_RIGHT,
			TOKEN_STAR_DOUBLE,
			TOKEN_STAR,
			TOKEN_STRING_UNTERMINATED,
			TOKEN_STRING,
			TOKEN_TAB,
			TOKEN_TILDE,
		}

		public Type m_eType;
		public InternalString m_sFileName;
		public int m_nLine;
		public int m_nColumn;
		public InternalString m_sValue;
		public void Stringify(InternalString sOut)
		{
			sOut.Append(GetString());
		}

		public string GetString()
		{
			switch (m_eType)
			{
				case Type.TOKEN_AND:
				{
					return "&&";
				}

				case Type.TOKEN_ANGLE_BRACKET_LEFT_EQUALS:
				{
					return "<=";
				}

				case Type.TOKEN_ANGLE_BRACKET_LEFT:
				{
					return "<";
				}

				case Type.TOKEN_ANGLE_BRACKET_RIGHT_EQUALS:
				{
					return ">=";
				}

				case Type.TOKEN_ANGLE_BRACKET_RIGHT:
				{
					return ">";
				}

				case Type.TOKEN_BANG:
				{
					return "!";
				}

				case Type.TOKEN_BITWISE_AND:
				{
					return "&";
				}

				case Type.TOKEN_BITWISE_OR:
				{
					return "|";
				}

				case Type.TOKEN_CARET:
				{
					return "^";
				}

				case Type.TOKEN_CARRIGE_RETURN:
				{
					return "\r";
				}

				case Type.TOKEN_COLON:
				{
					return ":";
				}

				case Type.TOKEN_COMMA:
				{
					return ",";
				}

				case Type.TOKEN_CURLY_BRACE_LEFT:
				{
					return "{";
				}

				case Type.TOKEN_CURLY_BRACE_RIGHT:
				{
					return "}";
				}

				case Type.TOKEN_DIVIDE:
				{
					return "/";
				}

				case Type.TOKEN_DOT:
				{
					return ".";
				}

				case Type.TOKEN_DOUBLE_ANGLE_BRACKET_LEFT:
				{
					return "<<";
				}

				case Type.TOKEN_DOUBLE_ANGLE_BRACKET_RIGHT:
				{
					return ">>";
				}

				case Type.TOKEN_DOUBLE_COLON:
				{
					return "::";
				}

				case Type.TOKEN_DOUBLE_EQUALS:
				{
					return "==";
				}

				case Type.TOKEN_EQUALS:
				{
					return "=";
				}

				case Type.TOKEN_KEYWORD_BASE:
				{
					return "base";
				}

				case Type.TOKEN_KEYWORD_BOOL:
				{
					return "bool";
				}

				case Type.TOKEN_KEYWORD_BREAK:
				{
					return "break";
				}

				case Type.TOKEN_KEYWORD_CASE:
				{
					return "case";
				}

				case Type.TOKEN_KEYWORD_CAST:
				{
					return "cast";
				}

				case Type.TOKEN_KEYWORD_CLASS:
				{
					return "class";
				}

				case Type.TOKEN_KEYWORD_CONST:
				{
					return "const";
				}

				case Type.TOKEN_KEYWORD_DEFAULT:
				{
					return "default";
				}

				case Type.TOKEN_KEYWORD_DELETE:
				{
					return "delete";
				}

				case Type.TOKEN_KEYWORD_DISOWN:
				{
					return "disown";
				}

				case Type.TOKEN_KEYWORD_DISPOSABLE:
				{
					return "disposable";
				}

				case Type.TOKEN_KEYWORD_DOUBLE:
				{
					return "double";
				}

				case Type.TOKEN_KEYWORD_ELSE:
				{
					return "else";
				}

				case Type.TOKEN_KEYWORD_ENUM:
				{
					return "enum";
				}

				case Type.TOKEN_KEYWORD_FALSE:
				{
					return "false";
				}

				case Type.TOKEN_KEYWORD_FLOAT:
				{
					return "float";
				}

				case Type.TOKEN_KEYWORD_FOR:
				{
					return "for";
				}

				case Type.TOKEN_KEYWORD_IF:
				{
					return "if";
				}

				case Type.TOKEN_KEYWORD_INT:
				{
					return "int";
				}

				case Type.TOKEN_KEYWORD_INT16:
				{
					return "Int16";
				}

				case Type.TOKEN_KEYWORD_INT32:
				{
					return "Int32";
				}

				case Type.TOKEN_KEYWORD_INT8:
				{
					return "Int8";
				}

				case Type.TOKEN_KEYWORD_NAMESPACE:
				{
					return "namespace";
				}

				case Type.TOKEN_KEYWORD_NEW:
				{
					return "new";
				}

				case Type.TOKEN_KEYWORD_NULL:
				{
					return "null";
				}

				case Type.TOKEN_KEYWORD_OVERRIDE:
				{
					return "override";
				}

				case Type.TOKEN_KEYWORD_OWN:
				{
					return "own";
				}

				case Type.TOKEN_KEYWORD_PRIVATE:
				{
					return "private";
				}

				case Type.TOKEN_KEYWORD_PUBLIC:
				{
					return "public";
				}

				case Type.TOKEN_KEYWORD_REF:
				{
					return "ref";
				}

				case Type.TOKEN_KEYWORD_RETURN:
				{
					return "return";
				}

				case Type.TOKEN_KEYWORD_STRING:
				{
					return "string";
				}

				case Type.TOKEN_KEYWORD_SWITCH:
				{
					return "switch";
				}

				case Type.TOKEN_KEYWORD_THIS:
				{
					return "this";
				}

				case Type.TOKEN_KEYWORD_TRUE:
				{
					return "true";
				}

				case Type.TOKEN_KEYWORD_TTHASH:
				{
					return "tthash";
				}

				case Type.TOKEN_KEYWORD_UINT:
				{
					return "uint";
				}

				case Type.TOKEN_KEYWORD_UINT16:
				{
					return "Uint16";
				}

				case Type.TOKEN_KEYWORD_UINT32:
				{
					return "Uint32";
				}

				case Type.TOKEN_KEYWORD_UINT64:
				{
					return "Uint64";
				}

				case Type.TOKEN_KEYWORD_UINT8:
				{
					return "Uint8";
				}

				case Type.TOKEN_KEYWORD_UNICHAR:
				{
					return "UniChar";
				}

				case Type.TOKEN_KEYWORD_USING:
				{
					return "using";
				}

				case Type.TOKEN_KEYWORD_VIRTUAL:
				{
					return "virtual";
				}

				case Type.TOKEN_KEYWORD_VOID:
				{
					return "void";
				}

				case Type.TOKEN_KEYWORD_VOIDPTR:
				{
					return "voidptr";
				}

				case Type.TOKEN_KEYWORD_WHILE:
				{
					return "while";
				}

				case Type.TOKEN_MINUS_EQUALS:
				{
					return "-=";
				}

				case Type.TOKEN_MINUS_MINUS:
				{
					return "--";
				}

				case Type.TOKEN_MINUS:
				{
					return "-";
				}

				case Type.TOKEN_MODULUS:
				{
					return "%";
				}

				case Type.TOKEN_NEW_LINE:
				{
					return "\n";
				}

				case Type.TOKEN_NOT_EQUALS:
				{
					return "!=";
				}

				case Type.TOKEN_OR:
				{
					return "||";
				}

				case Type.TOKEN_PARENTHESIS_LEFT:
				{
					return "(";
				}

				case Type.TOKEN_PARENTHESIS_RIGHT:
				{
					return ")";
				}

				case Type.TOKEN_PLUS_EQUALS:
				{
					return "+=";
				}

				case Type.TOKEN_PLUS_PLUS:
				{
					return "++";
				}

				case Type.TOKEN_PLUS:
				{
					return "+";
				}

				case Type.TOKEN_QUESTION_MARK:
				{
					return "?";
				}

				case Type.TOKEN_SEMICOLON:
				{
					return ";";
				}

				case Type.TOKEN_SPACE:
				{
					return " ";
				}

				case Type.TOKEN_SQUARE_BRACKET_LEFT:
				{
					return "[";
				}

				case Type.TOKEN_SQUARE_BRACKET_RIGHT:
				{
					return "]";
				}

				case Type.TOKEN_STAR:
				{
					return "*";
				}

				case Type.TOKEN_STAR_DOUBLE:
				{
					return "**";
				}

				case Type.TOKEN_TAB:
				{
					return "\t";
				}

				case Type.TOKEN_TILDE:
				{
					return "~";
				}

				case Type.TOKEN_CHAR:
				{
					return m_sValue.GetExternalString();
				}

				case Type.TOKEN_CHAR_UNTERMINATED:
				{
					return m_sValue.GetExternalString();
				}

				case Type.TOKEN_IDENTIFIER:
				{
					return m_sValue.GetExternalString();
				}

				case Type.TOKEN_NUMBER:
				{
					return m_sValue.GetExternalString();
				}

				case Type.TOKEN_STRING:
				{
					return m_sValue.GetExternalString();
				}

				case Type.TOKEN_STRING_UNTERMINATED:
				{
					return m_sValue.GetExternalString();
				}

			}
			return "???";
		}

		public Token Clone()
		{
			Token pToken = new Token();
			pToken.m_eType = m_eType;
			pToken.m_sFileName = m_sFileName;
			pToken.m_nLine = m_nLine;
			pToken.m_nColumn = m_nColumn;
			if (m_sValue != null)
				pToken.m_sValue = new InternalString(m_sValue.GetExternalString());
			NumbatLogic.Token __3778855882 = pToken;
			pToken = null;
			return __3778855882;
		}

		public Token()
		{
		}

		~Token()
		{
		}

	}
}

