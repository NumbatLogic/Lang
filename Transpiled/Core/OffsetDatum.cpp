#include "OffsetDatum.hpp"

namespace NumberDuck
{
	namespace Secret
	{
		class OffsetDatum;
	}
}
namespace NumberDuck
{
	namespace Secret
	{
		OffsetDatum* OffsetDatum::Create(OffsetDatum* pOther)
		{
			OffsetDatum* pThis = new OffsetDatum();
			if (pOther != 0)
				pThis->Set(pOther);
			{
				NumberDuck::Secret::OffsetDatum* __186135525 = pThis;
				pThis = 0;
				return __186135525;
			}
		}

		void OffsetDatum::Set(OffsetDatum* pOther)
		{
			m_nOffset = pOther->m_nOffset;
		}

		OffsetDatum::OffsetDatum()
		{
			m_nOffset = 0;
		}

	}
}

