/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

	This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#include "KDLColladaLibraryJointsExporter.h"
#include "KDLColladaLibraryKinematicsModelsExporter.h"
#include "KDLColladaLibraryKinematicsScenesExporter.h"
#include "KDLColladaSceneExporter.h"

#include "KDLColladaExporter.h"
#include "COLLADASWStreamWriter.h"
#include "COLLADABUNativeString.h"
#include "COLLADASWAsset.h"
#include "Logger.h"

#include <string>

using namespace COLLADABU;
using namespace KDL;
using namespace std;

KDLColladaExporter::KDLColladaExporter(const std::string& filename,
                                       std::vector<Chain>& kdlChains) :
                                                                        mStreamWriter ( NativeString (filename),
                                                                        false,
                                                                        COLLADASW::StreamWriter::COLLADA_1_5_0 ),
                                                                        kdlChains(kdlChains)
{
    Logger::setMinLoglevel(Logger::LOGDEBUG);
    Logger::setLogfile("exporter.log");
}

KDLColladaExporter::~KDLColladaExporter()
{

}

bool KDLColladaExporter::exportAsset()
{

    COLLADASW::Asset asset ( &mStreamWriter );

    // Add contributor information
    // Set the author
    String userName = "Alexey Zakharov";
    String authoringTool = "KDL COLLADA exporter";


    if ( !userName.empty() )
        asset.getContributor().mAuthor = String ( userName );

    /*const COLLADASW::URI maxFileUri = mExportSceneGraph->getMaxFileUri();
    if ( !maxFileUri.getPathFile().empty() )
        asset.getContributor().mSourceData = maxFileUri.getURIString();
    */

    asset.getContributor().mAuthoringTool = authoringTool;



    SystemUnitType systemUnitType = UNITS_MILLIMETERS;

    float systemUnitScale = 1;

    switch ( systemUnitType )
    {

    case UNITS_INCHES:
        asset.setUnit ( "inch", systemUnitScale * 0.0254f );
        break;

    case UNITS_FEET:
        asset.setUnit ( "feet", systemUnitScale * 0.3048f );
        break;

    case UNITS_MILES:
        asset.setUnit ( "mile", systemUnitScale * 1609.344f );
        break;

    case UNITS_MILLIMETERS:
        asset.setUnit ( "millimeter", systemUnitScale * 0.001f );
        break;

    case UNITS_CENTIMETERS:
        asset.setUnit ( "centimeter", systemUnitScale * 0.01f );
        break;

    case UNITS_METERS:
        asset.setUnit ( "meter", systemUnitScale );
        break;

    case UNITS_KILOMETERS:
        asset.setUnit ( "kilometer", systemUnitScale * 1000.0f );
        break;

    default:
        break;
    }

    asset.setUpAxisType ( COLLADASW::Asset::Z_UP );

    asset.add();

    return true;
}

bool KDLColladaExporter::exportJoints(vector<COLLADASW::Joint>& joints)
{
    KDLColladaLibraryJointsExporter jointExporter( &mStreamWriter );
    bool status = jointExporter.doExport(kdlChains);
  //  joints = jointExporter.getJoints();
    return status;
}

bool KDLColladaExporter::exportKinematicsModels(vector<COLLADASW::Joint>& joints)
{
    KDLColladaLibraryKinematicsModelsExporter kinematicsModelsExporter( &mStreamWriter );
    return kinematicsModelsExporter.doExport( kdlChains);
}

bool KDLColladaExporter::exportKinematicsScenes()
{
    KDLColladaLibraryKinematicsScenesExporter kinematicsScenesExporter( &mStreamWriter );
    return kinematicsScenesExporter.doExport(kdlChains);
}

bool KDLColladaExporter::exportScene()
{
    KDLColladaSceneExporter sceneExporter( &mStreamWriter );
    return sceneExporter.doExport(kdlChains);
}

bool KDLColladaExporter::exportChain ()
{
    bool status = true;

    LOG(DEBUG) << "Exporting to" << this->mStreamWriter.getCOLLADAVersion();
    mStreamWriter.startDocument();
    status = exportAsset();

    vector<COLLADASW::Joint> joints;
    status = exportJoints(joints);

    status = exportKinematicsModels(joints);

    status = exportKinematicsScenes();

    status = exportScene();
    mStreamWriter.endDocument();

    return status;
}

