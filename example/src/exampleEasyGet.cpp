/*exampleEasyGet.cpp */
/**
 * Copyright - See the COPYRIGHT that is included with this distribution.
 * EPICS pvData is distributed subject to a Software License Agreement found
 * in file LICENSE that is included with this distribution.
 */
/**
 * @author mrk
 */

/* Author: Marty Kraimer */

#include <iostream>

#include <pv/easyPVA.h>

using namespace std;
using namespace epics::pvData;
using namespace epics::pvAccess;
using namespace epics::easyPVA;


static void exampleDouble(EasyPVAPtr const &easyPVA)
{
    cout << "example double scalar\n";
    double value;
    try {
        cout << "short way\n";
        value =  easyPVA->channel("exampleDouble")->get()->getDouble();
        cout << "as double " << value << endl;
    } catch (std::runtime_error e) {
        cout << "exception " << e.what() << endl;
    }
    cout << "long way\n";
    EasyChannelPtr easyChannel = easyPVA->createChannel("exampleDouble");
    easyChannel->issueConnect();
    Status status = easyChannel->waitConnect(2.0);
    if(!status.isOK()) {cout << " connect failed\n"; return;}
    EasyGetPtr easyGet = easyChannel->createGet();
    easyGet->issueConnect();
    status = easyGet->waitConnect();
    if(!status.isOK()) {cout << " createGet failed\n"; return;}
    value = easyGet->getDouble();
    cout << "as double " << value << endl;
}

static void exampleDoubleArray(EasyPVAPtr const &easyPVA)
{
    cout << "example double array\n";
    shared_vector<double> value;
    try {
        cout << "short way\n";
        value =  easyPVA->createChannel("exampleDoubleArray")->createGet()->getDoubleArray();
        cout << "as doubleArray " << value << endl;
    } catch (std::runtime_error e) {
        cout << "exception " << e.what() << endl;
    }
    try {
        cout << "long way\n";
        EasyChannelPtr easyChannel = easyPVA->createChannel("exampleDoubleArray");
        easyChannel->connect(2.0);
        EasyGetPtr easyGet = easyChannel->createGet();
        value = easyGet->getDoubleArray();
        cout << "as doubleArray " << value << endl;
    } catch (std::runtime_error e) {
        cout << "exception " << e.what() << endl;
    }
}

static void examplePowerSupply(EasyPVAPtr const &easyPVA)
{
    cout << "example powerSupply\n";
    PVStructurePtr pvStructure;
    try {
        cout << "short way\n";
        pvStructure =  easyPVA->createChannel("examplePowerSupply")->createGet("field()")->getPVStructure();
        cout << pvStructure << endl;
    } catch (std::runtime_error e) {
        cout << "exception " << e.what() << endl;
    }
     
}

int main(int argc,char *argv[])
{
    EasyPVAPtr easyPVA = EasyPVA::create();
    exampleDouble(easyPVA);
    exampleDoubleArray(easyPVA);
    examplePowerSupply(easyPVA);
    cout << "done\n";
    return 0;
}
