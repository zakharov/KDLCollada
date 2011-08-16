
#include <iostream>
#include <vector>
#include <fstream>

#include "KDLCollada.h"


using namespace std;


int main()
{
    KDLCollada kdlCollada;
    vector <KDL::Chain> kinematicsModels;
    const string filename =  "simple.dae";  // loading collada kinematics model and converting it to kdl serial chain
    if (!kdlCollada.load(COLLADA_MODELS_PATH + filename, kinematicsModels))
    {
        cout << "Failed to import " << filename << endl;
        return 0;
    }

    cout << "Imported " << kinematicsModels.size() << " kinematics chains" << endl;

    for (unsigned int i = 0; i < kinematicsModels.size(); i++)  // parsing output kdl serail chain
    {
        KDL::Chain chain = kinematicsModels[i];
        cout << "Chain " << i << " has " << chain.getNrOfSegments() << " segments" << endl;

        for (unsigned int u = 0; u < chain.getNrOfSegments(); u++)
        {
            KDL::Segment segment = chain.segments[u];
            string segmentName = segment.getName();
            cout << "Segment " << segmentName << " :" <<endl;

            KDL::Frame f_tip = segment.getFrameToTip();
            KDL::Vector rotAxis = f_tip.M.GetRot();
            double rotAngle = f_tip.M.GetRotAngle(rotAxis);
            KDL::Vector trans = f_tip.p;
            cout << "   frame: rotation " << rotAxis.x() << " " << rotAxis.y() << " " << rotAxis.z() << " " << rotAngle * 180 / M_PI << endl;
            cout << "   frame: translation " << trans.x() << " " << trans.y() << " " << trans.z() << endl;

            KDL::RigidBodyInertia inertia = segment.getInertia();
            KDL::Joint joint = segment.getJoint();

            string jointName = joint.getName();
            string jointType = joint.getTypeName();
            KDL::Vector jointAxis = joint.JointAxis();
            KDL::Vector jointOrigin = joint.JointOrigin();

            cout << "   joint name: " << jointName << endl;
            cout << "         type: " << jointType << endl;
            cout << "         axis: " << jointAxis.x() << " " <<jointAxis.y() << " " << jointAxis.z() << endl;
            cout << "         origin: " << jointOrigin.x() << " " << jointOrigin.y() << " " << jointOrigin.z() << endl;
        }
    }

    return 0;
}

