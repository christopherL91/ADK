import java.util.HashMap;
import java.util.Map;
import java.util.Arrays;

public class Trie {
    Trie[] children;
    String word;

    public Trie() {
        this.word = null;
        this.children = new Trie[256];
    }

    public void insert(String word) {
        Trie node = this;
        for (int i = 0; i < word.length(); i++) {
            char letter = word.charAt(i);
            if(node.children[letter] == null) {
                Trie nextNode = new Trie();
                node.children[letter] = nextNode;
                node = nextNode;
            } else {
                node = node.children[letter];
            }
        }
        node.word = word;
    }
}
