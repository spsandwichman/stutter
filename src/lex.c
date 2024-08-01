#include "stutter.h"

typedef struct Lexer {
    u64 cursor;
    string text;
} Lexer;

static Token next(Lexer* l) {
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

