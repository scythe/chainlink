#pragma once

#define link(name, vars) \
   typedef struct __cl_s_link_##name { \
      __cl_chain_##name name; \
      vars; \
   } __cl_link_##name;

#define chainfunc(ret, name, __VA_ARGS__) \
   ret __cl_mangle_##name(__cl_link_##name _, __VA_ARGS__); \
   typedef __typeof__(__cl_mangle_##name) __cl_chain_##name; \
   ret __cl_mangle_##name(__cl_link_##name name, __VA_ARGS__)

/* C99 Sec 6.7.2.1 Par. 13 Within a structure object, the non-bit-field members and the units in 
 * which bit-fields reside have addresses that increase in the order in which they are 
 * declared. A pointer to a structure object, suitably converted, points to its initial 
 * member (or if that member is a bit-field, then to the unit in which it resides), and 
 * vice versa. There may be unnamed padding within a structure object, but not at its beginning.
 *
 * In other words, I can do this.
 */
#define cl_call(name, __VA_ARGS__) \
   (* (__cl_chain_##name *) name)(name, __VA_ARGS__)

#define chainarr(type, name) \
   typedef type *__cl_chain_##name; \
   typedef type __cl_chainlit_##name;

#define cl_index(name, arr, ind) \
   (*(((__cl_chain_##name) arr) + ind))

#define cl_index_check(id, name, arr, ind) { \
   if(ind < arr.n && ind >= 0) id = cl_index(name, arr, ind); \
   else id = * (__typeof__(id) *) cl_zero; \
}

static const __attribute__((unused)) unsigned long cl_zero = {0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, \
0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,\ 
0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,\
 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,\ 
0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,\
 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,\
 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,\ 
0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,\ 
0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,\ 
0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,\
 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,\ 
0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,\
 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,\
 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,\ 
0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,\ 
0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,\ 
0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,\
 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,\ 
0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,\
 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,\
 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,\ 
0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0,0, 0, 0, 0}; 

#define chainunion(name, type) \
   typedef __cl_chain_##name type;

#define cl_as(name, var, kind) \
   (((__cl_chain_##name) var).kind)

//Counts arguments. It's really too bad I never learned to count higher than three...
#define CL_NARG( ...) CL_NARG_(__VA_ARGS__,CL_RSEQ_N())
#define CL_NARG_(...) CL_ARG_N(__VA_ARGS__)
#define CL_ARG_N(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19, \
	_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39, \
	_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59, \
	_61,_62,_63,N,...) N

#define CL_RSEQ_N() 3,3,3,3,3,3,3,3, 3,3,3,3,3,3,3,3, 3,3,3,3,3,3,3,3, 3,3,3,3,3,3,3,3, \
	3,3,3,3,3,3,3,3, 3,3,3,3,3,3,3,3, 3,3,3,3,3,3,3,3, 3,3,3,3,3,2,1,0

//first __VA_ARG is always "id", variable being declared
#define chainfunc_decl(name, ...) \
   chainfunc_decl_(CL_NARG(__VA_ARGS__), name, __VA_ARGS__)

#define chainfunc_decl_(len, name, id, ...) \
   chainfunc_decl_##len(name, id, __VA_ARGS__) 
   
#define chainfunc_decl_1(name, id, ...) \
   __cl_link_##name id = { __cl_mangle_##name }

#define chainfunc_decl_2(name, id, ...) \
   __cl_link_##name id = {__cl_mangle_##name, __VA_ARGS__}

#define chainfunc_decl_3(name, id, ...) \
   __cl_link_##name id = {__cl_mangle_##name, __VA_ARGS__}

#define chainarr_decl(name, ...) \
   chainarr_decl_(CL_NARG(__VA_ARGS__), name, __VA_ARGS__)

#define chainarr_decl_(len, name, id, ...) \
   chainarr_decl_##len(name, id, __VA_ARGS__) 
   
#define chainarr_decl_1(name, id, ...) \
   __cl_link_##name id = { NULL }

#define chainarr_decl_2(name, id, varlit, ...) { \
   __cl_chainlit_##name __cl_mangle_##id[] = varlit; \
   __cl_link_##name id = { __cl_mangle_##id , .n = sizeof(__cl_mangle_##id)}; \
}

#define chainarr_decl_3(name, id, varlit, ...) { \
   __cl_chainlit_##name __cl_mangle_##id[] = varlit; \
   __cl_link_##name id = { __cl_mangle_##id , .n = sizeof(__cl_mangle_##id),  __VA_ARGS__ };\
}

#define chainptr_decl(name, ...) \
   chainptr_decl_(CL_NARG(__VA_ARGS__), name, __VA_ARGS__)

#define chainptr_decl_(len, name, id, ...) \
   chainptr_decl_##len(name, id, __VA_ARGS__) 
   
#define chainptr_decl_1(name, id, ...) \
   __cl_link_##name id = { NULL }

#define chainptr_decl_2(name, id, ptr, ...) { \
   __cl_chain_##name __cl_mangle_##id = ptr; \
   __cl_link_##name id = { __cl_mangle_##id }; \
}

#define chainptr_decl_3(name, id, ptr, ...) { \
   __cl_chain_##name __cl_mangle_##id = ptr; \
   __cl_link_##name id = { __cl_mangle_##id , __VA_ARGS__ };\
}

#define chainptr_alloc(name, ...) \
   chainarr_alloc_(CL_NARG(__VA_ARGS__), name, __VA_ARGS__)

#define chainptr_alloc_(len, name, id, ...) \
   chainptr_alloc_##len(name, id, __VA_ARGS__) 
   
#define chainptr_alloc_1(name, id, ...) \
   enum { alloc_requires_length = 1/0 }

#define chainptr_alloc_2(name, id, n) { \
   __cl_chain_##name __cl_mangle_##id = malloc(n * sizeof(__cl_chainlit_##name)); \
   __cl_link_##name id = { __cl_mangle_##id }; \
}

#define chainptr_alloc_3(name, id, n, ...) { \
   __cl_chain_##name __cl_mangle_##id = malloc(n * sizeof(__cl_chainlit_##name)); \
   __cl_link_##name id = { __cl_mangle_##id , __VA_ARGS__ };\
}

#define chainptr_realloc(name, id, n) \
   id.name = realloc(id.name, sizeof(__cl_chainlit_##name) * n);

//FIXME: define chain unions. separate declaration/definition. should work in headers etc.

#define cl_t(name) __cl_link_name


