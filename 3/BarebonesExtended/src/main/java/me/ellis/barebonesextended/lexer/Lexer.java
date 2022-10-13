package me.ellis.barebonesextended.lexer;

import java.util.*;
import java.util.stream.Collectors;

public class Lexer {
    private final static Map<String, LexerToken> KEYWORD_TOKENS = new HashMap<>();

    static {
        KEYWORD_TOKENS.put("clear", new LexerToken(LexerTokenType.CLEAR));
        KEYWORD_TOKENS.put("incr", new LexerToken(LexerTokenType.INCR));
        KEYWORD_TOKENS.put("decr", new LexerToken(LexerTokenType.DECR));
        KEYWORD_TOKENS.put("while", new LexerToken(LexerTokenType.WHILE));
        KEYWORD_TOKENS.put("not", new LexerToken(LexerTokenType.NOT));
        KEYWORD_TOKENS.put("do", new LexerToken(LexerTokenType.DO));
        KEYWORD_TOKENS.put("end", new LexerToken(LexerTokenType.END));
        KEYWORD_TOKENS.put("in", new LexerToken(LexerTokenType.IN));
        KEYWORD_TOKENS.put("out", new LexerToken(LexerTokenType.OUT));
    }

    private final List<String> data;

    public Lexer(List<String> tokenData) {
        this.data = tokenData;
    }

    private Optional<Double> parseAsNumber(String t) {
        try {
            return Optional.of(Double.parseDouble(t));
        } catch (NumberFormatException ignored) {
            return Optional.empty();
        }
    }

    /***
     * Converts list of text tokens into LexerToken objects for use in Parser
     * @return List of LexerToken according to given list of text tokens in constructor
     */
    public List<LexerToken> lex() {
        return this.data.stream()
                .map(t -> {
                    // is an operator?
                    if (KEYWORD_TOKENS.containsKey(t))
                        return KEYWORD_TOKENS.get(t);

                    // not an operator therefore try a number literal & finally a symbol
                    return this.parseAsNumber(t)
                            .map(numVal -> new LexerToken(LexerTokenType.NUMBER, numVal))
                            .orElseGet(() -> new LexerToken(LexerTokenType.SYMBOL, t));
                })
                .collect(Collectors.toList());
    }
}
