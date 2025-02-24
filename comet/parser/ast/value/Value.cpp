#include <cstdio>

#include <ast\value\Value.hpp>

namespace comet {

/*============================Number value===========================*/

// Constructors
// By string
NumberValue::NumberValue(std::string value) {
    m_value = std::stoi(value);
}

// By integer value
NumberValue::NumberValue(int value) : m_value(value) { }


inline std::string NumberValue::asString() const {
    return std::to_string(m_value);
}



inline int NumberValue::asNumber() const {
    return m_value;
}



/*============================String value===========================*/

// Constructor
StringValue::StringValue(std::string value) : m_value(value){ }
    
inline std::string StringValue::asString() const {
    return m_value;
}


// return length of string
inline int StringValue::asNumber() const {
    return m_value.size();
}

}