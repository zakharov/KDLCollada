#include "KDLColladaImporter.h"
#include "COLLADAFW.h"
#include <iostream>

#define DEBUG

using namespace std;
using namespace COLLADAFW;

KDLColladaImporter::KDLColladaImporter()
{

}

KDLColladaImporter::KDLColladaImporter(const KDLColladaImporter& orig)
{

}

KDLColladaImporter::~KDLColladaImporter()
{

}

void KDLColladaImporter::cancel(const COLLADAFW::String& errorMessage)
{

}

void KDLColladaImporter::start()
{

}

void KDLColladaImporter::finish()
{

}

bool KDLColladaImporter::writeGlobalAsset ( const COLLADAFW::FileInfo* asset )
{
    return true;
}

bool KDLColladaImporter::writeScene ( const COLLADAFW::Scene* scene )
{
    return true;
}

bool KDLColladaImporter::writeVisualScene ( const COLLADAFW::VisualScene* visualScene )
{
    return true;
}

bool KDLColladaImporter::writeLibraryNodes ( const COLLADAFW::LibraryNodes* libraryNodes )
{
    return true;
}

bool KDLColladaImporter::writeGeometry ( const COLLADAFW::Geometry* geometry )
{
    return true;
}

bool KDLColladaImporter::writeMaterial( const COLLADAFW::Material* material )
{
    return true;
}

bool KDLColladaImporter::writeEffect( const COLLADAFW::Effect* effect )
{
    return true;
}

bool KDLColladaImporter::writeCamera( const COLLADAFW::Camera* camera )
{
    return true;
}

bool KDLColladaImporter::writeImage( const COLLADAFW::Image* image )
{
    return true;
}

bool KDLColladaImporter::writeLight( const COLLADAFW::Light* light )
{
    return true;
}

bool KDLColladaImporter::writeAnimation( const COLLADAFW::Animation* animation )
{
    return true;
}

bool KDLColladaImporter::writeAnimationList( const COLLADAFW::AnimationList* animationList )
{
    return true;
}

bool KDLColladaImporter::writeSkinControllerData( const COLLADAFW::SkinControllerData* skinControllerData )
{
    return true;
}

bool KDLColladaImporter::writeController( const COLLADAFW::Controller* controller )
{
    return true;
}

bool KDLColladaImporter::writeFormulas( const COLLADAFW::Formulas* formulas )
{
    return true;
}

bool KDLColladaImporter::writeFormula( const COLLADAFW::Formula* formulas )
{
    return true;
}

void KDLColladaImporter::parseLinkJointConnections(KinematicsModel* kinModelPtr) {
    const KinematicsModel::LinkJointConnections& linkJointConnArray = kinModelPtr->getLinkJointConnections();

    for (size_t i = 0; i < linkJointConnArray.getCount(); i++) {
        KinematicsModel::LinkJointConnection* linkJointConnPtr = linkJointConnArray[i];
        size_t jointIndex = linkJointConnPtr->getJointIndex();
        size_t linkNumber = linkJointConnPtr->getLinkNumber();
        const TransformationPointerArray& transformArray = linkJointConnPtr->getTransformations();
        #ifdef DEBUG
        cout << "joint index = " << jointIndex << " connected to " << " link number = " << linkNumber << endl;
        #endif
    }
}

bool KDLColladaImporter::writeKinematicsScene( const COLLADAFW::KinematicsScene* kinematicsScene )
{
    cout << "Kinematics scene found, let's parse it!" << endl;
    const InstanceKinematicsSceneArray& instanceKinSceneArray = kinematicsScene->getInstanceKinematicsScenes();

    const KinematicsModelArray& kinModelArray = kinematicsScene->getKinematicsModels();
#ifdef DEBUG
        cout << "Found " << kinModelArray.getCount() << " kinematics models." << endl;
#endif
    for (size_t i = 0; i < kinModelArray.getCount(); i++) {
        KinematicsModel* kinModelPtr = kinModelArray[i];
        if (kinModelPtr != NULL) {
            parseLinkJointConnections(kinModelPtr);
//            kinModelPtr.getLinkJointConnections();

        }

    }


    return true;
}

