package me.ellis.barebonesextended.parser.codelet.impl;

import me.ellis.barebonesextended.parser.codelet.ICodelet;

public class DecrCodelet implements ICodelet {
    private final String symbol;

    public DecrCodelet(String symbol) {
        this.symbol = symbol;
    }

    @Override
    public String getCode() {
        return this.symbol + "--;";
    }
}
