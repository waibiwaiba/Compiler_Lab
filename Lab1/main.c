#include "node.h"
#include "syntax.tab.h"

extern pNode root;

extern int yylineno;
extern int yyparse();
extern void yyrestart(FILE*);

unsigned lexError = FALSE;
unsigned synError = FALSE;

// 主函数
int main(int argc, char** argv) {
    // 如果没有传入参数，直接调用语法分析器并返回错误
    if (argc <= 1) {
        yyparse();  // 调用 Bison 语法分析器
        return 1;   // 返回错误码 1
    }

    // 打开传入的文件
    FILE* f = fopen(argv[1], "r");
    if (!f) {
        perror(argv[1]);    // 输出错误信息
        return 1;           // 返回错误码 1
    }

    // 重置 Flex 的输入缓冲区，并调用 Bison 语法分析器解析文件
    yyrestart(f);           // 重置输入缓冲区
    yyparse();              // 调用 Bison 语法分析器

    // 如果没有语法错误或词法错误，则打印语法树信息
    if (!lexError && !synError) {
        printTreeInfo(root, 0); // 打印语法树信息
    }

    // 释放语法树节点的内存并返回成功
    delNode(root);          // 释放语法树节点的内存
    return 0;               // 返回成功码 0
}