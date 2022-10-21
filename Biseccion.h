#include <iostream>
#include <string>
#include <cmath>
#include <iterator>
#include <map>

using namespace std;

class BiseccionSolveFunctions{

public:
    float get_trigo_result(string type_function, string ecuation, int intervalo, int _pow) {
        float result;
        if (ecuation == ""){
            ecuation = "1";
        }
        if (type_function == "") {
            result = pow(stoi(ecuation) * intervalo, _pow);
        } else if (type_function == "cos") {
            result = pow(cos(stoi(ecuation) * intervalo), _pow);
        } else if (type_function == "sen") {
            result = pow(sin(stoi(ecuation) * intervalo), _pow);
        } else if (type_function == "tan") {
            result = pow(tan(stoi(ecuation) * intervalo), _pow);
        }
        return result;
    }

    string reduce_ecuation(string ecuation, string type_ecuation = "") {
        string copy_ecuacion;
        copy_ecuacion = ecuation;
        if (type_ecuation != "") {
            copy_ecuacion.replace(copy_ecuacion.find(type_ecuation),copy_ecuacion.find("(") + 1, "");
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
        return merged_result
    }

};


class Biseccion{
private:
    int grado;
    string *ecuacion;
    int *intervalo, intervalo1, intervalo2;
public:
    BiseccionSolveFunctions solve = *new BiseccionSolveFunctions();
    void setGrado() {
        cout << "Introduce el grado del polinomio:" << endl;
        cin >> grado;
    }

    void setIntervalo() {
        int longitud = 0;
        cout << "Introduce el principio del intervalo: " << endl;
        cin >> intervalo1;
        cout << "Introduce el final del intervalo: " << endl;
        cin >> intervalo2;
        for (int i = intervalo1; i <= intervalo2; i++){
            longitud++;
        }
        intervalo = new int[longitud];
        for (int i = intervalo1; i <= intervalo2; i++){
            intervalo[i] = i;
        }
    }

    void generar_ecuacion(){
        ecuacion = new string[grado + 1];
    }

    void fillEcuacion(){
        for (int i = 0; i < grado + 1; i++) {
            cout << "Introduce el elemento " << i + 1 << " de la ecuacion" << endl;
            cin >> ecuacion[i];
        }
    }

    void sustituir(){
        string cases[3] = {"cos", "sen", "tan"};
        map<string, map<string, float>> results;
        map<string, float> merged_result;
        float result;
        for (int i = 0; i <= grado; i++) {
            try{
                result = stof(ecuacion[i]);
                for (int k = intervalo1; k <= intervalo2; k++){
                    results[to_string(grado)][to_string(intervalo[k])] = result;
                }
            } catch (const std::invalid_argument) {
                float result;
                for (int j = 0; j < 5; j++){
                    string type_ecuation;
                    for (int k = intervalo1; k <= intervalo2; k++) {
                        if (ecuacion[i].find(cases[j]) != string::npos) {
                            type_ecuation = cases[j];

                        } else if (!(ecuacion[i].find(cases[j]) != string::npos) and ecuacion[i].find("x") != string::npos) {
                            type_ecuation = "";
                        }
                        string new_ecuation = solve.reduce_ecuation(ecuacion[i], type_ecuation);
                        try {
                            result = solve.get_trigo_result(type_ecuation,new_ecuation,intervalo[k],i);
                            results[to_string(grado)][to_string(intervalo[k])] = result;
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
