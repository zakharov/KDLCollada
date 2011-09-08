/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

	This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#include "COLLADASWStreamWriter.h"
#include "COLLADASWRotate.h"
#include "COLLADASWConstantsKinematicsExtension.h"
#include "Logger.h"

namespace COLLADASW
{

// ---------------------------------------------------
Rotate::Rotate (
    StreamWriter* streamWriter,
    double x,
    double y,
    double z,
    double w,
    const String& rotateSid)
    : ElementWriter ( streamWriter )
    , BaseExtraTechnique ( )
    , mX (x)
    , mY (y)
    , mZ (z)
    , mW (w)
    , mRotateSid ( rotateSid )
{
}

// ---------------------------------------------------
Rotate::Rotate (const Rotate& orig)
    : ElementWriter ( orig.mSW )
    , BaseExtraTechnique ( )
    , mX ( orig.getX() )
    , mY ( orig.getY() )
    , mZ ( orig.getZ() )
    , mW ( orig.getW() )
    , mRotateSid ( orig.getRotateSid() )
{

}

// ---------------------------------------------------
void Rotate::add () const
{
    mSW->openElement ( CSWC::CSW_ELEMENT_ROTATE);

    if ( !getRotateSid().empty() )
        mSW->appendAttribute ( CSWC::CSW_ATTRIBUTE_SID, getRotateSid() );

    mSW->appendValues (mX, mY, mZ, mW);
    mSW->closeElement();
}


} //namespace COLLADASW
