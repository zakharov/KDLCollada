/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

	This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#include "COLLADASWStreamWriter.h"
#include "COLLADASWTranslate.h"
#include "COLLADASWConstantsKinematicsExtension.h"
#include "Logger.h"

namespace COLLADASW
{

// ---------------------------------------------------
Translate::Translate (
    StreamWriter* streamWriter,
    double x,
    double y,
    double z,
    const String& translateSid)
    : ElementWriter ( streamWriter )
    , BaseExtraTechnique ( )
    , mX (x)
    , mY (y)
    , mZ (z)
    , mTranslateSid ( translateSid )
{
}

// ---------------------------------------------------
Translate::Translate (const Translate& orig)
    : ElementWriter ( orig.mSW )
    , BaseExtraTechnique ( )
    , mX ( orig.getX() )
    , mY ( orig.getY() )
    , mZ ( orig.getZ() )
    , mTranslateSid ( orig.getTranslateSid() )
{

}

// ---------------------------------------------------
void Translate::add () const
{
    mSW->openElement ( CSWC::CSW_ELEMENT_TRANSLATE );

    if ( !getTranslateSid().empty() )
        mSW->appendAttribute ( CSWC::CSW_ATTRIBUTE_SID, getTranslateSid() );

    mSW->appendValues (mX, mY, mZ);
    mSW->closeElement();
}


} //namespace COLLADASW
