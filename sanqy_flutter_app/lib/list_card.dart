import 'package:flutter/material.dart';
import 'package:back_button_interceptor/back_button_interceptor.dart';
import 'dart:ffi' as ffi;
import 'ffi_def.dart';
import 'package:ffi/ffi.dart';
import 'add_mod_card.dart';

class ListCard extends StatefulWidget{
	const ListCard({super.key, required this.dylib,
															required this.handler,
															required this.finish});
	final ffi.DynamicLibrary dylib;
	final ffi.Pointer handler;
	final Function() finish;
	State<ListCard> createState() => _ListCard();
}

class _ListCard extends State<ListCard>{
	late final GetCardWord getCardWord;
	late final GetCardsUids getCardsUids;
	late final InvalidateCardsUids invalidateCardsUids;
	late ffi.Pointer<ffi.Pointer<TwoInt>> cardsUidListP;
	late int listSize;
	late List<String?> front;
	late List<String?> back;

	int? uidFront;
	int? uidBack;
	
	bool isModCard = false;

	@override
	void initState() {
		 super.initState();
		 loadLibrary();
		 BackButtonInterceptor.add(myInterceptor);
	}

	void loadLibrary() async{
		getCardWord =
				widget.dylib.lookupFunction
				<Cfunc_GetCardWord, GetCardWord>('getCardWord');
		getCardsUids =
				widget.dylib.lookupFunction
				<Cfunc_GetCardsUids, GetCardsUids>('getCardsUids');
		invalidateCardsUids =
				widget.dylib.lookupFunction
				<Cfunc_InvalidateCardsUids,
				InvalidateCardsUids>('invalidateCardsUids');


		cardsUidListP = malloc.allocate<ffi.Pointer<TwoInt>>(ffi.sizeOf<ffi.Pointer<TwoInt>>());
		makeList();
		
	}
	void makeList(){
		listSize = getCardsUids(widget.handler,cardsUidListP);
		front = List<String?>.filled(listSize,null);
		back = List<String?>.filled(listSize,null);
		setState(()=>{});
	}

	String getFromList(int index,int face){
		final list = (face==0) ? front : back;
		if (list[index] == null){
			final ptr =	malloc.allocate<Utf8>(1 * 500);
			TwoInt uids =(cardsUidListP.value+index).ref;
			int uid = face==0 ? uids.one : uids.two;

			getCardWord(widget.handler,uid,ptr);
			list[index] = ptr.toDartString();
			malloc.free(ptr);
		}
		return list[index]!;
	}

	@override
	void dispose() {
		 BackButtonInterceptor.remove(myInterceptor);
		 invalidateCardsUids(cardsUidListP.value);
		 malloc.free(cardsUidListP);
		 super.dispose();
	}

	bool myInterceptor(bool stopDefaultButtonEvent, RouteInfo info) {
		if(!stopDefaultButtonEvent){
			widget.finish();
		}
		return true;
	}
	void openModCard(index){
			isModCard = true;
			TwoInt uids =(cardsUidListP.value+index).ref;
			uidFront = uids.one;
			uidBack = uids.two;
			setState(()=>{});
	}

	void closeModCard(){
		isModCard = false;
		uidFront = null;
		uidBack = null;
		makeList();
		setState(()=>{});
	}
	@override
	Widget build(BuildContext context){
		if (isModCard){
			return AddModCard(
				dylib:widget.dylib,
				handler:widget.handler,
				finish:closeModCard,
				uidFront:uidFront,
				uidBack:uidBack,
			);
		}
		return Scaffold(
			body: ListView.builder(
				itemCount: listSize,
				itemBuilder: (context, index) {
					final itemFront = getFromList(index,0);
					final itemBack = getFromList(index,1);
					return ListTile(
						onTap:()=>openModCard(index),
						title:Row(
							mainAxisAlignment:MainAxisAlignment.spaceBetween,
							children:[
								Text("$itemFront | $itemBack"),
							]
						),
					);
				},
			),
		);
	}
}
