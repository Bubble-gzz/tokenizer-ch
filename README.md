# tokenizer-ch
这是一个基于hash字典树的高效中文分词工具(实际上支持所有utf-8编码的字符)
## 使用方法
### 第一步
将词库放到`vocab.txt`中
格式为每行一词，如下:
```
一心一意
一个
专心致志
三心二意
一天
```
### 第二步
将待分词的文本放到`text.txt`中
### 第三步
编译运行`main.cpp`
### 第四步
在`result.txt`中查看分词结果

## 相关库使用说明（**如果只是使用分词功能可以忽略此部分说明**）
### utf-8.h
这个库是用来处理utf-8编码的文件的，众所周知，中文字符无法直接读入存放到字符串中处理，因此写了这个库，将utf-8字符的编码以int形式存放为一个个独立元素。
使用方法如下：
#### 第一步
直接用`fgets`读入utf-8编码的内容存放到字符串`char *buff`中，此时由于很多字符占了超过1个字节，因此无法直接处理`buff`中的内容
#### 第二步
包含下面两个接口:

`int decode(char *buff,int *res);`

将保存了字符串的`buff`中的内容以字为单位存放到`res`中，此时`res`中每个元素都是一个完整utf-8字符的二进制编码，函数返回值为`res`的长度

`void encode(FILE *fout, const int *res, int res_L, int mode = CHARFORM);`

将`res`的[0,resL)部分的编码所代表的utf-8字符输出到`fout`中,默认输出字符,如果`mode = INTFORM`,则输出utf-8编码数值

### trieCH.h
这个库封装了支持utf-8字符集的字典树，字典树的结点为trieNode类：
```c++
namespace trieCH {
    struct trieNode{  //trieNode类，表示字典树的一个节点
        int cnt, code, isEnd, hashCreated, next;
        int hashN, backupPoint;
        trieNode* children;
        trieNode();
        trieNode* builtin_getChild(int code, int isBuild, int endFlag = 0);
        trieNode* getChild(int code); //获取对应utf-8字符编码为code的子节点的地址
    };
}
```
调用接口如下：

`trieNode* trieCH::buildTrie(FILE *fin)`

从`fin`中读入词库，生成字典树，返回根节点的指针

`trieNode* trieCH::trieNode::getChild(int code);` 

获取对应utf-8字符编码为code的子节点的地址


