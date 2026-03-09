#include "Token.hpp"
#include "../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class InternalString;
	class Token;
}
#line 1 "../../../Source/Core/Token.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/Token.nll"
#line 105 "../../../Source/Core/Token.nll"
	void Token::Stringify(InternalString* sOut)
	{
#line 107 "../../../Source/Core/Token.nll"
		sOut->Append(GetString());
	}

#line 110 "../../../Source/Core/Token.nll"
	const char* Token::GetString()
	{
#line 112 "../../../Source/Core/Token.nll"
		switch (m_eType)
		{
			case Type::TOKEN_ANGLE_BRACKET_LEFT:
			{
#line 114 "../../../Source/Core/Token.nll"
				return "<";
			}

			case Type::TOKEN_ANGLE_BRACKET_RIGHT:
			{
#line 115 "../../../Source/Core/Token.nll"
				return ">";
			}

			case Type::TOKEN_BANG:
			{
#line 116 "../../../Source/Core/Token.nll"
				return "!";
			}

			case Type::TOKEN_BITWISE_AND:
			{
#line 117 "../../../Source/Core/Token.nll"
				return "&";
			}

			case Type::TOKEN_BITWISE_OR:
			{
#line 118 "../../../Source/Core/Token.nll"
				return "|";
			}

			case Type::TOKEN_CARET:
			{
#line 119 "../../../Source/Core/Token.nll"
				return "^";
			}

			case Type::TOKEN_CARRIGE_RETURN:
			{
#line 120 "../../../Source/Core/Token.nll"
				return "\r";
			}

			case Type::TOKEN_COLON:
			{
#line 121 "../../../Source/Core/Token.nll"
				return ":";
			}

			case Type::TOKEN_COMMA:
			{
#line 122 "../../../Source/Core/Token.nll"
				return ",";
			}

			case Type::TOKEN_CURLY_BRACE_LEFT:
			{
#line 123 "../../../Source/Core/Token.nll"
				return "{";
			}

			case Type::TOKEN_CURLY_BRACE_RIGHT:
			{
#line 124 "../../../Source/Core/Token.nll"
				return "}";
			}

			case Type::TOKEN_DIVIDE:
			{
#line 125 "../../../Source/Core/Token.nll"
				return "/";
			}

			case Type::TOKEN_DOT:
			{
#line 126 "../../../Source/Core/Token.nll"
				return ".";
			}

			case Type::TOKEN_DOUBLE_COLON:
			{
#line 127 "../../../Source/Core/Token.nll"
				return "::";
			}

			case Type::TOKEN_EQUALS:
			{
#line 128 "../../../Source/Core/Token.nll"
				return "=";
			}

			case Type::TOKEN_KEYWORD_BASE:
			{
#line 129 "../../../Source/Core/Token.nll"
				return "base";
			}

			case Type::TOKEN_KEYWORD_BOOL:
			{
#line 130 "../../../Source/Core/Token.nll"
				return "bool";
			}

			case Type::TOKEN_KEYWORD_BREAK:
			{
#line 131 "../../../Source/Core/Token.nll"
				return "break";
			}

			case Type::TOKEN_KEYWORD_CASE:
			{
#line 132 "../../../Source/Core/Token.nll"
				return "case";
			}

			case Type::TOKEN_KEYWORD_CAST:
			{
#line 133 "../../../Source/Core/Token.nll"
				return "cast";
			}

			case Type::TOKEN_KEYWORD_CLASS:
			{
#line 134 "../../../Source/Core/Token.nll"
				return "class";
			}

			case Type::TOKEN_KEYWORD_CONST:
			{
#line 135 "../../../Source/Core/Token.nll"
				return "const";
			}

			case Type::TOKEN_KEYWORD_DEFAULT:
			{
#line 136 "../../../Source/Core/Token.nll"
				return "default";
			}

			case Type::TOKEN_KEYWORD_DELETE:
			{
#line 137 "../../../Source/Core/Token.nll"
				return "delete";
			}

			case Type::TOKEN_KEYWORD_DISOWN:
			{
#line 138 "../../../Source/Core/Token.nll"
				return "disown";
			}

			case Type::TOKEN_KEYWORD_DISPOSABLE:
			{
#line 139 "../../../Source/Core/Token.nll"
				return "disposable";
			}

			case Type::TOKEN_KEYWORD_DOUBLE:
			{
#line 140 "../../../Source/Core/Token.nll"
				return "double";
			}

			case Type::TOKEN_KEYWORD_ELSE:
			{
#line 141 "../../../Source/Core/Token.nll"
				return "else";
			}

			case Type::TOKEN_KEYWORD_ENUM:
			{
#line 142 "../../../Source/Core/Token.nll"
				return "enum";
			}

			case Type::TOKEN_KEYWORD_FALSE:
			{
#line 143 "../../../Source/Core/Token.nll"
				return "false";
			}

			case Type::TOKEN_KEYWORD_FLOAT:
			{
#line 144 "../../../Source/Core/Token.nll"
				return "float";
			}

			case Type::TOKEN_KEYWORD_FOR:
			{
#line 145 "../../../Source/Core/Token.nll"
				return "for";
			}

			case Type::TOKEN_KEYWORD_IF:
			{
#line 146 "../../../Source/Core/Token.nll"
				return "if";
			}

			case Type::TOKEN_KEYWORD_INT:
			{
#line 147 "../../../Source/Core/Token.nll"
				return "int";
			}

			case Type::TOKEN_KEYWORD_INT16:
			{
#line 148 "../../../Source/Core/Token.nll"
				return "Int16";
			}

			case Type::TOKEN_KEYWORD_INT32:
			{
#line 149 "../../../Source/Core/Token.nll"
				return "Int32";
			}

			case Type::TOKEN_KEYWORD_INT8:
			{
#line 150 "../../../Source/Core/Token.nll"
				return "Int8";
			}

			case Type::TOKEN_KEYWORD_NAMESPACE:
			{
#line 151 "../../../Source/Core/Token.nll"
				return "namespace";
			}

			case Type::TOKEN_KEYWORD_NEW:
			{
#line 152 "../../../Source/Core/Token.nll"
				return "new";
			}

			case Type::TOKEN_KEYWORD_NULL:
			{
#line 153 "../../../Source/Core/Token.nll"
				return "null";
			}

			case Type::TOKEN_KEYWORD_OVERRIDE:
			{
#line 154 "../../../Source/Core/Token.nll"
				return "override";
			}

			case Type::TOKEN_KEYWORD_OWN:
			{
#line 155 "../../../Source/Core/Token.nll"
				return "own";
			}

			case Type::TOKEN_KEYWORD_PRIVATE:
			{
#line 156 "../../../Source/Core/Token.nll"
				return "private";
			}

			case Type::TOKEN_KEYWORD_PUBLIC:
			{
#line 157 "../../../Source/Core/Token.nll"
				return "public";
			}

			case Type::TOKEN_KEYWORD_REF:
			{
#line 158 "../../../Source/Core/Token.nll"
				return "ref";
			}

			case Type::TOKEN_KEYWORD_RETURN:
			{
#line 159 "../../../Source/Core/Token.nll"
				return "return";
			}

			case Type::TOKEN_KEYWORD_STRING:
			{
#line 160 "../../../Source/Core/Token.nll"
				return "string";
			}

			case Type::TOKEN_KEYWORD_SWITCH:
			{
#line 161 "../../../Source/Core/Token.nll"
				return "switch";
			}

			case Type::TOKEN_KEYWORD_THIS:
			{
#line 162 "../../../Source/Core/Token.nll"
				return "this";
			}

			case Type::TOKEN_KEYWORD_TRUE:
			{
#line 163 "../../../Source/Core/Token.nll"
				return "true";
			}

			case Type::TOKEN_KEYWORD_TTHASH:
			{
#line 164 "../../../Source/Core/Token.nll"
				return "tthash";
			}

			case Type::TOKEN_KEYWORD_UINT:
			{
#line 165 "../../../Source/Core/Token.nll"
				return "uint";
			}

			case Type::TOKEN_KEYWORD_UINT16:
			{
#line 166 "../../../Source/Core/Token.nll"
				return "Uint16";
			}

			case Type::TOKEN_KEYWORD_UINT32:
			{
#line 167 "../../../Source/Core/Token.nll"
				return "Uint32";
			}

			case Type::TOKEN_KEYWORD_UINT64:
			{
#line 168 "../../../Source/Core/Token.nll"
				return "Uint64";
			}

			case Type::TOKEN_KEYWORD_UINT8:
			{
#line 169 "../../../Source/Core/Token.nll"
				return "Uint8";
			}

			case Type::TOKEN_KEYWORD_UNICHAR:
			{
#line 170 "../../../Source/Core/Token.nll"
				return "UniChar";
			}

			case Type::TOKEN_KEYWORD_USING:
			{
#line 171 "../../../Source/Core/Token.nll"
				return "using";
			}

			case Type::TOKEN_KEYWORD_VIRTUAL:
			{
#line 172 "../../../Source/Core/Token.nll"
				return "virtual";
			}

			case Type::TOKEN_KEYWORD_VOID:
			{
#line 173 "../../../Source/Core/Token.nll"
				return "void";
			}

			case Type::TOKEN_KEYWORD_VOIDPTR:
			{
#line 174 "../../../Source/Core/Token.nll"
				return "voidptr";
			}

			case Type::TOKEN_KEYWORD_WHILE:
			{
#line 175 "../../../Source/Core/Token.nll"
				return "while";
			}

			case Type::TOKEN_MINUS:
			{
#line 176 "../../../Source/Core/Token.nll"
				return "-";
			}

			case Type::TOKEN_MINUS_MINUS:
			{
#line 177 "../../../Source/Core/Token.nll"
				return "--";
			}

			case Type::TOKEN_MODULUS:
			{
#line 178 "../../../Source/Core/Token.nll"
				return "%";
			}

			case Type::TOKEN_NEW_LINE:
			{
#line 179 "../../../Source/Core/Token.nll"
				return "\n";
			}

			case Type::TOKEN_PARENTHESIS_LEFT:
			{
#line 180 "../../../Source/Core/Token.nll"
				return "(";
			}

			case Type::TOKEN_PARENTHESIS_RIGHT:
			{
#line 181 "../../../Source/Core/Token.nll"
				return ")";
			}

			case Type::TOKEN_PLUS:
			{
#line 182 "../../../Source/Core/Token.nll"
				return "+";
			}

			case Type::TOKEN_PLUS_PLUS:
			{
#line 183 "../../../Source/Core/Token.nll"
				return "++";
			}

			case Type::TOKEN_QUESTION_MARK:
			{
#line 184 "../../../Source/Core/Token.nll"
				return "?";
			}

			case Type::TOKEN_SEMICOLON:
			{
#line 185 "../../../Source/Core/Token.nll"
				return ";";
			}

			case Type::TOKEN_SPACE:
			{
#line 186 "../../../Source/Core/Token.nll"
				return " ";
			}

			case Type::TOKEN_SQUARE_BRACKET_LEFT:
			{
#line 187 "../../../Source/Core/Token.nll"
				return "[";
			}

			case Type::TOKEN_SQUARE_BRACKET_RIGHT:
			{
#line 188 "../../../Source/Core/Token.nll"
				return "]";
			}

			case Type::TOKEN_STAR:
			{
#line 189 "../../../Source/Core/Token.nll"
				return "*";
			}

			case Type::TOKEN_STAR_DOUBLE:
			{
#line 190 "../../../Source/Core/Token.nll"
				return "**";
			}

			case Type::TOKEN_TAB:
			{
#line 191 "../../../Source/Core/Token.nll"
				return "\t";
			}

			case Type::TOKEN_TILDE:
			{
#line 192 "../../../Source/Core/Token.nll"
				return "~";
			}

			case Type::TOKEN_CHAR:
			{
#line 194 "../../../Source/Core/Token.nll"
				return m_sValue->GetExternalString();
			}

			case Type::TOKEN_CHAR_UNTERMINATED:
			{
#line 195 "../../../Source/Core/Token.nll"
				return m_sValue->GetExternalString();
			}

			case Type::TOKEN_IDENTIFIER:
			{
#line 196 "../../../Source/Core/Token.nll"
				return m_sValue->GetExternalString();
			}

			case Type::TOKEN_NUMBER:
			{
#line 197 "../../../Source/Core/Token.nll"
				return m_sValue->GetExternalString();
			}

			case Type::TOKEN_STRING:
			{
#line 198 "../../../Source/Core/Token.nll"
				return m_sValue->GetExternalString();
			}

			case Type::TOKEN_STRING_UNTERMINATED:
			{
#line 199 "../../../Source/Core/Token.nll"
				return m_sValue->GetExternalString();
			}

		}
#line 202 "../../../Source/Core/Token.nll"
		return "???";
	}

#line 205 "../../../Source/Core/Token.nll"
	Token* Token::Clone()
	{
		Token* pToken = new Token();
#line 208 "../../../Source/Core/Token.nll"
		pToken->m_eType = m_eType;
#line 209 "../../../Source/Core/Token.nll"
		pToken->m_sFileName = m_sFileName;
#line 210 "../../../Source/Core/Token.nll"
		pToken->m_nLine = m_nLine;
#line 211 "../../../Source/Core/Token.nll"
		pToken->m_nColumn = m_nColumn;
#line 212 "../../../Source/Core/Token.nll"
		if (m_sValue != 0)
#line 213 "../../../Source/Core/Token.nll"
			pToken->m_sValue = new InternalString(m_sValue->GetExternalString());
		NumbatLogic::Token* __3778724684 = pToken;
#line 215 "../../../Source/Core/Token.nll"
		pToken = 0;
#line 215 "../../../Source/Core/Token.nll"
		return __3778724684;
	}

#line 4 "../../../Source/Core/Token.nll"
	Token::Token()
	{
		m_eType = Type::TOKEN_ANGLE_BRACKET_LEFT;
		m_sFileName = 0;
		m_nLine = 0;
		m_nColumn = 0;
		m_sValue = 0;
	}

#line 4 "../../../Source/Core/Token.nll"
	Token::~Token()
	{
		if (m_sValue) delete m_sValue;
	}

}

