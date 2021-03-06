#define WIN32_LEAN_AND_MEAN
#include <windows.h>

extern "C"
{
    __declspec(dllexport) volatile char luaHelperIsInitialized;

    __declspec(dllexport) char luaHelperWorkingDirectory[1024] = {};

    __declspec(dllexport) __declspec(noinline) void OnLuaHelperInitialized()
    {
        volatile char dummy = 0;
    }

    __declspec(dllexport) __declspec(noinline) void OnLuaHelperBreakpointHit()
    {
        volatile char dummy = 0;
    }

    __declspec(dllexport) __declspec(noinline) void OnLuaHelperStepComplete()
    {
        volatile char dummy = 0;
    }

    __declspec(dllexport) __declspec(noinline) void OnLuaHelperStepOut()
    {
        volatile char dummy = 0;
    }

    __declspec(dllexport) __declspec(noinline) void OnLuaHelperStepInto()
    {
        volatile char dummy = 0;
    }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch(ul_reason_for_call)
	{
    case DLL_PROCESS_ATTACH:
        GetCurrentDirectoryA(1024, luaHelperWorkingDirectory);

        luaHelperIsInitialized = 1;
        OnLuaHelperInitialized();
        break;
    default:
		break;
	}

	return TRUE;
}

#include <stdio.h>

//#define DEBUG_MODE

#define LUA_HOOKCALL	0
#define LUA_HOOKRET	1
#define LUA_HOOKLINE	2
#define LUA_HOOKCOUNT	3
#define LUA_HOOKTAILCALL 4
#define LUA_HOOKTAILRET 4

namespace Lua_5_3
{
    typedef unsigned char lu_byte;

    struct GCObject;

    union Value
    {
        GCObject *gc;    /* collectable objects */
        void *p;         /* light userdata */
        int b;           /* booleans */
        void* f; /* light C functions */
        long long i;   /* integer numbers */
        double n;    /* float numbers */
    };

    struct TValue
    {
        Value value_;
        int tt_;
    };

    typedef TValue *StkId;

    typedef unsigned Instruction;

    struct LocVar;
    struct Upvaldesc;
    struct TString;

    struct Proto
    {
        GCObject *next; lu_byte tt; lu_byte marked;
        lu_byte numparams;  /* number of fixed parameters */
        lu_byte is_vararg;
        lu_byte maxstacksize;  /* number of registers needed by this function */
        int sizeupvalues;  /* size of 'upvalues' */
        int sizek;  /* size of 'k' */
        int sizecode;
        int sizelineinfo;
        int sizep;  /* size of 'p' */
        int sizelocvars;
        int linedefined;  /* debug information  */
        int lastlinedefined;  /* debug information  */
        TValue *k;  /* constants used by the function */
        Instruction *code;  /* opcodes */
        struct Proto **p;  /* functions defined inside the function */
        int *lineinfo;  /* map from opcodes to source lines (debug information) */
        LocVar *locvars;  /* information about local variables (debug information) */
        Upvaldesc *upvalues;  /* upvalue information */
        struct LClosure *cache;  /* last-created closure with this prototype */
        TString  *source;  /* used for debug information */
        GCObject *gclist;
    };

    struct LClosure
    {
        GCObject *next;
        lu_byte tt;
        lu_byte marked;
        lu_byte nupvalues;
        GCObject *gclist;
        struct Proto *p;

        // Don't care for other fields
    };

    struct CallInfo
    {
        StkId func;  /* function index in the stack */

        // Don't care for other fields
    };

    struct lua_Debug
    {
        int event;
        const char *name;	/* (n) */
        const char *namewhat;	/* (n) 'global', 'local', 'field', 'method' */
        const char *what;	/* (S) 'Lua', 'C', 'main', 'tail' */
        const char *source;	/* (S) */
        int currentline;	/* (l) */
        int linedefined;	/* (S) */
        int lastlinedefined;	/* (S) */
        unsigned char nups;	/* (u) number of upvalues */
        unsigned char nparams;/* (u) number of parameters */
        char isvararg;        /* (u) */
        char istailcall;	/* (t) */

        // Don't care for other fields
    };

    struct global_State;

    struct lua_State
    {
        GCObject *next; lu_byte tt; lu_byte marked;
        unsigned short nci;  /* number of items in 'ci' list */
        lu_byte status;
        StkId top;  /* first free slot in the stack */
        global_State *l_G;
        CallInfo *ci;  /* call info for current function */

        // Don't care for other fields
    };

    struct TString
    {
        GCObject *next; lu_byte tt; lu_byte marked;
        lu_byte extra;  /* reserved words for short strings; "has hash" for longs */
        lu_byte shrlen;  /* length for short strings */
        unsigned int hash;
        union
        {
            size_t lnglen;  /* length for long strings */
            struct TString *hnext;  /* linked list for hash table */
        } u;
    };
}

namespace Lua_5_2
{
    typedef unsigned char lu_byte;

    struct GCObject;

    union Value
    {
        GCObject *gc;    /* collectable objects */
        void *p;         /* light userdata */
        int b;           /* booleans */
        void *f; /* light C functions */
    };

    struct TValue
    {
        union
        {
            struct
            {
                Value v__; int tt__;
            } i;
            double d__;
        } u;
    };

    typedef TValue *StkId;

    typedef unsigned Instruction;

    struct LocVar;
    struct Upvaldesc;
    union TString;

    struct Proto
    {
        GCObject *next; lu_byte tt; lu_byte marked;
        TValue *k;  /* constants used by the function */
        Instruction *code;
        struct Proto **p;  /* functions defined inside the function */
        int *lineinfo;  /* map from opcodes to source lines (debug information) */
        LocVar *locvars;  /* information about local variables (debug information) */
        Upvaldesc *upvalues;  /* upvalue information */
        union Closure *cache;  /* last created closure with this prototype */
        TString  *source;  /* used for debug information */
        int sizeupvalues;  /* size of 'upvalues' */
        int sizek;  /* size of `k' */
        int sizecode;
        int sizelineinfo;
        int sizep;  /* size of `p' */
        int sizelocvars;
        int linedefined;
        int lastlinedefined;
        GCObject *gclist;
        lu_byte numparams;  /* number of fixed parameters */
        lu_byte is_vararg;
        lu_byte maxstacksize;  /* maximum stack used by this function */
    };

    struct LClosure
    {
        GCObject *next; lu_byte tt; lu_byte marked; lu_byte nupvalues; GCObject *gclist;
        struct Proto *p;

        // Don't care for other fields
    };

    struct CallInfo
    {
        StkId func;  /* function index in the stack */

        // Don't care for other fields
    };

    struct lua_Debug
    {
        int event;
        const char *name;	/* (n) */
        const char *namewhat;	/* (n) 'global', 'local', 'field', 'method' */
        const char *what;	/* (S) 'Lua', 'C', 'main', 'tail' */
        const char *source;	/* (S) */
        int currentline;	/* (l) */
        int linedefined;	/* (S) */
        int lastlinedefined;	/* (S) */
        unsigned char nups;	/* (u) number of upvalues */
        unsigned char nparams;/* (u) number of parameters */
        char isvararg;        /* (u) */
        char istailcall;	/* (t) */

        // Don't care for other fields
    };

    struct global_State;

    struct lua_State
    {
        GCObject *next; lu_byte tt; lu_byte marked;
        lu_byte status;
        StkId top;  /* first free slot in the stack */
        global_State *l_G;
        CallInfo *ci;  /* call info for current function */

        // Don't care for other fields
    };

    union TString
    {
        union
        {
            double u; void *s; long l;
        } dummy;  /* ensures maximum alignment for strings */
        struct
        {
            GCObject *next; lu_byte tt; lu_byte marked;
            lu_byte extra;  /* reserved words for short strings; "has hash" for longs */
            unsigned int hash;
            size_t len;  /* number of characters in string */
        } tsv;
    };
}

namespace Lua_5_1
{
    typedef unsigned char lu_byte;

    union GCObject;

    union Value
    {
        GCObject *gc;
        void *p;
        double n;
        int b;
    };

    struct TValue
    {
        Value value; int tt;
    };

    typedef TValue *StkId;

    typedef unsigned Instruction;

    struct LocVar;
    struct Upvaldesc;
    union TString;

    struct Proto
    {
        GCObject *next; lu_byte tt; lu_byte marked;
        TValue *k;  /* constants used by the function */
        Instruction *code;
        struct Proto **p;  /* functions defined inside the function */
        int *lineinfo;  /* map from opcodes to source lines */
        struct LocVar *locvars;  /* information about local variables */
        TString **upvalues;  /* upvalue names */
        TString  *source;
        int sizeupvalues;
        int sizek;  /* size of `k' */
        int sizecode;
        int sizelineinfo;
        int sizep;  /* size of `p' */
        int sizelocvars;
        int linedefined;
        int lastlinedefined;
        GCObject *gclist;
        lu_byte nups;  /* number of upvalues */
        lu_byte numparams;
        lu_byte is_vararg;
        lu_byte maxstacksize;
    };

    struct LClosure
    {
        GCObject *next; lu_byte tt; lu_byte marked; lu_byte isC; lu_byte nupvalues; GCObject *gclist;
        struct Table *env;
        struct Proto *p;

        // Don't care for other fields
    };

    struct CallInfo
    {
        StkId base;  /* base for this function */
        StkId func;  /* function index in the stack */
        StkId top;  /* top for this function */
        const Instruction *savedpc;
        int nresults;  /* expected number of results from this function */
        int tailcalls;  /* number of tail calls lost under this entry */
    };

    struct lua_Debug
    {
        int event;
        const char *name;	/* (n) */
        const char *namewhat;	/* (n) `global', `local', `field', `method' */
        const char *what;	/* (S) `Lua', `C', `main', `tail' */
        const char *source;	/* (S) */
        int currentline;	/* (l) */
        int nups;		/* (u) number of upvalues */
        int linedefined;	/* (S) */
        int lastlinedefined;	/* (S) */

        // Don't care for other fields
    };

    struct global_State;

    struct lua_State
    {
        GCObject *next; lu_byte tt; lu_byte marked;
        lu_byte status;
        StkId top;  /* first free slot in the stack */
        StkId base;  /* base of current function */
        global_State *l_G;
        CallInfo *ci;  /* call info for current function */
        const Instruction *savedpc;  /* `savedpc' of current function */
        StkId stack_last;  /* last free slot in the stack */
        StkId stack;  /* stack base */
        CallInfo *end_ci;  /* points after end of ci array*/
        CallInfo *base_ci;  /* array of CallInfo's */
        int stacksize;
        int size_ci;  /* size of array `base_ci' */
        unsigned short nCcalls;  /* number of nested C calls */
        unsigned short baseCcalls;  /* nested C calls when resuming coroutine */
        lu_byte hookmask;
        lu_byte allowhook;
        int basehookcount;
        int hookcount;

        // Don't care for other fields
    };

    union TString
    {
        union
        {
            double u; void *s; long l;
        } dummy;  /* ensures maximum alignment for strings */
        struct
        {
            GCObject *next; lu_byte tt; lu_byte marked;
            lu_byte reserved;
            unsigned int hash;
            size_t len;
        } tsv;
    };
}

struct LuaHelperBreakData
{
    uintptr_t line;
    uintptr_t proto;
    const char *sourceName;
};

extern "C" __declspec(dllexport) unsigned luaHelperBreakCount = 0;
extern "C" __declspec(dllexport) LuaHelperBreakData luaHelperBreakData[256] = {};
extern "C" __declspec(dllexport) unsigned luaHelperBreakHitId = 0;
extern "C" __declspec(dllexport) uintptr_t luaHelperBreakHitLuaStateAddress = 0;
extern "C" __declspec(dllexport) char luaHelperBreakSources[128 * 256] = {};

extern "C" __declspec(dllexport) unsigned luaHelperStepOver = 0;
extern "C" __declspec(dllexport) unsigned luaHelperStepInto = 0;
extern "C" __declspec(dllexport) unsigned luaHelperStepOut = 0;
extern "C" __declspec(dllexport) unsigned luaHelperSkipDepth = 0;

void LuaHelperStepHook(int event)
{
    if(event == LUA_HOOKCALL)
    {
        if(luaHelperStepInto)
        {
            OnLuaHelperStepInto();
        }
        else if(luaHelperStepOver || luaHelperStepOut)
        {
            luaHelperSkipDepth++;
        }
    }

    if(event == LUA_HOOKTAILCALL)
    {
        if(luaHelperStepInto)
        {
            OnLuaHelperStepInto();
        }
    }

    if(event == LUA_HOOKRET)
    {
        if(luaHelperStepOut && luaHelperSkipDepth == 0)
        {
            OnLuaHelperStepOut();
        }
        else if((luaHelperStepOver || luaHelperStepOut) && luaHelperSkipDepth > 0)
        {
            luaHelperSkipDepth--;
        }
    }

    if(event == LUA_HOOKLINE && (luaHelperStepOver || luaHelperStepInto) && luaHelperSkipDepth == 0)
        OnLuaHelperStepComplete();
}

void LuaHelperBreakpointHook(void *L, int line, uintptr_t proto, const char *sourceName)
{
    for(auto curr = luaHelperBreakData, end = luaHelperBreakData + luaHelperBreakCount; curr != end; curr++)
    {
        if(line != curr->line)
            continue;

        if(curr->proto)
        {
            if(proto == curr->proto)
            {
                luaHelperBreakHitId = unsigned(curr - luaHelperBreakData);
                luaHelperBreakHitLuaStateAddress = uintptr_t(L);

                OnLuaHelperBreakpointHit();
                break;
            }
        }
        else
        {
            if(strcmp(curr->sourceName, sourceName) == 0)
            {
                luaHelperBreakHitId = unsigned(curr - luaHelperBreakData);
                luaHelperBreakHitLuaStateAddress = uintptr_t(L);

                OnLuaHelperBreakpointHit();
                break;
            }
        }
    }
}

extern "C" __declspec(dllexport) void LuaHelperHook_5_3(Lua_5_3::lua_State *L, Lua_5_3::lua_Debug *ar)
{
#if defined(DEBUG_MODE)
    const char *sourceName = "uknown location";

    if(ar->i_ci && (ar->i_ci->func->tt_ & 0x3f) == 6)
    {
        auto proto = ((Lua_5_3::LClosure*)ar->i_ci->func->value_.gc)->p;

        sourceName = (char*)proto->source + sizeof(Lua_5_3::TString);
    }

    if(ar->event == LUA_HOOKCALL)
    {
        if(luaHelperStepInto)
        {
            printf("hook call at line %d from '%s', step into (skip depth %d)\n", ar->currentline, sourceName, luaHelperSkipDepth);

            OnLuaHelperStepInto();
        }
        else if(luaHelperStepOver || luaHelperStepOut)
        {
            printf("hook call at line %d from '%s', step over (skip depth raised to %d)\n", ar->currentline, sourceName, luaHelperSkipDepth + 1);

            luaHelperSkipDepth++;
        }
    }

    if(ar->event == LUA_HOOKTAILCALL)
    {
        if(luaHelperStepInto)
        {
            printf("hook tail at line %d from '%s', step into (skip depth %d)\n", ar->currentline, sourceName, luaHelperSkipDepth);

            OnLuaHelperStepInto();
        }
    }

    if(ar->event == LUA_HOOKRET)
    {
        if(luaHelperStepOut && luaHelperSkipDepth == 0)
        {
            printf("hook return at line %d from '%s', step out (skip depth %d)\n", ar->currentline, sourceName, luaHelperSkipDepth);

            OnLuaHelperStepOut();
        }
        else if((luaHelperStepOver || luaHelperStepOut) && luaHelperSkipDepth > 0)
        {
            printf("hook return at line %d from '%s', step over (skip depth dropped to %d)\n", ar->currentline, sourceName, luaHelperSkipDepth - 1);

            luaHelperSkipDepth--;
        }
    }

    if(ar->event == LUA_HOOKLINE && (luaHelperStepOver || luaHelperStepInto))
    {
        printf("hook line at line %d from '%s', step%s%s%s (skip depth %d)\n", ar->currentline, sourceName, luaHelperStepOver ? " over" : "", luaHelperStepInto ? " into" : "", luaHelperStepOut ? " out" : "", luaHelperSkipDepth);

        if(luaHelperSkipDepth == 0)
        {
            printf("step complete\n");

            OnLuaHelperStepComplete();
        }
    }
#else
    LuaHelperStepHook(ar->event);
#endif

    if(L->ci && (L->ci->func->tt_ & 0x3f) == 6)
    {
        auto proto = ((Lua_5_3::LClosure*)L->ci->func->value_.gc)->p;

        const char *sourceName = (char*)proto->source + sizeof(Lua_5_3::TString);

        LuaHelperBreakpointHook(L, ar->currentline, uintptr_t(proto), sourceName);
    }
}

extern "C" __declspec(dllexport) void LuaHelperHook_5_2(Lua_5_2::lua_State *L, Lua_5_2::lua_Debug *ar)
{
    LuaHelperStepHook(ar->event);

    if(L->ci && (L->ci->func->u.i.tt__ & 0x3f) == 6)
    {
        auto proto = ((Lua_5_2::LClosure*)L->ci->func->u.i.v__.gc)->p;

        const char *sourceName = (char*)proto->source + sizeof(Lua_5_2::TString);

        LuaHelperBreakpointHook(L, ar->currentline, uintptr_t(proto), sourceName);
    }
}

extern "C" __declspec(dllexport) void LuaHelperHook_5_1(Lua_5_1::lua_State *L, Lua_5_1::lua_Debug *ar)
{
    if(ar->event == LUA_HOOKCALL)
    {
        if(luaHelperStepInto)
        {
            OnLuaHelperStepInto();
        }
        else if(luaHelperStepOver || luaHelperStepOut)
        {
            luaHelperSkipDepth++;
        }
    }

    if(ar->event == LUA_HOOKRET || ar->event == LUA_HOOKTAILRET)
    {
        if(luaHelperStepOut && luaHelperSkipDepth == 0)
        {
            OnLuaHelperStepOut();
        }
        else if((luaHelperStepOver || luaHelperStepOut) && luaHelperSkipDepth > 0)
        {
            luaHelperSkipDepth--;
        }
    }

    if(ar->event == LUA_HOOKLINE && (luaHelperStepOver || luaHelperStepInto) && luaHelperSkipDepth == 0)
    {
        OnLuaHelperStepComplete();
    }

    unsigned callInfoIndex = 0;

    if(ar->event != LUA_HOOKTAILRET)
        callInfoIndex = unsigned(L->ci - L->base_ci);

    if(callInfoIndex >= 0)
    {
        auto function = L->base_ci[callInfoIndex].func;

        if((function->tt & 0x3f) == 6)
        {
            auto luaClosure = (Lua_5_1::LClosure*)function->value.gc;

            if(!luaClosure->isC)
            {
                auto proto = luaClosure->p;

                const char *sourceName = (char*)proto->source + sizeof(Lua_5_1::TString);

                LuaHelperBreakpointHook(L, ar->currentline, uintptr_t(proto), sourceName);
            }
        }
    }
}
