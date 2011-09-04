/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

	This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#include <iostream>
#include <vector>
#include <fstream>

#include "KDLCollada.h"


using namespace std;
using namespace KDL;

int main()
{
    Chain puma560;
    puma560.addSegment(Segment());
    puma560.addSegment(Segment(Joint(Joint::RotZ),
                               Frame::DH(0.0,M_PI_2,0.0,0.0),
                               RigidBodyInertia(0,Vector::Zero(),RotationalInertia(0,0.35,0,0,0,0))));
    puma560.addSegment(Segment(Joint(Joint::RotZ),
                               Frame::DH(0.4318,0.0,0.0,0.0),
                               RigidBodyInertia(17.4,Vector(-.3638,.006,.2275),RotationalInertia(0.13,0.524,0.539,0,0,0))));
    puma560.addSegment(Segment());
    puma560.addSegment(Segment(Joint(Joint::RotZ),
                               Frame::DH(0.0203,-M_PI_2,0.15005,0.0),
                               RigidBodyInertia(4.8,Vector(-.0203,-.0141,.070),RotationalInertia(0.066,0.086,0.0125,0,0,0))));
    puma560.addSegment(Segment(Joint(Joint::RotZ),
                               Frame::DH(0.0,M_PI_2,0.4318,0.0),
                               RigidBodyInertia(0.82,Vector(0,.019,0),RotationalInertia(1.8e-3,1.3e-3,1.8e-3,0,0,0))));
    puma560.addSegment(Segment());
    puma560.addSegment(Segment());
    puma560.addSegment(Segment(Joint(Joint::RotZ),
                               Frame::DH(0.0,-M_PI_2,0.0,0.0),
                               RigidBodyInertia(0.34,Vector::Zero(),RotationalInertia(.3e-3,.4e-3,.3e-3,0,0,0))));
    puma560.addSegment(Segment(Joint(Joint::RotZ),
                               Frame::DH(0.0,0.0,0.0,0.0),
                               RigidBodyInertia(0.09,Vector(0,0,.032),RotationalInertia(.15e-3,0.15e-3,.04e-3,0,0,0))));
    puma560.addSegment(Segment());

    KDLCollada kdlCollada;
    const string filename =  "test.dae";  // loading collada kinematics model and converting it to kdl serial chain
    vector <Chain> chains;
    chains.push_back(puma560);
    if (!kdlCollada.save(COLLADA_MODELS_PATH + filename, chains))
    {
        cout << "Failed to export " << filename;
        return 0;
    }

    return 0;
}

