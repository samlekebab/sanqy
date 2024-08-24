import 'package:flutter/material.dart';
import 'package:back_button_interceptor/back_button_interceptor.dart';

class AddDeck extends StatefulWidget{
	const AddDeck({super.key,required this.addDeck});
	final Function addDeck;
	@override
	State<AddDeck> createState() => _AddDeck();
}
class _AddDeck extends State<AddDeck>{
	String? inputText;

	@override
	void initState() {
		 super.initState();
		 BackButtonInterceptor.add(myInterceptor);
	}

	@override
	void dispose() {
		 BackButtonInterceptor.remove(myInterceptor);
		 super.dispose();
	}

	bool myInterceptor(bool stopDefaultButtonEvent, RouteInfo info) {
		if(!stopDefaultButtonEvent){
			widget.addDeck(null);
		}
		return true;
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
								labelText: 'Enter deck name',
							),
							onChanged:(String str)=>{inputText = str},
						),
						ElevatedButton(
							onPressed: () => widget.addDeck(inputText),
							child: const Text('enter'),
						),
					]
				)
			)
		);
	}
}
