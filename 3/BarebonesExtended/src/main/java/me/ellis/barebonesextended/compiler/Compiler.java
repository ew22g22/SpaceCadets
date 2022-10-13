package me.ellis.barebonesextended.compiler;

import me.ellis.barebonesextended.parser.ParserInfo;
import me.ellis.barebonesextended.parser.codelet.ICodelet;

import java.util.Deque;
import java.util.Set;

public class Compiler {
    private final Deque<ICodelet> codeletQueue;
    private final Set<String> referencedSymbols;

    public Compiler(ParserInfo parserInfo) {
        this.codeletQueue = parserInfo.getCodeletQueue();
        this.referencedSymbols = parserInfo.getReferencedSymbols();
    }

    public String generateCompilerOutput() {
        // should be at the end of the deque
        ICodelet setupCodelet = this.codeletQueue.pollLast();

        if (setupCodelet == null)
            return null;

        // include C standard io library and setup entry point
        StringBuilder code = new StringBuilder("#include <stdio.h> \n int main() {" + setupCodelet.getCode());

        // append the codelets to the output
        while (!this.codeletQueue.isEmpty()) {
            ICodelet codelet = this.codeletQueue.pollLast();
            code.append(codelet.getCode());
        }

        return code.append("}").toString();
    }
}
