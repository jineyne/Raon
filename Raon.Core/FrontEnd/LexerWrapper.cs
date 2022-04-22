using Raon.Core.Utility;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Raon.Core.FrontEnd;

internal class LexerWrapper : NativeWrapper
{
    [DllImport(DllName, EntryPoint = "CreateLexer")]
    internal static extern LexerSafeHandle CreateLexer([MarshalAs(UnmanagedType.LPWStr)] string source);

    [DllImport(DllName, EntryPoint = "FreeLexer")]
    internal static extern void FreeLexer(IntPtr lexer);

    [DllImport(DllName, EntryPoint = "GetNextToken")]
    internal static extern TokenSafeHandle GetNextToken(LexerSafeHandle lexer);
}
