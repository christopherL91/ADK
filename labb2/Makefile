JFLAGS=
JC= javac
JVM = java -Xmx1024m
.SUFFIXES: .java .class
.java.class:
	$(JC) $(JFLAGS) $*.java

CLASSES = \
	Main.java \
	MatrixWords.java

default: classes

classes: $(CLASSES:.java=.class)

clean:
	-rm -rf *.class
