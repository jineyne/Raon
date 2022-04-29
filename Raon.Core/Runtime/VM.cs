namespace Raon.Core.Runtime;

public class VM : IDisposable
{
    private readonly VMSafeHandle _handle;
    private bool _disposedValue;

    public VM()
    {
        _handle = VMWrapper.CreateVM();
    }

    public void Dispose()
    {
        Dispose(true);
    }

    public void ExecuteSource(string source)
    {
        VMWrapper.ExecuteSource(_handle, source);
    }

    protected virtual void Dispose(bool disposing)
    {
        if (!_disposedValue)
        {
            if (_handle != null && !_handle.IsInvalid) _handle.Dispose();

            _disposedValue = true;
        }
    }
}