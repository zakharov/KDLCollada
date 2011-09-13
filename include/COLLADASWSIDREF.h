/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

    This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#ifndef __COLLADASTREAMWRITER_SIDREF_H__
#define __COLLADASTREAMWRITER_SIDREF_H__

#include "COLLADASWPrerequisites.h"
#include "COLLADASWStreamWriter.h"
#include "COLLADASWExtraTechnique.h"
#include "COLLADASWConstants.h"
#include "COLLADASWCameraOptic.h"
#include "COLLADAFWJointPrimitive.h"

namespace COLLADASW
{

    /** A class that hold all information about an @a \<joint\> element.*/
    class SIDREF : public ElementWriter, public BaseExtraTechnique
    {

    private:

        String mPath;

    public:

        /** Adds the joint information. */
        void add() const;

    public:

        /**
        * Constructor
        * @param cameraId The id of the camera.
        * @param cameraName The name of the camera.
        */
        SIDREF (
            StreamWriter* streamWriter,
            const String& value = ElementWriter::EMPTY_STRING);

        /** Copy constructor **/
        SIDREF (const SIDREF& orig);

        /** Destructor */
        virtual ~SIDREF()
        { }

        const String& getPath() const { return mPath; }

    };

} //namespace COLLADASW

#endif //__COLLADASTREAMWRITER_JOINT_H__
