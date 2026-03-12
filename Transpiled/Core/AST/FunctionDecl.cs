#line 1 "../../../Source/Core/AST/FunctionDecl.nll"
namespace NumbatLogic
{
	class FunctionDecl : AST
	{
		public TypeRef m_pTypeRef;
		public Token m_pNameToken;
		public string m_sMangledName;
		public ParamDecl m_pParamDecl;
		public bool m_bConst;
		public Scope m_pScope;
#line 12 "../../../Source/Core/AST/FunctionDecl.nll"
		public static FunctionDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum, AST pParent)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 16 "../../../Source/Core/AST/FunctionDecl.nll"
			TypeRef pTypeRef = TypeRef.TryCreate(pTokenContainer, pTempOffset);
			if (pTypeRef == null)
			{
#line 18 "../../../Source/Core/AST/FunctionDecl.nll"
				return null;
			}
			Token pNameToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_IDENTIFIER);
			if (pNameToken == null)
			{
#line 22 "../../../Source/Core/AST/FunctionDecl.nll"
				return null;
			}
#line 23 "../../../Source/Core/AST/FunctionDecl.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 25 "../../../Source/Core/AST/FunctionDecl.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_LEFT) == null)
			{
#line 26 "../../../Source/Core/AST/FunctionDecl.nll"
				return null;
			}
			ParamDecl pParamDecl = ParamDecl.TryCreate(pTokenContainer, pTempOffset);
			if (pParamDecl == null)
			{
				Console.Log("expected ParamDecl");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				Assert.Plz(false);
				return null;
			}
#line 37 "../../../Source/Core/AST/FunctionDecl.nll"
			bool bConst = false;
			Token pConst = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_CONST);
			if (pConst != null)
			{
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
				bConst = true;
			}
#line 45 "../../../Source/Core/AST/FunctionDecl.nll"
			Scope pScope = null;
			Token pSemicolon = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SEMICOLON);
			if (pSemicolon != null)
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			else
			{
				pScope = Scope.TryCreate(pTokenContainer, pTempOffset, false);
				if (pScope == null)
				{
					Console.Log("expected scope");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					Assert.Plz(false);
				}
			}
#line 61 "../../../Source/Core/AST/FunctionDecl.nll"
			FunctionDecl pFunctionDecl = new FunctionDecl();
#line 63 "../../../Source/Core/AST/FunctionDecl.nll"
			pFunctionDecl.m_eType = AST.Type.AST_FUNCTION_DECL;
			pFunctionDecl.m_pParent = pParent;
			pFunctionDecl.m_pFirstToken = pTypeRef.m_pFirstToken;
			pFunctionDecl.m_pTypeRef = pTypeRef;
			pFunctionDecl.m_pNameToken = pNameToken;
			pFunctionDecl.m_sMangledName = pNameToken.GetString();
			pFunctionDecl.m_pParamDecl = pParamDecl;
			pFunctionDecl.m_bConst = bConst;
			pFunctionDecl.m_pScope = pScope;
			NumbatLogic.TypeRef __2942767685 = pTypeRef;
			pTypeRef = null;
#line 73 "../../../Source/Core/AST/FunctionDecl.nll"
			pFunctionDecl.AddChild(__2942767685);
			NumbatLogic.ParamDecl __3702925988 = pParamDecl;
#line 74 "../../../Source/Core/AST/FunctionDecl.nll"
			pParamDecl = null;
#line 74 "../../../Source/Core/AST/FunctionDecl.nll"
			pFunctionDecl.AddChild(__3702925988);
#line 76 "../../../Source/Core/AST/FunctionDecl.nll"
			if (pScope != null)
			{
				NumbatLogic.Scope __1530815332 = pScope;
#line 77 "../../../Source/Core/AST/FunctionDecl.nll"
				pScope = null;
#line 77 "../../../Source/Core/AST/FunctionDecl.nll"
				pFunctionDecl.AddChild(__1530815332);
			}
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.FunctionDecl __4280092330 = pFunctionDecl;
#line 80 "../../../Source/Core/AST/FunctionDecl.nll"
			pFunctionDecl = null;
#line 80 "../../../Source/Core/AST/FunctionDecl.nll"
			return __4280092330;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			base.Validate(pValidator, pParent);
#line 87 "../../../Source/Core/AST/FunctionDecl.nll"
			if (m_pTypeRef.m_pTypeToken.m_eType == Token.Type.TOKEN_IDENTIFIER)
			{
				if (m_pTypeRef.m_ePointerType == TypeRef.PointerType.OWNED)
				{
					pValidator.AddError("Return value cannot be a owned pointer!", m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
					return;
				}
			}
#line 97 "../../../Source/Core/AST/FunctionDecl.nll"
			ValueType pValueType = m_pTypeRef.CreateValueType(pValidator.m_pResolver);
			if (pValueType == null)
			{
				pValidator.AddError("Unable to compute value type of function result", m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
				return;
			}
#line 104 "../../../Source/Core/AST/FunctionDecl.nll"
			if (pValueType.m_pClassDecl != null)
				AddClassDeclReference(pValueType.m_pClassDecl, AST.OutputFile.HEADER, true);
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			MemberFunctionDecl pMemberFunctionDecl = null;
			if (m_pParent != null && m_pParent.m_eType == AST.Type.AST_MEMBER_FUNCTION_DECL)
				pMemberFunctionDecl = (MemberFunctionDecl)(m_pParent);
#line 114 "../../../Source/Core/AST/FunctionDecl.nll"
			bool bGeneric = pMemberFunctionDecl != null && pMemberFunctionDecl.m_pParentClassDecl.m_pGenericTypeDeclVector.GetSize() > 0;
#line 116 "../../../Source/Core/AST/FunctionDecl.nll"
			if (pMemberFunctionDecl != null && eLanguage == AST.Language.CS && ExternalString.Equal("GetType", m_pNameToken.GetString()))
			{
#line 119 "../../../Source/Core/AST/FunctionDecl.nll"
				pOutputBuilder.m_sOut.Append("new ");
			}
#line 122 "../../../Source/Core/AST/FunctionDecl.nll"
			m_pTypeRef.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 124 "../../../Source/Core/AST/FunctionDecl.nll"
			pOutputBuilder.m_sOut.AppendChar(' ');
#line 126 "../../../Source/Core/AST/FunctionDecl.nll"
			if (eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE)
			{
				if (pMemberFunctionDecl != null)
				{
					AST pPrefixParent = pMemberFunctionDecl;
					InternalString sPrefix = new InternalString("");
					InternalString sTemp = new InternalString("");
#line 134 "../../../Source/Core/AST/FunctionDecl.nll"
					while (pPrefixParent.m_pParent != null)
					{
						if (pPrefixParent.m_eType == AST.Type.AST_CLASS_DECL)
						{
							sTemp.Set(sPrefix.GetExternalString());
							sPrefix.Set("");
							((ClassDecl)(pPrefixParent)).m_pNameToken.Stringify(sPrefix);
							sPrefix.Append("::");
							sPrefix.Append(sTemp.GetExternalString());
						}
#line 145 "../../../Source/Core/AST/FunctionDecl.nll"
						pPrefixParent = pPrefixParent.m_pParent;
					}
#line 149 "../../../Source/Core/AST/FunctionDecl.nll"
					pOutputBuilder.m_sOut.Append(sPrefix.GetExternalString());
				}
			}
#line 153 "../../../Source/Core/AST/FunctionDecl.nll"
			pOutputBuilder.m_sOut.Append(m_sMangledName);
			m_pParamDecl.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 156 "../../../Source/Core/AST/FunctionDecl.nll"
			if (m_bConst && eLanguage == AST.Language.CPP)
				pOutputBuilder.m_sOut.Append(" const");
#line 160 "../../../Source/Core/AST/FunctionDecl.nll"
			if ((eOutputFile == AST.OutputFile.HEADER && !bGeneric) || eLanguage == AST.Language.NLL_DEF)
			{
				pOutputBuilder.m_sOut.Append(";\n");
				return;
			}
#line 166 "../../../Source/Core/AST/FunctionDecl.nll"
			if (m_pScope == null)
			{
				pOutputBuilder.m_sOut.Append(";\n");
			}
			else
			{
				pOutputBuilder.m_sOut.AppendChar('\n');
				m_pScope.Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
				pOutputBuilder.m_sOut.AppendChar('\n');
			}
		}

#line 3 "../../../Source/Core/AST/FunctionDecl.nll"
		public FunctionDecl()
		{
		}

	}
}

