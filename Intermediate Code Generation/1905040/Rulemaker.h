#include<string>
#include<vector>
class Rulemaker
{    /* data */
public:

    std::string rule;
    std::vector <Rulemaker*> rulelist;
    int rulestrt;
    int ruleend;
    void add(Rulemaker* rule){
        rulelist.push_back(rule);
    };
};
