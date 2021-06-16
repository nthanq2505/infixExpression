#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <math.h>
#include "stack.h"
#include "function.h"
using namespace std;


int main()
{
    
    ifstream filein;
    filein.open("input.txt");
    ofstream fileout;
    fileout.open("output.txt");
    string s;
    string mode = "-t";
    while (!filein.eof())
    {
        string newS;
        if (mode == "-c"){
            while (getline(filein, s)) {
                stringstream ss(s);
                int laHaiSoLienTuc = 0;
                StackFloat so;
                Stack toanTu;
                while (getline(ss, newS, ' ')) {
                    if (newS[0] == '(') {
                        while(newS[0] == '('){
                            string dauMoNgoac = newS.substr(0, 1);
                            kiemTraHaiSoLienTuc(laHaiSoLienTuc, dauMoNgoac);
                            thucHien(dauMoNgoac, so, toanTu);
                            newS.erase(0, 1);
                        }
                        if (kiemTraHaiSoLienTuc(laHaiSoLienTuc, newS)) {
                            fileout << "E" << endl;
                            break;
                        }
                        thucHien(newS, so, toanTu);
                    }
                    else if (newS[newS.size() - 1] == ')') {
                        int viTri = newS.find(")");
                        string motSo = newS.substr(0, viTri);
                        newS.erase(0, viTri);
                        if (kiemTraHaiSoLienTuc(laHaiSoLienTuc, motSo)) {
                            fileout << "E" << endl;
                            break;
                        }
                        thucHien(motSo, so, toanTu);
                        while (newS[0] == ')')
                        {
                            string dauDongNgoac = newS.substr(0, 1);
                            kiemTraHaiSoLienTuc(laHaiSoLienTuc, dauDongNgoac);
                            thucHien(dauDongNgoac, so, toanTu);
                            newS.erase(newS.size() - 1, 1);
                        }                    
                    }
                    else {
                        if (kiemTraHaiSoLienTuc(laHaiSoLienTuc, newS)) {
                            fileout << "E" << endl;
                            break;
                        }
                        thucHien(newS, so, toanTu);
                    }

                }
                if (laHaiSoLienTuc != 2) {
                    while (!toanTu.empty()) {
                        float soThuNhat = so.top();
                        so.pop();
                        float soThuHai = so.top();
                        so.pop();
                        so.push(tinhToan(soThuHai, soThuNhat, toanTu.top()));
                        toanTu.pop();
                    }
                    fileout << fixed <<setprecision(2) <<so.top() << endl;
                }
            }
        }
        else if (mode == "-t"){
            while (getline(filein, s)) {
                stringstream ss(s);
                int laHaiSoLienTuc = 0;
                Stack so;
                Stack toanTu;
                while (getline(ss, newS, ' ')) {
                    if (newS[0] == '(') {
                        while(newS[0] == '('){
                            string dauMoNgoac = newS.substr(0, 1);
                            kiemTraHaiSoLienTuc(laHaiSoLienTuc, dauMoNgoac);
                            thucHien2(dauMoNgoac, so, toanTu);
                            newS.erase(0, 1);
                        }
                        if (kiemTraHaiSoLienTuc(laHaiSoLienTuc, newS)) {
                            fileout << "E" << endl;
                            break;
                        }
                        thucHien2(newS, so, toanTu);
                    }
                    else if (newS[newS.size() - 1] == ')') {
                        int viTri = newS.find(")");
                        string motSo = newS.substr(0, viTri);
                        newS.erase(0, viTri);
                        if (kiemTraHaiSoLienTuc(laHaiSoLienTuc, motSo)) {
                            fileout << "E" << endl;
                            break;
                        }
                        thucHien2(motSo, so, toanTu);
                        while (newS[0] == ')')
                        {
                            string dauDongNgoac = newS.substr(0, 1);
                            kiemTraHaiSoLienTuc(laHaiSoLienTuc, dauDongNgoac);
                            thucHien2(dauDongNgoac, so, toanTu);
                            newS.erase(0, 1);
                        }                    
                    }
                    else {
                        if (kiemTraHaiSoLienTuc(laHaiSoLienTuc, newS)) {
                            fileout << "E" << endl;
                            break;
                        }
                        thucHien2(newS, so, toanTu);
                    }

                }
                if (laHaiSoLienTuc != 2) {
                    while (!toanTu.empty()) {
                        string soThuNhat = so.top();
                        so.pop();
                        string soThuHai = so.top();
                        so.pop();
                        
                        string imp = soThuHai + (soThuHai!="" ? " " : "") +  soThuNhat + (soThuHai!="" ? " " : "") + toanTu.top() + (toanTu.top()!="" ? " " : "");
                        so.push(imp);
                        toanTu.pop();
                    }
                    fileout << so.top() << endl;
                }
            }
        }
        filein.close();
        fileout.close();
    }


    system("pause");
    return 0;
}