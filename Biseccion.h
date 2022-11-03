#include <iostream>
#include <string>
#include <cmath>
#include <iterator>
#include <map>

using namespace std;

class BisectionSolveFunction{
public:
    float get_solved_function(string type_function, string ecuation, float interval, int _pow) {
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
            result = pow(stof(ecuation) * interval, _pow);
        } else if (type_function == "cos") {
            result = pow(cos(stof(ecuation) * interval), _pow);
        } else if (type_function == "sen") {
            result = pow(sin(stof(ecuation) * interval), _pow);
        } else if (type_function == "tan") {
            result = pow(tan(stof(ecuation) * interval), _pow);
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
    float calculate_iteration(float a, float b){
        return (a+b)/2;
    }
};


class Ecuation{
private:
    int grade;
    float *interval, interval1, interval2;
    string *ecuation;
public:
    BisectionSolveFunction solve = *new BisectionSolveFunction();
    float getIntervalo1(){
        return interval1;
    }

    float getIntervalo2(){
        return interval2;
    }

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
        float inter[2] = {interval1, interval2};
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

    bool isValidFunction(map<string, float> merged_result){
        float first_result = 0.0, second_result;
        for (map<string, float>::iterator it2 = merged_result.begin(); it2 != merged_result.end(); ++it2){
            //cout << it2->first << ":" << it2->second<< endl;
            if (first_result == 0.0){
                first_result = it2->second;
            } else {
                second_result = it2->second;
            }
        }
        return (first_result > 0 and second_result < 0) or (first_result < 0 and second_result > 0);
    }

    map<string, float> sustituir(float *_interval){
        string cases[3] = {"cos", "sen", "tan"};
        map<string, map<string, float>> results;
        map<string, float> merged_result;
        float result;
        float first_result = 0.0, second_result = 0.0;
        if (_interval[0] == 9999){
            _interval = interval;
        }
        for (int i = 0; i < grade + 1; i++) {
            try{
                result = stof(ecuation[i]);
                for (int i = 0; i < sizeof(&_interval)/sizeof(_interval[0]); i++){
                    results[to_string(grade)][to_string(_interval[i])] += result;
                }
            } catch (const std::invalid_argument) {
                float result;
                for (int j = 0; j < 3; j++){
                    string type_ecuation;
                    for (int k = 0; k < sizeof(&_interval)/sizeof(_interval[0]); k++) {
                        if (ecuation[i].find(cases[j]) != string::npos) {
                            type_ecuation = cases[j];
                        } else if (!(ecuation[i].find(cases[j]) != string::npos) and ecuation[i].find("x") != string::npos) {
                            type_ecuation = "";
                        }
                        string new_ecuation = solve.reduce_ecuation(ecuation[i], type_ecuation);
                        try {
                            result = solve.get_solved_function(type_ecuation,new_ecuation,_interval[k],i);
                            results[to_string(grade)][to_string(_interval[k])] += result;
                        } catch (std::invalid_argument) {
                            //
                        }
                    }
                }
            }
            merged_result = solve.merge_results(results);
        }
        return merged_result;
    }
    float getIteration(){
        float iteration;
        iteration = solve.calculate_iteration(interval1, interval2);
        return iteration;
    }
};


class Bisection {
public:
    Ecuation ecu = *new Ecuation();

    void main() {
        map<string, float> result, result2;
        ecu.setGrado();
        ecu.generar_ecuacion();
        ecu.fillEcuacion();
        ecu.setIntervalo();
        float _inter[2] = {9999, 9999};

        result = ecu.sustituir(_inter);
        if (ecu.isValidFunction(result)) {
            float first_result = 0.0, second_result = 0.0;
            for (map<string, float>::iterator it2 = result.begin(); it2 != result.end(); ++it2){
                //cout << it2->first << ":" << it2->second<< endl;
                if (first_result == 0.0 and it2->first == to_string(ecu.getIntervalo1())){
                    first_result = it2->second;
                }
            }
            //cout << "esto debio ser " << first_result << " , " << second_result << endl;
            float error = 1;
            float inter[2] = {ecu.getIntervalo1(), ecu.getIntervalo2()};
            float iteration = ecu.solve.calculate_iteration(inter[0], inter[1]);
            float to_iterate[1] = {iteration};
            result = ecu.sustituir(to_iterate);
            for (map<string, float>::iterator it2 = result.begin(); it2 != result.end(); ++it2){
                if (second_result == 0 and it2->first == to_string(to_iterate[0])) {
                    second_result = (it2->second)/2;
                }
            }
            float efe_de_equis = first_result * second_result;
            //cout << "el primero es " << first_result << " el segundo es " << second_result << endl;
            while (error > pow(10, -5)){
                float last_iteration = iteration;
                if (efe_de_equis > 0){
                    inter[0] = iteration;
                } else {
                    inter[1] = iteration;
                }
                result = ecu.sustituir(inter);
                first_result = 0.0;
                second_result = 0.0;
                for (map<string, float>::iterator it2 = result.begin(); it2 != result.end(); ++it2){
                    //cout << it2->first << ":" << it2->second<< endl;
                    if (first_result == 0.0 and it2->first == to_string(inter[0])){
                        first_result = it2->second;
                    } else {
                        second_result = it2->second;
                    }
                }

                iteration = ecu.solve.calculate_iteration(inter[0], inter[1]);
                //cout << "segunda iter " << iteration << endl;
                float to_iterate[1] = {iteration};
                result = ecu.sustituir(to_iterate);
                for (map<string, float>::iterator it2 = result.begin(); it2 != result.end(); ++it2){
                    if (it2->first == to_string(to_iterate[0])) {
                        second_result = it2->second;
                    }
                }
                //cout << "el segundo el primero es " << first_result << " el segundo es " << second_result << endl;
                error = (iteration - last_iteration)/iteration;
                efe_de_equis = first_result * second_result;
                if (error < 0) {
                    error = error * -1;
                }
            }
            cout << "el resultado es " << iteration << endl;
        } else {
            cout << "la funcion no es valida" << endl;
        }
    }

};



int main() {
    Bisection bi = Bisection();
    bi.main();
};
