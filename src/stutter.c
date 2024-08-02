#include "orbit.h"
#include "stutter.h"

int main() {
    da(Token) token_stream = lex(str("yuh"));

    u32 current = 0;
    Expr* program = parse_list(token_stream.at, &current);

    print_expr(program, 0);
}