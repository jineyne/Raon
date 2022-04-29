namespace Raon.Core;

public class Raon
{
    private static Utility.Utility.LoggerDelegate _delegateInstance;

    private static void Print(string msg)
    {
        Console.WriteLine(msg);
    }

    public static void Init()
    {
        Utility.Utility.InitRaon();

        //_delegateInstance = Print;
        //Utility.Utility.AddLogger(_delegateInstance);
    }
}