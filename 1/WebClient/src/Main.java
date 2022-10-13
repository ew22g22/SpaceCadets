import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws IOException {
                .filter(l -> l.contains("og:title"))
                .findAny()
                .ifPresent(s -> System.out.println(s.split("content=\"")[1].split("\"")[0]));
    }
}