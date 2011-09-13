/*
    Copyright (c) 2011 Alexey Zakharov
    email alexey.zakharov at gmail.com

    This file is part of KDLColladaParser.

    Licensed under the MIT Open Source License,
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#ifndef __COLLADASTREAMWRITER_LIBRARY_KINEMATICS_SCENENS_H__
#define __COLLADASTREAMWRITER_LIBRARY_KINEMATICS_SCENENS_H__

#include "COLLADASWPrerequisites.h"
#include "COLLADASWExtraTechnique.h"
#include "COLLADASWLibrary.h"

namespace COLLADASW
{

    class KinematicsScene;
    class InstanceKinematicsModel;
    class Newparam;
    class SIDREF;
    class Float;
    /** Class to simply the creation of @a \<library_kinematics_models\>*/
    class LibraryKinematicsScenes : public Library, public BaseExtraTechnique
    {

    public:
        /** Constructor
        @param streamWriter The stream the @a \<library_kinematics_models\> and @a \<kinematics_model\>'s
        should be written to.
        */
        LibraryKinematicsScenes ( StreamWriter* streamWriter );

        /** Destructor*/
        virtual ~LibraryKinematicsScenes() {}



    protected:

        void addKinematicsScene ( const KinematicsScene& kinematicsScene );
        void startKinematicsScene ( const KinematicsScene& kinematicsScene );
        void endKinematicsScene ( const KinematicsScene& kinematicsScene );
        void addInstanceKinematicsModel ( const InstanceKinematicsModel& instanceKinematicsModel );
        void startInstanceKinematicsModel ( const InstanceKinematicsModel& instanceKinematicsModel );
        void endInstanceKinematicsModel ( const InstanceKinematicsModel& instanceKinematicsModel );
        void startNewparam ( const Newparam& newparam );
        void endNewparam ( const Newparam& newparam );
        void addNewparam ( const Newparam& newparam );
        void addSIDREF ( const SIDREF& sidref );
        void addFloat ( const Float& value );

    };
} //namespace COLLADASW

#endif //__COLLADASTREAMWRITER_LIBRARY_KINEMATICS_MODELS_H__
