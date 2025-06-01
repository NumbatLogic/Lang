namespace NumberDuck
{
	namespace Secret
	{
		class OffsetDatum
		{
			public int m_nOffset;
			public static OffsetDatum Create(OffsetDatum pOther)
			{
				OffsetDatum pThis = new OffsetDatum();
				if (pOther != null)
					pThis.Set(pOther);
				{
					NumberDuck.Secret.OffsetDatum __186135525 = pThis;
					pThis = null;
					return __186135525;
				}
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
}

