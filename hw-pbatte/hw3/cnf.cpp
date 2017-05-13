#include "cnf.h"
#include <cstdlib>
using namespace std;

/**
 * Helper function to take the absolute value of an integer
 */
int intabs(int a)
{
    if(a < 0) return -a;
    return a;
}

Clause::Clause() : isTrue_(false)
{

}

Clause::Clause(const vector<int>& vars)
    : vars_(vars), isTrue_(false)
{

}
int Clause::eval(std::map<int,int>& varValues)
{
    bool check = false;
    for(unsigned int i = 0; i < vars_.size(); i++)
    {
        map<int, int>::iterator it;

        if(vars_[i] < 0)
        {
            if(varValues[-vars_[i]] == 0)
                check = true;
        }
        else
        {
            if(varValues[vars_[i]] == 1)
                check = true;
        }
    }
    if(check == true && isTrue_ == false)
    {
        isTrue_ = true; return 1;
    }
    else if(check == false && isTrue_ == true)
    {
        isTrue_ = false; return -1;
    }
    else
        return 0;
}


CNFFormula::CNFFormula(int nVars, const vector<Clause*>& clauses)
    : clauses_(clauses), numSatisfied_(0)
{
    for(int i = 1; i <= nVars; i++)
    {
        set<Clause*> included_clauses;
        vector<Clause*>::const_iterator iter;
        for(iter = clauses_.begin(); iter != clauses_.end(); ++iter)
        {
            vector<int> temp_vals = (*iter)->vars();

            for(unsigned int k = 0; k < temp_vals.size(); k++)
            {
                if(intabs(temp_vals[k]) == i)
                    included_clauses.insert(*iter);
            }
        }
        varValues_.insert(make_pair(i, -1));
        varToClauses_.insert(make_pair(i, included_clauses));
    }
}

CNFFormula::~CNFFormula()
{
    map<int, set<Clause*> >::iterator it;
    set<Clause*>::iterator it2;
    for(it = varToClauses_.begin(); it != varToClauses_.end(); ++it)
    {
        set<Clause*> temp = it->second;
        for(it2 = temp.begin(); it2 != temp.end(); ++it2)
        {
            temp.erase(it2);
        }
        varToClauses_.erase(it);
    }

    vector<Clause*>::iterator c;
    for(c = clauses_.begin(); c != clauses_.end(); ++c)
    {
        delete *c;
    }
}

bool CNFFormula::isSatisfied() const
{
    return numSatisfied_ == clauses_.size();
}

void CNFFormula::printVarValues() const
{
    map<int, int>::const_iterator it;
    for(it = varValues_.begin(); it != varValues_.end(); ++it)
    {
        if(it->second == -1)
            cout << "Var " << it->first << " : " << "Unassigned" << endl;
        else
            cout << "Var " << it->first << " : " << it->second << endl;

    }
}
void CNFFormula::assignVar(int var, int val)
{
    map<int, int>::iterator it = varValues_.find(var);

    it->second = val;

    int check;
    map<int, set<Clause*> >::iterator it2 = varToClauses_.find(var);

    set<Clause*> included_clauses = it2->second;
    set<Clause*>::iterator it3;
    for(it3 = included_clauses.begin(); it3 != included_clauses.end(); ++it3)
    {
        check = (*it3)->eval(varValues_);        

        numSatisfied_ += check;
    }
}