/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

    This file is part of KDLColladaParser.
    
    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#ifndef __COLLADASTREAMWRITER_LIBRARY_JOINTS_H__
#define __COLLADASTREAMWRITER_LIBRARY_JOINTS_H__

#include "COLLADASWPrerequisites.h"
#include "COLLADASWExtraTechnique.h"
#include "COLLADASWLibrary.h"
#include "COLLADASWJoint.h"

namespace COLLADASW
{

    /** Class to simply the creation of @a \<library_joints\> and @a \<joints\>'s*/
    class LibraryJoints : public Library, public BaseExtraTechnique
    {

    public:
        /** Constructor
        @param streamWriter The stream the @a \<library_joints\> and @a \<joints\>'s
        should be written to.
        */
        LibraryJoints ( StreamWriter* streamWriter );

        /** Destructor*/
        virtual ~LibraryJoints() {}

    protected:

        /** Adds @a \<joint\> element. If not already opened, it opens @a \<library_joints\>*/
        void addJoint ( const Joint& joint );

    };

} //namespace COLLADASW

#endif //__COLLADASTREAMWRITER_LIBRARY_CAMERAS_H__
