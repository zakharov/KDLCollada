/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

    This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#ifndef __COLLADASTREAMWRITER_LINK_H__
#define __COLLADASTREAMWRITER_LINK_H__

#include "COLLADASWPrerequisites.h"
#include "COLLADASWStreamWriter.h"
#include "COLLADASWExtraTechnique.h"
#include "COLLADASWConstants.h"
#include "COLLADASWCameraOptic.h"
#include "COLLADAFWJointPrimitive.h"

namespace COLLADASW
{

    /** A class that hold all information about an @a \<joint\> element.*/
    class Link : public ElementWriter, public BaseExtraTechnique
    {

    private:

        // LibraryJoints should be able to call the add() method.
        friend class LibraryKinematicsModels;

        String mLinkSid;

        String mLinkName;

    protected:

        /** Adds the joint information. */
        void add() const;
        void start() const;
        void end() const;

    public:

        /**
        * Constructor
        * @param cameraId The id of the camera.
        * @param cameraName The name of the camera.
        */
        Link (
            StreamWriter* streamWriter,
            const String& linkSid = ElementWriter::EMPTY_STRING,
            const String& linkName = ElementWriter::EMPTY_STRING);

        /** Copy constructor **/
        Link (const Link& orig);

        /** Destructor */
        virtual ~Link()
        { }

        const String& getLinkSid() const { return mLinkSid; }
        const String& getLinkName() const { return mLinkName; }

    };

} //namespace COLLADASW

#endif //__COLLADASTREAMWRITER_JOINT_H__
