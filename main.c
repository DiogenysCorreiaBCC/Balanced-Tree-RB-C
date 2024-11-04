#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

int main(int argc, char* argv[]) {
    Tree root;
    initialize(&root);
    int opt;

    while(1) {
		scanf("%d", &opt);

		switch(opt) {
				int value;
			
				case 1:
						scanf("%d", &value);
						insert(&root, value);
						break;
				case 2:
                        preOrder(root);
                        printf("\n");
						break;
                case 3:
						scanf("%d", &value);
						remov(&root, value);
                        break;
				case 99:
						exit(0);
		}
	}
}  










































































































