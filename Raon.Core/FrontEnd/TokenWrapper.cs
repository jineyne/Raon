using System.Runtime.InteropServices;
using Raon.Core.Utility;

namespace Raon.Core.FrontEnd;

internal class TokenWrapper : NativeWrapper
{
    [DllImport(DllName, EntryPoint = "CreateToken")]
    internal static extern TokenSafeHandle CreateToken(int type);

    [DllImport(DllName, EntryPoint = "FreeToken")]
    internal static extern void FreeToken(IntPtr token);

    [DllImport(DllName, EntryPoint = "GetTokenType")]
    internal static extern TokenType GetTokenType(TokenSafeHandle token);

    [DllImport(DllName, EntryPoint = "GetTokenValueAsInteger")]
    internal static extern Int64 GetTokenValueAsInteger(TokenSafeHandle token);

    [DllImport(DllName, EntryPoint = "GetTokenValueAsReal")]
    internal static extern double GetTokenValueAsReal(TokenSafeHandle token);

    [DllImport(DllName, EntryPoint = "GetTokenValueAsCString")]
    [return: MarshalAs(UnmanagedType.LPWStr)]
    internal static extern String GetTokenValueAsCString(TokenSafeHandle token);
}