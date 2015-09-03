JFLAGS= -g
JC= javac
JVM = java
.SUFFIXES: .java .class
.java.class:
	$(JC) $(JFLAGS) $*.java

CLASSES = \
	Main.java \
	ClosestWords.java \
	Trie.java

default: classes

classes: $(CLASSES:.java=.class)

clean:
	-rm -rf *.class
