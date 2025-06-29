namespace NumbatLogic
{
	class OffsetDatum
	{
		public int m_nOffset;
		public static OffsetDatum Create(OffsetDatum pOther)
		{
			OffsetDatum pThis = new OffsetDatum();
			if (pOther != null)
				pThis.Set(pOther);
			NumbatLogic.OffsetDatum __3620161242 = pThis;
			pThis = null;
			return __3620161242;
		}

		public void Set(OffsetDatum pOther)
		{
			m_nOffset = pOther.m_nOffset;
		}

		public OffsetDatum()
		{
		}

	}
}

