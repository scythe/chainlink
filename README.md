If you're reading this, it is because `chainlink.h` is so new, it has not even been properly tested.
It should work fine, with at most slight modification: but *caveat emptor*!

# chainlink

`chainlink.h` is a collection of convenience functions that provide basic support for 
closures, boxed arrays, and tagged unions. It attempts to be transparent, robust, and portable,
and does not intend to change the way C is written. Rather, our only goal here is to
provide a little syntactic sugar for doing things C programmers already regularly do, and
to support idiomatic C coding, rather than to replace it. Therefore, chainlink is intended to
"play nice" with C's ordinary type system, and chainlink-using programs should produce "normal"
compilation errors if the code contains typing errors.

Originally, `chainlink` was planned to be written as a proper extension, with the same goals as above,
and with the additional features of conforming rigorously to a simple specification, providing
more general mixin-like functionality, and allowing some limited type inference via structural subtyping,
with a couple compilation flags to give rules on how much inference is allowed. However, the
complete version of `chainlink` would have taken quite a bit of effort to write, and it seemed a little
silly to write an entire C extension solely for my personal use. `chainlink` proper might still happen,
someday, but only if I (or you!) find a reason to make it.

The `chainlink.h` file is less than 200 lines of standard C and depends only on a couple things:

 * the compiler extension `__typeof__`
 * `memset(), malloc(), and realloc()`
 * C99 structure literals with designated initializers

It is hoped that people who wish to use chainlink.h will be able to read the file and understand how it works,
so that they may do so without making wrong assumptions about what chainlink should do. It is also hoped that
libraries which use chainlink will be written to be compatible with libraries which do not use chainlink.

## coding style

The recommended way to use chainlink.h is to follow the Linux kernel style guide, to use .n for the length of an array,
and to use .t for the type of a union. I disagree with Linus essentially in only one place: I like the one-line "if" statement.
Also, he would probably hate `chainlink.h`, so don't try to use it in the kernel (duh).

It is also recommended that you do not sit and code for more than three hours at a time. Go take a walk outside. Also, though
the style guide occasionally makes reference to staying up for twenty hours until you can barely recognize indentation,
don't do that.
