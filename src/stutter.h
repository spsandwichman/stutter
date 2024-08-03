#include "orbit.h"

typedef struct Token Token;
struct Token {
    u8 kind;
    u32 len;
    char* raw;
};