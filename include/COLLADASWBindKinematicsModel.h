/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

    This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#ifndef __COLLADASTREAMWRITER_BIND_KINEMATICS_MODEL_H__
#define __COLLADASTREAMWRITER_BIND_KINEMATICS_MODEL_H__

#include "COLLADASWPrerequisites.h"
#include "COLLADASWStreamWriter.h"
#include "COLLADASWExtraTechnique.h"
#include "COLLADASWConstants.h"

namespace COLLADASW
{

    /** A class that hold all information about an @a \<joint\> element.*/
    class BindKinematicsModel : public ElementWriter, public BaseExtraTechnique
    {

    private:

        String mNode;
        String mParam;

    public:

        /** Adds the joint information. */
        void add() const;
        void start () const;
        void end () const;

    public:

        /**
        * Constructor
        * @param cameraId The id of the camera.
        * @param cameraName The name of the camera.
        */
        BindKinematicsModel (
            StreamWriter* streamWriter,
            const String& mNode = ElementWriter::EMPTY_STRING,
            const String& mParam = ElementWriter::EMPTY_STRING);

        /** Copy constructor **/
        BindKinematicsModel (const BindKinematicsModel& orig);

        /** Destructor */
        virtual ~BindKinematicsModel()
        { }

        const String& getNode() const { return mNode; }
        const String& getParam() const { return mParam; }

    };

} //namespace COLLADASW

#endif //__COLLADASTREAMWRITER_JOINT_H__
