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
        Trie trie = readWordList(stdin);
        String word;

        while ((word = stdin.readLine()) != null) {
            CloserWords closestWords = new CloserWords(word, trie);
            int minDistance = closestWords.getMinDistance();
            System.out.printf("%s (%d)",word, minDistance);
            for (String w : closestWords.getClosestWords()) {
                System.out.printf(" %s",w);
            }
            System.out.println();
        }
    }

    public static Trie readWordList(BufferedReader input) throws IOException {
        Trie trie = new Trie();
        String line;

        while ((line = input.readLine()) != null) {
            if (line.equals("#")) {
                break;
            }
            trie.insert(line);
        }
        return trie;
    }
}
