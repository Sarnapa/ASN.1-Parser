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
        if(it->getLimitType() == MEMBER_LIMIT)
        {
            for(vector<RangeObject>::iterator it2 = limitsVector.begin(); it2 != limitsVector.end(); ++it2)
            {
                if((it->getParamVect())[0] == it2->getTypeName())
                {
                    it->printMemberLimit();
                    break;
                }
            }
        }
        else if(it->getLimitType() == SEQUENCE_OF_LIMIT)
        {
            if((it->getParamVect())[0] != "BOOLEAN")
            {
                for(vector<RangeObject>::iterator it2 = limitsVector.begin(); it2 != limitsVector.end(); ++it2)
                {
                    if((it->getParamVect())[0] == it2->getTypeName())
                    {
                        it->printSequenceOfLimit();
                        break;
                    }
                }
            }
            else
            {
                it->printSequenceOfLimit();
            }
        }
        else
        {
            it->printLimit();
        }
    }
}

void RangeService::clear()
{
    currentLimitParams.clear();
}

void RangeService::clearWithoutTypeName()
{
    string typeName = string(currentLimitParams.front());
    currentLimitParams.clear();
    currentLimitParams.push_back(typeName);
}
