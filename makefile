main: src/main.c src/search.c src/queue.c src/io.c src/trie.c
	- gcc -Wall -Wextra -Werror -std=c99 -g src/main.c src/search.c src/queue.c src/io.c src/trie.c -o main

testTrie: tests/testTrie.c src/trie.c
	- gcc -Wall -Wextra -Werror -std=c99 -g tests/testTrie.c src/trie.c -o testTrie

testQueue: tests/testQueue.c src/queue.c
	- gcc -Wall -Wextra -Werror -std=c99 -g tests/testQueue.c src/queue.c -o testQueue

testSearch: tests/testSearch.c src/search.c src/queue.c src/io.c src/trie.c
	- gcc -Wall -Wextra -Werror -std=c99 -g tests/testSearch.c src/search.c src/queue.c src/io.c src/trie.c -o testSearch
