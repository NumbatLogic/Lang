#line 1 "../../../Source/Core/OffsetDatum.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/OffsetDatum.nll"
	class OffsetDatum
	{
#line 5 "../../../Source/Core/OffsetDatum.nll"
		public int m_nOffset;
#line 7 "../../../Source/Core/OffsetDatum.nll"
		public static OffsetDatum Create(OffsetDatum pOther)
		{
#line 9 "../../../Source/Core/OffsetDatum.nll"
			OffsetDatum pThis = new OffsetDatum();
#line 10 "../../../Source/Core/OffsetDatum.nll"
			if (pOther != null)
#line 11 "../../../Source/Core/OffsetDatum.nll"
				pThis.Set(pOther);
			NumbatLogic.OffsetDatum __3749477135 = pThis;
#line 12 "../../../Source/Core/OffsetDatum.nll"
			pThis = null;
#line 12 "../../../Source/Core/OffsetDatum.nll"
			return __3749477135;
		}

#line 15 "../../../Source/Core/OffsetDatum.nll"
		public void Set(OffsetDatum pOther)
		{
#line 17 "../../../Source/Core/OffsetDatum.nll"
			m_nOffset = pOther.m_nOffset;
		}

#line 3 "../../../Source/Core/OffsetDatum.nll"
		public OffsetDatum()
		{
		}

	}
}

