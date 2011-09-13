/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

	This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#include "COLLADASWStreamWriter.h"
#include "COLLADASWInstanceKinematicsModel.h"
#include "COLLADASWConstantsKinematicsExtension.h"
#include "Logger.h"

namespace COLLADASW
{

// ---------------------------------------------------
InstanceKinematicsModel::InstanceKinematicsModel (
    StreamWriter* streamWriter,
    const String& instanceKinematicsModelURL,
    const String& instanceKinematicsModelSid)
    : ElementWriter ( streamWriter )
    , BaseExtraTechnique ( )
    , mInstanceKinematicsModelURL ( instanceKinematicsModelURL )
    , mInstanceKinematicsModelSid ( instanceKinematicsModelSid )

{}

// ---------------------------------------------------
InstanceKinematicsModel::InstanceKinematicsModel (const InstanceKinematicsModel& orig)
    : ElementWriter ( orig.mSW )
    , BaseExtraTechnique ( )
    , mInstanceKinematicsModelURL ( orig.getInstanceKinematicsModelURL() )
    , mInstanceKinematicsModelSid ( orig.getInstanceKinematicsModelSid() )

{

}

void InstanceKinematicsModel::start () const
{
    mSW->openElement ( CSWCKinematics::CSW_ELEMENT_INSTANCE_KINEMATICS_MODEL );
    mSW->appendAttribute ( CSWC::CSW_ATTRIBUTE_URL, getInstanceKinematicsModelURL() );
    mSW->appendAttribute ( CSWC::CSW_ATTRIBUTE_SID, getInstanceKinematicsModelSid() );

}

void InstanceKinematicsModel::end () const
{
    mSW->closeElement();
}

// ---------------------------------------------------
void InstanceKinematicsModel::add () const
{
    start();
    end();
}

} //namespace COLLADASW
