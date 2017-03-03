#ifndef _HERD_H_
#define _HERD_H_

#include "genome.h"
#include <algorithm>

const int POPULATION_SIZE = 100;

typedef Warrior {
	int fitness_;
	genome* g_;

	bool operator<(Warrior w) { return fitness_ < w.fitness_; }
} war_s;

typedef vector<war_s> herd;

herd initHerd() {
	herd h;

	for(int i = 0; i < POPULATION_SIZE; ++i) {
		genome* temp = initGenome();
		h.push_back(temp);
	}

	return h;
}

void sortHerd(herd& h) {
	sort(h.begin(), h.end());
}

void topHalfSelection(herd& h) {
	sortHerd(h);

	for(int i = h.size(); i > h.size()/2; --i) {
		int index = rand()%(h.size()/2) + (h.size()/2);
		
		h.at(i) = h.at(index);
	}

}

void rouletteSelection(herd& h) {
	sortHerd(h);
	
	herd new_herd;
	
	double fitness_sum = 0.0;
	
	for(int i = 0; < h.size(); ++i) {
		fitness_sum += (double)h.at(i).fitness_;
	}

	for(int i = 0; i < h.size(); ++i) {
		double chance = (((double) rand()) / RAND_MAX);
		chance = chance * fitness_sum;
		int index = 0;
		
		while(chance > 0){
			chance -= h.at(index).fitness_;
			index++;
		}

		new_herd.push_back(h.at(index));

	}

	h = new_herd;
}

void tournmentSelection(herd& h, int size) {
	herd new_herd;

	for(int i = 0; i < h.size(); ++i) {
		war_s champion = h.at(rand()%h.size);

		for(int x = 0; x < (size-1); ++x) {
			int index = rand()%h.size();
			
			if(champion.fitness_ < h.at(index)) {
				champion = h.at(index)
			}
		}

		new_herd.push_back(champion);
	}

	h = new_herd;
}
		
#endif
