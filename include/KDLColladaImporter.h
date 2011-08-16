/*
 * File:   KDLColladaImporter.h
 * Author: alexey
 *
 * Created on July 20, 2011, 10:07 AM
 */

#ifndef KDLCOLLADAIMPORTER_H
#define	KDLCOLLADAIMPORTER_H

#include "COLLADAFWIWriter.h"
#include <vector>
#include <kdl/chain.hpp>
#include "COLLADAFW.h"

namespace COLLADAFW
{
class Formulas;
class Formula;
class KinematicsScene;
class KinematicsModel;
class InstanceKinematicsScene;
class Joint;
}

namespace KDL
{
class Chain;
class Frame;
}

class KDLColladaImporter : public COLLADAFW::IWriter
{
    // member declarations
private:
    void parseKinematicsModel(const COLLADAFW::KinematicsScene* kinematicsScenePtr, std::vector<KDL::Chain>& kdlChainArray);
    void parseLinkJointConnections(COLLADAFW::KinematicsModel* kinModelPtr);
//    void parseJointPrimitiveArray(COLLADAFW::Joint* jointPtr);
    void parseJointPrimitiveArray(COLLADAFW::Joint* jointPtr, KDL::Joint::JointType& jointType, KDL::Vector& jointAxis);
    void parseNodeLinkBindArray(COLLADAFW::InstanceKinematicsScene* instKinScene);
    void parseTransformationArray(COLLADAFW::TransformationPointerArray* transformationArray, KDL::Frame& frame);
    // public function declarations
public:
    KDLColladaImporter();
    KDLColladaImporter(std::vector<KDL::Chain>& kdlChain);
    virtual ~KDLColladaImporter();

    /** This method will be called if an error in the loading process occurred and the loader cannot
    continue to to load. The writer should undo all operations that have been performed.
    @param errorMessage A message containing informations about the error that occurred.
    */
    virtual void cancel(const COLLADAFW::String& errorMessage);

    /** This is the method called. The writer hast to prepare to receive data.*/
    virtual void start();

    /** This method is called after the last write* method. No other methods will be called after this.*/
    virtual void finish();

    /** When this method is called, the writer must write the global document asset.
    @return The writer should return true, if writing succeeded, false otherwise.*/
    virtual bool writeGlobalAsset ( const COLLADAFW::FileInfo* asset );

    /** When this method is called, the writer must write the entire visual scene.
    @return The writer should return true, if writing succeeded, false otherwise.*/
    virtual bool writeScene ( const COLLADAFW::Scene* scene );

    /** When this method is called, the writer must write the entire visual scene.
    @return The writer should return true, if writing succeeded, false otherwise.*/
    virtual bool writeVisualScene ( const COLLADAFW::VisualScene* visualScene );

    /** When this method is called, the writer must handle all nodes contained in the
    library nodes.
    @return The writer should return true, if writing succeeded, false otherwise.*/
    virtual bool writeLibraryNodes ( const COLLADAFW::LibraryNodes* libraryNodes );

    /** When this method is called, the writer must write the geometry.
    @return The writer should return true, if writing succeeded, false otherwise.*/
    virtual bool writeGeometry ( const COLLADAFW::Geometry* geometry );

    /** When this method is called, the writer must write the material.
    @return The writer should return true, if writing succeeded, false otherwise.*/
    virtual bool writeMaterial( const COLLADAFW::Material* material );

    /** When this method is called, the writer must write the effect.
    @return The writer should return true, if writing succeeded, false otherwise.*/
    virtual bool writeEffect( const COLLADAFW::Effect* effect );

    /** When this method is called, the writer must write the camera.
    @return The writer should return true, if writing succeeded, false otherwise.*/
    virtual bool writeCamera( const COLLADAFW::Camera* camera );

    /** When this method is called, the writer must write the image.
    @return The writer should return true, if writing succeeded, false otherwise.*/
    virtual bool writeImage( const COLLADAFW::Image* image );

    /** When this method is called, the writer must write the light.
    @return The writer should return true, if writing succeeded, false otherwise.*/
    virtual bool writeLight( const COLLADAFW::Light* light );

    /** Writes the animation.
    @return True on succeeded, false otherwise.*/
    virtual bool writeAnimation( const COLLADAFW::Animation* animation );

    /** When this method is called, the writer must write the AnimationList.
    @return The writer should return true, if writing succeeded, false otherwise.*/
    virtual bool writeAnimationList( const COLLADAFW::AnimationList* animationList );

    /** When this method is called, the writer must write the skin controller data.
    @return The writer should return true, if writing succeeded, false otherwise.*/
    virtual bool writeSkinControllerData( const COLLADAFW::SkinControllerData* skinControllerData );

    /** When this method is called, the writer must write the controller.
    @return The writer should return true, if writing succeeded, false otherwise.*/
    virtual bool writeController( const COLLADAFW::Controller* controller );

    /** When this method is called, the writer must write the formula.
    @return The writer should return true, if writing succeeded, false otherwise.*/
    virtual bool writeFormulas( const COLLADAFW::Formulas* formulas );

    /** When this method is called, the writer must write the formula.
    @return The writer should return true, if writing succeeded, false otherwise.*/
    virtual bool writeFormula( const COLLADAFW::Formula* formulas );

    /** When this method is called, the writer must write the kinematics scene.
    @return The writer should return true, if writing succeeded, false otherwise.*/
    virtual bool writeKinematicsScene( const COLLADAFW::KinematicsScene* kinematicsScene );

    // private function declarations
private:
    /** Disable default copy ctor. */
    KDLColladaImporter( const KDLColladaImporter& pre );
    /** Disable default assignment operator. */
    const KDLColladaImporter& operator= ( const KDLColladaImporter& pre );

    std::vector<KDL::Chain>& kdlChain;

};

#endif
