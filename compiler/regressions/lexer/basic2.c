// RUN: cbit %s --keep_lexer=true 
// RUN: diff basic2.lex basic2.expected 
// RUN: rm -rf basic2.lex

int add(int a, int b) {
    return a+b;
}

int main() {
    int a = add(2,3);
    return 0;
}