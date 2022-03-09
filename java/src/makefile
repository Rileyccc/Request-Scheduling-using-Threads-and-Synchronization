JFLAGS = -g
JC = javac
JVM = java

FILE =
.SUFFIXES: .java .class
.java.class:
		$(JC) $(JFLAGS) $*.java


CLASSES = \
		pac/Request.java \
    	pac/BoundedBuffer.java \
    	pac/Main.java \

MAIN = pac/Main

exec: classes
	$(JVM) $(MAIN) $(FILE)

default: classes

classes: $(CLASSES:.java=.class)

clean:
		$(RM) pac/*.class