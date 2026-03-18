#pragma once

namespace NumbatLogic
{
	class OffsetDatum;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/OffsetDatum.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/OffsetDatum.nll"
	class OffsetDatum
	{
		public: int m_nOffset;
#line 7 "/home/cliffya/git/Lang/Source/Core/OffsetDatum.nll"
		public: static OffsetDatum* Create(OffsetDatum* pOther);
#line 15 "/home/cliffya/git/Lang/Source/Core/OffsetDatum.nll"
		public: void Set(OffsetDatum* pOther);
#line 3 "/home/cliffya/git/Lang/Source/Core/OffsetDatum.nll"
		public: OffsetDatum();
	};
}

