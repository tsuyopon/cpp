/*
 * Parse RSS Sample using XPath.
 *
 * (Reference)
 *     http://d.hatena.ne.jp/hakutoitoi/20090319/1237397160
 *
 */
#include <stdio.h>
#include <libxml/xmlreader.h>
#include <libxml/xpath.h>
#include <iostream>
using namespace std;

enum Status {
    Success = 0,
    Fail    = -1,
};

const char* RSSFILE    = "./rssparse.rss";
const char* XPATH_ITEM = "/rss/channel";
    
int main(void) {

	// Read XML From FILE
    xmlTextReaderPtr reader =  xmlNewTextReaderFilename(RSSFILE);
    if (!reader) return Fail;

    xmlTextReaderRead(reader);
    xmlTextReaderExpand(reader);
    xmlDocPtr doc = xmlTextReaderCurrentDoc(reader);
    if (!doc) return Fail;

    xmlXPathContextPtr ctx = xmlXPathNewContext(doc);
    if (!ctx) return Fail;
    
    xmlXPathObjectPtr xpobj = xmlXPathEvalExpression((xmlChar *)XPATH_ITEM, ctx);
    if (!xpobj) return Fail;

    xmlNodeSetPtr nodes = xpobj->nodesetval;
    int size = (nodes) ? nodes->nodeNr : 0;
    for (int i = 0; i < size; ++i) {
		cout << "######" << i << "start" << endl;
        if (!xmlXPathNodeSetIsEmpty(nodes)) {
            xmlNodePtr node = xmlXPathNodeSetItem(nodes, i);
			xmlNodePtr cur = node->xmlChildrenNode;
			while( cur != NULL){
				if( (!xmlStrcmp(cur->name, (const xmlChar*)"title") ) ){
					cout << "title:" << cur->children->content << endl;
				}
				if( (!xmlStrcmp(cur->name, (const xmlChar*)"description") ) ){
					cout << "description:" << cur->children->content << endl;
				}
				if( (!xmlStrcmp(cur->name, (const xmlChar*)"link") ) ){
					cout << "link:" << cur->children->content << endl;
				}
				if( (!xmlStrcmp(cur->name, (const xmlChar*)"lastBuildDate") ) ){
					cout << "lastBuildDate:" << cur->children->content << endl;
				}
				if( (!xmlStrcmp(cur->name, (const xmlChar*)"pubDate") ) ){
					cout << "pubDate:" << cur->children->content << endl;
				}
				if( (!xmlStrcmp(cur->name, (const xmlChar*)"ttl") ) ){
					cout << "ttl:" << cur->children->content << endl;
				}
				if( (!xmlStrcmp(cur->name, (const xmlChar*)"item") ) ){
					cout << "item:" << cur->children->content << endl;
				}
			cur = cur->next;
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
