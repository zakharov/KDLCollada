/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

	This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#include "KDLColladaLibraryKinematicsScenesExporter.h"
#include "COLLADASWInstanceKinematicsModel.h"
#include "COLLADASWKinematicsScene.h"
#include "COLLADASWLibraryKinematicsScenes.h"
#include "COLLADASWNewparam.h"
#include "COLLADASWSIDREF.h"
#include "COLLADASWFloat.h"
#include <kdl/chain.hpp>
#include <string>
#include <sstream>
#include "Logger.h"

using namespace std;


const string defaultJointIdPrefix = "joint";
const string defaultLinkIdPrefix = "link";
const string kdlDefaultSegmentName = "NoName";
const string kdlDefaultJointName = "NoName";

string toString(int number);

KDLColladaLibraryKinematicsScenesExporter::KDLColladaLibraryKinematicsScenesExporter ( COLLADASW::StreamWriter * streamWriter) : COLLADASW::LibraryKinematicsScenes(streamWriter)
{

}

KDLColladaLibraryKinematicsScenesExporter::~KDLColladaLibraryKinematicsScenesExporter()
{

}

bool KDLColladaLibraryKinematicsScenesExporter::doExport(vector<KDL::Chain>& kdlChains)
{
    openLibrary();


    COLLADASW::KinematicsScene kinematicsScene(COLLADASW::LibraryKinematicsScenes::mSW, "kinematics_scene.01");
    startKinematicsScene(kinematicsScene);
    makeColladaSWInstanceKinematicsModel(COLLADASW::LibraryKinematicsScenes::mSW, kdlChains[0], "kinematics_scene.01" ,"chain.01", "chain.01");
    endKinematicsScene(kinematicsScene);
    closeLibrary();
    return true;
}

COLLADASW::InstanceKinematicsModel KDLColladaLibraryKinematicsScenesExporter::makeColladaSWInstanceKinematicsModel(COLLADASW::StreamWriter* streamWriter,
                                                                                                         KDL::Chain& kdlChain,
                                                                                                         string kinSceneId, string url, string sid)
{

    string modelURL = "#" + url;
    string modelSid = sid;

    COLLADASW::InstanceKinematicsModel colladaInstanceKinematicsModel(streamWriter, modelURL, modelSid);
    startInstanceKinematicsModel(colladaInstanceKinematicsModel);

    COLLADASW::Newparam newparam(streamWriter, "param.model");
    startNewparam(newparam);
    COLLADASW::SIDREF sidref(streamWriter, kinSceneId + "/" + sid);
    addSIDREF(sidref);
    endNewparam(newparam);

    unsigned int segNum = kdlChain.getNrOfSegments();

    for (unsigned int i = 0; i < segNum; i++ )
    {
        string path = "param." + defaultJointIdPrefix + toString(i) + ".axis";
        COLLADASW::Newparam newparamAxis(streamWriter, path);

        COLLADASW::SIDREF sidrefAxis(streamWriter, kinSceneId + "/" + sid + "/" + defaultJointIdPrefix + toString(i) + "/axis" );


        path = "param." + defaultJointIdPrefix + toString(i) + ".value";
        COLLADASW::Newparam newparamValue(streamWriter, path);

        COLLADASW::Float _float(streamWriter, 0);

        startNewparam(newparamAxis);
        addSIDREF(sidrefAxis);
        endNewparam(newparamAxis);
        startNewparam(newparamValue);
        addFloat(_float);
        endNewparam(newparamValue);
    }

    return colladaInstanceKinematicsModel;
}


