/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

	This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#include "COLLADASWStreamWriter.h"
#include "COLLADASWKinematicsModel.h"
#include "COLLADASWConstantsKinematicsExtension.h"
#include "Logger.h"

namespace COLLADASW
{

// ---------------------------------------------------
KinematicsModel::KinematicsModel (
    StreamWriter* streamWriter,
    const String& kinematicsModelId,
    const String& kinematicsModelName)
    : ElementWriter ( streamWriter )
    , BaseExtraTechnique ( )
    , mKinematicsModelId ( kinematicsModelId )

{}

// ---------------------------------------------------
KinematicsModel::KinematicsModel (const KinematicsModel& orig)
    : ElementWriter ( orig.mSW )
    , BaseExtraTechnique ( )
    , mKinematicsModelId ( orig.getKinematicsModelId() )

{

}

void KinematicsModel::start () const
{
    mSW->openElement ( CSWCKinematics::CSW_ELEMENT_KINEMATICS_MODEL );
    mSW->appendAttribute ( CSWC::CSW_ATTRIBUTE_ID, mKinematicsModelId );
    mSW->openElement( CSWC::CSW_ELEMENT_TECHNIQUE_COMMON );

}

void KinematicsModel::end () const
{
    mSW->closeElement();
    mSW->closeElement();
}

// ---------------------------------------------------
void KinematicsModel::add () const
{
    start();
    end();
}

} //namespace COLLADASW
