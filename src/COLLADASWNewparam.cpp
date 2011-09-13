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
#include "COLLADASWConstantsKinematicsExtension.h"
#include "Logger.h"

namespace COLLADASW
{

// ---------------------------------------------------
Newparam::Newparam (
    StreamWriter* streamWriter,
    const String& newparamSid)
    : ElementWriter ( streamWriter )
    , BaseExtraTechnique ( )
    , mNewparamSid ( newparamSid )
{

}

// ---------------------------------------------------
Newparam::Newparam (const Newparam& orig)
    : ElementWriter ( orig.mSW )
    , BaseExtraTechnique ( )
    , mNewparamSid ( orig.getNewparamSid() )
{

}

// ---------------------------------------------------

void Newparam::start () const
{
    mSW->openElement ( CSWC::CSW_ELEMENT_NEWPARAM );
    mSW->appendAttribute ( CSWC::CSW_ATTRIBUTE_SID, getNewparamSid() );

}

void Newparam::end () const
{
    mSW->closeElement();
}

void Newparam::add () const
{
    start();
    end();
}


} //namespace COLLADASW
