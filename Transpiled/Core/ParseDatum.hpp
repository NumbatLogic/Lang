#pragma once

namespace NumbatLogic
{
	class InternalString;
}
namespace NumbatLogic
{
	class ParseDatum
	{
		public: InternalString* m_sInput;
		public: InternalString* m_sCurrentRead;
		public: int m_nCurrentReadLine;
		public: int m_nCurrentReadColumn;
		public: InternalString* m_sFileName;
		public: int m_nLine;
		public: int m_nColumn;
		public: ParseDatum();
		public: void ClearCurrentRead();
		public: virtual ~ParseDatum();
	};
}

