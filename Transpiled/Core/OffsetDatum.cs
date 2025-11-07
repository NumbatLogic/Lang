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
			NumbatLogic.OffsetDatum __4031796760 = pThis;
			pThis = null;
			return __4031796760;
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

