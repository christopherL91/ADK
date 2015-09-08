import java.util.HashMap;
import java.util.ArrayList;
import java.util.TreeSet;
import java.util.Collections;
import java.util.SortedSet;
import java.util.Iterator;

public class MemoLevenshtein {
    private HashMap<StringPair,Integer> cache;
    private int minDistance = 40;
    private ArrayList<String> closestWords;

    public MemoLevenshtein() {
        this.cache = new HashMap<StringPair, Integer>(1000000,0.99f);
        this.closestWords = new ArrayList<String>();
    }

    private int storeInCache(StringPair pair, int distance) {
        this.cache.put(pair,distance);
        return distance;
    }

    private int calculateDistance(String a, int aStart, int aLen, String b, int bStart, int bLen) {
        StringPair pair = new StringPair(a.substring(aStart), b.substring(bStart));
        if(aLen == 0) {
            return storeInCache(pair,bLen);
        } else if(bLen == 0) {
            return storeInCache(pair,aLen);
        }
        if(a.charAt(aStart) == b.charAt(bStart)) {
            int dist = calculateDistance(a,aStart+1,aLen-1, b, bStart+1, bLen-1);
            return storeInCache(pair,dist);
        }
        Integer cached_distance = this.cache.get(pair);
        if(cached_distance != null) {
            return cached_distance;
        }
        int deleteDistance = calculateDistance(a,aStart+1,aLen-1,b, bStart, bLen);
        int insertDistance = calculateDistance(a,aStart,aLen, b,bStart+1,bLen-1);
        int editDistance = calculateDistance(a,aStart+1,aLen-1, b,bStart+1,bLen-1);
        int minDistance = Math.min(deleteDistance,Math.min(insertDistance, editDistance));
        return storeInCache(pair,minDistance+1);
    }

    public int distance(String a, String b) {
        int aEnd = a.length();
        int bEnd = b.length();
        StringPair pair = new StringPair(a, b);
        Integer cached_distance = this.cache.get(pair);
        if(cached_distance == null) {
            if(aEnd > bEnd) {
                return storeInCache(pair,calculateDistance(b,0,bEnd,a,0,aEnd));
            } else {
                return storeInCache(pair,calculateDistance(a,0,aEnd,b,0,bEnd));
            }
        } else {
            return cached_distance;
        }
    }

    public void search(String word, TreeSet<String> dictionary) {
        int minDistance = Integer.MAX_VALUE;
        Iterator<String> before = dictionary.headSet(word).iterator();
        int dist;
        do {
            String str = before.next();
            dist = distance(word,str);
            if(dist < minDistance) {
                this.closestWords.clear();
                this.closestWords.add(str);
                minDistance = dist;
            } else if(dist == minDistance) {
                this.closestWords.add(str);
            }
        } while(before.hasNext() && dist <= minDistance + 4);

        Iterator<String> after = dictionary.tailSet(word, false).iterator(); //Do not include this element
        do {
            String str = after.next();
            dist = distance(word,str);
            if(dist < minDistance) {
                this.closestWords.clear();
                this.closestWords.add(str);
                minDistance = dist;
            } else if(dist == minDistance) {
                this.closestWords.add(str);
            }
        } while(after.hasNext() && dist <= minDistance + 4);
        this.minDistance = minDistance;
    }

    public ArrayList<String> getClosestWords() {
        Collections.sort(this.closestWords);
        return this.closestWords;
    }

    public int getMinDistance() {
        return this.minDistance;
    }
}
