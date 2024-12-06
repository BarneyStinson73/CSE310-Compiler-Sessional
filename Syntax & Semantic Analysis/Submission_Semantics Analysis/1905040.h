#pragma once

#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class globals
{
public:
    inline static int bucket;                // 10
    inline static int scope_table_count;     // 0
    inline static int position_in_hashchain; // 1
    // globals(){
    //     bucket=10;
    //     scope_table_count=0;
    //     position_in_hashchain=1;
    // }
};
class SymbolInfo
{
private:
    string name, type;

public:
    string optional;
    SymbolInfo *next;
    vector<SymbolInfo *> var_dec_list;
    vector<SymbolInfo *> func_dec_list;
    int func_def_flag = 0;

    // parse_tree purpose
    vector<SymbolInfo *> symbol_list;
    int start = 0;
    int end = 0;
    int leaf = 0;
    string message;
    SymbolInfo()
    {
        name = "";
        type = "";
        optional = "";
        next = NULL;
    }
    SymbolInfo(string s, string t)
    {
        name = s;
        type = t;
        optional = "";
        next = NULL;
    }
    void setName(string s)
    {
        name = s;
    }
    string getName()
    {
        return name;
    }
    void setType(string s)
    {
        type = s;
    }
    string getType()
    {
        return type;
    }
    void add(SymbolInfo *s)
    {
        symbol_list.push_back(s);
    }
};
class ScopeTable
{
private:
    /* data */
public:
    int scope_num;
    int order_no;
    /// @brief
    SymbolInfo **array;
    ScopeTable *parent;
    ScopeTable()
    {
        scope_num = 10;
        for (int i = 0; i < scope_num; i++)
        {
            array[i] = NULL;
        }
        order_no = globals::scope_table_count;
    }
    ScopeTable(int n)
    {
        scope_num = n;
        array = new SymbolInfo *[scope_num];
        for (int i = 0; i < scope_num; i++)
        {
            array[i] = NULL;
        }
        globals::scope_table_count++;
        order_no = globals::scope_table_count;
    }
    unsigned long long SDBMHash(string str)
    {
        unsigned long long hash = 0;
        unsigned int i = 0;
        unsigned int len = str.length();

        for (i = 0; i < len; i++)
        {
            hash = ((str[i]) + (hash << 6) + (hash << 16) - hash);
        }

        return hash;
    }
    long long hash_function(string name)
    {
        return SDBMHash(name) % scope_num;
    }
    bool insert(string s, string t) // return type needed
    {
        globals::position_in_hashchain = 1;
        int prb = 0, symbol_count = 1;
        long long p = hash_function(s);
        SymbolInfo *temp = array[p];
        SymbolInfo *emp = new SymbolInfo();
        emp->next = NULL;
        emp->setName(s);
        emp->setType(t);
        if (array[p] == NULL)
        {
            array[p] = emp;
            return true;
        }
        else
        {
            while (temp->next != nullptr)
            {
                if (temp->getName() == s)
                {
                    prb = 1;
                    break;
                }
                temp = temp->next;
                symbol_count++;
            }
            if (temp->getName() == s)
            {
                prb = 1;
            }
            if (prb == 1)
            {
                return false;
            }
            else
            {
                symbol_count++;
                temp->next = emp;
                return true;
            }
        }
    }
    bool o_insert(string s, string t, string o)
    {
        globals::position_in_hashchain = 1;
        int prb = 0, symbol_count = 1;
        long long p = hash_function(s);
        SymbolInfo *temp = array[p];
        SymbolInfo *emp = new SymbolInfo();
        emp->next = NULL;
        emp->setName(s);
        emp->setType(t);
        emp->optional = o;
        if (array[p] == NULL)
        {
            array[p] = emp;
            return true;
        }
        else
        {
            while (temp->next != nullptr)
            {
                if (temp->getName() == s)
                {
                    prb = 1;
                    break;
                }
                temp = temp->next;
                symbol_count++;
            }
            if (temp->getName() == s)
            {
                prb = 1;
            }
            if (prb == 1)
            {
                return false;
            }
            else
            {
                symbol_count++;
                temp->next = emp;
                return true;
            }
        }
    }
    SymbolInfo *LookUp(string n)
    {
        globals::position_in_hashchain = 1;
        long long p = hash_function(n);
        SymbolInfo *temp = array[p];
        if (array[p] == NULL)
        {
            return nullptr;
        }
        else
        {
            while (temp->next != NULL)
            {
                // cout<<temp->getName()<<endl;
                if (temp->getName() == n)
                {
                    return temp;
                }
                temp = temp->next;
                globals::position_in_hashchain++;
            }
            if (temp != NULL)
            {
                if (temp->getName() == n)
                {
                    return temp;
                }
            }
            return nullptr;
        }
    }
    bool Delete(string n)
    {
        long long p = hash_function(n);
        SymbolInfo *temp = array[p];
        if (array[p] == NULL)
        {
            return false;
        }
        else
        {
            SymbolInfo *r;
            int flag = 0;
            int symbol_count = 1;
            r = NULL;
            while (temp != NULL)
            {
                if (temp->getName() == n)
                {
                    flag = 1;
                    break;
                }
                r = temp;
                temp = temp->next;
                symbol_count++;
            }
            if (flag == 0)
            {
                return false;
            }
            else
            {

                if (symbol_count != 1)
                    r->next = temp->next;
                else
                {
                    array[p] = NULL;
                }

                if (r == NULL)
                {
                    array[p] = NULL;
                }
                return true;
            }
        }
    }

    ~ScopeTable()
    {
        delete[] array;
    }
};
class SymbolTable
{
public:
    ScopeTable *current;
    // globals a;
    SymbolTable(int n)
    {
        globals::scope_table_count = 0;
        current = new ScopeTable(n);
        globals::bucket = n;
    }
    void enter_scope()
    {
        ScopeTable *temp = new ScopeTable(globals::bucket);
        temp->parent = current;
        current = temp;
    }
    void exit_scope()
    {
        ScopeTable *s = current;
        if (current->parent == NULL)
            return;
        current = current->parent;
        delete s;
    }
    bool insert(string s, string t)
    {
        return current->insert(s, t); // inserting a value
    }
    bool opt_insert(string s, string t, string o)
    {
        return current->o_insert(s, t, o);
    }
    bool remove(string s)
    {
        return current->Delete(s);
        // remove a symbol
    }
    SymbolInfo *LookUp(string s)
    {
        ScopeTable *temp = current;
        int count = 1;
        while (temp->parent != NULL)
        {
            if (temp->LookUp(s) != nullptr)
            {
                return temp->LookUp(s);
            };
            temp = temp->parent;
            count++;
        }
        if (temp->LookUp(s) != NULL)
        {
            return temp->LookUp(s);
        }
        globals::position_in_hashchain = 1;
        return nullptr;
    }
    SymbolInfo *Scope_LookUp(string s)
    {
        ScopeTable *temp = current;
        int count = 1;
        if (temp->LookUp(s) != nullptr)
        {
            return temp->LookUp(s);
        };
        globals::position_in_hashchain = 1;
        return nullptr;
    }
};
