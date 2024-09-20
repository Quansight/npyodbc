#ifndef _NPCONTAINER_H_
#define _NPCONTAINER_H_

#include <cstring>
#include <vector>
#include <Python.h>
#include <sqltypes.h>
#include <string.h>

#define STR_LEN 128 + 1
#define REM_LEN 254 + 1

PyObject *Cursor_fetchdictarray(PyObject *self, PyObject *args, PyObject *kwargs);

extern char fetchdictarray_doc[];

extern Py_ssize_t iopro_text_limit;

class ColumnMetadata {
public:
    ColumnMetadata(
        SQLHSTMT hstmt,
        SQLCHAR *name,
        SQLSMALLINT sql_type,
        SQLULEN sql_size,
        SQLSMALLINT sql_decimal,
        SQLSMALLINT sql_nullable
    );
    ~ColumnMetadata();

    SQLCHAR *sql_name;
    SQLSMALLINT sql_type;
    SQLULEN sql_size;
    SQLSMALLINT sql_decimal;
    SQLSMALLINT sql_nullable;

    SQLCHAR szSchema[STR_LEN];
    SQLCHAR szCatalog[STR_LEN];
    SQLCHAR szColumnName[STR_LEN];
    SQLCHAR szTableName[STR_LEN];
    SQLCHAR szTypeName[STR_LEN];
    SQLCHAR szRemarks[REM_LEN];
    SQLCHAR szColumnDefault[STR_LEN];
    SQLCHAR szIsNullable[STR_LEN];

    SQLINTEGER ColumnSize;
    SQLINTEGER BufferLength;
    SQLINTEGER CharOctetLength;
    SQLINTEGER OrdinalPosition;

    SQLSMALLINT DataType;
    SQLSMALLINT DecimalDigits;
    SQLSMALLINT NumPrecRadix;
    SQLSMALLINT Nullable;
    SQLSMALLINT SQLDataType;
    SQLSMALLINT DatetimeSubtypeCode;

    SQLLEN cbCatalog;
    SQLLEN cbSchema;
    SQLLEN cbTableName;
    SQLLEN cbColumnName;
    SQLLEN cbDataType;
    SQLLEN cbTypeName;
    SQLLEN cbColumnSize;
    SQLLEN cbBufferLength;
    SQLLEN cbDecimalDigits;
    SQLLEN cbNumPrecRadix;
    SQLLEN cbNullable;
    SQLLEN cbRemarks;
    SQLLEN cbColumnDefault;
    SQLLEN cbSQLDataType;
    SQLLEN cbDatetimeSubtypeCode;
    SQLLEN cbCharOctetLength;
    SQLLEN cbOrdinalPosition;
    SQLLEN cbIsNullable;
};

class TableColumnMetadata {
public:
    TableColumnMetadata(SQLHSTMT hstmt);
    ~TableColumnMetadata();


    std::vector<ColumnMetadata *> columns;
    ColumnMetadata operator[](const char *col);
};


#endif  // _NPCONTAINER_H_
