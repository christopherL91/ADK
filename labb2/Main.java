/*
*  Credits:
*  Ursprunglig författare: Viggo Kann KTH viggo@nada.kth.se
*/

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.List;

public class Main {
    public static void main(String args[]) throws IOException {
        BufferedReader stdin = new BufferedReader(new InputStreamReader(System.in, "UTF-8"));
        List<String> wordList = readWordList(stdin);
        String word;

        while ((word = stdin.readLine()) != null) {
            ClosestWords closestWords = new ClosestWords(word, wordList);
            System.out.printf("%s (%d)",word,closestWords.getMinDistance());
            for (String w : closestWords.getClosestWords()) {
                System.out.printf(" %s",w);
            }
            System.out.println();
        }
    }

    public static List<String> readWordList(BufferedReader input) throws IOException {
        LinkedList<String> list = new LinkedList<String>();
        String line;

        while ((line = input.readLine()) != null) {
            if (line.equals("#")) {
                break;
            }
            list.add(line);
        }
        return list;
    }
}
