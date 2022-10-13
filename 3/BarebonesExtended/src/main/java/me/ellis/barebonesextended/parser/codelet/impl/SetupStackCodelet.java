package me.ellis.barebonesextended.parser.codelet.impl;

import me.ellis.barebonesextended.parser.codelet.ICodelet;

import java.util.Set;
import java.util.stream.Collectors;

public class SetupStackCodelet implements ICodelet {
    private final Set<String> referencedSymbols;

    public SetupStackCodelet(Set<String> referencedSymbols) {
        this.referencedSymbols = referencedSymbols;
    }

    @Override
    public String getCode() {
        return "long long int " + this.referencedSymbols.stream()
                .map(s -> s + ",")
                .collect(Collectors.joining())
                .replaceAll(",$", ";");
    }
}
