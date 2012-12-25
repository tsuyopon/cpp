/*
 * tree walk program.
 *
 * See http://d.hatena.ne.jp/l1o0/20110201/1296564519
 *
 */
#include <stdio.h>
#include <string.h>
#include <libxml/tree.h>
#include <libxml/parser.h>

void trim(char *str)
{
    int i;

    for (i = strlen(str) - 1; 0 <= i; i--) {
        if ((str[i] == '\r') ||
            (str[i] == '\n') ||
            (str[i] == ' ')) {
            str[i] = '\0';
        }
        else {
            break;
        }
    }
}

void walk(xmlNodePtr node, int depth)
{
    char     buf[64];
    char     content[128];
    xmlNode *cur_node = NULL;
    int i = 0;

    /* Indent space */
    for (i = 0; i < (depth * 2); i++) {
        buf[i] = ' ';
    }
    buf[i] = '\0';

    for (cur_node = node; cur_node; cur_node = cur_node->next) {
        printf("%s", buf);

        /* Type */
        printf("type(%d):", cur_node->type);
        switch (cur_node->type) {
            case XML_ELEMENT_NODE:
                printf("Node, ");
                break;
            case XML_ATTRIBUTE_NODE:
                printf("Attribute, ");
                break;
            case XML_TEXT_NODE:
                printf("Text, ");
                break;
            default:
                printf("Other, ");
                break;
        }

        /* Name of node, or entity */
        printf("name:%s, ", cur_node->name);

        /* Content */
        if (NULL == cur_node->content) {
            printf("content:(null)");
        }
        else {
            strcpy(content, (char *)cur_node->content);
            trim(content);
            printf("content:%s", content);
        }
        printf("\n");

        walk(cur_node->children, depth + 1);
    }
}

int main(int argc, char **argv)
{
    xmlDocPtr  doc;
    xmlNodePtr root_element = NULL;
    const char      *input_file;
    int        ret;

    input_file = "treewalk1.xml";

    LIBXML_TEST_VERSION;

    /* Read document */
    doc = xmlReadFile(input_file, NULL, 0);
    if (doc == NULL) {
        fprintf(stderr, "Failed to parse %s\n", input_file);
        return false;
    }

    /*Get the root element node */
    root_element = xmlDocGetRootElement(doc);

    /* Walk child */
    walk(root_element, 0);

    /* Free document */
    xmlFreeDoc(doc);

    xmlCleanupParser();

    return 0;
}
