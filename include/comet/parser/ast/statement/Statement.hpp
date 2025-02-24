#pragma once

namespace comet {

class Statement {
public:

    virtual ~Statement() = default;

    virtual void execute() = 0;
};


}