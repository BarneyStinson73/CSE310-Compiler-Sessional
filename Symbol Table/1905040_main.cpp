#include <iostream>
#include<cstdio>
#include <string>
using namespace std;
int bucket;
int scope_table_count=0;
int position_in_hashchain=1;
string list[5];
class SymbolInfo
{
private:
    string name,type;
public:
    SymbolInfo *next;
    void setName(string s)
    {
        name=s;
    }
    string getName()
    {
        return name;
    }
    void setType(string s)
    {
        type=s;
    }
    string getType()
    {
        return type;
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
    SymbolInfo** array;
    ScopeTable* parent;
    ScopeTable()
    {
        scope_num=0;
        scope_table_count++;
        for(int i=0;i<scope_num;i++){
            array[i]=NULL;
        }
        order_no=scope_table_count;
        cout<<"\tScopeTable# "<<order_no<<" created"<<endl;

    }
    ScopeTable(int n)
    {
        scope_num=n;
        array=new SymbolInfo*[scope_num];
        for(int i=0;i<scope_num;i++){
            array[i]=NULL;
        }
        scope_table_count++;
        order_no=scope_table_count;
        cout<<"\tScopeTable# "<<order_no<<" created"<<endl;
    }
    unsigned long long SDBMHash(string str)
    {
        unsigned long long hash = 0;
        unsigned int i = 0;
        unsigned int len = str.length();

        for (i = 0; i < len; i++)
        {
            hash = ((str[i]) + (hash << 6) + (hash << 16) - hash)%scope_num;
        }

        return hash;
    }
    long long hash_function(string name)
    {
        return SDBMHash(name) % scope_num;
    }
    bool insert(string s,string t) //return type needed
    {
        position_in_hashchain=1;
        int prb=0,symbol_count=1;
        long long  p=hash_function(s);
        SymbolInfo* temp=array[p];
        SymbolInfo* emp=new SymbolInfo();
        emp->next=NULL;
        emp->setName(s);
        emp->setType(t);
        if(array[p] == NULL)
        {
            array[p]=emp;
            cout<<"\tInserted in ScopeTable# "<<order_no<<" at position "<<p+1<<", "<<symbol_count<<endl;
            return true;
        }
        else
        {
            while(temp->next!=nullptr)
            {
                if(temp->getName() == s){
                    prb=1;
                    cout<<"\t'"<<list[1]<<"' "<<"already exists in the current ScopeTable"<<endl;
                    break;
                }
                temp=temp->next;
                symbol_count++;

            }
            if(temp->getName() == s){
                prb=1;
                cout<<"\t'"<<list[1]<<"' "<<"already exists in the current ScopeTable"<<endl;
            }
            if(prb==1){
                return false;
            }
            else{
                symbol_count++;
                temp->next=emp;
                cout<<"\tInserted in ScopeTable# "<<order_no<<" at position "<<p+1<<", "<<symbol_count<<endl;
                return true;
            }
        }
    }
    SymbolInfo* LookUp(string n){
        position_in_hashchain=1;
        long long  p=hash_function(n);
        SymbolInfo* temp=array[p];
        if(array[p] == NULL)
        {
            return nullptr;
        }
        else{
            while(temp->next!=NULL)
            {
                // cout<<temp->getName()<<endl;
                if(temp->getName() == n){
                    return temp;
                }
                temp=temp->next;
                position_in_hashchain++;
            }
            if(temp !=NULL){
                if(temp->getName() == n){
                    return temp;
                }
            }
            return nullptr;
        }
    }
    bool Delete(string n){
        long long  p=hash_function(n);
        SymbolInfo* temp=array[p];
        if(array[p] == NULL)
        {
            cout<<"\tNot found in the current ScopeTable"<<endl;
            return false;
        }
        else{
            SymbolInfo* r;
            int flag=0;
            int symbol_count=1;
            r=NULL;
            while(temp!=NULL)
            {
                if(temp->getName() == n){
                    flag=1;
                    break;
                }
                r=temp;
                temp=temp->next;
                symbol_count++;
            }
            if(flag==0){
                cout<<"\tNot found in the current ScopeTable"<<endl;
                return false;
            }
            else{

                if(symbol_count!=1)r->next=temp->next;
                else{
                    array[p]=NULL;
                }

                if(r==NULL){
                    array[p]=NULL;
                }
                cout<<"\tDeleted '"<<list[1]<<"' from ScopeTable# "<<order_no<<" at position "<<
                hash_function(list[1])+1<<", "<<symbol_count<<endl;
                return true;
            }

        }
    }
    void Print(){
        int count=1;
        cout<<"\tScopeTable# "<<order_no<<endl;
        for(int i=0;i<scope_num;i++){
            cout<<"\t"<<count<<"--> ";
            if(array[i]==NULL){
                cout<<endl;
            }
            else{
                SymbolInfo* temp=array[i];
                while(temp!=NULL){
                    cout<<"<" <<temp->getName()<<"," <<temp->getType()<<"> ";
                    temp=temp->next;
                }
                cout<<endl;
            }

            count++;
        }
    }
    ~ScopeTable(){
        delete[] array;
    }

};
class SymbolTable
{
public:
    ScopeTable* current;
    SymbolTable(int n){
        current=new ScopeTable(n);
    }
    void enter_scope()
    {
        ScopeTable* temp=new ScopeTable(bucket);
        temp->parent=current;
        current=temp;
    }
    void exit_scope()
    {
        ScopeTable* s=current;
        current=current->parent;
        cout<<"\tScopeTable# "<<s->order_no<<" removed"<<endl;
        delete s;

    }
    bool insert(string s,string t)
    {
        return current->insert(s,t);//inserting a value

    }
    bool remove(string s)
    {
        return current->Delete(s);
        //remove a symbol
    }
    SymbolInfo* LookUp(string s)
    {
        ScopeTable* temp=current;
        int count =1;
        while(temp->parent !=NULL){
            if(temp->LookUp(s)!=nullptr){
                cout<<"\t'"<<list[1]<<"'" << " found in ScopeTable# " <<temp->order_no<< " at position "<<
                    temp->hash_function(list[1])+1 <<", "<< position_in_hashchain <<endl;
                return temp->LookUp(s);
            };
            temp=temp->parent;
            count++;
        }
        if(temp->LookUp(s) !=NULL){
            cout<<"\t'"<<list[1] << "'" << " found in ScopeTable# " << temp->order_no << " at position " <<
                temp->hash_function(list[1])+1 << ", " <<position_in_hashchain<<endl;
            return temp->LookUp(s);
        }
        cout<<"\t'" <<list[1]<<"'" << " not found in any of the ScopeTables" <<endl;
        position_in_hashchain=1;
        return nullptr;
    }
    void print_current(){
        current->Print();
    }
    void print_all(){
        ScopeTable* temp=current;
        while(temp!=NULL){
            temp->Print();
            temp=temp->parent;
        }
    }
};

void split (string s)
{
    int curr = 0, i = 0,start = 0, end = 0;

    while (i <= s.length())
    {
        if (s[i] == ' ' || i == s.length())
        {
            end = i;
            string word = "";
            word.append(s, start, end - start);
            list[curr] = word;
            curr ++;
            start = end + 1;
        }
        i=i+1;
    }
}
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    long long bucket_number;
    int command_no=1;
    cin>>bucket_number;
    cin.ignore();
    bucket=bucket_number;
    SymbolTable* start=new SymbolTable(bucket_number);
    start->current->parent=NULL;
    while(true){

        for(int i=0;i<5;i++){
            list[i]="";
        }

        string str,delim;
        getline(cin,str);
        cout<<"Cmd "<<command_no<<": ";
        cout<<str<<endl;
        split(str);
        if(list[0]=="Q"){
            ScopeTable* temp=start->current;
            while(temp!=NULL){
                start->exit_scope();
                temp=start->current;
            }
            break;
        }
        else if(list[0]=="I"){
            //insert a symbol in symbol table

            if(list[3]!= ""|list[1] ==""|list[2] ==""){
                cout<<"\tNumber of parameters mismatch for the command I"<<endl;
            }
            else{
                bool p;
                p=start->insert(list[1],list[2]);
            }
        }

        else if(list[0]=="L"){      //Lookup in symbol table
            if(list[2]!= ""|list[1] ==""){
                cout<<"\tNumber of parameters mismatch for the command L"<<endl;
            }
            else{
                SymbolInfo* latest=new SymbolInfo();
                latest->next=NULL;
                latest=start->LookUp(list[1]);
            }
        }

        else if(list[0]=="D"){      //delete
            if(list[2]!= ""|list[1] ==""){
                cout<<"\tNumber of parameters mismatch for the  command D"<<endl;
            }
            else{
                bool check;
                check= start->remove(list[1]);
            }
        }

        else if(list[0]=="P"){      //delete
            if(list[2]!= "" | list[1]==""){
                cout<<"\tNumber of parameters mismatch for the command P"<<endl;
            }
            else{
                if(list[1]=="A"){
                    start->print_all();
                }
                else if(list[1]=="C")
                    start->print_current();
            }
        }
        else if(list[0]=="S"){      //enter scope
            if(list[1]!= ""){
                cout<<"\tNumber of parameters mismatch for the command S"<<endl;
            }
            else{
                start->enter_scope();
            }
        }
        else if(list[0]=="E"){      //delete
            if(list[1]!= ""){
                cout<<"\tNumber of parameters mismatch for the command E"<<endl;
            }
            else{
                if(start->current->parent==NULL){
                    cout<<"\tScopeTable# 1 cannot be removed"<<endl;
                }
                else{
                    start->exit_scope();
                }
            }
        }
        command_no++;
    }
}