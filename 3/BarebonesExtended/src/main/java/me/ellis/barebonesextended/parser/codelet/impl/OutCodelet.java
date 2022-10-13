package me.ellis.barebonesextended.parser.codelet.impl;

import me.ellis.barebonesextended.parser.codelet.ICodelet;

public class OutCodelet implements ICodelet {
    private final String symbol;

    public OutCodelet(String symbol) {
        this.symbol = symbol;
    }

    @Override
    public String getCode() {
        return "printf(\"%lld\\n\", " + symbol + ");";
    }
}
