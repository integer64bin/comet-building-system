#include <cctype>
#include <iostream>

#include <Lexer.hpp>



namespace comet {

const char Lexer::eof = -1;

Lexer::Lexer(std::string &src) : m_src(src) { 
    m_index = 0;
    m_length = m_src.length();
}

/*===========================Methods implementation==========================*/

std::vector<Token> &Lexer::tokenize() {
    while(get() != eof) {
        char current = get();
        if(std::isdigit( current )) {
            tokenizeNumber();
            continue;
        }
        if(isOperator()) {
            tokenizeOperator();
            continue;
        }
        if(current == '\"'){
            tokenizeText();
            continue;
        }
        if(current == '#') {
            tokenizeComments();
            continue;
        }
        if(std::isalpha(current)) {
            tokenizeWord();
            continue;
        }
        next(); // skips \n \s \t \v \r \f
    }
    return m_tokens;
}

void Lexer::tokenizeNumber() {
    std::string_view number;
    std::size_t s = m_index;
    while( std::isdigit( get() ) ) {
        next();
    }
    number = m_src.substr(s, m_index-s);
    add(TokenType::NUMBER, number.data());
}


void Lexer::tokenizeOperator() {
    add(static_cast<TokenType>( get() ), m_src.substr(m_index, 1).data() );
    next();
}

void Lexer::tokenizeWord() {
    std::size_t s = m_index;
    std::string_view buff;
    while(std::isalpha(next())); //skips all letters
    m_index--; // a last symbol wasn't letter
    buff = m_src.substr(s, m_index-s);
    add(TokenType::WORD, buff.data());
}

void Lexer::tokenizeText() {
    next(); // skips "
    std::size_t s = m_index;
    while( get() != '"' ) {
        if(get() == '/') {
            m_src.replace(m_index, 1, "\\");
        }
        next();
    }
    next();
    add(TokenType::TEXT, m_src.substr(s, m_index-s-1).data() );
}

void Lexer::tokenizeComments() {
    while(next() != '\n');
}

// Supporting methods
char Lexer::get(size_t relativePos) {
    // std::cout << m_index << std::endl;
    if(relativePos+m_index >= m_length)
        return eof;
    size_t i = m_index + relativePos;
    return m_src[i];
}

inline char Lexer::peek() {
    char c = m_src[m_index++];
    return c == 0 ? eof : c;
}

inline char Lexer::next() {
    return m_src[m_index++];
}

inline bool Lexer::isOperator() {
    return get() == TokenType::COMMA  ||
           get() == TokenType::LPAREN ||
           get() == TokenType::RPAREN ||
           get() == TokenType::COLON  ||
           get() == TokenType::DOLLAR ||
           get() == TokenType::EQ;
}


inline void Lexer::add(TokenType type, std::string text) {
    m_tokens.push_back(Token(type, text));
}


}
// k7-f16IEE-_CaNnA!_78eF-CcE