/* digraph.h
 * 1/17/20
 * logic circuit graph data struct
 * */

#ifndef digraph.h
#define digraph.h

typedef enum type{WIRE, NOT, OR, AND, NAND, XOR};
typedef struct point;
typedef struct node;
void traverse();
void paint();
#endif
