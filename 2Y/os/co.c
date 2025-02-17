#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(){
    for(int i = 0 ; i < 4 ; i++){
        for(int j = 0 ; j < 1<<i ; j++){
            printf("%d", i+1);
            printf("\n");
        }
    }
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