#include "db.h"
#include <iostream>

CardDatabase::CardDatabase(const char * file):
	sqLiteDb(file,SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE)
{
	printf("opening database %s\n",file);

	//initialize if this is the creation of the db
	//query the existance of the card table
	bool isTableCard;
	SQLite::Statement   query(sqLiteDb,
		"""SELECT name FROM sqlite_master \
		WHERE type='table' AND name='card'""");
	query.executeStep();
	isTableCard = query.hasRow();
	if (!isTableCard){
		printf("creating the card table\n");
		SQLite::Statement(sqLiteDb,
			""" CREATE TABLE card \
			(uid INTEGER PRIMARY KEY,\
			 word TEXT,\
			 face INTEGER,\
			 mate INTEGER,\
			 status TEXT,\
			 revisionTime INTEGER,\
			 shown INTEGER,\
			 failed INTEGER)""").exec();

	}
	    
}
int CardDatabase::insertRow(const Card& card, int mate){
	SQLite::Statement query(sqLiteDb,
		"""INSERT INTO card \
		(word,face,mate,status,revisionTime,shown,failed) \
		VALUES (?,?,?,?,?,?,?)""");
	query.bind(1,card.word);
	query.bind(2,card.face);
	query.bind(3,mate);
	query.bind(4,card.status);
	query.bind(5,card.revisionTime);
	query.bind(6,card.shown);
	query.bind(7,card.failed);
	query.exec();
	SQLite::Statement query2(sqLiteDb,
		"""SELECT uid FROM card where rowid=last_insert_rowid()""");
	query2.executeStep();
	
	int uid = query2.getColumn(0);
	return uid;

}
void CardDatabase::setRowMate(int uid, int mate){
	SQLite::Statement query(sqLiteDb,
		"""\
	 UPDATE card SET mate=? WHERE uid=?;""");
	query.bind(1,mate);
	query.bind(2,uid);
	query.exec();

}
void CardDatabase::insertCard(TwoCards& card){
	int uidFront = insertRow(card.front,0);
	int uidBack = insertRow(card.back,uidFront);
	setRowMate(uidFront,uidBack);
	card.front.uid = uidFront;
	card.back.uid = uidBack;
}

int CardDatabase::getTwoCardArray(TwoCards** ret, int face){
	SQLite::Statement countQuery(sqLiteDb,
		"""SELECT COUNT(*) FROM card WHERE face=0""");
	countQuery.executeStep();
	int count = countQuery.getColumn(0);
	SQLite::Statement query(sqLiteDb,
		"""SELECT * FROM card AS front \
		JOIN card AS back ON front.mate=back.uid \
		WHERE front.face=?""");
	query.bind(1,face);
	TwoCards* card = new TwoCards[count];
	int i=0;
	while(query.executeStep()){
		card[i].front = 
		Card{
			query.getColumn(0),
			query.getColumn(1),
			query.getColumn(8),
			query.getColumn(2),
			query.getColumn(4),
			query.getColumn(5),
			query.getColumn(6),
			query.getColumn(7)};
		card[i].back = 
		Card{
			query.getColumn(8),
			query.getColumn(9),
			query.getColumn(0),
			query.getColumn(10),
			query.getColumn(12),
			query.getColumn(13),
			query.getColumn(14),
			query.getColumn(15)};
		i++;



	}
	*ret = card;
	return count;

}
int CardDatabase::deleteCardAndMate (int uid){

	SQLite::Statement query(sqLiteDb,
		"""SELECT mate FROM card WHERE \
		uid=?""");
	query.bind(1,uid);

	//if exist
	if (query.executeStep()){
		int uidMate = query.getColumn(0);
		SQLite::Statement query2(sqLiteDb,
			"""DELETE FROM card \
			WHERE uid=?""");
		query2.bind(1,uidMate);
		query2.exec();
		query2.reset();
		query2.bind(1,uid);
		query2.exec();
		return uidMate;
	}
	return 0;
}
void CardDatabase::setCardOption(int revisionTime, const Option* option, int uid){
	SQLite::Statement query(sqLiteDb,
		"""\
	 UPDATE card SET revisionTime=?,status=?,shown=?,failed=? WHERE uid=?""");
	query.bind(1,revisionTime);
	query.bind(2,option->status);
	query.bind(3,option->shown);
	query.bind(4,option->failed);
	query.bind(5,uid);
	query.exec();

}
Card CardDatabase::getCard(int cardID){

	SQLite::Statement query(sqLiteDb,
		"""SELECT * FROM card \
		WHERE uid=?""");
	query.bind(1,cardID);
	query.executeStep();
	return Card {
			query.getColumn(0),
			query.getColumn(1),
			query.getColumn(3),
			query.getColumn(2),
			query.getColumn(4),
			query.getColumn(5),
			query.getColumn(6),
			query.getColumn(7)};
	

}
void CardDatabase::updateCard(char* newWord,int uid){
	SQLite::Statement query(sqLiteDb,
		"""\
	 UPDATE card SET word=? WHERE uid=?;""");
	query.bind(1,newWord);
	query.bind(2,uid);
	query.exec();
}
void CardDatabase::resetAllCards(const char* status, int revTime){
	SQLite::Statement query(sqLiteDb,
		"""\
	 UPDATE card SET status=?,revisionTime=?,shown=0,failed=0 """);
	query.bind(1,status);
	query.bind(2,revTime);
	query.exec();
}
