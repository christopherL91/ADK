/*
*  Credits:
*  Ursprunglig författare: Viggo Kann KTH viggo@nada.kth.se
*/

import java.util.Arrays;
import java.io.BufferedReader;
import java.io.InputStream;
import java.io.BufferedInputStream;
import java.util.Comparator;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.TreeSet;
import java.util.List;

public class Main {
    public static void main(String args[]) throws IOException {
        long start = System.currentTimeMillis();
        InputStream stdin = System.in;
        Result result = readWordList(stdin);
        ArrayList<String> dictionary = result.dictionary;
        String[] words = result.words;

        start = System.currentTimeMillis();
        MatrixWords closestWords = new MatrixWords();
        for(String word: words) {
            if(word == null) {
                break;
            }
            // CloserWords closestWords = new CloserWords(word, dictionary);
            closestWords.search(dictionary,word);
            int minDistance = closestWords.getMinDistance();
            System.out.print(word);
            System.out.print(" (");
            System.out.print(minDistance);
            System.out.print(")");
            for (String w : closestWords.getClosestWords()) {
                System.out.print(" ");
                System.out.print(w);
            }
            System.out.println();
        }
    }

    private static class Result {
        ArrayList<String> dictionary;
        String[] words;
        public Result(ArrayList<String> dictionary, String[] words) {
            this.dictionary = dictionary;
            this.words = words;
        }
    }

    public static Result readWordList(InputStream inputStream) throws IOException {
        ArrayList<String> dictionary = new ArrayList<String>(500000);

        int len = 4*1048576; // 4 MB
        byte[] buffer = new byte[len];
        int read;
        boolean misspelled = false;
        String[] misspelledWords = new String[100];
        int misspelledIndex = 0;
        int offset = 0;
        while ((read = inputStream.read(buffer,offset, len-offset)) != -1)
        {
            int lastBreak = -1;
            for(int i = offset+read-1; i >= 0; i--) {
                if(buffer[i] == '\n') {
                    lastBreak = i+1;
                    break;
                } else {
                    i--;
                }
            }
            if(lastBreak == -1) {
                lastBreak = read;
            }
            offset = offset + read - lastBreak;
            int lineStart = 0;
            for(int i = 0; i < lastBreak; i++) {
                if(buffer[i] == '\n') {
                    int lineLength = i-lineStart;
                    //Don't include trailing '\r'
                    if(buffer[i-1] == 13) {
                        lineLength -= 1;
                    }
                    String line = new String(buffer,lineStart,lineLength, "UTF-8");
                    i++; //Skip '\n' char
                    lineStart = i;
                    if(line.equals("#")) {
                        misspelled = true;
                        continue;
                    }
                    if(!misspelled) {
                        dictionary.add(line);
                    } else {
                        misspelledWords[misspelledIndex] = line;
                        misspelledIndex++;
                    }
                }
            }
            //Write last remaining to beginning of buffer.
            for(int i = 0; i < offset; i++) {
                buffer[i] = buffer[lastBreak+i];
            }
        }
        if(offset > 0) {
            String lastLine = new String(buffer, 0, offset, "UTF-8");
            misspelledWords[misspelledIndex] = lastLine;
            misspelledIndex++;
        }
        return new Result(dictionary, misspelledWords);
    }
}

