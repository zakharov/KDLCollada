/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

	This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#include "COLLADASWStreamWriter.h"
#include "COLLADASWBindKinematicsModel.h"
#include "COLLADASWConstantsKinematicsExtension.h"
#include "Logger.h"

namespace COLLADASW
{

// ---------------------------------------------------
BindKinematicsModel::BindKinematicsModel (
    StreamWriter* streamWriter,
    const String& node,
    const String& param)
    : ElementWriter ( streamWriter )
    , BaseExtraTechnique ( )
    , mNode ( node )
    , mParam ( param )
{

}

// ---------------------------------------------------
BindKinematicsModel::BindKinematicsModel (const BindKinematicsModel& orig)
    : ElementWriter ( orig.mSW )
    , BaseExtraTechnique ( )
    , mNode ( orig.getNode( ))
    , mParam ( orig.getParam( ))
{

}

// ---------------------------------------------------

void BindKinematicsModel::start () const
{
    mSW->openElement ( CSWCKinematics::CSW_ELEMENT_BIND_KINEMATICS_MODEL );
    mSW->appendAttribute ( CSWCKinematics::CSW_ATTRIBUTE_NODE, getNode() );
    mSW->openElement ( CSWC::CSW_ELEMENT_PARAM );
    mSW->appendValues ( getParam() );
    mSW->closeElement();
}

void BindKinematicsModel::end () const
{

    mSW->closeElement();
}

void BindKinematicsModel::add () const
{
    start();
    end();
}


} //namespace COLLADASW
