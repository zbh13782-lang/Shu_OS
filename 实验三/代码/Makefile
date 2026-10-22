CC = gcc
CFLAGS = -Wall -Wextra
PROGRAMS = hello 01_identity_exec 02_fork_wait 03_process_tree 04_multi_exec \
           05_memory_copy 06_pipe 07_lifecycle 08_server 08_client 09_signal \
           10_producer_consumer

all: $(PROGRAMS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(PROGRAMS)
