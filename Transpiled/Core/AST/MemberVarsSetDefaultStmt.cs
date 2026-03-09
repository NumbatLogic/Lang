#line 1 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
	class MemberVarsSetDefaultStmt : AST
	{
#line 6 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
		public MemberVarsSetDefaultStmt()
		{
#line 8 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
			m_eType = AST.Type.MEMBER_VARS_SET_DEFAULT_STMT;
#line 9 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
			m_bStatement = true;
		}

#line 12 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
#line 14 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
			base.Validate(pValidator, pParent);
#line 17 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
			if (m_pParent.m_eType == AST.Type.AST_SCOPE)
			{
#line 19 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
				if (m_pParent.m_pParent.m_eType == AST.Type.AST_TOR_DECL)
				{
					TorDecl pTorDecl = (TorDecl)(m_pParent.m_pParent);
#line 22 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
					if (pTorDecl.m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_CONSTRUCT)
					{
#line 24 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
						if (m_pParent.m_pFirstChild != this)
						{
#line 26 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
							pValidator.AddError("MemberVarsSetDefaultStmt should be first child of constructor", null, 0, 0);
#line 27 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
							return;
						}
#line 31 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
						if (pTorDecl.m_pParent.m_eType != AST.Type.AST_CLASS_DECL)
						{
#line 33 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
							pValidator.AddError("MemberVarsSetDefaultStmt parent constructor is not child of a class decl???", null, 0, 0);
#line 34 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
							return;
						}
#line 37 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
						return;
					}
				}
			}
#line 42 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
			pValidator.AddError("Expected parent to be constructor", null, 0, 0);
		}

#line 45 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 47 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
			if (eLanguage == AST.Language.CPP)
			{
				AST pChild = m_pParent.m_pParent.m_pParent.m_pFirstChild;
#line 50 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
				while (pChild != null)
				{
#line 52 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
					if (pChild.m_eType == AST.Type.AST_MEMBER_VAR_DECL)
					{
						MemberVarDecl pMemberVarDecl = (MemberVarDecl)(pChild);
#line 56 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
						if (!pMemberVarDecl.m_bStatic)
						{
							Project pProject = GetProject();
#line 59 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
							if (pProject == null || pProject.m_pValidator == null)
#line 60 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
								continue;
							ValueType pValueType = pMemberVarDecl.m_pVarDecl.m_pTypeRef.GetRecursiveValueType(pProject.m_pValidator.m_pResolver);
#line 63 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
							if (!pMemberVarDecl.m_pVarDecl.m_pTypeRef.m_bConst)
							{
#line 65 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
								if (pMemberVarDecl.m_pVarDecl.m_pArraySizeVector != null)
								{
									int nArraySizeSize = pMemberVarDecl.m_pVarDecl.m_pArraySizeVector.GetSize();
#line 68 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
									for (int i = 0; i < nArraySizeSize; i++)
									{
										AST pArraySize = pMemberVarDecl.m_pVarDecl.m_pArraySizeVector.Get(i);
#line 71 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										Util.Pad(nDepth + i, pOutputBuilder.m_sOut);
#line 72 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										pOutputBuilder.m_sOut.Append("for (int _x");
#line 73 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										pOutputBuilder.m_sOut.AppendInt(i);
#line 74 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										pOutputBuilder.m_sOut.Append(" = 0; _x");
#line 75 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										pOutputBuilder.m_sOut.AppendInt(i);
#line 76 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										pOutputBuilder.m_sOut.Append(" < ");
#line 77 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										pArraySize.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 78 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										pOutputBuilder.m_sOut.Append("; _x");
#line 79 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										pOutputBuilder.m_sOut.AppendInt(i);
#line 80 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										pOutputBuilder.m_sOut.Append("++)\n");
									}
#line 83 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
									Util.Pad(nDepth + nArraySizeSize, pOutputBuilder.m_sOut);
#line 84 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
									pOutputBuilder.m_sOut.AppendString(pMemberVarDecl.m_pVarDecl.m_pNameToken.GetString());
#line 86 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
									for (int i = 0; i < nArraySizeSize; i++)
									{
#line 88 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										pOutputBuilder.m_sOut.Append("[_x");
#line 89 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										pOutputBuilder.m_sOut.AppendInt(i);
#line 90 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
										pOutputBuilder.m_sOut.Append("]");
									}
#line 92 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
									pOutputBuilder.m_sOut.Append(" = ");
#line 95 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
									switch (pValueType.m_eType)
									{
										case ValueType.Type.INT:
										{
#line 99 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											pOutputBuilder.m_sOut.Append("0");
#line 100 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											break;
										}

										case ValueType.Type.BOOL:
										{
#line 104 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											pOutputBuilder.m_sOut.Append("false");
#line 105 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											break;
										}

										case ValueType.Type.CHAR:
										case ValueType.Type.UNICHAR:
										{
#line 110 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											pOutputBuilder.m_sOut.Append("'0'");
#line 111 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											break;
										}

										case ValueType.Type.CLASS_DECL_VALUE:
										case ValueType.Type.GENERIC_TYPE_DECL_VALUE:
										case ValueType.Type.DELEGATE_DECL_VALUE:
										case ValueType.Type.VOIDPTR:
										case ValueType.Type.STRING:
										{
#line 119 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											pOutputBuilder.m_sOut.Append("0");
#line 120 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											break;
										}

										case ValueType.Type.ENUM_DECL_VALUE:
										{
#line 124 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											if (pValueType.m_pEnumDecl == null)
#line 125 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
												pOutputBuilder.m_sOut.Append("no_m_pEnumDecl");
											EnumDeclValue pEnumDeclValue = pValueType.m_pEnumDecl.m_pEnumDeclValueVector.Get(0);
#line 127 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											if (pValueType.m_pEnumDecl == null)
#line 128 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
												pOutputBuilder.m_sOut.Append("no_pEnumDeclValue");
#line 130 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											pMemberVarDecl.m_pVarDecl.m_pTypeRef.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 131 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											pOutputBuilder.m_sOut.Append("::");
#line 132 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											pEnumDeclValue.m_pFirstToken.Stringify(pOutputBuilder.m_sOut);
#line 133 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											break;
										}

										default:
										{
#line 137 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											pOutputBuilder.m_sOut.Append("???");
#line 138 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											pValueType.StringifyType(pOutputBuilder.m_sOut);
#line 139 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											break;
										}

									}
#line 142 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
									pOutputBuilder.m_sOut.Append(";\n");
								}
								else
								{
#line 147 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
									Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 148 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
									pOutputBuilder.m_sOut.AppendString(pMemberVarDecl.m_pVarDecl.m_pNameToken.GetString());
#line 149 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
									pOutputBuilder.m_sOut.Append(" = ");
#line 150 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
									switch (pValueType.m_eType)
									{
										case ValueType.Type.INT:
										{
#line 154 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											pOutputBuilder.m_sOut.Append("0");
#line 155 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											break;
										}

										case ValueType.Type.BOOL:
										{
#line 159 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											pOutputBuilder.m_sOut.Append("false");
#line 160 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											break;
										}

										case ValueType.Type.CHAR:
										case ValueType.Type.UNICHAR:
										{
#line 165 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											pOutputBuilder.m_sOut.Append("'0'");
#line 166 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											break;
										}

										case ValueType.Type.CLASS_DECL_VALUE:
										case ValueType.Type.GENERIC_TYPE_DECL_VALUE:
										case ValueType.Type.DELEGATE_DECL_VALUE:
										case ValueType.Type.VOIDPTR:
										case ValueType.Type.STRING:
										{
#line 174 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											pOutputBuilder.m_sOut.Append("0");
#line 175 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											break;
										}

										case ValueType.Type.ENUM_DECL_VALUE:
										{
#line 179 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											if (pValueType.m_pEnumDecl == null)
#line 180 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
												pOutputBuilder.m_sOut.Append("no_m_pEnumDecl");
											EnumDeclValue pEnumDeclValue = pValueType.m_pEnumDecl.m_pEnumDeclValueVector.Get(0);
#line 182 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											if (pValueType.m_pEnumDecl == null)
#line 183 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
												pOutputBuilder.m_sOut.Append("no_pEnumDeclValue");
#line 185 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											pMemberVarDecl.m_pVarDecl.m_pTypeRef.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 186 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											pOutputBuilder.m_sOut.Append("::");
#line 187 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											pEnumDeclValue.m_pFirstToken.Stringify(pOutputBuilder.m_sOut);
#line 188 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											break;
										}

										default:
										{
#line 192 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											pOutputBuilder.m_sOut.Append("???");
#line 193 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											pValueType.StringifyType(pOutputBuilder.m_sOut);
#line 194 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
											break;
										}

									}
#line 197 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
									pOutputBuilder.m_sOut.Append(";\n");
								}
							}
						}
					}
#line 202 "../../../Source/Core/AST/MemberVarsSetDefaultStmt.nll"
					pChild = pChild.m_pNextSibling;
				}
			}
		}

	}
}

