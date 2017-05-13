#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <map>
#include "cnf.h"
using namespace std;


/**
 * Read the contents of a CNF file and converts to a
 * vector of Clauses
 *
 * @param[in]  filename Character array of the DIMACS CNF file
 * @param[out] numV     will be set with the number of variables
 *                      present in the file
 * @param[out] clauses  will be filled with pointers to dynamically
 *                      allocated Clause objects representing
 *                      the formula
 * @returns False if successful, true if there was an error
 *
 */
bool readCNFFile(char* filename,
                 int& numV,
                 vector<Clause*>& clauses)
{
    ifstream ifile(filename);
    if(ifile.fail()) {
        cerr << "Couldn't open file" << endl;
        return 1;
    }
    int numC;
    char cmd;
    string myline;
    bool problemFound = false;
    // Read everything up through the problem statement
    while( !problemFound  && ifile >> cmd ) {
        if(cmd == 'c') {
            getline(ifile, myline);
        }
        else if(cmd == 'p') {
            getline(ifile, myline);
            stringstream ss(myline);
            string dummy;
            ss >> dummy >> numV >> numC;
            if(ss.fail()) {
                cerr << "Couldn't read problem description line" << endl;
                return 1;
            }
            problemFound = true;
        }
    }
    // Read the clauses
    for(int i=0; i < numC; i++) {
        int var;
        vector<int> cvars;
        ifile >> var;
        while( var != 0) {
            cvars.push_back(var);
            ifile >> var;
        }

        clauses.push_back(new Clause(cvars));
    }
    return 0;
}

/**
 * Print all clauses -- for debugging if necessary
 */
void printClauses(vector<Clause* >& clauses)
{
    for(unsigned int i=0; i < clauses.size(); i++) {
        vector<int> vars = clauses[i]->vars();
        for(unsigned int j=0; j < vars.size(); j++) {
            cout << vars[j] << " ";
        }
        cout << endl;
    }
}


/**
 * Helper function to print the status after the var is
 * set to the given value
 */
void assignAndPrint(CNFFormula& cnf, int var, int val)
{
    cnf.assignVar(var, val);
    bool res = cnf.isSatisfied();
    if(res) {
        cout << "Assignment satisfies the formula" << endl;
    }
    else {
        cout << "Assignment leaves the formula unsatisfied" << endl;
    }
}


/**
 * Read the CNF file and implements the command interface
 * to the user.
 */
int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please provide the cnf filename" << endl;
        return 1;
    }
    int numVars;
    vector<Clause* > clauses;
    bool status = readCNFFile(argv[1],  numVars, clauses);
    if(status) {
        cerr << "Error..." << endl;
        return 1;
    }
    //  printClauses(clauses);
    CNFFormula cnf(numVars, clauses);

    string cmd, line;
    while( getline(cin, line) ) {
        stringstream ss(line);
        if(ss >> cmd) {
            int var, val;
            if(cmd == "quit") break;
            else if(cmd == "set") {
                if(ss >> var >> val) {
                    if(var >= 1 && var <= numVars && (val == VAL0 || val == VAL1)) {
                        assignAndPrint(cnf, var, val);
                    }
                    else {
                        cout << "Incorrect variable or value" << endl;
                    }
                }
            }
            else if(cmd == "unset") {
                if(ss >> var) {
                    if(var >= 1 && var <= numVars) {
                        assignAndPrint(cnf, var, UNK);
                    }
                    else {
                        cout << "Incorrect variable" << endl;
                    }
                }

            }
            else if(cmd == "print") {
                cnf.printVarValues();
            }
            else {
                cout << "Unknown command" << endl;
            }
        }
    }

    return 0;
}
