#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "csv.h"

ht_hash_table *read_csv_file(char *filepath, char *delim) {
    ht_hash_table *ht = ht_new();
    FILE *fp;
    char line[255];
    char* k;
    char* v;
    fp = fopen(filepath, "r");
    while (fgets(line, 255, (FILE *)fp)) {
        k = strtok(line, delim);
        v = strtok(NULL, delim);
        ht_insert(ht, k, v);
    }
    fclose(fp);
    return ht;
}