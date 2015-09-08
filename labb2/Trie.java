import java.util.HashMap;
import java.util.Map;
import java.util.Arrays;
import java.util.BitSet;

public class Trie {
    private int size;
    private int nodeSize;
    private int[] base;
    private short[] check;
    private int[] tail;
    private int last;
    private BitSet term;
    private CharSequence tails;

    char[] word;
    Trie[] children;
    int numchilds = 0;

    public Trie() {
        this.children = new Trie[29];
    }

    public void insert(char[] word) {
        Trie node = this;
        int depth = 0;
        for (int i = 0; i < word.length; i++) {
            char letter = word[i];
            int index = letter - 'a';
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
            // depth++;
            // if(depth > 4) {
            //     node = this;
            //     depth = 0;
            // }
            if(node.children[index] == null) {
                node.children[index] = new Trie();
            }
            node = node.children[index];
        }
        node.word = word;
    }
}
