//#include <iostream>
//#include <string>
//#include <vector>
//using namespace std;
//class Alarm;
//
//class AlarmClock {
//public:
//    // Your constructors and destructor.
//    //这里构造函数里要构造出来m_alarms
//    AlarmClock();
//    ~AlarmClock();
//    void AddAlarm(Alarm* alarm);
//    void Input();
//    void TimeElapse();
//    Alarm* ptr;
//
//private:
//    std::vector<Alarm*> m_alarms; //m_alarms为一个vector对象，它可以存放Alarm*类型的对象，即可以存放指向Alarm对象的指针
//    int alarm_num;//从input中提取总共有多少个alarm
//    int real_time;
//    Alarm* alarm;
//    int count;
//    
//};
//
//AlarmClock::AlarmClock() :real_time(0),alarm_num(0),alarm(NULL),count(0),ptr(NULL) {
//    
//}
//
//AlarmClock::~AlarmClock() {
//    for (int i = 0; i < (*this).alarm_num; i++) {
//        delete (*this).m_alarms[i];
//    }
//}
//
//
//
//class Alarm {
//public:
//    Alarm();// Your constructors and destructor.
//    ~Alarm();
//    //这里构造函数要用m_alarms里面存的clock的名字与起始时间给alarm_name与alarm_time赋值
//    virtual void Trigger();
//    string R_OR_S;
//    int alarm_time_minute;
//    string alarm_time_str;
//    string alarm_name;
//    int is_valid;
//    int is_tomorrow;
//
//
//protected:
//    // Declare protected members so that child classes have access to them.
//    // ...
// 
//
//};
//Alarm::Alarm():alarm_time_minute(0),is_valid(1),is_tomorrow(0) {
//    
//}
//Alarm::~Alarm() {
//
//}
//
//void Alarm::Trigger() {
//   
//}
//
//class RepeatableAlarm : public Alarm
//{
//    //这里要写的是RepeatableAlarm的属性 （函数）每天同一时间响铃
//public:
//    virtual void Trigger();
//    
//};
//
//class SnoozeableAlarm : public Alarm
//{
//    //这里要写的是SnoozeableAlarm的属性 （函数）如果snooze——button==N 则不再响铃，如果snooze_button==Y,则隔十分钟再响铃（因为不是数字，所以用的是字符串的替代法）
//    //element有 snooze button对应“Y” “N” 两种不同的结果 
//public:
//    virtual void Trigger();
//    
//};
//
//void RepeatableAlarm::Trigger() {
//    (*this).is_valid = 1;
//    (*this).is_tomorrow = 0;
//    cout << "Alarm " << (*this).alarm_name << " has triggered at " << (*this).alarm_time_str <<"." << endl;//因为每天都会响铃，所以不用delete
//}
//
//void SnoozeableAlarm::Trigger() {  //今天响铃完就不会响了，所以要delete
//    (*this).is_tomorrow = 0;
//    cout << "Alarm " << (*this).alarm_name << " has triggered at " << (*this).alarm_time_str <<". Snooze? (Y/N)" << endl;
//    string answer;
//    //while (1) {
//        cin >> answer;
//        if (answer == "Y") {     //还需要处理如果定了23：50的闹钟，睡到了00：00怎么办？
//            (*this).is_valid = 1;
//            (*this).alarm_time_minute += 10;
//           
//            int result = (*this).alarm_time_minute / 60;
//            int remainder = (*this).alarm_time_minute % 60;
//            if (result >= 24) {
//                result = result-24;
//                (*this).is_tomorrow = 1;
//                (*this).alarm_time_minute -= 1440;
//            }
//         
//            string result_str, remainder_str;
//            if (result == 0) {
//                result_str = "00";
//            }
//            else if (result >= 1 && result <= 9) {
//                result_str = "0" + to_string(result);
//            }
//            else {
//                result_str = to_string(result);
//            }
//            if (remainder == 0) {
//                remainder_str = "00";
//            }
//            else if (remainder >= 1 && remainder <= 9) {
//                remainder_str = "0" + to_string(remainder);
//            }
//            else {
//                remainder_str = to_string(remainder);
//            }
//           
//            (*this).alarm_time_str = result_str + ":" + remainder_str;
//  
//            /*if ((*this).is_tomorrow == 0) {
//                cout << "Alarm " << (*this).alarm_name << " has triggered at " << (*this).alarm_time_str << ". Snooze? (Y/N)" << endl;
//            }*/
//            if((*this).is_tomorrow==1) {
//                (*this).is_valid = 1;
//                //(*this).is_tomorrow = 0;
//                //break;
//            }
//        }
//        else{
//            (*this).is_valid = 0;
//            (*this).is_tomorrow = 0;
//            //break;
//        }
//    
//}
//
//
///**************** Implementations ******************/
//void AlarmClock::AddAlarm(Alarm* alarm) {  //这里传入的参数是alarm，为指向Alarm对象的指针  这个参数是在其他函数里create的
//    (*this).m_alarms.push_back(alarm);
//}
//
//void AlarmClock::Input() {
//    //一共三天，在每天的开头会调用这个函数，即在00：00时
//    //这里需要做的就是建立输入的窗口
//    for (int k = 0; k < (*this).alarm_num; k++) {
//        (*this).m_alarms[k]->is_tomorrow = 0;
//    }
//    int add_num;
//    cin >> add_num;
//    (*this).alarm_num += add_num;
//    for (int i = 0; i < add_num; i++) {      
//        string a, b, c;
//        cin >> a >> b >> c;
//        if (a == "R") {
//            (*this).count += 1;
//            (*this).ptr = new RepeatableAlarm;
//            (*ptr).alarm_name = c;
//            (*ptr).alarm_time_minute = ((b[0] - '0') * 10 + (b[1] - '0')) * 60 + (b[3] - '0') * 10 + (b[4] - '0');
//            (*ptr).alarm_time_str = b;
//            (*ptr).R_OR_S = a;
//            (*this).AddAlarm((*this).ptr);
//        }
//        else if (a == "S") {
//            (*this).count += 1;
//            (*this).ptr = new SnoozeableAlarm;
//            (*ptr).alarm_name = c;
//            (*ptr).alarm_time_minute = ((b[0] - '0') * 10 + (b[1] - '0')) * 60 + (b[3] - '0') * 10 + (b[4] - '0');
//            (*ptr).alarm_time_str = b;
//            (*ptr).R_OR_S = a;
//            (*this).AddAlarm((*this).ptr);
//        }
//       
//    }
//
//
//}
//
//void AlarmClock::TimeElapse() {
//    //先遍历所有clock的时间，找是否有与该时刻对应的clock     &&( (*this).m_alarms[i]->is_tomorrow == 0)
//    //如果有，则调用triggle函数，如果有且不止一个，则按照add的顺序依次调用triggle函数
//    for (int i = 0; i < (*this).alarm_num; i++) {
//        if (((*this).m_alarms[i]->alarm_time_minute == (*this).real_time ) && ((*this).m_alarms[i]->is_valid == 1) && ((*this).m_alarms[i]->is_tomorrow == 0)) {
//            (*this).m_alarms[i]->Trigger();
//            
//        }
//      
//    }
//    (*this).real_time += 1;
//    if ((*this).real_time == 1440) {
//        (*this).real_time = 0;
//    }
//}

// ...

//int main() {
//    AlarmClock clock;
//    for (int days = 0; days < 3; days++) {
//        std::cout << "Do you want to add any alarms?" << std::endl;
//        clock.Input();
//      
//        for (int minute = 0; minute < 1440; minute++) {  //调用TimeElapse看看有没有符合的clock
//            clock.TimeElapse();
//        }
//       
//        std::cout << "A day has elapsed." << std::endl;
//    }
//}