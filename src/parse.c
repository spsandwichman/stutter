#include "stutter.h"

Expr* new_expr(u8 type) {
    Expr* e = calloc(1, sizeof(Expr));
    e->type = type;
    return e;
}

Expr* parse_atom(Token* ts, u32* current);

Expr* parse_list(Token* ts, u32* current) {
    Expr* this = parse_atom(ts, current);
    if (this->type == TYPE_NIL) return this;

    Expr* pair = new_expr(TYPE_PAIR);
    pair->pair.this = this;
    if (ts[*current].kind == TOK_CLOSE_PAREN) {
        pair->pair.next = new_expr(TYPE_NIL);
    } else {
        pair->pair.next = parse_list(ts, current);
    }
    return pair;
}

Expr* parse_atom(Token* ts, u32* current) {
    switch (ts[*current].kind) {
    case TOK_EOF:
        return new_expr(TYPE_NIL);
    case TOK_IDENT:
        Expr* symbol = new_expr(TYPE_SYMBOL);
        symbol->symbol = (string){.raw = ts[*current].raw, .len = ts[*current].len};
        (*current)++;
        return symbol;
    case TOK_OPEN_PAREN:
        (*current)++;
        Expr* list = parse_list(ts, current);
        if (ts[*current].kind != TOK_CLOSE_PAREN) {
            CRASH("expected )");
        }
        (*current)++;
        return list;
    case TOK_CLOSE_PAREN:
        CRASH("unexpected )");
    default:
        CRASH("unrecognized something or other");
        break;
    }
}

static void indent(int level) {
    for_range(_, 0, level) printf("    ");
}

void print_expr(Expr* e, int level) {

    switch (e->type) {
    case TYPE_NIL:
        indent(level);
        printf("nil\n");
        break;
    case TYPE_INT:
        indent(level);
        printf("%lld\n", e->integer);
        break;
    case TYPE_SYMBOL:
        indent(level);
        printf(str_fmt"\n", str_arg(e->symbol));
        break;
    case TYPE_PAIR:
        indent(level);
        printf(".\n");
        print_expr(e->pair.this, level + 1);
        print_expr(e->pair.next, level + 1);
        break;
    default:
        CRASH("");
    }
}