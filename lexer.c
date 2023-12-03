#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Token types
typedef enum {
    RESERVED,
    IDENTIFIER,
    LITERAL,
    SYMBOL,
    WHITESPACE,
    COMMENT,
    INVALID
} TokenType;

// Token structure
typedef struct {
    TokenType type;
    char value[100];
} Token;

// Function to tokenize the input code
Token* tokenize(const char* code, int* numTokens) {
    Token* tokens = malloc(sizeof(Token) * strlen(code));
    int tokenCount = 0;
    int codeIndex = 0;

    while (code[codeIndex] != '\\0') {
        // Skip whitespace
        if (code[codeIndex] == ' ' || code[codeIndex] == '\\t' || code[codeIndex] == '\\n') {
            codeIndex++;
            continue;
        }

        // Check for reserved keywords
        if (strncmp(&code[codeIndex], "reserve", 7) == 0 ||
            strncmp(&code[codeIndex], "update", 6) == 0 ||
            strncmp(&code[codeIndex], "cancel", 6) == 0 ||
            strncmp(&code[codeIndex], "check", 5) == 0 ||
            strncmp(&code[codeIndex], "create", 6) == 0 ||
            strncmp(&code[codeIndex], "generate", 8) == 0 ||
            strncmp(&code[codeIndex], "request", 7) == 0) {
            // Create reserved token
            tokens[tokenCount].type = RESERVED;
            strncpy(tokens[tokenCount].value, &code[codeIndex], 10);
            tokens[tokenCount].value[10] = '\\0';
            tokenCount++;
            codeIndex += 10;
            continue;
        }

        // Check for identifiers
        if (isalpha(code[codeIndex])) {
            int identifierIndex = 0;
            while (isalpha(code[codeIndex]) || isdigit(code[codeIndex])) {
                tokens[tokenCount].value[identifierIndex] = code[codeIndex];
                codeIndex++;
                identifierIndex++;
            }
            tokens[tokenCount].value[identifierIndex] = '\\0';
            tokens[tokenCount].type = IDENTIFIER;
            tokenCount++;
            continue;
        }

        // Check for literals
        if (isdigit(code[codeIndex])) {
            int literalIndex = 0;
            while (isdigit(code[codeIndex])) {
                tokens[tokenCount].value[literalIndex] = code[codeIndex];
                codeIndex++;
                literalIndex++;
            }
            tokens[tokenCount].value[literalIndex] = '\\0';
            tokens[tokenCount].type = LITERAL;
            tokenCount++;
            continue;
        }

        // Check for symbols
        if (code[codeIndex] == '<' || code[codeIndex] == '>' || code[codeIndex] == '=' || code[codeIndex] == '-') {
            tokens[tokenCount].value[0] = code[codeIndex];
            tokens[tokenCount].value[1] = '\\0';
            tokens[tokenCount].type = SYMBOL;
            tokenCount++;
            codeIndex++;
            continue;
        }

        // Check for comments
        if (code[codeIndex] == '/' && code[codeIndex + 1] == '/') {
            int commentIndex = 0;
            while (code[codeIndex] != '\\n' && code[codeIndex] != '\\0') {
                tokens[tokenCount].value[commentIndex] = code[codeIndex];
                codeIndex++;
                commentIndex++;
            }
            tokens[tokenCount].value[commentIndex] = '\\0';
            tokens[tokenCount].type = COMMENT;
            tokenCount++;
            continue;
        }

        // Invalid token
        tokens[tokenCount].value[0] = code[codeIndex];
        tokens[tokenCount].value[1] = '\\0';
        tokens[tokenCount].type = INVALID;
        tokenCount++;
        codeIndex++;
    }

    *numTokens = tokenCount;
    return tokens;
}

// Function to print tokens
void printTokens(Token* tokens, int numTokens) {
    for (int i = 0; i < numTokens; i++) {
        printf("Token Type: %d, Value: %s\\n", tokens[i].type, tokens[i].value);
    }
}

int main() {
    const char* code = "reserve room deluxe from 2022-01-01 to 2022-01-05 for John Doe";
    int numTokens;
    Token* tokens = tokenize(code, &numTokens);
    printTokens(tokens, numTokens);
    free(tokens);
    return 0;
}
