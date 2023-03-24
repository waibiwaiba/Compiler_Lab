#ifndef NODE_H
#define NODE_H

// #include <unistd.h>
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "enum.h"

// #define NAME_LENGTH 32
// #define VAL_LENGTH 64

#define TRUE 1
#define FALSE 0

// typedef uint_32 bool;

// node type declared
typedef struct node {
    int lineNo;  //  node in which line
    //   int depth;   //  node depth, for count white space for print
    NodeType type;  // node type
    char* name;     //  node name
    char* val;      //  node value

    struct node* child;  //  non-terminals node first child node
    struct node* next;   //  non-terminals node next brother node

} Node;

typedef Node* pNode;

static inline pNode newNode(int lineNo, NodeType type, char* name, int argc, ...)
{
    pNode curNode = NULL;
    int nameLength = strlen(name) + 1;

    curNode = (pNode)malloc(sizeof(Node));  // 为节点分配内存空间

    assert(curNode != NULL);  // 检查内存是否分配成功

    curNode->name = (char*)malloc(sizeof(char) * nameLength);  // 为节点的名称分配内存空间

    assert(curNode->name != NULL);  // 检查内存是否分配成功

    curNode->lineNo = lineNo;  // 设置节点的行号
    curNode->type = type;  // 设置节点的类型
    strncpy(curNode->name, name, nameLength);  // 复制节点名称

    va_list vaList;
    va_start(vaList, argc);  // 初始化可变参数列表

    pNode tempNode = va_arg(vaList, pNode);  // 获取第一个参数

    curNode->child = tempNode;  // 将第一个参数设置为节点的子节点

    for (int i = 1; i < argc; i++) {  // 遍历剩余的参数
        tempNode->next = va_arg(vaList, pNode);  // 获取下一个参数，并将其设置为当前节点的兄弟节点
        if (tempNode->next != NULL) {  // 如果兄弟节点不为空
            tempNode = tempNode->next;  // 将当前节点设置为兄弟节点，继续遍历
        }
    }

    va_end(vaList);  // 结束可变参数列表

    return curNode;  // 返回新创建的节点
}

// 定义一个静态内联函数newTokenNode
// 参数lineNo: 标记所在的行号
// 参数type: 标记的节点类型
// 参数tokenName: 标记的名称
// 参数tokenText: 标记的文本
static inline pNode newTokenNode(int lineNo, NodeType type, char* tokenName, char* tokenText) {
    // 分配内存来创建一个新节点
    pNode tokenNode = (pNode)malloc(sizeof(Node));
    // 计算标记名称和标记文本的长度
    int nameLength = strlen(tokenName) + 1;
    int textLength = strlen(tokenText) + 1;

    // 确认节点内存分配成功
    assert(tokenNode != NULL);

    // 设置节点的行号和类型
    tokenNode->lineNo = lineNo;
    tokenNode->type = type;

    // 分配内存来存储标记名称和标记文本
    tokenNode->name = (char*)malloc(sizeof(char) * nameLength);
    tokenNode->val = (char*)malloc(sizeof(char) * textLength);

    // 确认标记名称和标记文本内存分配成功
    assert(tokenNode->name != NULL);
    assert(tokenNode->val != NULL);

    // 复制标记名称和标记文本到节点中
    strncpy(tokenNode->name, tokenName, nameLength);
    strncpy(tokenNode->val, tokenText, textLength);

    // 设置节点的子节点和兄弟节点为NULL
    tokenNode->child = NULL;
    tokenNode->next = NULL;

    // 返回新节点的指针
    return tokenNode;
}

// 定义一个静态内联函数delNode，用于删除节点及其子节点
// 参数node：要删除的节点的指针
static inline void delNode(pNode node) {
    // 如果节点为空，则直接返回
    if (node == NULL) return;

    // 递归删除节点的子节点
    while (node->child != NULL) {
        pNode temp = node->child;
        node->child = node->child->next;
        delNode(temp);
    }

    // 释放节点的名称和值所占的内存
    free(node->name);
    free(node->val);

    // 释放节点所占的内存
    free(node);

    // 将节点的指针设置为NULL，以避免出现野指针
    node->name = NULL;
    node->val = NULL;
    node = NULL;
}

// 定义一个静态内联函数printTreeInfo
// 参数curNode: 当前节点的指针
// 参数height: 当前节点在树中的深度
static inline void printTreeInfo(pNode curNode, int height) {
    // 如果当前节点为空，则直接返回
    if (curNode == NULL) {
        return;
    }

    // 打印当前节点在树中的深度
    for (int i = 0; i < height; i++) {
        printf("  ");
    }

    // 根据节点的类型打印节点的名称和值
    printf("%s", curNode->name);
    if (curNode->type == NOT_A_TOKEN) {
        printf(" (%d)", curNode->lineNo);
    } else if (curNode->type == TOKEN_TYPE || curNode->type == TOKEN_ID || curNode->type == TOKEN_INT) {
        printf(": %s", curNode->val);
    } else if (curNode->type == TOKEN_FLOAT) {
        printf(": %lf", atof(curNode->val));
    }

    // 换行
    printf("\n");

    // 递归打印当前节点的子节点和兄弟节点
    printTreeInfo(curNode->child, height + 1);
    printTreeInfo(curNode->next, height);
}

#endif