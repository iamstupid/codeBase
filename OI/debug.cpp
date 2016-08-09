#ifdef __use_Descr
  #define Descr(functional,...) namespace zballCodes_##__FILE__{ \
    const char* functional##_desc=#__VA_ARGS__; \
  }
#else
  #define Descr(...)
#endif

Descr(
  __content__,
  useful macros for debugging
)

Descr(
  __debug_open,
  if defined, load the following functionals, otherwise all functionals evaluates to nothing
)

#define __debug_open

#ifdef __debug_open

  Descr(
    If,
    Macro If works like real If but it only accepts a value -- 0 or 1,
    but it is still useful because macros can expand lazily, so we can make a lot of testing with it.
    If_0,If_1 and If_ are routines for If
  )
  
  Descr(
    cat,
    just cat two tokens, but can expand one more time
  )
  
  Descr(
    eval,
    expand one level
  )
  
  Descr(
    Empty,
    just a placeholder for Empty argument
    <Note: cannot be transformed into 0 directly, but can do some like If(k,0,1) to transform>
  )
  
  Descr(
    Block,
    Block a function's evaluation
  )
  
  Descr(
    Raw,
    just an alias for eval;
    but there is still some difference in using, or you can just ignore the difference.
    it is used to send pack a Expression into __VA_ARGS__
  )
  
  Descr(
    Expr,
    Make a Expression into one argument, even if it contains comma
  )
  
  Descr(
    depug,
    routine for implementing debug and codei, in fact is an unnecessary shortcut
  )
  
  Descr(
    debug,
    if version_##id evaluates to 1,then
      output like printf but redirected into stderr
      flushed membuf.
    otherwise
      do nothing
  )
  
  Descr(
    codei,
    if version_##id evaluates to 1,then
      evaluates to the given code
    otherwise
      do nothing
  )
  
	#define If_1(A,B) A
	#define If_0(A,B) B
	#define If_
	#define cat(A,B) A##B
	#define eval(...) __VA_ARGS__
	#define Empty
	#define Block(x) x Empty
	#define Raw(...) __VA_ARGS__
	#define Expr(...) Block(Raw)(__VA_ARGS__)

	#define If(cond,A,B) cat(If_,cond)(A,B)

	#define version_0 0
	#define version_1 1

	#define version_at 1
	
	#define depug(id,...) eval(eval(If(cat(version_,id),Expr(__VA_ARGS__),Empty)))
	#define debug(id,...) depug(id,{fprintf(stderr,##__VA_ARGS__),fflush(stderr);})
	#define codei(id,...) depug(id,__VA_ARGS__;)

#else
	
	#define debug(...)
	#define codei(...)

#endif
