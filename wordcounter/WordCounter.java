import java.io.File;
import java.io.FileWriter;
import java.io.FileNotFoundException;
import java.io.IOException;

import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.Files;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Scanner;

public class WordCounter {

    static int EXIT_FAILURE = 1;

    public static void main (String[] args) {

        if (args.length < 1) {
            System.err.println("Error: missing file argument.");
            System.exit(EXIT_FAILURE);
        }

        File file = new File(args[0]);

        if (!file.exists()) {
            System.err.printf("Error: file '%s' doesn't exist.\n", args[0]);
            System.exit(EXIT_FAILURE);
        }

        if (!file.canRead()) {
            System.err.println("Error: file is not readable.");
            System.exit(EXIT_FAILURE);
        }

        if (!getFileType(args[0]).equals("text/plain")) {
            System.err.println("Error: only 'text/plain' filetype is supported.");
            System.exit(EXIT_FAILURE);
        }

        if (file.length() == 0) {
            System.err.print("Error: File is empty.");
            System.exit(EXIT_FAILURE);
        }

        HashMap<String, Integer> wordsMap = readWordsIntoMap(file);

        for (String key: wordsMap.keySet()) {
            System.out.printf("%-20s %d\n", key, wordsMap.get(key));
        }

    }

    private static HashMap<String, Integer> readWordsIntoMap(File file) {
        Scanner scanner = getScanner(file);
        HashMap<String, Integer> wordsMap = new HashMap<String, Integer>();

        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            String[] words = splitIntoWords(line);
            for (String word : words) {
                if (wordsMap.containsKey(word)) {
                    wordsMap.put(word, wordsMap.get(word) + 1);
                } else {
                    wordsMap.put(word, 0);
                }
            }
        }

        scanner.close();
        return wordsMap;
    }

    private static String[] splitIntoWords(String line) {
        String[] words = line.split("[.,:;!?`'\"-- ]");
        return Arrays.stream(words).filter(s -> !s.isEmpty()).toArray(String[]::new);
    }

    private static Scanner getScanner(File file) {
        try {
            return new Scanner(file);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } return null;
    }

    private static String getFileType(String fileName) {
        try {
             return Files.probeContentType(Paths.get(fileName));
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }
    }

}
