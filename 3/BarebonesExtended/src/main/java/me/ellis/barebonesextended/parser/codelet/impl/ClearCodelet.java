package me.ellis.barebonesextended.parser.codelet.impl;

import me.ellis.barebonesextended.parser.codelet.ICodelet;

public class ClearCodelet implements ICodelet {
    private final String symbol;

    public ClearCodelet(String symbol) {
        this.symbol = symbol;
    }

    @Override
    public String getCode() {
        return this.symbol + " = 0;";
    }
}
