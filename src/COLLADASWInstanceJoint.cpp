/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

	This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#include "COLLADASWStreamWriter.h"
#include "COLLADASWInstanceJoint.h"
#include "COLLADASWConstantsKinematicsExtension.h"
#include "Logger.h"

namespace COLLADASW
{

// ---------------------------------------------------
InstanceJoint::InstanceJoint (
    StreamWriter* streamWriter,
   // const COLLADAFW::JointPrimitive& jointPrimitive,
    const String& instanceJointUrl,
    const String& instanceJointSid)
    : ElementWriter ( streamWriter )
    , BaseExtraTechnique ( )
  //  , mJointPrimitive ( jointPrimitive )
    , mInstanceJointUrl ( instanceJointUrl )
    , mInstanceJointSid ( instanceJointSid )
{
    LOG(DEBUG) << "URL: " << mInstanceJointUrl;
}

// ---------------------------------------------------
InstanceJoint::InstanceJoint (const InstanceJoint& orig)
    : ElementWriter ( orig.mSW )
    , BaseExtraTechnique ( )
    , mInstanceJointUrl ( orig.getInstanceJointUrl() )
    , mInstanceJointSid ( orig.getInstanceJointSid() )
{
    LOG(DEBUG) << "URL: " << mInstanceJointUrl;
    LOG(DEBUG) << "Sid: " << mInstanceJointSid;
}

// ---------------------------------------------------

void InstanceJoint::add () const
{
    mSW->openElement ( CSWCKinematics::CSW_ELEMENT_INSTANCE_JOINT );
    mSW->appendAttribute ( CSWC::CSW_ATTRIBUTE_URL, getInstanceJointUrl() );
    mSW->appendAttribute ( CSWC::CSW_ATTRIBUTE_SID, getInstanceJointSid() );
    mSW->closeElement();
}

} //namespace COLLADASW
