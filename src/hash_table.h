typedef struct {
        char* key;
        char* val;
} ht_item;

typedef struct {
        int size;
        int count;
        ht_item** items;
} ht_hash_table;

static ht_item* ht_new_item(const char* k, const char* v);
ht_hash_table* ht_new(void);
static void ht_delete_item(ht_item* i);
void ht_del_hash_table(ht_hash_table* ht);
