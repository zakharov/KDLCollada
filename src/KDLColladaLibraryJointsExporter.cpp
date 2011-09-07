/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

	This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/


#include "KDLColladaLibraryJointsExporter.h"
#include "COLLADAFWJointPrimitive.h"
#include "COLLADASWLibraryJoints.h"
#include <kdl/chain.hpp>
#include <kdl/segment.hpp>
#include <string>
#include <sstream>
#include "Logger.h"

using namespace std;
using namespace KDL;

const string defaultJointIdPrefix = "joint";
const string kdlDefaultJointName = "NoName";

string toString(int number)
{
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

KDLColladaLibraryJointsExporter::KDLColladaLibraryJointsExporter ( COLLADASW::StreamWriter * streamWriter) : COLLADASW::LibraryJoints(streamWriter)
{

}

KDLColladaLibraryJointsExporter::~KDLColladaLibraryJointsExporter()
{

}

const vector<COLLADASW::Joint>& KDLColladaLibraryJointsExporter::getJoints()
{
    return joints;
}

bool KDLColladaLibraryJointsExporter::doExport(vector <Chain>& kdlChains)
{
    if (kdlChains.empty())
    {
        LOG(DEBUG) << "KDL Chains array is empty, has nothing to export";
        return false;
    }


    LOG(WARNING) << "Taking first element from the KDL chain array";

    Chain kdlChain = kdlChains[0];
    openLibrary();

    unsigned int jointNr = kdlChain.getNrOfJoints();

    for (unsigned int i = 0; i < jointNr; i++)
    {
        Segment segment = kdlChain.getSegment(i);
        Joint kdlJoint = segment.getJoint();
        string uniqueId = defaultJointIdPrefix + toString(i);
        COLLADASW::Joint colladaJoint = makeColladaSWJoint(COLLADASW::LibraryJoints::mSW, kdlJoint, uniqueId);
        LOG(INFO) << "Joint id: " << colladaJoint.getJointId();
        LOG(INFO) << "Joint name: " << colladaJoint.getJointName();
        addJoint(colladaJoint);
        joints.push_back(colladaJoint);
    }

    closeLibrary();

    return true;
}

COLLADASW::Joint KDLColladaLibraryJointsExporter::makeColladaSWJoint(COLLADASW::StreamWriter* streamWriter, Joint& kdlJoint, string uniqueId)
{


    string jointName = kdlJoint.getName();

    if (jointName == kdlDefaultJointName)
        jointName = uniqueId;
    Joint::JointType jointType = kdlJoint.getType();
    Vector jointAxis = kdlJoint.JointAxis();


    COLLADAFW::JointPrimitive::Type type;
    switch (jointType)
    {
        case Joint::RotAxis :
        {
            type = COLLADAFW::JointPrimitive::REVOLUTE;
            break;
        }
        case Joint::RotX :
        {
            type = COLLADAFW::JointPrimitive::REVOLUTE;
            break;
        }
        case Joint::RotY :
        {
            type = COLLADAFW::JointPrimitive::REVOLUTE;
            break;
        }
        case Joint::RotZ :
        {
            type = COLLADAFW::JointPrimitive::REVOLUTE;
            break;
        }

        case Joint::TransAxis :
        {
            type = COLLADAFW::JointPrimitive::PRISMATIC;
            break;
        }

        case Joint::TransX :
        {
            type = COLLADAFW::JointPrimitive::PRISMATIC;
            break;
        }

        case Joint::TransY :
        {
            type = COLLADAFW::JointPrimitive::PRISMATIC;
            break;
        }

        case Joint::TransZ :
        {
            type = COLLADAFW::JointPrimitive::PRISMATIC;
            break;
        }

        default :
            LOG(ERROR) << "Unknown joint type: " << kdlJoint.getTypeName() << ", changing to revolute type with no axis.";
            type = COLLADAFW::JointPrimitive::REVOLUTE;
    }

    COLLADABU::Math::Vector3 axis(jointAxis.x(), jointAxis.y(), jointAxis.z());

    COLLADAFW::JointPrimitive jointPrimitive(COLLADAFW::UniqueId(uniqueId), type);
    jointPrimitive.setAxis(axis);

   // jointPrimitive.setHardLimitMax(10);
   // jointPrimitive.setHardLimitMin(-10);


    COLLADASW::Joint colladaJoint(streamWriter, jointPrimitive, uniqueId, jointName); //TODO make sure that ID is unique


//    kdlJoint.name = uniqueId;

    LOG(INFO) << "Joint id: " << colladaJoint.getJointId();
    LOG(INFO) << "Joint name: " << colladaJoint.getJointName();


    return colladaJoint;
}
