#include <token\Token.hpp>
#include <util.hpp>

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
        case comet::TokenType::COMMA:  return std::string_view("cmm");
        case comet::TokenType::TEXT:   return std::string_view("txt");
        case comet::TokenType::WORD:   return std::string_view("wrd");
        case comet::TokenType::NUMBER: return std::string_view("num");
        case comet::TokenType::LPAREN: return std::string_view("lpr");
        case comet::TokenType::RPAREN: return std::string_view("rpr");
        case comet::TokenType::COLON:  return std::string_view("cln");
        case comet::TokenType::DOLLAR: return std::string_view("dlr");
        case comet::TokenType::EQ:     return std::string_view("eql");
        default:
            return std::string_view("unk");
    }
}


}