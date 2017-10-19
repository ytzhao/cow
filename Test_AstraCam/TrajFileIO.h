#ifndef C_TRAJ_FILE_IO_H
#define C_TRAJ_FILE_IO_H

#include <iostream>
#include <fstream>
#include <vector>

# include "../../OSPublic/EwaySysDefine.h"
# include "../../../../ThirdPartyLib/Eigen/Dense"
# include "../../LowLevelAI/Application/LAIGlobal.h"

# define TempNum 9
using namespace std;

class CTrajFileIO
{
    public:
        static eint TrajReadFromFile(estring strFileName, vector<Eigen::VectorXd>&vPosition, eint nCol);
        static eint TrajReadFromFile(estring strFileName, vector<edouble>& vTime, vector<Eigen::VectorXd>&vPosition, eint nCol);

        static eint TrajWriteToFileAppend(estring strFileName, vector<Eigen::VectorXd>&vPosition, eint nCol);
        static eint TrajWriteToFileAppend(estring strFileName, vector<edouble>& vTime, vector<Eigen::VectorXd>&vPosition, eint nCol);

        static eint TrajWriteToFileUpdate(estring strFileName, vector<Eigen::VectorXd>&vPosition, eint nCol);
        static eint TrajWriteToFileUpdate(estring strFileName, vector<edouble>& vTime, vector<Eigen::VectorXd>&vPosition, eint nCol);

        static eint TrajWriteToFile(estring strFileName, vector<edouble>& vTime, vector<Eigen::VectorXd>&vPosition, eint nCol);

        // unchanged
//        static eint MusicReadFromFile(estring strFileName, vector<edouble>& vTime, vector<eint>& vLeft, vector<eint>& vRight);

        // for weitao's test
        static eint AppendFile(estring strFileName, edouble dTime, Eigen::VectorXd MatPosition);

    private:
        static eint FindFilePath(estring &strFilePath, estring strFileName, estring strFolderName="/Traj/");
};


#endif // C_TRAJ_FILE_IO_H

