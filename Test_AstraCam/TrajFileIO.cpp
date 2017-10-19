# include "TrajFileIO.h"


eint CTrajFileIO::FindFilePath(estring &strFilePath, estring strFileName, estring strFolderName)
{
    // check whether the file exist
    echar szFilePath[MAXPATHSIZE] = {0};
    echar szFilePathNew[MAXPATHSIZE] = {0};
    EGetCurrentPath(szFilePath, MAXPATHSIZE);
    estrcpy(szFilePathNew, szFilePath);

    eint nStrFileLen = estrlen(szFilePath);
    eint nSlashCount = 0;
    for (eint i=nStrFileLen; i>=0; i--)
    {
        if('/'==szFilePathNew[i])
        {
            nSlashCount++;
            if(3==nSlashCount)
                {szFilePathNew[i]=0;}
        }
    }
    estrcat(szFilePathNew, strFolderName.c_str());
    estrcat(szFilePathNew, strFileName.c_str());

    strFilePath = szFilePathNew;

    return ERR_NONE;
}


//eint CTrajFileIO::MusicReadFromFile(estring strFileName, vector<edouble>& vTime, vector<eint>& vLeft, vector<eint>& vRight)
//{
//    ifstream inFile(strFileName.c_str());
//    estring strTmp;

//    if (!inFile)
//    {
//        cout << "No file exists." << endl;
//        return LIMB_CMD_CANNOT_OPEN_FILE;
//    }

//    vector<edouble> vTmp;
//    inFile >> strTmp;
//    while(!inFile.eof())
//    {
//        vTmp.push_back(atof(strTmp.c_str()));
//        inFile >> strTmp;
//    }

//    eint nSize = vTmp.size();
//    eint nRow = nSize / 3;
//    for(eint i = 0; i < nRow; i++)
//    {
//        vTime.push_back(vTmp.at(i*3));
//        vLeft.push_back(vTmp.at(i*3 + 1));
//        vRight.push_back(vTmp.at(i*3 + 2));
//    }

//    return ERR_NONE;
//}


eint CTrajFileIO::AppendFile(estring strFileName, edouble dTime, Eigen::VectorXd MatPosition)
{
    FILE* pFile;
    pFile = fopen(strFileName.c_str(), "a+");
    // write time
    fprintf(pFile, "%.4f \t", dTime);

    // write position
    for(eint i = 0; i != MatPosition.rows(); i++){
        fprintf(pFile, "%.4f \t", MatPosition(i));
    }
    fprintf(pFile, "\n");
    fclose(pFile);

    return ERR_NONE;
}


eint CTrajFileIO::TrajReadFromFile(estring strFileName, vector<edouble>& vTime, vector<Eigen::VectorXd>&vPosition, eint nCol)
{
//    estring strFilePath;
//    CTrajFileIO::FindFilePath(strFilePath, strFileName);
//    ifstream inFile(strFilePath.c_str());

    ifstream inFile(strFileName.c_str());
    estring strTmp;

    // traj file doesn't exist
    if (!inFile)
    {
        OSG_WriteLog(LogPriNormal, "Can NOT find trajectory file: %s", strFileName.c_str());
        return LIMB_CMD_CANNOT_OPEN_FILE;
    }

    // read data from file into temporary vector
    vector<edouble> vTmp;
    inFile >> strTmp;
    while(!inFile.eof())
    {
        vTmp.push_back(atof(strTmp.c_str()));
        inFile >> strTmp;
    }

    if (0!=(vTmp.size()%nCol))
    {
        OSG_WriteLog(LogPriNormal, "TrajReadFromFile: trajectory file doesn't have %d values per line");
        return -1;
    }

    // process data
    eint nSize = vTmp.size();
    eint nRow = nSize / nCol;
    Eigen::MatrixXd sTmp(nCol-1,1);
    for(eint i=0; i<nRow; i++)
    {
        vTime.push_back(vTmp.at(i*nCol));
        for (eint j=1; j<nCol; j++)
        {
            sTmp(j-1, 0) = vTmp.at(i*nCol + j);
        }
        vPosition.push_back(sTmp);
    }

    return ERR_NONE;
}


eint CTrajFileIO::TrajWriteToFile(estring strFileName, vector<edouble>& vTime, vector<Eigen::VectorXd>&vPosition, eint nCol)
{
    if (vTime.size()!=vPosition.size())
    {
        OSG_WriteLog(LogPriNormal, "Trajectory write to file, time size is not equal to position size.");
        return -1;
    }

//    estring strFilePath;
//    CTrajFileIO::FindFilePath(strFilePath, strFileName);

    FILE* pFile;
//    pFile = fopen(strFilePath.c_str(), "r");
    pFile = fopen(strFileName.c_str(), "r");

    // traj already exists
    if (pFile)
    {
        OSG_WriteLog(LogPriNormal, "Trajectory file already exists: %s", strFileName.c_str());
        return -1;
    }

    // read data from file into temporary vector
//    pFile = fopen(strFilePath.c_str(), "w");
    pFile = fopen(strFileName.c_str(), "w");

    Eigen::MatrixXd sTmp;
    for (euint i=0; i<vPosition.size(); i++)
    {
        sTmp = vPosition.at(i);
        fprintf(pFile, "%.4f", vTime.at(i));
        fprintf(pFile, "\t");

        for (eint j=0; j<(nCol-1); j++)
        {
            fprintf(pFile, "%.4f", sTmp(j, 0));
            fprintf(pFile, "\t");
        }
        fprintf(pFile, "\n");
    }
    fclose(pFile);
    OSG_WriteLog(LogPriNormal, "Trajectory write file done.");
    return ERR_NONE;
}


eint CTrajFileIO::TrajWriteToFileAppend(estring strFileName, vector<edouble>& vTime, vector<Eigen::VectorXd> &vPosition, eint nCol)
{
    if (vTime.size()!=vPosition.size())
    {
        OSG_WriteLog(LogPriNormal, "Trajectory write to file, time size is not equal to position size.");
        return -1;
    }

//    estring strFilePath;
//    CTrajFileIO::FindFilePath(strFilePath, strFileName);

    FILE* pFile;
//    pFile = fopen(strFilePath.c_str(), "a+");
    pFile = fopen(strFileName.c_str(), "a+");

    Eigen::MatrixXd sTmp;
    for (euint i=0; i<vPosition.size(); i++)
    {
        sTmp = vPosition.at(i);
        fprintf(pFile, "%.4f", vTime.at(i));
        fprintf(pFile, "\t");

        for (eint j=0; j<(nCol-1); j++)
        {
            fprintf(pFile, "%.4f", sTmp(j, 0));
            fprintf(pFile, "\t");
        }
        fprintf(pFile, "\n");
    }
    fclose(pFile);
    return ERR_NONE;
}


eint CTrajFileIO::TrajWriteToFileUpdate(estring strFileName, vector<edouble>& vTime, vector<Eigen::VectorXd>&vPosition, eint nCol)
{
    if (vTime.size()!=vPosition.size())
    {
        OSG_WriteLog(LogPriNormal, "Trajectory write to file, time size is not equal to position size.");
        return -1;
    }

//    estring strFilePath;
//    CTrajFileIO::FindFilePath(strFilePath, strFileName);

    FILE* pFile;
//    pFile = fopen(strFilePath.c_str(), "w");
    pFile = fopen(strFileName.c_str(), "w");

    // read data from file into temporary vector
    Eigen::MatrixXd sTmp;
    for (euint i=0; i<vPosition.size(); i++)
    {
        sTmp = vPosition.at(i);
        fprintf(pFile, "%.4f", vTime.at(i));
        fprintf(pFile, "\t");

        for (eint j=0; j<nCol-1; j++)
        {
            fprintf(pFile, "%.4f", sTmp(j, 0));
            fprintf(pFile, "\t");
        }
        fprintf(pFile, "\n");
    }
    fclose(pFile);
    OSG_WriteLog(LogPriNormal, "Trajectory write file update done.");
    return ERR_NONE;
}


eint CTrajFileIO::TrajWriteToFileUpdate(estring strFileName, vector<Eigen::VectorXd>&vPosition, eint nCol)
{
//    estring strFilePath;
//    CTrajFileIO::FindFilePath(strFilePath, strFileName);

    FILE* pFile;
//    pFile = fopen(strFilePath.c_str(), "w");
    pFile = fopen(strFileName.c_str(), "w");

    // read data from file into temporary vector
    Eigen::MatrixXd sTmp;
    for (euint i=0; i<vPosition.size(); i++)
    {
        sTmp = vPosition.at(i);
        for (eint j=0; j<nCol; j++)
        {
            fprintf(pFile, "%.4f", sTmp(j, 0));
            fprintf(pFile, "\t");
        }
        fprintf(pFile, "\n");
    }
    fclose(pFile);
    OSG_WriteLog(LogPriNormal, "Trajectory write file done.");
    return ERR_NONE;
}


// withou time
eint CTrajFileIO::TrajReadFromFile(estring strFileName, vector<Eigen::VectorXd>&vPosition, eint nCol)
{
//    estring strFilePath;
//    CTrajFileIO::FindFilePath(strFilePath, strFileName);
//    ifstream inFile(strFilePath.c_str());

    ifstream inFile(strFileName.c_str());
    estring strTmp;

    // traj file doesn't exist
    if (!inFile)
    {
        OSG_WriteLog(LogPriNormal, "Can NOT find trajectory file: %s", strFileName.c_str());
        return LIMB_CMD_CANNOT_OPEN_FILE;
    }

    // read data from file into temporary vector
    vector<edouble> vTmp;
    inFile >> strTmp;
    while(!inFile.eof())
    {
        vTmp.push_back(atof(strTmp.c_str()));
        inFile >> strTmp;
    }

    // process data
    eint nSize = vTmp.size();
    eint nRow = nSize / nCol;
    Eigen::MatrixXd sTmp(nCol,1);

    for(eint i=0; i<nRow; i++)
    {
        for (eint j=0; j<nCol; j++)
        {
            sTmp(j,0) = vTmp.at(i*nCol + j);
        }
        vPosition.push_back(sTmp);
    }
    return ERR_NONE;
}


eint CTrajFileIO::TrajWriteToFileAppend(estring strFileName, vector<Eigen::VectorXd>&vPosition, eint nCol)
{
//    estring strFilePath;
//    CTrajFileIO::FindFilePath(strFilePath, strFileName);

    FILE* pFile;
//    pFile = fopen(strFilePath.c_str(), "a+");
    pFile = fopen(strFileName.c_str(), "a+");

    Eigen::MatrixXd sTmp;
    for (euint i=0; i<vPosition.size(); i++)
    {
        sTmp = vPosition.at(i);
        for (eint j=0; j<nCol; j++)
        {
            fprintf(pFile, "%.4f", sTmp(j, 0));
            fprintf(pFile, "\t");
        }
        fprintf(pFile, "\n");
    }
    fclose(pFile);
    return ERR_NONE;
}


