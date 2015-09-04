import java.util.HashMap;
import java.util.Map;
import java.util.Arrays;

public class Trie {
    Trie[] children;
    String word;

    public Trie() {
        this.children = new Trie[29];
    }

    public void insert(String word) {
        Trie node = this;
        for (int i = 0; i < word.length(); i++) {
            char letter = word.charAt(i);
            int index = -1;
            if(letter <= 'z') {
                index = letter - 'a';
            } else {
                if(letter == 'ö') {
                    index = 28;
                } else if (letter == 'ä') {
                    index = 27;
                } else if (letter == 'å') {
                    index = 26;
                }
            }
            if(node.children[index] == null) {
                node.children[index] = new Trie();
            }
            node = node.children[index];
        }
        node.word = word;
    }

    // private void createString(StringBuilder result, boolean first, StringBuilder indentation) {
    //     result.append(indentation.toString());
    //     result.append("| ");
    //     first = true;
    //     // indentation.append("  ");
    //     for (Map.Entry<Character, Trie> entry : this.children.entrySet()) {
    //         result.append(indentation.toString());
    //         result.append("\n");
    //         result.append(indentation.toString());
    //         result.append("+- "+entry.getKey() + "\n");
    //         Trie node = entry.getValue();
    //         StringBuilder nextIndent = new StringBuilder();
    //         nextIndent.append(indentation.toString());
    //         if(this.children.size() > 1) {
    //             nextIndent.append("|  ");
    //         } else {
    //             nextIndent.append("   ");
    //         }
    //         node.createString(result, first, nextIndent);
    //         first = false;
    //     }
    // }
    // public String toString() {
    //     StringBuilder result = new StringBuilder();
    //     StringBuilder indentation = new StringBuilder();
    //     result.append("()\n");
    //     this.createString(result, true, indentation);
    //     return result.toString();
    // }
    public static void main(String[] args) {
        Trie trie = new Trie();
        trie.insert("godis");
        trie.insert("gott");
        trie.insert("adam");
        System.out.println(trie);
    }
}
