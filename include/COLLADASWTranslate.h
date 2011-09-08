/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

    This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#ifndef __COLLADASTREAMWRITER_TRANSLATE_H__
#define __COLLADASTREAMWRITER_TRANSLATE_H__

#include "COLLADASWPrerequisites.h"
#include "COLLADASWStreamWriter.h"
#include "COLLADASWExtraTechnique.h"
#include "COLLADASWConstants.h"

namespace COLLADASW
{

    /** A class that hold all information about an @a \<joint\> element.*/
    class Translate : public ElementWriter, public BaseExtraTechnique
    {

    private:

        // LibraryJoints should be able to call the add() method.
        friend class LibraryKinematicsModels;

        double mX;
        double mY;
        double mZ;
        String mTranslateSid;

    protected:

        /** Adds the joint information. */
        void add() const;


    public:

        /**
        * Constructor
        * @param cameraId The id of the camera.
        * @param cameraName The name of the camera.
        */
        Translate (
            StreamWriter* streamWriter,
            double x = 0,
            double y = 0,
            double z = 0,
            const String& translateSid = ElementWriter::EMPTY_STRING);

        /** Copy constructor **/
        Translate (const Translate& orig);

        /** Destructor */
        virtual ~Translate()
        { }

        const String& getTranslateSid() const { return mTranslateSid; }
        double getX() const { return mX; }
        double getY() const { return mY; }
        double getZ() const { return mZ; }
     };

} //namespace COLLADASW

#endif //__COLLADASTREAMWRITER_TRANSLATE_H__
