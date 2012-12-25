/*
 * Parse RSS Sample using XPath.
 *
 * (Reference)
 *     http://d.hatena.ne.jp/hakutoitoi/20090319/1237397160
 *     http://wiki.livedoor.jp/koba24505/d/libxml2%A5%C1%A5%E5%A1%BC%A5%C8%A5%EA%A5%A2%A5%EB
 *
 */
#include <stdio.h>
#include <libxml/xmlreader.h>
#include <libxml/xpath.h>

enum Status {
    Success = 0,
    Fail    = -1,
};

const char* REQUEST_API    = "http://messages.yahoo.co.jp/bbs?action=4&board=552019556&sid=552019556&tid=kcc08bc0obafb3u";
const char* XPATH_ITEM     = "/rss//item/*/text()";
const char* XPATH_TITLE    = "/rss//item/title/text()";
const char* XPATH_PUB_DATE = "/rss//item/pubDate/text()";
    
int main(void) {

	// Read XML From REQUEST_API
    xmlTextReaderPtr reader =  xmlNewTextReaderFilename(REQUEST_API);
    if (!reader) return Fail;

    xmlTextReaderRead(reader);
    xmlTextReaderExpand(reader);
    xmlDocPtr doc = xmlTextReaderCurrentDoc(reader);
    if (!doc) return Fail;

    xmlXPathContextPtr ctx = xmlXPathNewContext(doc);
    if (!ctx) return Fail;
    
	// Application XPath Evaluation
    xmlXPathObjectPtr xpobj = xmlXPathEvalExpression((xmlChar *)XPATH_ITEM, ctx);
    if (!xpobj) return Fail;

    xmlNodeSetPtr nodes = xpobj->nodesetval;
    int size = (nodes) ? nodes->nodeNr : 0;     // node->nodeNr identifies count elements.
    for (int i = 0; i < size; ++i) {
        if (!xmlXPathNodeSetIsEmpty(nodes)) {
            xmlNodePtr node = xmlXPathNodeSetItem(nodes, i);
            if (node->content) {
                printf("%s => %s\n", node->parent->name, node->content);
            } else {
                printf("invalid node\n");
                return Fail;
            }
        }
    }

    xmlXPathFreeObject(xpobj);
    xmlXPathFreeContext(ctx);
    xmlFreeDoc(doc);
    xmlFreeTextReader(reader);
    xmlCleanupParser();
    return Success;
}
