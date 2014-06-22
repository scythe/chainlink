#pragma once
/* for memset() */
#include <string.h>

#define link(name, vars) \
	typedef struct __cl_s_link_##name { \
		__cl_chain_##name name; \
		vars; \
	} __cl_link_##name;

/* 
 * It's good practice not to use typedefs when the type decorator (struct etc) would provide
 * some useful information about the behaviour of the object. We provide this, which acts as
 * a sort of type decorator, and should only be typedeffed if it ceases to be a useful
 * indicator of the behaviour of the object.
 */
#define cl_t(name) __cl_link_name

/* For definitions in header files. */
#define chainlink(name, id) \
	__cl_link_##name id

#define chainfunc(ret, name, __VA_ARGS__) \
	ret (*__cl_mangle_##name)(__cl_link_##name _, __VA_ARGS__); \
	typedef __typeof__(__cl_mangle_##name) __cl_chain_##name; \
	ret (*__cl_mangle_##name)(__cl_link_##name name, __VA_ARGS__)

/*
 * C99 Sec 6.7.2.1 A pointer to a structure object, suitably converted, points to its initial 
 * member (or if that member is a bit-field, then to the unit in which it resides), and 
 * vice versa. There may be unnamed padding within a structure object, but not at its beginning.
 *
 * In other words, we can do this. It's not necessary, but it emphasizes the transparency of this approach.
 */
#define cl_call(name, __VA_ARGS__) \
	(** (__cl_chain_##name *) &name)(name, __VA_ARGS__)

#define chainarr(type, name) \
	typedef type *__cl_chain_##name; \
	typedef type __cl_chainlit_##name;

/* No emphasis here: rather, we want to make an lvalue. */
#define cl_index(name, arr, ind) \
	(arr.##name[ind])

/* Bounds-checking! Arrays are bounds-checked using the .n parameter. */
#define cl_index_check(id, name, arr, ind) { \
	if(ind < arr.n && ind >= 0) id = cl_index(name, arr, ind); \
	else memset(&id, 0, sizeof(id)); \
}

#define cl_realloc(id, name, n) { \
	id.##name = realloc(id.##name, n * sizeof(__cl_chainlit_##name)); \
	id.n = n; \
}

/*
 * Here we take advantage of 6.7.2.1 again: "A pointer to a union object, 
 * suitably converted, points to each of its members..."
 * So the struct is the same address as its first member, the union,
 * which is at the same address as its active member, the type.
 * Obviously using this for unsafe type conversions will result
 * in undefined behavior, so don't do that.
 */ 
#define chainunion(name, type) \
	typedef __cl_chain_##name type;

#define cl_as(var, type) \
	(* (type *) &var)

/*
 * This is explicitly intended to work even where var is a function call.
 * We expect tagged (chain) unions to have a .t which represents their type.
 * "code" should have braces, unless it is a single statement.
 */
#define cl_assign_check(name, var, t, id, code) {  \
	__cl_link_##name __cl_holder_##id = var; \
	if(__cl_holder_##id.t != t) code; \
	id = cl_as(__cl_holder_##id, __typeof__(id)); \
}

/*
 * Counts arguments. It's really too bad I never learned to count higher than three... 
 * We use this to implement portable, safe variadic macros. Unfortunately it's still
 * pretty awkward, but we manage to cover every useful case without anything like
 * gcc's ##__VA_ARGS__ extension or the like. 
 */
#define CL_NARG( ...) CL_NARG_(__VA_ARGS__,CL_RSEQ_N())
#define CL_NARG_(...) CL_ARG_N(__VA_ARGS__)
#define CL_ARG_N(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19, \
	_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39, \
	_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59, \
	_61,_62,_63,N,...) N

#define CL_RSEQ_N() 3,3,3,3,3,3,3,3, 3,3,3,3,3,3,3,3, 3,3,3,3,3,3,3,3, 3,3,3,3,3,3,3,3, \
	3,3,3,3,3,3,3,3, 3,3,3,3,3,3,3,3, 3,3,3,3,3,3,3,3, 3,3,3,3,3,2,1,0

/*
 * Chainlink definition macros. Each takes the link name and
 * a variable identifier, arrays take an optional length, and 
 * unions take an optional type. Array length is stored as .n,
 * and union type is stored as .t: this is the standard way
 * to use chainlink's boxed arrays and tagged unions. 
 */
#define chainfunc_decl(name, ...) \
	chainfunc_decl_(CL_NARG(__VA_ARGS__), name, __VA_ARGS__)

#define chainfunc_decl_(len, name, ...) \
	chainfunc_decl_##len(name, __VA_ARGS__) 
	
#define chainfunc_decl_1(name, id) \
	__cl_link_##name id = { __cl_mangle_##name }

#define chainfunc_decl_2(name, id, ...) \
	__cl_link_##name id = {__cl_mangle_##name, __VA_ARGS__}

#define chainfunc_decl_3(name, id, ...) \
	__cl_link_##name id = {__cl_mangle_##name, __VA_ARGS__}

#define chainarr_decl(name, ...) \
	chainarr_decl_(CL_NARG(__VA_ARGS__), name, __VA_ARGS__)

#define chainarr_decl_(len, name, ...) \
	chainarr_decl_##len(name, __VA_ARGS__) 
	
#define chainarr_decl_1(name, id) \
	__cl_link_##name id = { NULL }

#define chainarr_decl_2(name, id, varlit) { \
	__cl_chainlit_##name __cl_mangle_##id[] = varlit; \
	__cl_link_##name id = { __cl_mangle_##id , .n = sizeof(__cl_mangle_##id)}; \
}

#define chainarr_decl_3(name, id, varlit, ...) { \
	__cl_chainlit_##name __cl_mangle_##id[] = varlit; \
	__cl_link_##name id = { __cl_mangle_##id , .n = sizeof(__cl_mangle_##id),  __VA_ARGS__ };\
}

#define chainptr_decl(name, ...) \
	chainptr_decl_(CL_NARG(__VA_ARGS__), name, __VA_ARGS__)

#define chainptr_decl_(len, name, ...) \
	chainptr_decl_##len(name, __VA_ARGS__) 
	
#define chainptr_decl_1(name, id) \
	__cl_link_##name id = { NULL }

#define chainptr_decl_2(name, id, n) { \
	__cl_link_##name id = { .n = n }; \
}

#define chainptr_decl_3(name, id, n, ...) { \
	__cl_link_##name id = { .n = n };\
}

#define chainptr_alloc(name, ...) \
	chainarr_alloc_(CL_NARG(__VA_ARGS__), name, __VA_ARGS__)

#define chainptr_alloc_(len, name, ...) \
	chainptr_alloc_##len(name, __VA_ARGS__) 
	
#define chainptr_alloc_1(name, id) \
	enum { alloc_requires_length = 1/0 }

#define chainptr_alloc_2(name, id, n) { \
	__cl_chain_##name __cl_mangle_##id = malloc(n * sizeof(__cl_chainlit_##name)); \
	__cl_link_##name id = { __cl_mangle_##id , .n = n}; \
}

#define chainptr_alloc_3(name, id, n, ...) { \
	__cl_chain_##name __cl_mangle_##id = malloc(n * sizeof(__cl_chainlit_##name)); \
	__cl_link_##name id = { __cl_mangle_##id , .n = n, __VA_ARGS__ };\
}

#define chainptr_realloc(name, id, n) \
	id.##name = realloc(id.##name, sizeof(__cl_chainlit_##name) * n);

#define chainunion_decl(name, ...) \
	chainunion_decl_(CL_NARG(__VA_ARGS__), name, __VA_ARGS__)

#define chainunion_decl_(len, name, ...) \
	chainunion_decl_##len(name, __VA_ARGS__) 

#define chainunion_decl_1(name, id) \
	__cl_link_##name id

#define chainunion_decl_2(name, id, t) { \
	__cl_link_##name id = {.t = t}; \
}

#define chainunion_decl_3(name, id, t, val, ...) { \
	__cl_link_##name id = {.t = t, __VA_ARGS__ };\
}

