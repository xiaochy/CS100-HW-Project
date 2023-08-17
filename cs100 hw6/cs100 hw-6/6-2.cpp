//#include <iostream>
//#include <string>
//#include <vector>
//using namespace std;
//class Alarm;
//
//class AlarmClock {
//public:
//    // Your constructors and destructor.
//    //���ﹹ�캯����Ҫ�������m_alarms
//    AlarmClock();
//    ~AlarmClock();
//    void AddAlarm(Alarm* alarm);
//    void Input();
//    void TimeElapse();
//    Alarm* ptr;
//
//private:
//    std::vector<Alarm*> m_alarms; //m_alarmsΪһ��vector���������Դ��Alarm*���͵Ķ��󣬼����Դ��ָ��Alarm�����ָ��
//    int alarm_num;//��input����ȡ�ܹ��ж��ٸ�alarm
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
//    //���ﹹ�캯��Ҫ��m_alarms������clock����������ʼʱ���alarm_name��alarm_time��ֵ
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
//    //����Ҫд����RepeatableAlarm������ ��������ÿ��ͬһʱ������
//public:
//    virtual void Trigger();
//    
//};
//
//class SnoozeableAlarm : public Alarm
//{
//    //����Ҫд����SnoozeableAlarm������ �����������snooze����button==N �������壬���snooze_button==Y,���ʮ���������壨��Ϊ�������֣������õ����ַ������������
//    //element�� snooze button��Ӧ��Y�� ��N�� ���ֲ�ͬ�Ľ�� 
//public:
//    virtual void Trigger();
//    
//};
//
//void RepeatableAlarm::Trigger() {
//    (*this).is_valid = 1;
//    (*this).is_tomorrow = 0;
//    cout << "Alarm " << (*this).alarm_name << " has triggered at " << (*this).alarm_time_str <<"." << endl;//��Ϊÿ�춼�����壬���Բ���delete
//}
//
//void SnoozeableAlarm::Trigger() {  //����������Ͳ������ˣ�����Ҫdelete
//    (*this).is_tomorrow = 0;
//    cout << "Alarm " << (*this).alarm_name << " has triggered at " << (*this).alarm_time_str <<". Snooze? (Y/N)" << endl;
//    string answer;
//    //while (1) {
//        cin >> answer;
//        if (answer == "Y") {     //����Ҫ�����������23��50�����ӣ�˯����00��00��ô�죿
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
//void AlarmClock::AddAlarm(Alarm* alarm) {  //���ﴫ��Ĳ�����alarm��Ϊָ��Alarm�����ָ��  ���������������������create��
//    (*this).m_alarms.push_back(alarm);
//}
//
//void AlarmClock::Input() {
//    //һ�����죬��ÿ��Ŀ�ͷ������������������00��00ʱ
//    //������Ҫ���ľ��ǽ�������Ĵ���
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
//    //�ȱ�������clock��ʱ�䣬���Ƿ������ʱ�̶�Ӧ��clock     &&( (*this).m_alarms[i]->is_tomorrow == 0)
//    //����У������triggle������������Ҳ�ֹһ��������add��˳�����ε���triggle����
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
//        for (int minute = 0; minute < 1440; minute++) {  //����TimeElapse������û�з��ϵ�clock
//            clock.TimeElapse();
//        }
//       
//        std::cout << "A day has elapsed." << std::endl;
//    }
//}