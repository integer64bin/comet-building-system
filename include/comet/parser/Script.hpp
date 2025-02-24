#pragma once

#include <string>
#include <list>

#include <parser\ast\statement\Statement.hpp>

namespace comet {

class Parser;

class Script {
    
    friend class Parser;

    std::string m_data;

    std::list<Statement*> m_statements;

    
public:

    Script() = default;
    
    Script(const std::string &src);

    ~Script();
    
    void perform();

    void execute();
    
private:

    void addStatement(Statement *st);

};



}