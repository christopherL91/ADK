public class StringPair {
    protected String a;
    protected String b;
    protected int aCode;
    protected int bCode;
    public StringPair(String a, String b) {
        this.a = a;
        this.b = b;
        this.aCode = a.hashCode();
        this.bCode = b.hashCode();
    }
    @Override
    public int hashCode() {
        int code = aCode * 31 + bCode;
        return code;
    }
    @Override
    public boolean equals(Object other) {
        StringPair otherPair = (StringPair) other;
        return a.equals(otherPair.a) && b.equals(otherPair.b);
    }
}
