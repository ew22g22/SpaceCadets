import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Main {
    public static void main(String[] args) throws IOException {
        System.getProperties().put("proxySet", "true");
        System.getProperties().put("proxyHost", "152.78.128.51");
        System.getProperties().put("proxyPort", "3128");


        Scanner scanner = new Scanner(System.in);
        String email = scanner.nextLine();
        String addr = "https://www.southampton.ac.uk/people/" + email.split("@")[0];
        URL url = new URL(addr);
        BufferedReader reader = new BufferedReader(new InputStreamReader(url.openStream()));

        List<String> list = new ArrayList<>();
        String line;
        while ((line = reader.readLine()) != null)
            list.add(line);

        if (String.join("", list).contains("Find a person")) {
            System.out.println("Failed to find that person.");
            return;
        }

        list.stream()
                .filter(l -> l.contains("og:title"))
                .findAny()
                .ifPresent(s -> System.out.println(s.split("content=\"")[1].split("\"")[0]));
    }
}