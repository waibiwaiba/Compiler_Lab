sudo apt-get install flex bison

在语句 gcc main.c syntax.tab.c -lfl -ly -o parser 中，-lfl 和 -ly 参数的作用是链接 flex 和 bison 生成的词法分析器和语法分析器库。

具体来说：

-lfl 参数链接 flex 生成的词法分析器库 libfl。flex 生成的词法分析器需要使用 libfl 库中提供的一些函数，如 yywrap 函数等。
-ly 参数链接 bison 生成的语法分析器库 liby。bison 生成的语法分析器需要使用 liby 库中提供的一些函数，如 yyparse 函数等。
这些库通常已经预先编译好并包含在操作系统的标准库中，因此只需要使用 -lfl 和 -ly 参数来链接它们即可。

最终，-o parser 参数将生成的可执行文件命名为 parser。

- `flex lexical.l` 会生成 lex.yy.c
- `bison -v syntax.y` 会生成 syntax.output\syntax.tab.c
- `bison -d syntax.y` 会生成 syntax.tab.c\syntax.tab.h
- `gcc main.c lex.yy.c -lfl -o scanner` 会生成 scanner
- `./scanner test.cmm`
- `gcc main.c syntax.tab.c -lfl -ly -o parser` 生成parser
- `gcc main.c syntax.tab.c -lfl -o parser`

```bash
(base) lx120l020121@ubuntu:~/CODE/Compiler_Lab/CompilerLab/lab1/Code$ gcc main.c syntax.tab.c -lfl -o parser
syntax.tab.c: In function ‘yyparse’:
syntax.tab.c:2011:9: warning: implicit declaration of function ‘yyerror’; did you mean ‘yyerrok’? [-Wimplicit-function-declaration]
 2011 |         yyerror (yymsgp);
      |         ^~~~~~~
      |         yyerrok
syntax.y: At top level:
syntax.y:156:1: warning: return type defaults to ‘int’ [-Wimplicit-int]
  156 | yyerror(char* msg){
      | ^~~~~~~
```

在syntax.y文件里，把yyerror改为void类型，参数改为const char* msg，并在开头添加函数声明即可。如下所示：

```
%{
    #include<stdio.h>
    #include"node.h"
    ...
    void yyerror(const char* msg);
%}
...
%%
...
%%
void yyerror(const char* msg){
fprintf(stdout, "Error type B at line %d: %s.\n", yylineno, msg);
}
```

如果报错如下，去掉-ly参数编译即可。

```bash
(base) lx120l020121@ubuntu:~/CODE/Compiler_Lab/CompilerLab/lab1/Code$ gcc main.c syntax.tab.c -lfl -ly -o parser
/usr/bin/ld: cannot find -ly
collect2: error: ld returned 1 exit status
```

运行make时，将执行以下指令：

首先，make将查找默认目标并执行它。在这个Makefile中，没有指定默认目标，因此make将执行第一个非伪目标，也就是parser。

parser目标依赖于syntax目标和除了lex.yy.o之外的所有.o目标文件。因此，make将检查这些依赖项是否需要重新编译。如果需要重新编译，将执行相应的规则。在这种情况下，make将先执行lexical和syntax-c规则，然后编译所有需要重新编译的.o文件。

syntax目标依赖于syntax.tab.o文件，因此make将检查syntax.tab.o是否需要重新编译。如果需要重新编译，将执行相应的规则。在这种情况下，make将编译syntax.y文件并生成syntax.tab.c和syntax.tab.h文件，然后编译syntax.tab.o文件。

lexical目标依赖于lex.yy.o文件，因此make将检查lex.yy.o是否需要重新编译。如果需要重新编译，将执行相应的规则。在这种情况下，make将编译lexical.l文件并生成lex.yy.c文件，然后编译lex.yy.o文件。

当所有依赖项都编译完成后，make将链接所有.o文件以生成可执行文件parser。

因此，执行make将依次执行以下操作：

编译syntax.y文件并生成syntax.tab.c和syntax.tab.h文件。
编译lexical.l文件并生成lex.yy.c文件。
编译所有需要重新编译的.o文件。
链接所有.o文件以生成可执行文件parser。