#include "COLLADAKinModelSerialChainIterator.h"
#include "COLLADABU.h"
#include "Logger.h"
#include <cmath>

using namespace COLLADAFW;
using namespace COLLADABU::Math;
using namespace std;
using namespace BRICS_MM;

COLLADAKinModelSerialChainIterator::~COLLADAKinModelSerialChainIterator()
{
    //dtor
}

COLLADAKinModelSerialChainIterator::COLLADAKinModelSerialChainIterator(KinematicsModel* kinModelPtr)
{
    current = 0;
    this->kinModelPtr = kinModelPtr;
    buildKinMatrix();
}

bool COLLADAKinModelSerialChainIterator::next() // move cursor and get next element
{
    if (size() == 0)
        return false;

    if (current < size()-1)
    {
        current++;
        return true;
    }
    else return
            false;

}

bool COLLADAKinModelSerialChainIterator::previous() // move cursor and get previous element
{
    return false;
}

void COLLADAKinModelSerialChainIterator::reset()    // reset iterator, move cursor to the root node
{
    current = 0;
}

unsigned int COLLADAKinModelSerialChainIterator::size() // return a number of elemnts
{
    unsigned int matrixSize = 0;
    for (unsigned int i = 0; i < kinMatrix.size(); i++)
    {
       // cout << kinMatrix[0][i] << " " << kinMatrix[1][i] << " " << kinMatrix[2][i] << " "  <<  endl;
       // cout << kinMatrix[0][i] << " " << kinMatrix[1][i] << " " << kinMatrix[2][i] <<  endl;

        if (kinMatrix[i][i+1] == NULL)
            return matrixSize;

        matrixSize++;
    }
    cout << endl;
    cout << endl;
    return matrixSize;
}

Joint* COLLADAKinModelSerialChainIterator::getJoint()  // get current element
{
    return kinModelPtr->getJoints()[kinMatrix[current][current+1]-1];
}

TransformationPointerArray* COLLADAKinModelSerialChainIterator::getTransformationArray()
{
    LOG (INFO) << "transformMatrix " << current << " " << kinMatrix[current][current+1];
    return transformMatrix[kinMatrix[current][current+1]-1][current];

}

unsigned int COLLADAKinModelSerialChainIterator::getMaxJointIndex(const KinematicsModel::LinkJointConnections& linkJointConnArray)
{
    unsigned int joint = 0;
    for (unsigned int i = 0; i < linkJointConnArray.getCount(); i++)
    {
        KinematicsModel::LinkJointConnection* linkJointConnPtr = linkJointConnArray[i];
        unsigned int j = linkJointConnPtr->getJointIndex();
        joint = max(joint,j);
    }
    return  joint;
}

unsigned int COLLADAKinModelSerialChainIterator::getLinkNumber(const KinematicsModel::LinkJointConnections& linkJointConnArray)
{
    unsigned int link = 0;
    for (unsigned int i = 0; i < linkJointConnArray.getCount(); i++)
    {
        KinematicsModel::LinkJointConnection* linkJointConnPtr = linkJointConnArray[i];
        unsigned int l = linkJointConnPtr->getLinkNumber();
        link = max(link,l);
    }
    return  link;
}

template <class T>
void COLLADAKinModelSerialChainIterator::initMatrix(unsigned int width, unsigned int height, std::vector< std::vector<T> >& matrix, T defaultValue)
{
    matrix.resize(width);
    for (unsigned int i = 0; i < width; i++)
    {
        matrix[i].resize(height);
        for (unsigned int y = 0; y < height; y++)
            matrix[i][y] = defaultValue;
    }
}

void COLLADAKinModelSerialChainIterator::parseLinkJointConnections(unsigned int jointIndex) //Here we assume that each joint has only 2 adjacent links
{
    const KinematicsModel::LinkJointConnections& linkJointConnArray = kinModelPtr->getLinkJointConnections();
    const JointPointerArray& jointArray = kinModelPtr->getJoints();
    bool isParentLink = true;
    KinematicsPair kinPair;
    for (unsigned int i = 0; i < linkJointConnArray.getCount(); i++)
    {
        KinematicsModel::LinkJointConnection* linkJointConnPtr = linkJointConnArray[i];
        unsigned int jIndex = linkJointConnPtr->getJointIndex();
        if (jIndex == jointIndex)
        {
            if (isParentLink)
            {
                unsigned int linkNumber = linkJointConnPtr->getLinkNumber();
                kinPair.parentLink = linkNumber;
                isParentLink = false;
            }
            else
            {
                unsigned int linkNumber = linkJointConnPtr->getLinkNumber();
                kinPair.childLink = linkNumber;
                isParentLink = true;
                kinMatrix[kinPair.parentLink][kinPair.childLink] = jointIndex+1;
            }
        }
    }
}


void COLLADAKinModelSerialChainIterator::buildTransformation()
{
    const KinematicsModel::LinkJointConnections& linkJointConnArray = kinModelPtr->getLinkJointConnections();

    for (unsigned int i = 0; i < linkJointConnArray.getCount(); i++)
    {
        KinematicsModel::LinkJointConnection* linkJointConnPtr = linkJointConnArray[i];
        LinkIndex linkIndex = linkJointConnPtr->getLinkNumber();
        JointIndex jointIndex = linkJointConnPtr->getJointIndex();
        TransformationPointerArray& transformArray = linkJointConnPtr->getTransformations();
        if (transformArray.getCount() > 0)
        {
            transformMatrix[jointIndex][linkIndex] = &transformArray;
        }
    }
}

void COLLADAKinModelSerialChainIterator::parseJointPrimitiveArray(COLLADAFW::Joint* jointPtr, KDL::Joint::JointType& jointType, KDL::Vector& jointAxis)
{
    const JointPrimitivePointerArray& jointPrimitiveArray = jointPtr->getJointPrimitives();

    if (jointPrimitiveArray.getCount() > 1)
        LOG(ERROR) << "found more than one joint primitive";

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
            LOG(ERROR) << "unknown joint type";
        }

    }

}

void COLLADAKinModelSerialChainIterator::buildKinMatrix()
{
    unsigned int maxJointIndex = getMaxJointIndex(kinModelPtr->getLinkJointConnections());
    unsigned int linkNumber = getLinkNumber(kinModelPtr->getLinkJointConnections());

    initMatrix(linkNumber+1, linkNumber+1, kinMatrix, 0);
    initMatrix(maxJointIndex+1, linkNumber, transformMatrix, (COLLADAFW::TransformationPointerArray*) NULL);

    buildTransformation();
    for (unsigned int i = 0; i <= maxJointIndex; i++)
    {
      //  vector<KinematicsPair> kinPairArray;
        parseLinkJointConnections(i);

        /*    vector<unsigned int> links;
            getConnectedLinks(i, kinModelPtr->getLinkJointConnections(), links);
            KinematicsModel::LinkJointConnection* linkJointConnPtr = linkJointConnArray[i];
            unsigned int jointIndex = linkJointConnPtr->getJointIndex();
            unsigned int linkNumber = linkJointConnPtr->getLinkNumber();
            const TransformationPointerArray& transformArray = linkJointConnPtr->getTransformations();
            Joint* jointPtr = jointArray[jointIndex];
        #ifdef DEBUG

             << "joint index = " << jointIndex << " connected to " << " link number = " << linkNumber << endl;
            cout << "joint name: " << jointPtr->getName() << endl;
        #endif
            parseJointPrimitiveArray(jointPtr);
        */
    }


}
