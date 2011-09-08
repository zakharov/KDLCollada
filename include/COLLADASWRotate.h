/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

    This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#ifndef __COLLADASTREAMWRITER_ROTATE_H__
#define __COLLADASTREAMWRITER_ROTATE_H__

#include "COLLADASWPrerequisites.h"
#include "COLLADASWStreamWriter.h"
#include "COLLADASWExtraTechnique.h"
#include "COLLADASWConstants.h"

namespace COLLADASW
{

    /** A class that hold all information about an @a \<joint\> element.*/
    class Rotate : public ElementWriter, public BaseExtraTechnique
    {

    private:

        // LibraryJoints should be able to call the add() method.
        friend class LibraryKinematicsModels;

        double mX;
        double mY;
        double mZ;
        double mW;
        String mRotateSid;

    protected:

        /** Adds the joint information. */
        void add() const;


    public:

        /**
        * Constructor
        * @param cameraId The id of the camera.
        * @param cameraName The name of the camera.
        */
        Rotate (
            StreamWriter* streamWriter,
            double x = 0,
            double y = 0,
            double z = 0,
            double w = 0,
            const String& rotateSid = ElementWriter::EMPTY_STRING);

        /** Copy constructor **/
        Rotate (const Rotate& orig);

        /** Destructor */
        virtual ~Rotate()
        { }

        const String& getRotateSid() const { return mRotateSid; }
        double getX() const { return mX; }
        double getY() const { return mY; }
        double getZ() const { return mZ; }
        double getW() const { return mW; }
     };

} //namespace COLLADASW

#endif //__COLLADASTREAMWRITER_ROTATE_H__
