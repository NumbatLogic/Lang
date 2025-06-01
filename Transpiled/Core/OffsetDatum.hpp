#pragma once

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
		class OffsetDatum
		{
			public: int m_nOffset;
			public: static OffsetDatum* Create(OffsetDatum* pOther);
			public: void Set(OffsetDatum* pOther);
			public: OffsetDatum();
		};
	}
}

