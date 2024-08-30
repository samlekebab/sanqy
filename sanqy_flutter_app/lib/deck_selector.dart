import 'package:flutter/material.dart';
import 'dart:ffi' as ffi;
import 'dart:io' show Platform, Directory;
import 'package:path/path.dart' as path;
import 'package:shared_preferences/shared_preferences.dart';
import 'add_deck.dart';
import 'deck_action.dart';

class DeckSelector extends StatefulWidget {
  const DeckSelector({super.key});
  @override
  State<DeckSelector> createState() => _DeckSelector();

}
class _DeckSelector extends State<DeckSelector>{
  List<String> decks = [];
	String? selectedDeck;
	int c=0;
	String? strDecks;
	bool isAddingDeck=false;
	bool isDeckAction=false;

  @override
  void initState() {
		super.initState();
		initDeck();
  }
	void initDeck() async {
		final SharedPreferences prefs = await SharedPreferences.getInstance();
		strDecks = await prefs.getString("decks");
		if (strDecks != null){
			decks = strDecks!.split('\n');
			c = decks.length;
		}
		setState(()=>{});
	}
	void closeDeck(){
		isDeckAction=false;
		selectedDeck = null;
		setState(()=>{});
	}
	void openDeck(int item){
		selectedDeck = decks[item];
		isDeckAction = true;
		setState(()=>{});
	}
  void save() async {
		final SharedPreferences prefs = await SharedPreferences
																			.getInstance();
		final strDecks = decks.join('\n');
		prefs.setString("decks",strDecks);
  }
	void addDeck(String? newDeck){
		isAddingDeck = false;
		if (newDeck!=null && newDeck.length>0){
			String toAdd = newDeck.substring(0,newDeck.length>15?15:newDeck.length);
			decks.add(toAdd);
			save();
		}
		setState(()=>{});
	}

	void deleteDecksItem(int idItem){
		decks.removeAt(idItem);
		setState(()=>{});
	}
  
  @override
  Widget build(BuildContext context) {
		if (isAddingDeck){
			return AddDeck(
				addDeck:addDeck
			);
		}
		if (isDeckAction){
			if  (selectedDeck == null){
				isDeckAction = false;
			}else{
				return DeckAction(
					deckName : selectedDeck!,
					closeDeck : closeDeck,	
				);
			}
		}
		return Scaffold(
			appBar: AppBar(
				title:const Text('Sanqy'),
			),
			body: ListView.builder(
				itemCount: decks.length,
				itemBuilder: (context, index) {
					final itemIndex = decks.length-index-1;
					final item = decks[itemIndex];
					return ListTile(
						onTap:()=>openDeck(itemIndex),
						title:Row(
							mainAxisAlignment:MainAxisAlignment.spaceBetween,
							children:[
								Text(item),
								TextButton(
									child: Icon(Icons.delete),
									onPressed:()=> deleteDecksItem(itemIndex),
								),
							]
						),
					);
				},
			),
			floatingActionButton: FloatingActionButton(
				onPressed: () => setState(()  {
						isAddingDeck = true;
					}),
				tooltip: 'add deck',
				child: const Icon(Icons.add),
			),
		);
  }
}
