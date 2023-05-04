#ifndef KINGKONGDB_H
#define KINGKONGDB_H

#include <stdint.h>

#ifndef __cplusplus
extern "C" {
#endif

struct Database;
struct DBHandle;
struct DBDocument;
struct DBDocumentIter;
struct DBArray;

typedef struct DBDocument DBDocument;

#define KKDB_TRANS_AUTO 0
#define KKDB_TRANS_READ 1
#define KKDB_TRANS_WRITE 2

#ifdef __cplusplus 
}
#endif

#endif 