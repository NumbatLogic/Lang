namespace NumbatLogic
{
	class TypeRef : AST
	{
		public enum PointerType
		{
			SHARED,
			OWNED,
			TRANSITON,
			OWNED_PREASSSIGN,
		}

		public bool m_bConst;
		public bool m_bRef;
		public Token m_pTypeToken;
		public Vector<TypeRef> m_pGenericTypeRefVector;
		public TypeRef m_pChildTypeRef;
		public PointerType m_ePointerType;
		public Token m_pCloneToken;
		public AST m_pFoundType;
		public TypeRef()
		{
			m_eType = AST.Type.AST_TYPE_REF;
			m_pGenericTypeRefVector = new Vector<TypeRef>();
			m_bConst = false;
			m_bRef = false;
		}

		public static TypeRef TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			bool bConst = false;
			Token pConstToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_CONST);
			if (pConstToken != null)
			{
				bConst = true;
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			}
			bool bRef = false;
			Token pRefToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_REF);
			if (pRefToken != null)
			{
				bRef = true;
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			}
			Token pTypeToken = pTokenContainer.Peek(pTempOffset);
			if (pTypeToken == null || pTypeToken.m_eType != Token.Type.TOKEN_KEYWORD_VOID && pTypeToken.m_eType != Token.Type.TOKEN_KEYWORD_INT && pTypeToken.m_eType != Token.Type.TOKEN_KEYWORD_BOOL && pTypeToken.m_eType != Token.Type.TOKEN_KEYWORD_UNICHAR && pTypeToken.m_eType != Token.Type.TOKEN_KEYWORD_STRING && pTypeToken.m_eType != Token.Type.TOKEN_KEYWORD_UINT && pTypeToken.m_eType != Token.Type.TOKEN_KEYWORD_UINT8 && pTypeToken.m_eType != Token.Type.TOKEN_KEYWORD_UINT16 && pTypeToken.m_eType != Token.Type.TOKEN_KEYWORD_UINT32 && pTypeToken.m_eType != Token.Type.TOKEN_KEYWORD_UINT64 && pTypeToken.m_eType != Token.Type.TOKEN_KEYWORD_INT8 && pTypeToken.m_eType != Token.Type.TOKEN_KEYWORD_INT16 && pTypeToken.m_eType != Token.Type.TOKEN_KEYWORD_INT32 && pTypeToken.m_eType != Token.Type.TOKEN_KEYWORD_DOUBLE && pTypeToken.m_eType != Token.Type.TOKEN_KEYWORD_FLOAT && pTypeToken.m_eType != Token.Type.TOKEN_KEYWORD_VOIDPTR && pTypeToken.m_eType != Token.Type.TOKEN_IDENTIFIER)
			{
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			TypeRef pTypeRef = new TypeRef();
			pTypeRef.m_pFirstToken = pTypeToken;
			if (pConstToken != null)
				pTypeRef.m_pFirstToken = pConstToken;
			pTypeRef.m_bConst = bConst;
			pTypeRef.m_pTypeToken = pTypeToken;
			pTypeRef.m_pChildTypeRef = null;
			pTypeRef.m_ePointerType = PointerType.SHARED;
			pTypeRef.m_bRef = bRef;
			if (pTypeToken.m_eType == Token.Type.TOKEN_IDENTIFIER)
			{
				Token pAngleBracketLeft = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_ANGLE_BRACKET_LEFT);
				if (pAngleBracketLeft != null)
				{
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
					while (true)
					{
						if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_ANGLE_BRACKET_RIGHT) != null)
						{
							pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
							break;
						}
						TypeRef pGenericTypeRef = TypeRef.TryCreate(pTokenContainer, pTempOffset);
						if (pGenericTypeRef == null)
						{
							Console.Log("expected inner TypeRef");
							Assert.Plz(false);
						}
						pTypeRef.m_pGenericTypeRefVector.PushBack(pGenericTypeRef);
						NumbatLogic.TypeRef __3744382558 = pGenericTypeRef;
						pGenericTypeRef = null;
						pTypeRef.AddChild(__3744382558);
						if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_ANGLE_BRACKET_RIGHT) != null)
						{
							continue;
						}
						if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_COMMA) == null)
						{
							InternalString sTemp = new InternalString("expected comma ");
							sTemp.Append(pTokenContainer.StringifyOffset(pTempOffset));
							Console.Log(sTemp.GetExternalString());
							Assert.Plz(false);
						}
						pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
					}
				}
			}
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_DOUBLE_COLON) != null)
			{
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
				TypeRef pChildTypeRef = TypeRef.TryCreate(pTokenContainer, pTempOffset);
				if (pChildTypeRef == null)
				{
					InternalString sTemp = new InternalString("expected child TypeRef... ");
					sTemp.Append(pTokenContainer.StringifyOffset(pTempOffset));
					Console.Log(sTemp.GetExternalString());
					Assert.Plz(false);
					return null;
				}
				pTypeRef.m_pChildTypeRef = pChildTypeRef;
				NumbatLogic.TypeRef __1983801666 = pChildTypeRef;
				pChildTypeRef = null;
				pTypeRef.AddChild(__1983801666);
			}
			else
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_STAR) != null)
				{
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
					pTypeRef.m_ePointerType = PointerType.OWNED;
				}
				else
					if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_STAR_DOUBLE) != null)
					{
						pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
						pTypeRef.m_ePointerType = PointerType.TRANSITON;
					}
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.TypeRef __967910118 = pTypeRef;
			pTypeRef = null;
			return __967910118;
		}

		public ClassDecl GetFoundClassDecl()
		{
			if (m_pFoundType != null && m_pFoundType.m_eType == AST.Type.AST_CLASS_DECL)
				return (ClassDecl)(m_pFoundType);
			return null;
		}

		protected void ValidateClassDecl(Validator pValidator, ClassDecl pClassDecl, TypeRef pThisOrChild)
		{
			if (m_pParent != null)
			{
				if (m_pParent.m_eType == AST.Type.AST_NEW_EXP)
				{
				}
				else
					if (m_pParent.m_eType == AST.Type.AST_TYPE_REF)
					{
						TypeRef pSubParentTypeRef = (TypeRef)(m_pParent);
						AddClassDeclReference(pClassDecl, AST.OutputFile.HEADER, true);
						if (pSubParentTypeRef.m_pChildTypeRef != this)
						{
							AST pParentParent = m_pParent.m_pParent;
							if (pParentParent != null)
							{
								if (pParentParent.m_eType == AST.Type.AST_NEW_EXP)
									AddClassDeclReference(pClassDecl, AST.OutputFile.SOURCE, false);
								AST pParentParentParent = pParentParent.m_pParent;
								if (pParentParentParent != null)
								{
									if (pParentParentParent.m_eType == AST.Type.AST_MEMBER_VAR_DECL)
										AddClassDeclReference(pClassDecl, AST.OutputFile.HEADER, false);
									else
										if (pParentParentParent.m_eType == AST.Type.AST_MEMBER_FUNCTION_DECL)
											AddClassDeclReference(pClassDecl, AST.OutputFile.HEADER, true);
										else
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
						if (pParentParent != null)
						{
							if (pParentParent.m_eType == AST.Type.AST_MEMBER_VAR_DECL || pParentParent.m_eType == AST.Type.AST_MEMBER_FUNCTION_DECL)
							{
								eOutputFile = AST.OutputFile.HEADER;
							}
							else
							{
								AST pParentParentParent = pParentParent.m_pParent;
								if (pParentParentParent != null)
								{
									AST pParentParentParentParent = pParentParentParent.m_pParent;
									if (pParentParentParentParent != null)
									{
										if (m_pParent.m_eType == AST.Type.AST_VAR_DECL && pParentParent.m_eType == AST.Type.AST_PARAM_DECL && (pParentParentParent.m_eType == AST.Type.AST_FUNCTION_DECL && pParentParentParentParent.m_eType == AST.Type.AST_MEMBER_FUNCTION_DECL || pParentParentParent.m_eType == AST.Type.AST_TOR_DECL || (pParentParentParent.m_eType == AST.Type.AST_FUNCTION_DECL && pParentParentParentParent.m_eType == AST.Type.DELEGATE_DECL)))
											eOutputFile = AST.OutputFile.HEADER;
									}
								}
							}
						}
						AddClassDeclReference(pClassDecl, eOutputFile, bForwardReference);
					}
			}
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			if (m_pTypeToken.m_eType == Token.Type.TOKEN_IDENTIFIER)
			{
				AST pType = null;
				bool bResolverTypeAmbiguous = false;
				string sTypeName = m_pTypeToken.GetString();
				TypeRef pParentTypeRef = null;
				if (m_pParent != null && m_pParent.m_eType == AST.Type.AST_TYPE_REF)
				{
					pParentTypeRef = (TypeRef)(m_pParent);
					if (pParentTypeRef.m_pChildTypeRef != this)
						pParentTypeRef = null;
				}
				Vector<Symbol> pCandidates = new Vector<Symbol>();
				AST pResolverBase = this;
				if (pParentTypeRef != null && pParentTypeRef.m_pFoundType != null)
					pResolverBase = pParentTypeRef.m_pFoundType;
				pValidator.m_pResolver.ResolveFromNode(pResolverBase, sTypeName, pCandidates);
				Vector<Symbol> pTypeLike = new Vector<Symbol>();
				for (int i = 0; i < pCandidates.GetSize(); i++)
				{
					Symbol pSym = pCandidates.Get(i);
					if (pSym.m_eKind == Symbol.Kind.CLASS || pSym.m_eKind == Symbol.Kind.ENUM || pSym.m_eKind == Symbol.Kind.GENERIC_PARAM || pSym.m_eKind == Symbol.Kind.DELEGATE || pSym.m_eKind == Symbol.Kind.NAMESPACE)
					{
						pTypeLike.PushBack(pSym);
					}
				}
				if (pTypeLike.GetSize() == 1)
				{
					Symbol pSymbol = pTypeLike.Get(0);
					if (pSymbol.m_pDeclAST != null)
					{
						pType = pSymbol.m_pDeclAST;
						m_pFoundType = pType;
					}
				}
				else
					if (pTypeLike.GetSize() > 1)
						bResolverTypeAmbiguous = true;
				if (pType == null)
				{
					if (bResolverTypeAmbiguous)
					{
						InternalString sAmbiguous = new InternalString("Ambiguous type (multiple declarations in scope): ");
						sAmbiguous.Append(sTypeName);
						pValidator.AddError(sAmbiguous.GetExternalString(), m_pTypeToken.m_sFileName, m_pTypeToken.m_nLine, m_pTypeToken.m_nColumn);
					}
					else
					{
						InternalString sTemp = new InternalString("Unknown type: ");
						sTemp.Append(sTypeName);
						TypeRef pSubParentTypeRef = null;
						if (m_pParent.m_eType == AST.Type.AST_TYPE_REF)
						{
							pSubParentTypeRef = (TypeRef)(m_pParent);
							if (pSubParentTypeRef.m_pChildTypeRef != this)
								pSubParentTypeRef = null;
						}
						if (pSubParentTypeRef != null && pSubParentTypeRef.m_pFoundType != null)
							sTemp.Append(" -- had parent");
						pValidator.AddError(sTemp.GetExternalString(), m_pTypeToken.m_sFileName, m_pTypeToken.m_nLine, m_pTypeToken.m_nColumn);
					}
					return;
				}
				if (pType.m_eType == AST.Type.AST_CLASS_DECL)
				{
					ClassDecl pClassDecl = (ClassDecl)(pType);
					ValidateClassDecl(pValidator, pClassDecl, this);
					if (m_pChildTypeRef != null)
					{
						m_pChildTypeRef.Validate(pValidator, null);
					}
				}
				else
					if (pType.m_eType == AST.Type.NAMESPACE_DECL)
					{
						if (m_pChildTypeRef == null)
						{
							pValidator.AddError("Namespace typeref musttt have a child???", m_pTypeToken.m_sFileName, m_pTypeToken.m_nLine, m_pTypeToken.m_nColumn);
							return;
						}
						if (m_pChildTypeRef.m_pTypeToken.m_eType != Token.Type.TOKEN_IDENTIFIER)
						{
							pValidator.AddError("child must be IDENTIFIER", m_pChildTypeRef.m_pTypeToken.m_sFileName, m_pChildTypeRef.m_pTypeToken.m_nLine, m_pChildTypeRef.m_pTypeToken.m_nColumn);
							return;
						}
						m_pChildTypeRef.Validate(pValidator, null);
					}
					else
						if (pType.m_eType == AST.Type.AST_ENUM_DECL)
						{
						}
						else
							if (pType.m_eType == AST.Type.AST_MEMBER_CLASS_DECL)
							{
							}
							else
								if (pType.m_eType == AST.Type.AST_MEMBER_ENUM_DECL)
								{
								}
								else
									if (pType.m_eType == AST.Type.AST_GENERIC_TYPE_DECL)
									{
									}
									else
										if (pType.m_eType == AST.Type.DELEGATE_DECL)
										{
										}
										else
										{
											InternalString sTemp = new InternalString("Found type, but it's not a AST_CLASS_DECL, AST_MEMBER_CLASS_DECL, NAMESPACE_DECL, AST_ENUM_DECL, AST_MEMBER_ENUM_DECL, AST_GENERIC_TYPE_DECL or DELEGATE_DECL! Got: ");
											pType.StringifyType(sTemp);
											pValidator.AddError(sTemp.GetExternalString(), m_pTypeToken.m_sFileName, m_pTypeToken.m_nLine, m_pTypeToken.m_nColumn);
										}
			}
			else
			{
				if (m_pChildTypeRef != null)
				{
					pValidator.AddError("Not identifier but has child type ref???", m_pTypeToken.m_sFileName, m_pTypeToken.m_nLine, m_pTypeToken.m_nColumn);
					return;
				}
			}
			for (int i = 0; i < m_pGenericTypeRefVector.GetSize(); i++)
			{
				TypeRef pGenericTypeRef = m_pGenericTypeRefVector.Get(i);
				pGenericTypeRef.Validate(pValidator, null);
			}
			base.Validate(pValidator, pParent);
		}

		public TypeRef Clone()
		{
			TypeRef pTypeRef = new TypeRef();
			pTypeRef.m_pCloneToken = m_pTypeToken.Clone();
			pTypeRef.m_bConst = m_bConst;
			pTypeRef.m_pFirstToken = pTypeRef.m_pCloneToken;
			pTypeRef.m_pTypeToken = pTypeRef.m_pCloneToken;
			pTypeRef.m_pFoundType = m_pFoundType;
			for (int i = 0; i < m_pGenericTypeRefVector.GetSize(); i++)
			{
				TypeRef pGenericTypeRef = m_pGenericTypeRefVector.Get(i).Clone();
				pTypeRef.m_pGenericTypeRefVector.PushBack(pGenericTypeRef);
				NumbatLogic.TypeRef __3769232678 = pGenericTypeRef;
				pGenericTypeRef = null;
				pTypeRef.AddChild(__3769232678);
			}
			pTypeRef.m_pChildTypeRef = null;
			if (m_pChildTypeRef != null)
			{
				TypeRef pChildTypeRef = m_pChildTypeRef.Clone();
				pTypeRef.m_pChildTypeRef = pChildTypeRef;
				NumbatLogic.TypeRef __2008520584 = pChildTypeRef;
				pChildTypeRef = null;
				pTypeRef.AddChild(__2008520584);
			}
			pTypeRef.m_ePointerType = m_ePointerType;
			NumbatLogic.TypeRef __992497841 = pTypeRef;
			pTypeRef = null;
			return __992497841;
		}

		public override AST BaseClone()
		{
			return Clone();
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			if (m_bConst)
			{
				bool bOutput = true;
				if (eLanguage == AST.Language.CS)
				{
					bOutput = false;
					Project pProject = GetProject();
					if (pProject != null && pProject.m_pValidator != null)
					{
						ValueType pValueType = GetRecursiveValueType(pProject.m_pValidator.m_pResolver);
						switch (pValueType.m_eType)
						{
							case ValueType.Type.INT:
							case ValueType.Type.BOOL:
							case ValueType.Type.CHAR:
							case ValueType.Type.UNICHAR:
							case ValueType.Type.ENUM_DECL_VALUE:
							{
								bOutput = true;
								break;
							}

						}
					}
				}
				if (bOutput)
					sOut.AppendString("const ");
			}
			if (eLanguage == AST.Language.CPP)
			{
				if (m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_UNICHAR)
					sOut.Append("unsigned short");
				else
					if (m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_STRING)
					{
						if (m_bConst)
							sOut.Append("char*");
						else
							sOut.Append("const char*");
					}
					else
						if (m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_UINT)
							sOut.Append("unsigned int");
						else
							if (m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_UINT8)
								sOut.Append("unsigned char");
							else
								if (m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_UINT16)
									sOut.Append("unsigned short");
								else
									if (m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_UINT32)
										sOut.Append("unsigned int");
									else
										if (m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_UINT64)
											sOut.Append("unsigned long long");
										else
											if (m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_INT32)
												sOut.Append("int");
											else
												if (m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_INT16)
													sOut.Append("short");
												else
													if (m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_INT8)
														sOut.Append("signed char");
													else
														if (m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_VOIDPTR)
															sOut.Append("void*");
														else
															m_pTypeToken.Stringify(sOut);
				if (m_bRef)
					sOut.AppendString("&");
			}
			else
				if (eLanguage == AST.Language.CS)
				{
					if (m_bRef && eLanguage == AST.Language.CS)
						sOut.AppendString("ref ");
					switch (m_pTypeToken.m_eType)
					{
						case Token.Type.TOKEN_KEYWORD_UNICHAR:
						{
							sOut.Append("char");
							break;
						}

						case Token.Type.TOKEN_KEYWORD_STRING:
						{
							sOut.Append("string");
							break;
						}

						case Token.Type.TOKEN_KEYWORD_VOIDPTR:
						{
							sOut.Append("object");
							break;
						}

						case Token.Type.TOKEN_KEYWORD_UINT8:
						{
							sOut.Append("byte");
							break;
						}

						case Token.Type.TOKEN_KEYWORD_UINT16:
						{
							sOut.Append("ushort");
							break;
						}

						case Token.Type.TOKEN_KEYWORD_UINT32:
						{
							sOut.Append("uint");
							break;
						}

						case Token.Type.TOKEN_KEYWORD_UINT64:
						{
							sOut.Append("ulong");
							break;
						}

						case Token.Type.TOKEN_KEYWORD_INT8:
						{
							sOut.Append("sbyte");
							break;
						}

						case Token.Type.TOKEN_KEYWORD_INT16:
						{
							sOut.Append("short");
							break;
						}

						case Token.Type.TOKEN_KEYWORD_INT32:
						{
							sOut.Append("int");
							break;
						}

						default:
						{
							m_pTypeToken.Stringify(sOut);
							break;
						}

					}
				}
				else
				{
					m_pTypeToken.Stringify(sOut);
				}
			if (m_pGenericTypeRefVector.GetSize() > 0)
			{
				sOut.AppendChar('<');
				for (int i = 0; i < m_pGenericTypeRefVector.GetSize(); i++)
				{
					if (i > 0)
						sOut.Append(", ");
					TypeRef pGenericTypeRef = m_pGenericTypeRefVector.Get(i);
					pGenericTypeRef.Stringify(eLanguage, eOutputFile, 0, sOut);
				}
				if (eLanguage == AST.Language.NLL_DEF)
					sOut.AppendChar('!');
				sOut.AppendChar('>');
			}
			if (m_pChildTypeRef != null)
			{
				switch (eLanguage)
				{
					case AST.Language.NLL:
					case AST.Language.NLL_DEF:
					case AST.Language.CPP:
					{
						sOut.Append("::");
						break;
					}

					case AST.Language.CS:
					{
						sOut.AppendChar('.');
						break;
					}

				}
				m_pChildTypeRef.Stringify(eLanguage, eOutputFile, 0, sOut);
			}
			TypeRef pFinalChildTypeRef = this;
			while (pFinalChildTypeRef.m_pChildTypeRef != null)
			{
				pFinalChildTypeRef = pFinalChildTypeRef.m_pChildTypeRef;
			}
			if (pFinalChildTypeRef.m_pTypeToken.m_eType == Token.Type.TOKEN_IDENTIFIER)
			{
				string sTypeName = pFinalChildTypeRef.m_pTypeToken.GetString();
				AST pType = pFinalChildTypeRef.m_pFoundType;
				string sxAppendString = "";
				if (eLanguage == AST.Language.CPP && pType != null && pType.m_eType == AST.Type.AST_CLASS_DECL)
					sxAppendString = "*";
				if (eLanguage == AST.Language.CPP && pType != null && pType.m_eType == AST.Type.DELEGATE_DECL)
					sxAppendString = "*";
				if (m_pParent != null)
				{
					if (m_pParent.m_eType == AST.Type.AST_NEW_EXP)
						sxAppendString = "";
					if (m_pParent.m_eType == AST.Type.AST_TYPE_REF)
					{
						TypeRef pParentTypeRef = (TypeRef)(m_pParent);
						if (pParentTypeRef.m_pChildTypeRef == this)
							sxAppendString = "";
					}
					if (m_pParent.m_eType == AST.Type.AST_CLASS_DECL)
					{
						ClassDecl pParentClassDecl = (ClassDecl)(m_pParent);
						if (pParentClassDecl.m_pBaseTypeRef == this)
							sxAppendString = "";
					}
					sOut.AppendString(sxAppendString);
				}
			}
		}

		public ValueType GetRecursiveValueType(Resolver pResolver)
		{
			if (m_pValueType == null)
				SetValueType(pResolver);
			if (m_pChildTypeRef != null)
				return m_pChildTypeRef.GetRecursiveValueType(pResolver);
			return m_pValueType;
		}

		public ValueType CreateValueType(Resolver pResolver)
		{
			if (m_pValueType == null)
				SetValueType(pResolver);
			if (m_pChildTypeRef != null)
				return m_pChildTypeRef.CreateValueType(pResolver);
			if (m_pValueType != null)
				return m_pValueType.Clone();
			return null;
		}

		protected ValueType SetValueType(Resolver pResolver)
		{
			switch (m_pTypeToken.m_eType)
			{
				case Token.Type.TOKEN_IDENTIFIER:
				{
					AST pType = m_pFoundType;
					if (pType == null && pResolver != null)
					{
						string sTypeName = m_pTypeToken.GetString();
						TypeRef pParentTypeRef = null;
						if (m_pParent != null && m_pParent.m_eType == AST.Type.AST_TYPE_REF)
						{
							pParentTypeRef = (TypeRef)(m_pParent);
							if (pParentTypeRef.m_pChildTypeRef != this)
								pParentTypeRef = null;
						}
						Vector<Symbol> pCandidates = new Vector<Symbol>();
						AST pResolverBase = this;
						if (pParentTypeRef != null && pParentTypeRef.m_pFoundType != null)
							pResolverBase = pParentTypeRef.m_pFoundType;
						pResolver.ResolveFromNode(pResolverBase, sTypeName, pCandidates);
						Vector<Symbol> pTypeLike = new Vector<Symbol>();
						for (int i = 0; i < pCandidates.GetSize(); i++)
						{
							Symbol pSym = pCandidates.Get(i);
							if (pSym.m_eKind == Symbol.Kind.CLASS || pSym.m_eKind == Symbol.Kind.ENUM || pSym.m_eKind == Symbol.Kind.GENERIC_PARAM || pSym.m_eKind == Symbol.Kind.DELEGATE || pSym.m_eKind == Symbol.Kind.NAMESPACE)
							{
								pTypeLike.PushBack(pSym);
							}
						}
						if (pTypeLike.GetSize() == 1)
						{
							Symbol pSymbol = pTypeLike.Get(0);
							if (pSymbol.m_pDeclAST != null)
							{
								pType = pSymbol.m_pDeclAST;
								m_pFoundType = pType;
							}
						}
					}
					if (pType != null)
					{
						if (pType.m_eType == AST.Type.AST_CLASS_DECL)
						{
							m_pValueType = new ValueType(ValueType.Type.CLASS_DECL_VALUE);
							m_pValueType.m_bConst = m_bConst;
							m_pValueType.m_pClassDecl = (ClassDecl)(pType);
							m_pValueType.m_ePointerType = m_ePointerType;
							for (int i = 0; i < m_pGenericTypeRefVector.GetSize(); i++)
							{
								TypeRef pGenericTypeRef = m_pGenericTypeRefVector.Get(i);
								ValueType pGenericValueType = pGenericTypeRef.CreateValueType(pResolver);
								if (pGenericValueType == null)
								{
									return null;
								}
								NumbatLogic.ValueType __2199059312 = pGenericValueType;
								pGenericValueType = null;
								m_pValueType.m_pGenericValueTypeVector.PushBack(__2199059312);
							}
							return m_pValueType;
						}
						if (pType.m_eType == AST.Type.AST_MEMBER_CLASS_DECL)
						{
							MemberClassDecl pMemberClass = (MemberClassDecl)(pType);
							if (pMemberClass.m_pClassDecl != null)
							{
								m_pValueType = new ValueType(ValueType.Type.CLASS_DECL_VALUE);
								m_pValueType.m_bConst = m_bConst;
								m_pValueType.m_pClassDecl = pMemberClass.m_pClassDecl;
								m_pValueType.m_ePointerType = m_ePointerType;
								for (int i = 0; i < m_pGenericTypeRefVector.GetSize(); i++)
								{
									TypeRef pGenericTypeRef = m_pGenericTypeRefVector.Get(i);
									ValueType pGenericValueType = pGenericTypeRef.CreateValueType(pResolver);
									if (pGenericValueType == null)
									{
										return null;
									}
									NumbatLogic.ValueType __2199190512 = pGenericValueType;
									pGenericValueType = null;
									m_pValueType.m_pGenericValueTypeVector.PushBack(__2199190512);
								}
								return m_pValueType;
							}
						}
						if (pType.m_eType == AST.Type.AST_GENERIC_TYPE_DECL)
						{
							m_pValueType = new ValueType(ValueType.Type.GENERIC_TYPE_DECL_VALUE);
							m_pValueType.m_bConst = m_bConst;
							m_pValueType.m_pGenericTypeDecl = (GenericTypeDecl)(pType);
							m_pValueType.m_ePointerType = m_ePointerType;
							return m_pValueType;
						}
						if (pType.m_eType == AST.Type.AST_ENUM_DECL)
						{
							m_pValueType = new ValueType(ValueType.Type.ENUM_DECL_VALUE);
							m_pValueType.m_bConst = m_bConst;
							m_pValueType.m_pEnumDecl = (EnumDecl)(pType);
							return m_pValueType;
						}
						if (pType.m_eType == AST.Type.AST_MEMBER_ENUM_DECL)
						{
							MemberEnumDecl pMemberEnum = (MemberEnumDecl)(pType);
							if (pMemberEnum.m_pEnumDecl != null)
							{
								m_pValueType = new ValueType(ValueType.Type.ENUM_DECL_VALUE);
								m_pValueType.m_bConst = m_bConst;
								m_pValueType.m_pEnumDecl = pMemberEnum.m_pEnumDecl;
								m_pValueType.m_ePointerType = m_ePointerType;
								return m_pValueType;
							}
						}
						if (pType.m_eType == AST.Type.ENUM_DECL_VALUE)
						{
							m_pValueType = new ValueType(ValueType.Type.ENUM_DECL_VALUE);
							m_pValueType.m_bConst = m_bConst;
							m_pValueType.m_pEnumDeclValue = (EnumDeclValue)(pType);
							return m_pValueType;
						}
						if (pType.m_eType == AST.Type.DELEGATE_DECL)
						{
							m_pValueType = new ValueType(ValueType.Type.DELEGATE_DECL_VALUE);
							m_pValueType.m_bConst = m_bConst;
							m_pValueType.m_pDelegateDecl = (DelegateDecl)(pType);
							return m_pValueType;
						}
					}
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
					m_pValueType = new ValueType(ValueType.Type.INT);
					m_pValueType.m_bConst = m_bConst;
					return m_pValueType;
				}

				case Token.Type.TOKEN_KEYWORD_STRING:
				{
					m_pValueType = new ValueType(ValueType.Type.STRING);
					m_pValueType.m_bConst = m_bConst;
					return m_pValueType;
				}

				case Token.Type.TOKEN_KEYWORD_BOOL:
				{
					m_pValueType = new ValueType(ValueType.Type.BOOL);
					m_pValueType.m_bConst = m_bConst;
					return m_pValueType;
				}

				case Token.Type.TOKEN_KEYWORD_UNICHAR:
				{
					m_pValueType = new ValueType(ValueType.Type.UNICHAR);
					m_pValueType.m_bConst = m_bConst;
					return m_pValueType;
				}

				case Token.Type.TOKEN_KEYWORD_VOID:
				{
					m_pValueType = new ValueType(ValueType.Type.VOID);
					m_pValueType.m_bConst = m_bConst;
					return m_pValueType;
				}

				case Token.Type.TOKEN_KEYWORD_VOIDPTR:
				{
					m_pValueType = new ValueType(ValueType.Type.VOIDPTR);
					m_pValueType.m_bConst = m_bConst;
					return m_pValueType;
				}

			}
			return null;
		}

		public bool IsIntegral()
		{
			Project pProject = GetProject();
			if (pProject == null || pProject.m_pValidator == null)
				return IsInt() || IsBool() || m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_UNICHAR;
			ValueType pValueType = GetRecursiveValueType(pProject.m_pValidator.m_pResolver);
			if (pValueType.m_eType == ValueType.Type.ENUM_DECL_VALUE)
				return true;
			return IsInt() || IsBool() || m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_UNICHAR;
		}

		public bool IsInt()
		{
			return m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_INT || m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_UINT || m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_UINT8 || m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_UINT16 || m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_UINT32 || m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_UINT64 || m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_INT8 || m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_INT16 || m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_INT32;
		}

		public bool IsBool()
		{
			return m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_BOOL;
		}

		public bool IsFloat()
		{
			return m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_FLOAT;
		}

		public bool IsDouble()
		{
			return m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_DOUBLE;
		}

		~TypeRef()
		{
		}

	}
}

