package me.ellis.barebonesextended.parser.codelet.impl;

import me.ellis.barebonesextended.parser.codelet.ICodelet;

public class EndCodelet implements ICodelet {
    @Override
    public String getCode() {
        return "}";
    }
}
