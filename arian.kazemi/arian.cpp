#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <occi.h>

using oracle::occi::Connection;
using oracle::occi::Environment;

using namespace oracle::occi;
using namespace std;

int main(void)
{
    //OCCI Variables
    Environment* env = nullptr;
    Connection* conn = nullptr;

    //User Variables
    string str;
    // string usr = "dbs211_232ngg15";
    string user = "dbs211_232ngg15";
    string pass = "62215237";
    // string srv = "myoracle12c.senecacollege.ca:1521/oracle12c";
    string constr = "myoracle12c.senecacollege.ca:1521/oracle12c";

    try
    {
        env = Environment::createEnvironment(Environment::DEFAULT);
        // conn = env->createConnection(usr, pass, srv);
        conn = env->createConnection(user, pass, constr);
        cout << "Connection is Successful!" << endl;
        Statement* stmt = conn->createStatement();

        ResultSet* rs = stmt->executeQuery("SELECT employeenumber,
            firstname, lastname, phone, extension FROM employees JOIN offices ON
            employees.officecode = offices.officecode AND offices.city = 'San Francisco'");
            cout << "**************** Employee Report ****************" << endl
            << "Employee Report:" << endl;

        while (rs->next()) {
            int ID = rs->getInt(1);
            string firstname = rs->getString(2);
            string lastname = rs->getString(3);
            string phone = rs->getString(4);
            string extention = rs->getString(5);
            cout << "ID: " << ID << setw(13) << right << setfill(' ');
            cout << "Name: " << firstname << " " << lastname << setw(15) << right << setfill(' ');
            cout << "Phone: " << phone << setw(20) << right << setfill(' ');
            cout << "Extension: " << extention << right << setfill('.') << endl;
        }

        stmt->executeQuery("CREATE VIEW viewresult AS SELECT
            e1.employeenumber, e1.firstname, e1.lastname, phone, e1.extension FROM employees
            e1 JOIN offices USING(officecode) JOIN employees e2 ON e1.employeenumber =
            e2.reportsto");
            cout << "Manager Report:" << endl;
        rs = stmt->executeQuery("SELECT DISTINCT employeenumber,
            firstname, lastname, phone, extension from viewresult ORDER BY employeenumber");
            while (rs->next()) {
                int ID = rs->getInt(1);
                string firstname = rs->getString(2);
                string lastname = rs->getString(3);
                string phone = rs->getString(4);
                string extention = rs->getString(5);
                cout << "ID: " << ID << setw(13) << right << setfill(' ');
                cout << "Name: " << firstname << " " << lastname << setw(15)
                    << right << setfill(' ');

                cout << "Phone: " << phone << setw(20) << right << setfill('
                    ');
                    cout << "Extension: " << extention << right << setfill('.') <<
                    endl;
            }
        stmt->executeQuery("DROP VIEW viewresult");
        conn->terminateStatement(stmt);
        env->terminateConnection(conn);
        Environment::terminateEnvironment(env);
    }
    catch (SQLException& sqlExcp)
    {
        cout << sqlExcp.getErrorCode() << ":" << sqlExcp.getMessage();
    }
    return 0;
}