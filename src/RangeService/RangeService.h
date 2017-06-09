// ASN.1 Parser
// Michal Piotrak - TKOM Project

#ifndef RANGESERVICE_H
#define RANGESERVICE_H

#include "RangeObject.h"

using namespace std;

class RangeService
{
    public:
        RangeService();
        virtual ~RangeService();
        void addCurrentLimitParam(string);
        void addLimit(LIMIT_TYPE);
        void printLimits();
        void clear();
    private:
        vector<RangeObject> limitsVector;
        vector<string> currentLimitParams;
};

#endif
