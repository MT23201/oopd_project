#include<iostream>
#include<string>
#include<fstream>
using namespace std;
class data
{   public:
    string specRange_data[5][101];
    string subscriber_data[4][101];
    string specRequest_data[4][101];
};
class auction : public data
{
    public:
    string auc_data[6][100];
    string mvno[4][21];

};
bool compareFloatDescending(const string &num1, const string &num2) {
    float f1 = stof(num1);
    float f2 = stof(num2);
    return f1 > f2;
}
bool compareDDMMYYYY(const string &date1, const string &date2) {
    int day1, month1, year1, day2, month2, year2;
    
    sscanf(date1.c_str(), "%d-%d-%d", &day1, &month1, &year1);
    sscanf(date2.c_str(), "%d-%d-%d", &day2, &month2, &year2);

    if (year1 != year2) {
        return year1 < year2;
    }
    if (month1 != month2) {
        return month1 < month2;
    }
    return day1 < day2;
}

bool compareMMYYYY(const string &date1, const string &date2) {
    int month1, year1, month2, year2;
    
    sscanf(date1.c_str(), "%d-%d", &month1, &year1);
    sscanf(date2.c_str(), "%d-%d", &month2, &year2);

    if (year1 != year2) {
        return year1 < year2;
    }
    return month1 < month2;
}
int main()
{
    auction a1;
    ifstream ip("spectrumRange.csv");

    if(!ip.is_open())
    {
        cout<<"Invalid file !\n";
    }

    int i = 0;
    while(ip.good())
    {
        getline(ip,a1.specRange_data[0][i],',');             
        getline(ip,a1.specRange_data[1][i],',');             
        getline(ip,a1.specRange_data[2][i],',');            
        getline(ip,a1.specRange_data[3][i],',');          
        getline(ip,a1.specRange_data[4][i],'\n');         
        i = i+1;
    }

    int n = 101;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (compareDDMMYYYY(a1.specRange_data[0][j], a1.specRange_data[0][j + 1])) {
                for (int k = 0; k < 5; k++) {
                    swap(a1.specRange_data[k][j], a1.specRange_data[k][j + 1]);
                }
            }
        }
    }
    
    ifstream op("subscribers.csv");

    if(!op.is_open())
    {
        cout<<"Invalid file !\n";
    }
    i = 0;
    while(op.good())
    {
        getline(op,a1.subscriber_data[0][i],',');            
        getline(op,a1.subscriber_data[1][i],',');            
        getline(op,a1.subscriber_data[2][i],',');            
        getline(op,a1.subscriber_data[3][i],'\n');           
        i = i+1;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (compareMMYYYY(a1.subscriber_data[0][j], a1.subscriber_data[0][j + 1])) {
                for (int k = 0; k < 4; k++) {
                    swap(a1.subscriber_data[k][j], a1.subscriber_data[k][j + 1]);
                }
            }
        }
    }
    ifstream sp("spectrumRequest.csv");
    if(!sp.is_open())
    {
        cout<<"Invalid file !\n";
    }

    i = 0;
    while(sp.good())
    {
        getline(sp,a1.specRequest_data[0][i],',');             
        getline(sp,a1.specRequest_data[1][i],',');            
        getline(sp,a1.specRequest_data[2][i],',');            
        getline(sp,a1.specRequest_data[3][i],'\n');           
        i = i+1;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (compareMMYYYY(a1.specRequest_data[0][j], a1.specRequest_data[0][j + 1])) {
                for (int k = 0; k < 4; k++) {
                    swap(a1.specRequest_data[k][j], a1.specRequest_data[k][j + 1]);
                }
            }
        }
    }

    ifstream mp("MVNOSpectrum.csv");
    if(!mp.is_open())
    {
        cout<<"Invalid file !\n";
    }

    i = 0;
    while(mp.good())
    {
        getline(mp,a1.mvno[0][i],',');             
        getline(mp,a1.mvno[1][i],',');             
        getline(mp,a1.mvno[2][i],',');            
        getline(mp,a1.mvno[3][i],'\n');           
        i = i+1;
    }

    for (int i = 0; i < 21 - 1; i++) {
        for (int j = 0; j < 21 - i - 1; j++) {
            if (compareMMYYYY(a1.mvno[0][j], a1.mvno[0][j + 1])) {
                for (int k = 0; k < 4; k++) {
                    swap(a1.mvno[k][j], a1.mvno[k][j + 1]);
                }
            }
        }
    }

if (!a1.mvno[1][0].empty() && a1.mvno[1][0] != " ") 
{
    std::cout << "--------------MVNOSpectrum Data------------------\n";
}

    for (int j = 0; j < 21; j++) {
    if (a1.mvno[1][j].compare(" ") == 1) {
        cout << "Date          :" << a1.mvno[0][j] << "\n";
        cout << "MVNO Company  :" << a1.mvno[1][j] << "\n";
        cout << "Location      :" << a1.mvno[2][j] << "\n";
        cout << "Request       :" << a1.mvno[3][j] << " MHz \n\n";
    }
}
    string circle;
    string req_dates[101];
    string req_company[101];
    string req_spec[101];
    string curr_spec[101];
    string curr_subcount[101];
     
    cout<<"Enter the circle:  ";                                 
    cin>>circle;
    cout<<"Circle selected is: "<<circle<<"\n";

    if(circle.compare("Delhi")==0 || circle.compare("Lucknow")==0 || circle.compare("Jaipur")==0 || circle.compare("Chandigarh")==0 || circle.compare("Patna")==0 || circle.compare("Kolkata")==0)
    {
        
        int p = 0;                 
    for(int i = 0;i<101;i++)
    {
        if(circle.compare(a1.specRequest_data[2][i])==0)
        {
            req_dates[p] = a1.specRequest_data[0][i];
            req_company[p] = a1.specRequest_data[1][i];
            req_spec[p] = a1.specRequest_data[3][i];
            p = p+1;
            
        }
    }
    for(int i=0;i<101;i++)
    {
        if(req_dates[i].compare(" ")==1 && req_dates[i+1].compare(" ")==1 && req_dates[i].substr(3,2).compare(req_dates[i+1].substr(3,2))==0)
        {
            
            a1.auc_data[0][i] = req_dates[i];
            a1.auc_data[1][i] = req_company[i];
            a1.auc_data[2][i] = req_spec[i];

        }
        else
        {
            a1.auc_data[0][i] = req_dates[i];
            a1.auc_data[1][i] = req_company[i];
            a1.auc_data[2][i] = req_spec[i];
            break;
        }
    }

     

    int temp;
    for(int i=0;i<101;i++)
    {
        temp = 0;
        if(a1.auc_data[2][i].compare(" ")==1)
        {
            for(int j = 0;j<101;j++)
            {
                if(a1.auc_data[1][i].compare(a1.specRange_data[1][j])==0 && circle.compare(a1.specRange_data[3][j])==0)
                {
                    temp = temp+1;
                }
            }
            
        }
        else
        {
            break;
        }

        a1.auc_data[3][i] = to_string(temp);
    }

    for(int i=0;i<101;i++)
    {
        if(a1.auc_data[3][i].compare(" ")==1)
        {
            for(int j = 0;j<101;j++)
            {
                if(a1.auc_data[1][i].compare(a1.subscriber_data[1][j])==0 && circle.compare(a1.subscriber_data[2][j])==0)
                {
                    a1.auc_data[4][i] = a1.subscriber_data[3][j];
                }
                if(a1.auc_data[4][i].compare(" ")==1)
                {
                    break;
                }
            }
        }
        else
        {
            break;
        }
    }

    float density;
    for(int i = 0;i<101;i++)
    {
        if(a1.auc_data[4][i].compare(" ")==1)
        {
            density = (stof(a1.auc_data[3][i])/stof(a1.auc_data[4][i]))*10000.0;
            a1.auc_data[4][i] = to_string(density);
        }
        else
        {
            break;
        }
    }

    for(int i=0;i<101;i++)
    {
        if(a1.auc_data[4][i].compare(" ")==1)
        {
            for(int j=0;j<101;j++)
            {
                if(a1.auc_data[1][i].compare(a1.specRange_data[1][j])==0 && a1.auc_data[2][i].compare(a1.specRange_data[2][j].substr(0,4))<=0 && circle.compare(a1.specRange_data[3][j])==0)
                {
                    a1.auc_data[5][i] = a1.specRange_data[4][j];
                }
                if(a1.auc_data[5][i].compare(" ")==1)
                {
                    break;
                }
            }
        }
        else
        {
            break;
        }
    }

    int ptr = 0;
    for(int i = 0;i<100;i++)
    {
        if(a1.auc_data[5][i].compare(" ")==1)
        {
            ptr = ptr+1;
        }
        else
        {
            break;
        }
    }

    for (int i = 0; i < ptr - 1; i++) {
        for (int j = 0; j < ptr - i - 1; j++) {
            if (compareFloatDescending(a1.auc_data[4][j], a1.auc_data[4][j + 1])) {
                for (int k = 0; k < 6; k++) {
                    swap(a1.auc_data[k][j], a1.auc_data[k][j + 1]);
                }
            }
        }
    }

    cout<<"-----------------Following are details for new spectrum allocation-----------------"<<"\n";
    cout<<"Date of request (MM-YY)      :           "<<a1.auc_data[0][0]<<"\n";
    cout<<"The band is alloted to       :           "<<a1.auc_data[1][0]<<"\n";
    cout<<"Alloted band frequency       :           "<<a1.auc_data[2][0]<<" MHz"<<"\n";
    cout<<"No. of bands in captive      :           "<<a1.auc_data[3][0]<<"\n";
    cout<<"Current usage density        :           "<<a1.auc_data[4][0]<<"\n";
    cout<<"Revenue generated            :           "<<a1.auc_data[5][0]<<" Cr (in INR)"<<"\n\n";

    ofstream outFile("Bidding_Report.txt", ios_base::app);

    if (outFile.is_open()) {

    outFile <<"--------------Fresh bidding for " <<circle<<"--------------"<< endl;
    outFile<<"Date of request (MM-YY)     :           "<<a1.auc_data[0][0]<<"\n";
    outFile<<"The band is alloted to      :           "<<a1.auc_data[1][0]<<"\n";
    outFile<<"Alloted band frequency      :           "<<a1.auc_data[2][0]<<" MHz"<<"\n";
    outFile<<"No. of bands in captive     :           "<<a1.auc_data[3][0]<<"\n";
    outFile<<"Current usage density       :           "<<a1.auc_data[4][0]<<"\n";
    outFile<<"Revenue generated           :           "<<a1.auc_data[5][0]<<" Cr (in INR)"<<"\n\n";

    outFile.close();
    

    } else {
        cerr << "Unable to open the file." << endl;
    }
    }
    else{
        cout<<"Please enter a valid circle!, valid circles are Delhi, Patna, Jaipur, Chandigarh, Kolkata and Lucknow."<<"\n\n";
    }
    

    return 0;
}