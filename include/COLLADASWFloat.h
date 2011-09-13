/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

    This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#ifndef __COLLADASTREAMWRITER_FLOAT_H__
#define __COLLADASTREAMWRITER_FLOAT_H__

#include "COLLADASWPrerequisites.h"
#include "COLLADASWStreamWriter.h"
#include "COLLADASWExtraTechnique.h"
#include "COLLADASWConstants.h"

namespace COLLADASW
{

    /** A class that hold all information about an @a \<joint\> element.*/
    class Float : public ElementWriter, public BaseExtraTechnique
    {

    private:

        double mValue;

    public:

        /** Adds the joint information. */
        void add() const;

    public:

        /**
        * Constructor
        * @param cameraId The id of the camera.
        * @param cameraName The name of the camera.
        */
        Float (
            StreamWriter* streamWriter,
            double value = 0);

        /** Copy constructor **/
        Float (const Float& orig);

        /** Destructor */
        virtual ~Float()
        { }

        double getValue() const { return mValue; }

    };

} //namespace COLLADASW

#endif //__COLLADASTREAMWRITER_JOINT_H__
