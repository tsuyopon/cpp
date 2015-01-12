all: shmreciever shmwriter

shmreciever: shmreciever.c
	gcc $? -o $@

shmwriter: shmwriter.c
	gcc $? -o $@

clean:
	rm -f a.out shmreciever shmwriter
