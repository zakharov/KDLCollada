/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

    This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#ifndef __COLLADASTREAMWRITER_NEWPARAM_H__
#define __COLLADASTREAMWRITER_NEWPARAM_H__

#include "COLLADASWPrerequisites.h"
#include "COLLADASWStreamWriter.h"
#include "COLLADASWExtraTechnique.h"
#include "COLLADASWConstants.h"

namespace COLLADASW
{

    /** A class that hold all information about an @a \<joint\> element.*/
    class Newparam : public ElementWriter, public BaseExtraTechnique
    {

    private:

        String mNewparamSid;

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
        Newparam (
            StreamWriter* streamWriter,
            const String& newparamSid = ElementWriter::EMPTY_STRING);

        /** Copy constructor **/
        Newparam (const Newparam& orig);

        /** Destructor */
        virtual ~Newparam()
        { }

        const String& getNewparamSid() const { return mNewparamSid; }

    };

} //namespace COLLADASW

#endif //__COLLADASTREAMWRITER_JOINT_H__
