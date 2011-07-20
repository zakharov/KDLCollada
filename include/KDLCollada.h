/*
 * File:   KDLCollada.h
 * Author: alexey
 *
 * Created on July 20, 2011, 8:19 AM
 */

#ifndef KDLCOLLADA_H
#define	KDLCOLLADA_H

#include <kdl/chain.hpp>
#include <string>

class KDLCollada {
public:
    KDLCollada();
    KDLCollada(const KDLCollada& orig);
    virtual ~KDLCollada();

    bool load(const std::string& filename, std::vector<KDL::Chain>& kdlChain);
    bool save(const std::string& filename, std::vector<KDL::Chain>& kdlChain);

private:

};

#endif	/* KDLCOLLADA_H */

