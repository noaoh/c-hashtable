#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "prime.h"
#include "xmemory.h"
#include "csv.h"

int main() {

        ht_hash_table* ht = read_csv_file("nato-alphabet.csv", ",");

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
