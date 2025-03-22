#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>

class automobile {
    public:
        std::string name;
        int* fuelConsumption;
        int maxSpeed;
        int power;


        automobile() {
            name = "None";
            fuelConsumption = nullptr;
            maxSpeed = 0;
            power = 0;
        }


        automobile(std::string n, int* fc, int ms, int p) {
            name = n;
            fuelConsumption = new int[3];
            for (int i = 0; i < 3; i++) fuelConsumption[i] = fc[i];
            maxSpeed = ms;
            power = p;
        }


        automobile(const automobile& a1) {
            name = a1.name;
            if (a1.fuelConsumption) {
                fuelConsumption = new int[3];
                for (int i = 0; i < 3; i++) fuelConsumption[i] = a1.fuelConsumption[i];
            } else fuelConsumption = nullptr;
            maxSpeed = a1.maxSpeed;
            power = a1.power;
        }


        automobile(automobile&& a1) {
            std::swap(name, a1.name);
            std::swap(fuelConsumption, a1.fuelConsumption);
            std::swap(maxSpeed, a1.maxSpeed);
            std::swap(power, a1.power);
            a1.fuelConsumption = nullptr;
        }


        automobile& operator=(automobile& a1) {
            if (this != &a1) {
                name = a1.name;
                maxSpeed = a1.maxSpeed;
                power = a1.power;
                delete[] fuelConsumption;
                if (a1.fuelConsumption) {
                    fuelConsumption = new int[3];
                    for (int i = 0; i < 3; i++) fuelConsumption[i] = a1.fuelConsumption[i];
                }
                else fuelConsumption = nullptr;
            }
            return *this;
        }


        automobile& operator=(automobile&& a1) {
            if (this != &a1) {
                delete[] fuelConsumption;
                std::swap(name, a1.name);
                std::swap(fuelConsumption, a1.fuelConsumption);
                std::swap(maxSpeed, a1.maxSpeed);
                std::swap(power, a1.power);
                a1.fuelConsumption = nullptr;
            }
            return *this;
        }


        ~automobile() {
            delete[] fuelConsumption;
        }


        bool operator<(const automobile& a1) const {
            return name < a1.name;
        }


        bool operator<(const automobile& a1) {
            if (!fuelConsumption || !a1.fuelConsumption) {
                return false;
            }
            return fuelConsumption[2] < a1.fuelConsumption[2];
        }

        bool operator==(const automobile& a1) const {
            return name == a1.name && fuelConsumption == a1.fuelConsumption && maxSpeed == a1.maxSpeed && power == a1.power;
        }

        friend std::ofstream& operator << (std::ofstream& out, const automobile& a1) {
            out << a1.name << " ";
            if (a1.fuelConsumption) {
                for (int i = 0; i < 2; i++) out << a1.fuelConsumption[i] << ", ";
                out << a1.fuelConsumption[2]  << " ";
            }
            else out << "Empty";
            out << a1.maxSpeed  << " ";
            out << a1.power;
            out << std::endl;
            return out;
        }


        friend std::ifstream& operator >> (std::ifstream& ifs, automobile& a1) {
            ifs >> a1.name;
            if (a1.fuelConsumption) {
                delete[] a1.fuelConsumption;
            }
            a1.fuelConsumption = new int[3];
            ifs >> a1.fuelConsumption[0];
            ifs >> a1.fuelConsumption[1];
            ifs >> a1.fuelConsumption[2];
            ifs >> a1.maxSpeed;
            ifs >> a1.power;
            return ifs;
        }
};


struct automobileHasher {
    std::hash<std::string> nameHash;
    std::hash<int*> fConsumptionHash;
    std::hash<int> mSpeedHash;
        std::hash<int> powerHash;
        size_t operator()(const automobile& a1) const {
            const size_t c = 2'946'901;
            return (c * c * nameHash(a1.name) + c * c * fConsumptionHash(a1.fuelConsumption) + c * c * mSpeedHash(a1.maxSpeed) + c * c * powerHash(a1.power));
        }
};


int main() {
    std::ifstream fIn("input.txt");
    std::ofstream fOut("output.txt");
    int c;
    fIn >> c;
    std::list<automobile> aList;
    std::vector<automobile> aVector;
    std::set<automobile> aSet;
    std::unordered_set<automobile, automobileHasher> aUnorderedSet;
    for (int i = 0; i < c; i++) {
        automobile a1;
        fIn >> a1;
        aList.push_back(a1);
    }
    for (const auto& a1 : aList) {
        aVector.push_back(a1);
    }
    for (const auto& a1: aList) {
        aSet.insert(a1);
    }
    for (const auto& a1: aList) {
        aUnorderedSet.insert(a1);
    }
    fOut << "Not sorted list:" << std::endl;
    for (const auto& a1 : aList) {
        fOut << a1;
    }
    fOut << "Not sorted vector:" << std::endl;
    for (const auto& a1 : aVector) {
        fOut << a1;
    }
    fOut << "Not sorted set:" << std::endl;
    for (const auto& a1 : aSet) {
        fOut << a1;
    }
    fOut << "Not sorted unordered set:" << std::endl;
    for (const auto& a1 : aSet) {
        fOut << a1;
    }
    aList.sort();
    fOut << "Sorted list:" << std::endl;
    for (const auto& a1 : aList) {
        fOut << a1;
    }
    std::sort(aVector.begin(), aVector.end());
    fOut << "Sorted vector:" << std::endl;
    for (const auto& a1 : aVector) {
        fOut << a1;
    }
    return 1;
}
