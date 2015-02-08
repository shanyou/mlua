#include "MLuaCommon.h"
#include "MLuaRefCount.h"
#include "MLuaEngine.h"
#include <map>
using namespace MLua;
///////////////////////////////////////////////////////////////
// gloable define

typedef std::map< std::string, CRefPtr<MLuaLoader> > LoaderList;

