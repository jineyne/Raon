using Microsoft.Win32.SafeHandles;

namespace Raon.Core.FrontEnd;

public class TokenSafeHandle : SafeHandleZeroOrMinusOneIsInvalid
{
    public TokenSafeHandle() : base(true) { }

    public IntPtr Ptr => handle;

    protected override bool ReleaseHandle()
    {
        TokenWrapper.FreeToken(this.handle);
        return true;
    }
}