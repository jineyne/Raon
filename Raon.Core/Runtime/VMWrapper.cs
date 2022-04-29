using System.Runtime.InteropServices;
using Raon.Core.Utility;

namespace Raon.Core.Runtime;

internal class VMWrapper : NativeWrapper
{
    [DllImport(DllName, EntryPoint = "CreateVM")]
    internal static extern VMSafeHandle CreateVM();

    [DllImport(DllName, EntryPoint = "FreeVM")]
    internal static extern void FreeVM(IntPtr vm);

    [DllImport(DllName, EntryPoint = "ExecuteSource")]
    internal static extern void ExecuteSource(VMSafeHandle vm, [MarshalAs(UnmanagedType.LPWStr)] string source);
}