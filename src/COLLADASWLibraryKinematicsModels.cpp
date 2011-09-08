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
#include "COLLADASWInstanceJoint.h"
#include "COLLADASWLink.h"
#include "COLLADASWRotate.h"
#include "COLLADASWTranslate.h"
#include "COLLADASWAttachmentFull.h"
#include "COLLADASWLibraryKinematicsModels.h"
#include "COLLADASWConstantsKinematicsExtension.h"

namespace COLLADASW
{

//---------------------------------------------------------------
LibraryKinematicsModels::LibraryKinematicsModels ( COLLADASW::StreamWriter* streamWriter )
    : Library ( streamWriter, CSWCKinematics::CSW_ELEMENT_LIBRARY_KINEMATICS_MODELS )
    , BaseExtraTechnique()
{}


//---------------------------------------------------------------
void LibraryKinematicsModels::addKinematicsModel ( const KinematicsModel& kinematicsModel )
{
    startKinematicsModel ( kinematicsModel );
    endKinematicsModel ( kinematicsModel );
}

void LibraryKinematicsModels::startKinematicsModel ( const KinematicsModel& kinematicsModel )
{
    openLibrary();
    kinematicsModel.start();
}

void LibraryKinematicsModels::endKinematicsModel ( const KinematicsModel& kinematicsModel )
{
    kinematicsModel.end();
}

void LibraryKinematicsModels::addInstanceJoint ( const InstanceJoint& instanceJoint )
{
    instanceJoint.add();
}

void LibraryKinematicsModels::startLink( const Link& link)
{
    link.start();
}

void LibraryKinematicsModels::endLink( const Link& link)
{
    link.end();
}

void LibraryKinematicsModels::addLink( const Link& link)
{
    startLink(link);
    endLink(link);
}

void LibraryKinematicsModels::startAttachmentFull( const AttachmentFull& attachmentFull)
{
    attachmentFull.start();
}

void LibraryKinematicsModels::endAttachmentFull( const AttachmentFull& attachmentFull)
{
    attachmentFull.end();
}

void LibraryKinematicsModels::addAttachmentFull( const AttachmentFull& attachmentFull)
{
    startAttachmentFull(attachmentFull);
    endAttachmentFull(attachmentFull);
}

void LibraryKinematicsModels::addTranslate( const Translate& translate )
{
    translate.add();
}

void LibraryKinematicsModels::addRotate( const Rotate& rotate )
{
    rotate.add();
}



} //namespace COLLADASW
