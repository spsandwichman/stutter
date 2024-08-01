#include "stutter.h"

typedef struct Lexer {
    u64 cursor;
    string text;
} Lexer;

static Token next(Lexer* l) {
    if (l->cursor >= l->text.len) {
        return (Token){
            .raw = &l->text.raw[l->text.len - 1],
            .len = 0, 
            .type = TOK_EOF};
    }

    while (l->cursor >= l->text.len) {
        
    }
}

da(Token) lex(string text) {
    
    da(Token) tokens = {0};
    da_init(&tokens, 64);

    Lexer l = {0, text};
    Token t;
    while ((t = next(&l)), t.type != TOK_EOF) {
        da_append(&tokens, t);
    }
}

