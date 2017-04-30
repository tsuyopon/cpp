all: sample1 sample2 sample3 sample4

sample1:
	g++ -o sample1 sample1.cc -std=c++11

sample2:
	g++ -o sample2 sample2.cc -std=c++11

sample3:
	g++ -o sample3_1 sample3_1.cc -std=c++11
	g++ -o sample3_2 sample3_2.cc -std=c++11

sample4:
	g++ -o sample4_nomove  sample4.cc
	g++ -o sample4_usemove sample4.cc -std=c++11

clean:
	rm -f a.out ./sample1 sample2 sample3_1 sample3_2 sample4_nomove sample4_usemove
