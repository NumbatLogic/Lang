#line 1 "../../../Source/Core/ValueType.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/ValueType.nll"
	class ValueType
	{
#line 6 "../../../Source/Core/ValueType.nll"
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

#line 37 "../../../Source/Core/ValueType.nll"
		public bool m_bConst;
#line 38 "../../../Source/Core/ValueType.nll"
		public Type m_eType;
#line 40 "../../../Source/Core/ValueType.nll"
		public ClassDecl m_pClassDecl;
#line 41 "../../../Source/Core/ValueType.nll"
		public TypeRef.PointerType m_ePointerType;
#line 43 "../../../Source/Core/ValueType.nll"
		public GenericTypeDecl m_pGenericTypeDecl;
#line 45 "../../../Source/Core/ValueType.nll"
		public EnumDecl m_pEnumDecl;
#line 46 "../../../Source/Core/ValueType.nll"
		public EnumDeclValue m_pEnumDeclValue;
#line 49 "../../../Source/Core/ValueType.nll"
		public OwnedVector<ValueType> m_pGenericValueTypeVector;
#line 51 "../../../Source/Core/ValueType.nll"
		public DelegateDecl m_pDelegateDecl;
#line 53 "../../../Source/Core/ValueType.nll"
		public FunctionDecl m_pFunctionDecl;
#line 55 "../../../Source/Core/ValueType.nll"
		public NamespaceNode m_pNamespaceNode;
#line 58 "../../../Source/Core/ValueType.nll"
		public ValueType(Type eType)
		{
#line 60 "../../../Source/Core/ValueType.nll"
			m_bConst = false;
#line 61 "../../../Source/Core/ValueType.nll"
			m_eType = eType;
#line 62 "../../../Source/Core/ValueType.nll"
			m_pGenericValueTypeVector = new OwnedVector<ValueType>();
#line 63 "../../../Source/Core/ValueType.nll"
			m_ePointerType = TypeRef.PointerType.SHARED;
		}

#line 66 "../../../Source/Core/ValueType.nll"
		public ValueType Clone()
		{
			ValueType pValueType = new ValueType(m_eType);
#line 70 "../../../Source/Core/ValueType.nll"
			pValueType.m_bConst = m_bConst;
#line 72 "../../../Source/Core/ValueType.nll"
			pValueType.m_pClassDecl = m_pClassDecl;
#line 73 "../../../Source/Core/ValueType.nll"
			pValueType.m_ePointerType = m_ePointerType;
#line 74 "../../../Source/Core/ValueType.nll"
			pValueType.m_pGenericTypeDecl = m_pGenericTypeDecl;
#line 76 "../../../Source/Core/ValueType.nll"
			pValueType.m_pEnumDecl = m_pEnumDecl;
#line 77 "../../../Source/Core/ValueType.nll"
			pValueType.m_pEnumDeclValue = m_pEnumDeclValue;
#line 79 "../../../Source/Core/ValueType.nll"
			pValueType.m_pDelegateDecl = m_pDelegateDecl;
#line 80 "../../../Source/Core/ValueType.nll"
			pValueType.m_pFunctionDecl = m_pFunctionDecl;
#line 82 "../../../Source/Core/ValueType.nll"
			if (m_pGenericValueTypeVector != null)
			{
#line 84 "../../../Source/Core/ValueType.nll"
				for (int i = 0; i < m_pGenericValueTypeVector.GetSize(); i++)
#line 85 "../../../Source/Core/ValueType.nll"
					pValueType.m_pGenericValueTypeVector.PushBack(m_pGenericValueTypeVector.Get(i).Clone());
			}
			NumbatLogic.ValueType __1751098362 = pValueType;
#line 88 "../../../Source/Core/ValueType.nll"
			pValueType = null;
#line 88 "../../../Source/Core/ValueType.nll"
			return __1751098362;
		}

#line 91 "../../../Source/Core/ValueType.nll"
		public bool ValidateAssignable(ValueType pTo, Validator pValidator, Token pToken)
		{
#line 93 "../../../Source/Core/ValueType.nll"
			if (pTo == null)
			{
#line 95 "../../../Source/Core/ValueType.nll"
				if (pValidator != null)
#line 96 "../../../Source/Core/ValueType.nll"
					pValidator.AddError("No pTo to compare to???", pToken.m_sFileName, pToken.m_nLine, pToken.m_nColumn);
#line 97 "../../../Source/Core/ValueType.nll"
				return false;
			}
#line 110 "../../../Source/Core/ValueType.nll"
			if (pTo.m_ePointerType != TypeRef.PointerType.OWNED && m_ePointerType == TypeRef.PointerType.OWNED_PREASSSIGN)
			{
				InternalString sTemp = new InternalString("Can't assign an owned pointer to a non-owned variable. FROM[");
#line 113 "../../../Source/Core/ValueType.nll"
				StringifyType(sTemp);
#line 114 "../../../Source/Core/ValueType.nll"
				sTemp.Append(" ptr=");
#line 115 "../../../Source/Core/ValueType.nll"
				StringifyPointerType(sTemp, m_ePointerType);
#line 116 "../../../Source/Core/ValueType.nll"
				sTemp.Append("] TO[");
#line 117 "../../../Source/Core/ValueType.nll"
				pTo.StringifyType(sTemp);
#line 118 "../../../Source/Core/ValueType.nll"
				sTemp.Append(" ptr=");
#line 119 "../../../Source/Core/ValueType.nll"
				StringifyPointerType(sTemp, pTo.m_ePointerType);
#line 120 "../../../Source/Core/ValueType.nll"
				sTemp.Append("]");
#line 121 "../../../Source/Core/ValueType.nll"
				pValidator.AddError(sTemp.GetExternalString(), pToken.m_sFileName, pToken.m_nLine, pToken.m_nColumn);
#line 122 "../../../Source/Core/ValueType.nll"
				return false;
			}
#line 125 "../../../Source/Core/ValueType.nll"
			if (pTo.m_ePointerType == TypeRef.PointerType.OWNED && (m_ePointerType != TypeRef.PointerType.OWNED_PREASSSIGN && m_eType != ValueType.Type.NULL_VALUE))
			{
				InternalString sTemp = new InternalString("Expected right side of = to be OWNED_PREASSSIGN (result of own). FROM[");
#line 128 "../../../Source/Core/ValueType.nll"
				StringifyType(sTemp);
#line 129 "../../../Source/Core/ValueType.nll"
				sTemp.Append(" ptr=");
#line 130 "../../../Source/Core/ValueType.nll"
				StringifyPointerType(sTemp, m_ePointerType);
#line 131 "../../../Source/Core/ValueType.nll"
				sTemp.Append("] TO[");
#line 132 "../../../Source/Core/ValueType.nll"
				pTo.StringifyType(sTemp);
#line 133 "../../../Source/Core/ValueType.nll"
				sTemp.Append(" ptr=");
#line 134 "../../../Source/Core/ValueType.nll"
				StringifyPointerType(sTemp, pTo.m_ePointerType);
#line 135 "../../../Source/Core/ValueType.nll"
				sTemp.Append("]");
#line 136 "../../../Source/Core/ValueType.nll"
				pValidator.AddError(sTemp.GetExternalString(), pToken.m_sFileName, pToken.m_nLine, pToken.m_nColumn);
#line 137 "../../../Source/Core/ValueType.nll"
				return false;
			}
			else
#line 139 "../../../Source/Core/ValueType.nll"
				if (m_ePointerType == TypeRef.PointerType.TRANSITON)
				{
					InternalString sTemp = new InternalString("Cannot store a TRANSITION pointer (need to `own` it). FROM[");
#line 142 "../../../Source/Core/ValueType.nll"
					StringifyType(sTemp);
#line 143 "../../../Source/Core/ValueType.nll"
					sTemp.Append(" ptr=");
#line 144 "../../../Source/Core/ValueType.nll"
					StringifyPointerType(sTemp, m_ePointerType);
#line 145 "../../../Source/Core/ValueType.nll"
					sTemp.Append("] TO[");
#line 146 "../../../Source/Core/ValueType.nll"
					pTo.StringifyType(sTemp);
#line 147 "../../../Source/Core/ValueType.nll"
					sTemp.Append(" ptr=");
#line 148 "../../../Source/Core/ValueType.nll"
					StringifyPointerType(sTemp, pTo.m_ePointerType);
#line 149 "../../../Source/Core/ValueType.nll"
					sTemp.Append("]");
#line 150 "../../../Source/Core/ValueType.nll"
					pValidator.AddError(sTemp.GetExternalString(), pToken.m_sFileName, pToken.m_nLine, pToken.m_nColumn);
#line 151 "../../../Source/Core/ValueType.nll"
					return false;
				}
#line 155 "../../../Source/Core/ValueType.nll"
			if ((m_pGenericValueTypeVector == null) != (pTo.m_pGenericValueTypeVector == null))
			{
#line 157 "../../../Source/Core/ValueType.nll"
				pValidator.AddError("m_pGenericValueTypeVector null mismatch", pToken.m_sFileName, pToken.m_nLine, pToken.m_nColumn);
#line 158 "../../../Source/Core/ValueType.nll"
				return false;
			}
#line 161 "../../../Source/Core/ValueType.nll"
			if (m_pGenericValueTypeVector != null)
			{
#line 163 "../../../Source/Core/ValueType.nll"
				if (m_pGenericValueTypeVector.GetSize() != pTo.m_pGenericValueTypeVector.GetSize())
				{
#line 165 "../../../Source/Core/ValueType.nll"
					pValidator.AddError("m_pGenericValueTypeVector size mismatch", pToken.m_sFileName, pToken.m_nLine, pToken.m_nColumn);
#line 166 "../../../Source/Core/ValueType.nll"
					return false;
				}
#line 169 "../../../Source/Core/ValueType.nll"
				for (int i = 0; i < m_pGenericValueTypeVector.GetSize(); i++)
				{
					ValueType pSubFrom = m_pGenericValueTypeVector.Get(i);
					ValueType pSubTo = pTo.m_pGenericValueTypeVector.Get(i);
#line 186 "../../../Source/Core/ValueType.nll"
					if (pSubFrom.m_ePointerType != pSubTo.m_ePointerType)
					{
#line 188 "../../../Source/Core/ValueType.nll"
						pValidator.AddError("sub pointer type mismatch", pToken.m_sFileName, pToken.m_nLine, pToken.m_nColumn);
#line 189 "../../../Source/Core/ValueType.nll"
						return false;
					}
				}
			}
#line 195 "../../../Source/Core/ValueType.nll"
			return true;
		}

#line 198 "../../../Source/Core/ValueType.nll"
		public TypeRef CreateTypeRef()
		{
			TypeRef pTypeRef = new TypeRef();
#line 201 "../../../Source/Core/ValueType.nll"
			pTypeRef.m_bConst = m_bConst;
#line 202 "../../../Source/Core/ValueType.nll"
			pTypeRef.m_ePointerType = m_ePointerType;
#line 204 "../../../Source/Core/ValueType.nll"
			switch (m_eType)
			{
				case Type.CLASS_DECL_VALUE:
				{
#line 208 "../../../Source/Core/ValueType.nll"
					pTypeRef.m_pCloneToken = new Token();
#line 209 "../../../Source/Core/ValueType.nll"
					pTypeRef.m_pCloneToken.m_eType = Token.Type.TOKEN_IDENTIFIER;
#line 210 "../../../Source/Core/ValueType.nll"
					pTypeRef.m_pCloneToken.m_sValue = new InternalString(m_pClassDecl.m_pNameToken.m_sValue.GetExternalString());
#line 211 "../../../Source/Core/ValueType.nll"
					pTypeRef.m_pTypeToken = pTypeRef.m_pCloneToken;
#line 214 "../../../Source/Core/ValueType.nll"
					if (m_pGenericValueTypeVector != null)
					{
#line 216 "../../../Source/Core/ValueType.nll"
						for (int i = 0; i < m_pGenericValueTypeVector.GetSize(); i++)
						{
							TypeRef pGenericTypeRef = m_pGenericValueTypeVector.Get(i).CreateTypeRef();
#line 219 "../../../Source/Core/ValueType.nll"
							pTypeRef.m_pGenericTypeRefVector.PushBack(pGenericTypeRef);
							NumbatLogic.TypeRef __3752644072 = pGenericTypeRef;
#line 220 "../../../Source/Core/ValueType.nll"
							pGenericTypeRef = null;
#line 220 "../../../Source/Core/ValueType.nll"
							pTypeRef.AddChild(__3752644072);
						}
					}
					NamespaceNode pNamespaceNode = m_pClassDecl.m_pNamespaceNode;
#line 227 "../../../Source/Core/ValueType.nll"
					while (pNamespaceNode != null && pNamespaceNode.m_sName != null)
					{
						TypeRef pNamespaceTypeRef = new TypeRef();
#line 231 "../../../Source/Core/ValueType.nll"
						pNamespaceTypeRef.m_pCloneToken = new Token();
#line 232 "../../../Source/Core/ValueType.nll"
						pNamespaceTypeRef.m_pCloneToken.m_eType = Token.Type.TOKEN_IDENTIFIER;
#line 233 "../../../Source/Core/ValueType.nll"
						pNamespaceTypeRef.m_pCloneToken.m_sValue = new InternalString(pNamespaceNode.m_sName.GetExternalString());
#line 234 "../../../Source/Core/ValueType.nll"
						pNamespaceTypeRef.m_pTypeToken = pNamespaceTypeRef.m_pCloneToken;
#line 236 "../../../Source/Core/ValueType.nll"
						pNamespaceTypeRef.m_pChildTypeRef = pTypeRef;
						NumbatLogic.TypeRef __975974828 = pTypeRef;
#line 237 "../../../Source/Core/ValueType.nll"
						pTypeRef = null;
#line 237 "../../../Source/Core/ValueType.nll"
						pNamespaceTypeRef.AddChild(__975974828);
						NumbatLogic.TypeRef __2554801001 = pNamespaceTypeRef;
#line 239 "../../../Source/Core/ValueType.nll"
						pNamespaceTypeRef = null;
#line 239 "../../../Source/Core/ValueType.nll"
						pTypeRef = __2554801001;
#line 241 "../../../Source/Core/ValueType.nll"
						pNamespaceNode = pNamespaceNode.m_pParent;
					}
					NumbatLogic.TypeRef __976040424 = pTypeRef;
#line 244 "../../../Source/Core/ValueType.nll"
					pTypeRef = null;
#line 244 "../../../Source/Core/ValueType.nll"
					return __976040424;
				}

				case Type.GENERIC_TYPE_DECL_VALUE:
				{
#line 248 "../../../Source/Core/ValueType.nll"
					pTypeRef.m_pCloneToken = new Token();
#line 249 "../../../Source/Core/ValueType.nll"
					pTypeRef.m_pCloneToken.m_eType = Token.Type.TOKEN_IDENTIFIER;
#line 250 "../../../Source/Core/ValueType.nll"
					pTypeRef.m_pCloneToken.m_sValue = new InternalString(m_pGenericTypeDecl.m_pFirstToken.m_sValue.GetExternalString());
#line 251 "../../../Source/Core/ValueType.nll"
					pTypeRef.m_pTypeToken = pTypeRef.m_pCloneToken;
					NumbatLogic.TypeRef __976106021 = pTypeRef;
#line 252 "../../../Source/Core/ValueType.nll"
					pTypeRef = null;
#line 252 "../../../Source/Core/ValueType.nll"
					return __976106021;
				}

			}
#line 256 "../../../Source/Core/ValueType.nll"
			Assert.Plz(false);
#line 257 "../../../Source/Core/ValueType.nll"
			return null;
		}

#line 260 "../../../Source/Core/ValueType.nll"
		public virtual void StringifyType(InternalString sOut)
		{
#line 262 "../../../Source/Core/ValueType.nll"
			switch (m_eType)
			{
				case Type.VOID:
				{
#line 264 "../../../Source/Core/ValueType.nll"
					sOut.Append("VOID");
#line 264 "../../../Source/Core/ValueType.nll"
					return;
				}

				case Type.INT:
				{
#line 265 "../../../Source/Core/ValueType.nll"
					sOut.Append("INT");
#line 265 "../../../Source/Core/ValueType.nll"
					return;
				}

				case Type.STRING:
				{
#line 266 "../../../Source/Core/ValueType.nll"
					sOut.Append("STRING");
#line 266 "../../../Source/Core/ValueType.nll"
					return;
				}

				case Type.BOOL:
				{
#line 267 "../../../Source/Core/ValueType.nll"
					sOut.Append("BOOL");
#line 267 "../../../Source/Core/ValueType.nll"
					return;
				}

				case Type.CHAR:
				{
#line 268 "../../../Source/Core/ValueType.nll"
					sOut.Append("CHAR");
#line 268 "../../../Source/Core/ValueType.nll"
					return;
				}

				case Type.UNICHAR:
				{
#line 269 "../../../Source/Core/ValueType.nll"
					sOut.Append("UNICHAR");
#line 269 "../../../Source/Core/ValueType.nll"
					return;
				}

				case Type.INSTANCE:
				{
#line 270 "../../../Source/Core/ValueType.nll"
					sOut.Append("INSTANCE");
#line 270 "../../../Source/Core/ValueType.nll"
					return;
				}

				case Type.VOIDPTR:
				{
#line 271 "../../../Source/Core/ValueType.nll"
					sOut.Append("VOIDPTR");
#line 271 "../../../Source/Core/ValueType.nll"
					return;
				}

				case Type.CLASS_DECL:
				{
#line 272 "../../../Source/Core/ValueType.nll"
					sOut.Append("CLASS_DECL");
#line 272 "../../../Source/Core/ValueType.nll"
					return;
				}

				case Type.CLASS_DECL_VALUE:
				{
#line 273 "../../../Source/Core/ValueType.nll"
					sOut.Append("CLASS_DECL_VALUE");
#line 273 "../../../Source/Core/ValueType.nll"
					return;
				}

				case Type.ENUM_DECL:
				{
#line 274 "../../../Source/Core/ValueType.nll"
					sOut.Append("ENUM_DECL");
#line 274 "../../../Source/Core/ValueType.nll"
					return;
				}

				case Type.ENUM_DECL_VALUE:
				{
#line 275 "../../../Source/Core/ValueType.nll"
					sOut.Append("ENUM_DECL_VALUE");
#line 275 "../../../Source/Core/ValueType.nll"
					return;
				}

				case Type.GENERIC_TYPE_DECL_VALUE:
				{
#line 276 "../../../Source/Core/ValueType.nll"
					sOut.Append("GENERIC_TYPE_DECL_VALUE");
#line 276 "../../../Source/Core/ValueType.nll"
					return;
				}

				case Type.STATIC_ARRAY:
				{
#line 277 "../../../Source/Core/ValueType.nll"
					sOut.Append("STATIC_ARRAY");
#line 277 "../../../Source/Core/ValueType.nll"
					return;
				}

				case Type.NULL_VALUE:
				{
#line 278 "../../../Source/Core/ValueType.nll"
					sOut.Append("NULL_VALUE");
#line 278 "../../../Source/Core/ValueType.nll"
					return;
				}

				case Type.DELEGATE_DECL_VALUE:
				{
#line 279 "../../../Source/Core/ValueType.nll"
					sOut.Append("DELEGATE_DECL_VALUE");
#line 279 "../../../Source/Core/ValueType.nll"
					return;
				}

				case Type.FUNCTION_DECL:
				{
#line 280 "../../../Source/Core/ValueType.nll"
					sOut.Append("FUNCTION_DECL");
#line 280 "../../../Source/Core/ValueType.nll"
					return;
				}

				case Type.NAMESPACE_NODE:
				{
#line 281 "../../../Source/Core/ValueType.nll"
					sOut.Append("NAMESPACE_NODE");
#line 281 "../../../Source/Core/ValueType.nll"
					return;
				}

			}
#line 283 "../../../Source/Core/ValueType.nll"
			sOut.Append("???");
		}

#line 286 "../../../Source/Core/ValueType.nll"
		public static void StringifyPointerType(InternalString sOut, TypeRef.PointerType ePointerType)
		{
#line 288 "../../../Source/Core/ValueType.nll"
			switch (ePointerType)
			{
				case TypeRef.PointerType.SHARED:
				{
#line 290 "../../../Source/Core/ValueType.nll"
					sOut.Append("SHARED");
#line 290 "../../../Source/Core/ValueType.nll"
					return;
				}

				case TypeRef.PointerType.OWNED:
				{
#line 291 "../../../Source/Core/ValueType.nll"
					sOut.Append("OWNED");
#line 291 "../../../Source/Core/ValueType.nll"
					return;
				}

				case TypeRef.PointerType.TRANSITON:
				{
#line 292 "../../../Source/Core/ValueType.nll"
					sOut.Append("TRANSITON");
#line 292 "../../../Source/Core/ValueType.nll"
					return;
				}

				case TypeRef.PointerType.OWNED_PREASSSIGN:
				{
#line 293 "../../../Source/Core/ValueType.nll"
					sOut.Append("OWNED_PREASSSIGN");
#line 293 "../../../Source/Core/ValueType.nll"
					return;
				}

			}
#line 295 "../../../Source/Core/ValueType.nll"
			sOut.Append("UNKNOWN_PTR");
		}

#line 4 "../../../Source/Core/ValueType.nll"
		~ValueType()
		{
		}

	}
}

