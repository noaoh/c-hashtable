#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "hash_table.h"
#include "prime.h"
#include "xmemory.h"

static ht_item HT_DELETED_ITEM = {NULL, NULL};

static ht_item* ht_new_item(const char* k, const char* v) {
        ht_item* i = malloc(sizeof(ht_item));
        i->key = strdup(k);
        i->val = strdup(v);
        return i;
}

ht_hash_table* ht_new_sized(const int base_size) {
        ht_hash_table* ht = xmalloc(sizeof(ht_hash_table));
        ht->base_size = base_size;

        ht->size = next_prime(ht->base_size);

        ht->count = 0;
        ht->items = xcalloc((size_t)ht->size, sizeof(ht_item*));
        return ht;
}

ht_hash_table* ht_new(void) {
        return ht_new_sized(HT_INITIAL_BASE_SIZE);
}

static void ht_del_item(ht_item* i) {
        free(i->key);
        free(i->val);
        free(i);
}

void ht_del_hash_table(ht_hash_table* ht) {
        for (int i = 0; i < ht->count; i++) {
                ht_item* item = ht->items[i];
                if (item != NULL) {
                        ht_del_item(item);
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

void ht_insert(ht_hash_table* ht, const char* key, const char* val) {
        const int load = ht->count * 100 / ht->size;
        if (load > 70) {
                ht_resize_up(ht);
        }
        ht_item* item = ht_new_item(key, val);
        int index = ht_get_hash(item->key, ht->size, 0);
        ht_item* cur_item = ht->items[index];
        int i = 1;
        while (cur_item != NULL) {
                if (cur_item != &HT_DELETED_ITEM) {
                        if (strcmp(cur_item->key, key) == 0) {
                                ht_del_item(cur_item);
                                ht->items[index] = item;
                                return;
                        }
                }
                index = ht_get_hash(item->key, ht->size, i);
                cur_item = ht->items[index];
                i++;
        }
        ht->items[index] = item;
        ht->count++;
}

char* ht_search(ht_hash_table* ht, const char* key) {
        int index = ht_get_hash(key, ht->size, 0);
        ht_item* item = ht->items[index];
        int i = 1;
        while (item != NULL) {
                if (item != &HT_DELETED_ITEM) {
                        if (strcmp(item->key, key) == 0) {
                                return item->val;
                        }
                }
        index = ht_get_hash(key, ht->size, i);
        item = ht->items[index];
        i++;
        }
        return NULL;
}

void ht_delete(ht_hash_table* ht, const char* key) {
        const int load = ht->count * 100 / ht->size;
        if (load < 10) {
                ht_resize_down(ht);
        }
        int index = ht_get_hash(key, ht->size, 0);
        ht_item* item = ht->items[index];
        int i = 1;
        while (item != NULL) {
                if (item != &HT_DELETED_ITEM) {
                        if (strcmp(item->key, key) == 0) {
                                ht_del_item(item);
                                ht->items[index] = &HT_DELETED_ITEM;
                        }
                }
                index = ht_get_hash(key, ht->size, i);
                item = ht->items[index];
                i++;
        }
        ht->count--;
}

static void ht_resize(ht_hash_table* ht, const int base_size) {
        if (base_size < HT_INITIAL_BASE_SIZE) {
                return;
        }
        ht_hash_table* new_ht = ht_new_sized(base_size);
        for (int i = 0; i < ht->size; i++) {
                ht_item* item = ht->items[i];
                if (item != NULL && item != &HT_DELETED_ITEM) {
                        ht_insert(new_ht, item->key, item->val);
                }
        }

        ht->base_size = new_ht->base_size;
        ht->count = new_ht->count;

        // To delete new_ht, we give it ht's size & items
        const int tmp_size = ht->size;
        ht->size = new_ht->size;
        new_ht->size = tmp_size;

        ht_item** tmp_items = ht->items;
        ht->items = new_ht->items;
        new_ht->items = tmp_items;

        ht_del_hash_table(new_ht);
}

static void ht_resize_up(ht_hash_table* ht) {
        const int new_size = ht->base_size * 2;
        ht_resize(ht, new_size);
}

static void ht_resize_down(ht_hash_table* ht) {
        const int new_size = ht->base_size / 2;
        ht_resize(ht, new_size);
}
