/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

    This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#ifndef __COLLADASTREAMWRITER_INSTANCE_KINEMATICS_MODEL_H__
#define __COLLADASTREAMWRITER_INSTANCE_KINEMATICS_MODEL_H__

#include "COLLADASWPrerequisites.h"
#include "COLLADASWStreamWriter.h"
#include "COLLADASWExtraTechnique.h"
#include "COLLADASWConstants.h"

namespace COLLADASW
{

    /** A class that hold all information about an @a \<kinematics_model\> element.*/
    class InstanceKinematicsModel : public ElementWriter, public BaseExtraTechnique
    {

    private:

        // LibraryJoints should be able to call the add() method.
        friend class LibraryKinematicsScenes;

        String mInstanceKinematicsModelURL;
        String mInstanceKinematicsModelSid;

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
        InstanceKinematicsModel (
            StreamWriter* streamWriter,
            const String& mInstanceKinematicsModelURL = ElementWriter::EMPTY_STRING,
            const String& mInstanceKinematicsModelSid = ElementWriter::EMPTY_STRING);

        /** Copy constructor **/
        InstanceKinematicsModel (const InstanceKinematicsModel& orig);

        /** Destructor */
        virtual ~InstanceKinematicsModel()
        { }

        const String& getInstanceKinematicsModelSid() const { return mInstanceKinematicsModelSid; }
        const String& getInstanceKinematicsModelURL() const { return mInstanceKinematicsModelURL; }


    };

} //namespace COLLADASW

#endif //__COLLADASTREAMWRITER_KINEMATICS_MODEL_H__
