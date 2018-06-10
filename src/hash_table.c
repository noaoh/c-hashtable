#include <stdlib.h>
#include <string.h>

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
