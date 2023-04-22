#include "semantic.h"
#include "syntax.tab.h"

extern pNode root;

extern int yylineno;
extern int yyparse();
extern void yyrestart(FILE*);

unsigned lexError = FALSE;
unsigned synError = FALSE;

int main(int argc, char** argv) {
    if (argc <= 1) {
        yyparse();
        return 1;
    }

    FILE* f = fopen(argv[1], "r");
    if (!f) {
        perror(argv[1]);
        return 1;
    }

    yyrestart(f);
    yyparse();
    if (!lexError && !synError) {
        // 创建符号表
        table = initTable();
        // printTreeInfo(root, 0);
        
        // 对语法树进行遍历，进行语义分析
        traverseTree(root);
        // 删除符号表，并释放语法树的内存
        deleteTable(table);
    }
    delNode(&root);
    return 0;
}
