package me.ellis.barebonesextended.lexer;

import me.ellis.barebonesextended.parser.codelet.ICodelet;
import me.ellis.barebonesextended.parser.codelet.impl.*;

public enum LexerTokenType {
    SYMBOL(null),
    NUMBER(null),
    CLEAR(ClearCodelet.class),
    INCR(IncrCodelet.class),
    DECR(DecrCodelet.class),
    WHILE(WhileCodelet.class),
    NOT(null),
    DO(null),
    END(EndCodelet.class),
    IN(InCodelet.class),
    OUT(OutCodelet.class);

    private final Class<? extends ICodelet> clazz;

    LexerTokenType(Class<? extends ICodelet> clazz) {
        this.clazz = clazz;
    }

    public Class<? extends ICodelet> getCodeletClass() {
        return this.clazz;
    }
}
