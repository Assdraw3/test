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
//    SQLHSTMT stmt = NULL;
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
//    rc = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
//    checkRC(rc, stmt, SQL_HANDLE_STMT, "AllocStmt failed");
//
//    // 删除指定学号的学生
//    SQLCHAR delete_sql[] =
//        "DELETE FROM Student WHERE Sno = '2024001001'";
//
//    rc = SQLExecDirectA(stmt, delete_sql, SQL_NTS);
//    checkRC(rc, stmt, SQL_HANDLE_STMT, "Delete failed");
//
//    printf("✅ 数据删除成功！\n");
//    printf("请登录 MySQL 客户端验证数据是否已删除。\n");
//
//    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
//    SQLDisconnect(dbc);
//    SQLFreeHandle(SQL_HANDLE_DBC, dbc);
//    SQLFreeHandle(SQL_HANDLE_ENV, env);
//    return 0;
//}