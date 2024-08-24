import 'package:flutter/material.dart';
import 'package:back_button_interceptor/back_button_interceptor.dart';
import 'dart:ffi' as ffi;
import 'ffi_def.dart';
import 'package:ffi/ffi.dart';

class AddModCard extends StatefulWidget{
	const AddModCard({super.key,
															required this.dylib,
															required this.handler,
															this.uidFront,
															this.uidBack,
															required this.finish,});
	final ffi.DynamicLibrary dylib;
	final ffi.Pointer handler;
	final int? uidFront;
	final int? uidBack;
	final Function() finish;

	State<AddModCard> createState() => _AddModCard();
}

class _AddModCard extends State<AddModCard>{
	String front = "";
	String back = "";
	late final InsertCard insertCard;
	late final GetCardWord getCardWord;
	late final ModifyCard modifyCard;
	late final DeleteCard deleteCard;
	bool isInMod = false;

	late TextEditingController myControllerFront;
	late TextEditingController myControllerBack;
	@override
		void initState() {
			super.initState();
			loadLibrary();
			BackButtonInterceptor.add(myInterceptor);

		}

	void loadLibrary() async{
		insertCard =
				widget.dylib.lookupFunction
				<Cfunc_InsertCard, InsertCard>('insertCard');
		getCardWord =
				widget.dylib.lookupFunction
				<Cfunc_GetCardWord, GetCardWord>('getCardWord');
		modifyCard =
				widget.dylib.lookupFunction
				<Cfunc_ModifyCard, ModifyCard>('modifyCard');
		deleteCard = 
				widget.dylib.lookupFunction
				<Cfunc_DeleteCard, DeleteCard>('deleteCard');
		 
			if (widget.uidBack!=null && widget.uidFront !=null){
				isInMod = true;

				final ptr =	malloc.allocate<Utf8>(1 * 500);
				getCardWord(widget.handler,widget.uidFront!,ptr);
				front = ptr.toDartString();
				getCardWord(widget.handler,widget.uidBack!,ptr);
				back = ptr.toDartString();
				malloc.free(ptr);

				setState(()=>{});
			}
			myControllerFront =TextEditingController(text: front);
			myControllerBack =TextEditingController(text: back);
	}
	@override
	void dispose() {
		 BackButtonInterceptor.remove(myInterceptor);
		 super.dispose();
	}

	bool myInterceptor(bool stopDefaultButtonEvent, RouteInfo info) {
		if(!stopDefaultButtonEvent){
			widget.finish();
		}
		return true;
	}
	void addCard(){
		insertCard(widget.handler,front.toNativeUtf8(),back.toNativeUtf8());
		widget.finish();
	}
	void modCard(){
		modifyCard(widget.handler,front.toNativeUtf8(),widget.uidFront!);
		modifyCard(widget.handler,back.toNativeUtf8(),widget.uidBack!);
		widget.finish();
	}
	void delCard(){
		deleteCard(widget.handler,widget.uidFront!);
		widget.finish();
	}

	@override
	Widget build(BuildContext context){
		return Scaffold(
			body: Center(
				child: Column(
					mainAxisAlignment:MainAxisAlignment.center,
					children:[
						TextField(
							decoration: const InputDecoration(
								border: UnderlineInputBorder(),
								labelText: 'front',
							),
							controller:myControllerFront,
							onChanged:(String str)=>{front = str},
						),
						TextField(
							decoration: const InputDecoration(
								border: UnderlineInputBorder(),
								labelText: 'back',
							),
							controller:myControllerBack,
							onChanged:(String str)=>{back = str},
						),
						ElevatedButton(
							onPressed: () => isInMod?modCard():addCard(),
							child: Text(isInMod?'modify card':'add card'),
						),
						isInMod
						? ElevatedButton(
							onPressed: () => delCard(),
							child: Text('delete card'),
						)
						: SizedBox(width:0,height:0),
					]
				)
			)
		);
	}
}
