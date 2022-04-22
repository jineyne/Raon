using System.Runtime.InteropServices;

namespace Raon.Core.FrontEnd;

public class Token : IDisposable
{
    readonly TokenSafeHandle _handle;
    private bool _disposedValue = false;

    public Token(TokenSafeHandle handle)
    {
        _handle = handle;
    }

    public TokenType Type => TokenWrapper.GetTokenType(_handle);

    public Int64 AsInteger => TokenWrapper.GetTokenValueAsInteger(_handle);

    public double AsReal => TokenWrapper.GetTokenValueAsReal(_handle);

    public string AsString => TokenWrapper.GetTokenValueAsCString(_handle);

    protected virtual void Dispose(bool disposing)
    {
        if (!_disposedValue)
        {
            if (_handle != null && !_handle.IsInvalid)
            {
                _handle.Dispose();
            }

            _disposedValue = true;
        }
    }

    public void Dispose()
    {
        Dispose(true);
        GC.SuppressFinalize(this);
    }
}