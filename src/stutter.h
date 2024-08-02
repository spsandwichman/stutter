#include "orbit.h"

typedef struct Token Token;
struct Token {
    u8 kind;
    u32 len;
    char* raw;
};

enum {
    TOK_OPEN_PAREN = '(',  // (
    TOK_CLOSE_PAREN = ')', // )

    TOK_QUOTE = '\'',
    TOK_COLON = ':',

    TOK_IDENT,

    TOK_INT,

    TOK_EOF,
};

da_typedef(Token);
da(Token) lex(string text);

enum {
    TYPE_NIL = 0,
    TYPE_INT,
    TYPE_SYMBOL,

    TYPE_PAIR,
};

typedef struct Expr Expr;
typedef struct Expr {
    u8 type;
    union {
        i64 integer;
        string symbol;

        struct {
            Expr* this;
            Expr* next;
        } pair;
    };
} Expr;

Expr* parse_list(Token* ts, u32* current);
void print_expr(Expr* e, int level);