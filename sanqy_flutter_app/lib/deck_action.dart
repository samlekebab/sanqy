import 'package:flutter/material.dart';
import 'ffi_def.dart';
import 'dart:ffi' as ffi;
import 'package:ffi/ffi.dart';
import 'package:path_provider/path_provider.dart';
import 'dart:io' show Directory;
import 'package:path/path.dart' as p;
import 'package:back_button_interceptor/back_button_interceptor.dart';
import 'add_mod_card.dart';
import 'study.dart';
import 'm_time.dart';
import 'list_card.dart';

class DeckAction extends StatefulWidget{
	const DeckAction({super.key, required this.deckName,
															required this.closeDeck});
	final String deckName;
	final Function() closeDeck;
	State<DeckAction> createState() => _DeckAction();
}

class _DeckAction extends State<DeckAction>{
		late final OpenDatabase openDatabase;
		late final CloseDatabase closeDatabase;
		late final TestStructFunc testStruct;
		late final ffi.DynamicLibrary dylib;
		late final String deckName;
		late final ffi.Pointer handler;

		bool isCreateCard = false;
		bool isStudy = false;
		bool isListCard = false;

	@override
	initState(){
		super.initState();
		loadLibrary();
		super.initState();
		BackButtonInterceptor.add(myInterceptor);
	}
	void loadLibrary() async{
		deckName = widget.deckName;
		final Directory appDocumentsDir = await getApplicationDocumentsDirectory();
		final path = p.join(appDocumentsDir.path,deckName);
		//print(path);

		dylib = ffi.DynamicLibrary.open("libsanqy.so");

		closeDatabase =
				dylib.lookupFunction
				<Cfunc_CloseDatabase, CloseDatabase>('closeDatabase');
		openDatabase =
				dylib.lookupFunction
				<Cfunc_OpenDatabase, OpenDatabase>('openDatabase');
		testStruct = 
				dylib.lookupFunction
				<TestStructFunc, TestStructFunc>('testStruct');

		handler = openDatabase(path.toNativeUtf8(),getMTime());


		TestStruct t = testStruct();
		//print(t.mInt);
	}

	@override
	void dispose() {
		 BackButtonInterceptor.remove(myInterceptor);
		 closeDatabase(handler);
		 super.dispose();
	}

	bool myInterceptor(bool stopDefaultButtonEvent, RouteInfo info) {
		if(!stopDefaultButtonEvent){
			widget.closeDeck();
		}
		return true;
	}
	void openCreateCard(){
		isCreateCard = true;
		setState(()=>{});
	}
	void closeCreateCard(){
		isCreateCard = false;
		setState(()=>{});
	}
	void openCardList(){
		isListCard = true;
		setState(()=>{});
	}
	void closeCardList(){
		isListCard = false;
		setState(()=>{});
	}
	void openStudy(){
		isStudy=true;
		setState(()=>{});
	}
	void closeStudy(){
		isStudy = false;
		setState(()=>{});
	}

	@override
	Widget build(BuildContext context){
		if (isCreateCard){
			return AddModCard(
				dylib:dylib,
				handler:handler,
				finish:()=>closeCreateCard(),
			);
		}

		if (isStudy){
			return Study(
				dylib:dylib,
				handler:handler,
				finish:()=>closeStudy(),
			);
		}

		if (isListCard){
			return ListCard(
				dylib:dylib,
				handler:handler,
				finish:()=>closeCardList(),
			);
		}

		return Scaffold(
			appBar: AppBar(
				title:Text("Sanqy : deck $deckName"),
			),
			body:Center(
				child: Column(
					mainAxisAlignment:MainAxisAlignment.center,
					children:[
						Text("deck $deckName"),
						ElevatedButton(
							onPressed: () => openCardList(),
							child: const Text('open card list'),
						),
						ElevatedButton(
							onPressed: () => openCreateCard(),
							child: const Text('create card'),
						),
						ElevatedButton(
							onPressed: () => openStudy(),
							child: const Text('studyy'),
						),
					]
				)
			)
		);
	}
}
