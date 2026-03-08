#line 0 "../../../Source/Core/AST/FunctionDecl.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/FunctionDecl.nll"
	class FunctionDecl : AST
	{
		public TypeRef m_pTypeRef;
		public Token m_pNameToken;
		public string m_sMangledName;
		public ParamDecl m_pParamDecl;
		public bool m_bConst;
		public Scope m_pScope;
		public static FunctionDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum, AST pParent)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			TypeRef pTypeRef = TypeRef.TryCreate(pTokenContainer, pTempOffset);
			if (pTypeRef == null)
			{
				return null;
			}
			Token pNameToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_IDENTIFIER);
			if (pNameToken == null)
			{
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_LEFT) == null)
			{
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
			bool bConst = false;
			Token pConst = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_CONST);
			if (pConst != null)
			{
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
				bConst = true;
			}
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
			FunctionDecl pFunctionDecl = new FunctionDecl();
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
			pFunctionDecl.AddChild(__2942767685);
			NumbatLogic.ParamDecl __3702925988 = pParamDecl;
			pParamDecl = null;
			pFunctionDecl.AddChild(__3702925988);
			if (pScope != null)
			{
				NumbatLogic.Scope __1530815332 = pScope;
				pScope = null;
				pFunctionDecl.AddChild(__1530815332);
			}
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.FunctionDecl __4280092330 = pFunctionDecl;
			pFunctionDecl = null;
			return __4280092330;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			base.Validate(pValidator, pParent);
			if (m_pTypeRef.m_pTypeToken.m_eType == Token.Type.TOKEN_IDENTIFIER)
			{
				if (m_pTypeRef.m_ePointerType == TypeRef.PointerType.OWNED)
				{
					pValidator.AddError("Return value cannot be a owned pointer!", m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
					return;
				}
			}
			ValueType pValueType = m_pTypeRef.CreateValueType(pValidator.m_pResolver);
			if (pValueType == null)
			{
				pValidator.AddError("Unable to compute value type of function result", m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
				return;
			}
			if (pValueType.m_pClassDecl != null)
				AddClassDeclReference(pValueType.m_pClassDecl, AST.OutputFile.HEADER, true);
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder out)
		{
			MemberFunctionDecl pMemberFunctionDecl = null;
			if (m_pParent != null && m_pParent.m_eType == AST.Type.AST_MEMBER_FUNCTION_DECL)
				pMemberFunctionDecl = (MemberFunctionDecl)(m_pParent);
			bool bGeneric = pMemberFunctionDecl != null && pMemberFunctionDecl.m_pParentClassDecl.m_pGenericTypeDeclVector.GetSize() > 0;
			if (pMemberFunctionDecl != null && eLanguage == AST.Language.CS && ExternalString.Equal("GetType", m_pNameToken.GetString()))
			{
				out.m_sOut.Append("new ");
			}
			m_pTypeRef.Stringify(eLanguage, eOutputFile, 0, out);
			out.m_sOut.AppendChar(' ');
			if (eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE)
			{
				if (pMemberFunctionDecl != null)
				{
					AST pPrefixParent = pMemberFunctionDecl;
					InternalString sPrefix = new InternalString("");
					InternalString sTemp = new InternalString("");
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
						pPrefixParent = pPrefixParent.m_pParent;
					}
					out.m_sOut.Append(sPrefix.GetExternalString());
				}
			}
			out.m_sOut.Append(m_sMangledName);
			m_pParamDecl.Stringify(eLanguage, eOutputFile, 0, out);
			if (m_bConst && eLanguage == AST.Language.CPP)
				out.m_sOut.Append(" const");
			if ((eOutputFile == AST.OutputFile.HEADER && !bGeneric) || eLanguage == AST.Language.NLL_DEF)
			{
				out.m_sOut.Append(";\n");
				return;
			}
			if (m_pScope == null)
			{
				out.m_sOut.Append(";\n");
			}
			else
			{
				out.m_sOut.AppendChar('\n');
				m_pScope.Stringify(eLanguage, eOutputFile, nDepth, out);
				out.m_sOut.AppendChar('\n');
			}
		}

		public FunctionDecl()
		{
		}

	}
}

