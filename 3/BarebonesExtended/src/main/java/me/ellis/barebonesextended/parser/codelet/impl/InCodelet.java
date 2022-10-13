package me.ellis.barebonesextended.parser.codelet.impl;

import me.ellis.barebonesextended.parser.codelet.ICodelet;

public class InCodelet implements ICodelet {
    private final String symbol;

    public InCodelet(String symbol) {
        this.symbol = symbol;
    }

    @Override
    public String getCode() {
        return "scanf(\"%lld\", &" + symbol + ");";
    }
}
