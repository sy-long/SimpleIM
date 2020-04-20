//XMLtool.h
//XML生成器及解析器

#ifndef XMLTOOL_H
#define XMLTOOL_H
#include <vector>
#include <string>
using namespace std;

class XMLParse
{
    public:
        struct xml_t
        {
            string LabelName; //标签名
            string LabelValue; //标签值
            vector<xml_t *> child;  //子标签
        };
    private:
        xml_t *result;
        string version; //版本值
        char *tdata;
    public:
        void parse(char *); //解析
        xml_t* get();
        string  getv();
    private:
        void clear();
        void parsewhitespace(); //处理空白字符
        xml_t* lableparse(); //实际解析
        void versionparse();
};

#endif