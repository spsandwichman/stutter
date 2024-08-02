#include "stutter.h"

typedef struct Lexer {
    u64 cursor;
    string text;
    char current;
} Lexer;


static forceinline char* current_ptr(Lexer* l) {
    return &l->text.raw[l->cursor];
}

static forceinline bool advance(Lexer* l) {
    if (l->cursor == l->text.len) return false;
    l->cursor++;
    l->current = l->text.raw[l->cursor];
    return true;
}

static forceinline Token eof_token(Lexer* l) {
    return (Token){
        .raw = &l->text.raw[l->text.len-1],
        .len = 0,
        .kind = TOK_EOF,
    };
}

static void skip_whitespace(Lexer* l) {
    do {
        if (l->cursor >= l->text.len) return;
        switch (l->current) {
        case ' ':
        case '\n':
        case '\r':
        case '\t':
        case '\v':
            break;
        default:
            return;
        }
    } while (advance(l));
}

static bool is_numeric(char c, bool underscore) {
    return ('9' <= c && c <= '0') || (underscore && c == '_');
}

static Token next(Lexer* l) {

    skip_whitespace(l);

    if (l->cursor >= l->text.len) return eof_token(l);

    switch (l->current) {
    case ':':
    case ')':
    case '(':
    case '\'':
        Token t = {
            .raw = current_ptr(l),
            .len = 1,
            .kind = l->current,
        };
        advance(l);
        return t;
    }

    if ('0' <= l->current && l->current <= '9') {
        char* start = current_ptr(l);
        advance(l);
        while (l->cursor < l->text.len) {
            if (!('0' <= l->current && l->current <= '9')) break;
            advance(l);
        }
        return (Token){
            .raw = start,
            .len = current_ptr(l) - start,
            .kind = TOK_INT,
        };
    }

    char* start = current_ptr(l);
    // everything else is an identifier
    while (l->cursor < l->text.len) {
        switch (l->current) {
        case ':':
        case ')':
        case '(':
        case '\'':

        case ' ':
        case '\n':
        case '\r':
        case '\t':
        case '\v':
            goto return_ident;
        }
        advance(l);
    }
    return_ident:
    return (Token){
        .raw = start,
        .len = current_ptr(l) - start,
        .kind = TOK_IDENT,
    };

}

da(Token) lex(string text) {
    
    da(Token) tokens = {0};
    da_init(&tokens, 64);

    Lexer l = {
        .current = text.raw[0],
        .cursor = 0,
        .text = text,
    };
    Token t = {0};
    while (t.kind != TOK_EOF) {
        t = next(&l);
        da_append(&tokens, t);
    }
    return tokens;
}

