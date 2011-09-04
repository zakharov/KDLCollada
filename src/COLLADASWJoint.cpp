/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

	This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#include "COLLADASWStreamWriter.h"
#include "COLLADASWJoint.h"
#include "COLLADASWConstantsKinematicsExtension.h"

namespace COLLADASW
{

// ---------------------------------------------------
Joint::Joint (
    StreamWriter* streamWriter,
    // JointPrimitive* jointPrimitive,
    const String& jointId,
    const String& jointName )
    : ElementWriter ( streamWriter )
    , BaseExtraTechnique ( )
    //, mJointPrimitive ( jointPrimitive )
    , mJointId ( jointId )
    , mJointName ( jointName )
{}

// ---------------------------------------------------
void Joint::add () const
{

    mSW->openElement ( CSWCKinematics::CSW_ELEMENT_JOINT );

    if ( !getJointId().empty() )
        mSW->appendAttribute ( CSWC::CSW_ATTRIBUTE_ID, getJointId() );

    if ( !getJointName().empty() )
        mSW->appendAttribute ( CSWC::CSW_ATTRIBUTE_NAME, getJointName() );

    // Write the optics element
    // mOptics->add ();

    // addExtraTechniques ( mSW );

    mSW->closeElement(); // COLLADASW_ELEMENT_CAMERA

}


} //namespace COLLADASW
