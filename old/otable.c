

// in the name of Allah

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "otable.h"

static FILE *fp = NULL;
static RecordItem records[MAX_NUM_RECORDS];

int findDataTypeByName(const char *dataTypeName)
{
    if (!strcmp(dataTypeName, "BIT"))
        return E_BIT;
    if (!strcmp(dataTypeName, "BOOLEAN"))
        return E_BOOLEAN;
    if (!strcmp(dataTypeName, "TINYINT"))
        return E_TINYINT;
    if (!strcmp(dataTypeName, "INT"))
        return E_INT;
    if (!strcmp(dataTypeName, "BIGINT"))
        return E_BIGINT;
    if (!strcmp(dataTypeName, "FLOAT"))
        return E_FLOAT;
	if (!strcmp(dataTypeName, "STRING"))
        return E_STRING;
    if (!strcmp(dataTypeName, "VARCHAR"))
        return E_STRING;
    if (!strcmp(dataTypeName, "DATETIME"))
        return E_DATETIME;
	
    return E_STRING;
}

char *strduplicate(char *src)
{
    char *out = (char *)calloc(strlen(src) + 1, sizeof(char));
    return out ? strcpy(out, src) : NULL;
}

char *strip(char *s)
{
    char *dummy = NULL, *r = NULL;
    if (!s || !*s) return NULL;

    if (*s != '"') return s;

    r = strrchr(s, '"');
    if (*(r + 1)) return s;

    dummy = strduplicate(s);
    dummy[strlen(dummy) - 1] = 0;

    strcpy(s, dummy + 1);
    free(dummy);

    return s;
}

static void make_header()
{
    char line[MAX_BUFF_SIZE];
    char label[MAX_BUFF_SIZE], dataTypeName[MAX_BUFF_SIZE], mutable_[MAX_BUFF_SIZE];
    int index = 1;
	
	HeaderItem *hp = headers;

    while (fgets(line, MAX_BUFF_SIZE - 1, fp)) {
        if ((hp - headers <= MAX_NUM_HEADERS)
               && sscanf(line, " <header label = \"%[_/a-zA-Z0-9]\" datatype = \"%[a-zA-Z0-9]\" mutable = \"%[a-zA-Z0-9]\" />",
                         label, dataTypeName, mutable_) >= 3) {

            hp->label = strduplicate(label);
            hp->index = index++;
            hp->dataType = findDataTypeByName(dataTypeName);
            hp->mutable_ = !strcmpi(mutable_, "True") ? 1 : 0;

            hp++;
        }
        else break;
    }

    hp->label = NULL;
}

static HeaderItem *findHeaderByLabel(const char *label)
{
	register HeaderItem *hp = headers;
	for (; hp; hp++) {
		if (!strcmp(hp->label, label))
			return hp;
	}
	return NULL;
}

static void insert_records()
{
    char val[MAX_BUFF_SIZE] = "";
    char colName[MAX_BUFF_SIZE], line[MAX_BUFF_SIZE];
    register RecordItem *rp = records;
    int row = 0;

    while(fgets(line, MAX_BUFF_SIZE - 1, fp)) {

        // a new record
        if (strstr(line, "<record>"))
            row++;

        // a new item
        else if ((rp - records <= MAX_NUM_RECORDS)
            && (sscanf(line, " <item col = \"%[._/a-zA-Z0-9]\" val = %[-, \".:$._a-zA-Z0-9] />", colName, val) >= 2)) {

            rp->val = *val ? strduplicate(strip(val)) : NULL;
            rp->hdrItem = findHeaderByLabel(colName);
            rp->row = row;

            //if (rp->hdrItem) printf("col = %s,\t\tval = %s\n", rp->hdrItem->label, rp->val);
            rp++;

            *val = *colName = *line = 0;
        }
        // record tag must be closed
        else if (!strstr(line, "</record>")) break;
    }

    if (!strstr(line, "</table>")) exit(-3);

    rp->val = NULL;
}

static int parse_root()
{
    char str[MAX_BUFF_SIZE];
    return (fgets(str, MAX_BUFF_SIZE - 1, fp) && !strcmp(str, "<table>\n")) || (exit(-1), 0);
}

void start()
{
    if (!(fp = fopen("C:\\Users\\RM-PC\\Documents\\def.xml", "r")))
        exit(-3);

    parse_root();
    make_header();
    insert_records();
    fclose(fp);
}

void run()
{
}

int main()
{
    start();
    run();
	return 0;
}
