#ifndef BIOD_H
#define BOID_H

#include <stdbool.h>

#include "boid.c"

typedef struct vec2 vec2;

typedef struct boid boid;

typedef struct LLBoid LLBoid;

LLBoid LLBoidStdConstr();

LLBoid LLBoidConstr(boid boidInput);

boid boidStdConstr();

boid boidConstr(vec2 postionInput, vec2 rotationInput);

void LLBoidAppend(LLBoid* self, boid item);

LLBoid LLBoidGetAt(LLBoid* self, int index);

void LLBoidPop(LLBoid* self, int index);

void LLBoidSetAt(LLBoid* self, int index, boid item);

int LLBoidLen(LLBoid* self);

void LLBoidPrint(LLBoid *selfList, bool printPosition, bool printRotation);

vec2 normalVec2(vec2 input);

vec2 avgRotFromLLBoid(LLBoid *self);

vec2 avgPositionDiff(LLBoid *selfList, boid self);

boid avgPosRotFromLLBoid(LLBoid *selfList, boid self);

boid nextPosition(LLBoid *selfList, boid self);

#endif