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
    class InstanceKinematicsScene : public ElementWriter, public BaseExtraTechnique
    {

    public:

        // LibraryJoints should be able to call the add() method.

        String mInstanceKinematicsSceneURL;
        String mInstanceKinematicsSceneSid;

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
        InstanceKinematicsScene (
            StreamWriter* streamWriter,
            const String& mInstanceKinematicsModelURL = ElementWriter::EMPTY_STRING);

        /** Copy constructor **/
        InstanceKinematicsScene (const InstanceKinematicsScene& orig);

        /** Destructor */
        virtual ~InstanceKinematicsScene()
        { }

        const String& getInstanceKinematicsSceneURL() const { return mInstanceKinematicsSceneURL; }


    };

} //namespace COLLADASW

#endif //__COLLADASTREAMWRITER_KINEMATICS_MODEL_H__
