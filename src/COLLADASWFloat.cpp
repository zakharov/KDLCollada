/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

	This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#include "COLLADASWStreamWriter.h"
#include "COLLADASWFloat.h"
#include "COLLADASWConstantsKinematicsExtension.h"
#include "Logger.h"

namespace COLLADASW
{

// ---------------------------------------------------
Float::Float (
    StreamWriter* streamWriter,
    double value)
    : ElementWriter ( streamWriter )
    , BaseExtraTechnique ( )
    , mValue ( value )
{

}

// ---------------------------------------------------
Float::Float (const Float& orig)
    : ElementWriter ( orig.mSW )
    , BaseExtraTechnique ( )
    , mValue ( orig.getValue() )
{

}

// ---------------------------------------------------

void Float::add () const
{
    mSW->openElement ( CSWC::CSW_ELEMENT_FLOAT );
    mSW->appendValues( getValue() );
    mSW->closeElement();
}


} //namespace COLLADASW
