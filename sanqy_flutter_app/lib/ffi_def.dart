import 'dart:ffi' as ffi;
import 'package:ffi/ffi.dart';
typedef Cfunc_helloWorld = ffi.Int Function();
typedef HelloWorld = int Function();
				

typedef Cfunc_OpenDatabase = ffi.Pointer Function(ffi.Pointer<Utf8>,ffi.Int);

typedef OpenDatabase = ffi.Pointer 
					Function(ffi.Pointer<Utf8>,int);

typedef Cfunc_CloseDatabase = ffi.Void 
					Function(ffi.Pointer);

typedef CloseDatabase = void 
					Function(ffi.Pointer);

typedef Cfunc_InsertCard = ffi.Bool
					Function(ffi.Pointer,ffi.Pointer<Utf8>,ffi.Pointer<Utf8>);

typedef InsertCard = bool
					Function(ffi.Pointer,ffi.Pointer<Utf8>,ffi.Pointer<Utf8>);

typedef Cfunc_GetRevision = ffi.Void
					Function(ffi.Pointer,ffi.Pointer<Utf8>);

typedef GetRevision = void
					Function(ffi.Pointer,ffi.Pointer<Utf8>);

typedef Cfunc_IsRevisionAvailable = ffi.Bool
					Function(ffi.Pointer,ffi.Int);

typedef IsRevisionAvailable = bool
					Function(ffi.Pointer,int);

typedef GetOptions = Options
					Function(ffi.Pointer);

typedef TestStructFunc = TestStruct
					Function();

typedef CFunc_RevisionCallback = ffi.Void
					Function(ffi.Pointer,ffi.Int,ffi.Int);

typedef RevisionCallback = void
					Function(ffi.Pointer,int,int);

typedef Cfunc_GetCardWord = ffi.Void
					Function(ffi.Pointer,ffi.Int,ffi.Pointer<Utf8>);

typedef GetCardWord = void
					Function(ffi.Pointer,int,ffi.Pointer<Utf8>);

typedef Cfunc_GetCardsUids = ffi.Int
					Function(ffi.Pointer,ffi.Pointer<ffi.Pointer<TwoInt>>);

typedef GetCardsUids = int
					Function(ffi.Pointer,ffi.Pointer<ffi.Pointer<TwoInt>>);

typedef Cfunc_InvalidateCardsUids = ffi.Void
					Function(ffi.Pointer<TwoInt>);

typedef InvalidateCardsUids = void
					Function(ffi.Pointer<TwoInt>);

typedef Cfunc_ModifyCard = ffi.Void
					Function(ffi.Pointer,ffi.Pointer<Utf8>,ffi.Int);

typedef ModifyCard = void
					Function(ffi.Pointer,ffi.Pointer<Utf8>,int);

typedef Cfunc_DeleteCard = ffi.Void
					Function(ffi.Pointer,ffi.Int);

typedef DeleteCard = void
					Function(ffi.Pointer,int);

final class Option extends ffi.Struct {
	@ffi.Int()
	external int time;
	

	@ffi.Array.multi([100])//OPTION_STR_MAX in C code
	external ffi.Array<ffi.Char> str;

	@ffi.Array.multi([100])//OPTION_STR_MAX in C code
	external ffi.Array<ffi.Char> status;
	
	@ffi.Int()
	external int shown;

	@ffi.Int()
	external int failed;

}
final class Options extends ffi.Struct {
	external Option option1;
	external Option option2;
	external Option option3;
	external Option option4;
}
final class TwoInt extends ffi.Struct {
	@ffi.Int()
	external int one;

	@ffi.Int()
	external int two;

}
final class TestStruct extends ffi.Struct {
	@ffi.Int()
	external int mInt;
}
