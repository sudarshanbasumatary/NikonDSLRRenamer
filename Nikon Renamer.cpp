#include <bits/stdc++.h>	

using namespace std;

struct fileData {
	string fdate, ftime, fname, fext;
};

bool get_file_names(vector <fileData> &fList) {
	ifstream fileList("list.txt", ios::in);
	
	string fdetails;
	if(fileList.is_open()) {
		int k = 0;
		while(getline(fileList, fdetails)) {
			k++;
			if(k >= 6) {
				string exts, fname, fdate, ftime;
				int flen = fdetails.length();
				if(flen > 39) {
					exts = fdetails.substr(flen - 3, 3);
					
					if((exts == "NEF" || exts == "JPG" || exts == "jpg" || exts == "MOV") && fdetails.substr(39, 4) == "DSC_") {
						fileData f;
						f.fdate = fdetails.substr(0, 10);
						f.ftime = fdetails.substr(12, 8);
						f.fname = fdetails.substr(39, flen - 39);
						f.fext = exts;
						fList.push_back(f);
					}
				}
			}
		}
		fileList.close();
		return false;
	}
	else {
		cout << "Could not open file!" << endl;
		return true;
	}
}

string format_date(string date) {
	return date.substr(6, 4) + date.substr(0, 2) + date.substr(3, 2);
}

string format_time(string time) {
	string ft = time.substr(0, 2) + time.substr(3, 2);
	if(time[6] == 'P') {
		if(ft[1] < '8') {
			ft[0] += 1;
			ft[1] += 2;
		}
		else if(ft[1] == '8') {
			ft[0] = '2';
			ft[1] = '0';
		}
		else if(ft[1] == '9') {
			ft[0] = '2';
			ft[1] = '1';
		}
	}
	else if(ft[0] == 1 && ft[1] == 2)
		ft[0] = ft[1] = '0';
		
	return ft;
}

void rename_files(const vector <fileData> &fList) {
	string new_fname;
	for(int i = 0; i < fList.size(); i++) {
		new_fname = "NIK" + format_date(fList[i].fdate) + "_" + format_time(fList[i].ftime) + "_" + fList[i].fname.substr(fList[i].fname.length() - 8, 4) + "." + fList[i].fext;
		if(!rename(fList[i].fname.c_str(), new_fname.c_str()))
			cout << "Rename Success: " << new_fname << endl;
		else cout << "Rename Failed: " << fList[i].fname << " " << new_fname << endl;
	}
}

int main() {
	vector <fileData> fList;
	if(!system("dir > list.txt")) {
		if(get_file_names(fList) == false)
			rename_files(fList);
		else cout << "File list read error!" << endl;
		
		if(system("del list.txt"))
			cout << "Couldn't delete list.txt" << endl;
	}
	else cout << "Command processor not found! Please create file list into \"list.txt\" by executing \"dir > list.txt\" in command prompt." << endl;
	return 0;
}