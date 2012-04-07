#ifndef JM_MAP_H
#define JM_MAP_H

//map.h
//J. MacMillan - Good Friday 2012

typedef char** map;

map create_map();
void destroy_map(map m);
int insert_map(map m, char *s);
int lookup_map(map m, char *s);
#define MAXLEN 256

#endif  
