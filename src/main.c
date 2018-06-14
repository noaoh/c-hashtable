#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "prime.h"
#include "xmemory.h"

int main() {
        ht_hash_table* ht = ht_new();
        FILE *fp;
        char line[255];
        char *k;
        char *v;
        fp = fopen("nato-alphabet.csv", "r");
        while (fgets(line, 255, (FILE *)fp)) {
                k = strtok(line, ",");
                v = strtok(NULL, ",");
                ht_insert(ht, k, v); 
        }
        char* alphabet[4] = {"A", "B", "C", "1"};
        for (int x = 0; x < 4; x++) {
                char* result = ht_search(ht, alphabet[x]);
                if (result == NULL) {
                        printf("Ouch oof my NULL bones\n");
                } else {
                        printf("value found: %s", result);
                }
        }
        ht_del_hash_table(ht);
}
