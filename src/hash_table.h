#define HT_INITIAL_BASE_SIZE 50
#define HT_PRIME_1 53
#define HT_PRIME_2 57

typedef struct {
        char* key;
        char* val;
} ht_item;

typedef struct {
        int size;
        int count;
        int base_size;
        ht_item** items;
} ht_hash_table;

static ht_item* ht_new_item(const char* k, const char* v);
static ht_hash_table* ht_new_sized(const int base_size);
ht_hash_table* ht_new(void);
static void ht_del_item(ht_item* i);
void ht_del_hash_table(ht_hash_table* ht);
static int ht_hash(
                const char* val, const int prime_num, const int bucket_num
                );
static int ht_get_hash(
                const char* val, const int bucket_num, const int attempt
                );
void ht_insert(ht_hash_table* ht, const char* key, const char* val);
char* ht_search(ht_hash_table* ht, const char* key);
void ht_delete(ht_hash_table* h, const char* key);
static void ht_resize(ht_hash_table* ht, const int base_size);
static void ht_resize_up(ht_hash_table* ht);
static void ht_resize_down(ht_hash_table* ht);
