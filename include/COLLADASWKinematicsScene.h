/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

    This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#ifndef __COLLADASTREAMWRITER_KINEMATICS_MODEL_H__
#define __COLLADASTREAMWRITER_JOINT_H__

#include "COLLADASWPrerequisites.h"
#include "COLLADASWStreamWriter.h"
#include "COLLADASWExtraTechnique.h"
#include "COLLADASWConstants.h"

namespace COLLADASW
{

    /** A class that hold all information about an @a \<kinematics_model\> element.*/
    class KinematicsScene : public ElementWriter, public BaseExtraTechnique
    {

    private:

        // LibraryJoints should be able to call the add() method.
        friend class LibraryKinematicsScenes;

        String mKinematicsSceneId;



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
        KinematicsScene (
            StreamWriter* streamWriter,
            const String& kinematicsSceneId = ElementWriter::EMPTY_STRING);

        /** Copy constructor **/
        KinematicsScene (const KinematicsScene& orig);

        /** Destructor */
        virtual ~KinematicsScene()
        { }

        const String& getKinematicsSceneId() const { return mKinematicsSceneId; }


    };

} //namespace COLLADASW

#endif //__COLLADASTREAMWRITER_KINEMATICS_MODEL_H__
