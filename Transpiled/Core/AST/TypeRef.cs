#line 1 "../../../Source/Core/AST/TypeRef.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/TypeRef.nll"
	class TypeRef : AST
	{
#line 6 "../../../Source/Core/AST/TypeRef.nll"
		public enum PointerType
		{
			SHARED,
			OWNED,
			TRANSITON,
			OWNED_PREASSSIGN,
		}

#line 14 "../../../Source/Core/AST/TypeRef.nll"
		public bool m_bConst;
#line 15 "../../../Source/Core/AST/TypeRef.nll"
		public bool m_bRef;
#line 16 "../../../Source/Core/AST/TypeRef.nll"
		public Token m_pTypeToken;
#line 17 "../../../Source/Core/AST/TypeRef.nll"
		public Vector<TypeRef> m_pGenericTypeRefVector;
#line 18 "../../../Source/Core/AST/TypeRef.nll"
		public TypeRef m_pChildTypeRef;
#line 19 "../../../Source/Core/AST/TypeRef.nll"
		public PointerType m_ePointerType;
#line 21 "../../../Source/Core/AST/TypeRef.nll"
		public Token m_pCloneToken;
#line 23 "../../../Source/Core/AST/TypeRef.nll"
		public AST m_pFoundType;
#line 25 "../../../Source/Core/AST/TypeRef.nll"
		public TypeRef()
		{
#line 27 "../../../Source/Core/AST/TypeRef.nll"
			m_eType = AST.Type.AST_TYPE_REF;
#line 28 "../../../Source/Core/AST/TypeRef.nll"
			m_pGenericTypeRefVector = new Vector<TypeRef>();
#line 29 "../../../Source/Core/AST/TypeRef.nll"
			m_bConst = false;
#line 30 "../../../Source/Core/AST/TypeRef.nll"
			m_bRef = false;
		}

#line 33 "../../../Source/Core/AST/TypeRef.nll"
		public static TypeRef TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			bool bConst = false;
			Token pConstToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_CONST);
#line 39 "../../../Source/Core/AST/TypeRef.nll"
			if (pConstToken != null)
			{
#line 41 "../../../Source/Core/AST/TypeRef.nll"
				bConst = true;
#line 42 "../../../Source/Core/AST/TypeRef.nll"
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			}
			bool bRef = false;
			Token pRefToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_REF);
#line 47 "../../../Source/Core/AST/TypeRef.nll"
			if (pRefToken != null)
			{
#line 49 "../../../Source/Core/AST/TypeRef.nll"
				bRef = true;
#line 50 "../../../Source/Core/AST/TypeRef.nll"
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			}
			Token pTypeToken = pTokenContainer.Peek(pTempOffset);
#line 54 "../../../Source/Core/AST/TypeRef.nll"
			if (pTypeToken == null || pTypeToken.m_eType != Token.Type.TOKEN_KEYWORD_VOID && pTypeToken.m_eType != Token.Type.TOKEN_KEYWORD_INT && pTypeToken.m_eType != Token.Type.TOKEN_KEYWORD_BOOL && pTypeToken.m_eType != Token.Type.TOKEN_KEYWORD_UNICHAR && pTypeToken.m_eType != Token.Type.TOKEN_KEYWORD_STRING && pTypeToken.m_eType != Token.Type.TOKEN_KEYWORD_UINT && pTypeToken.m_eType != Token.Type.TOKEN_KEYWORD_UINT8 && pTypeToken.m_eType != Token.Type.TOKEN_KEYWORD_UINT16 && pTypeToken.m_eType != Token.Type.TOKEN_KEYWORD_UINT32 && pTypeToken.m_eType != Token.Type.TOKEN_KEYWORD_UINT64 && pTypeToken.m_eType != Token.Type.TOKEN_KEYWORD_INT8 && pTypeToken.m_eType != Token.Type.TOKEN_KEYWORD_INT16 && pTypeToken.m_eType != Token.Type.TOKEN_KEYWORD_INT32 && pTypeToken.m_eType != Token.Type.TOKEN_KEYWORD_DOUBLE && pTypeToken.m_eType != Token.Type.TOKEN_KEYWORD_FLOAT && pTypeToken.m_eType != Token.Type.TOKEN_KEYWORD_VOIDPTR && pTypeToken.m_eType != Token.Type.TOKEN_IDENTIFIER)
			{
#line 72 "../../../Source/Core/AST/TypeRef.nll"
				return null;
			}
#line 73 "../../../Source/Core/AST/TypeRef.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			TypeRef pTypeRef = new TypeRef();
#line 78 "../../../Source/Core/AST/TypeRef.nll"
			pTypeRef.m_pFirstToken = pTypeToken;
#line 79 "../../../Source/Core/AST/TypeRef.nll"
			if (pConstToken != null)
#line 80 "../../../Source/Core/AST/TypeRef.nll"
				pTypeRef.m_pFirstToken = pConstToken;
#line 81 "../../../Source/Core/AST/TypeRef.nll"
			pTypeRef.m_bConst = bConst;
#line 82 "../../../Source/Core/AST/TypeRef.nll"
			pTypeRef.m_pTypeToken = pTypeToken;
#line 83 "../../../Source/Core/AST/TypeRef.nll"
			pTypeRef.m_pChildTypeRef = null;
#line 84 "../../../Source/Core/AST/TypeRef.nll"
			pTypeRef.m_ePointerType = PointerType.SHARED;
#line 86 "../../../Source/Core/AST/TypeRef.nll"
			pTypeRef.m_bRef = bRef;
#line 88 "../../../Source/Core/AST/TypeRef.nll"
			if (pTypeToken.m_eType == Token.Type.TOKEN_IDENTIFIER)
			{
				Token pAngleBracketLeft = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_ANGLE_BRACKET_LEFT);
#line 91 "../../../Source/Core/AST/TypeRef.nll"
				if (pAngleBracketLeft != null)
				{
#line 93 "../../../Source/Core/AST/TypeRef.nll"
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 95 "../../../Source/Core/AST/TypeRef.nll"
					while (true)
					{
#line 97 "../../../Source/Core/AST/TypeRef.nll"
						if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_ANGLE_BRACKET_RIGHT) != null)
						{
#line 99 "../../../Source/Core/AST/TypeRef.nll"
							pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 100 "../../../Source/Core/AST/TypeRef.nll"
							break;
						}
						TypeRef pGenericTypeRef = TypeRef.TryCreate(pTokenContainer, pTempOffset);
#line 104 "../../../Source/Core/AST/TypeRef.nll"
						if (pGenericTypeRef == null)
						{
#line 106 "../../../Source/Core/AST/TypeRef.nll"
							Console.Log("expected inner TypeRef");
#line 107 "../../../Source/Core/AST/TypeRef.nll"
							Assert.Plz(false);
						}
#line 110 "../../../Source/Core/AST/TypeRef.nll"
						pTypeRef.m_pGenericTypeRefVector.PushBack(pGenericTypeRef);
						NumbatLogic.TypeRef __3744382558 = pGenericTypeRef;
#line 111 "../../../Source/Core/AST/TypeRef.nll"
						pGenericTypeRef = null;
#line 111 "../../../Source/Core/AST/TypeRef.nll"
						pTypeRef.AddChild(__3744382558);
#line 113 "../../../Source/Core/AST/TypeRef.nll"
						if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_ANGLE_BRACKET_RIGHT) != null)
						{
#line 114 "../../../Source/Core/AST/TypeRef.nll"
							continue;
						}
#line 116 "../../../Source/Core/AST/TypeRef.nll"
						if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_COMMA) == null)
						{
							InternalString sTemp = new InternalString("expected comma ");
#line 119 "../../../Source/Core/AST/TypeRef.nll"
							sTemp.Append(pTokenContainer.StringifyOffset(pTempOffset));
#line 120 "../../../Source/Core/AST/TypeRef.nll"
							Console.Log(sTemp.GetExternalString());
#line 121 "../../../Source/Core/AST/TypeRef.nll"
							Assert.Plz(false);
						}
#line 123 "../../../Source/Core/AST/TypeRef.nll"
						pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
					}
				}
			}
#line 128 "../../../Source/Core/AST/TypeRef.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_DOUBLE_COLON) != null)
			{
#line 130 "../../../Source/Core/AST/TypeRef.nll"
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
				TypeRef pChildTypeRef = TypeRef.TryCreate(pTokenContainer, pTempOffset);
#line 133 "../../../Source/Core/AST/TypeRef.nll"
				if (pChildTypeRef == null)
				{
					InternalString sTemp = new InternalString("expected child TypeRef... ");
#line 136 "../../../Source/Core/AST/TypeRef.nll"
					sTemp.Append(pTokenContainer.StringifyOffset(pTempOffset));
#line 137 "../../../Source/Core/AST/TypeRef.nll"
					Console.Log(sTemp.GetExternalString());
#line 138 "../../../Source/Core/AST/TypeRef.nll"
					Assert.Plz(false);
#line 139 "../../../Source/Core/AST/TypeRef.nll"
					return null;
				}
#line 142 "../../../Source/Core/AST/TypeRef.nll"
				pTypeRef.m_pChildTypeRef = pChildTypeRef;
				NumbatLogic.TypeRef __1983801666 = pChildTypeRef;
#line 143 "../../../Source/Core/AST/TypeRef.nll"
				pChildTypeRef = null;
#line 143 "../../../Source/Core/AST/TypeRef.nll"
				pTypeRef.AddChild(__1983801666);
			}
			else
#line 150 "../../../Source/Core/AST/TypeRef.nll"
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_STAR) != null)
				{
#line 152 "../../../Source/Core/AST/TypeRef.nll"
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 153 "../../../Source/Core/AST/TypeRef.nll"
					pTypeRef.m_ePointerType = PointerType.OWNED;
				}
				else
#line 155 "../../../Source/Core/AST/TypeRef.nll"
					if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_STAR_DOUBLE) != null)
					{
#line 157 "../../../Source/Core/AST/TypeRef.nll"
						pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 158 "../../../Source/Core/AST/TypeRef.nll"
						pTypeRef.m_ePointerType = PointerType.TRANSITON;
					}
#line 164 "../../../Source/Core/AST/TypeRef.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.TypeRef __967910118 = pTypeRef;
#line 165 "../../../Source/Core/AST/TypeRef.nll"
			pTypeRef = null;
#line 165 "../../../Source/Core/AST/TypeRef.nll"
			return __967910118;
		}

#line 169 "../../../Source/Core/AST/TypeRef.nll"
		public ClassDecl GetFoundClassDecl()
		{
#line 171 "../../../Source/Core/AST/TypeRef.nll"
			if (m_pFoundType != null && m_pFoundType.m_eType == AST.Type.AST_CLASS_DECL)
#line 172 "../../../Source/Core/AST/TypeRef.nll"
				return (ClassDecl)(m_pFoundType);
#line 173 "../../../Source/Core/AST/TypeRef.nll"
			return null;
		}

#line 176 "../../../Source/Core/AST/TypeRef.nll"
		protected void ValidateClassDecl(Validator pValidator, ClassDecl pClassDecl, TypeRef pThisOrChild)
		{
#line 178 "../../../Source/Core/AST/TypeRef.nll"
			if (m_pParent != null)
			{
#line 182 "../../../Source/Core/AST/TypeRef.nll"
				if (m_pParent.m_eType == AST.Type.AST_NEW_EXP)
				{
				}
				else
#line 187 "../../../Source/Core/AST/TypeRef.nll"
					if (m_pParent.m_eType == AST.Type.AST_TYPE_REF)
					{
						TypeRef pSubParentTypeRef = (TypeRef)(m_pParent);
#line 192 "../../../Source/Core/AST/TypeRef.nll"
						AddClassDeclReference(pClassDecl, AST.OutputFile.HEADER, true);
#line 195 "../../../Source/Core/AST/TypeRef.nll"
						if (pSubParentTypeRef.m_pChildTypeRef != this)
						{
							AST pParentParent = m_pParent.m_pParent;
#line 198 "../../../Source/Core/AST/TypeRef.nll"
							if (pParentParent != null)
							{
#line 200 "../../../Source/Core/AST/TypeRef.nll"
								if (pParentParent.m_eType == AST.Type.AST_NEW_EXP)
#line 201 "../../../Source/Core/AST/TypeRef.nll"
									AddClassDeclReference(pClassDecl, AST.OutputFile.SOURCE, false);
								AST pParentParentParent = pParentParent.m_pParent;
#line 204 "../../../Source/Core/AST/TypeRef.nll"
								if (pParentParentParent != null)
								{
#line 208 "../../../Source/Core/AST/TypeRef.nll"
									if (pParentParentParent.m_eType == AST.Type.AST_MEMBER_VAR_DECL)
#line 209 "../../../Source/Core/AST/TypeRef.nll"
										AddClassDeclReference(pClassDecl, AST.OutputFile.HEADER, false);
									else
#line 210 "../../../Source/Core/AST/TypeRef.nll"
										if (pParentParentParent.m_eType == AST.Type.AST_MEMBER_FUNCTION_DECL)
#line 211 "../../../Source/Core/AST/TypeRef.nll"
											AddClassDeclReference(pClassDecl, AST.OutputFile.HEADER, true);
										else
#line 213 "../../../Source/Core/AST/TypeRef.nll"
											AddClassDeclReference(pClassDecl, AST.OutputFile.SOURCE, true);
								}
							}
						}
					}
					else
					{
						AST.OutputFile eOutputFile = AST.OutputFile.SOURCE;
						bool bForwardReference = pThisOrChild.m_pChildTypeRef == null && m_pGenericTypeRefVector.GetSize() == 0;
						AST pParentParent = m_pParent.m_pParent;
#line 224 "../../../Source/Core/AST/TypeRef.nll"
						if (pParentParent != null)
						{
#line 226 "../../../Source/Core/AST/TypeRef.nll"
							if (pParentParent.m_eType == AST.Type.AST_MEMBER_VAR_DECL || pParentParent.m_eType == AST.Type.AST_MEMBER_FUNCTION_DECL)
							{
#line 228 "../../../Source/Core/AST/TypeRef.nll"
								eOutputFile = AST.OutputFile.HEADER;
							}
							else
							{
								AST pParentParentParent = pParentParent.m_pParent;
#line 233 "../../../Source/Core/AST/TypeRef.nll"
								if (pParentParentParent != null)
								{
									AST pParentParentParentParent = pParentParentParent.m_pParent;
#line 236 "../../../Source/Core/AST/TypeRef.nll"
									if (pParentParentParentParent != null)
									{
#line 238 "../../../Source/Core/AST/TypeRef.nll"
										if (m_pParent.m_eType == AST.Type.AST_VAR_DECL && pParentParent.m_eType == AST.Type.AST_PARAM_DECL && (pParentParentParent.m_eType == AST.Type.AST_FUNCTION_DECL && pParentParentParentParent.m_eType == AST.Type.AST_MEMBER_FUNCTION_DECL || pParentParentParent.m_eType == AST.Type.AST_TOR_DECL || (pParentParentParent.m_eType == AST.Type.AST_FUNCTION_DECL && pParentParentParentParent.m_eType == AST.Type.DELEGATE_DECL)))
#line 239 "../../../Source/Core/AST/TypeRef.nll"
											eOutputFile = AST.OutputFile.HEADER;
									}
								}
							}
						}
#line 245 "../../../Source/Core/AST/TypeRef.nll"
						AddClassDeclReference(pClassDecl, eOutputFile, bForwardReference);
					}
			}
		}

#line 250 "../../../Source/Core/AST/TypeRef.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
#line 252 "../../../Source/Core/AST/TypeRef.nll"
			if (m_pTypeToken.m_eType == Token.Type.TOKEN_IDENTIFIER)
			{
				AST pType = null;
				bool bResolverTypeAmbiguous = false;
				string sTypeName = m_pTypeToken.GetString();
				TypeRef pParentTypeRef = null;
#line 264 "../../../Source/Core/AST/TypeRef.nll"
				if (m_pParent != null && m_pParent.m_eType == AST.Type.AST_TYPE_REF)
				{
#line 266 "../../../Source/Core/AST/TypeRef.nll"
					pParentTypeRef = (TypeRef)(m_pParent);
#line 267 "../../../Source/Core/AST/TypeRef.nll"
					if (pParentTypeRef.m_pChildTypeRef != this)
#line 268 "../../../Source/Core/AST/TypeRef.nll"
						pParentTypeRef = null;
				}
				Vector<Symbol> pCandidates = new Vector<Symbol>();
				AST pResolverBase = this;
#line 273 "../../../Source/Core/AST/TypeRef.nll"
				if (pParentTypeRef != null && pParentTypeRef.m_pFoundType != null)
#line 274 "../../../Source/Core/AST/TypeRef.nll"
					pResolverBase = pParentTypeRef.m_pFoundType;
#line 275 "../../../Source/Core/AST/TypeRef.nll"
				pValidator.m_pResolver.ResolveFromNode(pResolverBase, sTypeName, pCandidates);
				Vector<Symbol> pTypeLike = new Vector<Symbol>();
#line 278 "../../../Source/Core/AST/TypeRef.nll"
				for (int i = 0; i < pCandidates.GetSize(); i++)
				{
					Symbol pSym = pCandidates.Get(i);
#line 281 "../../../Source/Core/AST/TypeRef.nll"
					if (pSym.m_eKind == Symbol.Kind.CLASS || pSym.m_eKind == Symbol.Kind.ENUM || pSym.m_eKind == Symbol.Kind.GENERIC_PARAM || pSym.m_eKind == Symbol.Kind.DELEGATE || pSym.m_eKind == Symbol.Kind.NAMESPACE)
					{
#line 287 "../../../Source/Core/AST/TypeRef.nll"
						pTypeLike.PushBack(pSym);
					}
				}
#line 291 "../../../Source/Core/AST/TypeRef.nll"
				if (pTypeLike.GetSize() == 1)
				{
					Symbol pSymbol = pTypeLike.Get(0);
#line 294 "../../../Source/Core/AST/TypeRef.nll"
					if (pSymbol.m_pDeclAST != null)
					{
#line 296 "../../../Source/Core/AST/TypeRef.nll"
						pType = pSymbol.m_pDeclAST;
#line 297 "../../../Source/Core/AST/TypeRef.nll"
						m_pFoundType = pType;
					}
				}
				else
#line 300 "../../../Source/Core/AST/TypeRef.nll"
					if (pTypeLike.GetSize() > 1)
#line 301 "../../../Source/Core/AST/TypeRef.nll"
						bResolverTypeAmbiguous = true;
#line 303 "../../../Source/Core/AST/TypeRef.nll"
				if (pType == null)
				{
#line 305 "../../../Source/Core/AST/TypeRef.nll"
					if (bResolverTypeAmbiguous)
					{
						InternalString sAmbiguous = new InternalString("Ambiguous type (multiple declarations in scope): ");
#line 308 "../../../Source/Core/AST/TypeRef.nll"
						sAmbiguous.Append(sTypeName);
#line 309 "../../../Source/Core/AST/TypeRef.nll"
						pValidator.AddError(sAmbiguous.GetExternalString(), m_pTypeToken.m_sFileName, m_pTypeToken.m_nLine, m_pTypeToken.m_nColumn);
					}
					else
					{
						InternalString sTemp = new InternalString("Unknown type: ");
#line 314 "../../../Source/Core/AST/TypeRef.nll"
						sTemp.Append(sTypeName);
						TypeRef pSubParentTypeRef = null;
#line 317 "../../../Source/Core/AST/TypeRef.nll"
						if (m_pParent.m_eType == AST.Type.AST_TYPE_REF)
						{
#line 319 "../../../Source/Core/AST/TypeRef.nll"
							pSubParentTypeRef = (TypeRef)(m_pParent);
#line 320 "../../../Source/Core/AST/TypeRef.nll"
							if (pSubParentTypeRef.m_pChildTypeRef != this)
#line 321 "../../../Source/Core/AST/TypeRef.nll"
								pSubParentTypeRef = null;
						}
#line 323 "../../../Source/Core/AST/TypeRef.nll"
						if (pSubParentTypeRef != null && pSubParentTypeRef.m_pFoundType != null)
#line 324 "../../../Source/Core/AST/TypeRef.nll"
							sTemp.Append(" -- had parent");
#line 326 "../../../Source/Core/AST/TypeRef.nll"
						pValidator.AddError(sTemp.GetExternalString(), m_pTypeToken.m_sFileName, m_pTypeToken.m_nLine, m_pTypeToken.m_nColumn);
					}
#line 328 "../../../Source/Core/AST/TypeRef.nll"
					return;
				}
#line 330 "../../../Source/Core/AST/TypeRef.nll"
				if (pType.m_eType == AST.Type.AST_CLASS_DECL)
				{
					ClassDecl pClassDecl = (ClassDecl)(pType);
#line 333 "../../../Source/Core/AST/TypeRef.nll"
					ValidateClassDecl(pValidator, pClassDecl, this);
#line 335 "../../../Source/Core/AST/TypeRef.nll"
					if (m_pChildTypeRef != null)
					{
#line 337 "../../../Source/Core/AST/TypeRef.nll"
						m_pChildTypeRef.Validate(pValidator, null);
					}
				}
				else
#line 340 "../../../Source/Core/AST/TypeRef.nll"
					if (pType.m_eType == AST.Type.NAMESPACE_DECL)
					{
#line 346 "../../../Source/Core/AST/TypeRef.nll"
						if (m_pChildTypeRef == null)
						{
#line 348 "../../../Source/Core/AST/TypeRef.nll"
							pValidator.AddError("Namespace typeref musttt have a child???", m_pTypeToken.m_sFileName, m_pTypeToken.m_nLine, m_pTypeToken.m_nColumn);
#line 349 "../../../Source/Core/AST/TypeRef.nll"
							return;
						}
#line 352 "../../../Source/Core/AST/TypeRef.nll"
						if (m_pChildTypeRef.m_pTypeToken.m_eType != Token.Type.TOKEN_IDENTIFIER)
						{
#line 354 "../../../Source/Core/AST/TypeRef.nll"
							pValidator.AddError("child must be IDENTIFIER", m_pChildTypeRef.m_pTypeToken.m_sFileName, m_pChildTypeRef.m_pTypeToken.m_nLine, m_pChildTypeRef.m_pTypeToken.m_nColumn);
#line 355 "../../../Source/Core/AST/TypeRef.nll"
							return;
						}
#line 358 "../../../Source/Core/AST/TypeRef.nll"
						m_pChildTypeRef.Validate(pValidator, null);
					}
					else
#line 361 "../../../Source/Core/AST/TypeRef.nll"
						if (pType.m_eType == AST.Type.AST_ENUM_DECL)
						{
						}
						else
#line 365 "../../../Source/Core/AST/TypeRef.nll"
							if (pType.m_eType == AST.Type.AST_MEMBER_CLASS_DECL)
							{
							}
							else
#line 370 "../../../Source/Core/AST/TypeRef.nll"
								if (pType.m_eType == AST.Type.AST_MEMBER_ENUM_DECL)
								{
								}
								else
#line 374 "../../../Source/Core/AST/TypeRef.nll"
									if (pType.m_eType == AST.Type.AST_GENERIC_TYPE_DECL)
									{
									}
									else
#line 378 "../../../Source/Core/AST/TypeRef.nll"
										if (pType.m_eType == AST.Type.DELEGATE_DECL)
										{
										}
										else
										{
											InternalString sTemp = new InternalString("Found type, but it's not a AST_CLASS_DECL, AST_MEMBER_CLASS_DECL, NAMESPACE_DECL, AST_ENUM_DECL, AST_MEMBER_ENUM_DECL, AST_GENERIC_TYPE_DECL or DELEGATE_DECL! Got: ");
#line 385 "../../../Source/Core/AST/TypeRef.nll"
											pType.StringifyType(sTemp);
#line 387 "../../../Source/Core/AST/TypeRef.nll"
											pValidator.AddError(sTemp.GetExternalString(), m_pTypeToken.m_sFileName, m_pTypeToken.m_nLine, m_pTypeToken.m_nColumn);
										}
			}
			else
			{
#line 393 "../../../Source/Core/AST/TypeRef.nll"
				if (m_pChildTypeRef != null)
				{
#line 395 "../../../Source/Core/AST/TypeRef.nll"
					pValidator.AddError("Not identifier but has child type ref???", m_pTypeToken.m_sFileName, m_pTypeToken.m_nLine, m_pTypeToken.m_nColumn);
#line 396 "../../../Source/Core/AST/TypeRef.nll"
					return;
				}
			}
#line 403 "../../../Source/Core/AST/TypeRef.nll"
			for (int i = 0; i < m_pGenericTypeRefVector.GetSize(); i++)
			{
				TypeRef pGenericTypeRef = m_pGenericTypeRefVector.Get(i);
#line 406 "../../../Source/Core/AST/TypeRef.nll"
				pGenericTypeRef.Validate(pValidator, null);
			}
#line 411 "../../../Source/Core/AST/TypeRef.nll"
			base.Validate(pValidator, pParent);
		}

#line 414 "../../../Source/Core/AST/TypeRef.nll"
		public TypeRef Clone()
		{
			TypeRef pTypeRef = new TypeRef();
#line 417 "../../../Source/Core/AST/TypeRef.nll"
			pTypeRef.m_pCloneToken = m_pTypeToken.Clone();
#line 418 "../../../Source/Core/AST/TypeRef.nll"
			pTypeRef.m_bConst = m_bConst;
#line 419 "../../../Source/Core/AST/TypeRef.nll"
			pTypeRef.m_pFirstToken = pTypeRef.m_pCloneToken;
#line 420 "../../../Source/Core/AST/TypeRef.nll"
			pTypeRef.m_pTypeToken = pTypeRef.m_pCloneToken;
#line 421 "../../../Source/Core/AST/TypeRef.nll"
			pTypeRef.m_pFoundType = m_pFoundType;
#line 423 "../../../Source/Core/AST/TypeRef.nll"
			for (int i = 0; i < m_pGenericTypeRefVector.GetSize(); i++)
			{
				TypeRef pGenericTypeRef = m_pGenericTypeRefVector.Get(i).Clone();
#line 426 "../../../Source/Core/AST/TypeRef.nll"
				pTypeRef.m_pGenericTypeRefVector.PushBack(pGenericTypeRef);
				NumbatLogic.TypeRef __3769232678 = pGenericTypeRef;
#line 427 "../../../Source/Core/AST/TypeRef.nll"
				pGenericTypeRef = null;
#line 427 "../../../Source/Core/AST/TypeRef.nll"
				pTypeRef.AddChild(__3769232678);
			}
#line 430 "../../../Source/Core/AST/TypeRef.nll"
			pTypeRef.m_pChildTypeRef = null;
#line 431 "../../../Source/Core/AST/TypeRef.nll"
			if (m_pChildTypeRef != null)
			{
				TypeRef pChildTypeRef = m_pChildTypeRef.Clone();
#line 434 "../../../Source/Core/AST/TypeRef.nll"
				pTypeRef.m_pChildTypeRef = pChildTypeRef;
				NumbatLogic.TypeRef __2008520584 = pChildTypeRef;
#line 435 "../../../Source/Core/AST/TypeRef.nll"
				pChildTypeRef = null;
#line 435 "../../../Source/Core/AST/TypeRef.nll"
				pTypeRef.AddChild(__2008520584);
			}
#line 438 "../../../Source/Core/AST/TypeRef.nll"
			pTypeRef.m_ePointerType = m_ePointerType;
			NumbatLogic.TypeRef __992497841 = pTypeRef;
#line 440 "../../../Source/Core/AST/TypeRef.nll"
			pTypeRef = null;
#line 440 "../../../Source/Core/AST/TypeRef.nll"
			return __992497841;
		}

#line 443 "../../../Source/Core/AST/TypeRef.nll"
		public override AST BaseClone()
		{
#line 445 "../../../Source/Core/AST/TypeRef.nll"
			return Clone();
		}

#line 448 "../../../Source/Core/AST/TypeRef.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 450 "../../../Source/Core/AST/TypeRef.nll"
			if (m_bConst)
			{
				bool bOutput = true;
#line 455 "../../../Source/Core/AST/TypeRef.nll"
				if (eLanguage == AST.Language.CS)
				{
#line 457 "../../../Source/Core/AST/TypeRef.nll"
					bOutput = false;
					Project pProject = GetProject();
#line 459 "../../../Source/Core/AST/TypeRef.nll"
					if (pProject != null && pProject.m_pValidator != null)
					{
						ValueType pValueType = GetRecursiveValueType(pProject.m_pValidator.m_pResolver);
#line 463 "../../../Source/Core/AST/TypeRef.nll"
						switch (pValueType.m_eType)
						{
							case ValueType.Type.INT:
							case ValueType.Type.BOOL:
							case ValueType.Type.CHAR:
							case ValueType.Type.UNICHAR:
							case ValueType.Type.ENUM_DECL_VALUE:
							{
#line 472 "../../../Source/Core/AST/TypeRef.nll"
								bOutput = true;
#line 473 "../../../Source/Core/AST/TypeRef.nll"
								break;
							}

						}
					}
				}
#line 479 "../../../Source/Core/AST/TypeRef.nll"
				if (bOutput)
#line 480 "../../../Source/Core/AST/TypeRef.nll"
					pOutputBuilder.m_sOut.AppendString("const ");
			}
#line 485 "../../../Source/Core/AST/TypeRef.nll"
			if (eLanguage == AST.Language.CPP)
			{
#line 487 "../../../Source/Core/AST/TypeRef.nll"
				if (m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_UNICHAR)
#line 488 "../../../Source/Core/AST/TypeRef.nll"
					pOutputBuilder.m_sOut.Append("unsigned short");
				else
#line 489 "../../../Source/Core/AST/TypeRef.nll"
					if (m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_STRING)
					{
#line 491 "../../../Source/Core/AST/TypeRef.nll"
						if (m_bConst)
#line 492 "../../../Source/Core/AST/TypeRef.nll"
							pOutputBuilder.m_sOut.Append("char*");
						else
#line 494 "../../../Source/Core/AST/TypeRef.nll"
							pOutputBuilder.m_sOut.Append("const char*");
					}
					else
#line 496 "../../../Source/Core/AST/TypeRef.nll"
						if (m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_UINT)
#line 497 "../../../Source/Core/AST/TypeRef.nll"
							pOutputBuilder.m_sOut.Append("unsigned int");
						else
#line 498 "../../../Source/Core/AST/TypeRef.nll"
							if (m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_UINT8)
#line 499 "../../../Source/Core/AST/TypeRef.nll"
								pOutputBuilder.m_sOut.Append("unsigned char");
							else
#line 500 "../../../Source/Core/AST/TypeRef.nll"
								if (m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_UINT16)
#line 501 "../../../Source/Core/AST/TypeRef.nll"
									pOutputBuilder.m_sOut.Append("unsigned short");
								else
#line 502 "../../../Source/Core/AST/TypeRef.nll"
									if (m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_UINT32)
#line 503 "../../../Source/Core/AST/TypeRef.nll"
										pOutputBuilder.m_sOut.Append("unsigned int");
									else
#line 504 "../../../Source/Core/AST/TypeRef.nll"
										if (m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_UINT64)
#line 505 "../../../Source/Core/AST/TypeRef.nll"
											pOutputBuilder.m_sOut.Append("unsigned long long");
										else
#line 506 "../../../Source/Core/AST/TypeRef.nll"
											if (m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_INT32)
#line 507 "../../../Source/Core/AST/TypeRef.nll"
												pOutputBuilder.m_sOut.Append("int");
											else
#line 508 "../../../Source/Core/AST/TypeRef.nll"
												if (m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_INT16)
#line 509 "../../../Source/Core/AST/TypeRef.nll"
													pOutputBuilder.m_sOut.Append("short");
												else
#line 510 "../../../Source/Core/AST/TypeRef.nll"
													if (m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_INT8)
#line 511 "../../../Source/Core/AST/TypeRef.nll"
														pOutputBuilder.m_sOut.Append("signed char");
													else
#line 512 "../../../Source/Core/AST/TypeRef.nll"
														if (m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_VOIDPTR)
#line 513 "../../../Source/Core/AST/TypeRef.nll"
															pOutputBuilder.m_sOut.Append("void*");
														else
#line 515 "../../../Source/Core/AST/TypeRef.nll"
															m_pTypeToken.Stringify(pOutputBuilder.m_sOut);
#line 517 "../../../Source/Core/AST/TypeRef.nll"
				if (m_bRef)
#line 518 "../../../Source/Core/AST/TypeRef.nll"
					pOutputBuilder.m_sOut.AppendString("&");
			}
			else
#line 520 "../../../Source/Core/AST/TypeRef.nll"
				if (eLanguage == AST.Language.CS)
				{
#line 522 "../../../Source/Core/AST/TypeRef.nll"
					if (m_bRef && eLanguage == AST.Language.CS)
#line 523 "../../../Source/Core/AST/TypeRef.nll"
						pOutputBuilder.m_sOut.AppendString("ref ");
#line 525 "../../../Source/Core/AST/TypeRef.nll"
					switch (m_pTypeToken.m_eType)
					{
						case Token.Type.TOKEN_KEYWORD_UNICHAR:
						{
#line 527 "../../../Source/Core/AST/TypeRef.nll"
							pOutputBuilder.m_sOut.Append("char");
#line 527 "../../../Source/Core/AST/TypeRef.nll"
							break;
						}

						case Token.Type.TOKEN_KEYWORD_STRING:
						{
#line 528 "../../../Source/Core/AST/TypeRef.nll"
							pOutputBuilder.m_sOut.Append("string");
#line 528 "../../../Source/Core/AST/TypeRef.nll"
							break;
						}

						case Token.Type.TOKEN_KEYWORD_VOIDPTR:
						{
#line 529 "../../../Source/Core/AST/TypeRef.nll"
							pOutputBuilder.m_sOut.Append("object");
#line 529 "../../../Source/Core/AST/TypeRef.nll"
							break;
						}

						case Token.Type.TOKEN_KEYWORD_UINT8:
						{
#line 530 "../../../Source/Core/AST/TypeRef.nll"
							pOutputBuilder.m_sOut.Append("byte");
#line 530 "../../../Source/Core/AST/TypeRef.nll"
							break;
						}

						case Token.Type.TOKEN_KEYWORD_UINT16:
						{
#line 531 "../../../Source/Core/AST/TypeRef.nll"
							pOutputBuilder.m_sOut.Append("ushort");
#line 531 "../../../Source/Core/AST/TypeRef.nll"
							break;
						}

						case Token.Type.TOKEN_KEYWORD_UINT32:
						{
#line 532 "../../../Source/Core/AST/TypeRef.nll"
							pOutputBuilder.m_sOut.Append("uint");
#line 532 "../../../Source/Core/AST/TypeRef.nll"
							break;
						}

						case Token.Type.TOKEN_KEYWORD_UINT64:
						{
#line 533 "../../../Source/Core/AST/TypeRef.nll"
							pOutputBuilder.m_sOut.Append("ulong");
#line 533 "../../../Source/Core/AST/TypeRef.nll"
							break;
						}

						case Token.Type.TOKEN_KEYWORD_INT8:
						{
#line 534 "../../../Source/Core/AST/TypeRef.nll"
							pOutputBuilder.m_sOut.Append("sbyte");
#line 534 "../../../Source/Core/AST/TypeRef.nll"
							break;
						}

						case Token.Type.TOKEN_KEYWORD_INT16:
						{
#line 535 "../../../Source/Core/AST/TypeRef.nll"
							pOutputBuilder.m_sOut.Append("short");
#line 535 "../../../Source/Core/AST/TypeRef.nll"
							break;
						}

						case Token.Type.TOKEN_KEYWORD_INT32:
						{
#line 536 "../../../Source/Core/AST/TypeRef.nll"
							pOutputBuilder.m_sOut.Append("int");
#line 536 "../../../Source/Core/AST/TypeRef.nll"
							break;
						}

						default:
						{
#line 540 "../../../Source/Core/AST/TypeRef.nll"
							m_pTypeToken.Stringify(pOutputBuilder.m_sOut);
#line 541 "../../../Source/Core/AST/TypeRef.nll"
							break;
						}

					}
				}
				else
				{
#line 549 "../../../Source/Core/AST/TypeRef.nll"
					m_pTypeToken.Stringify(pOutputBuilder.m_sOut);
				}
#line 553 "../../../Source/Core/AST/TypeRef.nll"
			if (m_pGenericTypeRefVector.GetSize() > 0)
			{
#line 555 "../../../Source/Core/AST/TypeRef.nll"
				pOutputBuilder.m_sOut.AppendChar('<');
#line 556 "../../../Source/Core/AST/TypeRef.nll"
				for (int i = 0; i < m_pGenericTypeRefVector.GetSize(); i++)
				{
#line 558 "../../../Source/Core/AST/TypeRef.nll"
					if (i > 0)
#line 559 "../../../Source/Core/AST/TypeRef.nll"
						pOutputBuilder.m_sOut.Append(", ");
					TypeRef pGenericTypeRef = m_pGenericTypeRefVector.Get(i);
#line 561 "../../../Source/Core/AST/TypeRef.nll"
					pGenericTypeRef.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
				}
#line 563 "../../../Source/Core/AST/TypeRef.nll"
				if (eLanguage == AST.Language.NLL_DEF)
#line 564 "../../../Source/Core/AST/TypeRef.nll"
					pOutputBuilder.m_sOut.AppendChar('!');
#line 565 "../../../Source/Core/AST/TypeRef.nll"
				pOutputBuilder.m_sOut.AppendChar('>');
			}
#line 568 "../../../Source/Core/AST/TypeRef.nll"
			if (m_pChildTypeRef != null)
			{
#line 570 "../../../Source/Core/AST/TypeRef.nll"
				switch (eLanguage)
				{
					case AST.Language.NLL:
					case AST.Language.NLL_DEF:
					case AST.Language.CPP:
					{
#line 576 "../../../Source/Core/AST/TypeRef.nll"
						pOutputBuilder.m_sOut.Append("::");
#line 577 "../../../Source/Core/AST/TypeRef.nll"
						break;
					}

					case AST.Language.CS:
					{
#line 581 "../../../Source/Core/AST/TypeRef.nll"
						pOutputBuilder.m_sOut.AppendChar('.');
#line 582 "../../../Source/Core/AST/TypeRef.nll"
						break;
					}

				}
#line 585 "../../../Source/Core/AST/TypeRef.nll"
				m_pChildTypeRef.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			}
			TypeRef pFinalChildTypeRef = this;
#line 589 "../../../Source/Core/AST/TypeRef.nll"
			while (pFinalChildTypeRef.m_pChildTypeRef != null)
			{
#line 591 "../../../Source/Core/AST/TypeRef.nll"
				pFinalChildTypeRef = pFinalChildTypeRef.m_pChildTypeRef;
			}
#line 594 "../../../Source/Core/AST/TypeRef.nll"
			if (pFinalChildTypeRef.m_pTypeToken.m_eType == Token.Type.TOKEN_IDENTIFIER)
			{
				string sTypeName = pFinalChildTypeRef.m_pTypeToken.GetString();
				AST pType = pFinalChildTypeRef.m_pFoundType;
				string sxAppendString = "";
#line 602 "../../../Source/Core/AST/TypeRef.nll"
				if (eLanguage == AST.Language.CPP && pType != null && pType.m_eType == AST.Type.AST_CLASS_DECL)
#line 603 "../../../Source/Core/AST/TypeRef.nll"
					sxAppendString = "*";
#line 605 "../../../Source/Core/AST/TypeRef.nll"
				if (eLanguage == AST.Language.CPP && pType != null && pType.m_eType == AST.Type.DELEGATE_DECL)
#line 606 "../../../Source/Core/AST/TypeRef.nll"
					sxAppendString = "*";
#line 613 "../../../Source/Core/AST/TypeRef.nll"
				if (m_pParent != null)
				{
#line 615 "../../../Source/Core/AST/TypeRef.nll"
					if (m_pParent.m_eType == AST.Type.AST_NEW_EXP)
#line 616 "../../../Source/Core/AST/TypeRef.nll"
						sxAppendString = "";
#line 618 "../../../Source/Core/AST/TypeRef.nll"
					if (m_pParent.m_eType == AST.Type.AST_TYPE_REF)
					{
						TypeRef pParentTypeRef = (TypeRef)(m_pParent);
#line 621 "../../../Source/Core/AST/TypeRef.nll"
						if (pParentTypeRef.m_pChildTypeRef == this)
#line 622 "../../../Source/Core/AST/TypeRef.nll"
							sxAppendString = "";
					}
#line 625 "../../../Source/Core/AST/TypeRef.nll"
					if (m_pParent.m_eType == AST.Type.AST_CLASS_DECL)
					{
						ClassDecl pParentClassDecl = (ClassDecl)(m_pParent);
#line 628 "../../../Source/Core/AST/TypeRef.nll"
						if (pParentClassDecl.m_pBaseTypeRef == this)
#line 629 "../../../Source/Core/AST/TypeRef.nll"
							sxAppendString = "";
					}
#line 632 "../../../Source/Core/AST/TypeRef.nll"
					pOutputBuilder.m_sOut.AppendString(sxAppendString);
				}
			}
		}

#line 637 "../../../Source/Core/AST/TypeRef.nll"
		public ValueType GetRecursiveValueType(Resolver pResolver)
		{
#line 639 "../../../Source/Core/AST/TypeRef.nll"
			if (m_pValueType == null)
#line 640 "../../../Source/Core/AST/TypeRef.nll"
				SetValueType(pResolver);
#line 642 "../../../Source/Core/AST/TypeRef.nll"
			if (m_pChildTypeRef != null)
#line 643 "../../../Source/Core/AST/TypeRef.nll"
				return m_pChildTypeRef.GetRecursiveValueType(pResolver);
#line 645 "../../../Source/Core/AST/TypeRef.nll"
			return m_pValueType;
		}

#line 649 "../../../Source/Core/AST/TypeRef.nll"
		public ValueType CreateValueType(Resolver pResolver)
		{
#line 651 "../../../Source/Core/AST/TypeRef.nll"
			if (m_pValueType == null)
#line 652 "../../../Source/Core/AST/TypeRef.nll"
				SetValueType(pResolver);
#line 654 "../../../Source/Core/AST/TypeRef.nll"
			if (m_pChildTypeRef != null)
#line 655 "../../../Source/Core/AST/TypeRef.nll"
				return m_pChildTypeRef.CreateValueType(pResolver);
#line 657 "../../../Source/Core/AST/TypeRef.nll"
			if (m_pValueType != null)
#line 658 "../../../Source/Core/AST/TypeRef.nll"
				return m_pValueType.Clone();
#line 660 "../../../Source/Core/AST/TypeRef.nll"
			return null;
		}

#line 663 "../../../Source/Core/AST/TypeRef.nll"
		protected ValueType SetValueType(Resolver pResolver)
		{
#line 667 "../../../Source/Core/AST/TypeRef.nll"
			switch (m_pTypeToken.m_eType)
			{
				case Token.Type.TOKEN_IDENTIFIER:
				{
					AST pType = m_pFoundType;
#line 673 "../../../Source/Core/AST/TypeRef.nll"
					if (pType == null && pResolver != null)
					{
						string sTypeName = m_pTypeToken.GetString();
						TypeRef pParentTypeRef = null;
#line 678 "../../../Source/Core/AST/TypeRef.nll"
						if (m_pParent != null && m_pParent.m_eType == AST.Type.AST_TYPE_REF)
						{
#line 680 "../../../Source/Core/AST/TypeRef.nll"
							pParentTypeRef = (TypeRef)(m_pParent);
#line 681 "../../../Source/Core/AST/TypeRef.nll"
							if (pParentTypeRef.m_pChildTypeRef != this)
#line 682 "../../../Source/Core/AST/TypeRef.nll"
								pParentTypeRef = null;
						}
						Vector<Symbol> pCandidates = new Vector<Symbol>();
						AST pResolverBase = this;
#line 686 "../../../Source/Core/AST/TypeRef.nll"
						if (pParentTypeRef != null && pParentTypeRef.m_pFoundType != null)
#line 687 "../../../Source/Core/AST/TypeRef.nll"
							pResolverBase = pParentTypeRef.m_pFoundType;
#line 688 "../../../Source/Core/AST/TypeRef.nll"
						pResolver.ResolveFromNode(pResolverBase, sTypeName, pCandidates);
						Vector<Symbol> pTypeLike = new Vector<Symbol>();
#line 690 "../../../Source/Core/AST/TypeRef.nll"
						for (int i = 0; i < pCandidates.GetSize(); i++)
						{
							Symbol pSym = pCandidates.Get(i);
#line 693 "../../../Source/Core/AST/TypeRef.nll"
							if (pSym.m_eKind == Symbol.Kind.CLASS || pSym.m_eKind == Symbol.Kind.ENUM || pSym.m_eKind == Symbol.Kind.GENERIC_PARAM || pSym.m_eKind == Symbol.Kind.DELEGATE || pSym.m_eKind == Symbol.Kind.NAMESPACE)
							{
#line 699 "../../../Source/Core/AST/TypeRef.nll"
								pTypeLike.PushBack(pSym);
							}
						}
#line 702 "../../../Source/Core/AST/TypeRef.nll"
						if (pTypeLike.GetSize() == 1)
						{
							Symbol pSymbol = pTypeLike.Get(0);
#line 705 "../../../Source/Core/AST/TypeRef.nll"
							if (pSymbol.m_pDeclAST != null)
							{
#line 707 "../../../Source/Core/AST/TypeRef.nll"
								pType = pSymbol.m_pDeclAST;
#line 708 "../../../Source/Core/AST/TypeRef.nll"
								m_pFoundType = pType;
							}
						}
					}
#line 713 "../../../Source/Core/AST/TypeRef.nll"
					if (pType != null)
					{
#line 715 "../../../Source/Core/AST/TypeRef.nll"
						if (pType.m_eType == AST.Type.AST_CLASS_DECL)
						{
#line 717 "../../../Source/Core/AST/TypeRef.nll"
							m_pValueType = new ValueType(ValueType.Type.CLASS_DECL_VALUE);
#line 718 "../../../Source/Core/AST/TypeRef.nll"
							m_pValueType.m_bConst = m_bConst;
#line 719 "../../../Source/Core/AST/TypeRef.nll"
							m_pValueType.m_pClassDecl = (ClassDecl)(pType);
#line 720 "../../../Source/Core/AST/TypeRef.nll"
							m_pValueType.m_ePointerType = m_ePointerType;
#line 724 "../../../Source/Core/AST/TypeRef.nll"
							for (int i = 0; i < m_pGenericTypeRefVector.GetSize(); i++)
							{
								TypeRef pGenericTypeRef = m_pGenericTypeRefVector.Get(i);
								ValueType pGenericValueType = pGenericTypeRef.CreateValueType(pResolver);
#line 729 "../../../Source/Core/AST/TypeRef.nll"
								if (pGenericValueType == null)
								{
#line 730 "../../../Source/Core/AST/TypeRef.nll"
									return null;
								}
								NumbatLogic.ValueType __2199059312 = pGenericValueType;
#line 731 "../../../Source/Core/AST/TypeRef.nll"
								pGenericValueType = null;
#line 731 "../../../Source/Core/AST/TypeRef.nll"
								m_pValueType.m_pGenericValueTypeVector.PushBack(__2199059312);
							}
#line 734 "../../../Source/Core/AST/TypeRef.nll"
							return m_pValueType;
						}
#line 737 "../../../Source/Core/AST/TypeRef.nll"
						if (pType.m_eType == AST.Type.AST_MEMBER_CLASS_DECL)
						{
							MemberClassDecl pMemberClass = (MemberClassDecl)(pType);
#line 740 "../../../Source/Core/AST/TypeRef.nll"
							if (pMemberClass.m_pClassDecl != null)
							{
#line 742 "../../../Source/Core/AST/TypeRef.nll"
								m_pValueType = new ValueType(ValueType.Type.CLASS_DECL_VALUE);
#line 743 "../../../Source/Core/AST/TypeRef.nll"
								m_pValueType.m_bConst = m_bConst;
#line 744 "../../../Source/Core/AST/TypeRef.nll"
								m_pValueType.m_pClassDecl = pMemberClass.m_pClassDecl;
#line 745 "../../../Source/Core/AST/TypeRef.nll"
								m_pValueType.m_ePointerType = m_ePointerType;
#line 747 "../../../Source/Core/AST/TypeRef.nll"
								for (int i = 0; i < m_pGenericTypeRefVector.GetSize(); i++)
								{
									TypeRef pGenericTypeRef = m_pGenericTypeRefVector.Get(i);
									ValueType pGenericValueType = pGenericTypeRef.CreateValueType(pResolver);
#line 751 "../../../Source/Core/AST/TypeRef.nll"
									if (pGenericValueType == null)
									{
#line 752 "../../../Source/Core/AST/TypeRef.nll"
										return null;
									}
									NumbatLogic.ValueType __2199190512 = pGenericValueType;
#line 753 "../../../Source/Core/AST/TypeRef.nll"
									pGenericValueType = null;
#line 753 "../../../Source/Core/AST/TypeRef.nll"
									m_pValueType.m_pGenericValueTypeVector.PushBack(__2199190512);
								}
#line 756 "../../../Source/Core/AST/TypeRef.nll"
								return m_pValueType;
							}
						}
#line 760 "../../../Source/Core/AST/TypeRef.nll"
						if (pType.m_eType == AST.Type.AST_GENERIC_TYPE_DECL)
						{
#line 762 "../../../Source/Core/AST/TypeRef.nll"
							m_pValueType = new ValueType(ValueType.Type.GENERIC_TYPE_DECL_VALUE);
#line 763 "../../../Source/Core/AST/TypeRef.nll"
							m_pValueType.m_bConst = m_bConst;
#line 764 "../../../Source/Core/AST/TypeRef.nll"
							m_pValueType.m_pGenericTypeDecl = (GenericTypeDecl)(pType);
#line 765 "../../../Source/Core/AST/TypeRef.nll"
							m_pValueType.m_ePointerType = m_ePointerType;
#line 766 "../../../Source/Core/AST/TypeRef.nll"
							return m_pValueType;
						}
#line 769 "../../../Source/Core/AST/TypeRef.nll"
						if (pType.m_eType == AST.Type.AST_ENUM_DECL)
						{
#line 771 "../../../Source/Core/AST/TypeRef.nll"
							m_pValueType = new ValueType(ValueType.Type.ENUM_DECL_VALUE);
#line 772 "../../../Source/Core/AST/TypeRef.nll"
							m_pValueType.m_bConst = m_bConst;
#line 773 "../../../Source/Core/AST/TypeRef.nll"
							m_pValueType.m_pEnumDecl = (EnumDecl)(pType);
#line 774 "../../../Source/Core/AST/TypeRef.nll"
							return m_pValueType;
						}
#line 777 "../../../Source/Core/AST/TypeRef.nll"
						if (pType.m_eType == AST.Type.AST_MEMBER_ENUM_DECL)
						{
							MemberEnumDecl pMemberEnum = (MemberEnumDecl)(pType);
#line 780 "../../../Source/Core/AST/TypeRef.nll"
							if (pMemberEnum.m_pEnumDecl != null)
							{
#line 782 "../../../Source/Core/AST/TypeRef.nll"
								m_pValueType = new ValueType(ValueType.Type.ENUM_DECL_VALUE);
#line 783 "../../../Source/Core/AST/TypeRef.nll"
								m_pValueType.m_bConst = m_bConst;
#line 784 "../../../Source/Core/AST/TypeRef.nll"
								m_pValueType.m_pEnumDecl = pMemberEnum.m_pEnumDecl;
#line 785 "../../../Source/Core/AST/TypeRef.nll"
								m_pValueType.m_ePointerType = m_ePointerType;
#line 786 "../../../Source/Core/AST/TypeRef.nll"
								return m_pValueType;
							}
						}
#line 790 "../../../Source/Core/AST/TypeRef.nll"
						if (pType.m_eType == AST.Type.ENUM_DECL_VALUE)
						{
#line 792 "../../../Source/Core/AST/TypeRef.nll"
							m_pValueType = new ValueType(ValueType.Type.ENUM_DECL_VALUE);
#line 793 "../../../Source/Core/AST/TypeRef.nll"
							m_pValueType.m_bConst = m_bConst;
#line 794 "../../../Source/Core/AST/TypeRef.nll"
							m_pValueType.m_pEnumDeclValue = (EnumDeclValue)(pType);
#line 795 "../../../Source/Core/AST/TypeRef.nll"
							return m_pValueType;
						}
#line 798 "../../../Source/Core/AST/TypeRef.nll"
						if (pType.m_eType == AST.Type.DELEGATE_DECL)
						{
#line 800 "../../../Source/Core/AST/TypeRef.nll"
							m_pValueType = new ValueType(ValueType.Type.DELEGATE_DECL_VALUE);
#line 801 "../../../Source/Core/AST/TypeRef.nll"
							m_pValueType.m_bConst = m_bConst;
#line 802 "../../../Source/Core/AST/TypeRef.nll"
							m_pValueType.m_pDelegateDecl = (DelegateDecl)(pType);
#line 803 "../../../Source/Core/AST/TypeRef.nll"
							return m_pValueType;
						}
					}
#line 807 "../../../Source/Core/AST/TypeRef.nll"
					return null;
				}

				case Token.Type.TOKEN_KEYWORD_INT:
				case Token.Type.TOKEN_KEYWORD_UINT:
				case Token.Type.TOKEN_KEYWORD_UINT8:
				case Token.Type.TOKEN_KEYWORD_UINT16:
				case Token.Type.TOKEN_KEYWORD_UINT32:
				case Token.Type.TOKEN_KEYWORD_UINT64:
				case Token.Type.TOKEN_KEYWORD_INT8:
				case Token.Type.TOKEN_KEYWORD_INT16:
				case Token.Type.TOKEN_KEYWORD_INT32:
				case Token.Type.TOKEN_KEYWORD_DOUBLE:
				case Token.Type.TOKEN_KEYWORD_FLOAT:
				{
#line 821 "../../../Source/Core/AST/TypeRef.nll"
					m_pValueType = new ValueType(ValueType.Type.INT);
#line 822 "../../../Source/Core/AST/TypeRef.nll"
					m_pValueType.m_bConst = m_bConst;
#line 823 "../../../Source/Core/AST/TypeRef.nll"
					return m_pValueType;
				}

				case Token.Type.TOKEN_KEYWORD_STRING:
				{
#line 827 "../../../Source/Core/AST/TypeRef.nll"
					m_pValueType = new ValueType(ValueType.Type.STRING);
#line 828 "../../../Source/Core/AST/TypeRef.nll"
					m_pValueType.m_bConst = m_bConst;
#line 829 "../../../Source/Core/AST/TypeRef.nll"
					return m_pValueType;
				}

				case Token.Type.TOKEN_KEYWORD_BOOL:
				{
#line 833 "../../../Source/Core/AST/TypeRef.nll"
					m_pValueType = new ValueType(ValueType.Type.BOOL);
#line 834 "../../../Source/Core/AST/TypeRef.nll"
					m_pValueType.m_bConst = m_bConst;
#line 835 "../../../Source/Core/AST/TypeRef.nll"
					return m_pValueType;
				}

				case Token.Type.TOKEN_KEYWORD_UNICHAR:
				{
#line 839 "../../../Source/Core/AST/TypeRef.nll"
					m_pValueType = new ValueType(ValueType.Type.UNICHAR);
#line 840 "../../../Source/Core/AST/TypeRef.nll"
					m_pValueType.m_bConst = m_bConst;
#line 841 "../../../Source/Core/AST/TypeRef.nll"
					return m_pValueType;
				}

				case Token.Type.TOKEN_KEYWORD_VOID:
				{
#line 845 "../../../Source/Core/AST/TypeRef.nll"
					m_pValueType = new ValueType(ValueType.Type.VOID);
#line 846 "../../../Source/Core/AST/TypeRef.nll"
					m_pValueType.m_bConst = m_bConst;
#line 847 "../../../Source/Core/AST/TypeRef.nll"
					return m_pValueType;
				}

				case Token.Type.TOKEN_KEYWORD_VOIDPTR:
				{
#line 851 "../../../Source/Core/AST/TypeRef.nll"
					m_pValueType = new ValueType(ValueType.Type.VOIDPTR);
#line 852 "../../../Source/Core/AST/TypeRef.nll"
					m_pValueType.m_bConst = m_bConst;
#line 853 "../../../Source/Core/AST/TypeRef.nll"
					return m_pValueType;
				}

			}
#line 856 "../../../Source/Core/AST/TypeRef.nll"
			return null;
		}

#line 859 "../../../Source/Core/AST/TypeRef.nll"
		public bool IsIntegral()
		{
			Project pProject = GetProject();
#line 862 "../../../Source/Core/AST/TypeRef.nll"
			if (pProject == null || pProject.m_pValidator == null)
#line 863 "../../../Source/Core/AST/TypeRef.nll"
				return IsInt() || IsBool() || m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_UNICHAR;
			ValueType pValueType = GetRecursiveValueType(pProject.m_pValidator.m_pResolver);
#line 865 "../../../Source/Core/AST/TypeRef.nll"
			if (pValueType.m_eType == ValueType.Type.ENUM_DECL_VALUE)
#line 866 "../../../Source/Core/AST/TypeRef.nll"
				return true;
#line 867 "../../../Source/Core/AST/TypeRef.nll"
			return IsInt() || IsBool() || m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_UNICHAR;
		}

#line 871 "../../../Source/Core/AST/TypeRef.nll"
		public bool IsInt()
		{
#line 873 "../../../Source/Core/AST/TypeRef.nll"
			return m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_INT || m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_UINT || m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_UINT8 || m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_UINT16 || m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_UINT32 || m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_UINT64 || m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_INT8 || m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_INT16 || m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_INT32;
		}

#line 884 "../../../Source/Core/AST/TypeRef.nll"
		public bool IsBool()
		{
#line 886 "../../../Source/Core/AST/TypeRef.nll"
			return m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_BOOL;
		}

#line 889 "../../../Source/Core/AST/TypeRef.nll"
		public bool IsFloat()
		{
#line 891 "../../../Source/Core/AST/TypeRef.nll"
			return m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_FLOAT;
		}

#line 894 "../../../Source/Core/AST/TypeRef.nll"
		public bool IsDouble()
		{
#line 896 "../../../Source/Core/AST/TypeRef.nll"
			return m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_DOUBLE;
		}

#line 4 "../../../Source/Core/AST/TypeRef.nll"
		~TypeRef()
		{
		}

	}
}

