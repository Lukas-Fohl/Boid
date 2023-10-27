#include <stdio.h>

#include "boid.h"

#define BOID_AMOUNT 50

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

	LLBoid n = LLBoidStdConstr();

	for(int i = 0; i < BOID_AMOUNT; i++){
		if(i == 48){
			rotationVector.x = 5;
		}else{
			rotationVector.x = 20;
		}
		boid *x = (boid*)malloc(sizeof(struct boid));
		x->rotation = rotationVector;
		x->postion = positionVector;
		LLBoidAppend(&n,*x);
	}

	//LLBoidPop(&n,0);

	LLBoidPrint(&n);

	//LLBoidLen(&n);
	//printf("%i\n",LLBoidLen(&n));

	return 0;
}
