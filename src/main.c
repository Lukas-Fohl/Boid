
#include <stdio.h>

#include "boid.h"

#define BOID_AMOUNT 50

void LLBtest(){
	if(LLBoidStdConstr().nextLLBoid == NULL && LLBoidStdConstr().content.postion.x == 0){
		printf("\t \033[32m [Test] LLBoidStdConstr passed ✓ \033[0m \n");
	}else{
		printf("\t \033[31m [Test] LLBoidStdConstr failed ✗ \033[0m \n");
	}

	LLBoid LLBTestVar = LLBoidStdConstr();
	LLBoidAppend(&LLBTestVar,boidStdConstr());

	if(LLBoidGetAt(&LLBTestVar,1).nextLLBoid == NULL && LLBoidGetAt(&LLBTestVar,1).content.postion.x == 0){
		printf("\t \033[32m [Test] LLBoidAppend passed ✓ \033[0m \n");
	}else{
		printf("\t \033[31m [Test] LLBoidAppend failed ✗ \033[0m \n");
	}

	boid testBoidVar = boidStdConstr();
	testBoidVar.postion.x = 5;
	LLBoidSetAt(&LLBTestVar,1,testBoidVar);
	if(LLBoidGetAt(&LLBTestVar,1).nextLLBoid == NULL && LLBoidGetAt(&LLBTestVar,1).content.postion.x == 5){
		printf("\t \033[32m [Test] LLBoidGetAt passed ✓ \033[0m \n");
	}else{
		printf("\t \033[31m [Test] LLBoidGetAt failed ✗ \033[0m \n");
	}

	testBoidVar.postion.y = 20;
	LLBoidSetAt(&LLBTestVar,1,testBoidVar);
	if(LLBoidGetAt(&LLBTestVar,1).content.postion.y == 20){
		printf("\t \033[32m [Test] LLBoidSetAt passed ✓ \033[0m \n");
	}else{
		printf("\t \033[31m [Test] LLBoidSetAt failed ✗ \033[0m \n");
	}

	LLBoidPop(&LLBTestVar,1);
	if(LLBTestVar.nextLLBoid == NULL){
		printf("\t \033[32m [Test] LLBoidPop passed ✓ \033[0m \n");
	}else{
		printf("\t \033[31m [Test] LLBoidPop failed ✗ \033[0m \n");
	}

	if(LLBoidLen(&LLBTestVar) == 1){
		printf("\t \033[32m [Test] LLBoidLen passed ✓ \033[0m \n");
	}else{
		printf("\t \033[31m [Test] LLBoidLen failed ✗ \033[0m \n");
	}
}

LLBoid makeLLBoid(){
	//create boidList
	vec2 rotationVector = {
		.x = 20,
		.y = 20
	};
	vec2 positionVector = {
		.x = 1,
		.y = 2
	};
	LLBoid reVal = LLBoidStdConstr();

	for(int i = 0; i < BOID_AMOUNT-1; i++){
		boid *x = (boid*)malloc(sizeof(struct boid));
		x->rotation = rotationVector;
		x->postion = positionVector;
		x->postion.x = i+1;
		LLBoidAppend(&reVal,*x);
	}
	return reVal;
}

int main(){
	LLBtest();
	LLBoid list = makeLLBoid();
	//LLBoidPrint(&list, true, true);

	LLBoid* temp = &list;
	while(1){
		//vec2 tempVec = nextPosition(&list,temp->content);
		//temp->content.postion = tempVec;
		if(temp->nextLLBoid == NULL){
			break;
		}
		temp = temp->nextLLBoid;
	}

	return 0;
}
