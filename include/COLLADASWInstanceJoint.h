/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

    This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#ifndef __COLLADASTREAMWRITER_INSTANCE_JOINT_H__
#define __COLLADASTREAMWRITER_INSTANCE_JOINT_H__

#include "COLLADASWPrerequisites.h"
#include "COLLADASWStreamWriter.h"
#include "COLLADASWExtraTechnique.h"
#include "COLLADASWConstants.h"
#include "COLLADASWCameraOptic.h"
#include "COLLADAFWJointPrimitive.h"

namespace COLLADASW
{

    /** A class that hold all information about an @a \<joint\> element.*/
    class InstanceJoint : public ElementWriter, public BaseExtraTechnique
    {

    private:

        // LibraryJoints should be able to call the add() method.
        friend class LibraryKinematicsModels;

//        BaseOptic* mOptics;

      //  COLLADAFW::JointPrimitive mJointPrimitive;

        String mInstanceJointSid;

        String mInstanceJointUrl;



    protected:

        /** Adds the joint information. */
        void add() const;

    public:

        /**
        * Constructor
        * @param cameraId The id of the camera.
        * @param cameraName The name of the camera.
        */
        InstanceJoint (
            StreamWriter* streamWriter,
            //const COLLADAFW::JointPrimitive& jointPrimitive,
            const String& instanceJointUrl = ElementWriter::EMPTY_STRING,
            const String& instanceJointSid = ElementWriter::EMPTY_STRING);

        /** Copy constructor **/
        InstanceJoint (const InstanceJoint& orig);

        /** Destructor */
        virtual ~InstanceJoint()
        { }

        const String& getInstanceJointSid() const { return mInstanceJointSid; }

        const String& getInstanceJointUrl() const { return mInstanceJointUrl; }

        //void setJointPrimitive(const COLLADAFW::JointPrimitive& jointPrimitive) { mJointPrimitive = jointPrimitive; };
        //const COLLADAFW::JointPrimitive& getJointPrimitive() const { return mJointPrimitive; };
//        const BaseOptic* getOptics() const { return mOptics; }

    };

} //namespace COLLADASW

#endif //__COLLADASTREAMWRITER_INSTANCE_JOINT_H__
