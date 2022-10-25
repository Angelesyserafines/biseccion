#include <iostream>
#include <string>
#include <cmath>
#include <iterator>
#include <map>

using namespace std;

class BisectionSolveFunction{
public:
    float get_solved_function(string type_function, string ecuation, int interval, int _pow) {
        float result;
        bool flag = false;
        if (ecuation == ""){
            ecuation = "1";
        }
        if (ecuation.find("-") != string::npos){

            flag = true;
            ecuation.replace(ecuation.find("-"), 1, "");
        }
        if (type_function == "") {
            result = pow(stoi(ecuation) * interval, _pow);
        } else if (type_function == "cos") {
            result = pow(cos(stoi(ecuation) * interval), _pow);
        } else if (type_function == "sen") {
            result = pow(sin(stoi(ecuation) * interval), _pow);
        } else if (type_function == "tan") {
            result = pow(tan(stoi(ecuation) * interval), _pow);
        }
        if (flag){
            return result * -1;
        }
        return result;
    }

    string reduce_ecuation(string ecuation, string type_ecuation = "") {
        string copy_ecuacion;
        copy_ecuacion = ecuation;
        bool flag = false;
        if (ecuation.find("-") != string::npos){
            flag = true;
        }
        if (type_ecuation != "") {
            int _finder;
            if (flag) {
                _finder = copy_ecuacion.find("(");
            } else {
                _finder = copy_ecuacion.find("(") + 1;
            }
            copy_ecuacion.replace(copy_ecuacion.find(type_ecuation),_finder, "");
            copy_ecuacion.replace(copy_ecuacion.find(")"), 1, "");
        }
        if (copy_ecuacion.find("x") != string::npos){
            copy_ecuacion.replace(copy_ecuacion.find("x"), 1, "");
        }
        return copy_ecuacion;
    }

    map<string, float> merge_results(map<string, map<string, float>> _map){
        map<string, float> merged_result;
        for (map <string, map<string, float>>::iterator it = _map.begin(); it != _map.end(); ++it){
            map<string, float> &internal_map = it->second;
            for (map<string, float>::iterator it2 = internal_map.begin(); it2 != internal_map.end(); ++it2){
                merged_result[it2->first] += it2->second;
            }
        }
        return merged_result;
    }

};


class Biseccion{
private:
    int grade, interval1, interval2, *interval;
    string *ecuation;
public:
    BisectionSolveFunction solve = *new BisectionSolveFunction();
    void setGrado() {
        cout << "Introduce el grado del polinomio:" << endl;
        cin >> grade;
    }

    void setIntervalo() {
        int longitud = 0;
        cout << "Introduce el principio del intervalo: " << endl;
        cin >> interval1;
        cout << "Introduce el final del intervalo: " << endl;
        cin >> interval2;
        int inter[2] = {interval1, interval2};
        interval = inter;
    }

    void generar_ecuacion(){
        ecuation = new string[grade + 1];
    }

    void fillEcuacion(){
        for (int i = 0; i < grade + 1; i++) {
            cout << "Introduce el elemento " << i + 1 << " de la ecuacion" << endl;
            cin >> ecuation[i];
        }
    }

    void sustituir(){
        string cases[3] = {"cos", "sen", "tan"};
        map<string, map<string, float>> results;
        map<string, float> merged_result;
        float result;
        for (int i = 0; i < grade + 1; i++) {
            try{
                result = stof(ecuation[i]);
                for (int i = 0; i < sizeof(interval)/sizeof(interval[0]); i++){
                    results[to_string(grade)][to_string(interval[i])] = result;
                }
            } catch (const std::invalid_argument) {
                float result;
                for (int j = 0; j < 3; j++){
                    string type_ecuation;
                    for (int k = 0; k < sizeof(interval)/sizeof(interval[0]); k++) {
                        if (ecuation[i].find(cases[j]) != string::npos) {
                            type_ecuation = cases[j];
                        } else if (!(ecuation[i].find(cases[j]) != string::npos) and ecuation[i].find("x") != string::npos) {
                            type_ecuation = "";
                        }
                        string new_ecuation = solve.reduce_ecuation(ecuation[i], type_ecuation);
                        try {
                            result = solve.get_solved_function(type_ecuation,new_ecuation,interval[k],i);
                            results[to_string(grade)][to_string(interval[k])] = result;
                        } catch (std::invalid_argument) {
                            //
                        }
                    }
                }
            }
            merged_result = solve.merge_results(results);
        }
        for (map<string, float>::iterator it2 = merged_result.begin(); it2 != merged_result.end(); ++it2){
            cout << it2->first << ":" << it2->second<< endl;
        }
    }
};



int main() {
    int grado;
    string *ecuacion;
    Biseccion bi = Biseccion();
    bi.setGrado();
    bi.generar_ecuacion();
    bi.fillEcuacion();
    bi.setIntervalo();
    bi.sustituir();
};
