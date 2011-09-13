/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

	This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#include "COLLADASWStreamWriter.h"
#include "COLLADASWKinematicsScene.h"
#include "COLLADASWConstantsKinematicsExtension.h"
#include "Logger.h"

namespace COLLADASW
{

// ---------------------------------------------------
KinematicsScene::KinematicsScene (
    StreamWriter* streamWriter,
    const String& kinematicsSceneId)
    : ElementWriter ( streamWriter )
    , BaseExtraTechnique ( )
    , mKinematicsSceneId ( kinematicsSceneId )

{}

// ---------------------------------------------------
KinematicsScene::KinematicsScene (const KinematicsScene& orig)
    : ElementWriter ( orig.mSW )
    , BaseExtraTechnique ( )
    , mKinematicsSceneId ( orig.getKinematicsSceneId() )

{

}

void KinematicsScene::start () const
{
    mSW->openElement ( CSWCKinematics::CSW_ELEMENT_KINEMATICS_SCENE );
    mSW->appendAttribute ( CSWC::CSW_ATTRIBUTE_ID, mKinematicsSceneId );

}

void KinematicsScene::end () const
{
    mSW->closeElement();
}

// ---------------------------------------------------
void KinematicsScene::add () const
{
    start();
    end();
}



} //namespace COLLADASW
