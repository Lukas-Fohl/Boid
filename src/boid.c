#include <stdlib.h>
#include <memory.h>
#include <math.h>

#define VECTOR_LENGTH 20

typedef struct vec2{
	int x,y;
}vec2;

typedef struct boid{
	vec2 postion, rotation;
}boid;

typedef struct LLBoid{
	boid content;
	struct LLBoid* nextLLBoid;
}LLBoid;
//[x]
boid boidStdConstr(){
	vec2 tempVec2 = {
		.x = 0,
		.y = 0
	};
	boid tempBoid = {
		.postion = tempVec2,
		.rotation = tempVec2
	};
	return tempBoid;
}
//[x]
boid boidConstr(vec2 postionInput, vec2 rotationInput){
	boid tempBoid = {
		.postion = postionInput,
		.rotation = rotationInput
	};
	return tempBoid;
}
//[x]
LLBoid LLBoidStdConstr(){
	LLBoid temp;
	vec2 tempVec2 = {
		.x = 0,
		.y = 0
	};
	boid tempBoid = {
		.postion = tempVec2,
		.rotation = tempVec2
	};
	temp.nextLLBoid = NULL;
	return temp;
}
//[x]
LLBoid LLBoidConstr(boid boidInput){
	LLBoid temp;
	temp.content = boidInput;
	temp.nextLLBoid = NULL;
	return temp;
}
//[x]
void LLBoidAppend(LLBoid* self, boid item){
	LLBoid* temp = self;
	int counter = 0;
	//find last element
	while(temp->nextLLBoid != NULL){
		counter++;
		temp = self->nextLLBoid;
	}
	//set next-ptr to new LLBoid
	//set content of new boid to $item
	LLBoid* boidItem = (LLBoid*)malloc(sizeof(LLBoid));
	*boidItem = LLBoidConstr(item);
	LLBoid* LLBoidTemp = boidItem;
	temp->nextLLBoid = LLBoidTemp;
	return;
}
//[x]
LLBoid LLBoidGetAt(LLBoid* self, int index){
	LLBoid* temp = self;
	int counter = 0;
	while(temp->nextLLBoid != NULL){
		if(counter == index){
			break;
		}
		counter++;
		temp = self->nextLLBoid;
	}
	//find last element
	//iter list return if i = $index
	return *temp;
}
//[x]
void LLBoidPop(LLBoid* self, int index){
	if(index < 1 || self->nextLLBoid == NULL){
		return;
	}else if(index == 0 && self->nextLLBoid != NULL){
		self = self->nextLLBoid;
		free(self);
		return;
	}

	//find index
	//change pointer from last to pointer of index-element
	//free(index-element)

	LLBoid* temp = self;
	int counter = 0;
	while(temp->nextLLBoid != NULL){
		if(counter == (index-1)){
			temp->nextLLBoid = temp->nextLLBoid->nextLLBoid;
			free(temp->nextLLBoid);
			return;
		}
		counter++;
		temp = self->nextLLBoid;
	}
	//if last item = item to change - not do while if list len = 1

	return;
}
//[x]
void LLBoidSetAt(LLBoid* self, int index, boid item){
	//find element @ index --> change content to $item
	LLBoid* temp = self;
	int counter = 0;
	while(temp->nextLLBoid != NULL){
		if(counter == index){
			self->content = item;
			return;
			//break;
		}
		counter++;
		temp = self->nextLLBoid;
	}
	//if last item = item to change - not do while if list len = 1
	temp->content = item;
	return;
}
//[x]
int LLBoidLen(LLBoid* self){
	//iter list --> when pointer == null return i
	LLBoid* temp = self;
	int counter = 1; //get real length
	while(temp->nextLLBoid != NULL){
		counter++;
		temp = self->nextLLBoid;
	}
	return counter;
}
//[x]
vec2 normalVec2(vec2 input){
	/*
		x**2 + y**2 = VECTOR_LENGTH**2 -> VECTOR_LENGTH = sqrt(x**2 + y**2)
		ratio * y = x

		-->

		VECTOR_LENGTH = sqrt((ratio*y)**2 + y**2)	| ()**2

		VECTOR_LENGTH**2 = (ratio*y)**2 + y**2		| /

		VECTOR_LENGTH**2 = y**2 * (ratio**2 + 1)	| /y**2

		VECTOR_LENGTH**2 / y**2 = (ratio**2 +1)		| /VECTOR_LENGTH**2

		y**2 = VECTOR_LENGTH**2 / (ratio**2 +1)		| sqrt()

		y = sqrt(VECTOR_LENGTH**2 / (ratio**2 +1))

		-->

		x = ratio * y
	*/
	double ratio = (double)input.x / (double)input.y;

	double vecPow2 = pow(
		(double)VECTOR_LENGTH,
		(double)2
	);

	double ratioPow2 = pow(
		(double)ratio,
		(double)2
	);

	double k = sqrt(
		(double)vecPow2 / ((double)ratioPow2 + (double)1)
	);

	double x = (double)ratio * (double)k;

	double y = (double)x / (double)ratio;

	vec2 returnValue = {
		.x = (int)round(x),
		.y = (int)round(y)
	};
	return returnValue;
}
//[x]
vec2 avgRotFromLLBoid(LLBoid *self){
	LLBoid* temp = self;
	int counter = 1;
	vec2 sumOfRot = {
		.x = 0,
		.y = 0
	};

	while(temp->nextLLBoid != NULL){
		counter++;
		sumOfRot.x += self->content.rotation.x;
		sumOfRot.y += self->content.rotation.y;
		temp = self->nextLLBoid;
	}

	vec2 returnValue = {
		.x = sumOfRot.x/counter,
		.y = sumOfRot.y/counter
	};
	return returnValue;
}
//[x]
vec2 avgPosFromLLBoid(LLBoid *self){
	LLBoid* temp = self;
	int counter = 1;
	vec2 sumOfPos = {
		.x = 0,
		.y = 0
	};

	while(temp->nextLLBoid != NULL){
		counter++;
		sumOfPos.x += self->content.postion.x;
		sumOfPos.y += self->content.postion.y;
		temp = self->nextLLBoid;
	}

	vec2 returnValue = {
		.x = sumOfPos.x/counter,
		.y = sumOfPos.y/counter
	};
	return returnValue;
}