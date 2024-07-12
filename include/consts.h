#ifndef OPENU_PROJECT_CONSTS_H
#define OPENU_PROJECT_CONSTS_H

#define MAX_LINE_LENGTH 80
#define OPCODES_COUNT 16
#define REGISTER_COUNT 8
#define INSTRUCTIONS_COUNT 4

/*
char* opcodes[] = {"mov","cmp","add","sub","lea","clr","not","inc","dec","jmp","bne","red","prn","jsr","rts","stop"};
char* instructions[] = {".data", ".string","entry","extern"};
char* registers[] = {"r0", "r1","r2","r3","r4","r5","r6","r7"};
*/

extern char* opcodes[];
extern char* instructions[];
extern char* registers[];
/* temp^ */



#endif //OPENU_PROJECT_CONSTS_H

