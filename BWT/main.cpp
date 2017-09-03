#include <QCoreApplication>
#include <iostream>
#include <stdlib.h>
#include <QFile>
#include <QDebug>
#include <QByteArray>
#include <windows.h>
#include <math.h>

char *global_in = NULL;
char *global_l = NULL;
char *m1 = NULL, *m2 = NULL, *m3 = NULL, *m4 = NULL;
int *pit1 = NULL;
int *pit2 = NULL;

int currentColumn = 0;
int *pB = NULL, *pE = NULL;
char *globalBuff = NULL;
char *globalBuffl = NULL;
bool fEntry = 0, fEntryWas = 0;
int summPos = 0;

void mergeSortMerge(int begin, int end){
    summPos = 0;
    for(int i=0; i<currentColumn+1; i++)
        summPos += pB[i];

    int j;
    int beginL, middle, beginR;
    beginL = begin; //начало левой части
    middle = (int)((begin+end)/2); //вычисление среднего элемента
    beginR = middle + 1; //начало правой части
    for(j=begin; j<=end; j++) //выполнять от начала до конца
        if (/**/(beginL<=middle)&&(/**/(beginR>end) || ((unsigned char)globalBuff[beginL]<(unsigned char)globalBuff[beginR])/**/)/**/)
        {
            globalBuffl[j] = globalBuff[beginL];
            m4[j+summPos] = m2[beginL+summPos];
            pit2[j+summPos] = pit1[beginL+summPos];
            beginL++;
        }
        else
        {
            globalBuffl[j] = globalBuff[beginR];
            m4[j+summPos] = m2[beginR+summPos];
            pit2[j+summPos] = pit1[beginR+summPos];
            beginR++;
        }
    //возвращение результата в список
    for(j=begin; j<=end; j++) globalBuff[j] = globalBuffl[j];
    for(j=begin+summPos; j<=end+summPos; j++) m2[j] = m4[j];
    for(j=begin+summPos; j<=end+summPos; j++) pit1[j] = pit2[j];
}

void mergeSortMerge2(int begin, int end, int sl1){
    summPos = 0;
    for(int i=0; i<currentColumn+1; i++){
        summPos += pB[i];
    }

    int j;
    int beginL, middle, beginR;
    beginL = begin; //начало левой части
    middle = begin + sl1 - 1;//(int)((begin+end)/2); //вычисление среднего элемента
    beginR = middle + 1; //начало правой части
    for(j=begin; j<=end; j++) //выполнять от начала до конца
        if (/**/(beginL<=middle)&&(/**/(beginR>end) || (globalBuff[beginL]<globalBuff[beginR])/**/)/**/){
            globalBuffl[j] = globalBuff[beginL];
            m4[j+summPos] = m2[beginL+summPos];
            pit2[j+summPos] = pit1[beginL+summPos];
            beginL++;
        }
        else{
            globalBuffl[j] = globalBuff[beginR];
            m4[j+summPos] = m2[beginR+summPos];
            pit2[j+summPos] = pit1[beginR+summPos];
            beginR++;
        }
    //возвращение результата в список
    for(j=begin; j<=end; j++) globalBuff[j] = globalBuffl[j];
    for(j=begin+summPos; j<=end+summPos; j++) m2[j] = m4[j];
    for(j=begin+summPos; j<=end+summPos; j++) pit1[j] = pit2[j];
}

void mergeSort(int begin, int end){
    int size = (end+1) - begin;
    if(size<=0 || size==1) return;

    unsigned char *mDegree = new unsigned char[30];
    unsigned char p_mDegree = 0;
    memset(mDegree, (unsigned char)255, 30);

    int u1 = 1, u2 = 1, buff1 = 1, buff2 = 2, buff3 = 0;
    bool f1 = false;

    for(int i=1; i<31; i++)
        if((int)pow(2, i)>size){
            //u1 = size - ((int)pow(2, i) - size);

            mDegree[p_mDegree] = i-1;
            p_mDegree++;

            for(int i=pow(2, mDegree[p_mDegree-1]); i<size; i = i + pow(2, mDegree[p_mDegree-1])){
                    for(int j=0; j<31; j++){
                        if((int)pow(2, j)>(size-i)){
                            mDegree[p_mDegree] = j-1;
                            p_mDegree++;
                            break;
                        }
                        else if((int)pow(2, j)==(size-i)){
                            mDegree[p_mDegree] = j;
                            p_mDegree++;
                            break;
                        }
                    }
            }

            f1 = true;
            break;

        }else if((int)pow(2, i)==size){
            //u1 = size;
            break;
        }

    if(f1){
        if(mDegree[p_mDegree-1]==0){
            end--;
            size--;
        }
        p_mDegree = 0;

        for(int g_i=begin; g_i<end+1; g_i=g_i+pow(2, mDegree[p_mDegree-1])){
            for(int i=g_i; i<(g_i+pow(2, mDegree[p_mDegree])); i=i+2)
                mergeSortMerge(i, i+buff1);

            buff1 = buff1<<2;
            buff2 = buff2<<1;

            for(int i=2; i<pow(2, mDegree[p_mDegree]); i=i<<1){
                for(int j=g_i; j<(g_i+pow(2, mDegree[p_mDegree])); j=j+buff2)
                    mergeSortMerge(j, j+(buff1-1));
                buff1 = buff1<<1;
                buff2 = buff2<<1;
            }

            buff1 = 1;
            buff2 = 2;
            p_mDegree++;
        }

        buff2 = p_mDegree;
        p_mDegree = 1;

        for(int i=pow(2, mDegree[p_mDegree-1]); i<size; i=(i+pow(2, mDegree[p_mDegree-1]))){
            mergeSortMerge2(begin, begin+((i+pow(2, mDegree[p_mDegree]))-1), i);
            p_mDegree++;
        }

        if(mDegree[buff2]==0){
            mergeSortMerge2(begin, begin+size, size);
        }
    }
    else{
        for(int i=begin; i<end+1; i=i+2)
            mergeSortMerge(i, i+buff1);

        buff1 = buff1<<2;
        buff2 = buff2<<1;

        for(int i=2; i<size; i=i<<1){
            for(int j=0; j<size; j=j+buff2)
                mergeSortMerge(j, j+(buff1-1));
            buff1 = buff1<<1;
            buff2 = buff2<<1;
        }
    }

    /*for(int i=0; i<30; i++){
        qDebug()<<"["<<i<<"] = "<<mDegree[i];
    }*/

    delete[] mDegree;
}


void mergeSortMerge12(int begin, int end){
    int j;
    int beginL, middle, beginR;
    beginL = begin; //начало левой части
    middle = (int)((begin+end)/2); //вычисление среднего элемента
    beginR = middle + 1; //начало правой части
    for(j=begin; j<=end; j++) //выполнять от начала до конца
        if (/**/(beginL<=middle)&&(/**/(beginR>end) || ((unsigned char)m1[beginL]<(unsigned char)m1[beginR])/**/)/**/){
            m3[j] = m1[beginL];
            m4[j] = m2[beginL];
            pit2[j] = pit1[beginL];
            beginL++;
        }
        else{
            m3[j] = m1[beginR];
            m4[j] = m2[beginR];
            pit2[j] = pit1[beginR];
            beginR++;
        }
    //возвращение результата в список
    for(j=begin; j<=end; j++) m1[j] = m3[j];
    for(j=begin; j<=end; j++) m2[j] = m4[j];
    for(j=begin; j<=end; j++) pit1[j] = pit2[j];
}

void mergeSortMerge22(int begin, int end, int sl1){
    int j;
    int beginL, middle, beginR;
    beginL = begin; //начало левой части
    middle = begin + sl1 - 1;//(int)((begin+end)/2); //вычисление среднего элемента
    beginR = middle + 1; //начало правой части
    for(j=begin; j<=end; j++) //выполнять от начала до конца
        if (/**/(beginL<=middle)&&(/**/(beginR>end) || ((unsigned char)m1[beginL]<(unsigned char)m1[beginR])/**/)/**/){
            m3[j] = m1[beginL];
            m4[j] = m2[beginL];
            pit2[j] = pit1[beginL];
            beginL++;
        }
        else{
            m3[j] = m1[beginR];
            m4[j] = m2[beginR];
            pit2[j] = pit1[beginR];
            beginR++;
        }
    //возвращение результата в список
    for(j=begin; j<=end; j++) m1[j] = m3[j];
    for(j=begin; j<=end; j++) m2[j] = m4[j];
    for(j=begin; j<=end; j++) pit1[j] = pit2[j];
}

void mergeSort2(int begin, int end){
    int size = (end+1) - begin;
    if(size<=0 || size==1) return;

    unsigned char *mDegree = new unsigned char[30];
    unsigned char p_mDegree = 0;
    memset(mDegree, (unsigned char)255, 30);

    int u1 = 1, u2 = 1, buff1 = 1, buff2 = 2, buff3 = 0;
    bool f1 = false;

    for(int i=1; i<31; i++)
        if((int)pow(2, i)>size){
            //u1 = size - ((int)pow(2, i) - size);

            mDegree[p_mDegree] = i-1;
            p_mDegree++;

            for(int i=pow(2, mDegree[p_mDegree-1]); i<size; i = i + pow(2, mDegree[p_mDegree-1])){
                    for(int j=0; j<31; j++){
                        if((int)pow(2, j)>(size-i)){
                            mDegree[p_mDegree] = j-1;
                            p_mDegree++;
                            break;
                        }
                        else if((int)pow(2, j)==(size-i)){
                            mDegree[p_mDegree] = j;
                            p_mDegree++;
                            break;
                        }
                    }
            }

            f1 = true;
            break;

        }else if((int)pow(2, i)==size){
            //u1 = size;
            break;
        }

    if(f1){
        if(mDegree[p_mDegree-1]==0){
            end--;
            size--;
        }
        p_mDegree = 0;

        for(int g_i=begin; g_i<end+1; g_i=g_i+pow(2, mDegree[p_mDegree-1])){
            for(int i=g_i; i<(g_i+pow(2, mDegree[p_mDegree])); i=i+2)
                mergeSortMerge12(i, i+buff1);

            buff1 = buff1<<2;
            buff2 = buff2<<1;

            for(int i=2; i<pow(2, mDegree[p_mDegree]); i=i<<1){
                for(int j=g_i; j<(g_i+pow(2, mDegree[p_mDegree])); j=j+buff2)
                    mergeSortMerge12(j, j+(buff1-1));
                buff1 = buff1<<1;
                buff2 = buff2<<1;
            }

            buff1 = 1;
            buff2 = 2;
            p_mDegree++;
        }

        buff2 = p_mDegree;
        p_mDegree = 1;

        for(int i=pow(2, mDegree[p_mDegree-1]); i<size; i=(i+pow(2, mDegree[p_mDegree-1]))){
            mergeSortMerge22(begin, begin+((i+pow(2, mDegree[p_mDegree]))-1), i);
            p_mDegree++;
            //qDebug()<<i;
            //Sleep(1000);
        }

        if(mDegree[buff2]==0){
            mergeSortMerge22(begin, begin+size, size);
        }
    }
    else{
        for(int i=begin; i<end+1; i=i+2)
            mergeSortMerge12(i, i+buff1);

        buff1 = buff1<<2;
        buff2 = buff2<<1;

        for(int i=2; i<size; i=i<<1){
            for(int j=0; j<size; j=j+buff2)
                mergeSortMerge12(j, j+(buff1-1));
            buff1 = buff1<<1;
            buff2 = buff2<<1;
        }
    }

    delete[] mDegree;
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile file1("test_file2.avi");
    QFile file2("test_file3.avi");
    QFile file3("test_file4.avi");
    QFile file4("test_file5.avi");

    if (!file1.open(QIODevice::ReadOnly)) { //QIODevice::ReadOnly | QIODevice::Text)
    qDebug() << "Ошибка открытия для чтения";
    }

    if (!file2.open(QIODevice::WriteOnly)) { //QIODevice::ReadOnly | QIODevice::Text)
    qDebug() << "Ошибка открытия для чтения";
    }

    if (!file3.open(QIODevice::WriteOnly)) { //QIODevice::ReadOnly | QIODevice::Text)
    qDebug() << "Ошибка открытия для чтения";
    }

    if (!file4.open(QIODevice::WriteOnly)) { //QIODevice::ReadOnly | QIODevice::Text)
    qDebug() << "Ошибка открытия для чтения";
    }

    QByteArray a1; int sR = 4; //8388608
    a1 = file1.read(sR);//a1 = file1.read((int)(file1.size())); 10 485 760

    qDebug()<<file1.size();
    qDebug()<<a1.size();

    global_in = a1.data();
    char *pt = a1.data();

    pit1 = new int[a1.size()];
    for(int i=0; i<a1.size(); i++)
        pit1[i] = i;

    qDebug()<<"checkPoint1";

    pit2 = new int[a1.size()];
    for(int i=0; i<a1.size(); i++)
        pit2[i] = i;

    qDebug()<<"checkPoint2";

    global_l = new char[a1.size()];
    for(int i=0; i<a1.size(); i++) global_l[i] = global_in[i];

    qDebug()<<"checkPoint3";

    m1 = new char[a1.size()];
    m2 = new char[a1.size()];
    m3 = new char[a1.size()];
    m4 = new char[a1.size()];

    for(int i=0; i<a1.size(); i++){
        m1[i] = (char)a1[i];
    }

    m2[0] = (char)a1[a1.size()-1];
    for(int i=0; i<a1.size()-1; i++){
        m2[i+1] = (char)a1[i];
    }

    for(int i=0; i<a1.size(); i++){
        m3[i] = (char)a1[i];
    }

    m4[0] = (char)a1[a1.size()-1];
    for(int i=0; i<a1.size()-1; i++){
        m4[i+1] = (char)a1[i];
    }

    mergeSort2(0, a1.size()-1);

    for(int i=0; i<a1.size(); i++)
        qDebug()<<pit1[i];

    pB = new int[a1.size()];
    memset(pB, 0, a1.size());

    pE = new int[a1.size()];
    memset(pE, 0, a1.size());

    int *mS = new int[a1.size()];
    memset(mS, 0, a1.size());

    while(pB[0]<a1.size())
    {
        if(currentColumn==0)
        {
            if(fEntryWas==true && fEntry==false)
                pB[currentColumn] = pE[currentColumn] + 1;

            pE[currentColumn] = pB[currentColumn];
            for(int i=pE[currentColumn]; i<a1.size()-1; i++ )
            {
                if(m1[i]==m1[i+1])
                    pE[currentColumn]++;
                else
                    break;
            }

            if(pE[currentColumn]!=pB[currentColumn])
            {
                globalBuff = new char[(pE[currentColumn]-pB[currentColumn])+1];
                for(int i=0; i<((pE[currentColumn]-pB[currentColumn])+1); i++)
                {
                    if((pit1[pB[currentColumn]+i]+(currentColumn+1))<a1.size())
                        globalBuff[i] = global_in[(pit1[pB[currentColumn]+i]+(currentColumn+1))];
                    else
                        globalBuff[i] = global_in[(pit1[pB[currentColumn]+i]+(currentColumn+1))-a1.size()];
                }

                for(int i=0; i<(pE[currentColumn]-pB[currentColumn])+1; i++)
                    qDebug()<<"["<<i<<"] = "<<(unsigned char)globalBuff[i];
                //Sleep(100000);

                globalBuffl = new char[(pE[currentColumn]-pB[currentColumn])+1];
                mergeSort(0, (pE[currentColumn]-pB[currentColumn]));

                delete[] globalBuffl;
                mS[currentColumn+1] = (pE[currentColumn]-pB[currentColumn])+1;
                currentColumn++;
                fEntry = true;
                fEntryWas = true;
                continue;

                /*for(int i=0; i<(pE[currentColumn]-pB[currentColumn])+1; i++)
                    qDebug()<<"["<<i<<"] = "<<(unsigned char)globalBuff[i];
                for(int i=0; i<a1.size(); i++)
                    qDebug()<<pit1[i];
                Sleep(100000);*/
            }
            else
            {
                pB[currentColumn]++;
                continue;
            }
        }
        else /*currentColumn!=0 Begin*/
        {
            if(fEntryWas)
            {
                fEntryWas = false;

                if(fEntry)
                {
                    pE[currentColumn] = pB[currentColumn];
                    for(int i=pE[currentColumn]; i<mS[currentColumn]-1; i++ )
                    {
                        if(globalBuff[i]==globalBuff[i+1])
                            pE[currentColumn]++;
                        else
                            break;
                    }

                    if(pE[currentColumn]!=pB[currentColumn])
                    {
                        summPos = 0;
                        for(int i=0; i<currentColumn+1; i++) summPos += pB[i];

                        delete[] globalBuff;
                        globalBuff = new char[(pE[currentColumn]-pB[currentColumn])+1];
                        for(int i=0; i<((pE[currentColumn]-pB[currentColumn])+1); i++)
                        {
                            if((pit1[pB[currentColumn]+i+summPos]+(currentColumn+1))<mS[currentColumn])
                                globalBuff[i] = global_in[(pit1[pB[currentColumn]+i+summPos]+(currentColumn+1))];
                            else
                                globalBuff[i] = global_in[(pit1[pB[currentColumn]+i+summPos]+(currentColumn+1))-mS[currentColumn]];
                        }

                        for(int i=0; i<(pE[currentColumn]-pB[currentColumn])+1; i++)
                            qDebug()<<"["<<i<<"] = "<<(unsigned char)globalBuff[i];
                        //Sleep(100000);

                        globalBuffl = new char[(pE[currentColumn]-pB[currentColumn])+1];
                        mergeSort(0, (pE[currentColumn]-pB[currentColumn]));

                        delete[] globalBuffl;
                        mS[currentColumn+1] = (pE[currentColumn]-pB[currentColumn])+1;
                        currentColumn++;
                        fEntry = true;
                        fEntryWas = true;
                        continue;

                        /*for(int i=0; i<(pE[currentColumn]-pB[currentColumn])+1; i++)
                            qDebug()<<"["<<i<<"] = "<<(unsigned char)globalBuff[i];
                        for(int i=0; i<a1.size(); i++)
                            qDebug()<<pit1[i];
                        Sleep(100000);*/
                    }
                    else
                    {
                        pB[currentColumn]++;
                        continue;
                    }

                }
                else{}
            }
            else /* !fEntryWas Begin*/
            {
                pE[currentColumn] = pB[currentColumn];
                for(int i=pE[currentColumn]; i<mS[currentColumn]-1; i++ )
                {
                    if(globalBuff[i]==globalBuff[i+1])
                        pE[currentColumn]++;
                    else
                        break;
                }

                if(pE[currentColumn]!=pB[currentColumn])
                {
                    globalBuff = new char[(pE[currentColumn]-pB[currentColumn])+1];
                    for(int i=0; i<((pE[currentColumn]-pB[currentColumn])+1); i++)
                    {
                        if((pit1[pB[currentColumn]+i]+(currentColumn+1))<a1.size())
                            globalBuff[i] = global_in[(pit1[pB[currentColumn]+i]+(currentColumn+1))];
                        else
                            globalBuff[i] = global_in[(pit1[pB[currentColumn]+i]+(currentColumn+1))-a1.size()];
                    }

                    for(int i=0; i<(pE[currentColumn]-pB[currentColumn])+1; i++)
                        qDebug()<<"["<<i<<"] = "<<(unsigned char)globalBuff[i];
                    //Sleep(100000);

                    globalBuffl = new char[(pE[currentColumn]-pB[currentColumn])+1];
                    mergeSort(0, (pE[currentColumn]-pB[currentColumn]));

                    delete[] globalBuffl;
                    mS[currentColumn+1] = (pE[currentColumn]-pB[currentColumn])+1;
                    currentColumn++;
                    fEntry = true;
                    fEntryWas = true;
                    continue;

                    /*for(int i=0; i<(pE[currentColumn]-pB[currentColumn])+1; i++)
                        qDebug()<<"["<<i<<"] = "<<(unsigned char)globalBuff[i];
                    for(int i=0; i<a1.size(); i++)
                        qDebug()<<pit1[i];
                    Sleep(100000);*/
                }
                else
                {
                    pB[currentColumn]++;
                    if(!(pB[currentColumn]<sM[currentColumn]))
                    {
                        delete[] globalBuffl;
                        mS[currentColumn] = 0;
                        currentColumn--;
                        fEntry = false;
                        fEntryWas = true;
                    }
                    continue;
                }
            } /*!fEntryWas  End*/
        } /*currentColumn!=0 End*/

    } /*while(pB[0]<a1.size()) End*/

    file2.write(a1);
    file3.write(m1, a1.size());
    file4.write(m2, a1.size());

    file1.close();
    file2.close();
    file3.close();
    file4.close();

    qDebug()<<"finish";

    return a.exec();
}

/*const int sM = 16000000;
global_in = new int[sM];
for(int i=0; i<sM; i++){
    global_in[i] = sM - i;
}

global_l = new int[sM];

for(int i=0; i<sM; i++) global_l[i] = global_in[i];

//for(int i=0; i<sM; i++)
 //   qDebug()<<"["<<i<<"] = "<<global_in[i];

qDebug()<<"";
//MergeSort begin
mergeSort(0, 15999999);
//MergeSort end

qDebug()<<"";

for(int i=0; i<sM; i++){
    qDebug()<<"["<<i<<"] = "<<global_in[i];
    //Sleep(500);
}*/
