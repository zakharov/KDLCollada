/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

    This file is part of KDLColladaParser.
    
    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#ifndef COLLADAKINMODELSERIALCHAINITERATOR_H
#define COLLADAKINMODELSERIALCHAINITERATOR_H

#include <vector>
#include <kdl/chain.hpp>
#include "COLLADAFW.h"

class COLLADAKinModelSerialChainIterator
{
    typedef unsigned int LinkIndex;
    typedef unsigned int JointIndex;
    struct KinematicsPair;
public:

    COLLADAKinModelSerialChainIterator(COLLADAFW::KinematicsModel* kinModelPtr);
    virtual ~COLLADAKinModelSerialChainIterator();

    bool next();
    bool previous();
    void reset();
    unsigned int size();
    COLLADAFW::Joint* getJoint();  // get current element
    COLLADAFW::TransformationPointerArray* getTransformationArray();

private:
    struct KinematicsPair
    {
        unsigned int parentLink;
        unsigned int childLink;
    };

    unsigned int getMaxJointIndex(const COLLADAFW::KinematicsModel::LinkJointConnections& linkJointConnArray);
    unsigned int getLinkNumber(const COLLADAFW::KinematicsModel::LinkJointConnections& linkJointConnArray);

    template <class T>
    //void initMatrix(unsigned int width, unsigned int height, std::vector< std::vector<T> >& matrix);
    void initMatrix(unsigned int width, unsigned int height, std::vector< std::vector<T> >& matrix, T defaultValue);
    void parseLinkJointConnections(unsigned int jointIndex);
    void parseJointPrimitiveArray(COLLADAFW::Joint* jointPtr, KDL::Joint::JointType& jointType, KDL::Vector& jointAxis);

    //void buildTransformation();
    void buildKinMatrix();

    void getKinematicsPair();
    std::vector< std::vector<int> > kinMatrix;
    std::vector< std::vector<COLLADAFW::TransformationPointerArray*> > transformMatrix;
    COLLADAFW::KinematicsModel* kinModelPtr;
    unsigned int current;

};



#endif // COLLADAKINMODELSERIALCHAINITERATOR_H
