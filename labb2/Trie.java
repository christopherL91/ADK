import java.util.HashMap;
import java.util.Map;
import java.util.Arrays;

public class Trie {
    HashMap<Character, Trie> children;
    String word;

    public Trie() {
        this.word = null;
        this.children = new HashMap<>();
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
        node.word = word;
    }
}
