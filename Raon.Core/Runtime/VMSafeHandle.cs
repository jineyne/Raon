using Microsoft.Win32.SafeHandles;

namespace Raon.Core.Runtime;

public class VMSafeHandle : SafeHandleZeroOrMinusOneIsInvalid
{
    public VMSafeHandle() : base(true)
    {
    }

    public IntPtr Ptr => handle;

    protected override bool ReleaseHandle()
    {
        VMWrapper.FreeVM(handle);
        return true;
    }
}