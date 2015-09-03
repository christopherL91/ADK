import java.util.ArrayList;
import java.util.TreeSet;
import java.util.List;
import java.util.Map;

public class CloserWords {
    private TreeSet<String> closestWords = null;
    private int closestDistance = Integer.MAX_VALUE;

    public CloserWords(String searchWord, Trie dictionary) {
        this.closestWords = new TreeSet<String>();
        this.search(searchWord, dictionary);
    }

    private void search(String searchWord, Trie dictionary) {
        int[] currentRow = new int[searchWord.length() + 1];
        for(int i = 0; i < currentRow.length; i++) {
            currentRow[i] = i;
        }

        for(int i = 0; i < 128; i++) {
            if(dictionary.children[i] != null) {
                this.searchRecursive(dictionary.children[i],(char) i,searchWord,currentRow);
            }
        }
    }

    private void searchRecursive(Trie node, char letter, String searchWord, int[] previousRow) {
        int[] currentRow = new int[searchWord.length() + 1];
        currentRow[0] = previousRow[0] + 1;
        for (int i = 1; i < currentRow.length; i++) {
            int insertCost = currentRow[i - 1] + 1;
            int deleteCost = previousRow[i] + 1;
            int replaceCost;
            if(searchWord.charAt(i-1) == letter) {
                replaceCost = previousRow[i - 1];
            } else {
                replaceCost = previousRow[i - 1] + 1;
            }
            currentRow[i] = Math.min(insertCost,Math.min(deleteCost,replaceCost));
        }

        int distance = currentRow[currentRow.length - 1];
        if(node.word != null && distance < this.closestDistance) {
            this.closestWords.clear();
            this.closestWords.add(node.word);
            this.closestDistance = distance;
        } else if(node.word != null && distance == this.closestDistance) {
            this.closestWords.add(node.word);
            this.closestDistance = distance;
        }

        for(int i = 0; i < 128; i++) {
            if(node.children[i] != null) {
                this.searchRecursive(node.children[i],(char) i,searchWord,currentRow);
            }
        }
    }

    public int getMinDistance() {
        return this.closestDistance;
    }

    public List<String> getClosestWords() {
        return new ArrayList<String>(this.closestWords);
    }
}
