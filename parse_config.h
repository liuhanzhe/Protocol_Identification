#ifndef _PARSE_CONFIG_H_
#define _PARSE_CONFIG_H_

#include <map>
#include <string>
#include <iostream>
#include <sstream> 

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>



#define PROTOCOL_XML_PATH "protocol_config/protocol.xml"

using namespace xercesc;

using namespace std;



class ParseConfig
{
    private:
        XercesDOMParser *parser;
        map<int, string> map_tcp_protocol;
        map<int, string> map_udp_protocol;

        void load_main_config();
        DOMNode* find_child_node(DOMNode *n, char *nodename);
        int pchar_to_int(char*);
        int get_trans_type(string);

        static ParseConfig *parse_config;

    public:
        static ParseConfig* get_instance()
        {
            if(parse_config==NULL)
                parse_config = new(ParseConfig);
            return parse_config;
        }

        ParseConfig();
        void load_protocol_config();
        
};




#endif //_PARSE_CONFIG_H_

