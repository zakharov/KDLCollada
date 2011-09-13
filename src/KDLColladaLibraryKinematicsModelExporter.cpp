/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

	This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/


#include "KDLColladaLibraryKinematicsModelsExporter.h"
#include "COLLADASWLibraryKinematicsModels.h"
#include "COLLADASWKinematicsModel.h"
#include "COLLADASWLink.h"
#include "COLLADASWTranslate.h"
#include "COLLADASWRotate.h"
#include "COLLADASWAttachmentFull.h"
#include <kdl/chain.hpp>
#include <kdl/segment.hpp>
#include <string>
#include <sstream>
#include "Logger.h"

using namespace std;
using namespace KDL;

const string defaultJointIdPrefix = "joint";
const string defaultLinkIdPrefix = "link";
const string kdlDefaultSegmentName = "NoName";
const string kdlDefaultJointName = "NoName";

string toString(int number);


KDLColladaLibraryKinematicsModelsExporter::KDLColladaLibraryKinematicsModelsExporter ( COLLADASW::StreamWriter * streamWriter) : COLLADASW::LibraryKinematicsModels(streamWriter)
{

}

KDLColladaLibraryKinematicsModelsExporter::~KDLColladaLibraryKinematicsModelsExporter()
{

}


bool KDLColladaLibraryKinematicsModelsExporter::doExport(vector <Chain>& kdlChains)
{
    if (kdlChains.empty())
    {
        LOG(DEBUG) << "KDL Chains array is empty, has nothing to export";
        return false;
    }


    LOG(WARNING) << "Taking first element from the KDL chain array";

    Chain kdlChain = kdlChains[0];
    openLibrary();

    COLLADASW::KinematicsModel colladaKinematicsModel = makeColladaSWKinematicsModel(COLLADASW::LibraryKinematicsModels::mSW, kdlChain, "chain.01");


    closeLibrary();
    return true;
}

COLLADASW::KinematicsModel KDLColladaLibraryKinematicsModelsExporter::makeColladaSWKinematicsModel(COLLADASW::StreamWriter* streamWriter,
                                                                                                          Chain& kdlChain, string id)
{
    COLLADASW::KinematicsModel kinematicsModel(streamWriter, id);
    startKinematicsModel(kinematicsModel);
    unsigned int jointNr = kdlChain.getNrOfSegments();


    for (unsigned int i = 0; i < jointNr; i++)
    {
        Segment segment = kdlChain.getSegment(i);
        Joint kdlJoint = segment.getJoint();
        string uniqueId = defaultJointIdPrefix + toString(i);
        string url = uniqueId;
        string sid = uniqueId;
        COLLADASW::InstanceJoint colladaInstanceJoint = makeColladaSWInstanceJoint(streamWriter, kdlJoint, url, sid);
        addInstanceJoint(colladaInstanceJoint);
    }

    makeColladaSWSerialKinematicsChain(streamWriter, kdlChain, id);

    endKinematicsModel(kinematicsModel);
    return kinematicsModel;
}

COLLADASW::InstanceJoint KDLColladaLibraryKinematicsModelsExporter::makeColladaSWInstanceJoint(COLLADASW::StreamWriter* streamWriter, Joint& kdlJoint, string url, string sid)
{

    string jointName = kdlJoint.getName();

    if (jointName == kdlDefaultJointName)
        jointName = url;
    jointName = "#" + jointName;

    COLLADASW::InstanceJoint colladaInstanceJoint(streamWriter, jointName, sid);

    return colladaInstanceJoint;
}

unsigned int KDLColladaLibraryKinematicsModelsExporter::makeColladaSWSerialKinematicsChain(COLLADASW::StreamWriter* streamWriter, Chain& kdlChain, string kinModelName, unsigned int jointCounter)
{

    unsigned int jointNumber = kdlChain.getNrOfSegments();
    if (jointCounter < jointNumber)
    {
        Segment segment = kdlChain.getSegment(jointCounter);
        Frame frame = segment.pose(0);
        Vector origin = frame.p;
        Rotation orientation = frame.M;

        double x,y,z,w;

        orientation.GetEulerZYX(z,y,x);


        string linkName = segment.getName();
        if (linkName == kdlDefaultSegmentName)
            linkName = defaultLinkIdPrefix;
        linkName = linkName + toString(jointCounter);

        COLLADASW::Link colladaLink(streamWriter, linkName, linkName);

        string jointName = segment.getJoint().getName();
        if (jointName == kdlDefaultJointName)
            jointName = defaultJointIdPrefix;
        jointName = kinModelName + "/" + jointName + toString(jointCounter);

        COLLADASW::AttachmentFull attachmentFull(streamWriter, jointName);
        startLink(colladaLink);
        startAttachmentFull(attachmentFull);

        if ( (origin.x() + origin.y() + origin.z()) != 0) {
            COLLADASW::Translate translate(streamWriter, origin.x(), origin.y(), origin.z());
            addTranslate(translate);
        }

        if (z != 0)
        {
            COLLADASW::Rotate rotateZ(streamWriter, 0, 0, 1, z * 180 / M_PI);
            addRotate(rotateZ);
        }

        if (y != 0)
        {
            COLLADASW::Rotate rotateY(streamWriter, 0, 1, 0, y * 180 / M_PI);
            addRotate(rotateY);
        }

        if (x != 0)
        {
            COLLADASW::Rotate rotateX(streamWriter, 1, 0, 0, x * 180 / M_PI);
            addRotate(rotateX);
        }


        ++jointCounter;
        makeColladaSWSerialKinematicsChain(streamWriter, kdlChain, kinModelName, jointCounter);
        endAttachmentFull(attachmentFull);
        endLink(colladaLink);
    }/* else
    {

        COLLADASW::Link colladaLink(streamWriter, toString(jointCounter), toString(jointCounter));
        addLink(colladaLink);
    }*/

    return jointCounter;
}
