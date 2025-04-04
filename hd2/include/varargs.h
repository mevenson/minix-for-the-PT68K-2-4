/*  varargs.h  */

typedef char *va_list;

#define  va_dcl		int va_alist;
#define  va_start(p)	(p) = (va_list) &va_alist;
#define  va_arg(p,type)	( (type *) ((p)+=sizeof(type)) )[-1]
#define  va_end(p)

#define vfprintf 	_doprintf
#define vprintf(fmt,args)	vfprintf(stdout,fmt,args)
