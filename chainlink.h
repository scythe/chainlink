
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
   if(ind < arr.len && ind >= 0) id = cl_index(name, arr, ind); \
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

//TODO: Actually import PP_NARG
//first __VA_ARG is always "id", variable being declared
#define chainfunc_decl(name, ...) \
   chainfunc_decl_(CL_NARG(__VA_ARGS__), name, __VA_ARGS__)

#define chainfunc_decl_(len, name, id, ...) \
   chainfunc_decl_##len(name, id, __VA_ARGS__) 
   
#define chainfunc_decl_1(name, id, ...) \
   __cl_link_##name id = { __cl_mangle_##name };

#define chainfunc_decl_2(name, id, ...) \
   __cl_link_##name id = {__cl_mangle_##name, __VA_ARGS__};

#define chainfunc_decl_3(name, id, ...) \
   __cl_link_##name id = {__cl_mangle_##name, __VA_ARGS__};

#define chainarr_decl(name, ...) \
   chainarr_decl_(CL_NARG(__VA_ARGS__), name, __VA_ARGS__)

#define chainarr_decl_(len, name, id, ...) \
   chainarr_decl_##len(name, id, __VA_ARGS__) 
   
#define chainarr_decl_1(name, id, ...) \
   __cl_link_##name id = { NULL };

#define chainarr_decl_2(name, id, varlit, ...) { \
   __cl_chainlit_##name __cl_mangle_##id[] = varlit; \
   __cl_link_##name id = { __cl_mangle_##id }; \
}

#define chainarr_decl_3(name, id, varlit, ...) { \
   __cl_chainlit_##name __cl_mangle_##id[] = varlit; \
   __cl_link_##name id = { __cl_mangle_##id , __VA_ARGS__ };\
}

#define cl_t(name) __cl_link_name


