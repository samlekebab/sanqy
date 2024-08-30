import 'package:flutter/material.dart';
import 'package:back_button_interceptor/back_button_interceptor.dart';
import 'dart:ffi' as ffi;
import 'ffi_def.dart';
import 'package:ffi/ffi.dart';
import 'm_time.dart';

enum StudyState {
	INIT,
	FINISHED,
	FRONT,
	BACK,
}


class Study extends StatefulWidget{
	const Study({super.key, required this.dylib,
															required this.handler,
															required this.finish});
	final ffi.DynamicLibrary dylib;
	final ffi.Pointer handler;
	final Function() finish;

	State<Study> createState() => _Study();
}
class _Study extends State<Study>{
	late final GetRevision getRevisionFront;
	late final GetRevision getRevisionBack;
	late final IsRevisionAvailable isRevisionAvailable;
	late final GetOptions getOptions;
	late final RevisionCallback revisionCallback;

	late final GetInt getRevisionCount;
	late final GetInt getNewCardCount; 
	late final GetInt getMaxNewCardCount;
	late final GetInt getCurrentNewCardCount;
	late final GetInt getCurrentRevisionCount;
	int currentRevisonCount = 0;
	int currentNewCardCount =0;
	int maxNewCardCount = 0;
	int newCardCount = 0;
	int revisionCount = 0;

	final fontSize = 20.0;
	String front = "";
	String back = "";
	late Options options;

	StudyState studyState = StudyState.INIT;

	@override
	void initState() {
		 super.initState();
		 loadLibrary();
		 BackButtonInterceptor.add(myInterceptor);
	}

	void loadLibrary() async{
		getRevisionBack =
				widget.dylib.lookupFunction
				<Cfunc_GetRevision, GetRevision>('getRevisionBack');
		getRevisionFront =
				widget.dylib.lookupFunction
				<Cfunc_GetRevision, GetRevision>('getRevisionFront');
		isRevisionAvailable = 
				widget.dylib.lookupFunction
				<Cfunc_IsRevisionAvailable, IsRevisionAvailable>('isRevisionAvailable');
		getOptions = 
				widget.dylib.lookupFunction
				<GetOptions, GetOptions>('getOptions');
		revisionCallback =
				widget.dylib.lookupFunction
				<CFunc_RevisionCallback, RevisionCallback>('revisionCallBack');

		getRevisionCount =
				widget.dylib.lookupFunction
				<Cfunc_GetInt, GetInt>('getRevisionCount');
		getNewCardCount =
				widget.dylib.lookupFunction
				<Cfunc_GetInt, GetInt>('getNewCardCount');
		getMaxNewCardCount =
				widget.dylib.lookupFunction
				<Cfunc_GetInt, GetInt>('getMaxNewCardCount');
		getCurrentNewCardCount =
				widget.dylib.lookupFunction
				<Cfunc_GetInt, GetInt>('getCurrentNewCardCount');
		getCurrentRevisionCount =
				widget.dylib.lookupFunction
				<Cfunc_GetInt, GetInt>('getCurrentRevisionCount');

		startStudy();
	}

	void startStudy(){
		if(isRevisionAvailable(widget.handler,getMTime())){
			final ptr =	malloc.allocate<Utf8>(1 * 500);
			getRevisionFront(widget.handler,ptr);
			front = ptr.toDartString();
			malloc.free(ptr);
			studyState = StudyState.FRONT;
		}else{
			studyState = StudyState.FINISHED;
		}
		currentRevisonCount = getCurrentRevisionCount(widget.handler);
		currentNewCardCount = getCurrentNewCardCount(widget.handler);
		maxNewCardCount = getMaxNewCardCount(widget.handler);
		newCardCount = getNewCardCount(widget.handler);
		revisionCount = getRevisionCount(widget.handler);
		setState(()=>{});
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
	void showBack(){
		studyState = StudyState.BACK;

		options = getOptions(widget.handler);

		final ptr =	malloc.allocate<Utf8>(1 * 500);
		getRevisionBack(widget.handler,ptr);
		back = ptr.toDartString();
		malloc.free(ptr);

		setState(()=>{});

	}
	
	bool isOption(Option opt){
		return opt.time != -1;
	}

	chooseOption(int option){
		revisionCallback(widget.handler,option,getMTime());
		startStudy();
	}
	String arrayToString(ffi.Array<ffi.Char> array) {
		final stringList = <int>[];
		var i = 0;
		while (array[i] != 0) {
			stringList.add(array[i]);
			i++;
		}
		return String.fromCharCodes(stringList);
	}

	@override
	Widget build(BuildContext context){
		if (studyState == StudyState.FRONT ||
				studyState == StudyState.BACK ||
				studyState == StudyState.FINISHED){
			final Widget backWidget = (studyState == StudyState.BACK) 
					?	SelectableText(back, 
							style:TextStyle(fontSize : fontSize),
							) 
					: SizedBox(width: 0, height: 0);
					

			final Widget answer = (studyState == StudyState.BACK) 
					?	Row(
						children:[
							isOption(options.option1)
								? ElevatedButton(
									onPressed:()=>chooseOption(1),
									child:Text(arrayToString(options.option1.str)),
								)
								: const SizedBox(width: 0, height: 0),
							isOption(options.option2)
								? ElevatedButton(
									onPressed:()=>chooseOption(2),
									child:Text(arrayToString(options.option2.str)),
								)
								: const SizedBox(width: 0, height: 0),
							isOption(options.option3)
								? ElevatedButton(
									onPressed:()=>chooseOption(3),
									child:Text(arrayToString(options.option3.str)),
								)
								: const SizedBox(width: 0, height: 0),
							isOption(options.option4)
								? ElevatedButton(
									onPressed:()=>chooseOption(4),
									child:Text(arrayToString(options.option4.str)),
								)
								: const SizedBox(width: 0, height: 0),
							]
						)
					: ElevatedButton(
						onPressed:()=>showBack(),
						child:const Text("see the awnser"),
					);

			return Scaffold(
				appBar: AppBar(
					title:Text("$currentNewCardCount/$maxNewCardCount" 
										"($newCardCount)new "
										"$currentRevisonCount/0"
										"($revisionCount)study"
										),
				),
				
				body: Center(
					child: Column(
						mainAxisAlignment:MainAxisAlignment.center,
						children:studyState == StudyState.FINISHED
							? [Text("no more cards to study")]
							: [
								SelectableText(front, 
									style:TextStyle(fontSize : fontSize),
								), 		
								backWidget,
								answer
							]
					)
				)
			);
		}
		return Text("init state");
	}

}
