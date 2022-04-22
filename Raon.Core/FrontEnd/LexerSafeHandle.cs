using Microsoft.Win32.SafeHandles;

namespace Raon.Core.FrontEnd;

internal class LexerSafeHandle : SafeHandleZeroOrMinusOneIsInvalid
{
    public LexerSafeHandle() : base(true) { }

    public IntPtr Ptr => handle;

    protected override bool ReleaseHandle()
    {
        LexerWrapper.FreeLexer(this.handle);
        return true;
    }
}
