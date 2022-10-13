package me.ellis.barebones;

import java.io.*;
import java.util.*;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.function.BiConsumer;
import java.util.stream.Collectors;

public class Main {
    private final static Map<String, Integer> VARS = new HashMap<>();
    private final static LinkedList<Map<String, Integer>> CONDITIONAL_STACK = new LinkedList<>();
    private static BiConsumer<AtomicInteger, String> nextCommand = (i, s) -> {
    };
    private final static HashMap<String, BiConsumer<AtomicInteger, String>> NEXT_COMMAND_MAP = new HashMap<>();

    static {
        NEXT_COMMAND_MAP.put("clear", (i, s) -> VARS.put(s, 0));
        NEXT_COMMAND_MAP.put("incr", (i, s) -> VARS.compute(s, (k, v) -> v == null ? 1 : v + 1));
        NEXT_COMMAND_MAP.put("decr", (i, s) -> VARS.compute(s, (k, v) -> v == null ? -1 : v - 1));
        NEXT_COMMAND_MAP.put("while", (i, s) -> {
            CONDITIONAL_STACK.push(new HashMap<>());
            Objects.requireNonNull(CONDITIONAL_STACK.peekFirst()).put(s, i.get() + 3);
            i.set(i.get() + 3);
        });
    }

    public static void main(String[] args) throws FileNotFoundException {
        List<String> cs = new BufferedReader(new FileReader(new Scanner(System.in).nextLine())).lines().flatMap(l -> Arrays.stream(l.replace(";", "").split(" "))).filter(s -> s.length() > 0).collect(Collectors.toList());

        for (AtomicInteger i = new AtomicInteger(); i.get() < cs.size(); i.getAndIncrement()) {
            if (cs.get(i.get()).equals("end")) {
                Objects.requireNonNull(CONDITIONAL_STACK.peekFirst()).entrySet().stream().findFirst().ifPresent(e -> {
                    if (VARS.get(e.getKey()) == 0) {
                        CONDITIONAL_STACK.pop();
                    } else {
                        i.set(e.getValue());
                    }
                });
                continue;
            }

            if (NEXT_COMMAND_MAP.containsKey(cs.get(i.get()))) {
                nextCommand = NEXT_COMMAND_MAP.get(cs.get(i.get()));
            } else {
                nextCommand.accept(i, cs.get(i.get()));
            }
        }

        for (Map.Entry<String, Integer> e : VARS.entrySet())
            System.out.println(e.getKey() + ": " + e.getValue());
    }
}
