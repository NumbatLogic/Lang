namespace NumberDuck
{
    namespace Secret
    {
        class nbAssert
        {
            public static void Assert(bool result, string test, string file, int line)
            {
                if (!result)
                    throw new System.Exception(test + "\n" + file + ":" + line);
            }

            public static void Assert(bool result)
            {
                Assert(result, "", "", 0);
            }
        }
    }
}