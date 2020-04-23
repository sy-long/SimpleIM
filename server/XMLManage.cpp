#include "XMLManage.h"

 void XMLManage::dataDispose(char *data)
 {
    XMLParse readparse;
    XMLParse::xml_t *xmltp;
    readparse.parse(data);
    xmltp=readparse.get();
    if(xmltp->LabelName=="iq")
    {
        if(xmltp->child[0]->LabelValue=="set")
        {
            if(xmltp->child[1]->LabelValue=="registered")
            {
                oper.registered(xmltp);
            }
        }
    }
 }