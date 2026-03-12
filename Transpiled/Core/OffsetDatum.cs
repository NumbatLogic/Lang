#line 1 "../../../Source/Core/OffsetDatum.nll"
namespace NumbatLogic
{
	class OffsetDatum
	{
		public int m_nOffset;
#line 7 "../../../Source/Core/OffsetDatum.nll"
		public static OffsetDatum Create(OffsetDatum pOther)
		{
			OffsetDatum pThis = new OffsetDatum();
			if (pOther != null)
				pThis.Set(pOther);
			NumbatLogic.OffsetDatum __3749477135 = pThis;
#line 12 "../../../Source/Core/OffsetDatum.nll"
			pThis = null;
#line 12 "../../../Source/Core/OffsetDatum.nll"
			return __3749477135;
		}

		public void Set(OffsetDatum pOther)
		{
			m_nOffset = pOther.m_nOffset;
		}

#line 3 "../../../Source/Core/OffsetDatum.nll"
		public OffsetDatum()
		{
		}

	}
}

