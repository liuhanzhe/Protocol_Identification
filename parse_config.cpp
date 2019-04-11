#include "parse_config.h"
#include "log.h"

ParseConfig::ParseConfig()
{
    XMLPlatformUtils::Initialize();
    parser = new XercesDOMParser();parser->setValidationScheme(XercesDOMParser::Val_Always);
}

void ParseConfig::load_protocol_config()
{   
    
    parser->setDoNamespaces(true);
    ErrorHandler* errHandler = (ErrorHandler*) new HandlerBase();
    parser->setErrorHandler(errHandler);
    load_main_config();
    
}

int ParseConfig::pchar_to_int(char* c)
{
    stringstream ss;
    int result;
    ss << c;
    ss >> result;
    return result;
}

void ParseConfig::load_main_config()
{
    parser->parse(PROTOCOL_XML_PATH);
    DOMDocument *doc = parser->getDocument();
    DOMElement *root = doc->getDocumentElement();
    DOMNode *DN=root;
    for (DN = DN->getFirstChild(); DN != 0;DN = DN->getNextSibling())
    {
        if (DN->getNodeType() == DOMNode::ELEMENT_NODE)
        {            
            if (XMLString::compareString(DN->getNodeName(),XMLString::transcode("protocol")) == 0){   
                DOMNode *trans_type = find_child_node(DN, (char*)"transport_type");                          
                DOMNode *node_port = find_child_node(DN, (char*)"port");
                string protocol_name = XMLString::transcode(DN->getAttributes()->getNamedItem(XMLString::transcode("name"))->getNodeValue());
                string protocol_trans_type = XMLString::transcode(trans_type->getTextContent());
                int protocol_port = pchar_to_int(XMLString::transcode(node_port->getTextContent()));
                #ifdef _DEBUG_
                    LOG_INFO(LOG_LEVEL_INFO, "protocol name: %s", protocol_name.c_str());
                    LOG_INFO(LOG_LEVEL_INFO, "protocol trans type: %s", protocol_trans_type.c_str());
                    LOG_INFO(LOG_LEVEL_INFO, "protocol port: %d", protocol_port);
                    //LOG(LOG_INFO, "protocol name: %s", protocol_name.c_str());
                    //LOG(LOG_INFO, "protocol trans type: %s", protocol_trans_type.c_str());
                    //LOG(LOG_INFO, "protocol port: %d", protocol_port);
                #endif
                if(protocol_trans_type == "tcp")
                    map_tcp_protocol.insert(pair<int,string>(protocol_port, protocol_name));
                else if(protocol_trans_type == "udp")
                    map_udp_protocol.insert(pair<int,string>(protocol_port, protocol_name));
            }
        }
    }
}


DOMNode* ParseConfig::find_child_node(DOMNode *n, char *nodename)
 {
     try
     {
         for (DOMNode *child = n->getFirstChild(); child != 0; child = child->getNextSibling())
         {
             if (child->getNodeType() == DOMNode::ELEMENT_NODE  && XMLString::compareString(child->getNodeName(), XMLString::transcode(nodename)) == 0)
             {
                 return child;
             }
         }
     }
     catch (const XMLException& toCatch)
     {
         char* message = XMLString::transcode(toCatch.getMessage());
         cout << "Exception message is: \n"
             << message << "\n";
         XMLString::release(&message);
     }
     return 0;
 }

 string ParseConfig::find_protocol_by_port(int trans_type, int sport, int dport)
 {
    map<int, string> map_protocol;
    if(trans_type == 0)
    {
        map_protocol = map_tcp_protocol;
    }
    else if (trans_type == 1)
    {
        map_protocol = map_udp_protocol;
    }   
    
    string protocol_name = "";
    map<int, string>::iterator siter = map_protocol.find(sport);
    map<int, string>::iterator piter = map_protocol.find(dport);
    if(siter != map_protocol.end())
    {
        protocol_name = siter->second;
    }
    else if(piter != map_protocol.end())
    {
        protocol_name = piter->second;
    }
    return protocol_name;
 }
