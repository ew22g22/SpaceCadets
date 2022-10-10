
import interpreter.lexer.Lexer;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;
import java.util.stream.Collectors;

public class Main {
    public static void main(String[] args) throws FileNotFoundException {
        Scanner scanner = new Scanner(System.in);
        String filename = scanner.nextLine();
        File file = new File(filename);

        if (!file.exists()) {
            System.out.println("Please enter a valid .bb file");
            return;
        }

        Scanner reader = new Scanner(file);

        ArrayList<String> lines = new ArrayList<>();
        while (reader.hasNextLine())
            lines.add(reader.nextLine());

        Lexer lexer = new Lexer(lines.stream().flatMap(s -> Arrays.stream(s.split(" "))).collect(Collectors.toList()));
    }
}