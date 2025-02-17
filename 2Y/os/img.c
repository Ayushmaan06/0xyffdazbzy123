#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(){
    printf("1\n");
    fork();
    printf("2\n");
    fork();
    printf("3\n");
    fork();
    printf("4\n");
    return 0;
}
/*
P (prints "1\n2\n3\n4\n")
├── C1 (prints "2\n3\n4\n")
│   ├── C1.1 (prints "3\n4\n")
│   │   ├── C1.1.1 (prints "4\n")
│   │   └── C1.1.2 (prints "4\n")
│   └── C1.2 (prints "3\n4\n")
│       ├── C1.2.1 (prints "4\n")
│       └── C1.2.2 (prints "4\n")
├── C2 (prints "2\n3\n4\n")
│   ├── C2.1 (prints "3\n4\n")
│   │   ├── C2.1.1 (prints "4\n")
│   │   └── C2.1.2 (prints "4\n")
│   └── C2.2 (prints "3\n4\n")
│       ├── C2.2.1 (prints "4\n")
│       └── C2.2.2 (prints "4\n")

1
2
2
3
3
3
3

*/