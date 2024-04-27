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

    static int StringLength(char* str)
    {
        int strLength = 0;

        for (int i = 0; str[i] != '\0'; i++)
            strLength++;

        return strLength;
    }

    static void StringCopy(char* str1, char* str2)
    {
        char* temp = str1;

        for (int i = 0; str2[i] != '\0'; i++)
        {
            *temp = str2[i];
            temp++;
        }
        *temp = '\0';
    }

    static char* GetStringFromBuffer(char* buffer)
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


};

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
    bool CompareDatesForMemories(Date&);
    bool CompareDatesForHome(Date&);
    int GetDay();
    int GetMonth();
    int GetYear();
};
Date Date::currentDate(0,0,0);

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
    Activity* activity;

public:
    Post();
    char* GetId();
    void SetSharedBy(Object*&);
    void SetLikedBy(Object*&);
    void ReadDataFromFile(ifstream&);
    char* GetSharedBy();
    void DisplayPost();
    void DisplayLikedBy();
    void AddComment(Comments*&);
    void AddActivity(Activity*&);
    void SelectPostsForHome();
    Post* SelectPostsForMemories();
    ~Post();
};

class Memory :public Post
{
    Post* OriginalPost;

public:
    Memory();
    void SetOriginalPost(Post*&);
    void Display();
    ~Memory();
};

class Object
{
    Post** Timeline;
    int totalPosts;
    char* ID;

public:
    Object();
    void SetID(char*);
    char* GetID();
    virtual void Display();
    void AddPostToTimeline(Post*);
    void ViewTimeline();
    void PostsForHome();
    Post* PostsForMemories();
    ~Object();
};

class Page : public Object
{
    char* Title;

public:
    Page();
    char* GetTitle();
    void ReadDataFromFile(ifstream&);
    void Display();
    ~Page();
};

class User : public Object
{

    char* Fname;
    char* Lname;
    User** FriendList;   
    Page** LikedPages;   
    int totalFriends;
    int totalPages;
    Memory* memory;

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
    void ShareMemory();
    ~User();
};

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
    void LikeAPost(const char*);
    void ViewLikes(const char*);
    void LoadData();
    void DisplayFunctionalities();
    ~Controller();
};

class Comments
{
    char* ID;
    Object* CommentBy;
    char* text;

public:
    Comments();
    void SetValues(char*, Object*&, char*);
    void Display();
    ~Comments();
};

class Activity {
    int type;
    char* value;

public:
    Activity();
    void SetActivity(int, char*);
    void DisplayActivity();
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

bool Date::CompareDatesForMemories(Date& date)
{
    if (day == date.GetDay() && month == date.GetMonth() && year>date.GetYear())
    {
        cout << "On this day " << year - date.GetYear() << " year ago:\n" << endl;
        return true;
    }
        
    else
        return false;
}

bool Date::CompareDatesForHome(Date& date)
{
    if (date.GetDay() <= day && date.GetDay() >= (day- 2))
        return true;

    else
        return false;
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
    cout << day << "/" << month << "/" << year;
}

void Date::ReadFromFile(ifstream& fin)
{
    fin >> day;
    fin >> month;
    fin >> year;
}

//------------------------------Post Class------------------------------

Post::Post()
{
    Id = nullptr;
    text = nullptr;
    SharedBy = nullptr;
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
    fin >> std::ws;
    fin.getline(temp2, 500);
    text = Helpers::GetStringFromBuffer(temp2);

}

char* Post::GetSharedBy()
{
    return SharedBy->GetID();
}

void Post::DisplayPost()
{
    cout << "---";
    SharedBy->Display();
    cout<< "(";
    SharedDate.Display();
    cout << ")" << endl<<endl;
    SharedBy->Display();
    if(activity)
        activity->DisplayActivity();
    cout << endl;
    cout << "\t'" << text << "'" << endl;
    cout << endl;
    for (int i = 0; i < totalComments; i++)
        comments[i]->Display();

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

void Post::AddActivity(Activity*& act)
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

Post* Post::SelectPostsForMemories()
{
    bool check = false;

    check = Date::currentDate.CompareDatesForMemories(SharedDate);

    if (check)
    {
        return this;
    }

    else
        return nullptr;

}

Post::~Post()
{
    if (Id)
        delete[] Id;

    if (text)
        delete[] text;

    SharedBy = nullptr;

    for (int i = 0; i < Likes; i++)
        LikedBy[i] = nullptr;

    delete[] LikedBy;

    if (activity)
        activity = nullptr;

}

//---------------------------Memory Class---------------------

Memory::Memory():Post()
{
    OriginalPost = nullptr;
}

void Memory::Display()
{
    if (OriginalPost == nullptr)
    {
        cout << "No memory to share :(" << endl;
    }

    else
    {
        OriginalPost->DisplayPost();
    }
}

void Memory::SetOriginalPost(Post*& pst)
{
    if(OriginalPost==nullptr)
        OriginalPost = pst;
    
}

Memory::~Memory()
{
    if (OriginalPost)
        OriginalPost = nullptr;
}

//--------------------------Activity Class----------------------

Activity::Activity()
{
    type = 0;
    value = nullptr;
}

void Activity::SetActivity(int i, char* c)
{
    type = i;
    value = Helpers::GetStringFromBuffer(c);
}

void Activity::DisplayActivity()
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

Post* Object::PostsForMemories()
{
    Post* temp = nullptr;

    for (int i = 0; i < totalPosts; i++)
    {
        temp= Timeline[i]->SelectPostsForMemories();

        if (temp)
            return temp;
    }

    return nullptr;
       
}

Object::~Object()
{
    if (ID)
        delete[] ID;

    for (int i = 0; i < totalPosts; i++)
        Timeline[i] = nullptr;

    delete[] Timeline;

}

//--------------------------Page Class---------------------------------

Page::Page() :Object()
{
    Title = nullptr;
}

char* Page::GetTitle()
{
    return Title;
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
    cout << Object::GetID() << "-" << Title;
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
    memory = nullptr;
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
    cout << Object::GetID() << "-\t" << Fname << " " << Lname;
}

void User::ViewFriendList()
{
    for (int i = 0; i < totalFriends; i++)
    {
        FriendList[i]->Display();
        cout << endl;
    }
}

void User::ViewLikedPages()
{
    for (int i = 0; i < totalPages; i++)
    {
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

void User::ShareMemory()
{
    Post* temp = PostsForMemories();

    if (temp)
    {
        memory = new Memory;
        memory->SetOriginalPost(temp);
        memory->Display();
    }
}

User::~User()
{

    if (Fname)
        delete[] Fname;

    if (Lname)
        delete[] Lname;

    for (int i = 0; i < totalFriends; i++)
        FriendList[i] = nullptr;
    delete[] FriendList;

    for (int i = 0; i < totalPages; i++)
        LikedPages[i] = nullptr;
    delete[] LikedPages;

    if (memory)
        memory = nullptr;

}

//---------------------Comments-----------------------

Comments::Comments()
{
    ID = nullptr;
    CommentBy = nullptr;
    text = nullptr;
}

void Comments::SetValues(char* c1, Object*& obj, char* c2)
{
    if(ID==nullptr)
        ID = Helpers::GetStringFromBuffer(c1);

    if (CommentBy == nullptr)
        CommentBy = obj;

    if (text == nullptr)
        text = Helpers::GetStringFromBuffer(c2);
       
}

void Comments::Display()
{
    CommentBy->Display();
    cout <<":'"<< text <<" '"<< endl;
    
}

Comments::~Comments()
{
    if (ID)
        delete[] ID;

    if (CommentBy)
        CommentBy = nullptr;

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
}

Post* Controller::SearchPostByID(const char* c)
{
    for (int i = 0; i < totalPosts; i++)
    {
        if (Helpers::CompareString(c, AllPosts[i]->GetId()))
            return AllPosts[i];
    }
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
        while (!Helpers::CompareString(temp, "-1"))
        {
            obj2[index] = SearchObject(temp);
            AllPosts[i]->SetLikedBy(obj2[index]);
            index++;

            fin >> temp;
        }
        

        obj1->AddPostToTimeline(AllPosts[i]);

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

    char cID[5], pID[10], uID[5];
    char text[500];

    for (int i = 0; i < total; i++)
    {
        Comments* temp1 = new Comments;
        
        fin >> cID;
        fin >> pID;

        Post* temp2 = SearchPostByID(pID);

        fin >> uID;

        Object* temp3 = SearchObject(uID);

        fin.getline(text, 500);

        temp1->SetValues(cID, temp3, text);

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

        Activity* temp2 = new Activity;
        temp2->SetActivity(type, value);

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
    cout << "Command:\tTimeLine" << endl;
    temp->ViewTimeline();

    cout << "\n\n-----------------------------------------------------------" << endl;
    cout << "Command:\tHomePage (";
    temp->Display();
    cout << ")" << endl;
    cout << "-----------------------------------------------------------\n" << endl;
    temp->ViewHome();

    cout << "\n\n-----------------------------------------------------------" << endl;
    cout << "Command:\tShare a memory" << endl;
    cout << "-----------------------------------------------------------\n" << endl;
    temp->ShareMemory();
}

void Controller::ViewPage(const char* c)
{
    Page* temp = SearchPageByID(c);

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
    Post* temp1 = SearchPostByID("post11");
    Object* temp2 = SearchObject(temp1->GetSharedBy());

    cout << "\n\n-----------------------------------------------------------" << endl;
    cout << "Command:\tViewPost(" <<c<<")"<< endl;
    cout << "-----------------------------------------------------------\n" << endl;
    temp1->DisplayPost();
    
}

void Controller::LikeAPost(const char* c)
{
    Post* temp1 = SearchPostByID(c);

    Object* temp2 = SearchObject("u3");

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

    cout << "\n\n-----------------------------------------------------------" << endl;
    cout << "Command:\tPostLikedBy" <<endl;
    cout << "-----------------------------------------------------------\n" << endl;
    cout << "Post : " << c << endl;
    cout << "\nLiked By : " << endl;
    temp->DisplayLikedBy();
}

void Controller::PostDisplay(const char* c)
{
    ViewPost(c);
    LikeAPost(c);
    ViewLikes(c);
}

void Controller::LoadData()
{
    Date::currentDate.SetValues(17, 4, 2024);
    LoadAllUsers("users.txt"); //Keep it easily configurable
    LoadAllPages("pages.txt"); //Keep it easily configurable
    LoadAllPosts("posts.txt");
    LinkUsersAndPages("friends.txt");
    LoadAllComments("comments.txt");
    LoadActivities("activity.txt");

}

void Controller::DisplayFunctionalities()
{
    UserDisplay("u7");
    PageDisplay("p5");
    PostDisplay("post6");
}

Controller::~Controller()
{
    if (AllUsers)
    {
        for (int i = 0; i < totalUsers; i++)
            AllUsers[i] = nullptr;
        delete[] AllUsers;
    }

    if (AllPages)
    {
        for (int i = 0; i < totalPages; i++)
            AllPages[i] = nullptr;
        delete[] AllPages;
    }

    if (AllPosts)
    {
        for (int i = 0; i < totalPosts; i++)
            AllPosts[i] = nullptr;
        delete[] AllPosts;
    }
}

//--------------------------Main------------------------

int main() 
{
    Controller mainApp;
    mainApp.LoadData();
    mainApp.DisplayFunctionalities();

    _CrtDumpMemoryLeaks();
    return 0;
}

