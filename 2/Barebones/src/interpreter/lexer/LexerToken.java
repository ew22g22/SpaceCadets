package interpreter.lexer;

public class LexerToken {
    LexerTokenType type;
    String tokenValue = null;

    public LexerToken(LexerTokenType type) {
        this.type = type;
    }

    public LexerToken(LexerTokenType type, String value) {
        this.type = type;
        this.tokenValue = value;
    }
}
