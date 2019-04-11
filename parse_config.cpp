#include "parse_config.h"

ParseConfig::ParseConfig()
{
}

void ParseConfig::load_protocol_config()
{
    XMLPlatformUtils::Initialize();
    XercesDOMParser *parser = new XercesDOMParser();parser->setValidationScheme(XercesDOMParser::Val_Always);
    parser->setDoNamespaces(true);
    ErrorHandler* errHandler = (ErrorHandler*) new HandlerBase();
    parser->setErrorHandler(errHandler);

    parser->parse(PROTOCOL_XML_PATH);
}
