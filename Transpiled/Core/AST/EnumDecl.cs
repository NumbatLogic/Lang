#line 0 "../../../Source/Core/AST/EnumDecl.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/EnumDecl.nll"
	class EnumDecl : AST
	{
		public Token m_pNameToken;
		public Vector<EnumDeclValue> m_pEnumDeclValueVector;
		public EnumDecl()
		{
			m_bCanDescend = true;
		}

		public static EnumDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token pEnumToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_ENUM);
			if (pEnumToken == null)
			{
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			EnumDecl pEnumDecl = new EnumDecl();
			pEnumDecl.m_eType = AST.Type.AST_ENUM_DECL;
			pEnumDecl.m_pFirstToken = pEnumToken;
			pEnumDecl.m_pEnumDeclValueVector = new Vector<EnumDeclValue>();
			pEnumDecl.m_pNameToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_IDENTIFIER);
			if (pEnumDecl.m_pNameToken == null)
			{
				Console.Log("expected enum name");
				Assert.Plz(false);
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_CURLY_BRACE_LEFT) == null)
			{
				Console.Log("expected opening curly brace");
				Assert.Plz(false);
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			while (true)
			{
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_CURLY_BRACE_RIGHT) != null)
				{
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 51 "../../../Source/Core/AST/EnumDecl.nll"
					break;
				}
				EnumDeclValue pEnumDeclValue = EnumDeclValue.TryCreate(pTokenContainer, pTempOffset);
				if (pEnumDeclValue == null)
				{
					Console.Log("expected EnumDeclValue");
					Assert.Plz(false);
				}
				pEnumDecl.m_pEnumDeclValueVector.PushBack(pEnumDeclValue);
				NumbatLogic.EnumDeclValue __478630801 = pEnumDeclValue;
				pEnumDeclValue = null;
				pEnumDecl.AddChild(__478630801);
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_CURLY_BRACE_RIGHT) != null)
				{
					continue;
				}
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_COMMA) == null)
				{
					Console.Log("expected comma");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					Assert.Plz(false);
				}
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			}
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.EnumDecl __4282209082 = pEnumDecl;
			pEnumDecl = null;
			return __4282209082;
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder out)
		{
			out.m_sOut.Append("enum ");
			m_pNameToken.Stringify(out.m_sOut);
			out.m_sOut.AppendChar('\n');
			Util.Pad(nDepth, out.m_sOut);
			out.m_sOut.Append("{\n");
			for (int i = 0; i < m_pEnumDeclValueVector.GetSize(); i++)
			{
				Util.Pad(nDepth + 1, out.m_sOut);
				EnumDeclValue pEnumDeclValue = m_pEnumDeclValueVector.Get(i);
				pEnumDeclValue.Stringify(eLanguage, eOutputFile, 0, out);
				out.m_sOut.Append(",\n");
			}
			Util.Pad(nDepth, out.m_sOut);
			if (eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.HEADER)
				out.m_sOut.Append("};\n");
			else
				out.m_sOut.Append("}\n");
		}

		~EnumDecl()
		{
		}

	}
}

