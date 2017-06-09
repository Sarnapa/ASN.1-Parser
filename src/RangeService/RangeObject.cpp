// ASN.1 Parser
// Michal Piotrak - TKOM Project

#include "RangeObject.h"

RangeObject::RangeObject()
{}

RangeObject::RangeObject(const RangeObject& rangeObject):limitType(rangeObject.limitType), typeName(rangeObject.typeName), paramVect(rangeObject.paramVect)
{}

RangeObject::RangeObject(LIMIT_TYPE limitType):limitType(limitType)
{}

RangeObject::RangeObject(LIMIT_TYPE limitType, vector<string> parameters): limitType(limitType)
{
    typeName = parameters.front();
    vector<string>::iterator it = parameters.begin();
    ++it;
    for(;it != parameters.end(); ++it)
    {
        paramVect.push_back((*it));
    }
}

RangeObject& RangeObject::operator =(RangeObject& rangeObject)
{
    this->limitType = rangeObject.limitType;
    this->typeName = rangeObject.typeName;
    this->paramVect = rangeObject.paramVect;
    return *this;
}

RangeObject::~RangeObject()
{}

void RangeObject::printLimit()
{
    cout << typeName << " - ";
    switch(limitType)
    {
        case MEMBER_LIMIT:
        {
            break;
        }
        case RANGE_VALUES_INTEGER:
        {
            printRangeValuesLimit();
            break;
        }
        case STRING_FROM_LIMIT:
        {
            printStringFromLimit();
            break;
        }
        case STRING_SIZE_LIMIT:
        {
            printStringSizeLimit();
            break;
        }
        case VALUES_LIST_ENUM:
        case VALUES_LIST_INTEGER:
        {
            printValueListLimit();
            break;
        }
    }
    cout << endl << endl;
}

void RangeObject::printRangeValuesLimit()
{
    cout << "Range limit: ";
    cout << "[" << paramVect.front() << " - " << paramVect.back() << "]";
}

void RangeObject::printStringFromLimit()
{
    cout << "Characters list limit: ";
    bool isInserted = false;
    bool isNumericString = false;
    string typeString = paramVect.front();
    if(typeString == "NumericString")
        isNumericString = true;
    vector<string>::iterator it = paramVect.begin();
    ++it;
    vector<string>::iterator stringsBegin = it;
    cout << "[";
    for(; it != paramVect.end(); ++it)
    {
        if((isNumericString && (*it).size() == 1 && isdigit((*it)[0])) || !isNumericString)
        {
            if(it != stringsBegin && isInserted)
                cout << ", ";
            cout << "\'" << *it << "\'";
            isInserted = true;
        }
    }
    cout << "]";
}

void RangeObject::printStringSizeLimit()
{
    cout << "Size limit: ";
    string typeString = paramVect.front();
    vector<string>::iterator it = paramVect.begin();
    ++it;
    if(paramVect.size() == 3)
        cout << "[" << (*it) << " - " << paramVect.back() << "]";
    else
        cout << "[" << (*it) << "]";
    if(typeString == "NumericString")
        printNumericStringLimit();
}

void RangeObject::printValueListLimit()
{
    cout << "Value list limit: ";
    cout << "[";
    for(vector<string>::iterator it = paramVect.begin(); it != paramVect.end(); ++it)
    {
        if(it != paramVect.begin())
            cout << ", ";
        cout << *it;
    }
    cout << "]";
}

void RangeObject::printNumericStringLimit()
{
    cout << endl;
    cout << "NumericString limit: ";
    cout << "[";
    for(unsigned int i = 0; i < 10; ++i)
    {
        if(i != 0)
            cout << ", ";
        cout << "\'" << i << "\'";
    }
    cout << "]";
}
