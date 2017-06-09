// ASN.1 Parser
// Michal Piotrak - TKOM Project

#ifndef RANGEOBJECT_H
#define RANGEOBJECT_H

#include <iostream>
#include <string>
#include <vector>
#include <ctype.h>

enum LIMIT_TYPE
{
    MEMBER_LIMIT,
    RANGE_VALUES_INTEGER,
    STRING_FROM_LIMIT,
    STRING_SIZE_LIMIT,
    VALUES_LIST_ENUM,
    VALUES_LIST_INTEGER,
    BOOLEAN_LIMIT,
    SEQUENCE_OF_LIMIT
};

using namespace std;

class RangeObject
{
    public:
        RangeObject();
        RangeObject(const RangeObject&);
        RangeObject(LIMIT_TYPE);
        RangeObject(LIMIT_TYPE, vector<string>);
        virtual ~RangeObject();
        RangeObject& operator =(RangeObject&);

        LIMIT_TYPE getLimitType();
        string getTypeName();
        string getIdentifierName();
        vector<string> getParamVect();

        void printLimit();
        void printMemberLimit();
        void printSequenceOfLimit();
    private:
        LIMIT_TYPE limitType;
        string typeName;
        string identifierName;
        vector<string> paramVect;

        void printRangeValuesLimit();
        void printStringFromLimit();
        void printStringSizeLimit();
        void printValueListLimit();
        void printBooleanLimit();
        void printNumericStringLimit();

        bool isIdentifierEmpty();
};

#endif
