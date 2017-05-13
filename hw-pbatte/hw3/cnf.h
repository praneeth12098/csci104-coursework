#ifndef CNF_H
#define CNF_H

#include <iostream>
#include <vector>
#include <set>
#include <map>

enum ValEnum {UNK=-1, VAL0=0, VAL1=1};


/**
 * Models one clause in a CNF formula
 */
class Clause
{
public:

    /**
     * Default constructor
     */
    Clause();

    /**
     * Constructs a Clause from its list of variables and their
     *  negated/true form (x = true form, -x = negated form)
     */
    Clause(const std::vector<int>& vars);

    /**
     * Given a map of the variables and their values
     * determine if the clauses has become true, false
     * or unchanged since the last evaluation
     *
     * @param [in] varValues map with key=variable ID and
     *                       value = {UNK, VAL0, or VAL1}
     * @return +1 if the clauses was not true the last time
     *            evaluated but is true now
     *         -1 if the clause was true the last time
     *            evaluated but is not true now
     *          0 if the clause's status is unchanged from
     *            the last evaluation
     */
    int eval(std::map<int,int>& varValues);

    /**
     * Return a copy of the variable list
     */
    std::vector<int> vars() const
    {
        return vars_;
    }
private:
    // vars (x or -x) present in the clause
    std::vector<int> vars_;
    // If the current assignment satisfies this one clause
    bool isTrue_;
};


/**
 * Models and performs operations on a CNFFormula
 */
class CNFFormula
{
public:
    /**
     * Constructs a CNFFormula given a number of variables
     * and the list of pointers to the (dynamically allocated)
     * clauses
     *
     * param[in] nVars maximum variable ID used in the formula
     * param[in] clauses List of clause pointers. The clause
     *                   objects are dynamically allocated and
     *                   should now be "owned" by this CNFFormula
     *                   object (i.e. CNFFormula is responsible
     *                   for their deallocation)
     */
    CNFFormula(int nVars, const std::vector<Clause*>& clauses);

    /**
     * Destructor
     */
    ~CNFFormula();

    /**
     * Updates the value of the given variable and re-evaluates
     * clauses containing that variable. Should run in O(log(n)*c) where
     * c is the number of clauses containing the specified variable and
     * n is the number of variables and the number of variables in a
     * clause is considered a constant
     *
     * @param[in] var Variable ID in the range 1 to n
     * @param[in] val {UNK, VAL0, or VAL1}
     */
    void assignVar(int var, int val);

    /**
     * Returns true if the entire formula evaluates to true,
     * and false, otherwise. Should run in O(1).
     */
    bool isSatisfied() const;

    /**
     * Prints the current assignment of variable values in a nice
     * format.  Follow the format given in the example output
     * in the assignment writeup.
     */
    void printVarValues() const;
private:
    // UNK = unassigned, VAL0=false, VAL1=true
    std::map<int,int> varValues_;
    std::map<int, std::set<Clause*> > varToClauses_;
    std::vector<Clause*> clauses_;
    unsigned int numSatisfied_;

};

#endif
