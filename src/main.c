#include <stdio.h>

#include "boid.h"

void test(){
	LLBoid x = LLBoidStdConstr();

	vec2 testVec = {
		.x = 1,
		.y = 2
	};

	boid testBoid = {
		.postion = testVec,
		.rotation = testVec
	};

	LLBoidAppend(&x,testBoid);

	printf("1 == %i\n",LLBoidGetAt(&x,1).content.postion.x);

	testBoid.postion.x = 80;

	LLBoidSetAt(&x,1,testBoid);

	printf("80 == %i\n",LLBoidGetAt(&x,1).content.postion.x);

	LLBoidPop(&x,1);

	printf("1 == %i\n",LLBoidLen(&x));
}

int main(){
	//test();
	vec2 rotationVector = {
		.x = 20,
		.y = 20
	};

	vec2 positionVector = {
		.x = 1,
		.y = 2
	};

	printf("%i\n",normalVec2(positionVector).x);
	printf("%i\n",normalVec2(positionVector).y);
	return 0;
}
