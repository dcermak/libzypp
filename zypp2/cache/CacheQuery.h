/*---------------------------------------------------------------------\
|                          ____ _   __ __ ___                          |
|                         |__  / \ / / . \ . \                         |
|                           / / \ V /|  _/  _/                         |
|                          / /__ | | | | | |                           |
|                         /_____||_| |_| |_|                           |
|                                                                      |
\---------------------------------------------------------------------*/


#ifndef ZYPP_CACHE_QUERY_H
#define ZYPP_CACHE_QUERY_H

#include <iosfwd>
#include <string>
#include <utility>

#include "zypp/base/ReferenceCounted.h"
#include "zypp/base/NonCopyable.h"
#include "zypp/base/PtrTypes.h"
#include "zypp/Pathname.h"
#include "zypp/data/RecordId.h"
#include "zypp/base/PtrTypes.h"

#include "zypp2/cache/CapabilityQuery.h"

///////////////////////////////////////////////////////////////////
namespace zypp
{ /////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////
  namespace cache
  { /////////////////////////////////////////////////////////////////
     
    /**
     * The Cache Query API provides access to the store data
    */
    class CacheQuery
    {
    public:
       /** Implementation. */
      class Impl;
      CacheQuery( Impl * );
      CacheQuery( const Pathname &dbdir );
      ~CacheQuery();
      CapabilityQuery createCapabilityQuery( const data::RecordId &id  );
    private:
      /** Pointer to implementation. */
      RW_pointer<Impl> _pimpl;
    };
    
  } // ns cache
} // ns zypp
#endif

