#ifndef _PARSE_CONFIG_H_
#define _PARSE_CONFIG_H_

#include <map>
#include <string>

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
        map<int, string> map_tcp_protocol;
        map<int, string> map_udp_protocol;

    public:
        ParseConfig();

        void load_protocol_config();
};




#endif //_PARSE_CONFIG_H_

