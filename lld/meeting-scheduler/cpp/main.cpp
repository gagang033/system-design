#include<bits/stdc++.h>
using namespace std;
int meetingsCount = 0;
struct TimeSlot {
    long startTime, endTime;
    TimeSlot(){}
    TimeSlot(long start, long end){
        this->startTime = start;
        this->endTime = end;
    }
};

class User {
    public:
        string userId, name, email;
        User(string id, string name, string email){
            this->userId = id;
            this->name = name;
            this->email = email;
        }   
};

class FCFSSchedulingStrategy;
class MeetingScheduler;

class Meeting {
    public:
        string meetingId;
        string meetingRoomId;
        TimeSlot timeSlot;
        vector<User*> participants;

        Meeting(string meetingId, string meetingRoomId, TimeSlot timeSlot, vector<User*> participants) {
            this->meetingId = meetingId;
            this->meetingRoomId = meetingRoomId;
            this->timeSlot = timeSlot;
            this->participants = participants;
        }

        void notifyParticipants() {
            for(auto particant: participants){
                cout<<"Notification sent to "<<particant->name<<" at "<<particant->email<<" for meeting "<<meetingId<<" in room "<<meetingRoomId<<endl;
            }
        }
};

class Compare {
    public:
        bool operator()(Meeting *a, Meeting *b){
            return a->timeSlot.startTime > b->timeSlot.startTime;
        }
};

class MeetingRoom {
    public:
        string meetingRooomId;
        priority_queue<Meeting*,vector<Meeting*>,Compare> meetings;
        int capacity;

        MeetingRoom(string id, int capacity){
            this->meetingRooomId = id;
            this->capacity = capacity;
            this->meetings = priority_queue<Meeting*,vector<Meeting*>,Compare>();
        }

        bool isAvailable(int count, TimeSlot timeslot){
            if(count > this->capacity){
                return false;
            }

            vector<Meeting*> tempMeetings;
            bool isFree = true;
            while(!this->meetings.empty()){
                if(timeslot.endTime <= meetings.top()->timeSlot.startTime){
                    break;
                }
                if((timeslot.startTime >= meetings.top()->timeSlot.startTime && timeslot.startTime <= meetings.top()->timeSlot.endTime) 
                || timeslot.endTime <= meetings.top()->timeSlot.endTime){ // not free
                    isFree=false;
                    break;
                }
                tempMeetings.push_back(meetings.top());
                meetings.pop();
            }

            for(auto meeting: tempMeetings){
                meetings.push(meeting);
            }

            return isFree;
        }

        void scheduleMeeting(TimeSlot timeSlot, vector<User*> participants){
            string meetingId = to_string(meetingsCount);
            meetingsCount++;
            Meeting* meeting = new Meeting(meetingId, this->meetingRooomId, timeSlot, participants);
            meeting->notifyParticipants();
            meetings.push(meeting);
        }
};

class SchedulingStrategy {
    public:
        virtual MeetingRoom* findMeetingRoom(int count, TimeSlot timeSlot, vector<MeetingRoom*> meetingRooms) = 0;
};

class FCFSSchedulingStrategy: public SchedulingStrategy {
    public:
        MeetingRoom* findMeetingRoom(int count, TimeSlot timeSlot, vector<MeetingRoom*> meetingRooms) {
            for(auto meetingRoom: meetingRooms){
                if(meetingRoom->isAvailable(count,timeSlot))
                    return meetingRoom;
            }
            return nullptr;
        };
};



class MeetingScheduler {
    public:
        SchedulingStrategy* schedulingStrategy;
        vector<MeetingRoom*> meetingRooms;

        MeetingScheduler(SchedulingStrategy* schedulingStrategy, vector<MeetingRoom*> meetingRooms){
            this->schedulingStrategy = schedulingStrategy;
            this->meetingRooms = meetingRooms;
        }

        bool scheduleMeeting(int count, TimeSlot timeSlot, vector<User*> participants){
            MeetingRoom* meetingRoom = schedulingStrategy->findMeetingRoom(count, timeSlot, this->meetingRooms);
            if(meetingRoom == nullptr)
                return false;
            meetingRoom->scheduleMeeting(timeSlot,participants);
            return true;
        }
};


int main(){
    User* gagan = new User("123", "Gagan", "a@email.com");
    User* naveen = new User("456", "Naveen", "b@email.com");
    User* sahil = new User("789", "Sahil", "c@email.com");

    FCFSSchedulingStrategy *strategy = new FCFSSchedulingStrategy();

    MeetingRoom* a = new MeetingRoom("1",2);
    MeetingRoom* b = new MeetingRoom("2",3);

    vector<MeetingRoom*> meetingRooms = {a,b};

    MeetingScheduler* meetingScheduler = new MeetingScheduler(strategy, meetingRooms);

    if(meetingScheduler->scheduleMeeting(2,{2,4},{naveen,gagan})){
        cout<<"Meeting a scheduled"<<endl;
    }
    else {
        cout<<"Couldn't find appropriate room for meeting a"<<endl;
    }

    if(meetingScheduler->scheduleMeeting(3,{2,4},{naveen,gagan,sahil})){
        cout<<"Meeting b scheduled"<<endl;
    }
    else {
        cout<<"Couldn't find appropriate room for meeting b"<<endl;
    }

    if(meetingScheduler->scheduleMeeting(3,{3,5},{naveen,gagan,sahil})){
        cout<<"Meeting c scheduled"<<endl;
    }
    else {
        cout<<"Couldn't find appropriate room for meeting c"<<endl;
    }

    if(meetingScheduler->scheduleMeeting(4,{10,12},{naveen,gagan,sahil})){
        cout<<"Meeting d scheduled"<<endl;
    }
    else {
        cout<<"Couldn't find appropriate room for meeting d"<<endl;
    }
}