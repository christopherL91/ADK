import java.util.HashMap;
import java.util.Map;
import java.util.Arrays;

public class Trie {
    private Map<Character, Trie> children;
    private String word;

    public Trie() {
        this.word = null;
        this.children = new HashMap<Character, Trie>();
    }

    public void insert(String word) {
        Trie node = this;
        for (int i = 0; i < word.length(); i++) {
            char letter = word.charAt(i);
            if(!node.children.containsKey(letter)) {
                Trie nextNode = new Trie();
                node.children.put(letter,nextNode);
                node = nextNode;
            } else {
                node = node.children.get(letter);
            }
        }
    }
    private void createString(StringBuilder result, boolean first, StringBuilder indentation) {
        result.append(indentation.toString());
        result.append("| ");
        first = true;
        // indentation.append("  ");
        for (Map.Entry<Character, Trie> entry : this.children.entrySet()) {
            result.append(indentation.toString());
            result.append("\n");
            result.append(indentation.toString());
            result.append("+- "+entry.getKey() + "\n");
            Trie node = entry.getValue();
            StringBuilder nextIndent = new StringBuilder();
            nextIndent.append(indentation.toString());
            if(this.children.size() > 1) {
                nextIndent.append("|  ");
            } else {
                nextIndent.append("   ");
            }
            node.createString(result, first, nextIndent);
            first = false;
        }
    }
    public String toString() {
        StringBuilder result = new StringBuilder();
        StringBuilder indentation = new StringBuilder();
        result.append("()\n");
        this.createString(result, true, indentation);
        return result.toString();
    }
    public static void main(String[] args) {
        Trie trie = new Trie();
        trie.insert("godis");
        trie.insert("gott");
        trie.insert("adam");
        System.out.println(trie);
    }
}
