#line 1 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
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
		public Vector<DecoratorCall> m_pDecoratorCallVector;
#line 13 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
		public FunctionDecl()
		{
			m_pDecoratorCallVector = new Vector<DecoratorCall>();
		}

		public static FunctionDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum, AST pParent)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 22 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
			TypeRef pTypeRef = TypeRef.TryCreate(pTokenContainer, pTempOffset);
			if (pTypeRef == null)
			{
#line 24 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
				return null;
			}
			OwnedVector<DecoratorCall> pOwnedDecoratorCallVector = new OwnedVector<DecoratorCall>();
			while (true)
			{
				DecoratorCall pDecoratorCall = DecoratorCall.TryCreate(pTokenContainer, pTempOffset);
				if (pDecoratorCall == null)
				{
#line 31 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
					break;
				}
				NumbatLogic.DecoratorCall __1592839561 = pDecoratorCall;
#line 33 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
				pDecoratorCall = null;
#line 33 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
				pOwnedDecoratorCallVector.PushBack(__1592839561);
			}
#line 36 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
			Token pNameToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_IDENTIFIER);
			if (pNameToken == null)
			{
#line 38 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
				return null;
			}
#line 39 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 41 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_LEFT) == null)
			{
#line 42 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
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
#line 53 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
			bool bConst = false;
			Token pConst = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_CONST);
			if (pConst != null)
			{
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
				bConst = true;
			}
#line 61 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
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
#line 76 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
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
			NumbatLogic.TypeRef __2942833288 = pTypeRef;
			pTypeRef = null;
#line 87 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
			pFunctionDecl.AddChild(__2942833288);
			NumbatLogic.ParamDecl __3702991591 = pParamDecl;
#line 88 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
			pParamDecl = null;
#line 88 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
			pFunctionDecl.AddChild(__3702991591);
#line 90 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
			while (pOwnedDecoratorCallVector.GetSize() > 0)
			{
				DecoratorCall pDecoratorCall = pOwnedDecoratorCallVector.PopFront();
				pDecoratorCall.m_pParent = pFunctionDecl;
				DecoratorCall pTemp = pDecoratorCall;
				pFunctionDecl.m_pDecoratorCallVector.PushBack(pTemp);
				NumbatLogic.DecoratorCall __1593233158 = pDecoratorCall;
#line 96 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
				pDecoratorCall = null;
#line 96 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
				pFunctionDecl.AddChild(__1593233158);
			}
#line 99 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
			if (pScope != null)
			{
				NumbatLogic.Scope __3569555213 = pScope;
#line 100 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
				pScope = null;
#line 100 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
				pFunctionDecl.AddChild(__3569555213);
			}
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.FunctionDecl __3411818370 = pFunctionDecl;
#line 103 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
			pFunctionDecl = null;
#line 103 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
			return __3411818370;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			base.Validate(pValidator, pParent);
#line 110 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
			if (m_pTypeRef.m_pTypeToken.m_eType == Token.Type.TOKEN_IDENTIFIER)
			{
				if (m_pTypeRef.m_ePointerType == TypeRef.PointerType.OWNED)
				{
					pValidator.AddError("Return value cannot be a owned pointer!", m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
					return;
				}
			}
#line 120 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
			ValueType pValueType = m_pTypeRef.CreateValueType(pValidator.m_pResolver);
			if (pValueType == null)
			{
				pValidator.AddError("Unable to compute value type of function result", m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
				return;
			}
#line 127 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
			if (pValueType.m_pClassDecl != null)
				AddClassDeclReference(pValueType.m_pClassDecl, AST.OutputFile.HEADER, true);
		}

		public void AppendFullyQualifiedName(Language eLanguage, InternalString sOut)
		{
			string sxSeparator = "::";
			if (eLanguage == AST.Language.CS)
				sxSeparator = ".";
#line 137 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
			AST pParent = m_pParent;
			while (pParent != null)
			{
				if (pParent.m_eType == AST.Type.AST_CLASS_DECL)
				{
					ClassDecl pClassDecl = (ClassDecl)(pParent);
					pClassDecl.AppendFullyQualifiedName(eLanguage, sOut);
					sOut.Append(sxSeparator);
					break;
				}
				pParent = pParent.m_pParent;
			}
#line 150 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
			sOut.Append(m_sMangledName);
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			MemberFunctionDecl pMemberFunctionDecl = null;
			if (m_pParent != null && m_pParent.m_eType == AST.Type.AST_MEMBER_FUNCTION_DECL)
				pMemberFunctionDecl = (MemberFunctionDecl)(m_pParent);
#line 159 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
			bool bGeneric = pMemberFunctionDecl != null && pMemberFunctionDecl.m_pParentClassDecl.m_pGenericTypeDeclVector.GetSize() > 0;
#line 161 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
			if (pMemberFunctionDecl != null && eLanguage == AST.Language.CS && ExternalString.Equal("GetType", m_pNameToken.GetString()))
			{
#line 164 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
				pOutputBuilder.m_sOut.Append("new ");
			}
#line 167 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
			m_pTypeRef.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			pOutputBuilder.m_sOut.AppendChar(' ');
#line 170 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
			if (eLanguage == AST.Language.NLL && m_pDecoratorCallVector != null && m_pDecoratorCallVector.GetSize() > 0)
			{
				for (int i = 0; i < m_pDecoratorCallVector.GetSize(); i++)
				{
					DecoratorCall pDecoratorCall = m_pDecoratorCallVector.Get(i);
					pDecoratorCall.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
				}
				pOutputBuilder.m_sOut.AppendChar(' ');
			}
#line 181 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
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
#line 199 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
						pPrefixParent = pPrefixParent.m_pParent;
					}
#line 202 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
					pOutputBuilder.m_sOut.Append(sPrefix.GetExternalString());
				}
			}
#line 206 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
			pOutputBuilder.m_sOut.Append(m_sMangledName);
			m_pParamDecl.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 209 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
			if (m_bConst && eLanguage == AST.Language.CPP)
				pOutputBuilder.m_sOut.Append(" const");
#line 213 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
			if ((eOutputFile == AST.OutputFile.HEADER && !bGeneric) || eLanguage == AST.Language.NLL_DEF)
			{
				pOutputBuilder.m_sOut.Append(";\n");
				return;
			}
#line 219 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
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

#line 3 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
		~FunctionDecl()
		{
		}

	}
}

