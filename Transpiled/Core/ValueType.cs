#line 1 "../../../Source/Core/ValueType.nll"
namespace NumbatLogic
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

#line 36 "../../../Source/Core/ValueType.nll"
		public bool m_bConst;
		public Type m_eType;
#line 39 "../../../Source/Core/ValueType.nll"
		public ClassDecl m_pClassDecl;
		public TypeRef.PointerType m_ePointerType;
#line 42 "../../../Source/Core/ValueType.nll"
		public GenericTypeDecl m_pGenericTypeDecl;
#line 44 "../../../Source/Core/ValueType.nll"
		public EnumDecl m_pEnumDecl;
		public EnumDeclValue m_pEnumDeclValue;
#line 48 "../../../Source/Core/ValueType.nll"
		public OwnedVector<ValueType> m_pGenericValueTypeVector;
#line 50 "../../../Source/Core/ValueType.nll"
		public DelegateDecl m_pDelegateDecl;
#line 52 "../../../Source/Core/ValueType.nll"
		public FunctionDecl m_pFunctionDecl;
#line 54 "../../../Source/Core/ValueType.nll"
		public NamespaceNode m_pNamespaceNode;
#line 57 "../../../Source/Core/ValueType.nll"
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
#line 69 "../../../Source/Core/ValueType.nll"
			pValueType.m_bConst = m_bConst;
#line 71 "../../../Source/Core/ValueType.nll"
			pValueType.m_pClassDecl = m_pClassDecl;
			pValueType.m_ePointerType = m_ePointerType;
			pValueType.m_pGenericTypeDecl = m_pGenericTypeDecl;
#line 75 "../../../Source/Core/ValueType.nll"
			pValueType.m_pEnumDecl = m_pEnumDecl;
			pValueType.m_pEnumDeclValue = m_pEnumDeclValue;
#line 78 "../../../Source/Core/ValueType.nll"
			pValueType.m_pDelegateDecl = m_pDelegateDecl;
			pValueType.m_pFunctionDecl = m_pFunctionDecl;
#line 81 "../../../Source/Core/ValueType.nll"
			if (m_pGenericValueTypeVector != null)
			{
				for (int i = 0; i < m_pGenericValueTypeVector.GetSize(); i++)
					pValueType.m_pGenericValueTypeVector.PushBack(m_pGenericValueTypeVector.Get(i).Clone());
			}
			NumbatLogic.ValueType __1751098362 = pValueType;
			pValueType = null;
#line 87 "../../../Source/Core/ValueType.nll"
			return __1751098362;
		}

		public bool ValidateAssignable(ValueType pTo, Validator pValidator, Token pToken)
		{
			if (pTo == null)
			{
				if (pValidator != null)
					pValidator.AddError("No pTo to compare to???", pToken.m_sFileName, pToken.m_nLine, pToken.m_nColumn);
				return false;
			}
#line 109 "../../../Source/Core/ValueType.nll"
			if (pTo.m_ePointerType != TypeRef.PointerType.OWNED && m_ePointerType == TypeRef.PointerType.OWNED_PREASSSIGN)
			{
				InternalString sTemp = new InternalString("Can't assign an owned pointer to a non-owned variable. FROM[");
				StringifyType(sTemp);
				sTemp.Append(" ptr=");
				StringifyPointerType(sTemp, m_ePointerType);
				sTemp.Append("] TO[");
				pTo.StringifyType(sTemp);
				sTemp.Append(" ptr=");
				StringifyPointerType(sTemp, pTo.m_ePointerType);
				sTemp.Append("]");
				pValidator.AddError(sTemp.GetExternalString(), pToken.m_sFileName, pToken.m_nLine, pToken.m_nColumn);
				return false;
			}
#line 124 "../../../Source/Core/ValueType.nll"
			if (pTo.m_ePointerType == TypeRef.PointerType.OWNED && (m_ePointerType != TypeRef.PointerType.OWNED_PREASSSIGN && m_eType != ValueType.Type.NULL_VALUE))
			{
				InternalString sTemp = new InternalString("Expected right side of = to be OWNED_PREASSSIGN (result of own). FROM[");
				StringifyType(sTemp);
				sTemp.Append(" ptr=");
				StringifyPointerType(sTemp, m_ePointerType);
				sTemp.Append("] TO[");
				pTo.StringifyType(sTemp);
				sTemp.Append(" ptr=");
				StringifyPointerType(sTemp, pTo.m_ePointerType);
				sTemp.Append("]");
				pValidator.AddError(sTemp.GetExternalString(), pToken.m_sFileName, pToken.m_nLine, pToken.m_nColumn);
				return false;
			}
			else
#line 138 "../../../Source/Core/ValueType.nll"
				if (m_ePointerType == TypeRef.PointerType.TRANSITON)
				{
					InternalString sTemp = new InternalString("Cannot store a TRANSITION pointer (need to `own` it). FROM[");
					StringifyType(sTemp);
					sTemp.Append(" ptr=");
					StringifyPointerType(sTemp, m_ePointerType);
					sTemp.Append("] TO[");
					pTo.StringifyType(sTemp);
					sTemp.Append(" ptr=");
					StringifyPointerType(sTemp, pTo.m_ePointerType);
					sTemp.Append("]");
					pValidator.AddError(sTemp.GetExternalString(), pToken.m_sFileName, pToken.m_nLine, pToken.m_nColumn);
					return false;
				}
#line 154 "../../../Source/Core/ValueType.nll"
			if ((m_pGenericValueTypeVector == null) != (pTo.m_pGenericValueTypeVector == null))
			{
				pValidator.AddError("m_pGenericValueTypeVector null mismatch", pToken.m_sFileName, pToken.m_nLine, pToken.m_nColumn);
				return false;
			}
#line 160 "../../../Source/Core/ValueType.nll"
			if (m_pGenericValueTypeVector != null)
			{
				if (m_pGenericValueTypeVector.GetSize() != pTo.m_pGenericValueTypeVector.GetSize())
				{
					pValidator.AddError("m_pGenericValueTypeVector size mismatch", pToken.m_sFileName, pToken.m_nLine, pToken.m_nColumn);
					return false;
				}
#line 168 "../../../Source/Core/ValueType.nll"
				for (int i = 0; i < m_pGenericValueTypeVector.GetSize(); i++)
				{
					ValueType pSubFrom = m_pGenericValueTypeVector.Get(i);
					ValueType pSubTo = pTo.m_pGenericValueTypeVector.Get(i);
#line 185 "../../../Source/Core/ValueType.nll"
					if (pSubFrom.m_ePointerType != pSubTo.m_ePointerType)
					{
						pValidator.AddError("sub pointer type mismatch", pToken.m_sFileName, pToken.m_nLine, pToken.m_nColumn);
						return false;
					}
				}
			}
#line 194 "../../../Source/Core/ValueType.nll"
			return true;
		}

		public TypeRef CreateTypeRef()
		{
			TypeRef pTypeRef = new TypeRef();
			pTypeRef.m_bConst = m_bConst;
			pTypeRef.m_ePointerType = m_ePointerType;
#line 203 "../../../Source/Core/ValueType.nll"
			switch (m_eType)
			{
				case Type.CLASS_DECL_VALUE:
				{
					pTypeRef.m_pCloneToken = new Token();
					pTypeRef.m_pCloneToken.m_eType = Token.Type.TOKEN_IDENTIFIER;
					pTypeRef.m_pCloneToken.m_sValue = new InternalString(m_pClassDecl.m_pNameToken.m_sValue.GetExternalString());
					pTypeRef.m_pTypeToken = pTypeRef.m_pCloneToken;
#line 213 "../../../Source/Core/ValueType.nll"
					if (m_pGenericValueTypeVector != null)
					{
						for (int i = 0; i < m_pGenericValueTypeVector.GetSize(); i++)
						{
							TypeRef pGenericTypeRef = m_pGenericValueTypeVector.Get(i).CreateTypeRef();
							pTypeRef.m_pGenericTypeRefVector.PushBack(pGenericTypeRef);
							NumbatLogic.TypeRef __3752644072 = pGenericTypeRef;
#line 219 "../../../Source/Core/ValueType.nll"
							pGenericTypeRef = null;
#line 219 "../../../Source/Core/ValueType.nll"
							pTypeRef.AddChild(__3752644072);
						}
					}
#line 225 "../../../Source/Core/ValueType.nll"
					NamespaceNode pNamespaceNode = m_pClassDecl.m_pNamespaceNode;
					while (pNamespaceNode != null && pNamespaceNode.m_sName != null)
					{
						TypeRef pNamespaceTypeRef = new TypeRef();
#line 230 "../../../Source/Core/ValueType.nll"
						pNamespaceTypeRef.m_pCloneToken = new Token();
						pNamespaceTypeRef.m_pCloneToken.m_eType = Token.Type.TOKEN_IDENTIFIER;
						pNamespaceTypeRef.m_pCloneToken.m_sValue = new InternalString(pNamespaceNode.m_sName.GetExternalString());
						pNamespaceTypeRef.m_pTypeToken = pNamespaceTypeRef.m_pCloneToken;
#line 235 "../../../Source/Core/ValueType.nll"
						pNamespaceTypeRef.m_pChildTypeRef = pTypeRef;
						NumbatLogic.TypeRef __975974828 = pTypeRef;
#line 236 "../../../Source/Core/ValueType.nll"
						pTypeRef = null;
#line 236 "../../../Source/Core/ValueType.nll"
						pNamespaceTypeRef.AddChild(__975974828);
						NumbatLogic.TypeRef __2554801001 = pNamespaceTypeRef;
						pNamespaceTypeRef = null;
#line 238 "../../../Source/Core/ValueType.nll"
						pTypeRef = __2554801001;
#line 240 "../../../Source/Core/ValueType.nll"
						pNamespaceNode = pNamespaceNode.m_pParent;
					}
					NumbatLogic.TypeRef __976040424 = pTypeRef;
					pTypeRef = null;
#line 243 "../../../Source/Core/ValueType.nll"
					return __976040424;
				}

				case Type.GENERIC_TYPE_DECL_VALUE:
				{
#line 247 "../../../Source/Core/ValueType.nll"
					pTypeRef.m_pCloneToken = new Token();
					pTypeRef.m_pCloneToken.m_eType = Token.Type.TOKEN_IDENTIFIER;
					pTypeRef.m_pCloneToken.m_sValue = new InternalString(m_pGenericTypeDecl.m_pFirstToken.m_sValue.GetExternalString());
					pTypeRef.m_pTypeToken = pTypeRef.m_pCloneToken;
					NumbatLogic.TypeRef __976106021 = pTypeRef;
#line 251 "../../../Source/Core/ValueType.nll"
					pTypeRef = null;
#line 251 "../../../Source/Core/ValueType.nll"
					return __976106021;
				}

			}
			Assert.Plz(false);
			return null;
		}

		public virtual void StringifyType(InternalString sOut)
		{
			switch (m_eType)
			{
				case Type.VOID:
				{
#line 263 "../../../Source/Core/ValueType.nll"
					sOut.Append("VOID");
#line 263 "../../../Source/Core/ValueType.nll"
					return;
				}

				case Type.INT:
				{
#line 264 "../../../Source/Core/ValueType.nll"
					sOut.Append("INT");
#line 264 "../../../Source/Core/ValueType.nll"
					return;
				}

				case Type.STRING:
				{
#line 265 "../../../Source/Core/ValueType.nll"
					sOut.Append("STRING");
#line 265 "../../../Source/Core/ValueType.nll"
					return;
				}

				case Type.BOOL:
				{
#line 266 "../../../Source/Core/ValueType.nll"
					sOut.Append("BOOL");
#line 266 "../../../Source/Core/ValueType.nll"
					return;
				}

				case Type.CHAR:
				{
#line 267 "../../../Source/Core/ValueType.nll"
					sOut.Append("CHAR");
#line 267 "../../../Source/Core/ValueType.nll"
					return;
				}

				case Type.UNICHAR:
				{
#line 268 "../../../Source/Core/ValueType.nll"
					sOut.Append("UNICHAR");
#line 268 "../../../Source/Core/ValueType.nll"
					return;
				}

				case Type.INSTANCE:
				{
#line 269 "../../../Source/Core/ValueType.nll"
					sOut.Append("INSTANCE");
#line 269 "../../../Source/Core/ValueType.nll"
					return;
				}

				case Type.VOIDPTR:
				{
#line 270 "../../../Source/Core/ValueType.nll"
					sOut.Append("VOIDPTR");
#line 270 "../../../Source/Core/ValueType.nll"
					return;
				}

				case Type.CLASS_DECL:
				{
#line 271 "../../../Source/Core/ValueType.nll"
					sOut.Append("CLASS_DECL");
#line 271 "../../../Source/Core/ValueType.nll"
					return;
				}

				case Type.CLASS_DECL_VALUE:
				{
#line 272 "../../../Source/Core/ValueType.nll"
					sOut.Append("CLASS_DECL_VALUE");
#line 272 "../../../Source/Core/ValueType.nll"
					return;
				}

				case Type.ENUM_DECL:
				{
#line 273 "../../../Source/Core/ValueType.nll"
					sOut.Append("ENUM_DECL");
#line 273 "../../../Source/Core/ValueType.nll"
					return;
				}

				case Type.ENUM_DECL_VALUE:
				{
#line 274 "../../../Source/Core/ValueType.nll"
					sOut.Append("ENUM_DECL_VALUE");
#line 274 "../../../Source/Core/ValueType.nll"
					return;
				}

				case Type.GENERIC_TYPE_DECL_VALUE:
				{
#line 275 "../../../Source/Core/ValueType.nll"
					sOut.Append("GENERIC_TYPE_DECL_VALUE");
#line 275 "../../../Source/Core/ValueType.nll"
					return;
				}

				case Type.STATIC_ARRAY:
				{
#line 276 "../../../Source/Core/ValueType.nll"
					sOut.Append("STATIC_ARRAY");
#line 276 "../../../Source/Core/ValueType.nll"
					return;
				}

				case Type.NULL_VALUE:
				{
#line 277 "../../../Source/Core/ValueType.nll"
					sOut.Append("NULL_VALUE");
#line 277 "../../../Source/Core/ValueType.nll"
					return;
				}

				case Type.DELEGATE_DECL_VALUE:
				{
#line 278 "../../../Source/Core/ValueType.nll"
					sOut.Append("DELEGATE_DECL_VALUE");
#line 278 "../../../Source/Core/ValueType.nll"
					return;
				}

				case Type.FUNCTION_DECL:
				{
#line 279 "../../../Source/Core/ValueType.nll"
					sOut.Append("FUNCTION_DECL");
#line 279 "../../../Source/Core/ValueType.nll"
					return;
				}

				case Type.NAMESPACE_NODE:
				{
#line 280 "../../../Source/Core/ValueType.nll"
					sOut.Append("NAMESPACE_NODE");
#line 280 "../../../Source/Core/ValueType.nll"
					return;
				}

			}
#line 282 "../../../Source/Core/ValueType.nll"
			sOut.Append("???");
		}

		public static void StringifyPointerType(InternalString sOut, TypeRef.PointerType ePointerType)
		{
			switch (ePointerType)
			{
				case TypeRef.PointerType.SHARED:
				{
#line 289 "../../../Source/Core/ValueType.nll"
					sOut.Append("SHARED");
#line 289 "../../../Source/Core/ValueType.nll"
					return;
				}

				case TypeRef.PointerType.OWNED:
				{
#line 290 "../../../Source/Core/ValueType.nll"
					sOut.Append("OWNED");
#line 290 "../../../Source/Core/ValueType.nll"
					return;
				}

				case TypeRef.PointerType.TRANSITON:
				{
#line 291 "../../../Source/Core/ValueType.nll"
					sOut.Append("TRANSITON");
#line 291 "../../../Source/Core/ValueType.nll"
					return;
				}

				case TypeRef.PointerType.OWNED_PREASSSIGN:
				{
#line 292 "../../../Source/Core/ValueType.nll"
					sOut.Append("OWNED_PREASSSIGN");
#line 292 "../../../Source/Core/ValueType.nll"
					return;
				}

			}
#line 294 "../../../Source/Core/ValueType.nll"
			sOut.Append("UNKNOWN_PTR");
		}

#line 3 "../../../Source/Core/ValueType.nll"
		~ValueType()
		{
		}

	}
}

