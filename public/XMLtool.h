//XMLtool.h
//XML生成器及解析器

#ifndef XMLTOOL_H
#define XMLTOOL_H
#include <vector>

Class XMLParser
{
    public:
        enum TYPE{VERSION,ANNOTATION,ELEMENT}
        struct xml_t
        {
            string LabelName;
            string LabelValue;
            TYPE type;
            vector<xml_t *> child; 
        } 
    private:
        int parsing(char *);
}

#endif