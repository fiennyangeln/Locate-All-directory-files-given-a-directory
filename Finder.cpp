#include "dirent.h"
#include <iostream>
#include <queue>
#include <string>

using namespace std;

int main()
{
    queue <std::string> qDir;
    DIR *dir;
    struct dirent *ent;
    string strFolder="C:\\Users\\Angelina\\Downloads\\tryAPI";
    string strBase=strFolder,strFileName;
    qDir.push(strBase);
    while (qDir.empty()==false)
    {
        if ((dir = opendir (qDir.front().c_str())) != NULL) 
        {
            while ((ent = readdir (dir)) != NULL) 
            {
                string strLine=ent->d_name;
                std::transform(strLine.begin(), strLine.end(),strLine.begin(), ::tolower);
                //if it is a directory, put it inside the queue to be explored later
                if (ent->d_type == DT_DIR && strncmp(strLine.c_str(),".",strlen("."))!=0) 
                {   
                    strFileName="";
                    strFileName.append(qDir.front()).append("\\").append(strLine);
                    qDir.push(strFileName);
                    std::cout<<strFileName<<endl;
                }
                //if it is not a directory, just print the filename
                else
                {   
                    strFileName=qDir.front();
                    strFileName.append("\\");
                    strFileName.append(strLine);
                    std::cout<<strFileName<<endl;
                }
            }
        }
        qDir.pop();
    }
}