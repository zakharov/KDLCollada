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
#include "Logger.h"

namespace COLLADASW
{

// ---------------------------------------------------
Joint::Joint (
    StreamWriter* streamWriter,
    const COLLADAFW::JointPrimitive& jointPrimitive,
    const String& jointId,
    const String& jointName)
    : ElementWriter ( streamWriter )
    , BaseExtraTechnique ( )
    , mJointPrimitive ( jointPrimitive )
    , mJointId ( jointId )
    , mJointName ( jointName )
{
}

// ---------------------------------------------------
Joint::Joint (const Joint& orig)
    : ElementWriter ( orig.mSW )
    , BaseExtraTechnique ( )
    , mJointPrimitive ( orig.getJointPrimitive() )
    , mJointId ( orig.getJointId() )
    , mJointName ( orig.getJointName() )
{

}

// ---------------------------------------------------
void Joint::add () const
{

    mSW->openElement ( CSWCKinematics::CSW_ELEMENT_JOINT );

    if ( !getJointId().empty() )
        mSW->appendAttribute ( CSWC::CSW_ATTRIBUTE_ID, getJointId() );

    if ( !getJointName().empty() )
        mSW->appendAttribute ( CSWC::CSW_ATTRIBUTE_NAME, getJointName() );

    bool isJointPrimitiveTagOpen = true;
    switch (mJointPrimitive.getType())
    {
        case COLLADAFW::JointPrimitive::REVOLUTE :
            mSW->openElement(CSWCKinematics::CSW_ELEMENT_REVOLUTE);
            break;
        case COLLADAFW::JointPrimitive::PRISMATIC :
            mSW->openElement(CSWCKinematics::CSW_ELEMENT_PRISMATIC);
            break;
        default :
            LOG(ERROR) << "Joint primitive is missing";
            isJointPrimitiveTagOpen = false;
    }

    if (isJointPrimitiveTagOpen)
    {
        mSW->appendAttribute (CSWC::CSW_ATTRIBUTE_SID, "axis"); // TODO:: chainge that

        mSW->openElement (CSWCKinematics::CSW_ELEMENT_AXIS);
        mSW->appendValues (mJointPrimitive.getAxis()[0], mJointPrimitive.getAxis()[1], mJointPrimitive.getAxis()[2]);
        mSW->closeElement();

        if (!isnan(mJointPrimitive.getHardLimitMin()) && !isnan(mJointPrimitive.getHardLimitMax()))
        {
            mSW->openElement (CSWCKinematics::CSW_ELEMENT_LIMITS);

            mSW->openElement (CSWCKinematics::CSW_ELEMENT_MIN);
            mSW->appendValues (mJointPrimitive.getHardLimitMin());
            mSW->closeElement();

            mSW->openElement (CSWCKinematics::CSW_ELEMENT_MAX);
            mSW->appendValues (mJointPrimitive.getHardLimitMax());
            mSW->closeElement();

            mSW->closeElement();
        }
        else
            LOG(WARNING) << "Joint primitive has no NaN limit values, skipping limits.";



        mSW->closeElement();
    }


 /*   if (jointType != CSWCKinematics::CSW_ERR_UNKNOWN_INPUT)
    {
        mSW->openElement(jointType);
        msW->closeElement();
    }
*/
    // Write the optics element
    // mOptics->add ();

    // addExtraTechniques ( mSW );

    mSW->closeElement(); // COLLADASW_ELEMENT_JOINT

}


} //namespace COLLADASW
