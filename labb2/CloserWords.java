import java.util.ArrayList;
import java.util.TreeSet;
import java.util.List;
import java.util.Map;
import java.util.Collections;

public class CloserWords {
    private ArrayList<char[]> closestWords = null;
    private int closestDistance;

    public CloserWords(char[] searchWord, Trie dictionary) {
        this.closestWords = new ArrayList<char[]>();
        int wordLength = searchWord.length;
        this.closestDistance = 40;
        this.search(searchWord, wordLength, dictionary);
    }

    private void search(char[] searchWord, int wordLength, Trie dictionary) {
        int[] currentRow = new int[wordLength + 1];
        for(int i = 0; i < currentRow.length; i++) {
            currentRow[i] = i;
        }
        Trie[] children = dictionary.children;
        for(int i = 0; i < 29; i++) {
            Trie child = children[i];
            if(child != null) {
                char letter = ' ';
                if(i < 26) {
                    letter = (char) (i + 'a');
                } else if (i == 26) {
                    letter = 'å';
                } else if(i == 27) {
                    letter = 'ä';
                } else if (i == 28) {
                    letter = 'ö';
                }
                this.searchRecursive(child,letter,searchWord,wordLength,currentRow);
            }
        }
    }

    private void searchRecursive(Trie node, char letter, char[] searchWord, int wordLength, int[] previousRow) {
        int[] currentRow = new int[wordLength + 1];
        currentRow[0] = previousRow[0] + 1;
        for (int i = 1; i < currentRow.length; i++) {
            int insertCost = currentRow[i - 1] + 1;
            int deleteCost = previousRow[i] + 1;
            int replaceCost;
            if(searchWord[i-1] == letter) {
                replaceCost = previousRow[i - 1];
            } else {
                replaceCost = previousRow[i - 1] + 1;
            }
            currentRow[i] = Math.min(insertCost,Math.min(deleteCost,replaceCost));
        }

        int distance = currentRow[currentRow.length - 1];
        char[] word = node.word;
        if(word != null && distance < this.closestDistance) {
            this.closestWords.clear();
            this.closestWords.add(word);
            this.closestDistance = distance;
        } else if(word != null && distance == this.closestDistance) {
            this.closestWords.add(word);
            this.closestDistance = distance;
        }
        int minCost = currentRow[0];
        for(int i = 1; i < currentRow.length; i++) {
            minCost = Math.min(minCost, currentRow[i]);
        }
        if(minCost <= this.closestDistance) {
            Trie[] children = node.children;
            for(int i = 0; i < 29; i++) {
                Trie child = children[i];
                if(child != null) {
                    char c = ' ';
                    if(i < 26) {
                        c = (char) (i + 'a');
                    } else if (i == 26) {
                        c = 'å';
                    } else if(i == 27) {
                        c = 'ä';
                    } else if (i == 28) {
                        c = 'ö';
                    }
                    this.searchRecursive(child,c,searchWord,wordLength,currentRow);
                }
            }
        }
    }

    public int getMinDistance() {
        return this.closestDistance;
    }

    public ArrayList<String> getClosestWords() {
        ArrayList<String> words = new ArrayList<String>(this.closestWords.size());
        for(char[] chars: this.closestWords) {
            words.add(new String(chars));
        }
        Collections.sort(words);
        return words;
    }
}
