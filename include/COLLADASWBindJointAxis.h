/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

    This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#ifndef __COLLADASTREAMWRITER_BIND_JOINT_AXIS_H__
#define __COLLADASTREAMWRITER_BIND_JOINT_AXIS_H__

#include "COLLADASWPrerequisites.h"
#include "COLLADASWStreamWriter.h"
#include "COLLADASWExtraTechnique.h"
#include "COLLADASWConstants.h"

namespace COLLADASW
{

    /** A class that hold all information about an @a \<joint\> element.*/
    class BindJointAxis : public ElementWriter, public BaseExtraTechnique
    {

    private:

        String mTarget;
        String mAxis;
        String mValue;

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
        BindJointAxis (
            StreamWriter* streamWriter,
            const String& target = ElementWriter::EMPTY_STRING,
            const String& axis = ElementWriter::EMPTY_STRING,
            const String& value = ElementWriter::EMPTY_STRING);

        /** Copy constructor **/
        BindJointAxis (const BindJointAxis& orig);

        /** Destructor */
        virtual ~BindJointAxis()
        { }

        const String& getTarget() const { return mTarget; }
        const String& getAxis() const { return mAxis; }
        const String& getValue() const { return mValue; }

    };

} //namespace COLLADASW

#endif //__COLLADASTREAMWRITER_JOINT_H__
