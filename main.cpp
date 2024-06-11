#include<iostream>
#include<fstream>
using namespace std;

class Helpers;
class Date;
class Post;
class Object;
class User;
class Page;
class Controller;
class Comments;
class Activity;
class Memory;
class PostContent;

class Helpers
{
public:

    static bool CompareString(const char a[], const char b[])
    {
        for (int i = 0; a[i] != '\0'; i++)
        {
            if (a[i] != b[i])
                return false;
        }

        return true;
    }

    static int StringLength(const char* str)
    {
        int strLength = 0;

        for (int i = 0; str[i] != '\0'; i++)
            strLength++;

        return strLength;
    }

    static void StringCopy(char* str1, const char* str2)
    {
        char* temp = str1;

        for (int i = 0; str2[i] != '\0'; i++)
        {
            *temp = str2[i];
            temp++;
        }
        *temp = '\0';
    }

    static char* GetStringFromBuffer(const char* buffer)
    {
        int strLen = StringLength(buffer);
        char* str = 0;
        if (strLen > 0)
        {
            str = new char[strLen + 1];
            StringCopy(str, buffer);
        }
        return str;
    }

    static char* StrConcat(const char* a, const char* b)
    {
        int strLen1 = StringLength(a);
        int strLen2 = StringLength(b);
        int len = strLen1 + strLen2;

        char* str = 0;
        if (len > 0)
        {
            str = new char[len + 1];
           
            int index = 0;

            for (int i = 0; i < strLen1; i++)
            {
                str[index] = a[i];
                index++;
            }
            
            for (int i = 0; i < strLen2; i++)
            {
                str[index] = b[i];
                index++;
            }
            str[index] = '\0';
        }
        return str;
    }


};

//--------------------------------DATE-------------------------------------------

class Date
{
    int day;
    int month;
    int year;
    
public:
    static Date currentDate;
    Date(int, int, int);
    void SetValues(int, int, int);
    void Display();
    void ReadFromFile(ifstream&);
    bool CompareDatesForHome(Date&);
    int DateDifference(Date&);
    int GetDay();
    int GetMonth();
    int GetYear();
};
Date Date::currentDate(0,0,0);

//--------------------------------POST-------------------------------------------

class Post
{
    char* Id;
    Date SharedDate;
    char* text;
    Object* SharedBy;
    Object** LikedBy;
    Comments** comments;
    int totalComments;
    int Likes;
    PostContent* activity;
    

public:
    static int TotalPosts;
    Post(const char*, const char*, Object*, Date);
    char* GetId();
    void SetSharedBy(Object*&);
    void SetLikedBy(Object*&);
    void ReadDataFromFile(ifstream&);
    char* GetSharedBy();
    void GetSharedByDisplay();
    char* GetText();
    void GetDate();
    virtual void DisplayPost();
    void DisplayLikedBy();
    void DisplayDifference(Post*&);
    void AddComment(Comments*&);
    void AddActivity(PostContent*&);
    void SelectPostsForHome();
    void SetPostID();
    virtual ~Post();
};
int Post::TotalPosts = 0;

//--------------------------------MEMORY-------------------------------------------

class Memory :public Post
{
    Post* OriginalPost;

public:
    Memory(Post*,const char*, Object*);
    void DisplayPost();
    ~Memory();
};

class Object
{
    int totalPosts;
    char* ID;

protected:
    Post** Timeline;

public:
    Object();
    void SetID(char*);
    char* GetID();
    virtual void Display();
    void AddPostToTimeline(Post*);
    void ViewTimeline();
    void PostsForHome();
    Post* AvailablePosts(const char*);
    virtual ~Object();
};


//--------------------------------PAGE-------------------------------------------

class Page : public Object
{
    char* Title;

public:
    Page();
    void ReadDataFromFile(ifstream&);
    void Display();
    ~Page();
};

//--------------------------------USER-------------------------------------------

class User : public Object
{

    char* Fname;
    char* Lname;
    User** FriendList;   
    Page** LikedPages;   
    int totalFriends;
    int totalPages;

public:
    User();
    void AddFriend(User* const&);
    void ReadDataFromFile(ifstream&);
    void LikePage(Page* const&);
    char* GetFname();
    char* GetLname();
    void Display();
    void ViewFriendList();
    void ViewLikedPages();
    void ViewHome();
    ~User();
};


//--------------------------------CONTROLLER-------------------------------------------

class Controller
{
    int totalUsers;
    int totalPages;
    int totalPosts;
    User** AllUsers;
    Page** AllPages;
    Post** AllPosts;


public:
    Controller();
    User*& SearchUserByID(const char*);
    Page* SearchPageByID(const char*);
    Post* SearchPostByID(const char*);
    void LoadAllUsers(const string&);
    void LoadAllPages(const string&);
    void LoadAllPosts(const string&);
    void LoadAllComments(const string&);
    void LoadActivities(const string&);
    Object* SearchObject(const char*);
    void LinkUsersAndPages(const string&);
    void UserDisplay(const char*);
    void ViewPage(const char*);
    void PageDisplay(const char*);
    void ViewPost(const char*);
    void PostDisplay(const char*);
    void LikeAPost(const char*, const char*);
    void ViewLikes(const char*);
    void LoadData();
    void DisplayFunctionalities();
    ~Controller();
};

//--------------------------------COMMENTS-------------------------------------------

class Comments
{
    char* ID;
    Object* CommentBy;
    char* text;
    

public:
    static int TotalComments;
    Comments();
    Comments(const char*, Object*,const char*);
    void SetCommentsID();
    void Display();
    ~Comments();
};
int Comments::TotalComments = 0;

//--------------------------------POST CONTENT-------------------------------------------

class PostContent
{
public:
    virtual void Display();
    virtual void SetActivity();
    virtual ~PostContent();
};

//--------------------------------ACTIVITY-------------------------------------------

class Activity : public PostContent
{
    int type;
    char* value;

public:
    Activity();
    Activity(int, char*);
    void Display();
    ~Activity();
};

//---------------------Date Class--------------------------

Date::Date(int d = 0, int m = 0, int y = 0)
{
    day = d;
    month = m;
    year = y;
}

void Date::SetValues(int d, int m, int y)
{
    day = d;
    month = m;
    year = y;
}


bool Date::CompareDatesForHome(Date& date)
{
    if ((date.GetDay() <= day && date.GetDay() >= (day- 2)) && date.GetMonth() == month && date.GetYear()==year)
        return true;

    else
        return false;
}

int Date::DateDifference(Date& date)
{
    return year - date.GetYear();
}

int Date::GetDay()
{
    return day;
}

int Date::GetMonth()
{
    return month;
}

int Date::GetYear()
{
    return year;
}

void Date::Display()
{
    if ((day == currentDate.GetDay()) && (month == currentDate.GetMonth()) && (year == currentDate.GetYear()))
        cout << "today";

    else if ((day + 1 == currentDate.GetDay()) && (month == currentDate.GetMonth()) && (year == currentDate.GetYear()))
        cout << "1 day";

    else if ((day + 2 == currentDate.GetDay()) && (month == currentDate.GetMonth()) && (year == currentDate.GetYear()))
        cout << "2 day";

    else if ((day + 3 == currentDate.GetDay()) && (month == currentDate.GetMonth()) && (year == currentDate.GetYear()))
        cout << "3 day";

    else if ((day + 4 == currentDate.GetDay()) && (month == currentDate.GetMonth()) && (year == currentDate.GetYear()))
        cout << "4 day";

    else if ((day + 5 == currentDate.GetDay()) && (month == currentDate.GetMonth()) && (year == currentDate.GetYear()))
        cout << "5 day";

    else if ((day + 6 == currentDate.GetDay()) && (month == currentDate.GetMonth()) && (year == currentDate.GetYear()))
        cout << "6 day";

    else if ((day + 7 == currentDate.GetDay()) && (month == currentDate.GetMonth()) && (year == currentDate.GetYear()))
        cout << "7 day";

    else
        cout << day << "/" << month << "/" << year;
    
}

void Date::ReadFromFile(ifstream& fin)
{
    fin >> day;
    fin >> month;
    fin >> year;
}

//------------------------------Post Class------------------------------

Post::Post(const char* id=nullptr, const char* txt=nullptr, Object* sharedby=nullptr, Date date=Date::currentDate)
{
    if(id)
        Id = Helpers::GetStringFromBuffer(id);
    if(txt)
        text = Helpers::GetStringFromBuffer(txt);
    SharedBy = sharedby;
    SharedDate = date;
    LikedBy = nullptr;
    comments = nullptr;
    totalComments = 0;
    Likes = 0;
    activity = nullptr;

}

char* Post::GetId()
{
    return Id;
}

void Post::SetSharedBy(Object*& obj)
{
    if (SharedBy == nullptr)
        SharedBy = obj;

}

void Post::SetLikedBy(Object*& obj)
{
    if (LikedBy == nullptr)
    {
        LikedBy=new Object*[10];

        for (int i = 0; i < 10; i++)
            LikedBy[i] = nullptr;

        LikedBy[0] = obj;

        Likes++;

        return;
    }

    else
    {
        for (int i = 0; i < 10; i++)
        {
            if (LikedBy[i] == nullptr)
            {
                LikedBy[i] = obj;
                Likes++;

                return;
            }
        }
    }

}

void Post::ReadDataFromFile(ifstream& fin)
{
    char temp1[10];
    fin >> temp1;
    Id = Helpers::GetStringFromBuffer(temp1);

    SharedDate.ReadFromFile(fin);

    char temp2[500];
    /*fin >> std::ws;*/
    fin.ignore();
    fin.getline(temp2, 500);
    text = Helpers::GetStringFromBuffer(temp2);

}

char* Post::GetSharedBy()
{
    if(SharedBy)
        return SharedBy->GetID();
    
}

void Post::GetSharedByDisplay()
{
   SharedBy->Display();
}

char* Post::GetText()
{
    return text;
}

void Post::GetDate()
{
    SharedDate.Display();
}

void Post::DisplayPost()
{
    cout << "---";
    SharedBy->Display();
    cout<< "(";
    SharedDate.Display();
    cout << ")" << endl;
    cout << "\n(" << Id << ")\n" << endl;
    SharedBy->Display();
    if(activity)
        activity->Display();
    cout << endl;
    cout << "\t'" << text << "'" << endl;
    cout << endl;
    for (int i = 0; i < totalComments; i++)
        comments[i]->Display();

}

void Post::DisplayDifference(Post*& pst)
{
    int x = this->SharedDate.DateDifference(pst->SharedDate);
    if (x > 0)
        cout << "\n------------" << x << " years ago------------" << endl;
    else if(x==0)
        cout << "\n------------few days ago------------" << endl;
}

void Post::AddComment(Comments*& cmt )
{
    if (comments == nullptr)
    {
        comments = new Comments * [10];

        for (int i = 0; i < 10; i++)
            comments[i] = nullptr;

        comments[0] = cmt;

        totalComments++;

        return;
    }

    else
    {
        for (int i = 0; i < 10; i++)
        {
            if (comments[i] == nullptr)
            {
                comments[i] = cmt;
                totalComments++;

                return;
            }
        }
    }
}

void Post::AddActivity(PostContent*& act)
{
    if (activity == nullptr)
    {
        activity = act;
    }
}

void Post::DisplayLikedBy()
{
    for (int i = 0; i < Likes; i++)
    {
        cout << LikedBy[i]->GetID()<<"- ";
        LikedBy[i]->Display();
        cout << endl;
    }
}

void Post::SelectPostsForHome()
{
    bool check = false;

    check = Date::currentDate.CompareDatesForHome(SharedDate);

    if (check)
    {
        cout << "\n-----------------------------------------------------------" << endl;
        this->DisplayPost();
        cout << "-----------------------------------------------------------\n" << endl;
    }
        

    return;
}

void Post::SetPostID()
{
    char temp[10];
    int numb = TotalPosts + 1;

    _itoa_s(numb, temp, 10);

    Id = Helpers::StrConcat("post", temp);

    TotalPosts++;
}

Post::~Post()
{
    if (Id)
        delete[] Id;

    if (text)
        delete[] text;

    if (LikedBy)
    {
        delete[] LikedBy;
    }

    if (comments)
    {
        for (int i = 0; i < totalComments; i++)
            delete comments[i];
        delete[] comments;
    }

    if (activity)
        delete[] activity;

}

//---------------------------Memory Class-----------------------

Memory::Memory(Post* pst=nullptr, const char* text=nullptr, Object* obj=nullptr) : Post(nullptr, text, obj, Date::currentDate)
{
    OriginalPost = pst;
    this->SetPostID();
}

void Memory::DisplayPost()
{
    if (OriginalPost == nullptr)
    {
        cout << "No memory to share :(" << endl;
    }

    else
    {
        cout << "---";
        this->GetSharedByDisplay();
        cout<< " (";
        this->GetDate();
        cout << ")" << endl;
        cout << "\nShared a memory:\n" << endl;
        cout <<"("<< this->GetId()<<")" << endl;
        cout << "\n\t'" <<this->GetText() << "'" << endl;
        cout << "\n\t\t'" << OriginalPost->GetText() << "'" << endl;
        this->DisplayDifference(OriginalPost);
    }
}

Memory::~Memory()
{
}

//--------------------------Post Content------------------------

void PostContent::Display()
{
}

void PostContent::SetActivity()
{
}

PostContent::~PostContent()
{
}

//--------------------------Activity Class--------------------------

Activity::Activity()
{
    type = 0;
    value = nullptr;
   
}

Activity::Activity(int i, char* c)
{
    type = i;
    value = Helpers::GetStringFromBuffer(c);
}

void Activity::Display()
{
    if (type == 1)
        cout << " is feeling" << value<<"!" << endl;
    else if (type == 2)
        cout << " is thinking about" << value<<"!" << endl;
    else if (type == 3)
        cout << " is making" << value<<"!" << endl;
    else if (type == 4)
        cout << " is celebrating" << value<<"!" << endl;
}

Activity::~Activity()
{
    if (value)
        delete[] value;
}

//--------------------------Object Class----------------------------

Object::Object()
{
    ID = nullptr;
    Timeline = nullptr;
    totalPosts = 0;
}

void Object::SetID(char* c)
{
    ID = Helpers::GetStringFromBuffer(c);
}

char* Object::GetID()
{
    return ID;
}

void Object::Display()
{
    cout << ID << endl;
}

void Object::AddPostToTimeline(Post* pst)
{
    if (Timeline == nullptr)
    {
        Timeline = new Post * [10];

        for (int i = 0; i < 10; i++)
            Timeline[i] = nullptr;

        Timeline[0] = pst;

        totalPosts++;

        return;
    }
    else
    {
        for (int i = 0; i < 10; i++)
        {
            if (Timeline[i] == nullptr)
            {
                Timeline[i] = pst;

                totalPosts++;

                return;
            }
        }
    }
}

void Object::ViewTimeline()
{
    cout << endl;
    for (int i = 0; i < totalPosts; i++)
    {
        cout << "-----------------------------------------------------------" << endl;
        Timeline[i]->DisplayPost();
    }

}

void Object::PostsForHome()
{
    for (int i = 0; i < totalPosts; i++)
        Timeline[i]->SelectPostsForHome();
}

Post* Object::AvailablePosts(const char* id)
{
    for (int i = 0; i < totalPosts; i++)
    {
        if(Helpers::CompareString(id, Timeline[i]->GetId()))
            return Timeline[i];
    }

    return nullptr;
}

Object::~Object()
{
    if (ID)
        delete[] ID;

    if (Timeline)
    {
        for (int i = 0; i < totalPosts; i++)
        {
            if(Timeline[i])
                delete Timeline[i];
        }
         
        delete[] Timeline;
    }
    

}

//--------------------------Page Class---------------------------------

Page::Page() :Object()
{
    Title = nullptr;
}

void Page::ReadDataFromFile(ifstream& fin)
{
    char temp[50];

    fin >> temp;
    Object::SetID(temp);

    if (Title == nullptr)
    {
        fin.getline(temp, 50);
        Title = Helpers::GetStringFromBuffer(temp);
    }

}

void Page::Display()
{
    cout <<Title;
}

Page::~Page()
{
    if (Title)
        delete[] Title;
}

//-----------------------------User Class-----------------------------

User::User() :Object()
{
    Fname = nullptr;
    Lname = nullptr;
    FriendList = nullptr;
    LikedPages = nullptr;
    totalFriends = 0;
    totalPages = 0;
}

void User::AddFriend(User* const& frnd)
{
    if (FriendList == nullptr)
    {
        FriendList = new User * [10];

        for (int i = 0; i < 10; i++)
            FriendList[i] = nullptr;

        FriendList[0] = frnd;

        totalFriends++;

        return;
    }
    else
    {
        for (int i = 0; i < 10; i++)
        {
            if (FriendList[i] == nullptr)
            {
                FriendList[i] = frnd;

                totalFriends++;

                return;
            }
        }
    }
}

void User::ReadDataFromFile(ifstream& file)
{
    char temp[10];

    file >> temp;
    Object::SetID(temp);

    file >> temp;
    if (Fname == nullptr)
    {
        Fname = Helpers::GetStringFromBuffer(temp);
    }

    file >> temp;
    if (Lname == nullptr)
    {
        Lname = Helpers::GetStringFromBuffer(temp);
    }

}

void User::LikePage(Page* const& pg)
{
    if (LikedPages == nullptr)
    {
        LikedPages = new Page * [10];

        for (int i = 0; i < 10; i++)
            LikedPages[i] = nullptr;

        LikedPages[0] = pg;

        totalPages++;

        return;
    }
    else
    {
        for (int i = 0; i < 10; i++)
        {
            if (LikedPages[i] == nullptr)
            {
                LikedPages[i] = pg;

                totalPages++;

                return;
            }
        }
    }
}

char* User::GetFname()
{
    return Fname;
}

char* User::GetLname()
{
    return Lname;
}

void User::Display()
{
    cout << Fname << " " << Lname;
}

void User::ViewFriendList()
{
    for (int i = 0; i < totalFriends; i++)
    {
        cout << FriendList[i]->GetID()<<"- ";
        FriendList[i]->Display();
        cout << endl;
    }
}

void User::ViewLikedPages()
{
    for (int i = 0; i < totalPages; i++)
    {
        cout << LikedPages[i]->GetID()<<"- ";
        LikedPages[i]->Display();
        cout << endl;
    }
}

void User::ViewHome()
{
    this->PostsForHome();

    for (int i = 0; i < totalFriends; i++)
        FriendList[i]->PostsForHome();

    for (int i = 0; i < totalPages; i++)
        LikedPages[i]->PostsForHome();

}


User::~User()
{

    if (Fname)
        delete[] Fname;

    if (Lname)
        delete[] Lname;

    if (FriendList)
    {
        delete[] FriendList;
    }
    
    if (LikedPages)
    {
        delete[] LikedPages;
    }
    
}

//---------------------Comments-----------------------

Comments::Comments()
{
    ID = nullptr;
    CommentBy = nullptr;
    text = nullptr;
}

Comments::Comments(const char* c1=nullptr, Object* obj=nullptr, const char* c2=nullptr)
{
    if (c1 == nullptr)
        SetCommentsID();
    else
        ID = Helpers::GetStringFromBuffer(c1);

    if (c2)
        text = Helpers::GetStringFromBuffer(c2);

    CommentBy = obj;
       
}

void Comments::SetCommentsID()
{
    char temp[10];
    int numb = TotalComments + 1;

    _itoa_s(numb, temp, 10);

    ID = Helpers::StrConcat("c", temp);

    TotalComments++;
}

void Comments::Display()
{
    cout << "\t\t";
    CommentBy->Display();
    cout <<":'"<< text <<" '"<< endl;
    
}

Comments::~Comments()
{
    if (ID)
        delete[] ID;

    if (text)
        delete[] text;
}

//--------------------------Controller------------------------------

Controller::Controller()
{
    totalUsers = 0;
    totalPages = 0;
    totalPosts = 0;
    AllPages = nullptr;
    AllUsers = nullptr;
    AllPosts = nullptr;
}



User*& Controller::SearchUserByID(const char* c)
{
    for (int i = 0; i < totalUsers; i++)
    {
        if (Helpers::CompareString(c, AllUsers[i]->GetID()))
            return AllUsers[i];
    }

    User* temp = nullptr;

    return temp;
}

Page* Controller::SearchPageByID(const char* c)
{
    for (int i = 0; i < totalPages; i++)
    {
        if (Helpers::CompareString(c, AllPages[i]->GetID()))
            return AllPages[i];
    }

    return nullptr;
}

Post* Controller::SearchPostByID(const char* c)
{
    for (int i = 0; i < totalPosts; i++)
    {
        if (Helpers::CompareString(c, AllPosts[i]->GetId()))
            return AllPosts[i];
    }

    return nullptr;
}

void Controller::LoadAllUsers(const string& filename)
{
    ifstream fin(filename);

    if (!fin)
    {
        cout << "File cannot open!" << endl;

        return;
    }

    fin >> totalUsers;

    AllUsers = new User * [totalUsers];

    for (int i = 0; i < totalUsers; i++)
    {
        AllUsers[i] = new User;
        AllUsers[i]->ReadDataFromFile(fin);

    }

}

void Controller::LoadAllPages(const string& filename)
{
    ifstream fin(filename);

    if (!fin)
    {
        cout << "File cannot open!" << endl;

        return;
    }

    fin >> totalPages;

    AllPages = new Page * [totalPages];

    for (int i = 0; i < totalPages; i++)
    {
        AllPages[i] = new Page;
        AllPages[i]->ReadDataFromFile(fin);
    }
}

void Controller::LoadAllPosts(const string& filename)
{
    ifstream fin(filename);

    if (!fin)
    {
        cout << "File cannot open!" << endl;

        return;
    }

    fin >> totalPosts;

    Post::TotalPosts = totalPosts;

    AllPosts = new Post * [totalPosts];

    for (int i = 0; i < totalPosts; i++)
    {
        AllPosts[i] = new Post;
        AllPosts[i]->ReadDataFromFile(fin);

        char temp[5];

        fin >> temp;

        Object* obj1 = SearchObject(temp);
        AllPosts[i]->SetSharedBy(obj1);

        Object** obj2 = new Object * [10];

        for (int i = 0; i < 10; i++)
            obj2[i] = nullptr;

        int index = 0;

        fin >> temp;
        while (!Helpers::CompareString(temp, "-1") && index<=10)
        {
            obj2[index] = SearchObject(temp);
            AllPosts[i]->SetLikedBy(obj2[index]);
            index++;

            fin >> temp;
        }
       
        obj1->AddPostToTimeline(AllPosts[i]);

        delete[] obj2;
    }
}

void Controller::LoadAllComments(const string& filename)
{
    ifstream fin(filename);

    if (!fin)
    {
        cout << "File cannot open!" << endl;

        return;
    }

    int total = 0;

    fin >> total;

    Comments::TotalComments = total;

    char cID[5], pID[10], uID[5];
    char text[500];

    for (int i = 0; i < total; i++)
    {
        
        fin >> cID;
        fin >> pID;

        Post* temp2 = SearchPostByID(pID);

        fin >> uID;

        Object* temp3 = SearchObject(uID);

        fin.getline(text, 500);


        Comments* temp1 = new Comments(cID, temp3, text);

        temp2->AddComment(temp1);

    }
}

void Controller::LoadActivities(const string& filename)
{
    ifstream fin(filename);

    if (!fin)
    {
        cout << "File cannot open!" << endl;

        return;
    }

    int total = 0;

    fin >> total;

    char pID[10], value[100];
    int type;

    for (int i = 0; i < total; i++)
    {
        fin >> pID;
        Post* temp1 = SearchPostByID(pID);

        fin >> type;

        fin.getline(value, 100);

        PostContent* temp2 = new Activity(type, value);
       
        temp1->AddActivity(temp2);
    }

}

Object* Controller::SearchObject(const char* c)
{
    Object* obj = SearchUserByID(c);

    if (obj == nullptr)
    {
        obj = SearchPageByID(c);

        return obj;
    }
    else
        return obj;

}

void Controller::LinkUsersAndPages(const string& filename)
{
    ifstream fin(filename);

    if (!fin)
    {
        cout << "File cannot open!" << endl;
        return;
    }

    char temp1[10];
    fin >> temp1;

    while (!Helpers::CompareString(temp1, "-1"))
    {

        User* temp2 = SearchUserByID(temp1);

        char temp3[10];

        fin >> temp3;

        while (!Helpers::CompareString(temp3, "-1"))
        {

            temp2->AddFriend(SearchUserByID(temp3));

            fin >> temp3;

        }

        char temp4[10];

        fin >> temp4;

        while (!Helpers::CompareString(temp4, "-1"))
        {
            temp2->LikePage(SearchPageByID(temp4));

            fin >> temp4;
        }

        fin >> temp1;
    }


}

void Controller::UserDisplay(const char* c)
{
    User* temp = SearchUserByID(c);

    if (temp == nullptr)
    {
        cout << "User not found :(" << endl;
        return;
    }
        
    cout << "\nCurrent User:\t" << temp->GetID() << "-" << temp->GetFname() << " " << temp->GetLname() << endl;

    cout << "\n\n-----------------------------------------------------------" << endl;
    cout << "Command:\tFriends Lists" << endl;
    cout << "-----------------------------------------------------------\n" << endl;
    temp->ViewFriendList();

    cout << "\n\n-----------------------------------------------------------" << endl;
    cout << "Command:\tLiked Pages" << endl;
    cout << "-----------------------------------------------------------\n" << endl;
    temp->ViewLikedPages();


    cout << "\n\n-----------------------------------------------------------" << endl;
    cout << "Command:\tShare a memory" << endl;
    cout << "-----------------------------------------------------------\n" << endl;
    Post* pst = temp->AvailablePosts("post10");
    if (pst != nullptr)
    {
        Memory* memPtr = new Memory(pst, "Never thought I will be able to do!", temp);
        temp->AddPostToTimeline(memPtr);
        cout << temp->GetFname() << " " << temp->GetLname() << " shared a memory of " << pst->GetId() << endl<<endl;
        memPtr->DisplayPost();
    }

  

    cout << "\n\n-----------------------------------------------------------" << endl;
    cout << "Command:\tTimeLine" << endl;
    temp->ViewTimeline();

    cout << "\n\n-----------------------------------------------------------" << endl;
    cout << "Command:\tHomePage (";
    temp->Display();
    cout << ")" << endl;
    cout << "-----------------------------------------------------------\n" << endl;
    temp->ViewHome();

    cout << "\n\n-----------------------------------------------------------" << endl;
    cout << "Command:\tAdd a comment" << endl;
    cout << "-----------------------------------------------------------\n" << endl;
    Post* pst1 = SearchPostByID("post5");
    if (pst1 != nullptr)
    {
        Comments* cmt = new Comments(nullptr, temp, " kiya baat hai !!!");
        pst1->AddComment(cmt);
        cout << temp->GetFname() << " " << temp->GetLname() << " commented on " << pst1->GetId() << endl << endl;
        pst1->DisplayPost();
    }


}

void Controller::ViewPage(const char* c)
{
    Page* temp = SearchPageByID(c);

    if (temp == nullptr)
    {
        cout << "Page not found :(" << endl;
        return;
    }

    cout << "\n\n-----------------------------------------------------------" << endl;
    cout << "Command:\tViewPage"<< endl;
    cout << "-----------------------------------------------------------\n" << endl;

    temp->Display();
    temp->ViewTimeline();

}

void Controller::PageDisplay(const char* c)
{
    ViewPage(c);
}

void Controller::ViewPost(const char* c)
{
    Post* temp1 = SearchPostByID(c);
    if (temp1 == nullptr)
    {
        cout << "Post not found :(" << endl;
        return;
    }

    Object* temp2 = SearchObject(temp1->GetSharedBy());

    User* user = SearchUserByID("u3");
    Comments* cmtPtr = new Comments(nullptr, user, "wow very beautiful");
    temp1->AddComment(cmtPtr);

    cout << "\n\n-----------------------------------------------------------" << endl;
    cout << "Command:\tViewPost(" <<c<<")"<< endl;
    cout << "-----------------------------------------------------------\n" << endl;
    temp1->DisplayPost();

}

void Controller::LikeAPost(const char* c, const char* user)
{
    Post* temp1 = SearchPostByID(c);
    if (temp1 == nullptr)
    {
        cout << "Post not found :(" << endl;
        return;
    }

    Object* temp2 = SearchObject(user);

    temp1->SetLikedBy(temp2);

    cout << "\n\n-----------------------------------------------------------" << endl;
    cout << "Command:\tLikeAPost(" << c << ")" << endl;
    cout << "-----------------------------------------------------------\n" << endl;
  
    temp1->DisplayPost();

    cout << "\nLiked By : ";
    temp2->Display();
}

void Controller::ViewLikes(const char* c)
{
    Post* temp = SearchPostByID(c);
    if (temp == nullptr)
    {
        cout << "Post not found :(" << endl;
        return;
    }

    cout << "\n\n-----------------------------------------------------------" << endl;
    cout << "Command:\tPostLikedBy" <<endl;
    cout << "-----------------------------------------------------------\n" << endl;
    cout << "Post : " << c << endl;
    cout << "\nLiked By : " << endl<<endl;
    temp->DisplayLikedBy();


}

void Controller::PostDisplay(const char* c)
{
    ViewPost(c);
    LikeAPost(c,"u3");
    ViewLikes(c);
}

void Controller::LoadData()
{
    Date::currentDate.SetValues(17, 4, 2024);
    LoadAllUsers("users.txt"); 
    LoadAllPages("pages.txt"); 
    LoadAllPosts("posts.txt");
    LinkUsersAndPages("friends.txt");
    LoadAllComments("comments.txt");
    LoadActivities("activity.txt");

}

void Controller::DisplayFunctionalities()
{
    UserDisplay("u7");
    PageDisplay("p5");
    PostDisplay("post5");
}

Controller::~Controller()
{
    if (AllUsers)
    {
        for (int i = 0; i < totalUsers; i++)
            delete AllUsers[i];
        delete[] AllUsers;
    }

    if (AllPages)
    {
        for (int i = 0; i < totalPages; i++)
            delete AllPages[i];
        delete[] AllPages;
    }

    if (AllPosts)
    {
        delete[] AllPosts;
    }
}

//--------------------------Main------------------------

int main() 
{
    {
        Controller mainApp;
        mainApp.LoadData();
        mainApp.DisplayFunctionalities();

    }
    
    _CrtDumpMemoryLeaks();
    return 0;
}

