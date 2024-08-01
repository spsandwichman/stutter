#include "orbit.h"

typedef struct Token Token;
struct Token {
    u8 type;
    u32 len;
    char* raw;
};

enum {
    TOK_OPEN, // (
    TOK_CLOSE, // )

    TOK_FLOAT,
    TOK_INT,
    TOK_STRING,
    TOK_SYMBOL,

    TOK_EOF,
};

da_typedef(Token);


// enum {
//     EXPR_LIST,
//     EXPR_I64,
//     EXPR_F64,
//     EXPR_STRING,
//     EXPR_SYMBOL,
// };

// typedef struct Expr Expr;
// struct Expr {
//     u8 kind;
//     u32 first_token;
//     union {
//         struct {
//             Expr* this;
//             Expr* next;
//         } list;
//         i64 i64;
//         f64 f64;
//         string string;
//         string symbol;
//     };
// };