/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

	This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#include "COLLADASWStreamWriter.h"
#include "COLLADASWBindJointAxis.h"
#include "COLLADASWConstantsKinematicsExtension.h"
#include "Logger.h"

namespace COLLADASW
{

// ---------------------------------------------------
BindJointAxis::BindJointAxis (
    StreamWriter* streamWriter,
    const String& target,
    const String& axis,
    const String& value)
    : ElementWriter ( streamWriter )
    , BaseExtraTechnique ( )
    , mTarget ( target )
    , mAxis ( axis )
    , mValue ( value )
{

}

// ---------------------------------------------------
BindJointAxis::BindJointAxis (const BindJointAxis& orig)
    : ElementWriter ( orig.mSW )
    , BaseExtraTechnique ( )
    , mTarget ( orig.getTarget() )
    , mAxis ( orig.getAxis() )
    , mValue ( orig.getValue() )
{

}

// ---------------------------------------------------

void BindJointAxis::start () const
{
 //   mSW->openElement ( CSWC::CSW_ELEMENT_NEWPARAM );
 //   mSW->appendAttribute ( CSWC::CSW_ATTRIBUTE_SID, getNewparamSid() );

}

void BindJointAxis::end () const
{
    mSW->closeElement();
}

void BindJointAxis::add () const
{
    start();
    end();
}


} //namespace COLLADASW
