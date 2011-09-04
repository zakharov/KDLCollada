/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

	This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#include "COLLADASWStreamWriter.h"
#include "COLLADASWLibraryJoints.h"
#include "COLLADASWConstantsKinematicsExtension.h"

namespace COLLADASW
{

//---------------------------------------------------------------
LibraryJoints::LibraryJoints ( COLLADASW::StreamWriter* streamWriter )
    : Library ( streamWriter, CSWCKinematics::CSW_ELEMENT_LIBRARY_JOINTS )
    , BaseExtraTechnique()
{}


//---------------------------------------------------------------
void LibraryJoints::addJoint ( const Joint& joint )
{
    openLibrary();
    joint.add();
}


} //namespace COLLADASW
