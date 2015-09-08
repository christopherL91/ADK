import java.util.Arrays;
import java.util.ArrayList;
import java.util.Collections;

public class MatrixWords {
    private static final int WORD_SIZE = 41;
    private static final int[][] matrix = new int[WORD_SIZE][WORD_SIZE];
    private static String previousWord;
    private static int previousWordLength = 0;
    private ArrayList<String> closestWords = null;
    private int closestDistance;

    public MatrixWords() {
        for (int i = 0; i < WORD_SIZE; i++) {
            matrix[i][0] = i;
        }
        for (int j = 0; j < WORD_SIZE; j++) {
            matrix[0][j] = j;
        }
    }

    public void search(ArrayList<String> dictionary, String searchWord) {
        final int searchLength = searchWord.length();
        this.closestDistance = WORD_SIZE;
        this.closestWords = new ArrayList<String>();
        previousWordLength = 0;
        previousWord = null;
        for(final String word: dictionary) {
            final int wordLength = word.length();
            int lenDiff = Math.abs(wordLength-searchLength);
            if(closestDistance == WORD_SIZE || lenDiff <= closestDistance+1) {
                int dist = distance(word, wordLength, searchWord, searchLength);
                if(dist < this.closestDistance) {
                    this.closestDistance = dist;
                    this.closestWords = new ArrayList<String>();
                    this.closestWords.add(word);
                }
                else if(dist == this.closestDistance) {
                    this.closestWords.add(word);
                }
            }
        }
    }

    private static final int distance(final String word,final int wordLength,final String searchWord,final int searchLength) {
        int minlen = Math.min(previousWordLength,wordLength);
        int start = 1;
        for(int i = 0; i < minlen && word.charAt(i) == previousWord.charAt(i); i++) {
            start++;
        }
        for (int j = start; j <= wordLength; j++) {
            for (int i = 1; i <= searchLength; i++) {
                int before = matrix[i-1][j-1];
                int deleteCost = matrix[i][j-1] + 1;
                int insertCost = matrix[i-1][j] + 1;
                int swap = (searchWord.charAt(i-1) == word.charAt(j-1)) ? 0 : 1;
                int swapCost = before + swap;
                matrix[i][j] = Math.min(deleteCost, Math.min(insertCost,swapCost));
            }
        }
        previousWord = word;
        previousWordLength = wordLength;
        return matrix[searchLength][wordLength];
    }

    public int getMinDistance() {
        return closestDistance;
    }

    public ArrayList<String> getClosestWords() {
        Collections.sort(closestWords);
        return closestWords;
    }
}
