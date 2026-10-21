//#define WIN32_LEAN_AND_MEAN
//#include <windows.h>
//#undef UNICODE
//#undef _UNICODE
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <sql.h>
//#include <sqlext.h>
//
//#pragma comment(lib, "odbc32.lib")
//
//void checkRC(SQLRETURN rc, SQLHANDLE handle, SQLSMALLINT handleType, const char* msg) {
//    if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) {
//        SQLCHAR sqlState[6];
//        SQLCHAR errMsg[256];
//        SQLINTEGER errCode;
//        SQLSMALLINT msgLen;
//
//        SQLGetDiagRecA(
//            handleType,
//            handle,
//            1,
//            sqlState,
//            &errCode,
//            errMsg,
//            sizeof(errMsg),
//            &msgLen
//        );
//
//        printf("ERROR: %s | SQLSTATE=%s | Code=%d | %s\n",
//            msg, sqlState, (int)errCode, errMsg);
//        exit(1);
//    }
//}
//
//int main() {
//    SQLHENV env = NULL;
//    SQLHDBC dbc = NULL;
//    SQLRETURN rc;
//
//    rc = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
//    checkRC(rc, env, SQL_HANDLE_ENV, "AllocEnv failed");
//
//    SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
//
//    rc = SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);
//    checkRC(rc, dbc, SQL_HANDLE_DBC, "AllocDbc failed");
//
//    SQLCHAR dsn[] = "ST124_ODBC";
//    SQLCHAR user[] = "root";
//    SQLCHAR pwd[] = "20260902yui";
//
//    rc = SQLConnectA(dbc, dsn, SQL_NTS, user, SQL_NTS, pwd, SQL_NTS);
//    checkRC(rc, dbc, SQL_HANDLE_DBC, "Connect failed");
//
//    printf("ODBC connect success!\n");
//
//    SQLDisconnect(dbc);
//    SQLFreeHandle(SQL_HANDLE_DBC, dbc);
//    SQLFreeHandle(SQL_HANDLE_ENV, env);
//    return 0;
//}