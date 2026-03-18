#include "OffsetDatum.hpp"

namespace NumbatLogic
{
	class OffsetDatum;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/OffsetDatum.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/OffsetDatum.nll"
#line 7 "/home/cliffya/git/Lang/Source/Core/OffsetDatum.nll"
	OffsetDatum* OffsetDatum::Create(OffsetDatum* pOther)
	{
		OffsetDatum* pThis = new OffsetDatum();
		if (pOther != 0)
			pThis->Set(pOther);
		NumbatLogic::OffsetDatum* __3749477135 = pThis;
#line 12 "/home/cliffya/git/Lang/Source/Core/OffsetDatum.nll"
		pThis = 0;
#line 12 "/home/cliffya/git/Lang/Source/Core/OffsetDatum.nll"
		return __3749477135;
	}

	void OffsetDatum::Set(OffsetDatum* pOther)
	{
		m_nOffset = pOther->m_nOffset;
	}

#line 3 "/home/cliffya/git/Lang/Source/Core/OffsetDatum.nll"
	OffsetDatum::OffsetDatum()
	{
		m_nOffset = 0;
	}

}

