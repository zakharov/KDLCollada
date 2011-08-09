#include "COLLADAKinModelSerialChainIterator.h"
#include <cmath>

using namespace COLLADAFW;
using namespace std;

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
    return kinMatrix.size();
}

Joint* COLLADAKinModelSerialChainIterator::getJoint()  // get current element
{
    return kinModelPtr->getJoints()[kinMatrix[current][current+1]];
}

TransformationPointerArray* COLLADAKinModelSerialChainIterator::getTransformationArray()
{
    return transformMatrix[current][kinMatrix[current][current+1]];

}

unsigned int COLLADAKinModelSerialChainIterator::getMaxJointIndex(const KinematicsModel::LinkJointConnections& linkJointConnArray)
{
    unsigned int joint;
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
    unsigned int link;
    for (unsigned int i = 0; i < linkJointConnArray.getCount(); i++)
    {
        KinematicsModel::LinkJointConnection* linkJointConnPtr = linkJointConnArray[i];
        unsigned int l = linkJointConnPtr->getLinkNumber();
        link = max(link,l);
    }
    return  link;
}

void COLLADAKinModelSerialChainIterator::initMatrix(unsigned int width, unsigned int height, std::vector< std::vector<TransformationPointerArray*> >& matrix)
{
    matrix.resize(width);
    for (unsigned int i = 0; i < width; i++)
    {
        matrix[i].resize(height);
    }
}

void COLLADAKinModelSerialChainIterator::initMatrix(unsigned int width, unsigned int height, std::vector< std::vector<unsigned int> >& matrix)
{
    matrix.resize(width);
    for (unsigned int i = 0; i < width; i++)
    {
        matrix[i].resize(height);
    }
}

void COLLADAKinModelSerialChainIterator::parseLinkJointConnections(unsigned int jointIndex, vector<KinematicsPair>& kinPairArray) //Here we assume that each joint has only 2 adjacent links
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
                unsigned int jIndex = linkJointConnPtr->getLinkNumber();
                kinPair.parentLink = jIndex;
                isParentLink = false;


            }
            else
            {
                unsigned int jIndex = linkJointConnPtr->getLinkNumber();
                kinPair.childLink = jIndex;
                isParentLink = true;
                kinPairArray.push_back(kinPair);
                kinMatrix[kinPair.parentLink][kinPair.childLink] = jointIndex;

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

void COLLADAKinModelSerialChainIterator::buildKinMatrix()
{
    unsigned int maxJointIndex = getMaxJointIndex(kinModelPtr->getLinkJointConnections());
    unsigned int linkNumber = getLinkNumber(kinModelPtr->getLinkJointConnections());

    initMatrix(linkNumber, linkNumber, kinMatrix);
    initMatrix(maxJointIndex+1, linkNumber, transformMatrix);
    buildTransformation();
    for (unsigned int i = 0; i <= maxJointIndex; i++)
    {
        vector<KinematicsPair> kinPairArray;
        parseLinkJointConnections(i, kinPairArray);

        /*    vector<unsigned int> links;
            getConnectedLinks(i, kinModelPtr->getLinkJointConnections(), links);
            KinematicsModel::LinkJointConnection* linkJointConnPtr = linkJointConnArray[i];
            unsigned int jointIndex = linkJointConnPtr->getJointIndex();
            unsigned int linkNumber = linkJointConnPtr->getLinkNumber();
            const TransformationPointerArray& transformArray = linkJointConnPtr->getTransformations();
            Joint* jointPtr = jointArray[jointIndex];
        #ifdef DEBUG
            cout << "joint index = " << jointIndex << " connected to " << " link number = " << linkNumber << endl;
            cout << "joint name: " << jointPtr->getName() << endl;
        #endif
            parseJointPrimitiveArray(jointPtr);
        */
    }


}
