#include <iostream>
#include <occi.h>
using oracle::occi::Environment;
using oracle::occi::Connection;
using oracle::occi::Statement;
using oracle::occi::ResultSet;
using namespace oracle::occi;
using namespace std;

int main()
{
    // Declare variables
    string user = "dbs211_232ngg15";
    string pass = "62215237";
    string constr = "myoracle12c.senecacollege.ca:1521/oracle12c";
    Environment* env = nullptr;
    Connection* conn = nullptr;
    Statement* stmt = nullptr;
    ResultSet* rs = nullptr;

    try {
        // Create the environment
        env = Environment::createEnvironment(Environment::DEFAULT);

        // Create the connection
        conn = env->createConnection(user, pass, constr);
        cout << "Connection is successful!" << endl;

        // Create the statement
        stmt = conn->createStatement();

        // Prompt for employee number
        int empNumber;
        cout << "Enter the employee number: ";
        cin >> empNumber;

        // Prepare the query
        string query = "SELECT * FROM employees WHERE employee_number = " + to_string(empNumber);

        // Execute the query
        rs = stmt->executeQuery(query);

        // Check if the result set is empty
        if (!rs->next()) {
            cout << "No records found for employee number " << empNumber << endl;
        }
        else {
            cout << "Employee Number\tFirst Name\tLast Name\tSalary" << endl;
            cout << "---------------------------------------------------------" << endl;

            // Fetch and display the data
            do {
                cout << rs->getInt("EMPLOYEE_NUMBER") << "\t\t"
                    << rs->getString("FIRST_NAME") << "\t\t"
                    << rs->getString("LAST_NAME") << "\t\t"
                    << rs->getFloat("SALARY") << endl;
            } while (rs->next());
        }

        // Close the result set
        stmt->closeResultSet(rs);

        // Close the statement
        conn->terminateStatement(stmt);

        // Close the connection
        env->terminateConnection(conn);
    }
    catch (SQLException& sqlExcp) {
        cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage() << endl;
    }

    // Terminate the environment
    Environment::terminateEnvironment(env);

    return 0;
}
