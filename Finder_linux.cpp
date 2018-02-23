#include <dirent.h>
#include <iostream>
#include <queue>
#include <string.h>
#include <bits/stl_algo.h>

using namespace std;

int main()
{
    queue <string> qDir;
    DIR *dir;
    struct dirent *ent;
    string strFolder;
    bool isValidDir = false;
    int length;

    // check for valid directory
    do
    {
        cout<<"Enter directory name: ";
        cin>>strFolder;
        length = strFolder.size();
        if(strFolder[length-1]=='/')
		{
            strFolder = strFolder.substr(0,length-1);
        }
        dir = opendir (strFolder.c_str());
        // cout<<"dir: "<<dir<<endl;              // debugging step prints hexadecimal address if directory found otherwise 0
        isValidDir = (dir!=NULL) ? true:false;
        if(!isValidDir)
		{
            cout<<"Not a valid directory!\n";
        }
    }
    while(!isValidDir);
	
    // string strFolder="/home/ankur/Desktop";    // debugging step
    string strBase = strFolder,strFileName;
    qDir.push(strBase);
    while (qDir.empty()==false)
    {
        if ((dir = opendir (qDir.front().c_str())) != NULL) 
        {
            while ((ent = readdir (dir)) != NULL) 
            {
                string strLine=ent->d_name;
                transform(strLine.begin(), strLine.end(),strLine.begin(), ::tolower);
                //if it is a directory, put it inside the queue to be explored later
                if (ent->d_type == DT_DIR && strncmp(strLine.c_str(),".",strlen("."))!=0) 
                {   
                    strFileName="";
                    strFileName.append(qDir.front()).append("/").append(strLine);
                    qDir.push(strFileName);
                    cout<<strFileName<<endl;
                }
                //if it is not a directory, just print the filename
                else
                {   
                    strFileName=qDir.front();
                    strFileName.append("/");
                    strFileName.append(strLine);
                    cout<<strFileName<<endl;
                }
            }
        }
        qDir.pop();
    }
}
