package me.ellis.barebonesextended.lexer;

public class LexerToken {
    private final LexerTokenType type;
    private String stringValue;
    private double numberValue;

    public LexerToken(LexerTokenType type) {
        this.type = type;
    }

    public LexerToken(LexerTokenType type, String stringValue) {
        this.type = type;
        this.stringValue = stringValue;
    }

    public LexerToken(LexerTokenType type, double numberValue) {
        this.type = type;
        this.numberValue = numberValue;
    }

    public LexerTokenType getType() {
        return this.type;
    }

    public String getStringValue() {
        return this.stringValue;
    }

    public double getNumberValue() {
        return this.numberValue;
    }
}
