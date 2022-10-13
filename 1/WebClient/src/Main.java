import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws IOException {
        new BufferedReader(new InputStreamReader((new URL("https://www.southampton.ac.uk/people/" + (new Scanner(System.in)).nextLine())).openStream())).lines().filter(l -> l.contains("og:title")).findAny().filter(l -> !l.contains("Find a person")).map(s -> s.split("content=\"")[1].split("\"")[0]).ifPresent(System.out::println);
    }
}