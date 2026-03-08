#pragma once

namespace NumbatLogic
{
	class OffsetDatum;
}
#line 1 "../../../Source/Core/OffsetDatum.nll"
namespace NumbatLogic
{
	class OffsetDatum
	{
		public: int m_nOffset;
		public: static OffsetDatum* Create(OffsetDatum* pOther);
		public: void Set(OffsetDatum* pOther);
		public: OffsetDatum();
	};
}

