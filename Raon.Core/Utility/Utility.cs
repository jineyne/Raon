using System.Runtime.InteropServices;

namespace Raon.Core.Utility;

internal class Utility : NativeWrapper
{
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void LoggerDelegate([MarshalAs(UnmanagedType.LPWStr)] string msg);

    [DllImport(DllName, EntryPoint = "InitRaon")]
    internal static extern void InitRaon();

    [DllImport(DllName, EntryPoint = "AddLogger")]
    internal static extern void AddLogger(LoggerDelegate @delegate);
}