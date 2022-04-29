using System.Runtime.InteropServices;
using Raon.Core.Runtime;

namespace Raon.Core.Console.Tests;

internal class Program
{
    [DllImport("kernel32.dll")]
    public static extern bool SetStdHandle(int stdHandle, IntPtr handle);

    [DllImport("kernel32.dll")]
    public static extern bool AllocConsole();

    [DllImport("stdout.dll")]
    public static extern void HelloWorld();

    private static void Main(string[] args)
    {
        Raon.Init();

        System.Console.WriteLine("****************************");
        System.Console.WriteLine("*** Raon Script Console! ***");
        System.Console.WriteLine("****************************");

        var vm = new VM();
        var running = true;

        while (running)
        {
            System.Console.Write(">> ");

            var line = System.Console.ReadLine();
            if (line == null) break;

            if (line.StartsWith("."))
            {
                var cmd = line.Substring(1).ToLower();
                switch (cmd)
                {
                    case "exit":
                        running = false;
                        continue;

                    default:
                        System.Console.WriteLine("[Raon.Script] invalid command");
                        break;
                }
            }

            vm.ExecuteSource(line);
        }

        System.Console.WriteLine("[Raon.Script] good bye.");
    }
}