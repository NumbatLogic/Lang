#line 0 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
	class MemberVarsSetDefaultStmt : AST
	{
		public MemberVarsSetDefaultStmt()
		{
			m_eType = AST.Type.MEMBER_VARS_SET_DEFAULT_STMT;
			m_bStatement = true;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			base.Validate(pValidator, pParent);
			if (m_pParent.m_eType == AST.Type.AST_SCOPE)
			{
				if (m_pParent.m_pParent.m_eType == AST.Type.AST_TOR_DECL)
				{
					TorDecl pTorDecl = (TorDecl)(m_pParent.m_pParent);
					if (pTorDecl.m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_CONSTRUCT)
					{
						if (m_pParent.m_pFirstChild != this)
						{
							pValidator.AddError("MemberVarsSetDefaultStmt should be first child of constructor", null, 0, 0);
							return;
						}
						if (pTorDecl.m_pParent.m_eType != AST.Type.AST_CLASS_DECL)
						{
							pValidator.AddError("MemberVarsSetDefaultStmt parent constructor is not child of a class decl???", null, 0, 0);
							return;
						}
						return;
					}
				}
			}
			pValidator.AddError("Expected parent to be constructor", null, 0, 0);
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder out)
		{
			if (eLanguage == AST.Language.CPP)
			{
				AST pChild = m_pParent.m_pParent.m_pParent.m_pFirstChild;
				while (pChild != null)
				{
					if (pChild.m_eType == AST.Type.AST_MEMBER_VAR_DECL)
					{
						MemberVarDecl pMemberVarDecl = (MemberVarDecl)(pChild);
						if (!pMemberVarDecl.m_bStatic)
						{
							Project pProject = GetProject();
							if (pProject == null || pProject.m_pValidator == null)
								continue;
							ValueType pValueType = pMemberVarDecl.m_pVarDecl.m_pTypeRef.GetRecursiveValueType(pProject.m_pValidator.m_pResolver);
							if (!pMemberVarDecl.m_pVarDecl.m_pTypeRef.m_bConst)
							{
								if (pMemberVarDecl.m_pVarDecl.m_pArraySizeVector != null)
								{
									int nArraySizeSize = pMemberVarDecl.m_pVarDecl.m_pArraySizeVector.GetSize();
									for (int i = 0; i < nArraySizeSize; i++)
									{
										AST pArraySize = pMemberVarDecl.m_pVarDecl.m_pArraySizeVector.Get(i);
										Util.Pad(nDepth + i, out.m_sOut);
										out.m_sOut.Append("for (int _x");
										out.m_sOut.AppendInt(i);
										out.m_sOut.Append(" = 0; _x");
										out.m_sOut.AppendInt(i);
										out.m_sOut.Append(" < ");
										pArraySize.Stringify(eLanguage, eOutputFile, 0, out);
										out.m_sOut.Append("; _x");
										out.m_sOut.AppendInt(i);
										out.m_sOut.Append("++)\n");
									}
									Util.Pad(nDepth + nArraySizeSize, out.m_sOut);
									out.m_sOut.AppendString(pMemberVarDecl.m_pVarDecl.m_pNameToken.GetString());
									for (int i = 0; i < nArraySizeSize; i++)
									{
										out.m_sOut.Append("[_x");
										out.m_sOut.AppendInt(i);
										out.m_sOut.Append("]");
									}
									out.m_sOut.Append(" = ");
									switch (pValueType.m_eType)
									{
										case ValueType.Type.INT:
										{
											out.m_sOut.Append("0");
#line 99 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											break;
										}

										case ValueType.Type.BOOL:
										{
											out.m_sOut.Append("false");
#line 104 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											break;
										}

										case ValueType.Type.CHAR:
										case ValueType.Type.UNICHAR:
										{
											out.m_sOut.Append("'0'");
#line 110 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											break;
										}

										case ValueType.Type.CLASS_DECL_VALUE:
										case ValueType.Type.GENERIC_TYPE_DECL_VALUE:
										case ValueType.Type.DELEGATE_DECL_VALUE:
										case ValueType.Type.VOIDPTR:
										case ValueType.Type.STRING:
										{
											out.m_sOut.Append("0");
#line 119 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											break;
										}

										case ValueType.Type.ENUM_DECL_VALUE:
										{
											if (pValueType.m_pEnumDecl == null)
												out.m_sOut.Append("no_m_pEnumDecl");
											EnumDeclValue pEnumDeclValue = pValueType.m_pEnumDecl.m_pEnumDeclValueVector.Get(0);
											if (pValueType.m_pEnumDecl == null)
												out.m_sOut.Append("no_pEnumDeclValue");
											pMemberVarDecl.m_pVarDecl.m_pTypeRef.Stringify(eLanguage, eOutputFile, 0, out);
											out.m_sOut.Append("::");
											pEnumDeclValue.m_pFirstToken.Stringify(out.m_sOut);
#line 132 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											break;
										}

										default:
										{
											out.m_sOut.Append("???");
											pValueType.StringifyType(out.m_sOut);
#line 138 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											break;
										}

									}
									out.m_sOut.Append(";\n");
								}
								else
								{
									Util.Pad(nDepth, out.m_sOut);
									out.m_sOut.AppendString(pMemberVarDecl.m_pVarDecl.m_pNameToken.GetString());
									out.m_sOut.Append(" = ");
									switch (pValueType.m_eType)
									{
										case ValueType.Type.INT:
										{
											out.m_sOut.Append("0");
#line 154 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											break;
										}

										case ValueType.Type.BOOL:
										{
											out.m_sOut.Append("false");
#line 159 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											break;
										}

										case ValueType.Type.CHAR:
										case ValueType.Type.UNICHAR:
										{
											out.m_sOut.Append("'0'");
#line 165 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											break;
										}

										case ValueType.Type.CLASS_DECL_VALUE:
										case ValueType.Type.GENERIC_TYPE_DECL_VALUE:
										case ValueType.Type.DELEGATE_DECL_VALUE:
										case ValueType.Type.VOIDPTR:
										case ValueType.Type.STRING:
										{
											out.m_sOut.Append("0");
#line 174 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											break;
										}

										case ValueType.Type.ENUM_DECL_VALUE:
										{
											if (pValueType.m_pEnumDecl == null)
												out.m_sOut.Append("no_m_pEnumDecl");
											EnumDeclValue pEnumDeclValue = pValueType.m_pEnumDecl.m_pEnumDeclValueVector.Get(0);
											if (pValueType.m_pEnumDecl == null)
												out.m_sOut.Append("no_pEnumDeclValue");
											pMemberVarDecl.m_pVarDecl.m_pTypeRef.Stringify(eLanguage, eOutputFile, 0, out);
											out.m_sOut.Append("::");
											pEnumDeclValue.m_pFirstToken.Stringify(out.m_sOut);
#line 187 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											break;
										}

										default:
										{
											out.m_sOut.Append("???");
											pValueType.StringifyType(out.m_sOut);
#line 193 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											break;
										}

									}
									out.m_sOut.Append(";\n");
								}
							}
						}
					}
					pChild = pChild.m_pNextSibling;
				}
			}
		}

	}
}

