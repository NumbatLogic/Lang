namespace NumberDuck
{
	namespace Secret
	{
		class Util
		{
			public static void Pad(int nDepth, InternalString sOut)
			{
				for (int i = 0; i < nDepth; i = i + 1)
					sOut.AppendChar('\t');
			}

			public static uint BadHash(InternalString sString)
			{
				Blob pBlob = new Blob(true);
				BlobView pBlobView = pBlob.GetBlobView();
				for (int i = 0; i < sString.GetLength(); i++)
				{
					char nChar = sString.GetChar(i);
					pBlobView.PackUint32(nChar);
				}
				uint nHaxTemp = pBlob.GetMsoCrc32();
				{
					return nHaxTemp;
				}
			}

		}
	}
}

