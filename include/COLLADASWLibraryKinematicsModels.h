/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

    This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#ifndef __COLLADASTREAMWRITER_LIBRARY_KINEMATICS_MODELS_H__
#define __COLLADASTREAMWRITER_LIBRARY_KINEMATICS_MODELS_H__

#include "COLLADASWPrerequisites.h"
#include "COLLADASWExtraTechnique.h"
#include "COLLADASWLibrary.h"

namespace COLLADASW
{

    class KinematicsModel;
    class InstanceJoint;
    class Link;
    class AttachmentFull;
    /** Class to simply the creation of @a \<library_kinematics_models\>*/
    class LibraryKinematicsModels : public Library, public BaseExtraTechnique
    {

    public:
        /** Constructor
        @param streamWriter The stream the @a \<library_kinematics_models\> and @a \<kinematics_model\>'s
        should be written to.
        */
        LibraryKinematicsModels ( StreamWriter* streamWriter );

        /** Destructor*/
        virtual ~LibraryKinematicsModels() {}

    protected:

        /** Adds @a \<kinematics_model\> element. If not already opened, it opens @a \<kinematics_model\>*/
        void startKinematicsModel ( const KinematicsModel& kinematicsModel );
        void endKinematicsModel ( const KinematicsModel& kinematicsModel );
        void addKinematicsModel ( const KinematicsModel& KinematicsModel );
        void addInstanceJoint ( const InstanceJoint& instanceJoint );

        void startLink( const Link& link);
        void endLink( const Link& link);
        void addLink( const Link& link);
        void startAttachmentFull( const AttachmentFull& attachmentFull);
        void endAttachmentFull( const AttachmentFull& attachmentFull);
        void addAttachmentFull( const AttachmentFull& attachmentFull);
    };

} //namespace COLLADASW

#endif //__COLLADASTREAMWRITER_LIBRARY_KINEMATICS_MODELS_H__
