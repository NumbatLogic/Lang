#line 1 "../../../Source/Core/AST/EnumDecl.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/EnumDecl.nll"
	class EnumDecl : AST
	{
#line 6 "../../../Source/Core/AST/EnumDecl.nll"
		public Token m_pNameToken;
#line 7 "../../../Source/Core/AST/EnumDecl.nll"
		public Vector<EnumDeclValue> m_pEnumDeclValueVector;
#line 9 "../../../Source/Core/AST/EnumDecl.nll"
		public EnumDecl()
		{
#line 11 "../../../Source/Core/AST/EnumDecl.nll"
			m_bCanDescend = true;
		}

#line 14 "../../../Source/Core/AST/EnumDecl.nll"
		public static EnumDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token pEnumToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_ENUM);
#line 19 "../../../Source/Core/AST/EnumDecl.nll"
			if (pEnumToken == null)
			{
#line 20 "../../../Source/Core/AST/EnumDecl.nll"
				return null;
			}
#line 21 "../../../Source/Core/AST/EnumDecl.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			EnumDecl pEnumDecl = new EnumDecl();
#line 25 "../../../Source/Core/AST/EnumDecl.nll"
			pEnumDecl.m_eType = AST.Type.AST_ENUM_DECL;
#line 26 "../../../Source/Core/AST/EnumDecl.nll"
			pEnumDecl.m_pFirstToken = pEnumToken;
#line 27 "../../../Source/Core/AST/EnumDecl.nll"
			pEnumDecl.m_pEnumDeclValueVector = new Vector<EnumDeclValue>();
#line 29 "../../../Source/Core/AST/EnumDecl.nll"
			pEnumDecl.m_pNameToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_IDENTIFIER);
#line 30 "../../../Source/Core/AST/EnumDecl.nll"
			if (pEnumDecl.m_pNameToken == null)
			{
#line 32 "../../../Source/Core/AST/EnumDecl.nll"
				Console.Log("expected enum name");
#line 33 "../../../Source/Core/AST/EnumDecl.nll"
				Assert.Plz(false);
#line 34 "../../../Source/Core/AST/EnumDecl.nll"
				return null;
			}
#line 36 "../../../Source/Core/AST/EnumDecl.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 38 "../../../Source/Core/AST/EnumDecl.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_CURLY_BRACE_LEFT) == null)
			{
#line 40 "../../../Source/Core/AST/EnumDecl.nll"
				Console.Log("expected opening curly brace");
#line 41 "../../../Source/Core/AST/EnumDecl.nll"
				Assert.Plz(false);
#line 42 "../../../Source/Core/AST/EnumDecl.nll"
				return null;
			}
#line 44 "../../../Source/Core/AST/EnumDecl.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 47 "../../../Source/Core/AST/EnumDecl.nll"
			while (true)
			{
#line 49 "../../../Source/Core/AST/EnumDecl.nll"
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_CURLY_BRACE_RIGHT) != null)
				{
#line 51 "../../../Source/Core/AST/EnumDecl.nll"
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 52 "../../../Source/Core/AST/EnumDecl.nll"
					break;
				}
				EnumDeclValue pEnumDeclValue = EnumDeclValue.TryCreate(pTokenContainer, pTempOffset);
#line 56 "../../../Source/Core/AST/EnumDecl.nll"
				if (pEnumDeclValue == null)
				{
#line 58 "../../../Source/Core/AST/EnumDecl.nll"
					Console.Log("expected EnumDeclValue");
#line 59 "../../../Source/Core/AST/EnumDecl.nll"
					Assert.Plz(false);
				}
#line 61 "../../../Source/Core/AST/EnumDecl.nll"
				pEnumDecl.m_pEnumDeclValueVector.PushBack(pEnumDeclValue);
				NumbatLogic.EnumDeclValue __478630801 = pEnumDeclValue;
#line 62 "../../../Source/Core/AST/EnumDecl.nll"
				pEnumDeclValue = null;
#line 62 "../../../Source/Core/AST/EnumDecl.nll"
				pEnumDecl.AddChild(__478630801);
#line 64 "../../../Source/Core/AST/EnumDecl.nll"
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_CURLY_BRACE_RIGHT) != null)
				{
#line 65 "../../../Source/Core/AST/EnumDecl.nll"
					continue;
				}
#line 67 "../../../Source/Core/AST/EnumDecl.nll"
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_COMMA) == null)
				{
#line 69 "../../../Source/Core/AST/EnumDecl.nll"
					Console.Log("expected comma");
#line 70 "../../../Source/Core/AST/EnumDecl.nll"
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 71 "../../../Source/Core/AST/EnumDecl.nll"
					Assert.Plz(false);
				}
#line 73 "../../../Source/Core/AST/EnumDecl.nll"
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			}
#line 76 "../../../Source/Core/AST/EnumDecl.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.EnumDecl __4282209082 = pEnumDecl;
#line 77 "../../../Source/Core/AST/EnumDecl.nll"
			pEnumDecl = null;
#line 77 "../../../Source/Core/AST/EnumDecl.nll"
			return __4282209082;
		}

#line 80 "../../../Source/Core/AST/EnumDecl.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 82 "../../../Source/Core/AST/EnumDecl.nll"
			pOutputBuilder.m_sOut.Append("enum ");
#line 83 "../../../Source/Core/AST/EnumDecl.nll"
			m_pNameToken.Stringify(pOutputBuilder.m_sOut);
#line 84 "../../../Source/Core/AST/EnumDecl.nll"
			pOutputBuilder.m_sOut.AppendChar('\n');
#line 85 "../../../Source/Core/AST/EnumDecl.nll"
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 86 "../../../Source/Core/AST/EnumDecl.nll"
			pOutputBuilder.m_sOut.Append("{\n");
#line 87 "../../../Source/Core/AST/EnumDecl.nll"
			for (int i = 0; i < m_pEnumDeclValueVector.GetSize(); i++)
			{
#line 89 "../../../Source/Core/AST/EnumDecl.nll"
				Util.Pad(nDepth + 1, pOutputBuilder.m_sOut);
				EnumDeclValue pEnumDeclValue = m_pEnumDeclValueVector.Get(i);
#line 91 "../../../Source/Core/AST/EnumDecl.nll"
				pEnumDeclValue.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 92 "../../../Source/Core/AST/EnumDecl.nll"
				pOutputBuilder.m_sOut.Append(",\n");
			}
#line 94 "../../../Source/Core/AST/EnumDecl.nll"
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 96 "../../../Source/Core/AST/EnumDecl.nll"
			if (eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.HEADER)
#line 97 "../../../Source/Core/AST/EnumDecl.nll"
				pOutputBuilder.m_sOut.Append("};\n");
			else
#line 99 "../../../Source/Core/AST/EnumDecl.nll"
				pOutputBuilder.m_sOut.Append("}\n");
		}

#line 4 "../../../Source/Core/AST/EnumDecl.nll"
		~EnumDecl()
		{
		}

	}
}

