class Time{
public:
    Time(int = 0, int = 0);
    Time(int, int, std::string);
    
    //Test Print
    void printSched();
    void printTM();
    
    
    bool operator==(Time);
    bool operator<(Time);
    bool operator>(Time);
    
    int operator-(Time);

private:
    int hh, mm, tm;
};

class Interval{
public:
    Time start, end;
    
    Interval(Time, int);
    Interval(Time, Time);
    Interval overlap(Interval i2);
    
    void printDur();
    int duration();
    
};

void Time::printSched(){
	printf("%d:%d ", hh, mm);
}

void Time::printTM(){
	printf("%d\n", tm);
}

Time::Time(int hh, int mm){
	Time::hh = hh;
	Time::mm = mm;
	Time::tm = (hh * 60) + mm;
}

Time::Time(int hh, int mm, std::string ampm){
	Time::hh = hh;
	Time::mm = mm;
	if(ampm == "AM" || ampm == "am"){
		if(hh == 12 && (ampm == "AM" || ampm == "am")){
			Time::hh = 0;
			Time::tm = mm;
		} else {
			Time::tm = (hh*60) + mm;
		}
	} else if(ampm == "PM" || ampm == "pm"){
		if(hh == 12 && (ampm == "PM" || ampm == "pm")){
			Time::hh = 12;
			Time::tm = (720 + (hh*60)) + mm;
		} else {
			Time::hh+=12;
			Time::tm = (720 + (hh*60)) + mm;
		}
	} else {
		Time::tm = 0;
	}
}

bool Time::operator == (Time other){
	if(Time::tm == other.tm){
		return true;
	}
	return false;
}

bool Time::operator < (Time other){
	if(Time::tm < other.tm){
		return true;
	}
	return false;
}

bool Time::operator > (Time other){
	if(Time::tm > other.tm){
		return true;
	}
	return false;
}

int Time::operator - (Time other){
	return Time::tm - other.tm;	
}

//Interval - Need to put 0 in the constructor time or else Compiler asked what value u want to pass;
Interval::Interval(Time t1, Time t2){
	Interval::start = t1;
	Interval::end = t2;
}

Interval::Interval(Time t1, int t2){
	int temp(t1 - Time(0,0));
    Interval::start = t1;
    Interval::end = Time((temp + t2)/60, (temp + t2)%60);
}

Interval Interval::overlap(Interval i2){
	Time start_time;
	Time end_time;
	if(i2.start > start && i2.end < end){
		start_time = Time(i2.start);
		end_time = Time(i2.end);
		//i2start.printSched();
		//printf("- ");
		//i2.end.printSched();
	} else if(
	(i2.start > start && i2.end > end) &&
	(end > i2.start)
	){
		start_time = Time(i2.start);
		end_time = Time(i2.end);
		//i2.start.printSched();
		//printf("- ");
		//i2.end.printSched();
	} else if((i2.start < start && i2.end < end) &&
	(i2.end > start)
	){
		start_time = Time(start);
		end_time = Time(i2.end);
		//i1.start.printSched();
		//printf("- ");
		//i2.end.printSched();
	} else if(start == i2.start && end < i2.end){
		start_time = Time(start);
		end_time = Time(end);
		//i1.start.printSched();
		//printf("- ");
		//i1.end.printSched();
	} else if(start == i2.start && end > i2.end){
		start_time = Time(i2.start);
		end_time = Time(i2.end);
		//i2.start.printSched();
		//printf("- ");
		//i2.end.printSched();
	}
	Interval I3 = Interval(start_time, end_time);
	return I3;
}

int Interval::duration(){
	return Interval::end - Interval::start;
}

void Interval::printDur(){
	printf("%d\n", duration());
}
