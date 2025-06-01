using NumberDuck.Secret;

class Application
{
	static void Main(string[] args)
	{
		Vector<string> pArgVector = new Vector<string>();
		for (int i = 0; i < args.Length; i++)
			pArgVector.PushBack(args[i]);

		CLI.Run(pArgVector);
	}
}
