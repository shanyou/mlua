#ifndef __MLUA_ENGINE_H__
#define __MLUA_ENGINE_H__
#include "MLuaCommon.h"
#include "MluaRefCount.h"

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include <string>
using namespace std;

#define ENGINE_NAME	"mlua"

#define MLUA_LOAD_SUCCESS	0
#define MLUA_LOAD_ERROR		1

#define MLUA_BUFFER_SIZE 	(512)
#define MLUA_MAX_FILENAME 	(256)
#define MLUA_SUFFIX			".lua"
#define MLUA_PACKAGE_NAME	"package.json"

namespace MLua {
	/*
	* base class for module loader
	*/
	class MLuaLoader : public RefCount
	{
	public:
		MLuaLoader();
		MLuaLoader(const char* loaderName);
	protected:
		virtual ~MLuaLoader();

	public:
		virtual int load_module(lua_State *L);
		virtual const char* name() const { return m_loader_name.c_str(); };

	protected:
		string m_loader_name;
	};

	/*-------------------------------------------------------------------------*\
	*	embed lua with socket openssl and related modules
	*	not thread safe class, mast create and run on the same thread.
	\*-------------------------------------------------------------------------*/
	class MLuaEngine : public RefCount
	{
	public:
		MLuaEngine(void);
		~MLuaEngine(void);

		bool is_opened() const {return m_luaState != NULL;}
		int id() const {return m_id;}
		lua_State* state() const {return m_luaState;}

		bool open(const char* work_path = 0);
		void close();
		
		bool load_file_in_zip(const char* file, const char* zipFile, const char* pwd = 0);

		bool clear_loaded_module(const char* module_name);

	public:
		static bool add_loader(MLuaLoader* loader);
		static bool add_zip(const char* zippath, const char* pwd = 0);
		/*
			if zip loader the name is the file name
		*/
		static void remove_loader(const char* loaderName);

	private:
		static int load_libs(lua_State* L);

	private:
		lua_State *m_luaState;
		int m_id;

	};

} // MLua


#endif//__MLUA_ENGINE_H__