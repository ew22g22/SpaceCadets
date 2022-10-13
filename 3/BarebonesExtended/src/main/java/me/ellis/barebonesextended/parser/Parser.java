package me.ellis.barebonesextended.parser;

import me.ellis.barebonesextended.lexer.LexerToken;
import me.ellis.barebonesextended.lexer.LexerTokenType;
import me.ellis.barebonesextended.parser.codelet.ICodelet;
import me.ellis.barebonesextended.parser.codelet.impl.*;

import java.lang.reflect.InvocationTargetException;
import java.util.*;

/*WARNING: Very ugly class ^^*/
public class Parser {
    private final List<LexerToken> lexerTokens;
    private final Set<String> referencedSymbols = new HashSet<>();
    private final Deque<LexerToken> operatorQueue = new LinkedList<>();
    private final Deque<ICodelet> codeletQueue = new LinkedList<>();
    private LexerToken currentTok, lastTok;

    public Parser(List<LexerToken> lexerTokens) {
        this.lexerTokens = lexerTokens;
    }

    // handle operators like incr, decr and clear
    private void handleUnaryOperator() {
        this.operatorQueue.push(this.currentTok);
    }

    // handle symbols (variables)
    private void handleSymbol() throws NoSuchMethodException, InvocationTargetException, InstantiationException, IllegalAccessException {
        // add symbol to set of referenced symbol for stack setup
        this.referencedSymbols.add(this.currentTok.getStringValue());

        // if we are defining the start of a loop, add loop codelet and break
        if (this.lastTok != null && this.lastTok.getType() == LexerTokenType.WHILE) {
            this.codeletQueue.push(new WhileCodelet(this.currentTok.getStringValue()));
            return;
        }

        // now push operators from op deque onto the
        // codelet deque
        while (!this.operatorQueue.isEmpty()) {
            LexerToken op = this.operatorQueue.pollLast();
            this.codeletQueue.push(op.getType().getCodeletClass()
                    .getConstructor(String.class)
                    .newInstance(this.currentTok.getStringValue()));
        }
    }

    // end of while loop
    private void handleEnd() {
        this.codeletQueue.push(new EndCodelet());
    }

    public ParserInfo parse() throws NoSuchMethodException, InvocationTargetException, InstantiationException, IllegalAccessException {
        // loop over lexed tokens
        for (LexerToken tok : this.lexerTokens) {
            this.lastTok = this.currentTok;
            this.currentTok = tok;

            switch (tok.getType()) {
                case CLEAR:
                case INCR:
                case DECR:
                case IN:
                case OUT:
                    this.handleUnaryOperator();
                    break;
                case SYMBOL:
                    this.handleSymbol();
                    break;
                case END:
                    this.handleEnd();
                    break;
                default:
                    break;
            }
        }

        this.codeletQueue.addLast(new SetupStackCodelet(this.referencedSymbols));
        return new ParserInfo(this.referencedSymbols, this.codeletQueue);
    }
}
