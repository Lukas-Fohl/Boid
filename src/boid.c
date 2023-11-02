#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <stdbool.h>

#define VECTOR_LENGTH 10

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

boid boidConstr(vec2 postionInput, vec2 rotationInput){
	boid tempBoid = {
		.postion = postionInput,
		.rotation = rotationInput
	};
	return tempBoid;
}

LLBoid LLBoidStdConstr(){
	//TODO malloc
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

LLBoid LLBoidConstr(boid boidInput){
	//TODO malloc
	LLBoid temp;
	temp.content = boidInput;
	temp.nextLLBoid = NULL;
	return temp;
}

void LLBoidAppend(LLBoid* self, boid item){
	LLBoid* temp = self;
	//find last element
	while(1){
		if(temp->nextLLBoid != NULL){
			temp = temp->nextLLBoid;
		}else{
			break;
		}
	}
	//set next-ptr to new LLBoid
	//set content of new boid to $item
	LLBoid* boidItem = (LLBoid*)malloc(sizeof(LLBoid));
	*boidItem = LLBoidConstr(item);
	//LLBoid* LLBoidTemp = boidItem;
	//temp->nextLLBoid = LLBoidTemp;
	temp->nextLLBoid = boidItem;
	return;
}

LLBoid LLBoidGetAt(LLBoid* self, int index){
	LLBoid* temp = self;
	int counter = 0;
	while(1){
		if(counter == index){
			break;
		}
		counter++;
		if(temp->nextLLBoid == NULL){
			temp->content.postion.x = 0;
			temp->content.postion.y = 0;

			temp->content.rotation.x = 0;
			temp->content.rotation.y = 0;
			break;
		}
		temp = temp->nextLLBoid;
	}
	//find last element
	//iter list return if i = $index
	return *temp;
}

void LLBoidPop(LLBoid* self, int index){
	if(index == 0 && self->nextLLBoid != NULL){
		//LLBoid* temp = self;
		*self = *self->nextLLBoid;
		//free(temp);
		return;
	}else if(index < 1 || self->nextLLBoid == NULL){
		return;
	}

	LLBoid* temp = self;
	int counter = 0;
	while(1){
		if(counter == index-1){
			LLBoid *tempPointer = temp->nextLLBoid;
			if(temp->nextLLBoid == NULL){
				return;
			}
			temp->nextLLBoid = temp->nextLLBoid->nextLLBoid;
			free(tempPointer);
			return;
		}
		if(temp->nextLLBoid == NULL){
			break;
		}
		temp = temp->nextLLBoid;
		counter++;
	}

	return;
}

void LLBoidSetAt(LLBoid* self, int index, boid item){
	//find element @ index --> change content to $item
	LLBoid* temp = self;
	int counter = 0;
	while(1){
		if(counter == index){
			temp->content = item;
			return;
			//break;
		}

		counter++;
		if(temp->nextLLBoid == NULL){
			break;
		}
		temp = temp->nextLLBoid;
	}
	//if last item = item to change - not do while if list len = 1
	//temp->content = item;
	return;
}

int LLBoidLen(LLBoid* self){
	//iter list --> when pointer == null return i
	LLBoid* temp = self;
	int counter = 0; //get real length
	while(1){
		counter++;
		if(temp->nextLLBoid == NULL){
			break;
		}
		temp = temp->nextLLBoid;
	}
	return counter;
}

void LLBoidPrint(LLBoid *selfList, bool printPosition, bool printRotation){
	LLBoid* temp = selfList;
	int counter = 0;
	while(1){
		printf("%i: \n",counter);
		if(printRotation){
			printf("\trotation:\n");
			printf("\t\tx::%i \t | \ty::%i\n",temp->content.rotation.x,temp->content.rotation.y);
			printf("\n");
		}
		if(printPosition){
			printf("\tposition:\n");
			printf("\t\tx::%i \t | \ty::%i\n",temp->content.postion.x,temp->content.postion.y);
		}

		if(temp->nextLLBoid == NULL){
			break;
		}
		temp = temp->nextLLBoid;
		counter++;
	};
}

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

vec2 avgRotFromLLBoid(LLBoid *self){
	LLBoid* temp = self;
	int counter = 1;
	vec2 sumOfRot = {
		.x = 0,
		.y = 0
	};

	while(1){
		counter++;
		sumOfRot.x += self->content.rotation.x;
		sumOfRot.y += self->content.rotation.y;
		if(temp->nextLLBoid == NULL){
			break;
		}
		temp = temp->nextLLBoid;
	}

	vec2 returnValue = {
		.x = sumOfRot.x/counter,
		.y = sumOfRot.y/counter
	};
	return returnValue;
}

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
		temp = temp->nextLLBoid;
	}

	vec2 returnValue = {
		.x = sumOfPos.x/counter,
		.y = sumOfPos.y/counter
	};
	return returnValue;
}

vec2 avgPositionDiff(LLBoid *selfList, boid self){
	//get postion differen from own --> avg
	//return
	LLBoid* temp = selfList;
	int counter = 0;
	vec2 sumOfPos = {
		.x = 0,
		.y = 0
	};

	while(temp->nextLLBoid != NULL){
		counter++;
		sumOfPos.x += abs( self.postion.x - selfList->content.postion.x );
		sumOfPos.y += abs( self.postion.y - selfList->content.postion.y );
		temp = temp->nextLLBoid;
	}

	sumOfPos.x = sumOfPos.x/counter;
	sumOfPos.y = sumOfPos.y/counter;

	return sumOfPos;
}
//[]
boid nextPosition(LLBoid *selfList, boid self){
	vec2 temp = {
		.x = 0,
		.y = 0
	};



	//speration --> avgPosDif *-1 * factor
	//allignment --> avg from avgRotation and self
	//push to next postion

	return self;
}
