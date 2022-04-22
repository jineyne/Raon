using System;
using NUnit.Framework;
using Raon.Core.FrontEnd;

namespace Raon.Core.Tests.Syntastics;

[TestFixture]
public class LexerTest
{
    [Test]
    public void GetNextTokenTest()
    {
        using (Lexer lexer = new Lexer("1 + \"1\" * 2 - 3.0"))
        {
            Assert.That(lexer.GetNextToken().Type, Is.EqualTo(TokenType.TOKEN_INTEGER));
            Assert.That(lexer.GetNextToken().Type, Is.EqualTo(TokenType.TOKEN_PLUS));
            Assert.That(lexer.GetNextToken().Type, Is.EqualTo(TokenType.TOKEN_STRING));
            Assert.That(lexer.GetNextToken().Type, Is.EqualTo(TokenType.TOKEN_ASTERISK));
            Assert.That(lexer.GetNextToken().Type, Is.EqualTo(TokenType.TOKEN_INTEGER));
            Assert.That(lexer.GetNextToken().Type, Is.EqualTo(TokenType.TOKEN_MINUS));
            Assert.That(lexer.GetNextToken().Type, Is.EqualTo(TokenType.TOKEN_REAL));
        }

        using (Lexer lexer = new Lexer(@"a = 1 + ""1\"" * 2 - 3.0
b = a / 10"))
        {
            Assert.That(lexer.GetNextToken().Type, Is.EqualTo(TokenType.TOKEN_IDENTIFIER));
            Assert.That(lexer.GetNextToken().Type, Is.EqualTo(TokenType.TOKEN_ASSIGN));
            Assert.That(lexer.GetNextToken().Type, Is.EqualTo(TokenType.TOKEN_INTEGER));
            Assert.That(lexer.GetNextToken().Type, Is.EqualTo(TokenType.TOKEN_PLUS));
            Assert.That(lexer.GetNextToken().Type, Is.EqualTo(TokenType.TOKEN_STRING));
            Assert.That(lexer.GetNextToken().Type, Is.EqualTo(TokenType.TOKEN_ASTERISK));
            Assert.That(lexer.GetNextToken().Type, Is.EqualTo(TokenType.TOKEN_INTEGER));
            Assert.That(lexer.GetNextToken().Type, Is.EqualTo(TokenType.TOKEN_MINUS));
            Assert.That(lexer.GetNextToken().Type, Is.EqualTo(TokenType.TOKEN_REAL));
            Assert.That(lexer.GetNextToken().Type, Is.EqualTo(TokenType.TOKEN_EOL));
            Assert.That(lexer.GetNextToken().Type, Is.EqualTo(TokenType.TOKEN_IDENTIFIER));
            Assert.That(lexer.GetNextToken().Type, Is.EqualTo(TokenType.TOKEN_ASSIGN));
            Assert.That(lexer.GetNextToken().Type, Is.EqualTo(TokenType.TOKEN_IDENTIFIER));
            Assert.That(lexer.GetNextToken().Type, Is.EqualTo(TokenType.TOKEN_SLASH));
            Assert.That(lexer.GetNextToken().Type, Is.EqualTo(TokenType.TOKEN_INTEGER));
        }
    }
}