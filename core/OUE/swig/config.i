%begin %{
#define WIN32_LEAN_AND_MEAN
#pragma warning(disable : 4312)
#pragma warning(disable : 4311)
#pragma warning(disable : 4267)
%}

#ifdef SWIGRUBY
#define SUPPORT_DIRECTORS
#endif


#ifdef SWIGLUA
%typemap(check) SWIGTYPE* NONNULL{
	if($1 == NULL)
		SWIG_fail_ptr("$symname",$argnum,$descriptor);
}

//unsupported
%define PROP_R(getter, prop)
%enddef
%define PROP_RW(setter, getter, prop)
%enddef
#elif defined(SWIGRUBY)
%typemap(check) SWIGTYPE* NONNULL{
	if($1 == NULL)
		SWIG_exception_fail(SWIG_ValueError, "Expected a non-null pointer! Arg #$argnum in $symname");
}

%define PROP_R(getter, prop)
%rename(#prop) getter;
%enddef
%define PROP_RW(getter, setter, prop)
PROP_R(getter, prop)
%rename(#prop"=") setter;
%enddef
#endif

//find in swigtype.swg ɾ����%as_voidptr
//Ϊ�˽���ʵ�ֵ����࣬���ܹ�׷�ٵ�����ʵ�����޸ġ�����������SWIG_NewPointerObj�����ƶԵ������newpointer��Ϊ��
/* Pointers, references */
%typemap(out,noblock=1) SWIGTYPE *, SWIGTYPE &, SWIGTYPE[] {
  %set_output(SWIG_NewPointerObj($1, $descriptor, $owner | %newpointer_flags));
}

%typemap(out, noblock=1) SWIGTYPE *const& {
  %set_output(SWIG_NewPointerObj(*$1, $*descriptor, $owner | %newpointer_flags));
}

