#include <def.h>

static int a1 (int Ch) {
	printf("TEST a1 --> %d\n",Ch);
	return (0);
}

static int a2 (int Ch) {
	printf("TEST a2 --> %d\n",Ch);
	return (0);
}

static int (*fps[]) (int) = {
		[0] = a1,
		[1] = a2
};

int testing (int a, int b) {
	return fps[b] (a);
}
