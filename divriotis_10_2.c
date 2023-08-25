#include <stdio.h>
#define ADRESSE_RELATIVE_DE(s,c) (unsigned long)&(((s*)0)->c)

int main(void)
{
	unsigned long x;
	typedef struct 
    {
        char c; 
        char *pc;
        int i;
    } s;

	printf("structure présentée : \ntypedef struct\n{\n     char c;\n     char *pc;\n     int i; \n} s;\n");
	printf("\n \n");

    s v;
    printf("affichage des adresses relatives : \n\n");
	x= (unsigned long)&v.i - (unsigned long)&v;
	printf("champ int i / s(sans macro): %lu\n\n",x);
	
    x=ADRESSE_RELATIVE_DE(s,c);
	printf("champ char c / s: %lu\n\n",x);
    x=ADRESSE_RELATIVE_DE(s,pc);
	printf("champ char *pc / s: %lu\n\n",x);
    x=ADRESSE_RELATIVE_DE(s,i);
	printf("champ int i / s: %lu\n\n",x);


	return 0;
}
