#pragma once

#include <string>

namespace comet {

class Value {
public:

    virtual ~Value() = default;

    virtual std::string asString() const = 0;

    virtual int asNumber() const = 0;

};



class NumberValue : public Value {

    int m_value;

public:

    NumberValue(std::string value);

    NumberValue(int value);

    inline std::string asString() const override;

    inline int asNumber() const override;

};



class StringValue : public Value {

    std::string m_value;

public:

    StringValue(std::string value);

    inline std::string asString() const override;

    // return length of string
    inline int asNumber() const override;

};

}