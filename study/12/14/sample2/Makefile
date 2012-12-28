.PHONY: sample sample-dbg all clean

PROGRAM = sample
DOBJS = Debug/sample-dbg.o
ROBJS = Release/sample.o

all: sample

$(PROGRAM)-dbg: Debug $(DOBJS)
	g++ -o $@ $(DOBJS)

$(PROGRAM): Release $(ROBJS)
	g++ -o $@ $(ROBJS)

Debug/%.o: $(PROGRAM).cc
	g++ -o $@ -c $<

Release/%.o: $(PROGRAM).cc
	g++ -o $@ -c -DNDEBUG $<

Debug:
	mkdir Debug

Release:
	mkdir Release

clean:
	rm -f $(PROGRAM) $(PROGRAM)-dbg
	rm -r Debug Release
