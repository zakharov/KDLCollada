
#include <iostream>
#include <vector>
#include <fstream>

#include "KDLCollada.h"


using namespace std;


int main()
{
    KDLCollada kdlCollada;
    vector <KDL::Chain> kinematicsModels;
    const string filename =  "simple.dae";
    if (kdlCollada.load(COLLADA_MODELS_PATH + filename, kinematicsModels))
        cout << "Imported " << filename << endl;
    else
        cout << "Failed to import " << filename << endl;

    return 0;
}

