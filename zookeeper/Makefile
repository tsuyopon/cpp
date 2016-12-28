all: clean zkcli zkhello sample1_st sample1_mt

zkcli:
	gcc zkcli.c -o zkcli -I /usr/local/include/zookeeper/ -lzookeeper_mt -g

zkhello:
	gcc zkhello.c -o zkhello -I /usr/local/include/zookeeper/ -lzookeeper_mt -g

# st: single thread
sample1_st:
	gcc sample1.c -o sample1_st -I /usr/local/include/zookeeper/ -lzookeeper_st -g

# mt: multi thread
sample1_mt:
	gcc sample1.c -o sample1_mt -I /usr/local/include/zookeeper/ -lzookeeper_mt -g


clean:
	rm -f zkcli zkhello sample1_st sample1_mt
