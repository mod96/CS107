#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "cachelab.h"

#define uc unsigned char
#define lld unsigned long long
#define MAX 2100000000
#define MIN_CUT 100000

typedef struct{
		size_t tag;
		size_t valid;
} cblock;

typedef struct{
		char hit;
		char miss;
		char eviction;
} flag;


int char2hex(char ch) {
		if ('0' <= ch && ch <= '9') {
				return ch - '0';
		}
		return 10 + (ch - 'a');
}

void int2bin(lld a, char* buffer, int buf_size) {
		buffer += (buf_size - 1);
		for (int i = 64; i >= 0; i--){
				*buffer-- = (a & 1) + '0';
				a >>= 1;
		}
}

size_t binary2sizet(char* str, int st, int ed) {
		size_t res = 0;
		size_t j = 0;
		for (int i = ed - 1; i >= st; i--){
				res += (size_t)(str[i] - '0') * (1 << j++);
		}
		return res;
}

lld parse_line(const char* str, size_t line_len, size_t* size) {
		char address[17];
		int i = 3,
				j = 0, 
				k = 0;
		char buffer[20];
		for (i = 3; i < line_len && j < 16; i++){
				if (str[i] == ',') {
						i++;
						for (; i<line_len && k < 19; i++){
								buffer[k++] = str[i];
						}
						buffer[k] = 0;
						*size = atoi(buffer);
						break;
				} else {
						address[j++] = str[i];
				}
		}
		address[j] = 0;

		// printf("0. parsed address: %s\n", address);
		// printf("0_1. j: %d\n", j);
		i = 0;
		lld res = 0;
		for (k = j - 1; k >= 0; k--) {
				res += (((lld)char2hex(address[k])) << i);
				i += 4;
				// printf("%llu\n", res);
		}	
		return res;
}

void parse_address(const lld address, size_t s, size_t b,
								   size_t* tag,
								   size_t* set,
								   size_t* b_offset) {
		char address_buf[65] = {'0'};
		address_buf[64] = 0;
    int2bin(address, address_buf, 64);
		// printf("2. %s\n", address_buf);

		*tag = binary2sizet(address_buf, 0, 64 - s - b);
		*set = binary2sizet(address_buf, 64 - s - b, 64 - b);
		*b_offset = binary2sizet(address_buf, 64 - b, 64);
}

void simulate(cblock** cache, lld addr, size_t s, size_t b, 
								flag* f, 
								size_t s_size, 
								size_t e_size, 
								size_t b_size,
								size_t size){
		size_t tag, set, b_offset;
		size_t i;
		size_t max_i, max_valid = 0, min_valid = MAX;
		char go_more = 1;
		// flag init
		*f = (flag) { .hit = 0, .miss = 0, .eviction = 0 };
		do {
			parse_address(addr, s, b, &tag, &set, &b_offset);
			// printf("3. addr: %llu, tag: %zu, set: %zu, b_offset: %zu, size: %zu\n", addr, tag, set, b_offset, size);

			// check for hit
			f->hit = 0;
			for (i = 0; i < e_size; i++){
				if (cache[set][i].valid) {
						cache[set][i].valid++;
						if (f->hit == 0 && cache[set][i].tag == tag) {
								f->hit = 1;
								cache[set][i].valid = 1;
						}
						if (cache[set][i].valid > max_valid){
								max_i = i;
								max_valid = cache[set][i].valid;
						}
						if (cache[set][i].valid < min_valid){
								min_valid = cache[set][i].valid;
						}
				}
			}	
			if (f->hit) {
					continue;
			}
			f->miss = 1;
			// refresh cache
			min_valid--;
			if (max_valid > MAX && min_valid > MIN_CUT) {
					for (i = 0; i < e_size; i++){
							if (cache[set][i].valid) cache[set][i].valid -= min_valid;
					}
			}
			// cache miss, so choose whether to evict or not
			max_valid = 0;
			for (i = 0; i < e_size; i++){
					if (cache[set][i].valid) {
							if (cache[set][i].valid > max_valid){
								max_i = i;
								max_valid = cache[set][i].valid;
						}
					} else {
							cache[set][i] = (cblock){ .tag = tag, .valid = 1 };
							go_more = 0;
							break;
					}
			}
			if (go_more == 0) continue;

			// do eviction
			f->eviction = 1;
			cache[set][max_i] = (cblock){ .tag = tag, .valid = 1 };

			if (size >= b_size - b_offset) size -= (b_size - b_offset);
			else size = 0;
			b_offset = 0;
			addr += b_size - b_offset;
			// printf("%zu %zu %zu", b_offset, size, b_size);
		} while (b_offset + size > b_size);
}



int main(int argc, char* argv[])
{
		FILE* fp;
		char* line = NULL;
		
		size_t line_len = 0, size;
		ssize_t read;

		size_t i = 1;
		uc s = 0, E = 0, b = 0;

		char verbose = 0;

		int hits = 0,
				misses = 0,
				evictions = 0;
		while (i < argc) {
				if((int)argv[i][0] == '-'){
						if (argv[i][1] == 's') {
								s = atoi(argv[i+1]);
						} else if (argv[i][1] == 'E') {
								E = atoi(argv[i+1]);
						} else if (argv[i][1] == 'b') {
								b = atoi(argv[i+1]);
						} else if (argv[i][1] == 't') {	
								fp = fopen(argv[i+1], "r");
								if (fp == NULL)
										exit(EXIT_FAILURE);
						} else if (argv[i][1] == 'v') {
								verbose = 1;
						}
						else {
								printf("Invalid argument passed.");
						}
				}
				i += 1;
		}
		assert(0 < s);
		assert(0 < E);
		assert(0 < b);
		assert(s + b < 8 * sizeof(size_t));

		size_t s_size = 1 << s,
			     e_size = E,
			     b_size = 1 << b;	
		cblock** cache = (cblock**)malloc(s_size * sizeof(cblock*));
		for (i = 0; i < s_size; i++){
				cache[i] = (cblock*)malloc(e_size * sizeof(cblock));
				// initialization
				for (size_t j = 0; j < e_size; j++){
						cache[i][j].valid = 0;
				}
		}
		
		lld addr;
		flag f;
		flag f_sub;
		char *printer1, *printer2;
		while ((read = getline(&line, &line_len, fp)) != -1) {
				if (line[0] == 'I') continue;
        addr = parse_line(line, line_len, &size);
				// printf("1. parse_line gives addr: %llu\n", addr);

				// remove ending \n
				line_len = strlen(line);
				if (line_len && (line[line_len - 1] == '\n')) line[--line_len] = 0;

				switch( line[1] ) {
						case 'L':
						case 'S':
								simulate(cache, addr, s, b, &f, s_size, e_size, b_size, size);
								if (f.miss) {
										misses++;
										if (f.eviction) {
											evictions++;
											printer1 = "miss eviction";
											} else {
											printer1 = "miss";										
											}
								} else {
									hits++;
									printer1 = "hit";
								}	
								if (verbose) printf("%s %s\n", line, printer1);
								break;
						case 'M':
								simulate(cache, addr, s, b, &f, s_size, e_size, b_size, size); // load
								simulate(cache, addr, s, b, &f_sub, s_size, e_size, b_size, size); // save
								if (f.miss) {
										misses++;
										if (f.eviction) {
											evictions++;
											printer1 = "miss eviction";
											} else {
											printer1 = "miss";										
											}
								} else {
									hits++;
									printer1 = "hit";
								}	

								if (f_sub.miss) {
										misses++;
										if (f_sub.eviction) {
											evictions++;
											printer2 = "miss eviction";
											} else {
											printer2 = "miss";										
											}
								} else {
									hits++;
									printer2 = "hit";
								}	

								if (verbose) printf("%s %s %s\n", line, printer1, printer2);
								break;
				}	
				// printf("Retrieved line of length %zu: %s", read, line);
		}	

    printSummary(hits, misses, evictions);

		for (i=0; i<s; i++){
				free(cache[i]);
		}

		fclose(fp);
		if (line){
				free(line);
		}
		exit(EXIT_SUCCESS);
		
    return 0;
}
