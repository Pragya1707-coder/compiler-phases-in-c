#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Structure to represent a Token
typedef struct {
    char type[20];
    char value[20];
} Token;

Token tokens[50];
int tokenCount = 0;

// Function Prototypes for Compiler Phases
void lexicalAnalysis(char *input);
void syntaxAnalysis();
void intermediateCodeGeneration();
void codeOptimization();
void targetCodeGeneration();

int main() {
    char input[100];

    printf("==================================================\n");
    printf("         MINI COMPILER PHASES DEMONSTRATION       \n");
    printf("==================================================\n\n");

    printf("Enter an assignment expression (e.g., x = y + 5): ");
    fgets(input, sizeof(input), stdin);

    // Remove newline character if present
    input[strcspn(input, "\n")] = 0;

    printf("\n>>> SOURCE CODE: %s <<<\n", input);

    // Phase 1: Lexical Analysis
    lexicalAnalysis(input);

    // Phase 2: Syntax Analysis
    syntaxAnalysis();

    // Phase 3 & 4: Intermediate Code Generation
    intermediateCodeGeneration();

    // Phase 5: Code Optimization
    codeOptimization();

    // Phase 6: Target Code Generation (8086 Assembly)
    targetCodeGeneration();

    return 0;
}

// ------------------------------------------------------------------
// PHASE 1: LEXICAL ANALYZER
// ------------------------------------------------------------------
void lexicalAnalysis(char *input) {
    printf("\n--------------------------------------------------\n");
    printf("PHASE 1: LEXICAL ANALYSIS (Tokenization)\n");
    printf("--------------------------------------------------\n");

    int i = 0;
    tokenCount = 0;

    while (input[i] != '\0') {
        if (isspace(input[i])) {
            i++;
            continue;
        }

        if (isalpha(input[i])) {
            int j = 0;
            while (isalnum(input[i])) {
                tokens[tokenCount].value[j++] = input[i++];
            }
            tokens[tokenCount].value[j] = '\0';
            strcpy(tokens[tokenCount].type, "IDENTIFIER");
            tokenCount++;
        }
        else if (isdigit(input[i])) {
            int j = 0;
            while (isdigit(input[i])) {
                tokens[tokenCount].value[j++] = input[i++];
            }
            tokens[tokenCount].value[j] = '\0';
            strcpy(tokens[tokenCount].type, "NUMBER");
            tokenCount++;
        }
        else if (strchr("+=*-/", input[i])) {
            tokens[tokenCount].value[0] = input[i++];
            tokens[tokenCount].value[1] = '\0';
            strcpy(tokens[tokenCount].type, "OPERATOR");
            tokenCount++;
        }
        else {
            printf("Lexical Error: Unknown character '%c'\n", input[i]);
            exit(1);
        }
    }

    printf("%-15s | %-15s\n", "TOKEN TYPE", "VALUE");
    printf("----------------------------------\n");
    for (int k = 0; k < tokenCount; k++) {
        printf("%-15s | %-15s\n", tokens[k].type, tokens[k].value);
    }
}

// ------------------------------------------------------------------
// PHASE 2: SYNTAX ANALYZER
// ------------------------------------------------------------------
void syntaxAnalysis() {
    printf("\n--------------------------------------------------\n");
    printf("PHASE 2: SYNTAX ANALYSIS (Parsing)\n");
    printf("--------------------------------------------------\n");

    // Check basic structural pattern: <IDENTIFIER> = <IDENTIFIER/NUMBER> <OPERATOR> <IDENTIFIER/NUMBER>
    if (tokenCount >= 5 &&
        strcmp(tokens[0].type, "IDENTIFIER") == 0 &&
        strcmp(tokens[1].value, "=") == 0 &&
        strcmp(tokens[3].type, "OPERATOR") == 0) {
        
        printf("Syntax Check Passed! Valid assignment statement.\n");
        printf("Abstract Syntax Tree (AST) Representation:\030\n");
        printf("       (=)\n");
        printf("      /   \\\n");
        printf("   (%s)   (%s)\n", tokens[0].value, tokens[3].value);
        printf("         /   \\\n");
        printf("      (%s)   (%s)\n", tokens[2].value, tokens[4].value);
    } else {
        printf("Syntax Error: Input does not match format '<var> = <arg1> <op> <arg2>'\n");
        exit(1);
    }
}

// ------------------------------------------------------------------
// PHASE 3: INTERMEDIATE CODE GENERATOR (Three-Address Code)
// ------------------------------------------------------------------
void intermediateCodeGeneration() {
    printf("\n--------------------------------------------------\n");
    printf("PHASE 3: INTERMEDIATE CODE GENERATION (TAC)\n");
    printf("--------------------------------------------------\n");

    printf("Three-Address Code (TAC):\n");
    printf("t1 = %s %s %s\n", tokens[2].value, tokens[3].value, tokens[4].value);
    printf("%s = t1\n", tokens[0].value);
}

// ------------------------------------------------------------------
// PHASE 4: CODE OPTIMIZER
// ------------------------------------------------------------------
void codeOptimization() {
    printf("\n--------------------------------------------------\n");
    printf("PHASE 4: CODE OPTIMIZATION\n");
    printf("--------------------------------------------------\n");

    // Check for Constant Folding Opportunity (e.g., x = 5 + 10)
    if (strcmp(tokens[2].type, "NUMBER") == 0 && strcmp(tokens[4].type, "NUMBER") == 0) {
        int val1 = atoi(tokens[2].value);
        int val2 = atoi(tokens[4].value);
        int res = 0;

        if (strcmp(tokens[3].value, "+") == 0) res = val1 + val2;
        else if (strcmp(tokens[3].value, "-") == 0) res = val1 - val2;
        else if (strcmp(tokens[3].value, "*") == 0) res = val1 * val2;
        else if (strcmp(tokens[3].value, "/") == 0) res = val1 / val2;

        printf("Optimization Applied: Constant Folding\n");
        printf("Optimized TAC:\n");
        printf("%s = %d\n", tokens[0].value, res);
    } else {
        printf("No constant folding available. TAC remains unchanged:\n");
        printf("t1 = %s %s %s\n", tokens[2].value, tokens[3].value, tokens[4].value);
        printf("%s = t1\n", tokens[0].value);
    }
}

// ------------------------------------------------------------------
// PHASE 5: TARGET CODE GENERATOR (8086 Assembly)
// ------------------------------------------------------------------
void targetCodeGeneration() {
    printf("\n--------------------------------------------------\n");
    printf("PHASE 5: TARGET CODE GENERATION (8086 Assembly)\n");
    printf("--------------------------------------------------\n");

    printf("Generated 8086 Assembly Code:\n\n");

    printf("MOV AX, %s\n", tokens[2].value);

    if (strcmp(tokens[3].value, "+") == 0) {
        printf("ADD AX, %s\n", tokens[4].value);
    } else if (strcmp(tokens[3].value, "-") == 0) {
        printf("SUB AX, %s\n", tokens[4].value);
    } else if (strcmp(tokens[3].value, "*") == 0) {
        printf("MOV BX, %s\n", tokens[4].value);
        printf("MUL BX\n");
    } else if (strcmp(tokens[3].value, "/") == 0) {
        printf("MOV BX, %s\n", tokens[4].value);
        printf("DIV BX\n");
    }

    printf("MOV %s, AX\n", tokens[0].value);
    printf("--------------------------------------------------\n");
}