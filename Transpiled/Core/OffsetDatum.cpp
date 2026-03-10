#include "OffsetDatum.hpp"

namespace NumbatLogic
{
	class OffsetDatum;
}
#line 0 "../../../Source/Core/OffsetDatum.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/OffsetDatum.nll"
#line 7 "../../../Source/Core/OffsetDatum.nll"
	OffsetDatum* OffsetDatum::Create(OffsetDatum* pOther)
	{
		OffsetDatum* pThis = new OffsetDatum();
#line 10 "../../../Source/Core/OffsetDatum.nll"
		if (pOther != 0)
#line 11 "../../../Source/Core/OffsetDatum.nll"
			pThis->Set(pOther);
		NumbatLogic::OffsetDatum* __3749477135 = pThis;
#line 12 "../../../Source/Core/OffsetDatum.nll"
		pThis = 0;
#line 12 "../../../Source/Core/OffsetDatum.nll"
		return __3749477135;
	}

#line 15 "../../../Source/Core/OffsetDatum.nll"
	void OffsetDatum::Set(OffsetDatum* pOther)
	{
#line 17 "../../../Source/Core/OffsetDatum.nll"
		m_nOffset = pOther->m_nOffset;
	}

#line 3 "../../../Source/Core/OffsetDatum.nll"
	OffsetDatum::OffsetDatum()
	{
		m_nOffset = 0;
	}

}

