#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "hash_table.h"

static ht_item* ht_new_item(const char* k, const char* v) {
        ht_item* i = malloc(sizeof(ht_item));
        i->key = strdup(k);
        i->val = strdup(v);
        return i;
}

ht_hash_table* ht_new(void) {
        ht_hash_table* ht = malloc(sizeof(ht_hash_table));

        ht->size = 100;
        ht->count = 0;
        ht->items = calloc((size_t)ht->size, sizeof(ht_item)); 
        return ht;
}

static void ht_delete_item(ht_item* i) {
        free(i->key);
        free(i->val);
        free(i);
}

void ht_del_hash_table(ht_hash_table* ht) {
        for (int i = 0; i < ht->count; i++) {
                ht_item* item = ht->items[i];
                if (item != NULL) {
                        ht_delete_item(item);
                }
        }
        free(ht->items);
        free(ht);
}

static int ht_hash(
                const char* val, const int prime_num, const int bucket_num
                ) {
        long hash = 0;
        const int string_len = strlen(val);
        for (int i = 0; i < string_len; i++) {
                hash += (long)pow(prime_num, (string_len - (i + 1))) * val[i]; 
                hash %= bucket_num;
        }
        return (int)hash;
}

static int ht_get_hash(
                const char* val, const int bucket_num, const int attempt
                ) {
        const int hash_a = ht_hash(val, HT_PRIME_1, bucket_num);
        const int hash_b = ht_hash(val, HT_PRIME_2, bucket_num);
        return (hash_a + (attempt * (hash_b + 1))) % bucket_num;
}
