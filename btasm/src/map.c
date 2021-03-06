//map.c
//Simple map for variables
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"

/*
int main()
{
    map m = create_map();
    int a = insert(m, "foo");
    a = insert(m, "foo");
    a = insert(m, "bar");
    a = lookup(m, "baz");
    a = lookup(m, "foo");
    return 0;   
}
*/

map create_map()
{
    return calloc(MAXLEN, sizeof(char *));
}


void destroy_map(map m)
{
    char *p = m[0];
    while (p) free(p++);
    free(m);
}


int insert_map(map m, char *s)
{
    if (s==NULL)
        return -1;
    
    int i=0;
    for(i=0;i<MAXLEN;i++) {
        if (m[i] == NULL) {
            m[i] = strdup(s);
            return i;
        }

        if (!strcmp(m[i], s)) {
            return -1;
        }
    }
}

int lookup_map(map m, char *s) 
{
    if (s==NULL)
        return -1;
    
    int i=0;
    for(i=0;i<MAXLEN;i++) {
        if (m[i] == NULL)
            return -1;
        if (!strcmp(m[i], s))
            return i;
    }
}
    
void dump_map(map m) 
{
    int i;
    for (i=0; i<MAXLEN; i++) {
        if (m[i] == NULL)
            break;
        printf("%-20s|%-5d\n", m[i], i);
    }
}

void reverse_map(map m)
{
    int i;
    char *t;
    
    //Find number of elems
    for (i=0; i<MAXLEN; i++) {
        if (m[i] == NULL) {
            i--; break;
        }
    }
    int len = i;

    for (i=0; i<(len+1)/2;i++) {
        t = m[i];
        m[i] = m[len-i];
        m[len-i] = t;
    }
}
