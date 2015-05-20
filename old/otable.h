#ifndef OTABLE_H
#define OTABLE_H

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_BUFF_SIZE   100
#define MAX_NUM_RECORDS 1000
#define MAX_NUM_HEADERS 100

enum _DataTypes {
    E_BIT, E_BOOLEAN, E_TINYINT,
    E_INT, E_BIGINT, E_FLOAT,
    E_STRING, E_DATETIME
};

typedef struct {
    char *label;
    int index;
    int dataType;
    int mutable_;
} HeaderItem;

HeaderItem headers[MAX_NUM_HEADERS];

typedef struct {
    HeaderItem *hdrItem;
    int row;
    char *val;
} RecordItem;


char *strduplicate(char *);
char *strip(char *);

#ifdef __cplusplus
}
#endif

#endif // OTABLE_H
