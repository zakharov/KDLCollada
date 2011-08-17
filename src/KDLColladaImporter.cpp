#include "KDLColladaImporter.h"
#include "COLLADAKinModelSerialChainIterator.h"
#include "COLLADAFW.h"
#include "COLLADABU.h"
#include "Logger.h"

#include <iostream>
#include <kdl/chain.hpp>


//#define DEBUG

using namespace std;
using namespace COLLADAFW;
using namespace COLLADABU::Math;
using namespace BRICS_MM;


KDLColladaImporter::KDLColladaImporter(std::vector<KDL::Chain>& kdlChain) : kdlChain(kdlChain)
{
    Logger::setMinLoglevel(Logger::LOGDEBUG);
	Logger::setLogfile("road_runner.log");
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
void KDLColladaImporter::parseTransformationArray(TransformationPointerArray* transformationArray, KDL::Frame& frame)
{

    frame = KDL::Frame::Identity();
    for (unsigned int i = 0; i < transformationArray->getCount(); i++)
    {
        Transformation* transform = (*transformationArray)[i];
        /*
        Types of tf tags in collada
                    MATRIX,
        			TRANSLATE,
        			ROTATE,
        			SCALE,
        			LOOKAT,
        			SKEW
        */

        switch (transform->getTransformationType())
        {
            case COLLADAFW::Transformation::TRANSLATE:
            {
                Vector3 t = dynamic_cast<COLLADAFW::Translate*> (transform)->getTranslation();
                KDL::Vector trans(t.x, t.y, t.z);
                KDL::Frame translation(trans);
                frame = frame * translation;
                break;
            }

            case COLLADAFW::Transformation::ROTATE:
            {
                Vector3 t = dynamic_cast<COLLADAFW::Rotate*> (transform)->getRotationAxis();
                double angle = static_cast<COLLADAFW::Rotate*> (transform)->getRotationAngle();
                KDL::Rotation rot(KDL::Rotation::Rot(KDL::Vector(t.x,
                                                                 t.y,
                                                                 t.z), angle  * COLLADABU::Math::PI / 180.0));

                KDL::Frame rotation(rot);
                frame = frame * rotation;
                break;
            }
        }
    }
}

void KDLColladaImporter::parseKinematicsModel(const KinematicsScene* kinematicsScenePtr, vector <KDL::Chain>& kdlChainArray)
{
    const KinematicsModelArray& kinModelArray = kinematicsScenePtr->getKinematicsModels();
    LOG(INFO) << "Found " << kinModelArray.getCount() << " kinematics models.";

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
        unsigned int segmentNumber = 0;
        do
        {
            Joint* joint = itr.getJoint();

            TransformationPointerArray* transform = itr.getTransformationArray();
            if (joint)
            {
                KDL::Joint::JointType jointType;
                KDL::Vector jointAxis;

                string jointName = joint->getName();
                parseJointPrimitiveArray(joint, jointType, jointAxis);

                KDL::Joint jointKDL(jointName, KDL::Vector(), jointAxis, jointType);

                char buffer[50] = {0};
                sprintf (buffer, "%d\0",segmentNumber);

                KDL::Frame frame;
                if (transform)
                {

                    //Transformation* tr = (*transform)[0];
                    parseTransformationArray(transform, frame);
                }

                KDL::Segment segmentKDL(buffer, jointKDL, frame);
                kdlChain.addSegment(segmentKDL);
                ++segmentNumber;
            }

        }
        while(itr.next() != NULL);

        kdlChainArray.push_back(kdlChain);
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

        LOG(DEBUG) << "joint index = " << jointIndex << " connected to " << " link number = " << linkNumber;
        LOG(DEBUG) << "joint name: " << jointPtr->getName();
        LOG(DEBUG) << "number of transforms: " << transformArray.getCount();

//        parseJointPrimitiveArray(jointPtr);

    }
}

void KDLColladaImporter::parseJointPrimitiveArray(COLLADAFW::Joint* jointPtr, KDL::Joint::JointType& jointType, KDL::Vector& jointAxis)
{
    const JointPrimitivePointerArray& jointPrimitiveArray = jointPtr->getJointPrimitives();

    if (jointPrimitiveArray.getCount() > 1)
        LOG(INFO) << "found more than one joint primitive";

    for (size_t i = 0; i < jointPrimitiveArray.getCount(); i++)
    {
        JointPrimitive* jointPtr = jointPrimitiveArray[i];
        Vector3& axis = jointPtr->getAxis();
        jointAxis.x( fabs(axis[0]));
        jointAxis.y( fabs(axis[1]));
        jointAxis.z( fabs(axis[2]));

        switch (jointPtr->getType())
        {
        case JointPrimitive::PRISMATIC:
            jointType = KDL::Joint::TransAxis;
            break;
        case JointPrimitive::REVOLUTE:
            jointType = KDL::Joint::RotAxis;
            break;
        default:
            LOG(INFO) << "unknown joint type";
        }

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

        LOG(DEBUG) << "node id = " << nodeId << " attached to model id = " << modelId << " link number = " << linkNum;

    }
}

bool KDLColladaImporter::writeKinematicsScene( const COLLADAFW::KinematicsScene* kinematicsScene )
{
    LOG(INFO) << "kinematics scene found, let's parse it!";
    const InstanceKinematicsSceneArray& instanceKinSceneArray = kinematicsScene->getInstanceKinematicsScenes();

#ifdef DEBUG
    for (int i = 0; i < instanceKinSceneArray.getCount(); i++)
    {
        InstanceKinematicsScene* instanceKinScenePtr = instanceKinSceneArray[i];
        LOG(DEBUG) << instanceKinScenePtr->getName();
        parseNodeLinkBindArray(instanceKinScenePtr);
    }
#endif


    parseKinematicsModel(kinematicsScene, kdlChain);


    return true;
}

