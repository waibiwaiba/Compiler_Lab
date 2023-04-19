代码来自：https://github.com/UnableToCode/CompilerLab

我修改了一点点，使代码能在我机器上正常运行。

Lab1:
- 去除了编译时的`-ly`选项
- 修改了`yyerror`函数，添加了声明，使得编译不会报`warning`
- `make`：编译
- `make test`：测试
- `make clean`：清除编译、测试生成的文件

Lab2:
- 修复了源代码运行测试用例`s13.cmm`时出现的`free(): double free detected in tcache 2 Aborted (core dumped)`的错误
- 添加了实验指导书上的17个必做测试用例
- `make`
- `make test`
- `make print`：将所有的测试用例及其输出重定向至一个文件中
- `make clean`