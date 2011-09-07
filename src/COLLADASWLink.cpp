/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

	This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#include "COLLADASWStreamWriter.h"
#include "COLLADASWLink.h"
#include "COLLADASWConstantsKinematicsExtension.h"
#include "Logger.h"

namespace COLLADASW
{

// ---------------------------------------------------
Link::Link (
    StreamWriter* streamWriter,
    const String& linkSid,
    const String& linkJointName)
    : ElementWriter ( streamWriter )
    , BaseExtraTechnique ( )
    , mLinkSid ( linkSid )
    , mLinkName ( linkJointName )
{

}

// ---------------------------------------------------
Link::Link (const Link& orig)
    : ElementWriter ( orig.mSW )
    , BaseExtraTechnique ( )
    , mLinkSid ( orig.getLinkSid() )
    , mLinkName ( orig.getLinkName() )
{

}

void Link::start() const
{
    mSW->openElement ( CSWCKinematics::CSW_ELEMENT_LINK );
    mSW->appendAttribute ( CSWC::CSW_ATTRIBUTE_SID, mLinkSid );
    mSW->appendAttribute ( CSWC::CSW_ATTRIBUTE_NAME, mLinkName );
 }

void Link::end() const
{
   mSW->closeElement();
}

// ---------------------------------------------------
void Link::add () const
{
    start();
    end();
}

} //namespace COLLADASW

