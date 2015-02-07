all: clean nonexclusive exclusive

nonexclusive: nonexclusive.cc
	g++ $? -o $@

exclusive: exclusive.cc
	g++ $? -o $@

clean:
	rm -f a.out nonexclusive exclusive
