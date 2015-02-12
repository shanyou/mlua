#include "MLuaCommon.h"
#include "MLuaThread.h"
#include "MLuaRefCount.h"
#include "MLuaEngine.h"

#include <map>
using namespace MLua;
///////////////////////////////////////////////////////////////
// gloable define

typedef std::map< std::string, CRefPtr<MLuaLoader> > LoaderList;

static LoaderList			g_loaderList;		/* static loaders */
static Mutex*                g_list_lock = NULL;		/* static loader access lock */
static int					g_count = 0;		/* total alive lua engine */
static int					g_id = 0;			/* global unique id */
static int					g_initialed = 0;	/* global init count */


/*
 * extern method for ini mlua engine for use
 */
void mlua_global_init(bool bInit) {
    if (bInit) {
        if (g_initialed == 0) {
            g_initialed++;
            g_count = 0;
            if (g_list_lock == 0) {
                g_list_lock = new Mutex();
            }
        }
    } else {
        g_initialed--;
        if (g_initialed == 0) {
            g_count = 0;
            g_loaderList.clear();
            if (g_list_lock) {
                delete g_list_lock;
                g_list_lock = NULL;
            }
        }
    }
}

//////////////////////////////////////////////////////////////
