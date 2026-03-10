#line 1 "../../../Source/Core/Token.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/Token.nll"
	class Token
	{
#line 5 "../../../Source/Core/Token.nll"
		public enum Type
		{
			TOKEN_ANGLE_BRACKET_LEFT,
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
			TOKEN_DOUBLE_COLON,
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
			TOKEN_MINUS,
			TOKEN_MINUS_MINUS,
			TOKEN_MODULUS,
			TOKEN_NEW_LINE,
			TOKEN_NUMBER,
			TOKEN_PARENTHESIS_LEFT,
			TOKEN_PARENTHESIS_RIGHT,
			TOKEN_PLUS,
			TOKEN_PLUS_PLUS,
			TOKEN_QUESTION_MARK,
			TOKEN_SEMICOLON,
			TOKEN_SPACE,
			TOKEN_SQUARE_BRACKET_LEFT,
			TOKEN_SQUARE_BRACKET_RIGHT,
			TOKEN_STAR,
			TOKEN_STAR_DOUBLE,
			TOKEN_STRING_UNTERMINATED,
			TOKEN_STRING,
			TOKEN_TAB,
			TOKEN_TILDE,
		}

#line 98 "../../../Source/Core/Token.nll"
		public Type m_eType;
#line 99 "../../../Source/Core/Token.nll"
		public InternalString m_sFileName;
#line 100 "../../../Source/Core/Token.nll"
		public int m_nLine;
#line 101 "../../../Source/Core/Token.nll"
		public int m_nColumn;
#line 102 "../../../Source/Core/Token.nll"
		public InternalString m_sValue;
#line 104 "../../../Source/Core/Token.nll"
		public void Stringify(InternalString sOut)
		{
#line 106 "../../../Source/Core/Token.nll"
			sOut.Append(GetString());
		}

#line 109 "../../../Source/Core/Token.nll"
		public string GetString()
		{
#line 111 "../../../Source/Core/Token.nll"
			switch (m_eType)
			{
				case Type.TOKEN_ANGLE_BRACKET_LEFT:
				{
#line 113 "../../../Source/Core/Token.nll"
					return "<";
				}

				case Type.TOKEN_ANGLE_BRACKET_RIGHT:
				{
#line 114 "../../../Source/Core/Token.nll"
					return ">";
				}

				case Type.TOKEN_BANG:
				{
#line 115 "../../../Source/Core/Token.nll"
					return "!";
				}

				case Type.TOKEN_BITWISE_AND:
				{
#line 116 "../../../Source/Core/Token.nll"
					return "&";
				}

				case Type.TOKEN_BITWISE_OR:
				{
#line 117 "../../../Source/Core/Token.nll"
					return "|";
				}

				case Type.TOKEN_CARET:
				{
#line 118 "../../../Source/Core/Token.nll"
					return "^";
				}

				case Type.TOKEN_CARRIGE_RETURN:
				{
#line 119 "../../../Source/Core/Token.nll"
					return "\r";
				}

				case Type.TOKEN_COLON:
				{
#line 120 "../../../Source/Core/Token.nll"
					return ":";
				}

				case Type.TOKEN_COMMA:
				{
#line 121 "../../../Source/Core/Token.nll"
					return ",";
				}

				case Type.TOKEN_CURLY_BRACE_LEFT:
				{
#line 122 "../../../Source/Core/Token.nll"
					return "{";
				}

				case Type.TOKEN_CURLY_BRACE_RIGHT:
				{
#line 123 "../../../Source/Core/Token.nll"
					return "}";
				}

				case Type.TOKEN_DIVIDE:
				{
#line 124 "../../../Source/Core/Token.nll"
					return "/";
				}

				case Type.TOKEN_DOT:
				{
#line 125 "../../../Source/Core/Token.nll"
					return ".";
				}

				case Type.TOKEN_DOUBLE_COLON:
				{
#line 126 "../../../Source/Core/Token.nll"
					return "::";
				}

				case Type.TOKEN_EQUALS:
				{
#line 127 "../../../Source/Core/Token.nll"
					return "=";
				}

				case Type.TOKEN_KEYWORD_BASE:
				{
#line 128 "../../../Source/Core/Token.nll"
					return "base";
				}

				case Type.TOKEN_KEYWORD_BOOL:
				{
#line 129 "../../../Source/Core/Token.nll"
					return "bool";
				}

				case Type.TOKEN_KEYWORD_BREAK:
				{
#line 130 "../../../Source/Core/Token.nll"
					return "break";
				}

				case Type.TOKEN_KEYWORD_CASE:
				{
#line 131 "../../../Source/Core/Token.nll"
					return "case";
				}

				case Type.TOKEN_KEYWORD_CAST:
				{
#line 132 "../../../Source/Core/Token.nll"
					return "cast";
				}

				case Type.TOKEN_KEYWORD_CLASS:
				{
#line 133 "../../../Source/Core/Token.nll"
					return "class";
				}

				case Type.TOKEN_KEYWORD_CONST:
				{
#line 134 "../../../Source/Core/Token.nll"
					return "const";
				}

				case Type.TOKEN_KEYWORD_DEFAULT:
				{
#line 135 "../../../Source/Core/Token.nll"
					return "default";
				}

				case Type.TOKEN_KEYWORD_DELETE:
				{
#line 136 "../../../Source/Core/Token.nll"
					return "delete";
				}

				case Type.TOKEN_KEYWORD_DISOWN:
				{
#line 137 "../../../Source/Core/Token.nll"
					return "disown";
				}

				case Type.TOKEN_KEYWORD_DISPOSABLE:
				{
#line 138 "../../../Source/Core/Token.nll"
					return "disposable";
				}

				case Type.TOKEN_KEYWORD_DOUBLE:
				{
#line 139 "../../../Source/Core/Token.nll"
					return "double";
				}

				case Type.TOKEN_KEYWORD_ELSE:
				{
#line 140 "../../../Source/Core/Token.nll"
					return "else";
				}

				case Type.TOKEN_KEYWORD_ENUM:
				{
#line 141 "../../../Source/Core/Token.nll"
					return "enum";
				}

				case Type.TOKEN_KEYWORD_FALSE:
				{
#line 142 "../../../Source/Core/Token.nll"
					return "false";
				}

				case Type.TOKEN_KEYWORD_FLOAT:
				{
#line 143 "../../../Source/Core/Token.nll"
					return "float";
				}

				case Type.TOKEN_KEYWORD_FOR:
				{
#line 144 "../../../Source/Core/Token.nll"
					return "for";
				}

				case Type.TOKEN_KEYWORD_IF:
				{
#line 145 "../../../Source/Core/Token.nll"
					return "if";
				}

				case Type.TOKEN_KEYWORD_INT:
				{
#line 146 "../../../Source/Core/Token.nll"
					return "int";
				}

				case Type.TOKEN_KEYWORD_INT16:
				{
#line 147 "../../../Source/Core/Token.nll"
					return "Int16";
				}

				case Type.TOKEN_KEYWORD_INT32:
				{
#line 148 "../../../Source/Core/Token.nll"
					return "Int32";
				}

				case Type.TOKEN_KEYWORD_INT8:
				{
#line 149 "../../../Source/Core/Token.nll"
					return "Int8";
				}

				case Type.TOKEN_KEYWORD_NAMESPACE:
				{
#line 150 "../../../Source/Core/Token.nll"
					return "namespace";
				}

				case Type.TOKEN_KEYWORD_NEW:
				{
#line 151 "../../../Source/Core/Token.nll"
					return "new";
				}

				case Type.TOKEN_KEYWORD_NULL:
				{
#line 152 "../../../Source/Core/Token.nll"
					return "null";
				}

				case Type.TOKEN_KEYWORD_OVERRIDE:
				{
#line 153 "../../../Source/Core/Token.nll"
					return "override";
				}

				case Type.TOKEN_KEYWORD_OWN:
				{
#line 154 "../../../Source/Core/Token.nll"
					return "own";
				}

				case Type.TOKEN_KEYWORD_PRIVATE:
				{
#line 155 "../../../Source/Core/Token.nll"
					return "private";
				}

				case Type.TOKEN_KEYWORD_PUBLIC:
				{
#line 156 "../../../Source/Core/Token.nll"
					return "public";
				}

				case Type.TOKEN_KEYWORD_REF:
				{
#line 157 "../../../Source/Core/Token.nll"
					return "ref";
				}

				case Type.TOKEN_KEYWORD_RETURN:
				{
#line 158 "../../../Source/Core/Token.nll"
					return "return";
				}

				case Type.TOKEN_KEYWORD_STRING:
				{
#line 159 "../../../Source/Core/Token.nll"
					return "string";
				}

				case Type.TOKEN_KEYWORD_SWITCH:
				{
#line 160 "../../../Source/Core/Token.nll"
					return "switch";
				}

				case Type.TOKEN_KEYWORD_THIS:
				{
#line 161 "../../../Source/Core/Token.nll"
					return "this";
				}

				case Type.TOKEN_KEYWORD_TRUE:
				{
#line 162 "../../../Source/Core/Token.nll"
					return "true";
				}

				case Type.TOKEN_KEYWORD_TTHASH:
				{
#line 163 "../../../Source/Core/Token.nll"
					return "tthash";
				}

				case Type.TOKEN_KEYWORD_UINT:
				{
#line 164 "../../../Source/Core/Token.nll"
					return "uint";
				}

				case Type.TOKEN_KEYWORD_UINT16:
				{
#line 165 "../../../Source/Core/Token.nll"
					return "Uint16";
				}

				case Type.TOKEN_KEYWORD_UINT32:
				{
#line 166 "../../../Source/Core/Token.nll"
					return "Uint32";
				}

				case Type.TOKEN_KEYWORD_UINT64:
				{
#line 167 "../../../Source/Core/Token.nll"
					return "Uint64";
				}

				case Type.TOKEN_KEYWORD_UINT8:
				{
#line 168 "../../../Source/Core/Token.nll"
					return "Uint8";
				}

				case Type.TOKEN_KEYWORD_UNICHAR:
				{
#line 169 "../../../Source/Core/Token.nll"
					return "UniChar";
				}

				case Type.TOKEN_KEYWORD_USING:
				{
#line 170 "../../../Source/Core/Token.nll"
					return "using";
				}

				case Type.TOKEN_KEYWORD_VIRTUAL:
				{
#line 171 "../../../Source/Core/Token.nll"
					return "virtual";
				}

				case Type.TOKEN_KEYWORD_VOID:
				{
#line 172 "../../../Source/Core/Token.nll"
					return "void";
				}

				case Type.TOKEN_KEYWORD_VOIDPTR:
				{
#line 173 "../../../Source/Core/Token.nll"
					return "voidptr";
				}

				case Type.TOKEN_KEYWORD_WHILE:
				{
#line 174 "../../../Source/Core/Token.nll"
					return "while";
				}

				case Type.TOKEN_MINUS:
				{
#line 175 "../../../Source/Core/Token.nll"
					return "-";
				}

				case Type.TOKEN_MINUS_MINUS:
				{
#line 176 "../../../Source/Core/Token.nll"
					return "--";
				}

				case Type.TOKEN_MODULUS:
				{
#line 177 "../../../Source/Core/Token.nll"
					return "%";
				}

				case Type.TOKEN_NEW_LINE:
				{
#line 178 "../../../Source/Core/Token.nll"
					return "\n";
				}

				case Type.TOKEN_PARENTHESIS_LEFT:
				{
#line 179 "../../../Source/Core/Token.nll"
					return "(";
				}

				case Type.TOKEN_PARENTHESIS_RIGHT:
				{
#line 180 "../../../Source/Core/Token.nll"
					return ")";
				}

				case Type.TOKEN_PLUS:
				{
#line 181 "../../../Source/Core/Token.nll"
					return "+";
				}

				case Type.TOKEN_PLUS_PLUS:
				{
#line 182 "../../../Source/Core/Token.nll"
					return "++";
				}

				case Type.TOKEN_QUESTION_MARK:
				{
#line 183 "../../../Source/Core/Token.nll"
					return "?";
				}

				case Type.TOKEN_SEMICOLON:
				{
#line 184 "../../../Source/Core/Token.nll"
					return ";";
				}

				case Type.TOKEN_SPACE:
				{
#line 185 "../../../Source/Core/Token.nll"
					return " ";
				}

				case Type.TOKEN_SQUARE_BRACKET_LEFT:
				{
#line 186 "../../../Source/Core/Token.nll"
					return "[";
				}

				case Type.TOKEN_SQUARE_BRACKET_RIGHT:
				{
#line 187 "../../../Source/Core/Token.nll"
					return "]";
				}

				case Type.TOKEN_STAR:
				{
#line 188 "../../../Source/Core/Token.nll"
					return "*";
				}

				case Type.TOKEN_STAR_DOUBLE:
				{
#line 189 "../../../Source/Core/Token.nll"
					return "**";
				}

				case Type.TOKEN_TAB:
				{
#line 190 "../../../Source/Core/Token.nll"
					return "\t";
				}

				case Type.TOKEN_TILDE:
				{
#line 191 "../../../Source/Core/Token.nll"
					return "~";
				}

				case Type.TOKEN_CHAR:
				{
#line 193 "../../../Source/Core/Token.nll"
					return m_sValue.GetExternalString();
				}

				case Type.TOKEN_CHAR_UNTERMINATED:
				{
#line 194 "../../../Source/Core/Token.nll"
					return m_sValue.GetExternalString();
				}

				case Type.TOKEN_IDENTIFIER:
				{
#line 195 "../../../Source/Core/Token.nll"
					return m_sValue.GetExternalString();
				}

				case Type.TOKEN_NUMBER:
				{
#line 196 "../../../Source/Core/Token.nll"
					return m_sValue.GetExternalString();
				}

				case Type.TOKEN_STRING:
				{
#line 197 "../../../Source/Core/Token.nll"
					return m_sValue.GetExternalString();
				}

				case Type.TOKEN_STRING_UNTERMINATED:
				{
#line 198 "../../../Source/Core/Token.nll"
					return m_sValue.GetExternalString();
				}

			}
#line 201 "../../../Source/Core/Token.nll"
			return "???";
		}

#line 204 "../../../Source/Core/Token.nll"
		public Token Clone()
		{
#line 206 "../../../Source/Core/Token.nll"
			Token pToken = new Token();
#line 207 "../../../Source/Core/Token.nll"
			pToken.m_eType = m_eType;
#line 208 "../../../Source/Core/Token.nll"
			pToken.m_sFileName = m_sFileName;
#line 209 "../../../Source/Core/Token.nll"
			pToken.m_nLine = m_nLine;
#line 210 "../../../Source/Core/Token.nll"
			pToken.m_nColumn = m_nColumn;
#line 211 "../../../Source/Core/Token.nll"
			if (m_sValue != null)
#line 212 "../../../Source/Core/Token.nll"
				pToken.m_sValue = new InternalString(m_sValue.GetExternalString());
			NumbatLogic.Token __3778724684 = pToken;
#line 214 "../../../Source/Core/Token.nll"
			pToken = null;
#line 214 "../../../Source/Core/Token.nll"
			return __3778724684;
		}

#line 3 "../../../Source/Core/Token.nll"
		public Token()
		{
		}

#line 3 "../../../Source/Core/Token.nll"
		~Token()
		{
		}

	}
}

