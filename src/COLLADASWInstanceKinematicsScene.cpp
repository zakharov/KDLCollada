/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

	This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#include "COLLADASWStreamWriter.h"
#include "COLLADASWInstanceKinematicsScene.h"
#include "COLLADASWConstantsKinematicsExtension.h"
#include "Logger.h"

namespace COLLADASW
{

// ---------------------------------------------------
InstanceKinematicsScene::InstanceKinematicsScene (
    StreamWriter* streamWriter,
    const String& instanceKinematicsSceneURL)
    : ElementWriter ( streamWriter )
    , BaseExtraTechnique ( )
    , mInstanceKinematicsSceneURL ( instanceKinematicsSceneURL )
{}

// ---------------------------------------------------
InstanceKinematicsScene::InstanceKinematicsScene (const InstanceKinematicsScene& orig)
    : ElementWriter ( orig.mSW )
    , BaseExtraTechnique ( )
    , mInstanceKinematicsSceneURL ( orig.getInstanceKinematicsSceneURL())

{

}

void InstanceKinematicsScene::start () const
{
    mSW->openElement ( CSWCKinematics::CSW_ELEMENT_INSTANCE_KINEMATICS_SCENE );
    mSW->appendAttribute ( CSWC::CSW_ATTRIBUTE_URL, getInstanceKinematicsSceneURL() );


}

void InstanceKinematicsScene::end () const
{
    mSW->closeElement();
}

void InstanceKinematicsScene::add () const
// ---------------------------------------------------
{
    start();
    end();
}

} //namespace COLLADASW
