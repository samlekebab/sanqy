//gives the time in minutes, for revisions
int getMTime (){
	final zero = DateTime.parse('2000-03-30 03:44:00');
	//print("check if time ref is local : ${!zero.isUtc}");

	//return time in minutes
	final now = DateTime.now();
	//print("check if now time is local : ${!now.isUtc}");

	final timeMili = now.millisecondsSinceEpoch-zero.millisecondsSinceEpoch;
	final res =  (timeMili/1000/60).toInt();
	//print(res);
	return res;

}
