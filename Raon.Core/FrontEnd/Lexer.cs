using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Raon.Core.FrontEnd;

public class Lexer : IDisposable
{
    readonly LexerSafeHandle _handle;
    private bool _disposedValue = false;

    public Lexer(string source)
    {
        _handle = LexerWrapper.CreateLexer(source);
    }

    public Token GetNextToken()
    {
        return new Token(LexerWrapper.GetNextToken(_handle));
    }

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
