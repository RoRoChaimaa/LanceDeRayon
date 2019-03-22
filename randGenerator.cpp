#include "pch.h"
#include "randGenerator.h"


float randGenerator::Generate() {
	float resultat;
		do {
		resultat = float((rand() / float(RAND_MAX)));
	} while (resultat >= 1);
	return resultat;
}
