
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

using namespace std;
struct idLabel{
    int id;
    string label;
    int dbId;
};
vector<idLabel> education_level{
        {1,"Non scolarisé",4},{2,"Primaire",1},{3,"Secondaire",2},{4,"Universitaire",3}
};
vector<idLabel> income_type_id{
        {1,"Salaire"},{2,"allocations chômage"},{3,"bourse d'études"},{4,"retraite"},{5,"retraite-pension"},{6,"RSA"},{7,"sans ressources"},{8,"Conjoint(e) Salarie(e)"}
};
vector<idLabel> city_id{
        {1,"MULHOUSE"},{2,"MULHOUSE"},{3,"ILLZACH"},{4,"RIEDISHEIM"},{5,"LUTTERBACK"},
        {6,"SAUSHEIM"},{7,"BRUNSTATT-DIDENHEIM"},{8,"PFASTATT"},{9,"KINGERSHEIM"},{10,"FLAXLADEN"},
        {12,"BRUEBACH"},{13,"MORSCHWILLER-LE-BAS"},{14,"WITTELSHEIM"},{15,"HABSHEIM"},{6,"COLMAR"},{16,"RIXHEIM"},{17,"WITTENHEIM"}
};
vector<idLabel>legal_situation{{1,"Acte de naissance",1},{2,"Carte de s�jour",2},{3,"Carte d'identit�",3},{4,"Passeport",4},{5,"Récépissé",5},{6,"Autre",6
}};
vector<idLabel> payment_mode{
        {1,"Chèque"},{2,"Espèces"},{3,"En attente"},{4,"Dispense"}
};
int getIncomeTypeId(const vector<idLabel>& data,const string& val){
    for(const auto & x : data){
        if(
                x.label[0]==val[0] && x.label[1]==val[1]&& x.label[2]==val[2] &&
                 sizeof(x.label)==sizeof(val)
                        //&&x.label[sizeof(val)-1]==val[sizeof(val)-1] && x.label[1]==val[sizeof(val)-2]&& x.label[2]==val[sizeof(val)-2]
                ){
            cout<<endl<<x.label<<"===="<<val<<endl;
            return x.dbId;
        }else{
            //cout<<endl<<x.label<<"!="<<val<<endl;
        }
    }
    return -1;
}
/*
vector<idLabel> income_type_id{
        {1,""},{2,""},{3,""},{4,""},{5,""},
};
vector<idLabel> income_type_id{
        {1,""},{2,""},{3,""},{4,""},{5,""},
};*/
bool isValidDate(const std::string& inputDate) {
    std::tm timeStruct = {};
    std::istringstream dateStream(inputDate);
    dateStream >> std::get_time(&timeStruct, "%d/%m/%Y");
    return !dateStream.fail();
}



string convertDateFormat(const std::string& inputDate) {
    // Convert the date string to a struct tm object.
    if(inputDate.length()==0)
        return "";
    struct tm tm;
    strptime(inputDate.c_str(), "%d/%m/%Y", &tm);

    // Convert the struct tm object to a date string in the Gregorian calendar.
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", &tm);

    return buffer;
}

void generateQuery(const std::string& file){
    std::ifstream inputFile(file); // Replace "data.txt" with the actual file name

    if (!inputFile.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return;
    }

    std::string line;
    //std::cout<<"INSERT INTO `users` (`id`, `family_name`, `first_name`, `gender_id`, `dob`, `address`, `city_id`, `tel`, `email`) VALUES ";



    int ID=1;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string token;
        std::vector<std::string> columns;

        while (std::getline(iss, token, ';')) {
            columns.push_back(token);
        }

        if (columns.size() >= 5) {


            std::cout<<endl<<endl<<"INSERT INTO `users` (`id`, `family_name`, `first_name`, `gender_id`, `dob`, `address`, `city_id`, `tel`, `email`) VALUE ";

            std::cout<<std::endl<<"("<<columns[0]<<",";
            std::cout<<"'"<<columns[1]<<"',";
            std::cout<<"'"<<columns[2]<<"',";
            int gender;
            string str_gender=columns[3];
            gender=str_gender=="Monsieur"? 1:2;
            std::cout<<"'"<<   gender<< "',";



            if(columns[7].length()==0)
                std::cout<<"NULL,";//dob
            else
                std::cout<<"'"<<convertDateFormat(columns[4])<<"',";//dob

            //columns[5]) represents age_gap
            std::cout<<"'"<<columns[6]<<"',";//addresss

            if(columns[7].length()==0)
                std::cout<<"NULL,";//city_id
            else
                std::cout<<"'"<<columns[7]<<"',";//city_id


            //columns[8]  QPV

            std::cout<<"'"<<columns[9]<<"',";//tel

            if(columns[10].length()==0)
                std::cout<<"NULL";//email
            else
                std::cout<<"'"<<columns[10]<<"'";//email
            std::cout<<");"<<endl<<endl;




            //Adherent
            cout<<"INSERT INTO `adherents` (`id`, `created_at`, `updated_at`, `user_id`, `city_id`, `QPV`, `place_of_birth`, `citizenship`, `legal_situation_id`, `marital_status_id`, `income_type_id`, `registration_date`, `french_entry_date`, `education_level_id`, `exit_date`, `CIR`) VALUES "<<endl;
            cout<<"(NULL, NULL, NULL,'"<< columns[0]<<"',";


            //city_id
            if(columns[7].length()==0)
                std::cout<<"NULL,";//city_id
            else
                std::cout<<"'"<<columns[7]<<"',";//city_id

            std::cout<<"'"<<columns[8]<<"',";//QPV
            //getIncomeTypeId
            std::cout<<""<<1<<",";//std::cout<<""<<1<<",";//std::cout<<"'"<<columns[11]<<"',";//place_of_birth
            std::cout<<""<<1<<",";//std::cout<<"'"<<columns[12]<<"',";//citizenship
            std::cout<<"####"<<getIncomeTypeId(legal_situation,columns[13])<<"&&&,"<<endl;//std::cout<<"'"<<columns[13]<<"',";//legal_situation_id
            std::cout<<""<<1<<",";//std::cout<<"'"<<columns[14]<<"',";//marital_status_id

            if(columns[16].length()==0)
                std::cout<<"NULL,";//income_type_id
            else{
                std::cout<<""<<1<<endl<<"'Income:"<<columns[16]<<endl<<"',"<<",";//std::cout<<"'"<<columns[16]<<"',";
            }


            if(columns[17].length()==0)
                std::cout<<"NULL,";//registration_date
            else
                std::cout<<"'"<<convertDateFormat(columns[17])<<"',";
            if(columns[18].length()==0)
                std::cout<<"NULL,";//french_entry_date
            else
                std::cout<<"'"<<convertDateFormat(columns[18])<<"',";



            if(columns[24].length()==0)
                std::cout<<"NULL,";//education_level_id
            else{
                std::cout<<endl<<1<<":"<<columns[24]<<"');"<<endl;//std::cout<<"'"<<columns[24]<<"',";
            }


            if(columns[28].length()==0)
                std::cout<<"NULL,";//exit_date
            else
                std::cout<<"'"<<convertDateFormat(columns[28])<<"',";

            std::cout<<"'"<<columns[19]<<"');";//CIR

            cout<<endl<<endl;

        }
    }
    std::cout<<endl;

    inputFile.close();

}
int main() {
    //std::cout<<isValidDate("28/08/1989");
    generateQuery("/home/oreste/Documents/old ssd/Downloads/ADHERENT(2).txt");
    return 0;
}

