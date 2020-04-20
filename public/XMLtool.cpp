#include "XMLtool.h"

void XMLParse::clear()
{
    result=NULL;
    version="";
    tdata=NULL;
}

XMLParse::xml_t* XMLParse::get()
{
    return result;
}

string XMLParse::getv()
{
    return version;
}

void XMLParse::versionparse()
{
    parsewhitespace();
    if(*tdata!='<'||*tdata=='\0')
        return;
    else
    {  
        tdata++;
        if(*tdata=='?')
        {
            tdata++;
            while(*tdata!='?')
            {
                version+=*tdata;
                tdata++;
            }
            tdata++;
            tdata++;
        }
        else
        {
            tdata--;
        }
    }
}

XMLParse::xml_t* XMLParse::lableparse()
{
    xml_t* node;
    parsewhitespace();
    if(*tdata!='<'||*tdata=='\0')
        return NULL;
    else
    {  
        tdata++;
        node=new xml_t;
        while(*tdata!='>')
        {
            node->LabelName+=*tdata;
            tdata++;
        }
        tdata++;
        parsewhitespace();
        char* ctest=++tdata;
        tdata--;
        while(*tdata=='<'&&*(ctest)!='/')
        {
            xml_t *tnode;
            tnode=lableparse();
            if(tnode!=NULL)
                node->child.push_back(tnode);
            ctest=++tdata;
            tdata--;
        }
        while(*tdata!='<')
        {
            node->LabelValue+=*tdata;
            tdata++;
        }
        while(*tdata!='>')
            tdata++;
        tdata++;
    }
    return node;
}


void XMLParse::parsewhitespace()
{
    while (*tdata == ' ' || *tdata == '\t' || *tdata == '\n' || *tdata == '\r')
	    tdata++;
}

void XMLParse::parse(char *data)
{   
    clear();
    tdata=data;
    versionparse();
    result=lableparse();
    return;
}