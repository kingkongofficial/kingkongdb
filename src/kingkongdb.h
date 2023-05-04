#ifndef KINGKONGDB_H
#define KINGKONGDB_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief structs
 * 
 */
struct Database;
struct DBHandle;
struct DBDocument;
struct DBDocumentIter;
struct DBArray;
struct DBObjectId;

/**
 * @brief typedef structs
 * 
 */
typedef struct DBDocument DBDocument;
typedef struct DBDocumentIter DBDocumentIter;
typedef struct DBArray DBArray;
typedef struct Database Database;
typedef struct DBHandle DBHandle;
typedef struct DBObjectId DBObjectId;

#define KKDB_TRANS_AUTO 0
#define KKDB_TRANS_READ 1
#define KKDB_TRANS_WRITE 2

#define KKDB_ERR_NOT_A_VALID_DB -46

/**
 * @brief KKDB[VALUE TYPE]
 * 
 */
typedef enum KKDB_VALUE_TYPE {
  KKDB_VAL_NULL = 0x0A,
  KKDB_VAL_DOUBL = 0x01,
  KKDB_VAL_BOOLEAN = 0x08,
  KKDB_VAL_INT = 0x16,
  KKDB_VAL_STRING = 0x02,
  KKDB_VAL_OBJECT_ID = 0x07,
  KKDB_VAL_ARRAY = 0x17,
  KKDB_VAL_DOCUMENT = 0x13,
  KKDB_VAL_BINARY = 0x05,
  KKDB_VAL_UTC_DATETIME = 0x09,
} KKDB_VALUE_TYPE;

/**
 * @brief KKDBValue
 * 
 */
typedef struct KKDBValue {
    KKDB_VALUE_TYPE tag: 8;
    /**
     * @brief values
     * 
     */
    union {
        int64_t     int_value;
        double      double_value;
        int         bool_value;
        const char* str;
        DBObjectId* oid;
        DBArray*    arr;
        DBDocument* doc;
        uint64_t    utc;
    } v;
} KKDBValue;

/**
 * @brief KKDB[NULL, INT, DOUBLE, BOOL]
 * 
 */
#define KKDB_NULL { KKDB_VAL_NULL, { .int_value = 0 } }
#define KKDB_INT(x) { KKDB_VAL_INT, { .int_value = (x) } }
#define KKDB_DOUBLE(x) { KKDB_VAL_DOUBL, { .double_value = (x) } }
#define KKDB_BOOL(x) { KKDB_VAL_BOOLEAN, { .bool_value = !!(x) ? 1 : 0 } }

/**
 * @brief KKDB[ERR TYPE]
 * 
 */
enum KKDB_ERR_TYPE {
  KKDB_ERR_COLLECTION_NOT_FOUND = -24,
};

/**
 * @brief KKDB[open]
 * 
 * @param path 
 * @return Database* 
 */
Database* KKDB_open(const char* path);

/**
 * @brief KKDB[error code]
 * 
 * @return int 
 */
int KKDB_error_code();

/**
 * @brief KKDB[start transaction]
 * 
 * @param db 
 * @param flags 
 * @return int 
 */
int KKDB_start_transaction(Database*db, int flags);

/**
 * @brief KKDB[commit]
 * 
 * @param db 
 * @return int 
 */
int KKDB_commit(Database* db);

/**
 * @brief KKDB[rollback]
 * 
 * @param db 
 * @return int 
 */
int KKDB_rollback(Database* db);

/**
 * @brief KKDB[create collection]
 * 
 * @param db 
 * @param name 
 * @param col_id 
 * @param meta_verison 
 * @return int 
 */
int KKDB_create_collection(Database* db, const char* name, uint32_t* col_id, uint32_t* meta_verison);

/**
 * @brief KKDB[get collection meta by name]
 * 
 * @param db 
 * @param name 
 * @param id 
 * @param version 
 * @return int 
 */
int KKDB_get_collection_meta_by_name(Database* db, const char* name, uint32_t* id, uint32_t* version);

/**
 * @brief KKDB[count]
 * 
 * @param db 
 * @param col_id 
 * @param meta_version 
 * @return int64_t 
 */
int64_t KKDB_count(Database* db, uint32_t col_id, uint32_t meta_version);

/**
 * @brief KKDB[insert]
 * 
 * @param db 
 * @param col_id 
 * @param meta_version 
 * @param doc 
 * @return int 
 */
int KKDB_insert(Database* db, uint32_t col_id, uint32_t meta_version, DBDocument* doc);

/**
 * @brief KKDB[find]
 * 
 * @param db 
 * @param col_id 
 * @param meta_version 
 * @param query 
 * @param out_handle 
 * @return int 
 */
int KKDB_find(Database* db, uint32_t col_id, uint32_t meta_version, const DBDocument* query, DBHandle** out_handle);

/**
 * @brief KKDB[update]
 * 
 * @param db 
 * @param col_id 
 * @param meta_version 
 * @param query 
 * @param update 
 * @return int64_t 
 */
int64_t KKDB_update(Database* db, uint32_t col_id, uint32_t meta_version, const DBDocument* query, const DBDocument* update);

/**
 * @brief KKDB[delete]
 * 
 * @param db 
 * @param col_id 
 * @param meta_version 
 * @param query 
 * @return int64_t 
 */
int64_t KKDB_delete(Database* db, uint32_t col_id, uint32_t meta_version, const DBDocument* query);

/**
 * @brief KKDB[delete all]
 * 
 * @param db 
 * @param col_id 
 * @param meta_version 
 * @return int64_t 
 */
int64_t KKDB_delete_all(Database* db, uint32_t col_id, uint32_t meta_version);

/**
 * @brief KKDB[drop]
 * 
 * @param db 
 * @param col_id 
 * @param meta_version 
 * @return int 
 */
int KKDB_drop(Database* db, uint32_t col_id, uint32_t meta_version);

/**
 * @brief KKDB[error msg]
 * 
 * @return const char* 
 */
const char* KKDB_error_msg();

/**
 * @brief KKDB[version]
 * 
 * @param buffer 
 * @param buffer_size 
 * @return int 
 */
int KKDB_version(char* buffer, unsigned int buffer_size);

/**
 * @brief KKDB[close]
 * 
 * @param db 
 */
void KKDB_close(Database* db);

/**
 * @brief KKDB[step]
 * 
 * @param handle 
 * @return int 
 */
int KKDB_step(DBHandle* handle);

/**
 * @brief KKDB[handle state]
 * 
 * @param handle 
 * @return int 
 */
int KKDB_handle_state(DBHandle* handle);

/**
 * @brief KKDB[handle get]
 * 
 * @param handle 
 * @param out_val 
 */
void KKDB_handle_get(DBHandle* handle, KKDBValue* out_val);

/**
 * @brief KKDB[handle to str]
 * 
 * @param handle 
 * @param buffer 
 * @param buffer_size 
 * @return int 
 */
int KKDB_handle_to_str(DBHandle* handle, char* buffer, unsigned int buffer_size);

/**
 * @brief KKDB[close and free handle]
 * 
 * @param handle 
 */
void KKDB_close_and_free_handle(DBHandle* handle);

/**
 * @brief KKDB[free handle]
 * 
 * @param handle 
 */
void KKDB_free_handle(DBHandle* handle);

/**
 * @brief KKDB[mk arr]
 * 
 * @return DBArray* 
 */
DBArray* KKDB_mk_arr();

/**
 * @brief KKDB[mk arr with size]
 * 
 * @param size 
 * @return DBArray* 
 */
DBArray* KKDB_mk_arr_with_size(unsigned int size);

/**
 * @brief KKDB[free ar]
 * 
 * @param arr 
 */
void KKDB_free_arr(DBArray* arr);

/**
 * @brief KKDB[arr len]
 * 
 * @param arr 
 * @return unsigned int 
 */
unsigned int KKDB_arr_len(DBArray* arr);

/**
 * @brief KKDB[arr push]
 * 
 * @param arr 
 * @param value 
 */
void KKDB_arr_push(DBArray* arr, KKDBValue value);

/**
 * @brief KKDB[arr set]
 * 
 * @param doc 
 * @param index 
 * @param val 
 * @return int 
 */
int KKDB_arr_set(DBArray* doc, uint32_t index, KKDBValue val);

/**
 * @brief KKDB[array get]
 * 
 * @param arr 
 * @param index 
 * @param out_val 
 * @return int 
 */
int KKDB_arr_get(DBArray* arr, unsigned int index, KKDBValue* out_val);

/**
 * @brief KKDB[mk_doc]
 * 
 * @return DBDocument* 
 */
DBDocument* KKDB_mk_doc();

/**
 * @brief KKDB[free doc]
 * 
 * @param doc 
 */
void KKDB_free_doc(DBDocument* doc);

/**
 * @brief KKDB[doc set]
 * 
 * @param doc 
 * @param key 
 * @param val 
 * @return int 
 */
int KKDB_doc_set(DBDocument* doc, const char* key, KKDBValue val);

/**
 * @brief KKDB[doc_get]
 * 
 * @param doc 
 * @param key 
 * @param out_val 
 * @return int 
 */
int KKDB_doc_get(DBDocument* doc, const char* key, KKDBValue* out_val);

/**
 * @brief KKDB[doc len]
 * 
 * @param doc 
 * @return int 
 */
int KKDB_doc_len(DBDocument* doc);

/**
 * @brief KKDB[doc iter]
 * 
 * @param doc 
 * @return DBDocumentIter* 
 */
DBDocumentIter* KKDB_doc_iter(DBDocument* doc);

/**
 * @brief KKDB[doc iter next]
 * 
 * @param iter 
 * @param key_buffer 
 * @param key_buffer_size 
 * @param out_val 
 * @return int 
 */
int KKDB_doc_iter_next(DBDocumentIter* iter,
  char* key_buffer, unsigned int key_buffer_size, KKDBValue* out_val);

/**
 * @brief KKDB[free doc iter]
 * 
 * @param iter 
 */
void KKDB_free_doc_iter(DBDocumentIter* iter);


/**
 * @brief KKDB mk binary value
 * 
 * @param bytes 
 * @param size 
 * @return KKDBValue 
 */
KKDBValue KKDB_mk_binary_value(const char* bytes, uint32_t size);

/**
 * @brief KKDB dup value
 * 
 * @param val 
 * @return KKDBValue 
 */
KKDBValue KKDB_dup_value(KKDBValue val);

/**
 * @brief KKDB free value
 * 
 * @param val 
 */
void KKDB_free_value(KKDBValue val);

/**
 * @brief KKDB mk object id
 * 
 * @param db 
 * @return DBObjectId* 
 */
DBObjectId* KKDB_mk_object_id(Database* db);

/**
 * @brief KKDB dup object_id
 * 
 * @param that 
 * @return DBObjectId* 
 */
DBObjectId* KKDB_dup_object_id(const DBObjectId* that);

/**
 * @brief KKDB[mk_object_id_from_bytes]
 * 
 * @param bytes 
 * @return DBObjectId* 
 */
DBObjectId* KKDB_mk_object_id_from_bytes(const char* bytes);

/**
 * @brief KKDB[object_id_to_bytes]
 * 
 * @param oid 
 * @param bytes 
 */
void KKDB_object_id_to_bytes(const DBObjectId* oid, char* bytes);

/**
 * @brief KKDB[free object id]
 * 
 */
void KKDB_free_object_id(DBObjectId*);

/**
 * @brief KKDB[object id to hex]
 * 
 * @param oid 
 * @param buffer 
 * @param size 
 * @return int 
 */
int KKDB_object_id_to_hex(const DBObjectId* oid, char* buffer, unsigned int size);

/**
 * @brief KKDB[mk utcdatetime]
 * 
 * @return uint64_t 
 */
uint64_t  KKDB_mk_UTCDateTime();


#ifdef __cplusplus
}
#endif

#endif