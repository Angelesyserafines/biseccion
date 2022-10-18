#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Biseccion{
private:
    int grado;
    string *ecuacion;
    int *intervalo, intervalo1, intervalo2;
public:
    static Biseccion get_trigo_result;

    void setGrado() {
        cout << "Introduce el grado del polinomio:" << endl;
        cin >> grado;
    }

    void setIntervalo() {
        int longitud = 0;
        cout << "Introduce el primer intervalo:" << endl;
        cin >> intervalo1;
        cout << "Introduce el segundo intervalo: " <<endl;
        cin >> intervalo2;
        for (int i = intervalo1; i <= intervalo2; i++){
            longitud++;
        }
        intervalo = new int[longitud];
        for (int i = intervalo1; i <= intervalo2; i++){
            intervalo[i] = i;
        }
    }

    int *getIntervalo(){
        return intervalo;
    }

    int getGrado(){
        return grado;
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

    string getEcuacion(){
        return *ecuacion;
    }

    Biseccion:get_trigo_result(string trigonometry_function, string ecuation, int intervalo, int _pow){
        float result;
        if (trigonometry_function == "cos") {
            result = pow(cos(stoi(ecuation) * intervalo), _pow);
        } else if (trigonometry_function == "sen") {
            result = pow(sin(stoi(ecuation) * intervalo), _pow);
        } else if (trigonometry_function == "tan") {
            result = pow(tan(stoi(ecuation) * intervalo), _pow);
        }
        return result;
    }

    void sustituir(){
        string cases[3] = {"cos", "sen", "tan"};
        for (int i = 0; i < grado + 1; i++) {
            for (int j = 0; j < 3; j++){
                if (ecuacion[i].find(cases[j]) != string::npos){
                    cout << "encontro " << cases[j] << endl;
                    string copy_ecuacion;
                    copy_ecuacion = ecuacion[i];
                    copy_ecuacion.replace(0,4, "");
                    copy_ecuacion.replace(copy_ecuacion.length()-1, 1, "");
                    cout << copy_ecuacion << endl;
                    if (copy_ecuacion.find("x") != string::npos){
                        copy_ecuacion.replace(copy_ecuacion.find("x"), 1, "");
                    }
                    for (int k = intervalo1; k <= intervalo2; k++) {
                        cout << "inter " << intervalo[k] << endl;
                        float result;
                        result = self.get_trigo_result(
                                cases[j],
                                copy_ecuacion,
                                intervalo[k],
                                i);
                        cout << "encontro " << result << endl;
                    }
                }
            }
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
