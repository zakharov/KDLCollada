/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

    This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#ifndef __COLLADASTREAMWRITER_ATTACHMENT_FULL_H__
#define __COLLADASTREAMWRITER_ATTACHMENT_FULL_H__

#include "COLLADASWPrerequisites.h"
#include "COLLADASWStreamWriter.h"
#include "COLLADASWExtraTechnique.h"
#include "COLLADASWConstants.h"

namespace COLLADASW
{

    /** A class that hold all information about an @a \<joint\> element.*/
    class AttachmentFull : public ElementWriter, public BaseExtraTechnique
    {

    private:

        // LibraryJoints should be able to call the add() method.
        friend class LibraryKinematicsModel;

        String mJoint;

    public:

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
        AttachmentFull (
            StreamWriter* streamWriter,
            const String& joint = ElementWriter::EMPTY_STRING);

        /** Copy constructor **/
        AttachmentFull (const AttachmentFull& orig);

        /** Destructor */
        virtual ~AttachmentFull()
        { }

        const String& getJoint() const { return mJoint; }
    };

} //namespace COLLADASW

#endif //__COLLADASTREAMWRITER_JOINT_H__
