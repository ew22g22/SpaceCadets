package me.ellis.barebonesextended.parser.codelet.impl;

import me.ellis.barebonesextended.parser.codelet.ICodelet;

public class WhileCodelet implements ICodelet {
    private final String symbol;

    public WhileCodelet(String symbol) {
        this.symbol = symbol;
    }

    @Override
    public String getCode() {
        return "while (" + symbol + " != 0) {";
    }
}
