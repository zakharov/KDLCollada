/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

	This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#include "COLLADASWStreamWriter.h"
#include "COLLADASWNewparam.h"
#include "COLLADASWSIDREF.h"
#include "COLLADASWFloat.h"
#include "COLLADASWKinematicsScene.h"
#include "COLLADASWInstanceKinematicsModel.h"
#include "COLLADASWLibraryKinematicsScenes.h"
#include "COLLADASWConstantsKinematicsExtension.h"

namespace COLLADASW
{

//---------------------------------------------------------------
LibraryKinematicsScenes::LibraryKinematicsScenes ( COLLADASW::StreamWriter* streamWriter )
    : Library ( streamWriter, CSWCKinematics::CSW_ELEMENT_LIBRARY_KINEMATICS_SCENENS )
    , BaseExtraTechnique()
{}

//---------------------------------------------------------------
void LibraryKinematicsScenes::addKinematicsScene ( const KinematicsScene& kinematicsScene )
{
    startKinematicsScene ( kinematicsScene );
    endKinematicsScene ( kinematicsScene );
}

void LibraryKinematicsScenes::startKinematicsScene ( const KinematicsScene& kinematicsScene )
{
    openLibrary();
    kinematicsScene.start();
}

void LibraryKinematicsScenes::endKinematicsScene ( const KinematicsScene& kinematicsScene )
{
    kinematicsScene.end();
}


void LibraryKinematicsScenes::addInstanceKinematicsModel ( const InstanceKinematicsModel& instanceKinematicsModel )
{
    instanceKinematicsModel.start();
    instanceKinematicsModel.end();
}

void LibraryKinematicsScenes::startInstanceKinematicsModel ( const InstanceKinematicsModel& instanceKinematicsModel )
{
    instanceKinematicsModel.start();
}

void LibraryKinematicsScenes::endInstanceKinematicsModel ( const InstanceKinematicsModel& instanceKinematicsModel )
{
    instanceKinematicsModel.end();
}

void LibraryKinematicsScenes::startNewparam ( const Newparam& newparam )
{
    newparam.start();
}

void LibraryKinematicsScenes::endNewparam ( const Newparam& newparam )
{
    newparam.end();
}

void LibraryKinematicsScenes::addNewparam ( const Newparam& newparam )
{
    newparam.start();
    newparam.end();
}

void LibraryKinematicsScenes::addSIDREF ( const SIDREF& sidref )
{
    sidref.add();
}

void LibraryKinematicsScenes::addFloat ( const Float& value )
{
    value.add();
}

} //namespace COLLADASW
