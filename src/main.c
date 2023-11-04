#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#include "boid.h"

#define BOID_AMOUNT 1000

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
		x->rotation.x = i+1;
		x->rotation.y = i/2+1;
		LLBoidAppend(&reVal,*x);
	}
	return reVal;
}

int mainLoopTime(){
	LLBoid list = makeLLBoid();

	LLBoid* temp = &list;

	struct timeval stop, start;
	gettimeofday(&start, NULL);
	for(int i = 0; i < 24; i++){
		while(1){
			temp->content = nextPosition(&list,temp->content);
			if(temp->nextLLBoid == NULL){
				break;
			}
			temp = temp->nextLLBoid;
		}
		temp = &list;
	}

	for(int i = 0; i < BOID_AMOUNT; i++){
		//LLBoidPop(&list,i);
	}

	gettimeofday(&stop, NULL);
	return((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec)/1000; 
}

void speedTest(){
	int samples = 200;
	int sum = 0;
	int printCounter = 0;

	printf(".");
	fflush(stdout);

	for(int i = 0; i < samples; i++){

		if((int)(((double)(((double)i/(double)samples)*100.0))/10.0) > printCounter){
			printf(".");
			fflush(stdout);
			printCounter++;
		}

		sum += mainLoopTime();
	}

	printf("\nit took %i ms\n", sum/samples); 
}

void mainLoop(){
	LLBoid list = makeLLBoid();

	LLBoid* temp = &list;

	while(1){
		temp->content = nextPosition(&list,temp->content);

		if(temp->nextLLBoid == NULL){
			break;
		}

		temp = temp->nextLLBoid;
	}

	for(int i = 0; i < BOID_AMOUNT; i++){
		//LLBoidPop(&list,i);
	}
}

int main(){
	//speedTest();
	//LLBtest();
	mainLoop();
	return 0;
}