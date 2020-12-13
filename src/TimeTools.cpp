#include "../include/HackQuarium.h"

int getActualHour() {
	return(AllStaticData::allData.secondFromEpoch/3600 % 24);
}

int getActualMinutes() {
	return(AllStaticData::allData.secondFromEpoch/60 % 60);
}