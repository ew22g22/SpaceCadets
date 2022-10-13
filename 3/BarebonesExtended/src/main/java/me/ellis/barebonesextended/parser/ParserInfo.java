package me.ellis.barebonesextended.parser;

import me.ellis.barebonesextended.parser.codelet.ICodelet;

import java.util.Deque;
import java.util.Set;

public class ParserInfo {
    private final Set<String> referencedSymbols;
    private final Deque<ICodelet> codeletQueue;

    public ParserInfo(Set<String> referencedSymbols, Deque<ICodelet> codeletQueue) {
        this.referencedSymbols = referencedSymbols;
        this.codeletQueue = codeletQueue;
    }

    public Set<String> getReferencedSymbols() {
        return this.referencedSymbols;
    }

    public Deque<ICodelet> getCodeletQueue() {
        return this.codeletQueue;
    }
}
