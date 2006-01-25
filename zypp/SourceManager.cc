/*---------------------------------------------------------------------\
|                          ____ _   __ __ ___                          |
|                         |__  / \ / / . \ . \                         |
|                           / / \ V /|  _/  _/                         |
|                          / /__ | | | | | |                           |
|                         /_____||_| |_| |_|                           |
|                                                                      |
\---------------------------------------------------------------------*/
/** \file	zypp/SourceManager.cc
 *
*/
#include <iostream>
#include "zypp/base/Logger.h"

#include "zypp/SourceManager.h"
#include "zypp/SourceFactory.h"
#include "zypp/Source.h"
#include "zypp/source/SourceImpl.h"


using std::endl;

///////////////////////////////////////////////////////////////////
namespace zypp
{ /////////////////////////////////////////////////////////////////

  IMPL_PTR_TYPE(SourceManager)

  SourceManager_Ptr SourceManager::_source_manager;

  SourceManager_Ptr SourceManager::sourceManager()
  {
    if ( ! _source_manager )
      _source_manager = new SourceManager;
    return _source_manager;
  }


  ///////////////////////////////////////////////////////////////////
  //
  //	METHOD NAME : SourceManager::SourceManager
  //	METHOD TYPE : Ctor
  //
  SourceManager::SourceManager()
  {}

  ///////////////////////////////////////////////////////////////////
  //
  //	METHOD NAME : SourceManager::~SourceManager
  //	METHOD TYPE : Dtor
  //
  SourceManager::~SourceManager()
  {}

  unsigned SourceManager::addSource(ResPoolManager & pool_r, const Url & url_r, const Pathname & path_r)
  {
    Source src = SourceFactory().createFrom(url_r, path_r);
    RW_pointer<Source> src_ptr = RW_pointer<Source>(new Source(src));
    _sources[_next_id] = src_ptr;
    addToPool(pool_r, src_ptr->resolvables());
    return _next_id++;
  }

  unsigned SourceManager::addSource(ResPoolManager & pool_r, Source & source_r)
  {
    RW_pointer<Source> src_ptr = RW_pointer<Source>(new Source(source_r));
    _sources[_next_id] = src_ptr;
    addToPool(pool_r, src_ptr->resolvables());
    return _next_id++;
  }

  void SourceManager::removeSource(ResPoolManager & pool_r, const unsigned id)
  {
    SourceMap::iterator it = _sources.find(id);
    if (it != _sources.end())
    {
      removeFromPool(pool_r, (it->second)->resolvables());
      _sources.erase(it);
    }
  }

  void SourceManager::addToPool(ResPoolManager & pool_r, const ResStore & store_r)
  {
    pool_r.insert(store_r.begin(), store_r.end());
  }

  void SourceManager::removeFromPool(ResPoolManager & pool_r, const ResStore & store_r)
  {
    for (ResStore::iterator it = store_r.begin(); it != store_r.end(); it++)
    {
      pool_r.erase(*it);
    }
  }




  /******************************************************************
  **
  **	FUNCTION NAME : operator<<
  **	FUNCTION TYPE : std::ostream &
  */
  std::ostream & operator<<( std::ostream & str, const SourceManager & obj )
  {
    return str << "Source Manager has " << " sources" << endl;
  }

  unsigned SourceManager::_next_id = 0;

  Source & SourceManager::findSource(const unsigned id)
  {
    SourceMap::iterator it = _sources.find(id);
    if (it == _sources.end())
    {
      ZYPP_THROW(Exception("Unknown source ID"));
    }
    return *(it->second);
  }

  /////////////////////////////////////////////////////////////////
} // namespace zypp
///////////////////////////////////////////////////////////////////
