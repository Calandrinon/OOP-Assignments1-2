/*Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <string.h>
int main() {
    char str[200];

    while (1) {
        scanf("%s", str);

        if (!strcmp(str, "exit"))
            break;

        printf("%s\n", str);

    }

    return 0;
}
