#pragma once

namespace NumbatLogic
{
	class InternalString;
}
#line 1 "../../../Source/Core/ParseDatum.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/ParseDatum.nll"
	class ParseDatum
	{
#line 6 "../../../Source/Core/ParseDatum.nll"
		public: InternalString* m_sInput;
#line 7 "../../../Source/Core/ParseDatum.nll"
		public: InternalString* m_sCurrentRead;
#line 9 "../../../Source/Core/ParseDatum.nll"
		public: int m_nCurrentReadLine;
#line 10 "../../../Source/Core/ParseDatum.nll"
		public: int m_nCurrentReadColumn;
#line 12 "../../../Source/Core/ParseDatum.nll"
		public: InternalString* m_sFileName;
#line 13 "../../../Source/Core/ParseDatum.nll"
		public: int m_nLine;
#line 14 "../../../Source/Core/ParseDatum.nll"
		public: int m_nColumn;
#line 16 "../../../Source/Core/ParseDatum.nll"
		public: ParseDatum();
#line 24 "../../../Source/Core/ParseDatum.nll"
		public: void ClearCurrentRead();
#line 4 "../../../Source/Core/ParseDatum.nll"
		public: virtual ~ParseDatum();
	};
}

