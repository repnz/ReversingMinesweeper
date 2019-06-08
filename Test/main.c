#include <stdio.h>

typedef struct _s {
	unsigned int a;
	unsigned int b;
} s;

void F(s x) {
}

int main() {
	F((s) { -1, -1 });

}