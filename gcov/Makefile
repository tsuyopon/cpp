# 古いGCCの場合(新しい方は-fのオプションを-coverageに置き換える)
sample1:
	gcc -fprofile-arcs -ftest-coverage -o sample1 sample1.c 
	./sample1
	gcov sample1.gcda
	@echo "####### execute cat sample1.c.gcov command to check gcov"

# 新しいGCCの場合
sample1_new:
	gcc -coverage -o sample1new sample1.c 
	./sample1
	gcov sample1.gcda
	@echo "####### execute cat sample1.c.gcov command to check gcov"

clean:
	rm -f sample1 sample1new
	rm -f sample1.c.gcov  sample1.gcda  sample1.gcno
