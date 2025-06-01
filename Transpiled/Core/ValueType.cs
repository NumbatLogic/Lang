namespace NumberDuck
{
	namespace Secret
	{
		class ValueType
		{
			public enum Type
			{
				VOID,
				INT,
				STRING,
				BOOL,
				CHAR,
				UNICHAR,
				INSTANCE,
				VOIDPTR,
				CLASS_DECL,
				CLASS_DECL_VALUE,
				ENUM_DECL,
				ENUM_DECL_VALUE,
				GENERIC_TYPE_DECL_VALUE,
				STATIC_ARRAY,
				NULL_VALUE,
				DELEGATE_DECL_VALUE,
				FUNCTION_DECL,
				NAMESPACE_NODE,
			}

			public bool m_bConst;
			public Type m_eType;
			public ClassDecl m_pClassDecl;
			public TypeRef.PointerType m_ePointerType;
			public GenericTypeDecl m_pGenericTypeDecl;
			public EnumDecl m_pEnumDecl;
			public EnumDeclValue m_pEnumDeclValue;
			public OwnedVector<ValueType> m_pGenericValueTypeVector;
			public DelegateDecl m_pDelegateDecl;
			public FunctionDecl m_pFunctionDecl;
			public NamespaceNode m_pNamespaceNode;
			public ValueType(Type eType)
			{
				m_bConst = false;
				m_eType = eType;
				m_pGenericValueTypeVector = new OwnedVector<ValueType>();
				m_ePointerType = TypeRef.PointerType.SHARED;
			}

			public ValueType Clone()
			{
				ValueType pValueType = new ValueType(m_eType);
				pValueType.m_bConst = m_bConst;
				pValueType.m_pClassDecl = m_pClassDecl;
				pValueType.m_ePointerType = m_ePointerType;
				pValueType.m_pGenericTypeDecl = m_pGenericTypeDecl;
				pValueType.m_pEnumDecl = m_pEnumDecl;
				pValueType.m_pEnumDeclValue = m_pEnumDeclValue;
				pValueType.m_pDelegateDecl = m_pDelegateDecl;
				pValueType.m_pFunctionDecl = m_pFunctionDecl;
				if (m_pGenericValueTypeVector != null)
				{
					for (int i = 0; i < m_pGenericValueTypeVector.GetSize(); i++)
						pValueType.m_pGenericValueTypeVector.PushBack(m_pGenericValueTypeVector.Get(i).Clone());
				}
				{
					NumberDuck.Secret.ValueType __415518348 = pValueType;
					pValueType = null;
					return __415518348;
				}
			}

			public bool ValidateAssignable(ValueType pTo, Validator pValidator, Token pToken)
			{
				if (pTo == null)
				{
					if (pValidator != null)
						pValidator.AddError("No pTo to compare to???", pToken.m_sFileName, pToken.m_nLine, pToken.m_nColumn);
					return false;
				}
				if (pTo.m_ePointerType != TypeRef.PointerType.OWNED && m_ePointerType == TypeRef.PointerType.OWNED_PREASSSIGN)
				{
					pValidator.AddError("Can't assign an owned pointer to a non-owned variable", pToken.m_sFileName, pToken.m_nLine, pToken.m_nColumn);
					return false;
				}
				if (pTo.m_ePointerType == TypeRef.PointerType.OWNED && (m_ePointerType != TypeRef.PointerType.OWNED_PREASSSIGN && m_eType != ValueType.Type.NULL_VALUE))
				{
					pValidator.AddError("Expected right side of = to be OWNED_PREASSSIGN (result of own)", pToken.m_sFileName, pToken.m_nLine, pToken.m_nColumn);
					return false;
				}
				else if (m_ePointerType == TypeRef.PointerType.TRANSITON)
				{
					pValidator.AddError("Cannot store a TRANSITION pointer (need to `own` it)", pToken.m_sFileName, pToken.m_nLine, pToken.m_nColumn);
					return false;
				}
				if ((m_pGenericValueTypeVector == null) != (pTo.m_pGenericValueTypeVector == null))
				{
					pValidator.AddError("m_pGenericValueTypeVector null mismatch", pToken.m_sFileName, pToken.m_nLine, pToken.m_nColumn);
					return false;
				}
				if (m_pGenericValueTypeVector != null)
				{
					if (m_pGenericValueTypeVector.GetSize() != pTo.m_pGenericValueTypeVector.GetSize())
					{
						pValidator.AddError("m_pGenericValueTypeVector size mismatch", pToken.m_sFileName, pToken.m_nLine, pToken.m_nColumn);
						return false;
					}
					for (int i = 0; i < m_pGenericValueTypeVector.GetSize(); i++)
					{
						ValueType pSubFrom = m_pGenericValueTypeVector.Get(i);
						ValueType pSubTo = pTo.m_pGenericValueTypeVector.Get(i);
						if (pSubFrom.m_ePointerType != pSubTo.m_ePointerType)
						{
							pValidator.AddError("sub pointer type mismatch", pToken.m_sFileName, pToken.m_nLine, pToken.m_nColumn);
							return false;
						}
					}
				}
				return true;
			}

			public TypeRef CreateTypeRef()
			{
				TypeRef pTypeRef = new TypeRef();
				pTypeRef.m_bConst = m_bConst;
				pTypeRef.m_ePointerType = m_ePointerType;
				switch (m_eType)
				{
					case Type.CLASS_DECL_VALUE:
					{
						pTypeRef.m_pCloneToken = new Token();
						pTypeRef.m_pCloneToken.m_eType = Token.Type.TOKEN_IDENTIFIER;
						pTypeRef.m_pCloneToken.m_sValue = new InternalString(m_pClassDecl.m_pNameToken.m_sValue.GetExternalString());
						pTypeRef.m_pTypeToken = pTypeRef.m_pCloneToken;
						if (m_pGenericValueTypeVector != null)
						{
							for (int i = 0; i < m_pGenericValueTypeVector.GetSize(); i++)
							{
								TypeRef pGenericTypeRef = m_pGenericValueTypeVector.Get(i).CreateTypeRef();
								pTypeRef.m_pGenericTypeRefVector.PushBack(pGenericTypeRef);
								{
									NumberDuck.Secret.TypeRef __1546460495 = pGenericTypeRef;
									pGenericTypeRef = null;
									pTypeRef.AddChild(__1546460495);
								}
							}
						}
						NamespaceNode pNamespaceNode = m_pClassDecl.m_pNamespaceNode;
						while (pNamespaceNode != null && pNamespaceNode.m_sName != null)
						{
							TypeRef pNamespaceTypeRef = new TypeRef();
							pNamespaceTypeRef.m_pCloneToken = new Token();
							pNamespaceTypeRef.m_pCloneToken.m_eType = Token.Type.TOKEN_IDENTIFIER;
							pNamespaceTypeRef.m_pCloneToken.m_sValue = new InternalString(pNamespaceNode.m_sName.GetExternalString());
							pNamespaceTypeRef.m_pTypeToken = pNamespaceTypeRef.m_pCloneToken;
							pNamespaceTypeRef.m_pChildTypeRef = pTypeRef;
							{
								NumberDuck.Secret.TypeRef __3079357496 = pTypeRef;
								pTypeRef = null;
								pNamespaceTypeRef.AddChild(__3079357496);
							}
							{
								NumberDuck.Secret.TypeRef __8652500 = pNamespaceTypeRef;
								pNamespaceTypeRef = null;
								pTypeRef = __8652500;
							}
							pNamespaceNode = pNamespaceNode.m_pParent;
						}
						{
							NumberDuck.Secret.TypeRef __3079357496 = pTypeRef;
							pTypeRef = null;
							return __3079357496;
						}
					}

					case Type.GENERIC_TYPE_DECL_VALUE:
					{
						pTypeRef.m_pCloneToken = new Token();
						pTypeRef.m_pCloneToken.m_eType = Token.Type.TOKEN_IDENTIFIER;
						pTypeRef.m_pCloneToken.m_sValue = new InternalString(m_pGenericTypeDecl.m_pFirstToken.m_sValue.GetExternalString());
						pTypeRef.m_pTypeToken = pTypeRef.m_pCloneToken;
						{
							NumberDuck.Secret.TypeRef __3079357496 = pTypeRef;
							pTypeRef = null;
							return __3079357496;
						}
					}

				}
				nbAssert.Assert(false);
				{
					return null;
				}
			}

			public virtual void StringifyType(InternalString sOut)
			{
				switch (m_eType)
				{
					case Type.VOID:
					{
						sOut.Append("VOID");
						return;
					}

					case Type.INT:
					{
						sOut.Append("INT");
						return;
					}

					case Type.STRING:
					{
						sOut.Append("STRING");
						return;
					}

					case Type.BOOL:
					{
						sOut.Append("BOOL");
						return;
					}

					case Type.CHAR:
					{
						sOut.Append("CHAR");
						return;
					}

					case Type.UNICHAR:
					{
						sOut.Append("UNICHAR");
						return;
					}

					case Type.INSTANCE:
					{
						sOut.Append("INSTANCE");
						return;
					}

					case Type.VOIDPTR:
					{
						sOut.Append("VOIDPTR");
						return;
					}

					case Type.CLASS_DECL:
					{
						sOut.Append("CLASS_DECL");
						return;
					}

					case Type.CLASS_DECL_VALUE:
					{
						sOut.Append("CLASS_DECL_VALUE");
						return;
					}

					case Type.ENUM_DECL:
					{
						sOut.Append("ENUM_DECL");
						return;
					}

					case Type.ENUM_DECL_VALUE:
					{
						sOut.Append("ENUM_DECL_VALUE");
						return;
					}

					case Type.GENERIC_TYPE_DECL_VALUE:
					{
						sOut.Append("GENERIC_TYPE_DECL_VALUE");
						return;
					}

					case Type.STATIC_ARRAY:
					{
						sOut.Append("STATIC_ARRAY");
						return;
					}

					case Type.NULL_VALUE:
					{
						sOut.Append("NULL_VALUE");
						return;
					}

					case Type.DELEGATE_DECL_VALUE:
					{
						sOut.Append("DELEGATE_DECL_VALUE");
						return;
					}

					case Type.FUNCTION_DECL:
					{
						sOut.Append("FUNCTION_DECL");
						return;
					}

					case Type.NAMESPACE_NODE:
					{
						sOut.Append("NAMESPACE_NODE");
						return;
					}

				}
				sOut.Append("???");
			}

			~ValueType()
			{
			}

		}
	}
}

