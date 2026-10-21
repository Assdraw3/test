#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef UNICODE
#undef _UNICODE

#include <stdio.h>
#include <stdlib.h>
#include <sql.h>
#include <sqlext.h>

#pragma comment(lib, "odbc32.lib")

void set_console_utf8() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
}

void checkRC(SQLRETURN rc, SQLHANDLE handle, SQLSMALLINT handleType, const char* msg) {
    if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) {
        SQLCHAR sqlState[6];
        SQLCHAR errMsg[256];
        SQLINTEGER errCode;
        SQLSMALLINT msgLen;

        SQLGetDiagRecA(
            handleType,
            handle,
            1,
            sqlState,
            &errCode,
            errMsg,
            sizeof(errMsg),
            &msgLen
        );

        printf("ERROR: %s | SQLSTATE=%s | Code=%d | %s\n",
            msg, sqlState, (int)errCode, errMsg);
        exit(1);
    }
}

int main() {
    set_console_utf8();

    SQLHENV env = NULL;
    SQLHDBC dbc = NULL;
    SQLHSTMT stmt = NULL;
    SQLRETURN rc;

    rc = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
    checkRC(rc, env, SQL_HANDLE_ENV, "AllocEnv failed");

    SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);

    rc = SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);
    checkRC(rc, dbc, SQL_HANDLE_DBC, "AllocDbc failed");

    // ✅ 关键修正：使用直接连接字符串，不依赖 DSN
    SQLCHAR connStr[] =
        "DRIVER={MySQL ODBC 9.7 Unicode Driver};"
        "SERVER=localhost;"
        "PORT=3306;"
        "DATABASE=st124;"
        "USER=root;"
        "PASSWORD=20260902yui;"
        "CHARSET=utf8mb4;";

    SQLCHAR outConnStr[1024];
    SQLSMALLINT outConnStrLen;

    rc = SQLDriverConnectA(
        dbc,
        NULL,
        connStr,
        SQL_NTS,
        outConnStr,
        sizeof(outConnStr),
        &outConnStrLen,
        SQL_DRIVER_COMPLETE
    );
    checkRC(rc, dbc, SQL_HANDLE_DBC, "Connect failed");

    printf("ODBC connect success!\n");

    rc = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    checkRC(rc, stmt, SQL_HANDLE_STMT, "AllocStmt failed");

    SQLCHAR select_sql[] =
        "SELECT Sno, Sname, Sage, Ssex, Sdept, Polity FROM Student";

    rc = SQLExecDirectA(stmt, select_sql, SQL_NTS);
    checkRC(rc, stmt, SQL_HANDLE_STMT, "Select failed");

    SQLCHAR sno[20], sname[50], ssex[10], sdept[50], polity[50];
    int sage;
    SQLLEN len;

    rc = SQLBindCol(stmt, 1, SQL_C_CHAR, sno, sizeof(sno), &len);
    checkRC(rc, stmt, SQL_HANDLE_STMT, "BindCol 1 failed");

    rc = SQLBindCol(stmt, 2, SQL_C_CHAR, sname, sizeof(sname), &len);
    checkRC(rc, stmt, SQL_HANDLE_STMT, "BindCol 2 failed");

    rc = SQLBindCol(stmt, 3, SQL_C_LONG, &sage, sizeof(sage), &len);
    checkRC(rc, stmt, SQL_HANDLE_STMT, "BindCol 3 failed");

    rc = SQLBindCol(stmt, 4, SQL_C_CHAR, ssex, sizeof(ssex), &len);
    checkRC(rc, stmt, SQL_HANDLE_STMT, "BindCol 4 failed");

    rc = SQLBindCol(stmt, 5, SQL_C_CHAR, sdept, sizeof(sdept), &len);
    checkRC(rc, stmt, SQL_HANDLE_STMT, "BindCol 5 failed");

    rc = SQLBindCol(stmt, 6, SQL_C_CHAR, polity, sizeof(polity), &len);
    checkRC(rc, stmt, SQL_HANDLE_STMT, "BindCol 6 failed");

    printf("=====================================================================\n");
    printf("学号\t\t姓名\t年龄\t性别\t院系\t\t政治面貌\n");
    printf("=====================================================================\n");

    while (SQLFetch(stmt) == SQL_SUCCESS) {
        printf("%s\t%s\t%d\t%s\t%s\t%s\n", sno, sname, sage, ssex, sdept, polity);
    }

    printf("=====================================================================\n");
    printf("✅ 查询完成！\n");

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    SQLDisconnect(dbc);
    SQLFreeHandle(SQL_HANDLE_DBC, dbc);
    SQLFreeHandle(SQL_HANDLE_ENV, env);
    return 0;
}