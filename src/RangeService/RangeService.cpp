// ASN.1 Parser
// Michal Piotrak - TKOM Project

#include "RangeService.h"

RangeService::RangeService()
{}

RangeService::~RangeService()
{}

void RangeService::addCurrentLimitParam(string param)
{
    currentLimitParams.push_back(param);
}

void RangeService::addLimit(LIMIT_TYPE limitType)
{
    limitsVector.push_back(RangeObject(limitType, currentLimitParams));
}

void RangeService::printLimits()
{
    cout << "Detected limits:" << endl;
    for(vector<RangeObject>::iterator it = limitsVector.begin(); it != limitsVector.end(); ++it)
    {
        it->printLimit();
    }
}

void RangeService::clear()
{
    currentLimitParams.clear();
}
