/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

	This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#include "COLLADASWStreamWriter.h"
#include "COLLADASWSIDREF.h"
#include "COLLADASWConstantsKinematicsExtension.h"
#include "Logger.h"

namespace COLLADASW
{

// ---------------------------------------------------
SIDREF::SIDREF (
    StreamWriter* streamWriter,
    const String& path )
    : ElementWriter ( streamWriter )
    , BaseExtraTechnique ( )
    , mPath ( path )
{

}

// ---------------------------------------------------
SIDREF::SIDREF (const SIDREF& orig)
    : ElementWriter ( orig.mSW )
    , BaseExtraTechnique ( )
    , mPath ( orig.getPath() )
{

}

// ---------------------------------------------------

void SIDREF::add () const
{
    mSW->openElement ( CSWCKinematics::CSW_ELEMENT_SIDREF );
    mSW->appendValues ( getPath() );
    mSW->closeElement();
}

} //namespace COLLADASW
