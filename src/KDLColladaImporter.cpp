#include "KDLColladaImporter.h"
#include "COLLADAKinModelSerialChainIterator.h"
#include "COLLADAFW.h"
#include "COLLADABU.h"
#include <iostream>

#include <kdl/chain.hpp>


//#define DEBUG

using namespace std;
using namespace COLLADAFW;
using namespace COLLADABU::Math;

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


//TODO create KinematicsModel iterator
//

//void createSerialKinematicsModelIterator(KinematicsModel* kinModelPtr) {    // Serail chain iterator of the COLLADA 1.5 <kinematics model> tag
//
//}



/*
example of parallel kinematics repr.

                      j4 l4
l0 j1 l1 j2 l2 j3  l3
                      0 --
--  0 -- 0 --  0  --
                      0 --
                      j5 l5

Structure matrix

   l0 l1 l2 l3 l4 l5
l0 0  0  0  0  0  0
l1 j1 0  0  0  0  0
l2  0 j2 0  0  0  0
l3  0 0  j3 0  0  0
l4  0 0  0  j4 0  0
l5  0 0  0  j5 0  0


Transformation matrix

   j0 j1 l2 j3 j4 j5
l0 0  0  0  0  0  0
l1 t1 0  0  0  0  0
l2  0 t2 0  0  0  0
l3  0 0  t3 0  0  0
l4  0 0  0  t4 0  0
l5  0 0  0  0  0  0

*/


void KDLColladaImporter::parseKinematicsModel(const KinematicsScene* kinematicsScenePtr, vector <KDL::Chain>& kdlChainArray)
{
    const KinematicsModelArray& kinModelArray = kinematicsScenePtr->getKinematicsModels();
#ifdef DEBUG
    cout << "Found " << kinModelArray.getCount() << " kinematics models." << endl;
#endif
    for (size_t i = 0; i < kinModelArray.getCount(); i++)
    {
        KinematicsModel* kinModelPtr = kinModelArray[i];
        KDL::Chain kdlChain;
        if (kinModelPtr != NULL)
        {
            parseLinkJointConnections(kinModelPtr);
            kdlChainArray.push_back(kdlChain);
        }

        COLLADAKinModelSerialChainIterator itr(kinModelPtr);
        do
        {
            Joint* joint = itr.getJoint();
            TransformationPointerArray* transform = itr.getTransformationArray();
            if (joint)
            {
                cout << "Joint " << joint->getName() << endl;

            }
            if (transform)
            {
                Transformation* tr = (*transform)[0];
                cout << tr->getTransformationType() << endl;
            }


        }
        while(itr.next() != NULL);

    }




}



void KDLColladaImporter::parseLinkJointConnections(KinematicsModel* kinModelPtr)
{
    const KinematicsModel::LinkJointConnections& linkJointConnArray = kinModelPtr->getLinkJointConnections();
    const JointPointerArray& jointArray = kinModelPtr->getJoints();

    for (size_t i = 0; i < linkJointConnArray.getCount(); i++)
    {
        KinematicsModel::LinkJointConnection* linkJointConnPtr = linkJointConnArray[i];
        size_t jointIndex = linkJointConnPtr->getJointIndex();
        size_t linkNumber = linkJointConnPtr->getLinkNumber();
        const TransformationPointerArray& transformArray = linkJointConnPtr->getTransformations();
        Joint* jointPtr = jointArray[jointIndex];
#ifdef DEBUG
        cout << "joint index = " << jointIndex << " connected to " << " link number = " << linkNumber << endl;
        cout << "joint name: " << jointPtr->getName() << endl;
        cout << "number of transforms: " << transformArray.getCount() << endl;
#endif
        parseJointPrimitiveArray(jointPtr);

    }
}

void KDLColladaImporter::parseJointPrimitiveArray(Joint* jointPtr)
{
    const JointPrimitivePointerArray& jointPrimitiveArray = jointPtr->getJointPrimitives();

    for (size_t i = 0; i < jointPrimitiveArray.getCount(); i++)
    {
        JointPrimitive* jointPtr = jointPrimitiveArray[i];
        Vector3& axis = jointPtr->getAxis();
#ifdef DEBUG
        cout << "Axis: " << fabs(axis[0]) << " " << fabs(axis[1]) << " " << fabs(axis[2]) << endl;
        switch (jointPtr->getType())
        {
        case JointPrimitive::PRISMATIC:
            cout << "Prismatic type" << endl;
            break;
        case JointPrimitive::REVOLUTE:
            cout << "Revolute type" << endl;
            break;
        default:
            cout << "Unknown type" << endl;
        }

#endif
    }

}

void  KDLColladaImporter::parseNodeLinkBindArray(InstanceKinematicsScene* instKinScene)
{
    const InstanceKinematicsScene::NodeLinkBindingArray& nodeLinkBindArray = instKinScene->getNodeLinkBindings();

    for (size_t i = 0; i < nodeLinkBindArray.getCount(); i++)
    {
        const InstanceKinematicsScene::NodeLinkBinding& nodeLinkBind = nodeLinkBindArray[i];
        size_t modelId = nodeLinkBind.kinematicsModelId;
        size_t linkNum = nodeLinkBind.linkNumber;
        COLLADAFW::UniqueId nodeId = nodeLinkBind.nodeUniqueId;

#ifdef DEBUG
        cout << "node id = " << nodeId << " attached to model id = " << modelId << " link number = " << linkNum << endl;
#endif
    }
}

bool KDLColladaImporter::writeKinematicsScene( const COLLADAFW::KinematicsScene* kinematicsScene )
{
    cout << "Kinematics scene found, let's parse it!" << endl;
    const InstanceKinematicsSceneArray& instanceKinSceneArray = kinematicsScene->getInstanceKinematicsScenes();

#ifdef DEBUG
    for (int i = 0; i < instanceKinSceneArray.getCount(); i++)
    {
        InstanceKinematicsScene* instanceKinScenePtr = instanceKinSceneArray[i];
        cout << instanceKinScenePtr->getName() << endl;
        parseNodeLinkBindArray(instanceKinScenePtr);
    }
#endif

    vector<KDL::Chain> chain;
    parseKinematicsModel(kinematicsScene, chain);


    return true;
}

