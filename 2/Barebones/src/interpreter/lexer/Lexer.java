package interpreter.lexer;

import java.util.Deque;
import java.util.LinkedList;
import java.util.List;

public class Lexer {
    private final List<String> data;
    private int i = 0;
    private String word = null;
    private final List<LexerToken> tokens = new LinkedList<>();
    private final Deque<LexerToken> opStack = new LinkedList<>();


    public Lexer(List<String> data) {
        this.data = data;
    }

    private boolean incrementLexer() {
        if (this.i++ >= this.data.size())
            return false;

        this.word = this.data.get(i);
        return true;
    }

    private void handleClear() {
        this.opStack.push(new LexerToken(LexerTokenType.CLEAR));
    }

    private void handleSymbol() {
        tokens.add(new LexerToken(LexerTokenType.SYMBOL, this.word));
        tokens.addAll(this.opStack);
    }

    public void lex() {
        while (incrementLexer()) {
            switch (this.word) {
                case "clear":
                    this.handleClear();
                case "incr":
                    break;
                case "decr":
                    break;
                case "while":
                    break;
                case "not":
                    break;
                case "end":
                    break;
                case "do":
                    break;
                default:
                    this.handleSymbol();
                    break;
            }
        }
    }
}
