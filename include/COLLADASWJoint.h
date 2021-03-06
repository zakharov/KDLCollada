/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

    This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#ifndef __COLLADASTREAMWRITER_JOINT_H__
#define __COLLADASTREAMWRITER_JOINT_H__

#include "COLLADASWPrerequisites.h"
#include "COLLADASWStreamWriter.h"
#include "COLLADASWExtraTechnique.h"
#include "COLLADASWConstants.h"
#include "COLLADASWCameraOptic.h"
#include "COLLADAFWJointPrimitive.h"

namespace COLLADASW
{

    /** A class that hold all information about an @a \<joint\> element.*/
    class Joint : public ElementWriter, public BaseExtraTechnique
    {

    private:

        // LibraryJoints should be able to call the add() method.
        friend class LibraryJoints;

//        BaseOptic* mOptics;

        COLLADAFW::JointPrimitive mJointPrimitive;

        String mJointId;

        String mJointName;



    protected:

        /** Adds the joint information. */
        void add() const;

    public:

        /**
        * Constructor
        * @param cameraId The id of the camera.
        * @param cameraName The name of the camera.
        */
        Joint (
            StreamWriter* streamWriter,
            const COLLADAFW::JointPrimitive& jointPrimitive,
            const String& jointId = ElementWriter::EMPTY_STRING,
            const String& jointName = ElementWriter::EMPTY_STRING);

        /** Copy constructor **/
        Joint (const Joint& orig);

        /** Destructor */
        virtual ~Joint()
        { }

        const String& getJointId() const { return mJointId; }
        const String& getJointName() const { return mJointName; }
        void setJointPrimitive(const COLLADAFW::JointPrimitive& jointPrimitive) { mJointPrimitive = jointPrimitive; };
        const COLLADAFW::JointPrimitive& getJointPrimitive() const { return mJointPrimitive; };
//        const BaseOptic* getOptics() const { return mOptics; }

    };

} //namespace COLLADASW

#endif //__COLLADASTREAMWRITER_JOINT_H__
