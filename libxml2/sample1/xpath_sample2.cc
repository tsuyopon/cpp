/*
 * Parse RSS using xpath.
 * Improvement version of the xpath_sample1.cc. Check diff between xpath_sample1.cc.
 *
 */
#include <stdio.h>
#include <libxml/xmlreader.h>
#include <libxml/xpath.h>

enum Status {
    Success = 0,
    Fail    = -1,
};

//const char* REQUEST_API    = "http://messages.yahoo.co.jp/bbs?action=4&board=552019556&sid=552019556&tid=kcc08bc0obafb3u";
const char* REQUEST_API    = "http://rss.dailynews.yahoo.co.jp/fc/rss.xml";
const char* XPATH_ITEM     = "/rss//item/*/text()";
const char* XPATH_TITLE    = "/rss//item/title/text()";
const char* XPATH_PUB_DATE = "/rss//item/pubDate/text()";
    
int main(void) {

	// Read XML From REQUEST_API
	xmlDocPtr doc = xmlParseFile(REQUEST_API);
    if (!doc) return Fail;

    xmlXPathContextPtr ctx = xmlXPathNewContext(doc);
    if (!ctx) return Fail;
    
    xmlXPathObjectPtr xpobj = xmlXPathEvalExpression((xmlChar *)XPATH_ITEM, ctx);
    if (!xpobj) return Fail;

    xmlNodeSetPtr nodes = xpobj->nodesetval;
    int size = (nodes) ? nodes->nodeNr : 0;
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
    xmlCleanupParser();
    return Success;
}
