.PHONY:all
all:shm_client shm_server
shm_client:shm_client.c
	gcc -o $@ $^
shm_server:shm_server.c
	gcc -o $@ $^

.PHONY:clean
clean:
	rm -f shm_client shm_server