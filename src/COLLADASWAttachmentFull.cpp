/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

	This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#include "COLLADASWStreamWriter.h"
#include "COLLADASWAttachmentFull.h"
#include "COLLADASWConstantsKinematicsExtension.h"
#include "Logger.h"

namespace COLLADASW
{

// ---------------------------------------------------
AttachmentFull::AttachmentFull (
    StreamWriter* streamWriter,
    const String& joint)
    : ElementWriter ( streamWriter )
    , BaseExtraTechnique ( )
    , mJoint ( joint )
{

}

// ---------------------------------------------------
AttachmentFull::AttachmentFull (const AttachmentFull& orig)
    : ElementWriter ( orig.mSW )
    , BaseExtraTechnique ( )
    , mJoint ( orig.getJoint() )
{

}

// ---------------------------------------------------
void AttachmentFull::add () const
{
    start();
    end();
}

void AttachmentFull::start() const
{
    mSW->openElement ( CSWCKinematics::CSW_ELEMENT_ATTACHMENT_FULL );
    mSW->appendAttribute ( CSWCKinematics::CSW_ATTRIBUTE_JOINT, mJoint );
}

void AttachmentFull::end() const
{
    mSW->closeElement();
}

} //namespace COLLADASW
