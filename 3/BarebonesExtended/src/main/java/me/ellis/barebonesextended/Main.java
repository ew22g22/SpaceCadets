package me.ellis.barebonesextended;

import me.ellis.barebonesextended.compiler.Compiler;
import me.ellis.barebonesextended.lexer.Lexer;
import me.ellis.barebonesextended.parser.Parser;

import java.io.*;
import java.lang.reflect.InvocationTargetException;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;
import java.util.stream.Collectors;

public class Main {
    public static void main(String[] args) throws IOException, NoSuchMethodException, InvocationTargetException, InstantiationException, IllegalAccessException {
        Scanner scanner = new Scanner(System.in);
        String filename = scanner.nextLine();
        BufferedReader reader = new BufferedReader(new FileReader(filename));

        // Read file lines, split by space, remove semicolons,
        // filter empty strings, collect to list of words
        List<String> tokens = reader.lines()
                .flatMap(l -> Arrays.stream(l.split(" ")))
                .map(t -> t.replace(";", ""))
                .filter(t -> t.length() > 0)
                .collect(Collectors.toList());

        Lexer lexer = new Lexer(tokens); // lex tokens
        Parser parser = new Parser(lexer.lex()); // parse result of lexer
        Compiler compiler = new Compiler(parser.parse()); // compile result of parser

        File file = new File("out.c");

        if (!file.exists())
            file.createNewFile();

        FileWriter writer = new FileWriter(file);
        writer.write(compiler.generateCompilerOutput());
        writer.close();
    }
}