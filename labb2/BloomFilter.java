import java.util.BitSet;
public class BloomFilter {
    BitSet bits;
    long numberOfBitsDivBy2;
    public BloomFilter() {
        int numBits = 1000000;
        bits = new BitSet(numBits);
        int hash = MurmurHash.hash32("testing");
        bits.set(Math.abs(hash)%numBits, true);
        hash = MurmurHash.hash32("katt");
        bits.set(Math.abs(hash)%numBits, true);
        System.out.println(bits);
    }

    public static void main(String[] args) {
        new BloomFilter();
    }

    private long getIndex(int hash) {
        return (hash % numberOfBitsDivBy2) + numberOfBitsDivBy2;
    }
}
