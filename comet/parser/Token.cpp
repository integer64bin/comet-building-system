#include <token\Token.hpp>

namespace comet {

Token::Token(TokenType type, std::string text) : 
            m_type(type), m_text(text) { }

TokenType Token::getType() const {
    return m_type;
}

std::string Token::getText() const {
    return m_text;
}


std::ostream &operator <<(std::ostream &os, const Token &t) {
    os << "type : " << asString(t.getType()) << " text : " << t.getText();
    return os;
}



std::string_view asString(comet::TokenType type) {
    switch(type) {
        case comet::TokenType::COMMA:  return std::string_view("comma");
        case comet::TokenType::TEXT:   return std::string_view("text");
        case comet::TokenType::WORD:   return std::string_view("word");
        case comet::TokenType::NUMBER: return std::string_view("number");
        case comet::TokenType::LPAREN: return std::string_view("left_parenthesis");
        case comet::TokenType::RPAREN: return std::string_view("right_parenthesis");
        case comet::TokenType::COLON:  return std::string_view("colon");
        case comet::TokenType::DOLLAR: return std::string_view("dollar");
        case comet::TokenType::EQ:     return std::string_view("equals");
        default:
            return std::string_view("unknown");
    }
}


}