#line 1 "../../../Source/Core/AST/EnumDecl.nll"
namespace NumbatLogic
{
	class EnumDecl : AST
	{
		public Token m_pNameToken;
		public Vector<EnumDeclValue> m_pEnumDeclValueVector;
#line 8 "../../../Source/Core/AST/EnumDecl.nll"
		public EnumDecl()
		{
			m_bCanDescend = true;
		}

		public static EnumDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 17 "../../../Source/Core/AST/EnumDecl.nll"
			Token pEnumToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_ENUM);
			if (pEnumToken == null)
			{
#line 19 "../../../Source/Core/AST/EnumDecl.nll"
				return null;
			}
#line 20 "../../../Source/Core/AST/EnumDecl.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 22 "../../../Source/Core/AST/EnumDecl.nll"
			EnumDecl pEnumDecl = new EnumDecl();
#line 24 "../../../Source/Core/AST/EnumDecl.nll"
			pEnumDecl.m_eType = AST.Type.AST_ENUM_DECL;
			pEnumDecl.m_pFirstToken = pEnumToken;
			pEnumDecl.m_pEnumDeclValueVector = new Vector<EnumDeclValue>();
#line 28 "../../../Source/Core/AST/EnumDecl.nll"
			pEnumDecl.m_pNameToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_IDENTIFIER);
			if (pEnumDecl.m_pNameToken == null)
			{
				Console.Log("expected enum name");
				Assert.Plz(false);
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 37 "../../../Source/Core/AST/EnumDecl.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_CURLY_BRACE_LEFT) == null)
			{
				Console.Log("expected opening curly brace");
				Assert.Plz(false);
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 46 "../../../Source/Core/AST/EnumDecl.nll"
			while (true)
			{
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_CURLY_BRACE_RIGHT) != null)
				{
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
					break;
				}
#line 54 "../../../Source/Core/AST/EnumDecl.nll"
				EnumDeclValue pEnumDeclValue = EnumDeclValue.TryCreate(pTokenContainer, pTempOffset);
				if (pEnumDeclValue == null)
				{
					Console.Log("expected EnumDeclValue");
					Assert.Plz(false);
				}
				pEnumDecl.m_pEnumDeclValueVector.PushBack(pEnumDeclValue);
				NumbatLogic.EnumDeclValue __478630801 = pEnumDeclValue;
#line 61 "../../../Source/Core/AST/EnumDecl.nll"
				pEnumDeclValue = null;
#line 61 "../../../Source/Core/AST/EnumDecl.nll"
				pEnumDecl.AddChild(__478630801);
#line 63 "../../../Source/Core/AST/EnumDecl.nll"
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_CURLY_BRACE_RIGHT) != null)
				{
#line 64 "../../../Source/Core/AST/EnumDecl.nll"
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
#line 75 "../../../Source/Core/AST/EnumDecl.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.EnumDecl __4282209082 = pEnumDecl;
#line 76 "../../../Source/Core/AST/EnumDecl.nll"
			pEnumDecl = null;
#line 76 "../../../Source/Core/AST/EnumDecl.nll"
			return __4282209082;
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			pOutputBuilder.m_sOut.Append("enum ");
			m_pNameToken.Stringify(pOutputBuilder.m_sOut);
			pOutputBuilder.m_sOut.AppendChar('\n');
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
			pOutputBuilder.m_sOut.Append("{\n");
			for (int i = 0; i < m_pEnumDeclValueVector.GetSize(); i++)
			{
				Util.Pad(nDepth + 1, pOutputBuilder.m_sOut);
				EnumDeclValue pEnumDeclValue = m_pEnumDeclValueVector.Get(i);
				pEnumDeclValue.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
				pOutputBuilder.m_sOut.Append(",\n");
			}
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 95 "../../../Source/Core/AST/EnumDecl.nll"
			if (eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.HEADER)
				pOutputBuilder.m_sOut.Append("};\n");
			else
				pOutputBuilder.m_sOut.Append("}\n");
		}

#line 3 "../../../Source/Core/AST/EnumDecl.nll"
		~EnumDecl()
		{
		}

	}
}

