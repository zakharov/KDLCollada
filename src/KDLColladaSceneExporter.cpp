/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

	This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/


#include "KDLColladaSceneExporter.h"
#include "COLLADASWScene.h"
#include "COLLADASWBindKinematicsModel.h"
#include "COLLADASWBindJointAxis.h"
#include "COLLADASWConstantsKinematicsExtension.h"
#include "COLLADASWInstanceKinematicsScene.h"
#include "COLLADABUURI.h"
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


KDLColladaSceneExporter::KDLColladaSceneExporter ( COLLADASW::StreamWriter * streamWriter) : COLLADASW::Scene(streamWriter, COLLADABU::URI())
{

}

KDLColladaSceneExporter::~KDLColladaSceneExporter()
{

}


bool KDLColladaSceneExporter::doExport(vector<KDL::Chain>& kdlChains)
{
    COLLADASW::Scene::mSW->openElement ( COLLADASW::CSWC::CSW_ELEMENT_SCENE );

    string url = "";
    url = url + "#" + "kinematics_scene.01";

    COLLADASW::InstanceKinematicsScene instanceKinScene( COLLADASW::Scene::mSW, url );
    instanceKinScene.start();

   // makeColladaSWInstanceKinematicsScene(COLLADASW::Scene::mSW, kdlChains[0], "","","");

    instanceKinScene.end();

    COLLADASW::Scene::mSW->closeElement();

    return true;
}

void KDLColladaSceneExporter::makeColladaSWInstanceKinematicsScene(COLLADASW::StreamWriter* streamWriter,
                                                                                                         KDL::Chain& kdlChain,
                                                                                                         string kinSceneId, string url, string sid)
{

    string modelURL = "";
    string param = "param.model";

    COLLADASW::BindKinematicsModel colladaBindKinematicsModel(streamWriter, modelURL, param);
    colladaBindKinematicsModel.add();

   /* COLLADASW::Newparam newparam(streamWriter, "param.model");
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
*/

}

